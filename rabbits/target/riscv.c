#include "hw/sysbus.h"
#include "sysemu/sysemu.h"
#include "hw/riscv/cpudevs.h"

#include "target.h"
#include "riscv.h"
#include "../sc_qemu.h"
#include "../sc_qdev_priv.h"

void sc_qemu_machine_init_target(qemu_context *ctx, const char *model)
{
    RISCVCPU *cpu;
    char const *m = model;
    int i;

    if(model == NULL) {
        m = "riscv-generic";
    }

    ctx->cpus = g_malloc0(sizeof(CPUState*) * smp_cpus);

    for(i = 0; i < smp_cpus; i++) {
        cpu = cpu_riscv_init(m);
        if (!cpu) {
            fprintf(stderr, "Unable to find CPU definition\n");
            exit(1);
        }

        cpu_riscv_clock_init(&cpu->env);
        ctx->cpus[i] = CPU(cpu);
    }
}

void sc_qemu_target_qdev_create(sc_qemu_qdev *ret, sc_qemu_qdev_e devid, va_list ap)
{
}
