#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

#include "helpers/headers/util.h"
#include "helpers/headers/constants.h"

#define iterations 1

struct operation operations[m] = { NULL };
double Iteration();

int main(){
    int i;
    for ( i = 0; i < iterations; i++)
    {
       Iteration();
    }
    
    
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
    printf("\nprogram took %f seconds to execute \n\n", cpu_time_used);

    return cpu_time_used;    
}
