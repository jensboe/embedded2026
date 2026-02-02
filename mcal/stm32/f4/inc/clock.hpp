/**
 * @file clock.hpp
 * @brief Implementation of the clock tree
 *
 */
#pragma once
#include "mcal.hpp"
#include "stm32f4xx.h"
namespace stm32::f4
{
	/**
	 * @brief Contains all relevant data for clock speed.
	 *
	 *
	 */
	template <uint32_t target_system_clock_hz, mcal::clock external_source = {0, mcal::clock::sources::clock}>
	struct clock_tree
	{
		static_assert(!(external_source.source != mcal::clock::sources::none && external_source.frequency_hz == 0),
					  "External clock source given, but frequency is 0");
		static_assert(target_system_clock_hz <= 180'000'000, "System clock must be lower than 180 MHz");
		static constexpr uint32_t HSI_frequency_hz = 16'000'000; //!< The internal HSI runs at 16 MHz

		static_assert((target_system_clock_hz >= 24'000'000) ||
						  external_source.frequency_hz == target_system_clock_hz ||
						  HSI_frequency_hz == target_system_clock_hz,

					  "If HSI or HSE doesn't match target frequency, the minimum target frequency must be 24MHz");
		/**
		 * @brief Possible sources for system clock
		 *
		 * Values are compatible with RM0390 section RCC clock configuration register SW
		 *
		 */
		enum class sources
		{
			HSI = 0b00,	  //!< HSI oscillator selected as system clock
			HSE = 0b01,	  //!< HSE oscillator selected as system clock
			PLL_P = 0b10, //!< PLL_P selected as system clock
			PLL_R = 0b11, //!< PLL_R selected as system clock
		};

		/**
		 * @brief 32 kHz low-speed internal RC (LSI RC) which drives the independent watchdog and, optionally, the RTC
		 * used for Auto-wakeup from the Stop/Standby mode.
		 *
		 */
		static constexpr uint32_t LSI_RC_frequency_hz = 32'000;

		/**
		 * @brief 32.768 kHz low-speed external crystal (LSE crystal), which optionally drives the RTC clock (RTCCLK)
		 *
		 */
		static constexpr uint32_t LSI_CRY_frequency_hz = 32'768;

		/**
		 * @brief Configured root source
		 *
		 * HSE or HSI depending on the settings.
		 * Not equal to sys clk source.
		 *
		 * @return constexpr sources
		 */
		static constexpr sources root_source()
		{
			if (external_source.source != mcal::clock::sources::none && external_source.frequency_hz > 0)
			{
				return sources::HSE;
			}
			else
			{
				return sources::HSI;
			}
		}

		/**
		 * @brief Configured root source frequency
		 *
		 * frequency of HSE or HSI depending on the settings.
		 * Not equal to sys clk freqency.
		 *
		 * @return constexpr uint32_t
		 */
		static constexpr uint32_t root_frequency_hz()
		{
			if (root_source() == sources::HSE)
			{
				return external_source.frequency_hz;
			}
			else
			{
				return HSI_frequency_hz;
			}
		}

