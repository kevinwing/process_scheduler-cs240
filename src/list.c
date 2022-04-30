/**
 * @file list.c
 * @author Kevin Wing (kevinrwing@gmail.com)
 * @brief A limited implimentation of a linked list which allows appending a node, removing the head node and destroying the list.
 * @date 2022-04-28
 */
#include "list.h"

void init_list(List *list)
{
    if (list == NULL)
    {
        // list cannot be NULL.
        return;
    }
    // set list to empty
   list->head = list->tail = NULL;
}

Node* new_node(const Proc *data)
{
    if (data == NULL)
    {
        // data cannot be NULL.
        return NULL;
    }

    // instantiate new node and allocate storage.
    Node *node_ptr = (Node*)malloc(sizeof(Node));

    if (node_ptr == NULL)
    {
        // allocation failed. Return NULL.
        return NULL;
    }

    node_ptr->data = (Proc){strdup(data->name), data->e_time, data->n_instructions};
    node_ptr->next = NULL;
    // node_ptr->data.name = strdup(data->name);
    // node_ptr->data.e_time = data->e_time;

    return node_ptr;
}

Proc* new_proc(const char *name, const int e_time, const int n_instuctions)
{
    Proc *proc_ptr = (Proc*)malloc(sizeof(Proc));
    if (proc_ptr == NULL)
    {
        // error allocating memory.
        return NULL;
    }

    proc_ptr->name = strdup(name);
    proc_ptr->e_time = e_time;
    proc_ptr->n_instructions = n_instuctions;

    return proc_ptr;
}

void destroy_list(List *list)
{
    if (list == NULL)
    {
        // list is already empty.
        return;
    }

    // Node *tmp_ptr = list->head;
    while (list->head != NULL)
    {
        // create temp node pointer and set to head.
        Node *tmp_ptr = list->head;

        // set head to next
        list->head = list->head->next;

        // free current processes allocated name storage.
        free(tmp_ptr->data.name);

        // free current nodes allocated memory.
        free(tmp_ptr);

        tmp_ptr = NULL; // ensure no dangling pointers.
    }
}

void append(List *list, const Proc *data)
{
    // create temp Node pointer and set to tail.
    // Node *tail_ref = list->tail;

    if (list == NULL)
    {
        // list cannot be NULL.
        return;
    }

    if (list->head == NULL)
    {
        list->head = new_node(data);
        list->tail = list->head;
    }
    else
    {
        list->tail->next = new_node(data);
        list->tail = list->tail->next;
    }
}

Proc* remove_head(List *list)
{
    // check if list is null.
    if (list == NULL)
    {
        // list cannot be null.
        exit(1);
    }

    if (list->head == NULL)
    {
        // empty list. no data.
        return NULL;
    }

    // create temp node pointer and initialize to head
    Node *temp = list->head;

    // move head pointer to next
    list->head = list->head->next;

    // save previous head data in process structure.
    Proc *data = new_proc(temp->data.name,
                            temp->data.e_time,
                            temp->data.n_instructions);

    // free data.name to prevent memory leaks.
    free(temp->data.name);

    // free head node to prevent memory leaks.
    free(temp);

    // ensure no dangling pointers.
    temp = NULL;

    return data;
}