#include "clists.h" 
int main() {
    node_t* head = new_linked_list(3, LINEAR_SINGLY_LINKED); 
    list_set_data(head, "Hello!", 2); 
    printf("%u\n", list_count_nodes(head)); 
    list_delete_node(head, 2, LINEAR_SINGLY_LINKED); 
    printf("%u\n", list_count_nodes(head));
    freelist(head);
}