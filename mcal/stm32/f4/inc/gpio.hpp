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
    static void writeHigh()
    {
        static_assert(pin < 16, "GPIO pin index must be < 16");
        reinterpret_cast<GPIO_TypeDef *>(GPIO_BASE)->ODR |= (1 << pin);
    }
    template <uint8_t pin>
    static void writeLow()
    {
        static_assert(pin < 16, "GPIO pin index must be < 16");
        reinterpret_cast<GPIO_TypeDef *>(GPIO_BASE)->ODR &= ~(1 << pin);
    }
    template <uint8_t pin>
    static bool read()
    {
        static_assert(pin < 16, "GPIO pin index must be < 16");
        return reinterpret_cast<GPIO_TypeDef *>(GPIO_BASE)->IDR & (1 << pin);
    }
};
#ifdef GPIOA_BASE
using GpioA = GpioImpl<GPIOA_BASE, RCC_AHB1ENR_GPIOAEN>;
static_assert(GpioPort<GpioA>);
#endif
#ifdef GPIOB_BASE
using GpioB = GpioImpl<GPIOB_BASE, RCC_AHB1ENR_GPIOBEN>;
static_assert(GpioPort<GpioB>);
#endif
#ifdef GPIOC_BASE
using GpioC = GpioImpl<GPIOC_BASE, RCC_AHB1ENR_GPIOCEN>;
static_assert(GpioPort<GpioC>);
#endif
#ifdef GPIOD_BASE
using GpioD = GpioImpl<GPIOD_BASE, RCC_AHB1ENR_GPIODEN>;
static_assert(GpioPort<GpioD>);
#endif
#ifdef GPIOE_BASE
using GpioE = GpioImpl<GPIOE_BASE, RCC_AHB1ENR_GPIOEEN>;
static_assert(GpioPort<GpioE>);
#endif
#ifdef GPIOF_BASE
using GpioF = GpioImpl<GPIOF_BASE, RCC_AHB1ENR_GPIOFEN>;
static_assert(GpioPort<GpioF>);
#endif
#ifdef GPIOG_BASE
using GpioG = GpioImpl<GPIOG_BASE, RCC_AHB1ENR_GPIOGEN>;
static_assert(GpioPort<GpioG>);
#endif
#ifdef GPIOH_BASE
using GpioH = GpioImpl<GPIOH_BASE, RCC_AHB1ENR_GPIOHEN>;
static_assert(GpioPort<GpioH>);
#endif
#ifdef GPIOI_BASE
using GpioI = GpioImpl<GPIOI_BASE, RCC_AHB1ENR_GPIOIEN>;
static_assert(GpioPort<GpioH>);
#endif
#ifdef GPIOJ_BASE
using GpioJ = GpioImpl<GPIOJ_BASE, RCC_AHB1ENR_GPIOJEN>;
static_assert(GpioPort<GpioJ>);
#endif
#ifdef GPIOK_BASE
using GpioK = GpioImpl<GPIOK_BASE, RCC_AHB1ENR_GPIOKEN>;
static_assert(GpioPort<GpioK>);
#endif

template <GpioPort Port, uint8_t Pin, GpioPinMode Mode = GpioPinMode::Input>
struct GpioPin
{
    static_assert(Pin < 16, "GPIO pin index must be < 16");
    static void init()
    {
        Port::enable();
        Port::template setMode<Pin, Mode>();
    }
    static void set() { Port::template writeHigh<Pin>(); }
    static void clear() { Port::template writeLow<Pin>(); }
};