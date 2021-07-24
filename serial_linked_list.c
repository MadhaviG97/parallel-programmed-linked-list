#include <time.h>
#include <math.h>

#include "helpers/headers/util.h"
#include "helpers/headers/constants.h"

struct operation operations[m] = { NULL };
double Iteration();

int main(){
    int i;
    double sum;
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
    printf("SRL - Average: %f, STD: %f\n", average, std);    
    return 0;
}

double Iteration(){
    struct list_node_s* ll_head = NULL;

    init_linked_list(ll_head);
    generateRandomOperations(operations);
    
    clock_t start, end;
    double cpu_time_used;

    start = clock();
    for (int i = 0; i < m; i++)
    {
        (*(operations[i].function))(operations[i].value, &ll_head);
    }    
    end = clock();
    cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;

    return cpu_time_used;    
}

