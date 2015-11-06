#include<stdio.h>

void rabbits_annotate_arm_insn( unsigned int insn)
{
    if(insn)
       printf(" Insn: %x\n", insn);
}

