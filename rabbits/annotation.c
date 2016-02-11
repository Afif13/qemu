#include "annotation.h"

/* Helper Implementation*/

tcg_target_ulong helper_ret_ldub_mmu_rabbits(CPUArchState *env, target_ulong addr,
                                     TCGMemOpIdx oi, uintptr_t retaddr)
{
    tcg_target_ulong res;
    unsigned mmu_idx = get_mmuidx(oi);
    int index = (addr >> TARGET_PAGE_BITS) & (CPU_TLB_SIZE - 1);
    target_ulong tlb_addr;

    res = helper_ret_ldub_mmu(env,addr,oi,retaddr);

    tlb_addr = env->tlb_table[mmu_idx][index].addr_read;

    if (unlikely(tlb_addr & ~TARGET_PAGE_MASK)) {
        //here we have an IO access so we return res and don't perform cache access
        return res;
    } else {
        rabbits_dcache_read_ub(addr & 0x07fffff); //HERE we should get Physical Guest addr
        return res;
    }
}

tcg_target_ulong helper_be_lduw_mmu_rabbits(CPUArchState *env, target_ulong addr,
                                     TCGMemOpIdx oi, uintptr_t retaddr)
{
    return helper_be_lduw_mmu(env, addr, oi, retaddr);
}

tcg_target_ulong helper_le_lduw_mmu_rabbits(CPUArchState *env, target_ulong addr,
                                     TCGMemOpIdx oi, uintptr_t retaddr)
{
    tcg_target_ulong res;
    unsigned mmu_idx = get_mmuidx(oi);
    int index = (addr >> TARGET_PAGE_BITS) & (CPU_TLB_SIZE - 1);
    target_ulong tlb_addr;

//   rabbits_dcache_read_uw(addr & 0x07fffff);

    res = helper_le_lduw_mmu(env,addr,oi,retaddr);

/*
    if(unlikely((addr & ~TARGET_PAGE_MASK) + 1 >= TARGET_PAGE_SIZE) {
        //here the address is unaligned here
        target_ulong next_addr; //we take the address in next page
        next_addr = addr +1;

        tlb_addr = env->tlb_table[mmu_idx][index+1].addr_read;
        if (!unlikely(tlb_addr & ~TARGET_PAGE_MASK)) {
            //it's not an IO access so we perform a cache access
            rabbits_dcache_read_uw(next_addr & 0x07fffff);

        }
    }
*/
    tlb_addr = env->tlb_table[mmu_idx][index].addr_read;

    if (unlikely(tlb_addr & ~TARGET_PAGE_MASK)) {
        //here we have an IO access so we return res and don't perform cache access
        return res;
    } else {
        rabbits_dcache_read_uw(addr & 0x07fffff);
        return res;
    }
}

tcg_target_ulong helper_be_ldul_mmu_rabbits(CPUArchState *env, target_ulong addr,
                                     TCGMemOpIdx oi, uintptr_t retaddr)
{
    return helper_be_ldul_mmu(env, addr, oi, retaddr);
}

tcg_target_ulong helper_le_ldul_mmu_rabbits(CPUArchState *env, target_ulong addr,
                                     TCGMemOpIdx oi, uintptr_t retaddr)
{
    tcg_target_ulong res;
    unsigned mmu_idx = get_mmuidx(oi);
    int index = (addr >> TARGET_PAGE_BITS) & (CPU_TLB_SIZE - 1);
    target_ulong tlb_addr;

    res = helper_ret_ldul_mmu(env,addr,oi,retaddr);

    tlb_addr = env->tlb_table[mmu_idx][index].addr_read;

    if (unlikely(tlb_addr & ~TARGET_PAGE_MASK)) {
        //here we have an IO access so we return res and don't perform cache access
        return res;
    } else {
        rabbits_dcache_read_ul(addr & 0x07fffff);
        return res;
    }
}

