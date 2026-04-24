#pragma once
#include "regs.h"

#define UART_BRR_24MHZ_115200 0x00D0U

void uart_init(void);
void uart_putc(char c);
void uart_puts(const char *s);
void uart_flush(void);
