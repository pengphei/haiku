/*
 * Copyright 2007, François Revol, revol@free.fr.
 * Distributed under the terms of the MIT License.
 *
 * Copyright 2006, Ingo Weinhold <bonefish@cs.tu-berlin.de>.
 * All rights reserved. Distributed under the terms of the MIT License.
 */

#include <KernelExport.h>
#include <arch/platform.h>
#include <boot/kernel_args.h>


status_t
arch_platform_init(struct kernel_args *kernelArgs)
{
	// NOTE: dprintf() is off-limits here, too early...
    // disable mmu
    __asm__ __volatile__("mrc p15, 0, r1, c1, c0, 0");
    __asm__ __volatile__("bic r1, r1, #0x1");
    __asm__ __volatile__("mcr p15, 0, r1, c1, c0, 0");

    // disable l1 cache
    __asm__ __volatile__("mrc p15, 0, r1, c1, c0, 0");
    __asm__ __volatile__("bic r1, r1, #(0x1 << 12)");
    __asm__ __volatile__("bic r1, r1, #(0x1 << 2)");
    __asm__ __volatile__("mcr p15, 0, r1, c1, c0, 0");

    // invalidate l1 cache
    //__asm__ __volatile__("mov r1, #0");
    //__asm__ __volatile__("mcr p15, 0, r1, c7, c5, 0");

    // invalidate tlb
    //__asm__ __volatile__("mcr p15, 0, r1, c8, c7, 0");
	return B_OK;
}

status_t
arch_platform_init_post_vm(struct kernel_args *kernelArgs)
{
	// no area to create, since we pass the FDT in the kernel_args
	// and the VM automagically creates the area's (with B_EXACT_ADDRESS)
	// for them.
	return B_OK;
}


status_t
arch_platform_init_post_thread(struct kernel_args *kernelArgs)
{
	// now we can create and use semaphores
	return B_OK;
}
