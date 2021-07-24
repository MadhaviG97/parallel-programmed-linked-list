#include <stdio.h>
#include "structs.h"

int Insert(unsigned int value, struct list_node_s** head_pp);
int Member(unsigned int value, struct list_node_s** head_pp);
int Delete(unsigned int value, struct list_node_s** head_pp);

void generateRandomOperations(ll_operation operation_arr[], unsigned int operand_arr[]);
void init_linked_list(struct list_node_s* ll_head);