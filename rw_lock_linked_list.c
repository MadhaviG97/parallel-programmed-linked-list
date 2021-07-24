#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

#include "util.h"

#define thread_count 8
#define m 10000

struct list_node_s {
    int data;
    struct list_node_s* next;
};

pthread_mutex_t list_mutex;

void *doRandomOperations(void* rank);

int main(){

    long thread;
    pthread_t* thread_handles;

    if (pthread_mutex_init(&list_mutex, NULL) != 0) {
        printf("Mutex initialization failed.");
        return 1;
    }

    thread_handles = malloc(thread_count * sizeof(pthread_t));
    for (thread = 0; thread < thread_count; thread++){
        pthread_create(&thread_handles[thread], NULL, doRandomOperations, (void*) thread);
    }

    return 0;
}

void *doRandomOperations(void* rank) {
    long my_rank = (long) rank;
    int local_m = m/thread_count;
    int my_first_row = my_rank * local_m;
    int my_last_row = (my_rank + 1) * local_m - 1;

    int i;
    for (i = my_first_row; i <= my_last_row; i++){
        // (*operation_arr[i])(operand_arr[i], &ll_head);
    }
}