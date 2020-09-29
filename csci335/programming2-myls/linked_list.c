#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <dirent.h>

#include "linked_list.h"
#include "shelper.h"
#include "console.h"

LinkedList *create()
{
    LinkedList *list = malloc(sizeof(LinkedList));

    if (list == NULL)
    {
        return NULL;
    }

    list->head = NULL;
    list->tail = NULL;
    list->count = 0;

    return list;
}

void destroy(LinkedList *list)
{
    // If the list is NULL, return.
    if (list == NULL)
    {
        return;
    }

    // If the list contains no elements, free the list and return.
    if (list->count == 0)
    {
        free(list);
        return;
    }

    do
    {
        // Save the ptr to the next element.
        Node *next = list->head->next;

        // First, free the value pointed to in the node.
        free(list->head->value);

        // Next, free the node itself.
        free(list->head);

        // Move the head of the list down.
        list->head = next;
    } while (list->head != list->tail);

    // Free the list.
    free(list);
}

Node *create_node(char *value, unsigned char type) {
    // Create a new node and initialize / set its properties.
    Node *new_node = malloc(sizeof(Node));

    if (new_node == NULL)
    {
        printf("Failed to allocate node.\n");

        return NULL;
    }

    new_node->value = malloc(sizeof(char) * 255);

    new_node->next = NULL;
    new_node->type = type;

    // Since main.c passes a pointer to an internal buffer, we need to copy the bytes.
    strcpy(new_node->value, value);
    
    return new_node;
}

void add(LinkedList *list, Node *new_node)
{
    // Increment our element counter.
    list->count++;

    // If there are no elements in the list, we need to set both head and tail to this new node.
    if (list->count == 1)
    {
        list->head = new_node;
        list->tail = new_node;

        return;
    }

    // Set the tail's next element to the new node.
    list->tail->next = new_node;

    // Set the tail of the list to the tail's next element.
    list->tail = list->tail->next;
}

void add_ascending(LinkedList *list, Node *new_node) {
    list->count++;
    
    // We don't need to place it into its correct location if it's the only element in the list.
    if (list->count == 1) {
        list->head = new_node;
        list->tail = new_node;
        
        return;
    }
    
    // If the new_node is smaller than the head, shift it here instead.
    if (smaller_than(new_node->value, list->head->value)) {
        new_node->next = list->head;
        list->head = new_node;
        
        return;
    }
    
    // If there's more than one element in the list, we need to iterate through and find its correct position.
    Node *target_node = list->head;
    while (target_node->next != NULL) {
        // Compare the value in the target_node with the new_node.
        if (smaller_than(new_node->value, target_node->next->value)) {
            // The new node goes before the target_node.
            new_node->next = target_node->next;
            target_node->next = new_node;
            
            return;
        }
        
        target_node = target_node->next;
    }
    
    // We're this far, it means everything else in the list is smaller than the rest. We need to add onto the end of the list.
    list->tail->next = new_node;
    list->tail = new_node;
}

void delete (LinkedList *list, Node *node)
{
    // Save our preceding and following values (for the sake of convenience and calculation).
    Node *preceding = list->head;
    Node *following = node->next;

    // Walk down the list until the next element is the target node.
    while (preceding->next != node)
    {
        preceding = preceding->next;
    }

    // Set the preceding's next element to the following node.
    preceding->next = following;

    // Decrement our count.
    list->count--;
}

Node *get(LinkedList *list, int index)
{
    Node *last = list->head;
    for (int i = 0; i < index; i++)
    {
        last = last->next;
    }

    return last;
}

Node *search(LinkedList *list, char *value)
{
    // If the list is null or empty, return -1.
    if (list == NULL || list->count == 0)
    {
        return NULL;
    }

    Node *current = list->head;

    while (current != NULL)
    {
        if (strcmp(value, current->value) == 0)
        {
            return current;
        }

        current = current->next;
    }

    return NULL;
}

void print_list(LinkedList *list)
{
    Node *current = list->head;
    
    for (int i = 0; i < list->count; i++)
    {
        if (current->type == DT_DIR) {
            printfc(current->value, MAGENTA);
        }
        
        else if (current->type == DT_REG) {
            printfc(current->value, WHITE);
        }
        
        printf("\n");
        current = current->next;
    }
}