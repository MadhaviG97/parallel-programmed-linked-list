#include <stdio.h>
#include <stdlib.h>
#include<time.h>
#include<math.h>

struct list_node_s {
    int data;
    struct list_node_s* next;
};

int Insert(int value, struct list_node_s** head_pp);
int Member(int value, struct list_node_s** head_pp);
int Delete(int value, struct list_node_s** head_pp);

int main(){
    int upper= (int) pow((double) 2, 16) - 1;
    int lower=0;
    int n=5; int m=10000;   
    int op_upper=1000; int op_lower=1; 

    int m_member = (int) (0.99*m); 
    int m_insert = (int) (0.005*m); 
    int m_delete = (int) (0.005*m);

    const int w_member = (int) (0.99*op_upper); 
    const int w_insert = (int) (0.005*op_upper); 
    const int w_delete = (int) (0.005*op_upper);
    
    struct list_node_s* ll_head=NULL;

    srand(time(0));
    
    int i=0;
    while (i < n){            
        int rand_numb = (rand() % (upper - lower + 1)) + lower;
        int return_val = Insert(rand_numb, &ll_head);
        if (return_val==1){
            i++;
        }
    }
    
    int (*operation_arr[m])(int, struct list_node_s**);
    int operand_arr[m];
    i=0;
    while ((m_member+m_insert+m_delete)!=0)
    {
        int operation = (rand() % (op_upper-op_lower+1)) + op_lower;
        int rand_numb = (rand() % (upper - lower)) + lower;

        if ((w_member >= operation) && (m_member!=0)){
            m_member--;
            operation_arr[i]=Member;
            operand_arr[i]=rand_numb;
            i++;
        }
        else if ((w_member < operation) && 
                    (w_insert+w_member >= operation) && 
                    (m_insert!=0)){
            m_insert--;
            operation_arr[i]=Insert;
            operand_arr[i]=rand_numb;
            i++;
        }
        else if (((w_insert+w_member) < operation) && 
                    (w_delete+w_insert+w_member >= operation) && 
                    (m_delete!=0)){
            m_delete--;
            operation_arr[i]=Delete;
            operand_arr[i]=rand_numb;
            i++;
        }
    }

    for (i = 0; i < m; i++)
    {
        (*operation_arr[i])(operand_arr[i], &ll_head);
    }    

    return 0;
}

int Insert(int value, struct list_node_s** head_pp){
    struct list_node_s* curr_p = *head_pp;
    struct list_node_s* pred_p = NULL;
    struct list_node_s* temp_p;

    while (curr_p !=NULL && curr_p->data < value){
        pred_p = curr_p;
        curr_p = curr_p->next;
    }
    
    if (curr_p == NULL || curr_p->data > value){
        temp_p = malloc(sizeof(struct list_node_s));
        temp_p->data = value;
        temp_p->next = curr_p;
        if (pred_p == NULL) // newly adding the first node
            *head_pp = temp_p;
        else
            pred_p->next = temp_p;
        return 1;
    }
    else // value in list
        return 0;
        
}

int Member(int value, struct list_node_s** head_pp){
    struct list_node_s* curr_p = *head_pp;

    while (curr_p !=NULL && curr_p->data < value){ 
        // printf("item: %d\n", curr_p->data);
        curr_p = curr_p->next;
    }

    if (curr_p == NULL || curr_p->data > value)
        return 0;
    else
        return 1;
}

int Delete(int value, struct list_node_s** head_pp){
    struct list_node_s* curr_p = *head_pp;
    struct list_node_s* pred_p = NULL;

    while (curr_p !=NULL && curr_p->data < value){
        pred_p = curr_p;
        curr_p = curr_p->next;
    }

    if (curr_p != NULL && curr_p->data == value){
        if (pred_p == NULL){ // del first node
            *head_pp = curr_p->next;
            free(curr_p);
        }
        else{
            pred_p->next = curr_p->next;
            free(curr_p);
        }
        return 1;
    }
    else    
        return 0;
}
