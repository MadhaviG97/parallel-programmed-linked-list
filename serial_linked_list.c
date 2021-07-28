#include <time.h>
#include <math.h>
#include <sys/time.h>

#include "helpers/headers/util.h"
#include "helpers/headers/constants.h"

struct operation operations[m] = { {NULL} };
double Iteration();

int main(){
    int i;
    double sum = 0;
    double ab[iterations];

    for(i = 0; i < iterations; i++)
    {
        ab[i] = Iteration();
        sum += ab[i];
    }

    double average = sum/(double) iterations;
    double error_sum = 0;

    for ( i = 0; i < iterations; i++)
    {
       error_sum += pow(ab[i]-average, 2);
    }
    
    double std = 0;
    if (iterations != 1){
        std = sqrt(error_sum/iterations);
    }
    printf("SRL - Average: %f, STD: %f\n", average, std);    
    return 0;
}

double Iteration(){
    struct list_node_s* ll_head = NULL;

    init_linked_list(ll_head);
    generateRandomOperations(operations);
    
    // clock_t start, end;
    // double cpu_time_used;
    // start = clock();

    struct timeval begin, end;
    gettimeofday(&begin, 0);

    for (int i = 0; i < m; i++)
    {
        (*(operations[i].function))(operations[i].value, &ll_head);
    }   

    // end = clock();
    // cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;

    gettimeofday(&end, 0);
    long seconds = end.tv_sec - begin.tv_sec;
    long microseconds = end.tv_usec - begin.tv_usec;
    double elapsed = seconds + microseconds*1e-6;

    return elapsed;    
}

