#include <string.h>  // for strcmp and strcpy
#include <stdlib.h>  // for malloc and free
#include <stdio.h>   // for printf
#include "linked_list.h"

#include <pthread.h>

pthread_mutex_t lock;

//constructor
linked_list* create_linked_list(){
    linked_list* ll = (linked_list*) malloc( sizeof(linked_list));
    ll->count = 0;
    ll->head = NULL;

    // Init the mutex lock.
    pthread_mutex_init(&lock, NULL);

    return ll;
}

// destructor
void destroy_linked_list( linked_list* ll ){
    pthread_mutex_lock(&lock);

    // empty the linked list
    while( ll->count > 0){
        linked_list_delete( ll, ll->head );
    }

    // un-allocate the memory
    free(ll);

    pthread_mutex_destroy(&lock);

}

// add a new node to the end of the linked list
void linked_list_add( linked_list* ll, char* data_in){
    // Lock the mutex.
    pthread_mutex_lock(&lock);

    node* n = (node *) malloc( sizeof(node) );
    n->data = (char *) malloc( sizeof(char) *( strlen(data_in)+1 ));
    strcpy(n->data, data_in);
    n->next = NULL;
    // Traverse the list to find the end node
    node * t = ll->head;
    if(t == NULL){
        ll->head = n;
    }else{
        while( t->next != NULL){
            t = t->next;
        }
        t->next = n;
    }
    // increase the size of the list
    ll->count++;

    pthread_mutex_unlock(&lock);
}

// Delete a node from the linked list
void linked_list_delete( linked_list* ll, node* to_delete){
    // pthread_mutex_lock(&lock);

    node* prev_node;
    if( ll->head == NULL){
        printf("Error, linked_list_delete() empty list\n");
        return;
    }else if( to_delete == ll->head ){
        ll->head = ll->head->next;
    }else{
        for( prev_node=ll->head; prev_node->next!=NULL; prev_node=prev_node->next ){
            if(prev_node->next == to_delete){
                break;
            }
        }
        if( prev_node->next == NULL){
            printf("Error, linked_list_delete(), could not find item in list\n");
            return;
        }
        prev_node->next = to_delete->next;  // connect the list
    }

    //free and reduce size
    ll->count--;
    free(to_delete->data);
    free(to_delete);

    // pthread_mutex_unlock(&lock);
}

// search for a node by it's data field
node* linked_list_search( linked_list* ll, char* search_string ){
    node* n;
    for( n=ll->head; n != NULL; n = n->next ){
        if( strcmp( n->data, search_string) == 0  ){
            break;
        }
    }
    if( n == NULL){
        printf("Error, linked_list_search(), could not find element in list\n");
        return NULL;
    }
    // success, found the element
    return n;
}

// get node by index
node* linked_list_get( linked_list* ll, int index){
    int count = 0;
    node* n = ll->head;
    if( ll->head == NULL){
        printf("error, linked_list_get() empty list\n");
        return NULL;
    }
    while( count < index ){
        if(n->next == NULL){
            printf("Error, linked_list_get() list shorted than %i \n", index);
            return NULL;
        }
        n = n->next;
        count++;
    }

    return n;

}

















