#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <math.h>

#include "helpers/headers/util.h"
#include "helpers/headers/constants.h"

struct operation operations[m] = { {NULL} };
struct list_node_s* ll_head = NULL;
pthread_mutex_t list_mutex;

void *doRandomOperations(void *rank);
double Iteration();

int main(){
    int i;
    double sum=0;
    double time[iterations];

    for(i = 0; i < iterations; i++)
    {
        time[i] = Iteration()*pow(10,6);
        sum += time[i];
        // printf("%f\n", time[i]);
    }

    double average = sum/iterations;
    double error_sum = 0;

    for ( i = 0; i < iterations; i++)
    {
       error_sum += pow(time[i]-average, 2);
    }
    
    double std = sqrt(error_sum/(iterations-1));
    double suff_n = (100*1.96*std)/(5*average);

    printf("MTX - Average: %f, STD: %f n: %f\n", average, std, pow(suff_n,2));
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

    struct timespec start, finish;    
    clock_gettime(CLOCK_MONOTONIC, &start);

    thread_handles = malloc(thread_count * sizeof(pthread_t));
    for (thread = 0; thread < thread_count; thread++){
        pthread_create(&thread_handles[thread], NULL, doRandomOperations, (void*) thread);
    }

    for (thread = 0; thread < thread_count; thread++){
        pthread_join(thread_handles[thread], NULL);
    }

    pthread_mutex_destroy(&list_mutex);

    free(thread_handles);

    clock_gettime(CLOCK_MONOTONIC, &finish);

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
