#include <stdint.h>

#define RCC_BASE    0x40021000UL
#define GPIOA_BASE  0x40010800UL
#define USART1_BASE 0x40013800UL

#define RCC_APB2ENR_IOPAEN   (1U << 2)
#define RCC_APB2ENR_AFIOEN   (1U << 0)
#define RCC_APB2ENR_USART1EN (1U << 14)

#define USART_SR_TXE         (1U << 7)
#define USART_SR_TC          (1U << 6)
#define USART_CR1_UE         (1U << 13)
#define USART_CR1_TE         (1U << 3)
#define USART_CR1_RE         (1U << 2)

typedef struct {
    volatile uint32_t CRL;
    volatile uint32_t CRH;
    volatile uint32_t IDR;
    volatile uint32_t ODR;
    volatile uint32_t BSRR;
    volatile uint32_t BRR;
    volatile uint32_t LCKR;
} GPIO_TypeDef;

typedef struct {
    volatile uint32_t SR;
    volatile uint32_t DR;
    volatile uint32_t BRR;
    volatile uint32_t CR1;
    volatile uint32_t CR2;
    volatile uint32_t CR3;
    volatile uint32_t GTPR;
} USART_TypeDef;

typedef struct {
    volatile uint32_t CR;
    volatile uint32_t CFGR;
    volatile uint32_t CIR;
    volatile uint32_t APB2RSTR;
    volatile uint32_t APB1RSTR;
    volatile uint32_t AHBENR;
    volatile uint32_t APB2ENR;
    volatile uint32_t APB1ENR;
    volatile uint32_t BDCR;
    volatile uint32_t CSR;
} RCC_TypeDef;

#define RCC    ((RCC_TypeDef *)RCC_BASE)
#define GPIOA  ((GPIO_TypeDef *)GPIOA_BASE)
#define USART1 ((USART_TypeDef *)USART1_BASE)

/* QEMU stm32vldiscovery runs with a fixed 24 MHz SYSCLK. */
#define UART_BRR_24MHZ_115200 0x00D0U

static void uart_init(void)
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

static void uart_putc(char c)
{
    while ((USART1->SR & USART_SR_TXE) == 0U) {
        /* wait */
    }
    USART1->DR = (uint32_t)(uint8_t)c;
}

static void uart_puts(const char *s)
{
    while (*s != '\0') {
        uart_putc(*s++);
    }
}

static void uart_flush(void)
{
    while ((USART1->SR & USART_SR_TC) == 0U) {
        /* wait */
    }
}

int main(void)
{
    uart_init();
    uart_puts("hello world\r\n");
    uart_flush();

    for (;;) {
        __asm__ volatile ("nop");
    }
}
