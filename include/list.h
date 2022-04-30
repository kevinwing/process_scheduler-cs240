/**
 * @file list.h
 * @author Kevin Wing (kevinrwing@gmail.com)
 * @brief Declaration file for a singly linked list with a pointer to the last node that will be
 * used as the underlying data structure in a queue.
 * @date 2022-04-28
 */
#ifndef LIST_H
#define LIST_H

#include <string.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct Proc Proc;
typedef struct Node Node;
typedef struct List List;

/**
 * @brief Structure to hold process data
 */
struct Proc
{
    char *name; // name of process
    int e_time; // entry time of process
    int n_instructions; // number of instructions of process
};

/**
 * @brief Structure to represent a list node containing process data and a
 * pointer to the next node or Null if last node.
 *
 * @men
 */
struct Node
{
    Proc data;
    Node *next; // pointer to next entry in list or Null if tail.
};

/**
 * @brief Structure to wrap the head and tail node pointers.
 *
 */
struct List
{
    Node *head;
    Node *tail;
};

void init_list(List *list);

// create a new, empty node with data and return pointer to Node.
Node* new_node(const Proc *data);

// create new process
Proc* new_proc(const char *name, const int e_time, const int n_instuctions);

// signarture for function to destroy the contents of the list and set it to Null.
void destroy_list(List *list);

// void push_to_list(List *list, const Proc *data);
// void insert_to_list(List *list, const Proc *data, Node *node);

// signature for function to append item to end of list and update tail pointer.
void append(List *list, const Proc *data);

// Proc remove_end(List *list); // return last list items data and delete node.


void add_node(List *list, Node *node);

// removes first node in list and returns the contained process data.
Proc* remove_head(List *list);

#endif