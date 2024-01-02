#include "clists.h" 
int main() {
    node_t* head = new_circular_slist(3);
    list_set_data(head, "Yo", 1); 
    list_set_data(head, "Duuududud", 2); 
    list_set_data(head, "Na!", 3);
    for (int i = 0; i < 6; ++i) {
        puts(head->data); 
        head = head->next;
    } 
    freelist(head);
}