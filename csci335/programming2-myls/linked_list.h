#ifndef LINKED_LIST_H
#define LINKED_LIST_H

typedef struct node
{
    char *value;
    struct node *next;
    unsigned char type;
    long size;
    char *perms;
    int is_e;
} Node;

typedef struct linked_list
{
    Node *head;
    Node *tail;
    int count;
} LinkedList;

LinkedList *create();
Node *create_node(char *value, unsigned char type);

void destroy(LinkedList *list);
void add(LinkedList *list, Node *new_node);
void add_ascending(LinkedList *list, Node *new_node);
void delete (LinkedList *list, Node *node);
void print_list(LinkedList *list);

Node *get(LinkedList *list, int index);
Node *search(LinkedList *list, char *value);

#endif