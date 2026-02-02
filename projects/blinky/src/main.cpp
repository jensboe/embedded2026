/**
 * @file main.cpp
 * @brief  Simple blinky application for Nucleo-F446ZE using GPIO and DWT delay.

 *
 */

#include "bsp.h"
#include <cstdio>
using namespace stm32::f4;
/**
 * @brief Use the Nucleo F446ZE board with 100 MHz system clock
 *
 */
using board = bsp::nucleo_f446ze<100'000'000>;
/**
 * @brief Main entry point for the blinky application.
 *
 * @return int
 */
int main(void)
{

	RCC->APB1ENR |= RCC_APB1ENR_PWREN;
	PWR->CR |= PWR_CR_VOS_0;
	FLASH->ACR |= FLASH_ACR_DCEN;
	FLASH->ACR |= FLASH_ACR_ICRST;
	FLASH->ACR |= FLASH_ACR_DCEN;
	FLASH->ACR |= FLASH_ACR_ICEN;
	FLASH->ACR |= FLASH_ACR_PRFTEN;
	FLASH->ACR |= (4 & FLASH_ACR_LATENCY_Msk);
	board::init();

	uint32_t loop_counter = 0;
	printf("HSI:    %9lu Hz\n", board::clock::HSI_frequency_hz);
	printf("HSE:    %9lu Hz\n", board::clock::HSE_frequency_hz);
	printf("HSE:    %9d Hz\n", HSE_VALUE);
	printf("root:   %9lu Hz\n", board::clock::root_frequency_hz());
	printf("SysClk: %9lu Hz\n", board::clock::get_system_clock());

	while (1)
	{
		printf("Delay count: %lu\n", ++loop_counter);
		board::LD_Green::set();
		board::LD_Red::set();
		board::Delay::ms(500);
		board::LD_Green::clear();
		board::LD_Red::clear();
		board::Delay::ms(500);
		if (board::B1::read())
		{
			board::LD_Blue::set();
		}
		else
		{
			board::LD_Blue::clear();
		}
	}

	return 0;
}
