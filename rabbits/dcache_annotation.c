#include "annotation.h"

//This should be architecture independant


//extern declaration
extern int32_t rabbits_cpu_index;

/* Helper Implementation*/

tcg_target_ulong helper_ret_ldub_mmu_rabbits(CPUArchState *env, target_ulong addr,
                                     TCGMemOpIdx oi, uintptr_t retaddr)
{
    tcg_target_ulong res,tmp;
    unsigned mmu_idx = get_mmuidx(oi);
    int index = (addr >> TARGET_PAGE_BITS) & (CPU_TLB_SIZE - 1);
    target_ulong tlb_addr;

    res = helper_ret_ldub_mmu(env,addr,oi,retaddr);

    tlb_addr = env->tlb_table[mmu_idx][index].addr_read;

    if (unlikely(tlb_addr & ~TARGET_PAGE_MASK)) {
        //here we have an IO access so we return res and don't perform cache access
        return res;
    } else {
        tmp = rabbits_dcache_read_ub(addr & 0x0fffffff); //HERE we should get Physical Guest addr
        if(tmp!=res) {
            DPRINTF("Reading data @ addr = %08x [tlb_addr = %08x, addend = %08x]\n",addr,tlb_addr,env->tlb_table[mmu_idx][index].addend);
            DPRINTF("qemu data = %02x -- Systemc data = %02x\n",res,tmp);
        }
#ifdef FULL_CACHE
        return /*tmp*/res;
#else
        return res;
#endif
    }
}

tcg_target_ulong helper_ret_ldsb_mmu_rabbits(CPUArchState *env, target_ulong addr,
                                     TCGMemOpIdx oi, uintptr_t retaddr)
{
    return (int8_t)helper_ret_ldub_mmu_rabbits(env,addr,oi,retaddr);
}

tcg_target_ulong helper_be_lduw_mmu_rabbits(CPUArchState *env, target_ulong addr,
                                     TCGMemOpIdx oi, uintptr_t retaddr)
{
    return helper_be_lduw_mmu(env, addr, oi, retaddr);
}

tcg_target_ulong helper_le_lduw_mmu_rabbits(CPUArchState *env, target_ulong addr,
                                     TCGMemOpIdx oi, uintptr_t retaddr)
{
    tcg_target_ulong res,tmp;
    unsigned mmu_idx = get_mmuidx(oi);
    int index = (addr >> TARGET_PAGE_BITS) & (CPU_TLB_SIZE - 1);
    target_ulong tlb_addr;


    res = helper_le_lduw_mmu(env,addr,oi,retaddr);

    tlb_addr = env->tlb_table[mmu_idx][index].addr_read;

    if (unlikely(tlb_addr & ~TARGET_PAGE_MASK)) {
        //here we have an IO access so we return res and don't perform cache access
        return res;
    } else {
        tmp = rabbits_dcache_read_uw(addr & 0x0fffffff);
        if(res!=tmp) {
            DPRINTF("Reading data @ addr = %08x [tlb_addr = %08x, addend = %08x]\n",addr,tlb_addr,env->tlb_table[mmu_idx][index].addend);
            DPRINTF("qemu data = %04x -- Systemc data = %04x\n",res,tmp);
        }
#ifdef FULL_CACHE
        return /*tmp*/res;
#else
        return res;
#endif
    }
}

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


tcg_target_ulong helper_be_ldul_mmu_rabbits(CPUArchState *env, target_ulong addr,
                                     TCGMemOpIdx oi, uintptr_t retaddr)
{
    return helper_be_ldul_mmu(env, addr, oi, retaddr);
}

tcg_target_ulong helper_le_ldul_mmu_rabbits(CPUArchState *env, target_ulong addr,
                                     TCGMemOpIdx oi, uintptr_t retaddr)
{
    tcg_target_ulong res,tmp;
    unsigned mmu_idx = get_mmuidx(oi);
    int index = (addr >> TARGET_PAGE_BITS) & (CPU_TLB_SIZE - 1);
    target_ulong tlb_addr;

    res = helper_ret_ldul_mmu(env,addr,oi,retaddr);

    tlb_addr = env->tlb_table[mmu_idx][index].addr_read;

    if (unlikely(tlb_addr & ~TARGET_PAGE_MASK)) {
        //here we have an IO access so we return res and don't perform cache access
        return res;
    } else {
        tmp = rabbits_dcache_read_ul(addr & 0x0fffffff);
        if(tmp!=res) {
            DPRINTF("Reading data @ addr = %08x [tlb_addr = %08x, addend = %08x]\n",addr,tlb_addr,env->tlb_table[mmu_idx][index].addend);
            DPRINTF("qemu data = %08x -- Systemc data = %08x\n",res,tmp);
        }
#ifdef FULL_CACHE
        return /*tmp*/res;
#else
        return res;
#endif
    }
}

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

uint64_t helper_be_ldq_mmu_rabbits(CPUArchState *env, target_ulong addr,
                                     TCGMemOpIdx oi, uintptr_t retaddr)
{
    return helper_be_ldq_mmu(env, addr, oi, retaddr);
}

