/**
 * @file clock.hpp
 * @brief STM32F4 clock tree configuration and control.
 */

#pragma once

#include <cstdint>

#include "mcal.hpp"
#include "stm32f4xx.h"

namespace stm32::f4
{
	/**
	 * @brief Clock tree configuration.
	 *
	 * @tparam target_system_clock Desired system clock frequency.
	 * @tparam external_source        Optional external clock source.
	 */
	template <utils::quantity::Hz_t target_system_clock,
			  mcal::clock external_source = {0 * utils::unit::Hz, mcal::clock::sources::clock}>
	struct clock_tree
	{
		static_assert(!(external_source.source != mcal::clock::sources::none &&
						external_source.frequency == 0 * utils::unit::Hz),
					  "External clock source specified but frequency is zero");

		static_assert(target_system_clock <= 180 * utils::unit::MHz, "STM32F4 system clock must not exceed 180 MHz");

		/**
		 * @brief Internal high-speed oscillator frequency.
		 *
		 */
		static constexpr utils::quantity::Hz_t HSI_frequency = 16 * utils::unit::MHz;

		/**
		 * @brief External high-speed oscillator frequency.
		 *
		 */
		static constexpr utils::quantity::Hz_t HSE_frequency = external_source.frequency;

		static_assert((target_system_clock >= 24 * utils::unit::MHz) || (HSE_frequency == target_system_clock) ||
						  (HSI_frequency == target_system_clock),
					  "If PLL is required, target frequency must be >= 24 MHz");

		/**
		 * @brief Get the system clock object
		 *
		 * @return std::uint32_t
		 */
		[[nodiscard]]
		static std::uint32_t get_system_clock() noexcept
		{
			return SystemCoreClock;
		}

		/**
		 * @brief Possible system clock sources (RM0390 compliant).
		 */
		enum class sources : std::uint32_t
		{
			HSI = 0b00,
			HSE = 0b01,
			PLL_P = 0b10,
			PLL_R = 0b11,
		};

		/**
		 * @brief Determine root clock source
		 *
		 * @return constexpr sources the root clock source
		 */
		static constexpr sources root_source() noexcept
		{
			return (external_source.source != mcal::clock::sources::none &&
					external_source.frequency > 0 * utils::unit::Hz)
					   ? sources::HSE
					   : sources::HSI;
		}

		/**
		 * @brief Configured root source frequency
		 *
		 * frequency of HSE or HSI depending on the settings.
		 * Not equal to sys clk freqency.
		 *
		 * @return constexpr uint32_t
		 */
		static constexpr utils::quantity::Hz_t root_frequency() noexcept
		{
			return (root_source() == sources::HSE) ? HSE_frequency : HSI_frequency;
		}

		/**
		 * @brief Current source (read via register)
		 *
		 * @return sources the current sysclock source
		 */
		static sources sysclock_source() noexcept
		{
			return static_cast<sources>((Register::read(RCC->CFGR, RCC_CFGR_SWS_Msk) >> RCC_CFGR_SWS_Pos));
		}
		/**
		 * @brief Set the sysclock source register
		 *
		 * @tparam source The clock source to be set
		 */
		template <sources source>
		static void set_sysclock_source() noexcept
		{
			Register::write<(static_cast<std::uint32_t>(source) << RCC_CFGR_SW_Pos), RCC_CFGR_SW_Msk>(RCC->CFGR);
		}

		/**
		 * @brief PLL configuration parameters.
		 *
		 * Represents the three core parameters of the STM32F4 main PLL.
		 * These values determine the VCO input frequency, VCO output
		 * frequency, and the final system clock output (PLL_P).
		 *
		 */
		struct config
		{
			uint32_t M; //!< Dividor M allowed values: 2 .. 63
			uint32_t N; //!< Multiplyer N allowed values: 50 .. 432
			uint32_t P; //!< Dividor P allowed values:  2, 4, 6, 8
		};
		struct PLL_P
		{
			/**
			 * @brief PLL configuration parameters.
			 *
			 * Represents the three core parameters of the STM32F4 main PLL.
			 * These values determine the VCO input frequency, VCO output
			 * frequency, and the final system clock output (PLL_P).
			 *
			 */
			struct config
			{
				std::uint32_t M; //!< 2 … 63
				std::uint32_t N; //!< 50 … 432
				std::uint32_t P; //!< {2,4,6,8}
			};

			/**
			 * @brief Computes a valid PLL configuration for a desired output frequency.
			 *
			 * This function performs a bounded search over all valid PLL parameter
			 * combinations (M, N, P) as defined by the STM32F4 PLL constraints.
			 * It attempts to find a configuration that produces the exact target
			 * output frequency on the PLL_P output.
			 *
			 * The search respects all limits from RM0390:
			 * - M: 2 … 63
			 * - N: 50 … 432
			 * - P: {2, 4, 6, 8}
			 * - clk_m  = source / M     1 ... 2 MHz
			 * - clk_n  = clk_m * N      100 ...432 MHz
			 * - clk_p  = clk_n / P      @p target exactly
			 *
			 * The algorithm iterates M → N → P in ascending order and returns the
			 * first valid configuration that satisfies all constraints.
			 *
			 * @param target  Desired clk_p output frequency in Hz (system clock target).
			 * @param source  Input clock frequency in Hz.
			 *
			 * @return A valid PLL configuration {M, N, P} if found.
			 *         Returns {0, 0, 0} if no valid configuration exists.
			 *
			 * @note This function is constexpr and can therefore be evaluated at
			 *       compile time, enabling full static validation of clock setups.
			 */
			static constexpr config calculate(utils::quantity::Hz_t target, utils::quantity::Hz_t source) noexcept
			{
				for (std::uint32_t M = 2; M <= 63; ++M)
				{
					const auto clk_m = source / M;
					if (clk_m > 2 * utils::unit::MHz)
						continue;
					if (clk_m < 1 * utils::unit::MHz)
						break;

					for (std::uint32_t N = 50; N <= 432; ++N)
					{
						const auto clk_n = clk_m * N;
						if (clk_n < 100 * utils::unit::MHz || clk_n > 432 * utils::unit::MHz)
							continue;

						for (std::uint32_t P = 2; P <= 8; P += 2)
						{
							if ((clk_n / P) == target)
							{
								return {M, N, P};
							}
						}
					}
				}
				return {0, 0, 0};
			}

