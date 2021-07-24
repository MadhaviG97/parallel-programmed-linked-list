#include <stdio.h>
#include <stdlib.h>
#include<time.h>
#include<math.h>

#include "../headers/util.h"
#include "../headers/constants.h"

void generateRandomOperations(ll_operation operation_arr[], unsigned int operand_arr[]) {

    int m_member = (int) (p_member*m); 
    int m_insert = (int) (p_insert*m); 
    int m_delete = (int) (p_delete*m);

    const int w_member = (int) (p_member*op_upper); 
    const int w_insert = (int) (p_insert*op_upper); 
    const int w_delete = (int) (p_delete*op_upper);
    
    int i = 0;
    while ((m_member + m_insert + m_delete) != 0)
    {
        int operation = (rand() % (op_upper - op_lower + 1)) + op_lower;
        unsigned int rand_numb = (rand() % (upper - lower)) + lower;

        if ((w_member >= operation) && (m_member != 0)){
            m_member--;
            operation_arr[i] = Member;
            operand_arr[i] = rand_numb;
            i++;
        }
        else if ((w_member < operation) && 
                    (w_insert + w_member >= operation) && 
                    (m_insert != 0)){
            m_insert--;
            operation_arr[i] = Insert;
            operand_arr[i] = rand_numb;
            i++;
        }
        else if (((w_insert + w_member) < operation) && 
                    (w_delete + w_insert + w_member >= operation) && 
                    (m_delete != 0)){
            m_delete--;
            operation_arr[i] = Delete;
            operand_arr[i] = rand_numb;
            i++;
        }
    }
    return;
}

void init_linked_list(struct list_node_s* ll_head){
    srand(time(0));
    
    int i = 0;
    while (i < n){            
        int rand_numb = (rand() % (upper - lower + 1)) + lower;
        int return_val = Insert(rand_numb, &ll_head);
        if (return_val == 1){
            i++;
        }
    }
}