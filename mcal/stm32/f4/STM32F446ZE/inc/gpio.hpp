#include "concept/gpio.hpp"
#include "stm32f4xx.h"
template <uint32_t GPIO_BASE>
struct stm32f4gpio
{
private:
    static GPIO_TypeDef *getGpio()
    {
        return reinterpret_cast<GPIO_TypeDef *>(GPIO_BASE);
    }

public:
    static void enableClock() { RCC->AHB1ENR |= RCC_AHB1ENR_GPIOBEN; }
    static void setModeOutput(uint8_t pin)
    {
        GPIOB->MODER &= ~(0b11 << (pin * 2));
        GPIOB->MODER |= (0b01 << (pin * 2));
    }
    static void writeHigh(uint8_t pin) { GPIOB->ODR |= (1 << pin); }
    static void writeLow(uint8_t pin) { GPIOB->ODR &= ~(1 << pin); }
};

using GpioB = stm32f4gpio<GPIOB_BASE>;

template <GpioPort Port, uint8_t Pin>
struct GpioPin
{
    static void init()
    {
        Port::enableClock();
        Port::setModeOutput(Pin);
    }
    static void set() { Port::writeHigh(Pin); }
    static void clear() { Port::writeLow(Pin); }
};