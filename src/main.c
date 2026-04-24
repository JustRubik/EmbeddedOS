#include <stdint.h>
#include "main.h"

int main()
{
    uart_init();
    uart_puts("hello world\r\n");
    uart_flush();

    for (;;) {
        __asm__ volatile ("wfi");
    }
}
