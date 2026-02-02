/**
 * @file mcal.hpp
 * @brief Main include file for mcal.
 */

#pragma once
#include "concepts/concepts.hpp"
/**
 * @brief Home of the Microcontroller Abstraction Layer.
 *
 */
namespace mcal
{
	/**
	 * @brief Common defintion of a clock source type
	 *
	 */
	struct clock
	{
		/**
		 * @brief Sources
		 *
		 */
		enum class sources
		{
			none = 0, //!< Dummy, not existing
			crystal,  //!< Crystal that need some internal resonator circuitry
			clock,	  //!< Something external provides a clear clock
		};
		uint32_t frequency_hz; //!< Frequency
		sources source;		   //!< Clock source
	};
} // namespace mcal

/**
 * @brief Register manipulation utilities.
 *
 */
struct Register
{
	/**
	 * @brief Set bits in a register.
	 *
	 * @param reg Register to be modified
	 * @param mask Bits to be set
	 */
	static inline void set(volatile uint32_t &reg, uint32_t mask)
	{
		reg |= mask;
	}

	/**
	 * @brief Clear bits in a register.
	 *
	 * @param reg Register to be modified
	 * @param mask Bits to be cleared
	 */
	static inline void clear(volatile uint32_t &reg, uint32_t mask)
	{
		reg &= ~mask;
	}

	/**
	 * @brief Write value to register with mask.
	 *
	 * Clears bits inside the mask and sets bits from value inside the mask.
	 * Example:
	 * Before : reg = 0b0000'1111
	 * Write<0b0000'1000, 0b0000'1100>(reg);
	 * After  : reg = 0b0000'1011
	 *
	 *
	 * @tparam value Value to be written
	 * @tparam mask Bits to be modified
	 * @param reg Register to be modified
	 */
	template <uint32_t value, uint32_t mask>
	static inline void write(volatile uint32_t &reg)
	{
		static_assert((value & ~mask) == 0, "Value contains bits outside of mask");
		reg = (reg & ~mask) | (value & mask);
	}

	/**
	 * @brief Read value from register with mask.
	 *
	 * @param reg Register to be modified
	 * @param mask Bits to be read (default: all bits)
	 * @return uint32_t
	 */
	static inline uint32_t read(const volatile uint32_t &reg, uint32_t mask = 0xFFFFFFFFu)
	{
		return reg & mask;
	}
};
