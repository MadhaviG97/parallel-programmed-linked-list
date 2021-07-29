#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include <sys/time.h>

#include "helpers/headers/util.h"
#include "helpers/headers/constants.h"

// struct operation operations[m] = { {NULL} };
int operations[m];

struct list_node_s* ll_head = NULL;
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
    
    double std = 0;
    if (iterations != 1){
        std = sqrt(error_sum/iterations);
    }
    printf("SRL - Average: %f, STD: %f\n", average, std);    
    return 0;
}

double Iteration(){

    init_linked_list(ll_head);
    generateRandomOperations(operations);
    
    // clock_t start, end;
    // double cpu_time_used;
    // start = clock();

    // struct timeval begin, end;
    // gettimeofday(&begin, 0);

    struct timespec start, finish;
    clock_gettime(CLOCK_REALTIME, &start);

    for (int i = 0; i < m; i++)
    {
        // (*(operations[i].function))(operations[i].value, &ll_head);
        if (operations[i] == 0) {
            unsigned int rand_numb = (rand() % (upper - lower)) + lower;
            Member(rand_numb, ll_head);
        } else if (operations[i] == 1) {
            unsigned int rand_numb = (rand() % (upper - lower)) + lower;
            Insert(rand_numb, &ll_head);
        } else {
            unsigned int rand_numb = (rand() % (upper - lower)) + lower;
            Delete(rand_numb, &ll_head);
        }
    }   

    // end = clock();
    // cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;

    // gettimeofday(&end, 0);
    // long seconds = end.tv_sec - begin.tv_sec;
    // long microseconds = end.tv_usec - begin.tv_usec;
    // double elapsed = seconds + microseconds*1e-6;

    clock_gettime(CLOCK_REALTIME, &finish);
    double time_spent = (finish.tv_sec - start.tv_sec) +
                        ((finish.tv_nsec - start.tv_nsec) / BILLION);

    return time_spent;    
}

