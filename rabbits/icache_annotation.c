#include "annotation.h"


//This should be architecture independant

/* The last PC used with icache call
   this will allow us to only do a new icache call
   if we are in a new line
   we only need the tag

  It's for the current CPU, so we need to reset it
  when the CPU change
*/
unsigned long last_pc_tag = 0xDEADBEEF;

//extern declaration
extern int32_t rabbits_cpu_index;

void rabbits_icache(unsigned long addr)
{
    unsigned long tag = addr >> ICACHE_LINE_BITS;

    if(tag != last_pc_tag) {
        Global_context->sysc.call_rabbits(Global_context->opaque,
                                   ICACHE_CALL,rabbits_cpu_index,addr,0,0);
        last_pc_tag = tag;
    }
}

