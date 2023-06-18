/* Tyler Taormina - taormina@pdx.edu */

#pragma once

#ifndef _LINKED_LIST_H
# define _LINKED_LIST_H

#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/time.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

#define OPTIONS "hvp:"
#define MAX_PATH_LEN 200
#define MAX_NAME_LEN 25
#define FILE_NAME "helpme.bin"


typedef struct program_s {
    uint32_t  id;
    char      name[MAX_NAME_LEN];
    char      path[MAX_PATH_LEN];
    uint32_t  program_type_flags;
} program_t;

typedef struct program_node_s {
    struct program_s      program;
    struct program_node_s *next;
} program_node_t;

typedef struct program_list_s {
    struct program_node_s *head;
    struct program_node_s *tail;
    int                   count;
} program_list_t;

int run_process(void);
int process_cmdline(int, char **);
int insert(struct program_s *, struct program_list_s *);
int build_struct(char *);
int remove_program(int);
int free_list(struct program_list_s *);
int write_list(void);
int read_list(struct program_list_s *);

#endif // _LINKED_LIST_H
