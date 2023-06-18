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
    char      *name
    char      *path;
    uint32_t  program_type_flags;
    Program_t *next;
} Program_t;

typedef struct Program_List_s {
    struct Program_s *head;
    int              count;
} Program_List_t;

int add(Program_s *new_prog);
int build_struct(char *prog_name);
int remove(int id_to_remove);

/* File write and read related functions */
int write_list();
int read_list();

#endif // _LINKED_LIST_H


