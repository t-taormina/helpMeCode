/* Tyler Taormina - taormina@pdx.edu */

#include "linked_list.h"

unsigned short is_verbose = 0;
unsigned short id_global = 1;
program_list_t *program_list = NULL;
char *arg_pname= NULL;
int arg_id = -1;


int 
process_cmdline(int argc, char **argv)
{
    int opt;
    program_t *prog = NULL;

    program_list = (program_list_t *) calloc(1, sizeof(program_list_t));
    read_list();

    while((opt = getopt(argc, argv, OPTIONS)) != -1) {
        switch(opt) {
            case 'h':
                printf("%s [arguments]\n\tv - enable verbose mode\n\ta - add new program by giving program name from within program path\n\tr - remove program by id number\n", argv[0]);
                exit(EXIT_SUCCESS);
                break;

            case 'v':
                is_verbose = !is_verbose;
                printf("Verbose mode enabled\n");
                break;

            case 'a':
                arg_pname = strdup(optarg);
                prog = build_prog(arg_pname);
                insert(prog);
                free(arg_pname);
                break;

            case 'r':
                arg_id = atoi(optarg);
                remove_program(arg_id);
                break;

            default:
                exit(EXIT_SUCCESS);
                break;
        }
    }
    print_list();
    write_list();
    free_list();
    return EXIT_SUCCESS;
}

int 
insert(program_t *new_prog)
{
    program_t *temp = NULL;
    if (NULL == new_prog) {
        return -1;
    }
    if (NULL == program_list->head) {
        program_list->head = new_prog;
    }
    else { 
        temp = program_list->head;
        while (NULL != temp->next) {
            temp = temp->next;
        }
        temp->next = new_prog;
    }
    program_list->count++;
    return program_list->count;
}

program_t * 
build_prog(char *prog_name)
{
    program_t *new_prog = NULL;
    char cwd[MAX_PATH_LEN] = {'\0'};

    new_prog = (program_t *) calloc(1, sizeof(program_t));
    id_global++;
    new_prog->id = id_global;
    strcpy(new_prog->name, prog_name);
    if (getcwd(cwd, sizeof(cwd)) == NULL) {
        perror("getcwd() error");
        exit(EXIT_FAILURE);
    }
    strcpy(new_prog->path, cwd);
    new_prog->program_type_flags = 0;
    new_prog->next = NULL;
    return new_prog;
}

int 
remove_program(int id)
{
    program_t *prev = NULL;
    program_t *curr = NULL;
    program_t *temp = NULL;

    if (id < 1) {
        fprintf(stderr, "Invalid id number\n");
        return -1;
    }

    if (NULL == program_list || NULL == program_list->head) {
        fprintf(stderr, "The list is empty\n");
        return 0;
    }

    if (id == program_list->head->id) {
        temp = program_list->head->next;
        free(program_list->head);
        program_list->head = temp;
    }
    else {
        prev = program_list->head;
        curr = program_list->head->next;
        while(NULL != curr) {
            if (id == curr->id) {
                printf("found the program to remove\n");
                temp = curr->next;
                free(curr);
                curr = temp;
                prev->next = curr;
            }
            else {
                prev = curr;
                curr = curr->next;
            }
        }
    }

    return 0;
}

int 
write_list(void)
{
    program_t *temp = NULL;
    int ofd;

    if (NULL == program_list) {
        return 1;
    }

    temp = program_list->head;
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
read_list(void)
{
    program_t temp = {0, "", "", 0, NULL};

    int ifd = -1;
    int id_align = 1;
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
        new_prog->id = id_align;
        strcpy(new_prog->name, temp.name);
        strcpy(new_prog->path, temp.path);
        new_prog->program_type_flags = temp.program_type_flags;
        new_prog->next = NULL;
        insert(new_prog);
        id_align++;
    }
    id_global = id_align;
    close(ifd);

    return 0;
}

int 
print_list(void)
{
    program_t *temp = NULL;

    if (NULL == program_list->head) {
        return 1;
    }

    if (is_verbose) {
        fprintf(stderr, "printing list\n");
    }

    temp = program_list->head;
    while(NULL != temp) {
        printf("ID: %d\n\tName of program: %s\n\tPath to program: %s\n"
                , temp->id, temp->name, temp->path);
        temp = temp->next;
    }

    return 0;
}

int 
free_list(void)
{
    int count;
    program_t *temp = NULL;

    if (NULL == program_list) { return 0; }

    if (is_verbose) {
        fprintf(stderr, "freeing list\n");
    }

    count = 0;
    while (NULL != program_list->head) {
        temp = program_list->head->next;
        if (is_verbose) {
            fprintf(stderr, "freeing node\n");
        }
        free(program_list->head);
        program_list->head = temp;
        count++;
    }
    free(program_list);
    program_list = NULL;

    return count;
}
