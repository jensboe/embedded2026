/**
 ******************************************************************************
 * @file      startup_stm32f446xx.cpp
 * @author    MCD Application Team (converted to C++)
 * @brief     STM32F446xx Devices vector table for GCC based toolchains.
 *            This module performs:
 *                - Set the initial SP
 *                - Set the initial PC == Reset_Handler,
 *                - Set the vector table entries with the exceptions ISR address
 *                - Branches to main in the C library (which eventually
 *                  calls main()).
 *            After Reset the Cortex-M4 processor is in Thread mode,
 *            priority is Privileged, and the Stack is set to Main.
 ******************************************************************************
 * @attention
 *
 * Copyright (c) 2017 STMicroelectronics.
 * All rights reserved.
 *
 * This software is licensed under terms that can be found in the LICENSE file
 * in the root directory of this software component.
 * If no LICENSE file comes with this software, it is provided AS-IS.
 *
 ******************************************************************************
 */

#include <cstdint>

/**
 * Linker script symbols
 */
extern uint32_t _estack; /* End of SRAM */
extern uint32_t _sdata;	 /* Start of .data section */
extern uint32_t _edata;	 /* End of .data section */
extern uint32_t _sidata; /* Start of .data section in FLASH */
extern uint32_t _sbss;	 /* Start of .bss section */
extern uint32_t _ebss;	 /* End of .bss section */

/* Function declarations */
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wpedantic"
extern int main(void);
#pragma GCC diagnostic pop

