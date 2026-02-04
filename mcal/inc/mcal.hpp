/**
 * @file mcal.hpp
 * @brief Main include file for the Microcontroller Abstraction Layer (MCAL).
 */

#pragma once

#include <cstdint>

#include "concepts/concepts.hpp"
#include "units.hpp"

namespace mcal
{
	/**
	 * @brief Common definition of a clock source.
	 */
	struct clock
	{
		/**
		 * @brief Available clock sources.
		 */
		enum class sources : std::uint8_t
		{
			none = 0, //!< Dummy / not present
			crystal,  //!< External crystal with resonator circuitry
			clock,	  //!< External clock source
		};

		utils::quantity::Hz_t frequency{}; //!< Clock frequency
		sources source{sources::none};	   //!< Clock source
	};

} // namespace mcal

/**
 * @brief Register manipulation utilities.
 *
 * Stateless helper functions for safe and expressive
 * bit-level register access.
 */
struct Register
{
	/**
	 * @brief Set bits in a register.
	 *
	 * @param reg  Register to be modified
	 * @param mask Bits to be set
	 */
	static inline void set(volatile std::uint32_t &reg, std::uint32_t mask) noexcept
	{
		reg |= mask;
	}

	/**
	 * @brief Clear bits in a register.
	 *
	 * @param reg  Register to be modified
	 * @param mask Bits to be cleared
	 */
	static inline void clear(volatile std::uint32_t &reg, std::uint32_t mask) noexcept
	{
		reg &= ~mask;
	}

	/**
	 * @brief Write masked value to a register.
	 *
	 * Clears all bits selected by @p mask and then writes
	 * the corresponding bits from @p value.
	 *
	 * Example:
	 * @code
	 * reg = 0b0000'1111;
	 * Register::write<0b0000'1000, 0b0000'1100>(reg);
	 * // reg == 0b0000'1011
	 * @endcode
	 *
	 * @tparam value Value to be written
	 * @tparam mask  Bit mask defining affected bits
	 * @param reg    Register to be modified
	 */
	template <std::uint32_t value, std::uint32_t mask>
	static inline void write(volatile std::uint32_t &reg) noexcept
	{
		static_assert((value & ~mask) == 0u, "value contains bits outside of mask");

		reg = (reg & ~mask) | (value & mask);
	}

	/**
	 * @brief Read masked value from a register.
	 *
	 * @param reg  Register to be read
	 * @param mask Bit mask defining bits of interest
	 * @return Masked register value
	 */
	[[nodiscard]]
	static inline std::uint32_t read(const volatile std::uint32_t &reg, std::uint32_t mask = 0xFFFF'FFFFu) noexcept
	{
		return reg & mask;
	}
};
