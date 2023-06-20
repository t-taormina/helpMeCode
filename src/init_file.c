/* Tyler Taormina */

#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/time.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

#include "linked_list.h"

int
main(void)
{
    int ofd = -1;
    program_t prog1 = {
        id_global
            , "helpme"
            , "/home/tylr/Development/Random/helpMeCode/src"
            , 0
            , NULL};

    program_t prog2 = {
        id_global + 1
            , "primesMT"
            , "/home/tylr/Development/School/CS333/labs/lab4"
            , 0
            , NULL};

    id_global++;

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
