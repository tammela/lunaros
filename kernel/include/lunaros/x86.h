#ifndef _X86_H
#define _X86_H

#include <std/stddef.h>

#include <lunaros/irq.h>
#include <lunaros/compiler.h>

static __inline void outb(uint16_t port, uint8_t val) {
   asm volatile("outb %0, %1" ::"a"(val), "Nd"(port));
}

/*
** Start all interrupts from the CPU
*/
static __inline void sti(void) {
   asm volatile("sti");
}

/*
** Stop all interrupts from the CPU
*/
static __inline void cli(void) {
   asm volatile("cli");
}

/*
** Loads the interrupt descriptor table
*/
static __inline void lidt(struct gate *entries, uint16_t size) {
   volatile struct idt idt;
   idt.size = size;
   idt.addr = (uint64_t)entries;
   asm volatile("lidt %0" ::"r"(idt));
}

/*
** Access the MSR registers
*/
static __inline void msr(uint32_t ecx, uint32_t *eax, uint32_t *edx) {
   uint32_t outa, outd;
   asm volatile("movl %2, %%ecx;"
                "rdmsr;"
                "movl %%eax, %0;"
                "movl %%edx, %1;"
                : "=m"(outa), "=m"(outd)
                : "r"(ecx)
   );
   *eax = outa;
   *edx = outd;
}

#endif /* _X86_H */