uint64_t helper_be_ldq_mmu_rabbits(CPUArchState *env, target_ulong addr,
                                     TCGMemOpIdx oi, uintptr_t retaddr)
{
    return helper_be_ldq_mmu(env, addr, oi, retaddr);
}

uint64_t helper_le_ldq_mmu_rabbits(CPUArchState *env, target_ulong addr,
                                     TCGMemOpIdx oi, uintptr_t retaddr)
{
    uint64_t res;
    unsigned mmu_idx = get_mmuidx(oi);
    int index = (addr >> TARGET_PAGE_BITS) & (CPU_TLB_SIZE - 1);
    target_ulong tlb_addr;

    res = helper_ret_ldq_mmu(env,addr,oi,retaddr);

    tlb_addr = env->tlb_table[mmu_idx][index].addr_read;

    if (unlikely(tlb_addr & ~TARGET_PAGE_MASK)) {
        //here we have an IO access so we return res and don't perform cache access
        return res;
    } else {
        rabbits_dcache_read_q(addr & 0x07fffff);
        return res;
    }
}

void helper_be_stq_mmu_rabbits(CPUArchState *env, target_ulong addr, uint64_t val,
                                     TCGMemOpIdx oi, uintptr_t retaddr)
{
    helper_be_stq_mmu(env, addr, val, oi, retaddr);
    //TODO: need to be implemented
}

void helper_le_stq_mmu_rabbits(CPUArchState *env, target_ulong addr, uint64_t val,
                                     TCGMemOpIdx oi, uintptr_t retaddr)
{
    unsigned mmu_idx = get_mmuidx(oi);
    int index = (addr >> TARGET_PAGE_BITS) & (CPU_TLB_SIZE - 1);
    target_ulong tlb_addr;

    helper_le_stq_mmu(env, addr, val, oi, retaddr);

    tlb_addr = env->tlb_table[mmu_idx][index].addr_write;

    if (!unlikely(tlb_addr & ~TARGET_PAGE_MASK)) {
        //here we don't have an IO access so perform cache access
        rabbits_dcache_write_q(addr & 0x07fffff, val);
    }
}

void helper_be_stl_mmu_rabbits(CPUArchState *env, target_ulong addr, uint32_t val,
                                     TCGMemOpIdx oi, uintptr_t retaddr)
{
    helper_be_stl_mmu(env, addr, val, oi, retaddr);
    //TODO: need to be implemented
}

void helper_le_stl_mmu_rabbits(CPUArchState *env, target_ulong addr, uint32_t val,
                                     TCGMemOpIdx oi, uintptr_t retaddr)
{
    unsigned mmu_idx = get_mmuidx(oi);
    int index = (addr >> TARGET_PAGE_BITS) & (CPU_TLB_SIZE - 1);
    target_ulong tlb_addr;

    helper_le_stl_mmu(env, addr, val, oi, retaddr);

    tlb_addr = env->tlb_table[mmu_idx][index].addr_write;

    if (!unlikely(tlb_addr & ~TARGET_PAGE_MASK)) {
        //here we don't have an IO access so perform cache access
        rabbits_dcache_write_l(addr & 0x07fffff, val);
    }

}

void helper_be_stw_mmu_rabbits(CPUArchState *env, target_ulong addr, uint16_t val,
                                     TCGMemOpIdx oi, uintptr_t retaddr)
{
    helper_be_stw_mmu(env, addr, val, oi, retaddr);
    //TODO: need to be implemented
}

void helper_le_stw_mmu_rabbits(CPUArchState *env, target_ulong addr, uint16_t val,
                                     TCGMemOpIdx oi, uintptr_t retaddr)
{
    unsigned mmu_idx = get_mmuidx(oi);
    int index = (addr >> TARGET_PAGE_BITS) & (CPU_TLB_SIZE - 1);
    target_ulong tlb_addr;

    helper_le_stw_mmu(env, addr, val, oi, retaddr);

    tlb_addr = env->tlb_table[mmu_idx][index].addr_write;

    if (!unlikely(tlb_addr & ~TARGET_PAGE_MASK)) {
        //here we don't have an IO access so perform cache access
        rabbits_dcache_write_w(addr & 0x07fffff, val);
    }
}

