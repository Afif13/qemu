#include<stdio.h>
#include "qemu_context_priv.h"
#include "tcg-op.h"

extern qemu_context *Global_context;

//The current CPU being run by Qemu
int32_t rabbits_cpu_index = -1;

/*The current number of cycles of the current CPU
  this number is reset when we change the CPU */
unsigned long nb_cycles ;

enum {
    INFO_CALL = 0,
    ANNOTATION_CALL = 1,
    ICACHE_CALL = 2,
    DCACHE_CALL = 3
};

void rabbits_cpu_update();

void rabbits_icache_call(unsigned long addr);

void rabbits_annotate_arm_insn(unsigned long insn);

void rabbits_annotate_thumb_insn( unsigned long insn);
