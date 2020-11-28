#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include "linked_list.h"
#include "mycurl.h"

struct args {
    linked_list *list;
    char *url;
};

void *ll_add_threaded(void *args) {
    struct args *arguments = (struct args *)args;
    linked_list *my_list = arguments->list;
    char *url = arguments->url;

    printf("%s\n",url);
    char* output = parse_and_fetch_url(url);

    linked_list_add(my_list, output);

    free(arguments);
    free(output);

    return NULL;
}

int main(int argc, char**argv){

    char* urls[10] = {
        "http://www.cs.unca.edu/~drawert/cs335/exam2/check1.php",
        "http://www.cs.unca.edu/~drawert/cs335/exam2/check2.php",
        "http://www.cs.unca.edu/~drawert/cs335/exam2/check3.php",
        "http://www.cs.unca.edu/~drawert/cs335/exam2/check4.php",
        "http://www.cs.unca.edu/~drawert/cs335/exam2/check5.php",
        "http://www.cs.unca.edu/~drawert/cs335/exam2/check6.php",
        "http://www.cs.unca.edu/~drawert/cs335/exam2/check7.php",
        "http://www.cs.unca.edu/~drawert/cs335/exam2/check8.php",
        "http://www.cs.unca.edu/~drawert/cs335/exam2/check9.php",
        "http://www.cs.unca.edu/~drawert/cs335/exam2/check10.php"
    };
    int i;

    linked_list* my_list = create_linked_list();
    pthread_t threads[10];

    for(i=0; i< 10; i++){
        struct args *arguments = malloc(sizeof(struct args));
        arguments->list = my_list;
        arguments->url = urls[i];

        pthread_create(&threads[i], NULL, ll_add_threaded, arguments);
    }

    for (int i = 0; i < 10; i++) {
        pthread_join(threads[i], NULL);
    }


    // print out list
    node* n;
    for(i=0; i < my_list->count; i++){
        n = linked_list_get(my_list, i);
        printf("[%i] %s\n", i, n->data);
    }
    // clean up
    destroy_linked_list( my_list );
    return 0;
}
