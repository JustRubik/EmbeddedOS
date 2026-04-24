#include "uart.h"

void uart_init(void)
{
    RCC->APB2ENR |= RCC_APB2ENR_IOPAEN | RCC_APB2ENR_AFIOEN | RCC_APB2ENR_USART1EN;

    /* PA9  = USART1_TX  -> Alternate Function Push-Pull, 50 MHz
       PA10 = USART1_RX  -> Input Floating
       CRH layout: each pin uses 4 bits, pins 8..15 are in CRH. */
    GPIOA->CRH &= ~((0xFU << 4) | (0xFU << 8));
    GPIOA->CRH |=  ((0xBU << 4) | (0x4U << 8));

    USART1->CR1 = 0;
    USART1->CR2 = 0;
    USART1->CR3 = 0;

    USART1->BRR = UART_BRR_24MHZ_115200;
    USART1->CR1 = USART_CR1_UE | USART_CR1_TE | USART_CR1_RE;
}

void uart_putc(char c)
{
    while ((USART1->SR & USART_SR_TXE) == 0U) {
        /* wait */
    }
    USART1->DR = (uint32_t)(uint8_t)c;
}

void uart_puts(const char *s)
{
    while (*s != '\0') {
        uart_putc(*s++);
    }
}

void uart_flush(void)
{
    while ((USART1->SR & USART_SR_TC) == 0U) {
        /* wait */
    }
}


