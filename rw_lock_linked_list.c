#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <math.h>
#include <sys/time.h>

#include "helpers/headers/util.h"
#include "helpers/headers/constants.h"

struct operation operations[m] = { NULL };
struct list_node_s* ll_head = NULL;
pthread_rwlock_t rw_lock;

void *doRandomOperations(void *rank);
double Iteration();

int main(){
    int i;
    double sum = 0;
    double time[iterations];

    for(i = 0; i < iterations; i++)
    {
        time[i] = Iteration();
        sum += time[i];
    }

    double average = sum/iterations;
    double error_sum = 0;

    for ( i = 0; i < iterations; i++)
    {
       error_sum += pow(time[i]-average, 2);
    }
    
    double std = sqrt(error_sum/iterations);
    printf("RWL - Average: %f, STD: %f\n", average, std);    
    return 0;

    return 0;
}

double Iteration(){
    init_linked_list(ll_head);
    generateRandomOperations(operations);

    long thread;
    pthread_t* thread_handles;

    if (pthread_rwlock_init(&rw_lock, NULL) != 0) {
        printf("Read/write lock initialization failed.");
        return 1;
    }

    // clock_t start, end;
    // double cpu_time_used;
    // start = clock();

    struct timeval begin, end;
    gettimeofday(&begin, 0);

    thread_handles = malloc(thread_count * sizeof(pthread_t));
    for (thread = 0; thread < thread_count; thread++){
        pthread_create(&thread_handles[thread], NULL, doRandomOperations, (void*) thread);
    }

    for (thread = 0; thread < thread_count; thread++){
        pthread_join(thread_handles[thread], NULL);
    }

    free(thread_handles);
    pthread_rwlock_destroy(&rw_lock);

    // end = clock();
    // cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;

    gettimeofday(&end, 0);
    long seconds = end.tv_sec - begin.tv_sec;
    long microseconds = end.tv_usec - begin.tv_usec;
    double elapsed = seconds + microseconds*1e-6;

    return elapsed;
}

void *doRandomOperations(void *rank) {
    long my_rank = (long) rank;

    int local_m = m/thread_count;
    int my_first_row = my_rank * local_m;
    int my_last_row = (my_rank + 1) * local_m - 1;

    int i;
    for (i = my_first_row; i <= my_last_row; i++){
        if (*Member == (operations[i].function)){            
            pthread_rwlock_rdlock(&rw_lock);
            (*(operations[i].function))(operations[i].value, &ll_head);
            pthread_rwlock_unlock(&rw_lock);
        }
        else{
            pthread_rwlock_wrlock(&rw_lock);
            (*(operations[i].function))(operations[i].value, &ll_head);
            pthread_rwlock_unlock(&rw_lock);
        }
    }

    return NULL;
}