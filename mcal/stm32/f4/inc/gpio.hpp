#include "concept/gpio.hpp"
#include "stm32f4xx.h"
template <uint32_t GPIO_BASE, uint32_t RCC_AHB1ENR_GPIOxEN>
struct GpioImpl
{
    static void enable() { RCC->AHB1ENR |= RCC_AHB1ENR_GPIOxEN; }
    static void disable() { RCC->AHB1ENR &= ~RCC_AHB1ENR_GPIOxEN; }

    template <uint8_t pin, GpioPinMode M>
    static void setMode()
    {
        GPIO_TypeDef *gpio = reinterpret_cast<GPIO_TypeDef *>(GPIO_BASE);
        gpio->MODER &= ~(0b11 << (pin * 2));
        if constexpr (M == GpioPinMode::Output)
        {
            gpio->MODER |= (0b01 << (pin * 2));
        }
        else if constexpr (M == GpioPinMode::Input)
        {
            // nothing to to, its empty
        }
    }
    template <uint8_t pin>
    static void writeHigh() { reinterpret_cast<GPIO_TypeDef *>(GPIO_BASE)->ODR |= (1 << pin); }
    template <uint8_t pin>
    static void writeLow() { reinterpret_cast<GPIO_TypeDef *>(GPIO_BASE)->ODR &= ~(1 << pin); }
};

using GpioA = GpioImpl<GPIOA_BASE, RCC_AHB1ENR_GPIOAEN>;
using GpioB = GpioImpl<GPIOB_BASE, RCC_AHB1ENR_GPIOBEN>;
using GpioC = GpioImpl<GPIOC_BASE, RCC_AHB1ENR_GPIOCEN>;
using GpioD = GpioImpl<GPIOD_BASE, RCC_AHB1ENR_GPIODEN>;
using GpioE = GpioImpl<GPIOE_BASE, RCC_AHB1ENR_GPIOEEN>;
using GpioF = GpioImpl<GPIOF_BASE, RCC_AHB1ENR_GPIOFEN>;
using GpioG = GpioImpl<GPIOG_BASE, RCC_AHB1ENR_GPIOGEN>;
using GpioH = GpioImpl<GPIOH_BASE, RCC_AHB1ENR_GPIOHEN>;

template <GpioPort Port, uint8_t Pin, GpioPinMode Mode = GpioPinMode::Input>
struct GpioPin
{
    static void init()
    {
        Port::enable();
        Port::template setMode<Pin, Mode>();
    }
    static void set() { Port::template writeHigh<Pin>(); }
    static void clear() { Port::template writeLow<Pin>(); }
};