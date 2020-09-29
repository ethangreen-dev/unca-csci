#include <dirent.h>
#include <stddef.h>
#include <sys/stat.h>

#include "myls.h"
#include "console.h"
#include "linked_list.h"

int main(int argc, char **argv)
{
    char *path = ".";

    if (argc > 1)
    {
        path = argv[1];
    }

    print_dir(path);
}

void print_dir(char *dirp)
{
    DIR *dir = opendir(dirp);
    LinkedList *list = create();

    if (dir == NULL)
    {
        printfc("Could not open directory.\n", RED);

        return;
    }

    struct dirent *entry;
    while ((entry = readdir(dir)) != NULL)
    {
        // struct stat *file_s;
        // stat(entry->d_name, file_s);
        
        // char *perms = malloc(sizeof(char) * 10);
        // format_perms(file_s->st_mode, perms);
        
        // Create a new node for the linked list.
        Node *new_node = create_node(entry->d_name, entry->d_type);
        
        // Add the new node to the list, sorted ascending. 
        add_ascending(list, new_node);
    }

    // Print the list out.
    print_list(list);
}

// I wanted to be able to stat() the path and get its perms via t_mode, but I ran out of time.
void format_perms(mode_t perms, char *buff) {
    char *mask = "rwxrwxrwx";
    
    for (int i = 0; i < 9; i++) {
        buff[i] = perms & (1 << (8 - i)) ? mask[i] : '-';
    }
    
    buff[9] = '\0';
}