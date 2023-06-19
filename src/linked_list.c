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
        /* Menu here */
        print_list(program_list);
        break;
    }
    write_list(program_list);
    free_list(program_list);
    return 0;
}

int 
process_cmdline(int argc, char **argv)
{
    int opt;
    //char buf[MAX_PATH_LEN];

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
build_prog(char *prog_name)
{
    return 0;
}

int 
remove_program(int id_to_remove)
{
    return 0;
}

int 
init_file(void)
{
    program_t prog1 = {
        id_global
        , "helpme"
        , "/home/tylr/Development/Random/helpMeCode/src"
        , 0
        , NULL};

    program_t prog2 = {
        ++id_global
        , "primesMT"
        , "/home/tylr/Development/School/CS333/labs/lab4"
        , 0
        , NULL};

    int ofd = -1;
    ofd = open(FILE_NAME
            , O_WRONLY | O_TRUNC | O_CREAT
            , S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH);

    if (ofd < 0) {
        perror("can't open " FILE_NAME " for output\n");
        exit(EXIT_FAILURE);
    }

    write(ofd, &prog1, sizeof(program_t));
    write(ofd, &prog2, sizeof(program_t));
    close(ofd);
    return 0;
}

int 
write_list(program_list_t *prog_list)
{
    program_t *temp = NULL;
    int ofd;

    if (NULL == prog_list) {
        return 1;
    }

    temp = prog_list->head;
    ofd = -1;
    ofd = open(FILE_NAME
            , O_WRONLY | O_TRUNC | O_CREAT
            , S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH);

    if (ofd < 0) {
        perror("can't open " FILE_NAME " for output\n");
        exit(EXIT_FAILURE);
    }


    while(NULL != temp) {
        write(ofd, temp, sizeof(program_t));
        temp = temp->next;
    }
    close(ofd);
    return 0;
}

int 
read_list(program_list_t *prog_list)
{
    program_t temp = {0, "", "", 0, NULL};

    int ifd = -1;
    ifd = open(FILE_NAME, O_RDONLY);

    if (ifd < 0) {
        perror("Can't open " FILE_NAME " for reading\n");
        exit(EXIT_FAILURE);
    }

    if (is_verbose) {
        fprintf(stderr, "reading file\n");
    }

    while(read(ifd, &temp, sizeof(program_t)) > 0) {
        program_t *new_prog = (program_t *) calloc(1, sizeof(program_t));
        new_prog->id = temp.id;
        strcpy(new_prog->name, temp.name);
        strcpy(new_prog->path, temp.path);
        new_prog->program_type_flags = temp.program_type_flags;
        new_prog->next = NULL;
        insert(new_prog, prog_list);
    }
    close(ifd);

    return 0;
}

int 
print_list(program_list_t *prog_list)
{
    program_t *temp = NULL;

    if (NULL == prog_list->head) {
        return 1;
    }

    if (is_verbose) {
        fprintf(stderr, "printing list\n");
    }

    temp = prog_list->head;
    while(NULL != temp) {
        printf("ID: %d\n\tName of program: %s\n\tPath to program: %s\n"
                , temp->id, temp->name, temp->path);
        temp = temp->next;
    }
    return 0;
}

int 
free_list(program_list_t *list)
{
    int count;
    program_t *temp = NULL;

    if (NULL == list) { return 0; }

    if (is_verbose) {
        fprintf(stderr, "freeing list\n");
    }

    count = 0;
    while (NULL != list->head) {
        temp = list->head->next;
        if (is_verbose) {
            fprintf(stderr, "freeing node\n");
        }
        free(list->head);
        list->head = temp;
        count++;
    }
    free(list);
    list = NULL;
    return count;
}
