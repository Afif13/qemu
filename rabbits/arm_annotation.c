#include "annotation.h"

//This is for ARM (i know it's trivial to guess it ...

//extern declaration
extern int32_t rabbits_cpu_index;
extern unsigned long nb_cycles;

void rabbits_arm_call(uint32_t pc, uint32_t insn)
{
    rabbits_icache(pc);

    //we need to make difference between normal instruction and thumb instruction
    rabbits_annotate_arm_insn(insn);

    //rabbits_annotate_thumb_insn(insn)
}

void rabbits_annotate_arm_insn(unsigned long insn)
{
    //Any instruction should at least take 1 cycle
    nb_cycles++;
    //TODO : consider the cases we have more than 1 cycle
}

void rabbits_annotate_thumb_insn( unsigned long insn)
{
    //Any instruction should at least take 1 cycle
    nb_cycles++;
    //TODO : consider the cases we have more than 1 cycle
}

