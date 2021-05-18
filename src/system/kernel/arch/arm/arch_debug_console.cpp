/*
 * Copyright 2007, François Revol, revol@free.fr.
 * Distributed under the terms of the MIT License.
 *
 * Copyright 2003-2006, Axel Dörfler, axeld@pinc-software.de.
 * Distributed under the terms of the MIT License.
 *
 * Copyright 2001, Travis Geiselbrecht. All rights reserved.
 * Distributed under the terms of the NewOS License.
 */


//#include <arch_platform.h>
#include <arch/debug_console.h>
#include <arch/generic/debug_uart.h>
#include <arch/arm/arch_uart_pl011.h>
#include <boot/kernel_args.h>
#include <kernel.h>
#include <vm/vm.h>
#include <string.h>


// TODO: Declare this in some header
DebugUART *gArchDebugUART;
extern DebugUART *debug_uart_from_fdt(const void *fdt);


void
arch_debug_remove_interrupt_handler(uint32 line)
{
}


void
arch_debug_install_interrupt_handlers(void)
{
}


int
arch_debug_blue_screen_try_getchar(void)
{
	// TODO: Implement correctly!
	return arch_debug_blue_screen_getchar();
}


char
arch_debug_blue_screen_getchar(void)
{
	return arch_debug_serial_getchar();
}


int
arch_debug_serial_try_getchar(void)
{
	// TODO: Implement correctly!
	return arch_debug_serial_getchar();
}


char
arch_debug_serial_getchar(void)
{
	if (gArchDebugUART == NULL)
		return NULL;

	return gArchDebugUART->GetChar(false);
}


void
arch_debug_serial_putchar(const char c)
{
    extern int PL011PutChar(char c);
    PL011PutChar(c);
    return;

	if (gArchDebugUART == NULL)
		return;

	gArchDebugUART->PutChar(c);
}


void
arch_debug_serial_puts(const char *s)
{
	while (*s != '\0') {
		arch_debug_serial_putchar(*s);
		s++;
	}
}


void
arch_debug_serial_early_boot_message(const char *string)
{
	// this function will only be called in fatal situations
	arch_debug_serial_puts(string);
}

status_t
arch_debug_console_init(kernel_args *args)
{
	// first try with hints from the FDT
	// TODO: Use UEFI somehow to get fdt
	//gArchDebugUART = debug_uart_from_fdt(args->platform_args.fdt);

	// As a last try, lets assume qemu's pl011 at a sane address
	if (gArchDebugUART == NULL)
		gArchDebugUART = arch_get_uart_pl011(0x9000000, 0x16e3600);

	// Oh well.
	if (gArchDebugUART == NULL)
		return B_ERROR;


//    gArchDebugUART->Enable();
//	gArchDebugUART->InitEarly();

    int32 ii = 0;
    char gd[20] = "HACB\n";
    while (ii<6) {
        arch_debug_serial_putchar(gd[ii]);
        ii++;
    }

    ii = 0;
    char gc[20] = {'H', 'A', 'C', 'B', '\n'};
    while (ii<6) {
        arch_debug_serial_putchar(gc[ii]);
        ii++;
    }

	return B_OK;
}


status_t
arch_debug_console_init_settings(kernel_args *args)
{
	return B_OK;
}
