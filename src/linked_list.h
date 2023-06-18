/* Tyler Taormina - taormina@pdx.edu */

#pragma once

#ifndef _LINKED_LIST_H
# define _LINKED_LIST_H

#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/time.h>

typedef struct Program_s {
    uint32_t  id;
    char      *name;
    char      *path;
    uint32_t  program_type_flags;
    struct Program_s *next;
} Program_t;

typedef struct Program_List_s {
    struct Program_s *head;
    struct Program_s *tail;
    int              count;
} Program_List_t;

int process_user_input(int argc, char **argv);
int insert(struct Program_s *new_prog);
int build_struct(char *prog_name);
int remove_program(int id_to_remove);
int free_list(struct Program_List_s *list);

/* File write and read related functions */
int write_list();
int read_list();

#endif // _LINKED_LIST_H