uint64_t helper_le_ldq_mmu_rabbits(CPUArchState *env, target_ulong addr,
                                     TCGMemOpIdx oi, uintptr_t retaddr)
{
    uint64_t res,tmp;
    unsigned mmu_idx = get_mmuidx(oi);
    int index = (addr >> TARGET_PAGE_BITS) & (CPU_TLB_SIZE - 1);
    target_ulong tlb_addr;

    res = helper_ret_ldq_mmu(env,addr,oi,retaddr);

    tlb_addr = env->tlb_table[mmu_idx][index].addr_read;

    if (unlikely(tlb_addr & ~TARGET_PAGE_MASK)) {
        //here we have an IO access so we return res and don't perform cache access
        return res;
    } else {
        tmp=rabbits_dcache_read_q(addr & 0x0fffffff);
        DPRINTF("qemu data = %x -- Systemc data = %x\n",res,tmp);
        DPRINTF("Reading data @ addr = %08x [tlb_addr = %08x, addend = %08x]\n",addr,tlb_addr,env->tlb_table[mmu_idx][index].addend);
#ifdef FULL_CACHE
        return /*tmp*/res;
#else
        return res;
#endif
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

    DPRINTF("Writing 64bit @ %08x val = %08x\n",addr,val);
    if (!unlikely(tlb_addr & ~TARGET_PAGE_MASK)) {
        //here we don't have an IO access so perform cache access
        rabbits_dcache_write_q(addr & 0x0fffffff , val);
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

    DPRINTF("Writing 32bit @ %08x val = %08x\n",addr,val);
    if (!unlikely(tlb_addr & ~TARGET_PAGE_MASK)) {
        //here we don't have an IO access so perform cache access
        rabbits_dcache_write_l(addr & 0x0fffffff , val);
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

    DPRINTF("Writing 16bit @ %08x val = %08x\n",addr,val);
    if (!unlikely(tlb_addr & ~TARGET_PAGE_MASK)) {
        //here we don't have an IO access so perform cache access
        rabbits_dcache_write_w(addr & 0x0fffffff , val);
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

    DPRINTF("Writing 8bit @ %08x val = %08x\n",addr,val);
    if (!unlikely(tlb_addr & ~TARGET_PAGE_MASK)) {
        //here we don't have an IO access so perform cache access
        rabbits_dcache_write_b(addr & 0x0fffffff , val);
    }

}


/* end helpers*/


uint8_t rabbits_dcache_read_ub(unsigned long addr)
{
//    DPRINTF("Reading Byte @%08x\n",addr);
    return (uint8_t)Global_context->sysc.call_rabbits(Global_context->opaque,
                               DCACHE_READ_CALL,rabbits_cpu_index,addr,0,1);
}
uint16_t rabbits_dcache_read_uw(unsigned long addr)
{
//    DPRINTF("Reading Word @%08x\n",addr);
    return (uint16_t)Global_context->sysc.call_rabbits(Global_context->opaque,
                               DCACHE_READ_CALL,rabbits_cpu_index,addr,0,2);
}
uint32_t rabbits_dcache_read_ul(unsigned long addr)
{
//    DPRINTF("Reading Long @%08x\n",addr);
    return (uint32_t)Global_context->sysc.call_rabbits(Global_context->opaque,
                               DCACHE_READ_CALL,rabbits_cpu_index,addr,0,4);
}
uint64_t rabbits_dcache_read_q(unsigned long addr)
{
//    DPRINTF("Reading Q @%08x\n",addr);
    return (uint64_t)Global_context->sysc.call_rabbits(Global_context->opaque,
                               DCACHE_READ_CALL,rabbits_cpu_index,addr,0,8);
}



void rabbits_dcache_write_b(unsigned long addr, uint8_t val)
{
//    DPRINTF("writing byte @%08x\n",addr);
    Global_context->sysc.call_rabbits(Global_context->opaque,
                               DCACHE_WRITE_CALL,rabbits_cpu_index,addr,val,1);
}
void rabbits_dcache_write_w(unsigned long addr, uint16_t val)
{
//    DPRINTF("writing word @%08x\n",addr);
    Global_context->sysc.call_rabbits(Global_context->opaque,
                               DCACHE_WRITE_CALL,rabbits_cpu_index,addr,val,2);
}
void rabbits_dcache_write_l(unsigned long addr, uint32_t val)
{
//    DPRINTF("writing long @%08x\n",addr);
    Global_context->sysc.call_rabbits(Global_context->opaque,
                               DCACHE_WRITE_CALL,rabbits_cpu_index,addr,val,4);
}
void rabbits_dcache_write_q(unsigned long addr, uint64_t val)
{
//    DPRINTF("writing Q @%08x\n",addr);
    Global_context->sysc.call_rabbits(Global_context->opaque,
                               DCACHE_WRITE_CALL,rabbits_cpu_index,addr,val,8);
}


