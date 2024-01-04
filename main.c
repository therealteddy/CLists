#include "clists.h"
#include <locale.h> 

void printcallback(void* data) {
    puts((char*) data);
}

int main() {
    node_t* head = new_linked_list(10, LINEAR_SINGLY_LINKED_LIST); 
    printf("%u\n", list_count_nodes(head)); 
    node_t* reverse_head = slist_reverse(head); 
    freelist(reverse_head);
}
