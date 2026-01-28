#include "concept/gpio.hpp"
#include "stm32f4xx.h"
template <uint32_t GPIO_BASE, uint32_t RCC_AHB1ENR_GPIOxEN>
struct stm32f4gpio
{
private:
    static GPIO_TypeDef *getGpio()
    {
        return reinterpret_cast<GPIO_TypeDef *>(GPIO_BASE);
    }

public:
    static void enableClock() { RCC->AHB1ENR |= RCC_AHB1ENR_GPIOxEN; }
    static void setModeOutput(uint8_t pin)
    {
        GPIOB->MODER &= ~(0b11 << (pin * 2));
        GPIOB->MODER |= (0b01 << (pin * 2));
    }
    static void writeHigh(uint8_t pin) { GPIOB->ODR |= (1 << pin); }
    static void writeLow(uint8_t pin) { GPIOB->ODR &= ~(1 << pin); }
};

using GpioA = stm32f4gpio<GPIOA_BASE, RCC_AHB1ENR_GPIOAEN>;
using GpioB = stm32f4gpio<GPIOB_BASE, RCC_AHB1ENR_GPIOBEN>;
using GpioC = stm32f4gpio<GPIOC_BASE, RCC_AHB1ENR_GPIOCEN>;
using GpioD = stm32f4gpio<GPIOD_BASE, RCC_AHB1ENR_GPIODEN>;
using GpioE = stm32f4gpio<GPIOE_BASE, RCC_AHB1ENR_GPIOEEN>;
using GpioF = stm32f4gpio<GPIOF_BASE, RCC_AHB1ENR_GPIOFEN>;
using GpioG = stm32f4gpio<GPIOG_BASE, RCC_AHB1ENR_GPIOGEN>;
using GpioH = stm32f4gpio<GPIOH_BASE, RCC_AHB1ENR_GPIOHEN>;


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