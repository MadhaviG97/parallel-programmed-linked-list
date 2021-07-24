struct list_node_s {
    unsigned int data;
    struct list_node_s* next;
};

typedef int (*ll_function)(unsigned int, struct list_node_s**);

struct operation {
    ll_function function;
    unsigned int value;
};