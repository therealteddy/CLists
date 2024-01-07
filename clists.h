#ifndef LISTS_H
#define LISTS_H

#include <stdlib.h>
#include <stddef.h>
#include <stdio.h>

#define freelist(head) free(head)
#define freenode(node_) free(node_)

enum node_types {
    NODE_HEAD, 
    NODE_TAIL, 
    NODE_BODY
};

enum list_types {
    LINEAR_SINGLY_LINKED_LIST,
    LINEAR_DOUBLY_LINKED_LIST,
    CIRCULAR_SINGLY_LINKED_LIST, 
    CIRCULAR_DOUBLY_LINKED_LIST
};

enum zip_types {
    ZIP_LINEAR_SINGLY_LINKED_LISTS,
    ZIP_LINEAR_DOUBLY_LINKED_LISTS, 
    ZIP_CIRCULAR_SINGLY_LINKED_LISTS, 
    ZIP_CIRCULAR_DOUBLY_LINKED_LISTS
}; 

struct node {
    void* data; 
    unsigned int type;
    struct node* next; 
    struct node* prev; 
};
typedef struct node node_t; 

typedef void (*printcallback_t)(void*);

/// @brief Counts the number of nodes from cnode
/// @param cnode The node to start counting from 
/// @return Returns the number of nodes from cnode
unsigned int list_count_nodes(node_t* cnode) {
    unsigned int nnode;
    node_t* node = cnode; 
    for (nnode = (node) ? 1 : 0; (node = node->next) ; nnode++) if (node == cnode) break;
    return nnode;
}

/// @brief Get the node at pnode
/// @param head A pointer to the first node in the list
/// @param pnode Position of the node you want
/// @return Returns a pointer to the node at pnode
node_t* list_get_node(node_t* head, unsigned int pnode) {
    if (!head) {
        fprintf(stderr, "%s %d: List is empty!\n", __FILE__, __LINE__); 
        return NULL;
    } else if (pnode < 1 || pnode > list_count_nodes(head)) {
        fprintf(stderr, "%s %d: Node does'nt exist at %u\n", __FILE__, __LINE__, pnode); 
        return NULL;
    }
    for (int i = 0; i++ < pnode-1; head = head->next); 
    return head;
}


/// @brief Sets data of a specific node 
/// @param head The first node of the list 
/// @param nodedata The data you would like to set to the node 
/// @param pnode The position of the node you would like to set data to 
/// @return Returns a pointer to the node data was set to
node_t* list_set_data(node_t* head, void* nodedata, unsigned int pnode) {
    if (!head) {
        fprintf(stderr, "%s %d: List is empty!\n", __FILE__, __LINE__); 
        return NULL;
    } else if (pnode < 1 || pnode > list_count_nodes(head)) {
        fprintf(stderr, "%s %d: Node does'nt exist at %u\n", __FILE__, __LINE__, pnode); 
        return NULL;
    }
    return list_get_node(head, pnode)->data = nodedata;
}

/// @brief Get the last node of a list 
/// @param head The first node in a list 
/// @return Returns NULL if list is empty, and a pointer to the last node if otherwise
node_t* list_get_tail(node_t* head) {
    if (!head) {
        fprintf(stderr, "%s %d: List is empty!\n", __FILE__, __LINE__); 
        return NULL;
    }
    return list_get_node(head, list_count_nodes(head));
}

/// @brief Create a singly linked list
/// @param nnode Number of nodes in the list
/// @return Return the head of the list
node_t* new_slist(unsigned int nnode) {
    node_t* nodes; 
     if (!nnode) {
        fprintf(stderr, "%s %d: Can't create a list with no nodes!\n", __FILE__, __LINE__);
        return NULL;
    } else if (!(nodes = (node_t*) malloc(sizeof(node_t) * nnode))) {
        fprintf(stderr, "%s %d: Failed to create nodes!\n", __FILE__, __LINE__);
        return NULL;
    }
    unsigned int cnode; 
    for (cnode = 0; cnode < nnode; cnode++) {
        nodes[cnode].next = (cnode == (nnode-1)) ? NULL : (nodes+(cnode+1)); 
        nodes[cnode].prev = NULL; 
        nodes[cnode].type = (cnode == 0) ? NODE_HEAD : (cnode == (nnode-1)) ? NODE_TAIL : NODE_BODY;
    }

    return nodes;
}

/// @brief Creates a linear, doubly linked list
/// @param nnode Number of nodes
/// @return Returns a pointer to the head
node_t* new_dlist(unsigned int nnode) {
    node_t* nodes; 
    if (!nnode) {
        fprintf(stderr, "%s %d: Can't create a list with no nodes!\n", __FILE__, __LINE__);
        return NULL;
    } else if (!(nodes = (node_t*) malloc(sizeof(node_t) * nnode))) {
        fprintf(stderr, "%s %d: Failed to create nodes!\n",__FILE__, __LINE__); 
        return NULL;
    }

    unsigned int cnode; 
    for (cnode = 0; cnode < nnode; cnode++) {
        nodes[cnode].next = (cnode == (nnode-1)) ? NULL : (nodes+(cnode+1));
        nodes[cnode].prev = (cnode == 0) ? NULL : (nodes+(cnode-1));
        nodes[cnode].type = (cnode == 0) ? NODE_HEAD : (cnode == (nnode-1)) ? NODE_TAIL : NODE_BODY; 
    }

    return nodes;
}

