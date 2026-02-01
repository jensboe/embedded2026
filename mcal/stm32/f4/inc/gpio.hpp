/**
 * @file gpio.hpp
 * @brief GPIO abstraction layer for STM32F4 series.
 *
 * This header provides a compile‑time GPIO implementation for STM32F4
 * microcontrollers. It exposes low‑level port control (clock enable/disable,
 * mode configuration, I/O operations) as well as a high‑level pin abstraction
 * that binds a specific port and pin into a type‑safe interface.
 *
 * The design follows a zero‑overhead, constexpr‑driven approach and integrates
 * with the mcal::concepts::GpioPort and GpioPin concepts to ensure correctness
 * at compile time.
 */
#pragma once
#include "mcal.hpp"
#include "stm32f4xx.h"
namespace stm32::f4
{
	using namespace mcal::concepts;

	/**
	 * @brief Generic GPIO port implementation for STM32F4 series.
	 *
	 * This template provides low‑level access to a specific GPIO port by
	 * exposing clock control, pin mode configuration, and basic I/O
	 * operations. It is intended to be used as a backend for higher‑level
	 * abstractions such as GpioPin.
	 *
	 * @tparam GPIO_BASE              Base address of the GPIO peripheral.
	 * @tparam RCC_AHB1ENR_GPIOxEN    Bit mask enabling the GPIO clock in RCC->AHB1ENR.
	 */
	template <uint32_t GPIO_BASE, uint32_t RCC_AHB1ENR_GPIOxEN>
	struct GpioImpl
	{
	  private:
		/**
		 * @brief Get a typed pointer to the GPIO peripheral.
		 */
		static constexpr GPIO_TypeDef *gpio()
		{
			return reinterpret_cast<GPIO_TypeDef *>(GPIO_BASE);
		}

		/**
		 * @brief Get a typed pointer to the RCC peripheral.
		 */
		static constexpr RCC_TypeDef *rcc()
		{
			return reinterpret_cast<RCC_TypeDef *>(RCC_BASE);
		}

	  public:
		/**
		 * @brief Enable the clock for this GPIO port.
		 */
		static void enable()
		{
			rcc()->AHB1ENR |= RCC_AHB1ENR_GPIOxEN;
		}

		/**
		 * @brief Disable the clock for this GPIO port.
		 */
		static void disable()
		{
			rcc()->AHB1ENR &= ~RCC_AHB1ENR_GPIOxEN;
		}

		/**
		 * @brief Set the gpio mode
		 *
		 * @tparam pin
		 * @tparam M
		 */
		template <uint8_t pin, GpioPinMode M>
		static void setMode()
		{
			gpio()->MODER &= ~(0b11 << (pin * 2));
			if constexpr (M == GpioPinMode::Output)
			{
				gpio()->MODER |= (0b01 << (pin * 2));
			}
			else if constexpr (M == GpioPinMode::Input)
			{
				// nothing to to, its empty
			}
		}

		/**
		 * @brief Write high to pin
		 *
		 * Use the ODR register to set the pin high.
		 *
		 * @tparam pin
		 * @todo use BSRR register instead
		 */
		template <uint8_t pin>
		static void writeHigh()
		{
			static_assert(pin < 16, "GPIO pin index must be < 16");
			gpio()->ODR |= (1 << pin);
		}

		/**
		 * @brief Write low to pin
		 *
		 * Use the ODR register to set the pin high.
		 *
		 * @tparam pin
		 * @todo use BSRR register instead
		 */
		template <uint8_t pin>
		static void writeLow()
		{
			static_assert(pin < 16, "GPIO pin index must be < 16");
			gpio()->ODR &= ~(1 << pin);
		}

		/**
		 * @brief Read pin state
		 *
		 * @tparam pin
		 * @return true
		 * @return false
		 */
		template <uint8_t pin>
		static bool read()
		{
			static_assert(pin < 16, "GPIO pin index must be < 16");
			return gpio()->IDR & (1 << pin);
		}
	};

	/**
	 * @brief High‑level GPIO pin abstraction for STM32F4 series.
	 *
	 * This template binds a specific GPIO port and pin number into a type‑safe
	 * interface that provides initialization and basic I/O operations. It
	 * leverages the underlying GpioImpl to perform low‑level operations.
	 *
	 * @tparam Port   GPIO port type conforming to GpioPort concept.
	 * @tparam Pin    GPIO pin number (0‑15).
	 * @tparam Mode   GPIO pin mode (Input/Output).
	 */
	template <GpioPort Port, uint8_t Pin, GpioPinMode Mode = GpioPinMode::Input>
	struct GpioPin
	{
		/**
		 * @brief Initialize the GPIO pin.
		 *
		 */
		static_assert(Pin < 16, "GPIO pin index must be < 16");
		static void init()
		{
			Port::enable();
			Port::template setMode<Pin, Mode>();
		}

		/**
		 * @brief Set the GPIO pin high.
		 *
		 */
		static void set()
		{
			Port::template writeHigh<Pin>();
		}

		/**
		 * @brief Clear the GPIO pin low.
		 *
		 */
		static void clear()
		{
			Port::template writeLow<Pin>();
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
} // namespace stm32::f4
