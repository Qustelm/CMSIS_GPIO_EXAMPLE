#include "stm32f10x.h"
#include CMSIS_device_header

void INIT_GPIOC13_OUTPUT() {
    // configure PC13 (LED port) as push-pull output 2 MHz

    RCC->APB2ENR |= RCC_APB2ENR_IOPCEN; // enable GPIOC clocking
    GPIOC->CRH &= ~(GPIO_CRH_CNF13 | GPIO_CRH_MODE13); // clear control bits
    GPIOC->CRH |= GPIO_CRH_MODE13_0; // MODE = 01 (output, 2 MHz), CNF = 00 (push-pull)
}

void INIT_GPIOA0_INPUT() {
    // configure PA0 as input with pull-up

    RCC->APB2ENR |= RCC_APB2ENR_IOPAEN; // enable GPIOA clocking
    GPIOA->CRL &= ~(GPIO_CRL_CNF0 | GPIO_CRL_MODE0); // clear control bits

    // MODE = 00, CNF = 10 - input with pull-up/down
    GPIOA->CRL |= GPIO_CRL_CNF0_1;
    GPIOA->ODR |= GPIO_ODR_ODR0; // enable pull-up
}

int main() {
    INIT_GPIOC13_OUTPUT();
    INIT_GPIOA0_INPUT();
    while (1) {
        if (!READ_BIT(GPIOA->IDR, GPIO_IDR_IDR0)) {
            GPIOC->BSRR = GPIO_BSRR_BS13; // set PC13 high (LED off on BluePill)
        } else {
            GPIOC->BSRR = GPIO_BSRR_BR13; // set PC13 low (LED on)
        }
    }
}
