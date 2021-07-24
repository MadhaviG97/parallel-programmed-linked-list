struct list_node_s {
    unsigned int data;
    struct list_node_s* next;
};

typedef int (*ll_operation)(unsigned int, struct list_node_s**);