/* Tyler Taormina - taormina@pdx.edu */

#include "linked_list.h"

#define OPTIONS "hvp:"

int 
process_user_input(int argc, char **argv)
{
    int opt;

    while((opt = getopt(argc, argv, OPTIONS)) != -1) {
        switch(opt) {
            case 'h':
                break;

            case 'v':
                break;

            case 'p':
                break;

            default:
                break;
        }
    }
}

int 
insert(Program_t *new_prog)
{
    if (NULL == new_prog) {
        return -1;
    }
    if (NULL == program_list->head) {
        program_list->head = program_list->tail = new_prog;
    }
    else {
        program_list->tail->next = new_prog;
        program_list->tail = new_prog;
    }
    program_list->count++;
    return program_list->count;
}

int 
build_struct(char *prog_name)
{
}

int 
remove_program(int id_to_remove)
{
}

/* File write and read related functions */
int 
write_list()
{
}

int 
read_list()
{
}

int 
free_list(Program_List_t *list)
{
    if (NULL == list) { return 0; }

    int count = 0;
    Program_t *temp = NULL;
    while (NULL != list->head) {
        temp = list->head;
        list->head = list->head->next;
        free(temp);
        temp = NULL;
        count++;
    }
    free(list);
    list = NULL;
    return count;
}


