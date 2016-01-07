#include<stdio.h>
#include "qemu_context_priv.h"
#include "tcg-op.h"

extern qemu_context *Global_context;

//The current CPU being run by Qemu
int32_t rabbits_cpu_index = -1;

unsigned long nb_cycles ;

enum {
    INFO_CALL = 0,
    ANNOTATION_CALL = 1,
    ICACHE_CALL = 2,
    DCACHE_CALL = 3
};


void icache_access(unsigned long addr);

void rabbits_icache_call(unsigned long addr,unsigned long size)
{

//    TCGv_ptr            f;
    TCGArg              args[1];

//    f = tcg_const_ptr ((tcg_target_long)icache_access);
    args[0] = tcg_const_ptr ((tcg_target_long)&nb_cycles);
    tcg_gen_callN (&tcg_ctx, icache_access, 0, 1, args);

//    tcg_temp_free_ptr (args[0]);
//    tcg_temp_free_ptr (f);

}

void icache_access(unsigned long addr)
{
    printf("   icache access to %lu\n",addr);

}

void rabbits_annotate_arm_insn( unsigned long insn)
{

    TCGv_ptr    addr = tcg_const_ptr ((tcg_target_long) &nb_cycles);
    TCGv    t1 = tcg_temp_new();


    tcg_gen_ld_tl (t1, addr, 0);
    tcg_gen_addi_tl (t1, t1, 1);
    tcg_gen_st_tl (t1, addr, 0);

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
                                        INFO_CALL,rabbits_cpu_index,0);
}

__attribute__((constructor))
void rabbits_init(void)
{
       atexit(rabbits_report);
}
