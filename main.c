#include <stdio.h>
#include <stdlib.h>
#include<time.h>

struct list_node_s {
    int data;
    struct list_node_s* next;
};

int Insert(int value, struct list_node_s** head_pp);
int Member(int value, struct list_node_s* head_p);

int main(){
    int upper=10;
    int lower=0;
    int noOfElements=5;
    struct list_node_s* ll_head;

    srand(time(0));

    int i;
    int last;
    for (i = 0; i < noOfElements; i++){
        int rand_numb = (rand() % (upper - lower + 1)) + lower;
        Insert(rand_numb, &ll_head);
    }
    Member(12, ll_head);

    // struct list_node_s* s;
    // s = malloc(sizeof(struct list_node_s));
    // curr->data = ll_head->data;
    // curr->next = ll_head->next;
    // while (curr !=NULL){
    //     printf("%d\n",curr->data);
    //     curr = curr->next;
    // }

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

int Member(int value, struct list_node_s* head_p){
    struct list_node_s* curr_p = head_p;

    while (curr_p !=NULL && curr_p->data < value){ 
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
