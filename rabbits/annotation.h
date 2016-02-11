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
    DCACHE_READ_CALL = 3,
    DCACHE_WRITE_CALL = 4
};

void rabbits_cpu_update();

/* Annotation */
void rabbits_annotate_arm_insn(unsigned long insn);

void rabbits_annotate_thumb_insn( unsigned long insn);

/* Instruction Cache */
void rabbits_icache_call(unsigned long addr);

/* Data Cache */
int8_t rabbits_dcache_read_ub(unsigned long addr);
int16_t rabbits_dcache_read_uw(unsigned long addr);
int32_t rabbits_dcache_read_l(unsigned long addr);
int64_t rabbits_dcache_read_q(unsigned long addr);

void rabbits_dcache_write_b(unsigned long addr, int8_t val);
void rabbits_dcache_write_w(unsigned long addr, int16_t val);
void rabbits_dcache_write_l(unsigned long addr, int32_t val);
void rabbits_dcache_write_q(unsigned long addr, int64_t val);


/* Helpers Load */

tcg_target_ulong helper_ret_ldub_mmu_rabbits(CPUArchState *env, target_ulong addr,
                                     TCGMemOpIdx oi, uintptr_t retaddr);

tcg_target_ulong helper_ret_ldsb_mmu_rabbits(CPUArchState *env, target_ulong addr,
                                     TCGMemOpIdx oi, uintptr_t retaddr)
{
    return (int8_t)helper_ret_ldub_mmu_rabbits(env,addr,oi,retaddr);
}

tcg_target_ulong helper_le_lduw_mmu_rabbits(CPUArchState *env, target_ulong addr,
                                     TCGMemOpIdx oi, uintptr_t retaddr);

tcg_target_ulong helper_be_lduw_mmu_rabbits(CPUArchState *env, target_ulong addr,
                                     TCGMemOpIdx oi, uintptr_t retaddr);

tcg_target_ulong helper_le_ldsw_mmu_rabbits(CPUArchState *env, target_ulong addr,
                                     TCGMemOpIdx oi, uintptr_t retaddr)
{
    return (int16_t)helper_le_lduw_mmu_rabbits(env,addr,oi,retaddr);
}

tcg_target_ulong helper_be_ldsw_mmu_rabbits(CPUArchState *env, target_ulong addr,
                                     TCGMemOpIdx oi, uintptr_t retaddr)
{
    return (int16_t)helper_be_lduw_mmu_rabbits(env,addr,oi,retaddr);
}

tcg_target_ulong helper_le_ldul_mmu_rabbits(CPUArchState *env, target_ulong addr,
                                     TCGMemOpIdx oi, uintptr_t retaddr);

tcg_target_ulong helper_be_ldul_mmu_rabbits(CPUArchState *env, target_ulong addr,
                                     TCGMemOpIdx oi, uintptr_t retaddr);

tcg_target_ulong helper_le_ldsl_mmu_rabbits(CPUArchState *env, target_ulong addr,
                                     TCGMemOpIdx oi, uintptr_t retaddr)
{
    return (int32_t)helper_le_ldul_mmu_rabbits(env,addr,oi,retaddr);
}

tcg_target_ulong helper_be_ldsl_mmu_rabbits(CPUArchState *env, target_ulong addr,
                                     TCGMemOpIdx oi, uintptr_t retaddr)
{
    return (int32_t)helper_be_ldul_mmu_rabbits(env,addr,oi,retaddr);
}

tcg_target_ulong helper_le_ldq_mmu_rabbits(CPUArchState *env, target_ulong addr,
                                     TCGMemOpIdx oi, uintptr_t retaddr);

tcg_target_ulong helper_be_ldq_mmu_rabbits(CPUArchState *env, target_ulong addr,
                                     TCGMemOpIdx oi, uintptr_t retaddr);


/* Helpers store */

void helper_le_stq_mmu_rabbits(CPUArchState *env, target_ulong addr, uint64_t val,
                                     TCGMemOpIdx oi, uintptr_t retaddr);

void helper_be_stq_mmu_rabbits(CPUArchState *env, target_ulong addr, uint64_t val,
                                     TCGMemOpIdx oi, uintptr_t retaddr);

void helper_le_stl_mmu_rabbits(CPUArchState *env, target_ulong addr, uint32_t val,
                                     TCGMemOpIdx oi, uintptr_t retaddr);

void helper_be_stl_mmu_rabbits(CPUArchState *env, target_ulong addr, uint32_t val,
                                     TCGMemOpIdx oi, uintptr_t retaddr);

void helper_le_stw_mmu_rabbits(CPUArchState *env, target_ulong addr, uint16_t val,
                                     TCGMemOpIdx oi, uintptr_t retaddr);

void helper_be_stw_mmu_rabbits(CPUArchState *env, target_ulong addr, uint16_t val,
                                     TCGMemOpIdx oi, uintptr_t retaddr);

void helper_ret_stb_mmu_rabbits(CPUArchState *env, target_ulong addr, uint8_t val,
                                     TCGMemOpIdx oi, uintptr_t retaddr);


