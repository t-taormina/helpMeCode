/* Tyler Taormina - taormina@pdx.edu */

#include "linked_list.h"

unsigned short is_verbose = 0;
unsigned short id_global = 1;

int
run_process(void)
{
    program_list_t *program_list = NULL;
    program_list = (program_list_t *) calloc(1, sizeof(program_list_t));
    read_list(program_list);
    for ( ; ; ) {
        break;
    }
    write_list();
    free_list(program_list);
    return 0;
}


int 
process_cmdline(int argc, char **argv)
{
    int opt;
    char buf[MAX_PATH_LEN];

    while((opt = getopt(argc, argv, OPTIONS)) != -1) {
        switch(opt) {
            case 'h':
                printf("help message here\n");
                break;

            case 'v':
                is_verbose = !is_verbose;
                printf("Verbose mode enabled\n");
                break;

            case 'p':

                break;

            default:
                break;
        }
    }
    return is_verbose;
}

int 
insert(program_t *new_prog, program_list_t *program_list)
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
    return 0;
}

int 
remove_program(int id_to_remove)
{
    return 0;
}

int 
write_list(void)
{
    int ofd = -1;
    program_t init_prog = {
        id_global
        , "helpme"
        , "/home/tylr/Development/Random/helpMeCode/src"
        , 0 };

    ofd = open(FILE_NAME
            , O_WRONLY | O_TRUNC | O_CREAT
            , S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH);

    if (ofd < 0) {
        perror("can't open " FILE_NAME " for output\n");
        exit(EXIT_FAILURE);
    }

    write(ofd, &init_prog, sizeof(program_t));
    close(ofd);
    return 0;
}

int 
read_list(program_list_t *prog_list)
{
    return 0;
}

int 
free_list(program_list_t *list)
{
    int count;
    program_node_t *temp = NULL;

    if (NULL == list) { return 0; }

    count = 0;
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
