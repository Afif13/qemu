#include<stdio.h>
#include "qemu_context_priv.h"
#include "tcg-op.h"

extern qemu_context *Global_context;

//The current CPU being run by Qemu
int32_t rabbits_cpu_index = -1;

unsigned long nb_cylces ;

enum {
    INFO_CALL = 0,
    ANNOTATION_CALL = 1,
    ICACHE_CALL = 2,
    DCACHE_CALL = 3
};

void rabbits_annotate_arm_insn( unsigned long insn)
{

    TCGv_ptr    addr = tcg_const_ptr ((tcg_target_long) &nb_cylces);
    TCGv    t1 = tcg_temp_new();


    tcg_gen_ld_i32 (t1, addr, 0);
    tcg_gen_add_i32 (t1, t1, 1);
    tcg_gen_st_i32 (t1, addr, 0);

    tcg_temp_free (t1);
    tcg_temp_free_ptr (addr);

}

void rabbits_annotate_thumb_insn( unsigned long insn)
{

    TCGv_ptr    addr = tcg_const_ptr ((tcg_target_long) &nb_cylces);
    TCGv    t1 = tcg_temp_new();


    tcg_gen_ld_i32 (t1, addr, 0);
    tcg_gen_add_i32 (t1, t1, 1);
    tcg_gen_st_i32 (t1, addr, 0);

    tcg_temp_free (t1);
    tcg_temp_free_ptr (addr);

}

void rabbits_cpu_update()
{
    if(rabbits_cpu_index!=-1) {
            Global_context->sysc.call_rabbits(Global_context->opaque,
                                       ANNOTATION_CALL,rabbits_cpu_index,nb_cylces);
    }
    if(rabbits_cpu_index == -1)
        rabbits_cpu_index = 0;
    else
        rabbits_cpu_index++;
    rabbits_cpu_index %= Global_context->num_cpu;
    nb_cylces = 0;
}

static void rabbits_report(void)
{
    Global_context->sysc.call_rabbits(Global_context->opaque,
                                        INFO_CALL,rabbits_cpu_index,0);
}

__attribute__((constructor))
void rabbits_init(void)
{
       atexit(rabbits_report);
}
