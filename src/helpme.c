/* Tyler Taormina - taormina@pdx.edu */

#include "linked_list.h"

extern unsigned short is_verbose;
extern unsigned short id_global;
int 
main(int argc, char **argv)
{
    int ret = -1;

    //init_file();
    process_cmdline(argc, argv);
    ret = run_process();
    return ret;
}
