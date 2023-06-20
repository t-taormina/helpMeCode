/* Tyler Taormina - taormina@pdx.edu */

#include "linked_list.h"

extern unsigned short is_verbose;
extern unsigned short id_global;

int 
main(int argc, char **argv)
{
    int ret = -1;

    ret = process_cmdline(argc, argv);
    return ret;
}
