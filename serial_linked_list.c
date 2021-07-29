#include <time.h>
#include <math.h>

#include "helpers/headers/util.h"
#include "helpers/headers/constants.h"

struct operation operations[m] = { {NULL} };
double Iteration();

int main(){
    int i;
    double sum=0;
    double time[iterations];

    for(i = 0; i < iterations; i++)
    {
        time[i] = Iteration()*pow(10,6);
        sum += time[i];
    }

    double average = sum/iterations;
    double error_sum = 0;

    for ( i = 0; i < iterations; i++)
    {
       error_sum += pow(time[i]-average, 2);
    }
    
    double std = sqrt(error_sum/(iterations-1));
    double suff_n = pow( ((100*1.96*std)/(5*average)) ,2);

    printf("SRL - Average: %f, STD: %f n: %f\n", average, std, suff_n);

    return 0;
}

double Iteration(){
    struct list_node_s* ll_head = NULL;

    init_linked_list(ll_head);
    generateRandomOperations(operations);

    struct timespec start, finish;
    clock_gettime(CLOCK_REALTIME, &start);

    for (int i = 0; i < m; i++)
    {
        (*(operations[i].function))(operations[i].value, &ll_head);
    }

    clock_gettime(CLOCK_REALTIME, &finish);
    double time_spent = (finish.tv_sec - start.tv_sec) +
                        ((finish.tv_nsec - start.tv_nsec) / BILLION);

    return time_spent;
}

