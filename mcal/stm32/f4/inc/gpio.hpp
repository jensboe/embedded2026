#include "concept/gpio.hpp"
#include "stm32f4xx.h"
template <uint32_t GPIO_BASE, uint32_t RCC_AHB1ENR_GPIOxEN>
struct GpioImpl
{
private:
    static GPIO_TypeDef *getGpio()
    {
        return reinterpret_cast<GPIO_TypeDef *>(GPIO_BASE);
    }

public:
    static void enable() { RCC->AHB1ENR |= RCC_AHB1ENR_GPIOxEN; }
    static void disable() { RCC->AHB1ENR &= ~RCC_AHB1ENR_GPIOxEN; }

    template <GpioPinMode M>
    static void setMode(uint8_t pin)
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

    static void writeHigh(uint8_t pin) { reinterpret_cast<GPIO_TypeDef *>(GPIO_BASE)->ODR |= (1 << pin); }
    static void writeLow(uint8_t pin) { reinterpret_cast<GPIO_TypeDef *>(GPIO_BASE)->ODR &= ~(1 << pin); }
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
        Port::template setMode<Mode>(Pin);
    }
    static void set() { Port::writeHigh(Pin); }
    static void clear() { Port::writeLow(Pin); }
};