void helper_ret_stb_mmu_rabbits(CPUArchState *env, target_ulong addr, uint8_t val,
                                     TCGMemOpIdx oi, uintptr_t retaddr)
{
    unsigned mmu_idx = get_mmuidx(oi);
    int index = (addr >> TARGET_PAGE_BITS) & (CPU_TLB_SIZE - 1);
    target_ulong tlb_addr;

    helper_ret_stb_mmu(env, addr, val, oi, retaddr);

    tlb_addr = env->tlb_table[mmu_idx][index].addr_write;

    if (!unlikely(tlb_addr & ~TARGET_PAGE_MASK)) {
        //here we don't have an IO access so perform cache access
        rabbits_dcache_write_b(addr & 0x07fffff, val);
    }

}


/* end helpers*/

void rabbits_icache_call(unsigned long addr)
{
    Global_context->sysc.call_rabbits(Global_context->opaque,
                               ICACHE_CALL,rabbits_cpu_index,addr,0,0);
}


int8_t rabbits_dcache_read_ub(unsigned long addr)
{
//    printf("Reading Byte @%08x\n",addr);
    return (int8_t)Global_context->sysc.call_rabbits(Global_context->opaque,
                               DCACHE_READ_CALL,rabbits_cpu_index,addr,0,1);
}
int16_t rabbits_dcache_read_uw(unsigned long addr)
{
//    printf("Reading Word @%08x\n",addr);
    return (int16_t)Global_context->sysc.call_rabbits(Global_context->opaque,
                               DCACHE_READ_CALL,rabbits_cpu_index,addr,0,2);
}
int32_t rabbits_dcache_read_ul(unsigned long addr)
{
//    printf("Reading Long @%08x\n",addr);
    return (int32_t)Global_context->sysc.call_rabbits(Global_context->opaque,
                               DCACHE_READ_CALL,rabbits_cpu_index,addr,0,4);
}
int64_t rabbits_dcache_read_q(unsigned long addr)
{
//    printf("Reading Q @%08x\n",addr);
    return (int64_t)Global_context->sysc.call_rabbits(Global_context->opaque,
                               DCACHE_READ_CALL,rabbits_cpu_index,addr,0,8);
}



void rabbits_dcache_write_b(unsigned long addr, int8_t val)
{
//    printf("writing byte @%08x\n",addr);
    Global_context->sysc.call_rabbits(Global_context->opaque,
                               DCACHE_WRITE_CALL,rabbits_cpu_index,addr,val,1);
}
void rabbits_dcache_write_w(unsigned long addr, int16_t val)
{
//    printf("writing word @%08x\n",addr);
    Global_context->sysc.call_rabbits(Global_context->opaque,
                               DCACHE_WRITE_CALL,rabbits_cpu_index,addr,val,2);
}
void rabbits_dcache_write_l(unsigned long addr, int32_t val)
{
//    printf("writing long @%08x\n",addr);
    Global_context->sysc.call_rabbits(Global_context->opaque,
                               DCACHE_WRITE_CALL,rabbits_cpu_index,addr,val,4);
}
void rabbits_dcache_write_q(unsigned long addr, int64_t val)
{
//    printf("writing Q @%08x\n",addr);
    Global_context->sysc.call_rabbits(Global_context->opaque,
                               DCACHE_WRITE_CALL,rabbits_cpu_index,addr,val,8);
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
                                   ANNOTATION_CALL,rabbits_cpu_index,nb_cycles,0,0);
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
                                        INFO_CALL,0,0,0,0);
}

__attribute__((constructor))
void rabbits_init(void)
{
//       atexit(rabbits_report);
}

