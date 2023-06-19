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
    program_t temp = {0, "", "", 0, NULL};
    int ifd = -1;

    ifd = open(FILE_NAME, O_RDONLY);
    if (ifd < 0) {
        perror("Can't open " FILE_NAME " for reading\n");
        exit(EXIT_FAILURE);
    }
    while(read(ifd, &temp, sizeof(program_t)) > 0) {
        printf("ID: %d\n\tName of program: %s\n\tPath to program: %s\n"
                , temp.id, temp.name, temp.path);
    }
    close(ifd);

    return EXIT_SUCCESS;
}
