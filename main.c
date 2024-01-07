#include "clists.h"
#include <locale.h> 

void printcallback(void* data) {
    puts((char*) data);
}

int main() {
    node_t* head = new_slist(10); 
    list_set_data(head, "world!", 1); 
    list_set_data(head, "hello, ", 10);
    node_t* rhead = slist_reverse(head);
    freelist(rhead); 
}
