#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <math.h>
#include <sys/time.h>

#include "helpers/headers/util.h"
#include "helpers/headers/constants.h"

struct operation operations[m] = { {NULL} };
struct list_node_s* ll_head = NULL;
pthread_mutex_t list_mutex = PTHREAD_MUTEX_INITIALIZER;;

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
    printf("MUT - Average: %f, STD: %f\n", average, std);    
    return 0;
}

double Iteration(){
    init_linked_list(ll_head);
    generateRandomOperations(operations);

    long thread;
    pthread_t* thread_handles;

    if (pthread_mutex_init(&list_mutex, NULL) != 0) {
        printf("Mutex initialization failed.");
        return 1;
    }

    // clock_t start, end;
    // double cpu_time_used;
    // start = clock();

    // struct timeval begin, end;
    // gettimeofday(&begin, 0);

    struct timespec start, finish;    
    clock_gettime(CLOCK_REALTIME, &start);

    thread_handles = malloc(thread_count * sizeof(pthread_t));
    for (thread = 0; thread < thread_count; thread++){
        pthread_create(&thread_handles[thread], NULL, doRandomOperations, (void*) thread);
    }

    for (thread = 0; thread < thread_count; thread++){
        pthread_join(thread_handles[thread], NULL);
    }

    pthread_mutex_destroy(&list_mutex);

    free(thread_handles);
    
    // end = clock();
    // cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;

    // gettimeofday(&end, 0);
    // long seconds = end.tv_sec - begin.tv_sec;
    // long microseconds = end.tv_usec - begin.tv_usec;
    // double elapsed = seconds + microseconds*1e-6;

    clock_gettime(CLOCK_REALTIME, &finish);
    double time_spent = (finish.tv_sec - start.tv_sec) + ((finish.tv_nsec - start.tv_nsec) / BILLION);

    return time_spent;

}



void *doRandomOperations(void *rank) {
    long my_rank = (long) rank;

    int local_m = m/thread_count;
    int my_first_row = my_rank * local_m;
    int my_last_row = (my_rank + 1) * local_m - 1;

    int i;
    for (i = my_first_row; i <= my_last_row; i++){
        pthread_mutex_lock(&list_mutex);
        (*(operations[i].function))(operations[i].value, &ll_head);
        pthread_mutex_unlock(&list_mutex);
    }

    return NULL;
}
