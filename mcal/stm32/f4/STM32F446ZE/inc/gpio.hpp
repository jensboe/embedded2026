#include "concept/gpio.hpp"
#include "stm32f4xx.h"

struct Stm32GpioB
{
    static void enableClock() { RCC->AHB1ENR |= RCC_AHB1ENR_GPIOBEN; }
    static void setModeOutput(uint8_t pin)
    {
        GPIOB->MODER &= ~(0b11 << (pin * 2));
        GPIOB->MODER |= (0b01 << (pin * 2));
    }
    static void writeHigh(uint8_t pin) { GPIOB->ODR |= (1 << pin); }
    static void writeLow(uint8_t pin) { GPIOB->ODR &= ~(1 << pin); }
};

template <GpioPort Port, uint8_t Pin>
struct Gpio
{
    static void init()
    {
        Port::enableClock();
        Port::setModeOutput(Pin);
    }
    static void set() { Port::writeHigh(Pin); }
    static void clear() { Port::writeLow(Pin); }
};