#ifndef ANNOTATION
#define ANNOTATION


#include<stdio.h>
#include "qemu_context_priv.h"
#include "tcg-op.h"


//#define DEBUG_ANNOTATION

#ifdef DEBUG_ANNOTATION
# define DPRINTF(fmt, ...) fprintf(stderr, fmt, ##__VA_ARGS__)
#else
# define DPRINTF(fmt, ...) do {} while(0)
#endif


extern qemu_context *Global_context;


#include"../../../src/components/qemu_wrapper/qemu-cache.h" //very bad idea ..
//We need this include for the FULL_CACHE and I_CACHE_LINES define

enum {
    /* Used to show Info of all the components */
    INFO_CALL = 0,
    /* Used to call the qemu_annotation component to update
       the Cycle Number for the CPU
     */
    ANNOTATION_CALL = 1,
    /* Used to do a synchronization with systemC
       do some wait after a run of all the CPUs
    */
    SYNC_CALL = 2,
    /* Perform Instruction Cache Call */
    ICACHE_CALL = 3,
    /* Perform Data Cache Read */
    DCACHE_READ_CALL = 4,
    /* Perform Data Cache Write */
    DCACHE_WRITE_CALL = 5,
    /* Invalidate a Data Cache entry */
    INVALIDATE_CALL = 6
};


/* Update the Current CPU */

void rabbits_cpu_update();


/* Arm Specific Annotation */

void rabbits_arm_call(uint32_t pc, uint32_t insn);

void rabbits_annotate_arm_insn(unsigned long insn);

void rabbits_annotate_thumb_insn( unsigned long insn);


/* End Arm Specific Annotation*/

/* Generic Annotion (archicture independant) */

/* Instruction Cache */
void rabbits_icache(unsigned long pc);


/* Data Cache */
uint8_t rabbits_dcache_read_ub(unsigned long addr);
uint16_t rabbits_dcache_read_uw(unsigned long addr);
uint32_t rabbits_dcache_read_ul(unsigned long addr);
uint64_t rabbits_dcache_read_q(unsigned long addr);

void rabbits_dcache_write_b(unsigned long addr, uint8_t val);
void rabbits_dcache_write_w(unsigned long addr, uint16_t val);
void rabbits_dcache_write_l(unsigned long addr, uint32_t val);
void rabbits_dcache_write_q(unsigned long addr, uint64_t val);


/* Load Helpers */

tcg_target_ulong helper_ret_ldub_mmu_rabbits(CPUArchState *env, target_ulong addr,
                                     TCGMemOpIdx oi, uintptr_t retaddr);

tcg_target_ulong helper_ret_ldsb_mmu_rabbits(CPUArchState *env, target_ulong addr,
                                     TCGMemOpIdx oi, uintptr_t retaddr);

tcg_target_ulong helper_le_lduw_mmu_rabbits(CPUArchState *env, target_ulong addr,
                                     TCGMemOpIdx oi, uintptr_t retaddr);

tcg_target_ulong helper_be_lduw_mmu_rabbits(CPUArchState *env, target_ulong addr,
                                     TCGMemOpIdx oi, uintptr_t retaddr);

tcg_target_ulong helper_le_ldsw_mmu_rabbits(CPUArchState *env, target_ulong addr,
                                     TCGMemOpIdx oi, uintptr_t retaddr);

tcg_target_ulong helper_be_ldsw_mmu_rabbits(CPUArchState *env, target_ulong addr,
                                     TCGMemOpIdx oi, uintptr_t retaddr);

tcg_target_ulong helper_le_ldul_mmu_rabbits(CPUArchState *env, target_ulong addr,
                                     TCGMemOpIdx oi, uintptr_t retaddr);

tcg_target_ulong helper_be_ldul_mmu_rabbits(CPUArchState *env, target_ulong addr,
                                     TCGMemOpIdx oi, uintptr_t retaddr);

tcg_target_ulong helper_le_ldsl_mmu_rabbits(CPUArchState *env, target_ulong addr,
                                     TCGMemOpIdx oi, uintptr_t retaddr);

tcg_target_ulong helper_be_ldsl_mmu_rabbits(CPUArchState *env, target_ulong addr,
                                     TCGMemOpIdx oi, uintptr_t retaddr);

tcg_target_ulong helper_le_ldq_mmu_rabbits(CPUArchState *env, target_ulong addr,
                                     TCGMemOpIdx oi, uintptr_t retaddr);

tcg_target_ulong helper_be_ldq_mmu_rabbits(CPUArchState *env, target_ulong addr,
                                     TCGMemOpIdx oi, uintptr_t retaddr);


/* Store Helpers */

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


#endif