/// @brief Create a new circular singly linked list 
/// @param nnode The number of nodes in the list
/// @return Returns a pointer to the head of the new list
node_t* new_circular_slist(unsigned int nnode) {
    node_t* head = new_slist(nnode); 
    return (list_get_tail(head)->next = head);
}

/// @brief Create a new circular doubly linked list
/// @param nnode Number of nodes in the new list
/// @return Returns pointer to the head of the newly created list
node_t* new_circular_dlist(unsigned int nnode) {
    node_t* head = new_dlist(nnode); 
    node_t* tail = list_get_tail(head); 
    head->prev = tail; 
    tail->next = head;
    return head;
}

/// @brief Create a linked list
/// @param nnode Number of nodes
/// @param ltype Type of list to create
/// @return Returns pointer to the head of the new list or NULL if failed to create a new list
node_t* new_linked_list(unsigned int nnode, unsigned int ltype) {
    switch (ltype)
    {
    case LINEAR_SINGLY_LINKED_LIST: 
        return new_slist(nnode); 
        break;
    
    case LINEAR_DOUBLY_LINKED_LIST: 
        return new_dlist(nnode); 
        break; 

    case CIRCULAR_SINGLY_LINKED_LIST: 
        return new_circular_slist(nnode); 
        break; 

    case CIRCULAR_DOUBLY_LINKED_LIST: 
        return new_circular_dlist(nnode); 
        break; 
    
    default:
        fprintf(stderr, "%s %d: Invalid list type!\n", __FILE__, __LINE__);
        return NULL;
        break;
    }
}

/// @brief Prints the data within linked
/// @param cnode The current node to print after
/// @param printnode_callback A callbeck function to print the data of a node
void list_print_nodedata(node_t* cnode, printcallback_t printnode_callback) {
    if (!cnode) {
        fprintf(stderr, "%s %d: List Doesn't exist!!\n", __FILE__, __LINE__);
        abort();
    }
    unsigned int nnode = list_count_nodes(cnode);
    for (int i = 0; (i++ < nnode); cnode = cnode->next) if (cnode->data) printnode_callback(cnode->data); 
}

/// @brief zip two linear singly linked list togther
/// @param xlist The list whose end ylist will append to
/// @param ylist The list which will be attached to the end of xlist 
/// @returns The head node to the new list
node_t* slist_zip(node_t* xlist, node_t* ylist) {
    node_t* xlist_tail = list_get_tail(xlist); 
    xlist_tail->next = ylist;
    xlist_tail->type = NODE_BODY;
    ylist->type = NODE_BODY; 
    return xlist;
}

/// @brief zip two linear doubly linked list togther
/// @param xlist The list whose end ylist will append to
/// @param ylist The list which will be attached to the end of xlist
/// @returns The head node of the new list 
node_t* dlist_zip(node_t* xlist, node_t* ylist) {
    node_t* xlist_tail = list_get_tail(xlist); 
    xlist_tail->next = ylist; 
    ylist->prev = xlist_tail;
    xlist_tail->type = NODE_BODY;
    ylist->type = NODE_BODY; 
    return xlist;
}

/// @brief zip two circular singly linked list togther
/// @param xlist The list whose end ylist will append to
/// @param ylist The list which will be attached to the end of xlist 
/// @returns The head node of the new list 
node_t* circular_slist_zip(node_t* xlist, node_t* ylist) {
    node_t* xlist_tail = list_get_tail(xlist); 
    xlist_tail->next = ylist; 

    node_t* ylist_tail = list_get_tail(ylist); 
    ylist_tail->next = xlist;

    ylist->type = NODE_BODY;
    xlist_tail->type = NODE_BODY;

    return xlist;
}

/// @brief zip two circular doubly linked list togther
/// @param xlist The list whose end ylist will append to
/// @param ylist The list which will be attached to the end of xlist 
/// @returns The head node of the new list 
node_t* circular_dlist_zip(node_t* xlist, node_t* ylist) {
    node_t* xlist_tail = list_get_tail(xlist); 
    xlist_tail->next = ylist; 

    node_t* ylist_tail = list_get_tail(ylist); 
    ylist_tail->next = xlist;

    ylist->prev = xlist_tail; 
    xlist->prev = ylist_tail;

    return xlist;
}

/// @brief zip two linked lists togther
/// @param x_list The list whose end ylist will append to
/// @param y_list The list which will be attached to the end of xlist 
/// @param ziptype The type of zipping to perform
/// @returns The head node of the new list 
node_t* list_zip(node_t* x_list, node_t* y_list, unsigned int ziptype) {
    switch (ziptype)
    {
    case ZIP_LINEAR_SINGLY_LINKED_LISTS: 
        return slist_zip(x_list, y_list); 
        break;

    case ZIP_LINEAR_DOUBLY_LINKED_LISTS: 
        return dlist_zip(x_list, y_list); 
        break; 

    case ZIP_CIRCULAR_SINGLY_LINKED_LISTS: 
        return circular_slist_zip(x_list, y_list); 
        break;

    case ZIP_CIRCULAR_DOUBLY_LINKED_LISTS: 
        return circular_dlist_zip(x_list, y_list); 
        break;
    
    default:
        fprintf(stderr, "%s %d: Invalid zip type!\n", __FILE__, __LINE__); 
        return NULL;
        break;
    }
}

#endif//LISTS_H