# CLists

A C library providing functionality for various types of linked lists: linear singly linked, linear doubly linked, circular singly linked, and circular doubly linked lists. The library offers operations such as creating lists, inserting nodes, setting data, and more.

## Table of Contents

- [Introduction](#introduction)
- [List Types](#list-types)
- [Functions](#functions)
- [Contributing](#contributing)
- [License](#license)

## Introduction

This library provides a set of functions for working with linked lists in C. Linked lists are data structures that consist of nodes, each containing a data element and a reference to the next (and optionally, the previous) node in the sequence.

## List Types

The library supports the following types of linked lists:

- Linear Singly Linked List
- Linear Doubly Linked List
- Circular Singly Linked List
- Circular Doubly Linked List

## Functions

### `node_t* new_linked_list(unsigned int nnode, unsigned int ltype)` 

Create a new linked list

### `node_t* list_get_node(node_t** head, unsigned int pnode)`

Retrieves the location of a node at the specified position.

### `node_t* list_set_data(node_t** head, void* userdata, unsigned int pnode)`

Sets data at a specific node in the list.

### `unsigned int list_count_nodes(node_t* cnode)`

Counts the number of nodes in the list, starting from the specified node.

### `node_t* list_get_tail(node_t* head)`

Get the last node of a linked list

### `void list_print_nodes(node_t* cnode, printcallback_t printnode_callback)` 

Print nodes after cnode in the list.

## Contributing

Feel free to contribute by opening issues or submitting pull requests. Follow the [Contributing Guidelines](CONTRIBUTING.md) for more details.

## License

This project is licensed under the [The Unlicense](LICENSE).

## Acknowledgements

Thank you Jesus for helping me finish this project. 

*README.md by ChatGPT*