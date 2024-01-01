#include "clists.h" 
int main() {
    node_t* head = new_circular_dlist(4); 
    list_set_data(&head, "Hello!", 4); 
    node_t* tail = list_get_tail(head); 
    puts(tail->data);
    freelist(head);
}