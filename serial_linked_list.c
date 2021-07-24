#include <stdio.h>
#include <stdlib.h>
#include<time.h>
#include<math.h>

#include "helpers/headers/util.h"
#include "helpers/headers/constants.h"

typedef int (*ll_operation)(unsigned int, struct list_node_s**);

void init_linked_list(struct list_node_s* ll_head);
void generateRandomOperations(ll_operation operation_arr[], unsigned int operand_arr[]);

int main(){
    ll_operation operation_arr[m] = { NULL };
    unsigned int operand_arr[m];
    struct list_node_s* ll_head = NULL;

    init_linked_list(ll_head);
    generateRandomOperations(operation_arr, operand_arr);
    
    clock_t begin = clock();
    for (int i = 0; i < m; i++)
    {
        (*operation_arr[i])(operand_arr[i], &ll_head);
    }    
    clock_t end = clock();
    double time_spent = (double)(end - begin) / CLOCKS_PER_SEC;

    printf("%f\n", time_spent);

    return 0;
}