#ifndef LISTS_H
#define LISTS_H

#include <stdlib.h>
#include <stddef.h>
#include <stdio.h>

#define freelist(head) free(head)

enum node_type {NODE_HEAD, NODE_TAIL, NODE_BODY};
enum list_type {LINEAR_SINGLY_LINKED, LINEAR_DOUBLY_LINKED, CIRCULAR_SINGLY_LINKED, CIRCULAR_DOUBLY_LINKED};

struct node {
    void* data; 
    unsigned int type;
    struct node* next; 
    struct node* prev; 
};
typedef struct node node_t; 

typedef void (*printcallback_t)(void*);

/// @brief Create a singly linked list
/// @param nnode Number of nodes in the list
/// @return Return the head of the list
node_t* new_slist(unsigned int nnode) {
    node_t* nodes; 
    if (!(nodes = (node_t*) malloc(sizeof(node_t) * nnode))) {
        fprintf(stderr, "%s %d: Could'nt create nodes!\n", __FILE__, __LINE__);
        abort();
    } 

    unsigned int cnode; 
    for (cnode = 0; cnode < nnode; cnode++) {
        nodes[cnode].next = (cnode == (nnode-1)) ? NULL : (nodes+(cnode+1)); 
        nodes[cnode].prev = NULL; 
        nodes[cnode].type = (cnode == 0) ? NODE_HEAD : (cnode == (nnode-1)) ? NODE_TAIL : NODE_BODY;
    }

    return nodes;
}

/// @brief Creates a new circular singly linked list
/// @param nnode Number of nodes in the list
/// @return Returns pointer to head of the list
node_t* new_circular_slist(unsigned int nnode) {
    node_t* nodes = new_slist(nnode); 

    // Set the last node to the first 
    nodes[nnode-1].next = nodes; 

    return nodes;
}

/// @brief Creates a linear, doubly linked list
/// @param nnode Number of nodes
/// @return Returns a pointer to the head
node_t* new_dlist(unsigned int nnode) {
    node_t* nodes; 
    if (!(nodes = (node_t*) malloc(sizeof(node_t) * nnode))) {
        fprintf(stderr, "%s %d: Failed to create nodes!\n",__FILE__, __LINE__); 
        abort();
    }

    unsigned int cnode; 
    for (cnode = 0; cnode < nnode; cnode++) {
        nodes[cnode].next = (cnode == (nnode-1)) ? NULL : (nodes+(cnode+1));
        nodes[cnode].prev = (cnode == 0) ? NULL : (nodes+(cnode-1));
        nodes[cnode].type = (cnode == 0) ? NODE_HEAD : (cnode == (nnode-1)) ? NODE_TAIL : NODE_BODY; 
    }

    return nodes;
}

/// @brief Creates a new circular doubly linked list
/// @param nnode Number of nodes
/// @return Returns a pointer to the head of the list
node_t* new_circular_dlist(unsigned int nnode) {
    node_t* nodes = new_dlist(nnode); 

    // Connect the end to form a circle
    nodes[0].prev = (nodes+(nnode-1)); 
    nodes[nnode-1].next = nodes;

    return nodes;
}

/// @brief Retrieves the location of a node
/// @param head The memory address of head
/// @param pnode The position of the node within the list (lists start at 1)
/// @return Returns a pointer to the retrieved node
node_t* list_get_node(node_t* head, unsigned int pnode) {
    node_t* node = (head); 
    for (int i = 0; i < (pnode-1); ++i) node = node->next; 
    return node;
}

/// @brief Get the last node of a linked list
/// @param head The first node in the list
/// @return Returns the last node
node_t* list_get_tail(node_t* head) {
    node_t* tail;
    for (tail = head; (tail->next) && (tail->next != head); tail = tail->next);
    return tail;  
}

/// @brief Sets data at a specific node
/// @param head The memory address of the head node
/// @param userdata The data to be set
/// @param pnode The position of the node in the list (lists start at 1)
/// @return Returns a pointer to the node where data was set
node_t* list_set_data(node_t** head, void* userdata, unsigned int pnode) {
    node_t* node;
    if (!(node = list_get_node(*head, pnode))) {
        fprintf(stderr, "%s %d: Node does not exist at %d\n", __FILE__, __LINE__, pnode); 
        abort();
    }
    node->data = userdata; 
    return node;
}

/// @brief Counts the number of nodes including the current node and every node after it
/// @param cnode The pointer to the current node in the list
/// @return Returns the number of nodes in the list
unsigned int list_count_nodes(node_t* cnode) {
    node_t* node = (cnode) ? cnode : NULL;
    unsigned int nnode = 0; 
    for (nnode = !(node) ? 0: 1; (node = node->next) && (node != cnode); nnode++);
    return nnode;
}

/// @brief Prints the data within linked
/// @param cnode The current node to print after
/// @param printnode_callback A callbeck function to print the data of a node
void list_print_nodes(node_t* cnode, printcallback_t printnode_callback) {
    unsigned int nnode = list_count_nodes(cnode); 
    for (int i = 0; i < nnode; ++i) {
        printnode_callback(cnode->data); 
        cnode = cnode->next;    
    }
}
#endif//LISTS_H