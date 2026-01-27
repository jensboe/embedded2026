#include <cstdint>
#include "stm32f4xx.h"

int main(void)
{
    
    // Enable GPIO B clock
    RCC->AHB1ENR |= RCC_AHB1ENR_GPIOBEN;

    // Configure PB0 (LED) as output
    GPIOB->MODER |= GPIO_MODER_MODE0_0; // Set PA5 to output mode

    // Main loop
    while (1)
    {
        // Turn LED on
        GPIOB->ODR |= (1 << 0);

        // Turn LED off
        GPIOB->ODR &= ~(1 << 0);
    }

    return 0;
}
