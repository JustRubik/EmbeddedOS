#pragma once
#include <stdint.h>

/* Base Addresses */
#define RCC_BASE      0x40021000UL
#define GPIOA_BASE    0x40010800UL
#define USART1_BASE   0x40013800UL

/* RCC Bit Definitions */
#define RCC_APB2ENR_IOPAEN   (1U << 2)
#define RCC_APB2ENR_AFIOEN   (1U << 0)
#define RCC_APB2ENR_USART1EN (1U << 14)

/* USART Bit Definitions */
#define USART_SR_TXE         (1U << 7)
#define USART_SR_TC          (1U << 6)
#define USART_CR1_UE         (1U << 13)
#define USART_CR1_TE         (1U << 3)
#define USART_CR1_RE         (1U << 2)

/* Structs */
typedef struct {
    volatile uint32_t CRL, CRH, IDR, ODR, BSRR, BRR, LCKR;
} GPIO_TypeDef;

typedef struct {
    volatile uint32_t CR, CFGR, CIR, APB2RSTR, APB1RSTR, AHBENR, APB2ENR, APB1ENR, BDCR, CSR;
} RCC_TypeDef;

typedef struct {
    volatile uint32_t SR, DR, BRR, CR1, CR2, CR3, GTPR;
} USART_TypeDef;

/* Peripheral Mapping */
#define RCC    ((RCC_TypeDef *)RCC_BASE)
#define GPIOA  ((GPIO_TypeDef *)GPIOA_BASE)
#define USART1 ((USART_TypeDef *)USART1_BASE)
