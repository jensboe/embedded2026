#include <cstdint>
#include "stm32f4xx.h"

// Main entry point for the STM32F446ZE microcontroller
int main(void)
{
    // Enable GPIO A clock
    RCC->AHB1ENR |= RCC_AHB1ENR_GPIOAEN;

    // Configure PA5 (LED) as output
    GPIOA->MODER |= GPIO_MODER_MODE5_0; // Set PA5 to output mode

    // Main loop
    while (1)
    {
        // Turn LED on
        GPIOA->ODR |= (1 << 5);

        // Turn LED off
        GPIOA->ODR &= ~(1 << 5);
    }

    return 0;
}
