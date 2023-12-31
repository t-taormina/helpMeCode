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
#include <string.h>

#define OPTIONS "hva:r:"
#define MAX_PATH_LEN 200
#define MAX_NAME_LEN 25
#define FILE_NAME "helpme.bin"


typedef struct program_s {
    int       id;
    char      name[MAX_NAME_LEN];
    char      path[MAX_PATH_LEN];
    uint8_t  program_type_flags;
    struct program_s *next;
} program_t;

typedef struct program_list_s {
    struct program_s *head;
    int              count;
} program_list_t;

int process_cmdline(int, char **);
int insert(struct program_s *);
struct program_s *build_prog(char *);
int remove_program(int);
int free_list(void);
int print_list(void);
int write_list(void);
int read_list(void);

#endif // _LINKED_LIST_H
