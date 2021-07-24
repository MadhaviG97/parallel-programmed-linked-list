#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <math.h>

#include "helpers/headers/util.h"
#include "helpers/headers/constants.h"

struct operation operations[m] = { NULL };
struct list_node_s* ll_head = NULL;
pthread_mutex_t list_mutex;

void *doRandomOperations(void *rank);

int main(){

    init_linked_list(ll_head);
    generateRandomOperations(operations);

    long thread;
    pthread_t* thread_handles;

    if (pthread_mutex_init(&list_mutex, NULL) != 0) {
        printf("Mutex initialization failed.");
        return 1;
    }

    clock_t start, end;
    double cpu_time_used;

    start = clock();

    thread_handles = malloc(thread_count * sizeof(pthread_t));
    for (thread = 0; thread < thread_count; thread++){
        pthread_create(&thread_handles[thread], NULL, doRandomOperations, (void*) thread);
    }

    for (thread = 0; thread < thread_count; thread++){
        pthread_join(thread_handles[thread], NULL);
    }

    free(thread_handles);

    end = clock();

    cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;
    printf("\nprogram took %f seconds to execute \n\n", cpu_time_used);

    return 0;
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
