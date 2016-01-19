#include "annotation.h"


void rabbits_icache_call(unsigned long addr)
{
    Global_context->sysc.call_rabbits(Global_context->opaque,
                               ICACHE_CALL,rabbits_cpu_index,addr);
}


void rabbits_annotate_arm_insn(unsigned long insn)
{

    TCGv_ptr    addr = tcg_const_ptr ((tcg_target_long) &nb_cycles);
    TCGv    t1 = tcg_temp_new();


    tcg_gen_ld_tl (t1, addr, 0);
    tcg_gen_addi_tl (t1, t1, 1);
    tcg_gen_st_tl (t1, addr, 0);

    //TODO : Test the cases we have more than 1 cycle

    tcg_temp_free (t1);
    tcg_temp_free_ptr (addr);

}

void rabbits_annotate_thumb_insn( unsigned long insn)
{

    TCGv_ptr    addr = tcg_const_ptr ((tcg_target_long) &nb_cycles);
    TCGv    t1 = tcg_temp_new();


    tcg_gen_ld_tl (t1, addr, 0);
    tcg_gen_addi_tl (t1, t1, 1);
    tcg_gen_st_tl (t1, addr, 0);

    tcg_temp_free (t1);
    tcg_temp_free_ptr (addr);

}

void rabbits_cpu_update()
{
    if(rabbits_cpu_index!=-1) {
        Global_context->sysc.call_rabbits(Global_context->opaque,
                                   ANNOTATION_CALL,rabbits_cpu_index,nb_cycles);
    }
    if(rabbits_cpu_index == -1)
        rabbits_cpu_index = 0;
    else
        rabbits_cpu_index++;
    rabbits_cpu_index %= Global_context->num_cpu;
    nb_cycles = 0;
}


static void rabbits_report(void)
{
    Global_context->sysc.call_rabbits(Global_context->opaque,
                                        INFO_CALL,NULL,NULL);
}

__attribute__((constructor))
void rabbits_init(void)
{
//       atexit(rabbits_report);
}