			/**
			 * @brief Write the config into the PLLCFGR registers
			 *
			 * @tparam config
			 */
			template <config cfg>
			static void set() noexcept
			{
				constexpr std::uint32_t value = ((cfg.M << RCC_PLLCFGR_PLLM_Pos) & RCC_PLLCFGR_PLLM_Msk) |
												((cfg.N << RCC_PLLCFGR_PLLN_Pos) & RCC_PLLCFGR_PLLN_Msk) |
												((((cfg.P / 2) - 1) << RCC_PLLCFGR_PLLP_Pos) & RCC_PLLCFGR_PLLP_Msk);

				constexpr std::uint32_t mask = RCC_PLLCFGR_PLLM_Msk | RCC_PLLCFGR_PLLN_Msk | RCC_PLLCFGR_PLLP_Msk;

				Register::write<value, mask>(RCC->PLLCFGR);
			}

			/**
			 * @brief Enables the PLL.
			 *
			 * Waits until PLL ready is set.
			 *
			 */
			static void enable() noexcept
			{
				Register::set(RCC->CR, RCC_CR_PLLON);
				while (!is_ready())
				{
				}
			}

			/**
			 * @brief Disables the PLL.
			 *
			 */
			static void disable() noexcept
			{
				Register::clear(RCC->CR, RCC_CR_PLLON);
			}

			/**
			 * @brief Configure the input source for the PLL
			 *
			 * Could be HSE or HSI
			 *
			 * @param source
			 */
			static void set_source(sources source) noexcept
			{
				if (source == sources::HSE)
				{
					Register::set(RCC->PLLCFGR, RCC_PLLCFGR_PLLSRC);
				}
				else
				{
					Register::clear(RCC->PLLCFGR, RCC_PLLCFGR_PLLSRC);
				}
			}

			/**
			 * @brief Checks if PLL is ready to use.
			 *
			 * @return true PLL is ready to use.
			 * @return false PLL is NOT ready to use.
			 */
			[[nodiscard]]
			static bool is_ready() noexcept
			{
				return Register::read(RCC->CR, RCC_CR_PLLRDY);
			}
		};

		/**
		 * @brief HSE register access
		 *
		 */
		struct HSE
		{
			/**
			 * @brief Enables HSE. Set bypass option if needed
			 *
			 */
			static void enable() noexcept
			{
				set_bypass();
				Register::set(RCC->CR, RCC_CR_HSEON);
				while (!is_ready())
				{
				}
			}

			/**
			 * @brief Disables HSE.
			 *
			 */
			static void disable() noexcept
			{
				Register::clear(RCC->CR, RCC_CR_HSEON);
			}

			/**
			 * @brief Configure the HSE Bypass in case an external clock is connected.
			 *
			 */
			static void set_bypass() noexcept
			{
				if (external_source.source == mcal::clock::sources::clock)
				{
					Register::set(RCC->CR, RCC_CR_HSEBYP);
				}
				else
				{
					Register::clear(RCC->CR, RCC_CR_HSEBYP);
				}
			}

			/**
			 * @brief Checks if HSE is ready to use.
			 *
			 * @return true HSE is ready to use.
			 * @return false HSE is NOT ready to use.
			 */
			[[nodiscard]]
			static bool is_ready() noexcept
			{
				return Register::read(RCC->CR, RCC_CR_HSERDY);
			}
		};

		/**
		 * @brief HSI register access
		 *
		 */
		struct HSI
		{
			/**
			 * @brief Enables HSI.
			 *
			 */
			static void enable() noexcept
			{
				Register::set(RCC->CR, RCC_CR_HSION);
				while (!is_ready())
				{
				}
			}
			/**
			 * @brief Disables HSI.
			 *
			 */
			static void disable() noexcept
			{
				Register::clear(RCC->CR, RCC_CR_HSION);
			}
			/**
			 * @brief Checks if HSI is ready to use.
			 *
			 * @return true HSI is ready to use.
			 * @return false HSI is NOT ready to use.
			 */
			[[nodiscard]]
			static bool is_ready() noexcept
			{
				return Register::read(RCC->CR, RCC_CR_HSIRDY);
			}
		};

		/**
		 * @brief Initialise the clock tree
		 *
		 */
		static void init() noexcept
		{
			if constexpr (root_source() == sources::HSE)
			{
				HSE::enable();
				set_sysclock_source<sources::HSE>();
				HSI::disable();
			}
			else
			{
				HSI::enable();
				set_sysclock_source<sources::HSI>();
				HSE::disable();
			}

			if constexpr (root_frequency() != target_system_clock)
			{
				PLL_P::disable();

				constexpr auto cfg = PLL_P::calculate(target_system_clock, root_frequency());

				static_assert(cfg.M != 0, "No valid PLL configuration found");

				PLL_P::template set<cfg>();
				PLL_P::set_source(root_source());
				PLL_P::enable();

				set_sysclock_source<sources::PLL_P>();
			}
			else
			{
				PLL_P::disable();
			}

			SystemCoreClockUpdate();
		}
	};

} // namespace stm32::f4
