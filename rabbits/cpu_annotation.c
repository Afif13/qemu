#include "annotation.h"

//This should be architecture independant

//The current CPU being run by Qemu
int32_t rabbits_cpu_index = -1;

/* The current number of cycles of the current CPU
   this number is reset when the CPU change
*/
unsigned long nb_cycles = 0;

//extern declartion
extern unsigned long last_pc_tag;

void rabbits_cpu_update()
{
    if(rabbits_cpu_index!=-1) {
        Global_context->sysc.call_rabbits(Global_context->opaque,
                                   ANNOTATION_CALL,rabbits_cpu_index,nb_cycles,0,0);
    }
    if(rabbits_cpu_index == -1)
        rabbits_cpu_index = 0;
    else
        rabbits_cpu_index++;

    if(rabbits_cpu_index == Global_context->num_cpu) {
        Global_context->sysc.call_rabbits(Global_context->opaque,
                                   SYNC_CALL,rabbits_cpu_index,0,0,0);
    }

    rabbits_cpu_index %= Global_context->num_cpu;

    //reset the values
    nb_cycles = 0;
    last_pc_tag = 0xDEADBEEF;
}


/* Used for Debug Purpose */
static void rabbits_report(void)
{
    Global_context->sysc.call_rabbits(Global_context->opaque,
                                        INFO_CALL,0,0,0,0);
}

__attribute__((constructor))
void rabbits_init(void)
{
//    atexit(rabbits_report);
}