extern "C"
{
	extern void SystemInit(void);
	extern void __libc_init_array(void);

	/**
	 * Exception Handler declarations with weak linkage
	 */

	/* Cortex M4 System Exceptions */
	void Reset_Handler(void) __attribute__((used));

	void Default_Handler(void);
	// Cortex-M Core Handlers
	void NMI_Handler(void) __attribute__((weak, alias("Default_Handler")));
	void HardFault_Handler(void) __attribute__((weak, alias("Default_Handler")));
	void MemManage_Handler(void) __attribute__((weak, alias("Default_Handler")));
	void BusFault_Handler(void) __attribute__((weak, alias("Default_Handler")));
	void UsageFault_Handler(void) __attribute__((weak, alias("Default_Handler")));
	void SVC_Handler(void) __attribute__((weak, alias("Default_Handler")));
	void DebugMon_Handler(void) __attribute__((weak, alias("Default_Handler")));
	void PendSV_Handler(void) __attribute__((weak, alias("Default_Handler")));
	void SysTick_Handler(void) __attribute__((weak, alias("Default_Handler")));

	// External Interrupts
	void WWDG_IRQHandler(void) __attribute__((weak, alias("Default_Handler")));
	void PVD_IRQHandler(void) __attribute__((weak, alias("Default_Handler")));
	void TAMP_STAMP_IRQHandler(void) __attribute__((weak, alias("Default_Handler")));
	void RTC_WKUP_IRQHandler(void) __attribute__((weak, alias("Default_Handler")));
	void FLASH_IRQHandler(void) __attribute__((weak, alias("Default_Handler")));
	void RCC_IRQHandler(void) __attribute__((weak, alias("Default_Handler")));
	void EXTI0_IRQHandler(void) __attribute__((weak, alias("Default_Handler")));
	void EXTI1_IRQHandler(void) __attribute__((weak, alias("Default_Handler")));
	void EXTI2_IRQHandler(void) __attribute__((weak, alias("Default_Handler")));
	void EXTI3_IRQHandler(void) __attribute__((weak, alias("Default_Handler")));
	void EXTI4_IRQHandler(void) __attribute__((weak, alias("Default_Handler")));
	void DMA1_Stream0_IRQHandler(void) __attribute__((weak, alias("Default_Handler")));
	void DMA1_Stream1_IRQHandler(void) __attribute__((weak, alias("Default_Handler")));
	void DMA1_Stream2_IRQHandler(void) __attribute__((weak, alias("Default_Handler")));
	void DMA1_Stream3_IRQHandler(void) __attribute__((weak, alias("Default_Handler")));
	void DMA1_Stream4_IRQHandler(void) __attribute__((weak, alias("Default_Handler")));
	void DMA1_Stream5_IRQHandler(void) __attribute__((weak, alias("Default_Handler")));
	void DMA1_Stream6_IRQHandler(void) __attribute__((weak, alias("Default_Handler")));
	void ADC_IRQHandler(void) __attribute__((weak, alias("Default_Handler")));
	void CAN1_TX_IRQHandler(void) __attribute__((weak, alias("Default_Handler")));
	void CAN1_RX0_IRQHandler(void) __attribute__((weak, alias("Default_Handler")));
	void CAN1_RX1_IRQHandler(void) __attribute__((weak, alias("Default_Handler")));
	void CAN1_SCE_IRQHandler(void) __attribute__((weak, alias("Default_Handler")));
	void EXTI9_5_IRQHandler(void) __attribute__((weak, alias("Default_Handler")));
	void TIM1_BRK_TIM9_IRQHandler(void) __attribute__((weak, alias("Default_Handler")));
	void TIM1_UP_TIM10_IRQHandler(void) __attribute__((weak, alias("Default_Handler")));
	void TIM1_TRG_COM_TIM11_IRQHandler(void) __attribute__((weak, alias("Default_Handler")));
	void TIM1_CC_IRQHandler(void) __attribute__((weak, alias("Default_Handler")));
	void TIM2_IRQHandler(void) __attribute__((weak, alias("Default_Handler")));
	void TIM3_IRQHandler(void) __attribute__((weak, alias("Default_Handler")));
	void TIM4_IRQHandler(void) __attribute__((weak, alias("Default_Handler")));
	void I2C1_EV_IRQHandler(void) __attribute__((weak, alias("Default_Handler")));
	void I2C1_ER_IRQHandler(void) __attribute__((weak, alias("Default_Handler")));
	void I2C2_EV_IRQHandler(void) __attribute__((weak, alias("Default_Handler")));
	void I2C2_ER_IRQHandler(void) __attribute__((weak, alias("Default_Handler")));
	void SPI1_IRQHandler(void) __attribute__((weak, alias("Default_Handler")));
	void SPI2_IRQHandler(void) __attribute__((weak, alias("Default_Handler")));
	void USART1_IRQHandler(void) __attribute__((weak, alias("Default_Handler")));
	void USART2_IRQHandler(void) __attribute__((weak, alias("Default_Handler")));
	void USART3_IRQHandler(void) __attribute__((weak, alias("Default_Handler")));
	void EXTI15_10_IRQHandler(void) __attribute__((weak, alias("Default_Handler")));
	void RTC_Alarm_IRQHandler(void) __attribute__((weak, alias("Default_Handler")));
	void OTG_FS_WKUP_IRQHandler(void) __attribute__((weak, alias("Default_Handler")));
	void TIM8_BRK_TIM12_IRQHandler(void) __attribute__((weak, alias("Default_Handler")));
	void TIM8_UP_TIM13_IRQHandler(void) __attribute__((weak, alias("Default_Handler")));
	void TIM8_TRG_COM_TIM14_IRQHandler(void) __attribute__((weak, alias("Default_Handler")));
	void TIM8_CC_IRQHandler(void) __attribute__((weak, alias("Default_Handler")));
	void DMA1_Stream7_IRQHandler(void) __attribute__((weak, alias("Default_Handler")));
	void FMC_IRQHandler(void) __attribute__((weak, alias("Default_Handler")));
	void SDIO_IRQHandler(void) __attribute__((weak, alias("Default_Handler")));
	void TIM5_IRQHandler(void) __attribute__((weak, alias("Default_Handler")));
	void SPI3_IRQHandler(void) __attribute__((weak, alias("Default_Handler")));
	void UART4_IRQHandler(void) __attribute__((weak, alias("Default_Handler")));
	void UART5_IRQHandler(void) __attribute__((weak, alias("Default_Handler")));
	void TIM6_DAC_IRQHandler(void) __attribute__((weak, alias("Default_Handler")));
	void TIM7_IRQHandler(void) __attribute__((weak, alias("Default_Handler")));
	void DMA2_Stream0_IRQHandler(void) __attribute__((weak, alias("Default_Handler")));
	void DMA2_Stream1_IRQHandler(void) __attribute__((weak, alias("Default_Handler")));
	void DMA2_Stream2_IRQHandler(void) __attribute__((weak, alias("Default_Handler")));
	void DMA2_Stream3_IRQHandler(void) __attribute__((weak, alias("Default_Handler")));
	void DMA2_Stream4_IRQHandler(void) __attribute__((weak, alias("Default_Handler")));
	void CAN2_TX_IRQHandler(void) __attribute__((weak, alias("Default_Handler")));
	void CAN2_RX0_IRQHandler(void) __attribute__((weak, alias("Default_Handler")));
	void CAN2_RX1_IRQHandler(void) __attribute__((weak, alias("Default_Handler")));
	void CAN2_SCE_IRQHandler(void) __attribute__((weak, alias("Default_Handler")));
	void OTG_FS_IRQHandler(void) __attribute__((weak, alias("Default_Handler")));
	void DMA2_Stream5_IRQHandler(void) __attribute__((weak, alias("Default_Handler")));
	void DMA2_Stream6_IRQHandler(void) __attribute__((weak, alias("Default_Handler")));
	void DMA2_Stream7_IRQHandler(void) __attribute__((weak, alias("Default_Handler")));
	void USART6_IRQHandler(void) __attribute__((weak, alias("Default_Handler")));
	void I2C3_EV_IRQHandler(void) __attribute__((weak, alias("Default_Handler")));
	void I2C3_ER_IRQHandler(void) __attribute__((weak, alias("Default_Handler")));
	void OTG_HS_EP1_OUT_IRQHandler(void) __attribute__((weak, alias("Default_Handler")));
	void OTG_HS_EP1_IN_IRQHandler(void) __attribute__((weak, alias("Default_Handler")));
	void OTG_HS_WKUP_IRQHandler(void) __attribute__((weak, alias("Default_Handler")));
	void OTG_HS_IRQHandler(void) __attribute__((weak, alias("Default_Handler")));
	void DCMI_IRQHandler(void) __attribute__((weak, alias("Default_Handler")));
	void FPU_IRQHandler(void) __attribute__((weak, alias("Default_Handler")));
	void SPI4_IRQHandler(void) __attribute__((weak, alias("Default_Handler")));
	void SAI1_IRQHandler(void) __attribute__((weak, alias("Default_Handler")));
	void SAI2_IRQHandler(void) __attribute__((weak, alias("Default_Handler")));
	void QUADSPI_IRQHandler(void) __attribute__((weak, alias("Default_Handler")));
	void CEC_IRQHandler(void) __attribute__((weak, alias("Default_Handler")));
	void SPDIF_RX_IRQHandler(void) __attribute__((weak, alias("Default_Handler")));
	void FMPI2C1_EV_IRQHandler(void) __attribute__((weak, alias("Default_Handler")));
	void FMPI2C1_ER_IRQHandler(void) __attribute__((weak, alias("Default_Handler")));

	/**
	 * Vector Table Definition
	 */
	typedef void (*pFunc)(void);

	/* Vector table */
	__attribute__((section(".isr_vector"), used)) const pFunc g_pfnVectors[139] = {
		/* Cortex-M4 exceptions */
		(pFunc)&_estack,	/*      0: End of Stack */
		Reset_Handler,		/*      1: Reset Handler */
		NMI_Handler,		/*      2: NMI Handler */
		HardFault_Handler,	/*      3: Hard Fault Handler */
		MemManage_Handler,	/*      4: Memory Management Fault Handler */
		BusFault_Handler,	/*      5: Bus Fault Handler */
		UsageFault_Handler, /*      6: Usage Fault Handler */
		nullptr,			/*      7: Reserved */
		nullptr,			/*      8: Reserved */
		nullptr,			/*      9: Reserved */
		nullptr,			/*     10: Reserved */
		SVC_Handler,		/*     11: SVC Handler (FreeRTOS) */
		DebugMon_Handler,	/*     12: Debug Monitor Handler */
		nullptr,			/*     13: Reserved */
		PendSV_Handler,		/*     14: PendSV Handler (FreeRTOS) */
		SysTick_Handler,	/*     15: SysTick Handler (FreeRTOS) */

		/* External interrupts */
		WWDG_IRQHandler,			   /*     16: Window WatchDog */
		PVD_IRQHandler,				   /*     17: PVD through EXTI Line detection */
		TAMP_STAMP_IRQHandler,		   /*     18: Tamper and TimeStamps through the EXTI line */
		RTC_WKUP_IRQHandler,		   /*     19: RTC Wakeup through the EXTI line */
		FLASH_IRQHandler,			   /*     20: FLASH */
		RCC_IRQHandler,				   /*     21: RCC */
		EXTI0_IRQHandler,			   /*     22: EXTI Line0 */
		EXTI1_IRQHandler,			   /*     23: EXTI Line1 */
		EXTI2_IRQHandler,			   /*     24: EXTI Line2 */
		EXTI3_IRQHandler,			   /*     25: EXTI Line3 */
		EXTI4_IRQHandler,			   /*     26: EXTI Line4 */
		DMA1_Stream0_IRQHandler,	   /*     27: DMA1 Stream 0 */
		DMA1_Stream1_IRQHandler,	   /*     28: DMA1 Stream 1 */
		DMA1_Stream2_IRQHandler,	   /*     29: DMA1 Stream 2 */
		DMA1_Stream3_IRQHandler,	   /*     30: DMA1 Stream 3 */
		DMA1_Stream4_IRQHandler,	   /*     31: DMA1 Stream 4 */
		DMA1_Stream5_IRQHandler,	   /*     32: DMA1 Stream 5 */
		DMA1_Stream6_IRQHandler,	   /*     33: DMA1 Stream 6 */
		ADC_IRQHandler,				   /*     34: ADC1, ADC2 and ADC3s */
		CAN1_TX_IRQHandler,			   /*     35: CAN1 TX */
		CAN1_RX0_IRQHandler,		   /*     36: CAN1 RX0 */
		CAN1_RX1_IRQHandler,		   /*     37: CAN1 RX1 */
		CAN1_SCE_IRQHandler,		   /*     38: CAN1 SCE */
		EXTI9_5_IRQHandler,			   /*     39: External Line[9:5]s */
		TIM1_BRK_TIM9_IRQHandler,	   /*     40: TIM1 Break and TIM9 */
		TIM1_UP_TIM10_IRQHandler,	   /*     41: TIM1 Update and TIM10 */
		TIM1_TRG_COM_TIM11_IRQHandler, /*     42: TIM1 Trigger and Commutation and TIM11 */
		TIM1_CC_IRQHandler,			   /*     43: TIM1 Capture Compare */
		TIM2_IRQHandler,			   /*     44: TIM2 */
		TIM3_IRQHandler,			   /*     45: TIM3 */
		TIM4_IRQHandler,			   /*     46: TIM4 */
		I2C1_EV_IRQHandler,			   /*     47: I2C1 Event */
		I2C1_ER_IRQHandler,			   /*     48: I2C1 Error */
		I2C2_EV_IRQHandler,			   /*     49: I2C2 Event */
		I2C2_ER_IRQHandler,			   /*     50: I2C2 Error */
		SPI1_IRQHandler,			   /*     51: SPI1 */
		SPI2_IRQHandler,			   /*     52: SPI2 */
		USART1_IRQHandler,			   /*     53: USART1 */
		USART2_IRQHandler,			   /*     54: USART2 */
		USART3_IRQHandler,			   /*     55: USART3 */
		EXTI15_10_IRQHandler,		   /*     56: External Line[15:10]s */
		RTC_Alarm_IRQHandler,		   /*     57: RTC Alarm (A and B) through EXTI Line */
		OTG_FS_WKUP_IRQHandler,		   /*     58: USB OTG FS Wakeup through EXTI line */
		TIM8_BRK_TIM12_IRQHandler,	   /*     59: TIM8 Break and TIM12 */
		TIM8_UP_TIM13_IRQHandler,	   /*     60: TIM8 Update and TIM13 */
		TIM8_TRG_COM_TIM14_IRQHandler, /*     61: TIM8 Trigger and Commutation and TIM14 */
		TIM8_CC_IRQHandler,			   /*     62: TIM8 Capture Compare */
		DMA1_Stream7_IRQHandler,	   /*     63: DMA1 Stream7 */
		FMC_IRQHandler,				   /*     64: FMC */
		SDIO_IRQHandler,			   /*     65: SDIO */
		TIM5_IRQHandler,			   /*     66: TIM5 */
		SPI3_IRQHandler,			   /*     67: SPI3 */
		UART4_IRQHandler,			   /*     68: UART4 */
		UART5_IRQHandler,			   /*     69: UART5 */
		TIM6_DAC_IRQHandler,		   /*     70: TIM6 and DAC1&2 underrun errors */
		TIM7_IRQHandler,			   /*     71: TIM7 */
		DMA2_Stream0_IRQHandler,	   /*     72: DMA2 Stream 0 */
		DMA2_Stream1_IRQHandler,	   /*     73: DMA2 Stream 1 */
		DMA2_Stream2_IRQHandler,	   /*     74: DMA2 Stream 2 */
		DMA2_Stream3_IRQHandler,	   /*     75: DMA2 Stream 3 */
		DMA2_Stream4_IRQHandler,	   /*     76: DMA2 Stream 4 */
		nullptr,					   /*     77: Reserved */
		nullptr,					   /*     78: Reserved */
		CAN2_TX_IRQHandler,			   /*     79: CAN2 TX */
		CAN2_RX0_IRQHandler,		   /*     80: CAN2 RX0 */
		CAN2_RX1_IRQHandler,		   /*     81: CAN2 RX1 */
		CAN2_SCE_IRQHandler,		   /*     82: CAN2 SCE */
		OTG_FS_IRQHandler,			   /*     83: USB OTG FS */
		DMA2_Stream5_IRQHandler,	   /*     84: DMA2 Stream 5 */
		DMA2_Stream6_IRQHandler,	   /*     85: DMA2 Stream 6 */
		DMA2_Stream7_IRQHandler,	   /*     86: DMA2 Stream 7 */
		USART6_IRQHandler,			   /*     87: USART6 */
		I2C3_EV_IRQHandler,			   /*     88: I2C3 event */
		I2C3_ER_IRQHandler,			   /*     89: I2C3 error */
		OTG_HS_EP1_OUT_IRQHandler,	   /*     90: USB OTG HS End Point 1 Out */
		OTG_HS_EP1_IN_IRQHandler,	   /*     91: USB OTG HS End Point 1 In */
		OTG_HS_WKUP_IRQHandler,		   /*     92: USB OTG HS Wakeup through EXTI */
		OTG_HS_IRQHandler,			   /*     93: USB OTG HS */
		DCMI_IRQHandler,			   /*     94: DCMI */
		nullptr,					   /*     95: Reserved */
		nullptr,					   /*     96: Reserved */
		FPU_IRQHandler,				   /*     97: FPU */
		nullptr,					   /*     98: Reserved */
		nullptr,					   /*     99: Reserved */
		SPI4_IRQHandler,			   /*    100: SPI4 */
		nullptr,					   /*    101: Reserved */
		nullptr,					   /*    102: Reserved */
		SAI1_IRQHandler,			   /*    103: SAI1 */
		nullptr,					   /*    104: Reserved */
		nullptr,					   /*    105: Reserved */
		nullptr,					   /*    106: Reserved */
		SAI2_IRQHandler,			   /*    107: SAI2 */
		QUADSPI_IRQHandler,			   /*    108: QuadSPI */
		CEC_IRQHandler,				   /*    109: CEC */
		SPDIF_RX_IRQHandler,		   /*    110: SPDIF RX */
		FMPI2C1_EV_IRQHandler,		   /*    111: FMPI2C 1 Event */
		FMPI2C1_ER_IRQHandler,		   /*    112: FMPI2C 1 Error */
	};
	void Default_Handler(void)
	{

		while (true)
		{
		}
	}
	/**
	 * @brief  This is the code that gets called when the processor first
	 *          starts execution following a reset event. Only the absolutely
	 *          necessary set is performed, after which the application
	 *          supplied main() routine is called.
	 * @param  None
	 * @retval : None
	 */
	void Reset_Handler(void)
	{
		/* Copy the data segment initializers from flash to SRAM */
		uint8_t *src = reinterpret_cast<uint8_t *>(&_sidata);
		uint8_t *dst = reinterpret_cast<uint8_t *>(&_sdata);
		uint8_t *dst_end = reinterpret_cast<uint8_t *>(&_edata);

		while (dst < dst_end)
		{
			*dst++ = *src++;
		}

		/* Zero fill the bss segment */
		dst = reinterpret_cast<uint8_t *>(&_sbss);
		dst_end = reinterpret_cast<uint8_t *>(&_ebss);

		while (dst < dst_end)
		{
			*dst++ = 0;
		}

		/* Call the clock system initialization function */
		SystemInit();

		/* Call static constructors */
		__libc_init_array();

/* Call the application's entry point */
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wpedantic"
		main();
#pragma GCC diagnostic pop

		/* Hang in infinite loop */
		while (1)
			;
	}
} /* extern "C" */