		/**
		 * @brief Current source (read via register)
		 *
		 * @return sources
		 */
		static sources sysclock_source()
		{
			return static_cast<sources>((RCC->CFGR & RCC_CFGR_SWS_Msk) >> RCC_CFGR_SWS_Pos);
		}
		/**
		 * @brief Set the sysclock source register
		 *
		 * @param source
		 */
		static void set_sysclock_source(sources source)
		{
			RCC->CFGR |= ((static_cast<uint32_t>(source)) << RCC_CFGR_SW_Pos);
		}
		/**
		 * @brief PLL_P register access
		 *
		 */
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
				uint32_t M; //!< Dividor M allowed values: 2 .. 63
				uint32_t N; //!< Multiplyer N allowed values: 50 .. 432
				uint32_t P; //!< Dividor P allowed values:  2, 4, 6, 8
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
			static constexpr config calculate(uint32_t target, uint32_t source)
			{
				for (uint32_t M = 2; M <= 63; ++M)
				{
					auto const clk_m = source / M;
					if (clk_m > 2'000'000)
						continue;
					if (clk_m < 1'000'000)
						break;

					for (uint32_t N = 50; N <= 432; ++N)
					{
						auto const clk_n = clk_m * N;
						if (clk_n > 432'000'000 || clk_n < 100'000'000)
							continue;

						for (uint32_t P = 2; P <= 8; P += 2)
						{
							auto const clk_p = clk_n / P;
							if (clk_p == target)
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
			 * @param config
			 */
			static void set(const config &config)
			{
				uint32_t value = 0;
				value |= (config.M << RCC_PLLCFGR_PLLM_Pos) & RCC_PLLCFGR_PLLM_Msk;
				value |= (config.N << RCC_PLLCFGR_PLLN_Pos) & RCC_PLLCFGR_PLLN_Msk;
				value |= (((config.P / 2) - 1) << RCC_PLLCFGR_PLLP_Pos) & RCC_PLLCFGR_PLLP_Msk;
				RCC->PLLCFGR = value;
			}
			/**
			 * @brief Enables the PLL.
			 *
			 * Waits until PLL ready is set.
			 *
			 */
			static void enable()
			{
				RCC->CR |= RCC_CR_PLLON;
				do
				{
				} while (!is_ready());
			}
			/**
			 * @brief Disables the PLL.
			 *
			 */
			static void disable()
			{
				RCC->CR &= ~RCC_CR_PLLON;
			}
			/**
			 * @brief Configure the input source for the PLL
			 *
			 * Could be HSE or HSI
			 *
			 * @param source
			 */
			static constexpr void set_source(const sources source)
			{
				if (source == sources::HSE)
				{
					RCC->PLLCFGR |= RCC_PLLCFGR_PLLSRC;
				}
				else
				{
					RCC->PLLCFGR &= ~RCC_PLLCFGR_PLLSRC;
				}
			}
			/**
			 * @brief Checks if PLL is ready to use.
			 *
			 * @return true PLL is ready to use.
			 * @return false PLL is NOT ready to use.
			 */
			static bool is_ready()
			{
				return (RCC->CR & RCC_CR_PLLRDY);
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
			static void enable()
			{
				set_bypass();
				RCC->CR |= RCC_CR_HSEON;
				do
				{
				} while (!is_ready());
			}
			/**
			 * @brief Disables HSE.
			 *
			 */
			static void disable()
			{
				RCC->CR &= ~RCC_CR_HSEON;
			}
			/**
			 * @brief Configure the HSE Bypass in case an external clock is connected.
			 *
			 */
			static void set_bypass()
			{
				if (external_source.source == mcal::clock::sources::clock)
				{
					RCC->CR |= RCC_CR_HSEBYP;
				}
				else
				{
					RCC->CR &= ~RCC_CR_HSEBYP;
				}
			}
			/**
			 * @brief Checks if HSE is ready to use.
			 *
			 * @return true HSE is ready to use.
			 * @return false HSE is NOT ready to use.
			 */
			static bool is_ready()
			{
				return (RCC->CR & RCC_CR_HSERDY);
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
			static void enable()
			{
				RCC->CR |= RCC_CR_HSION;
				do
				{
				} while (!is_ready());
			}
			/**
			 * @brief Disables HSI.
			 *
			 */
			static void disable()
			{
				RCC->CR &= ~RCC_CR_HSION;
			}
			/**
			 * @brief Checks if HSI is ready to use.
			 *
			 * @return true HSI is ready to use.
			 * @return false HSI is NOT ready to use.
			 */
			static bool is_ready()
			{
				return (RCC->CR & RCC_CR_HSIRDY);
			}
		};

		/**
		 * @brief Initialise the clock tree
		 *
		 */
		static void init(void)
		{
			if constexpr (root_source() == sources::HSE)
			{
				HSE::enable();
				set_sysclock_source(sources::HSE);
				HSI::disable();
			}
			else
			{
				HSI::enable();
				set_sysclock_source(sources::HSI);
				HSE::disable();
			}
			if constexpr (root_frequency_hz() != target_system_clock_hz)
			{
				PLL_P::disable();
				constexpr auto config = PLL_P::calculate(target_system_clock_hz, root_frequency_hz());
				static_assert(config.M != 0, "Invalid PLL setting");
				PLL_P::set(config);
				PLL_P::set_source(root_source());
				PLL_P::enable();
				set_sysclock_source(sources::PLL_R);
			}
			else
			{
				PLL_P::disable();
			}
		}
	};

	/**
	 * @brief The System clock frequency
	 *
	 * Since no change is implemented the System Clock frequency is always 16 MHz.
	 *
	 */
	static constexpr uint32_t SystemClock_hz = 42;

} // namespace stm32::f4
