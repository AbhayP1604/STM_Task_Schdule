#include <stdint.h>

#define SRAM_RAM_START    0x20000000U
#define SRAM_SIZE 		  (128 * 1024)         //128kbyte of sram = 128 * 1024 of addressable space/physical memory  
#define SRAM_RAM_END	  ((SRAM_RAM_START) + (SRAM_SIZE) )	// points to sram end

#define STACK_START 	   SRAM_RAM_END
// system exceptions
void Reset_Handler(void);
void NMI_Handler(void)                  __attribute__ ((weak, alias("Default_Handler")));
void HardFault_Handler(void)            __attribute__ ((weak, alias("Default_Handler")));
void MemManage_Handler(void)            __attribute__ ((weak, alias("Default_Handler")));
void BusFault_Handler(void)             __attribute__ ((weak, alias("Default_Handler")));
void UsageFault_Handler(void)           __attribute__ ((weak, alias("Default_Handler")));
void SVC_Handler(void)                  __attribute__ ((weak, alias("Default_Handler")));
void DebugMon_Handler(void)             __attribute__ ((weak, alias("Default_Handler")));
void PendSV_Handler(void)               __attribute__ ((weak, alias("Default_Handler")));
void SysTick_Handler(void)              __attribute__ ((weak, alias("Default_Handler")));

// External Interrupts
void WWDG_IRQHandler(void)              __attribute__ ((weak, alias("Default_Handler")));
void PVD_IRQHandler(void)               __attribute__ ((weak, alias("Default_Handler")));
void TAMP_STAMP_IRQHandler(void)        __attribute__ ((weak, alias("Default_Handler")));
void RTC_WKUP_IRQHandler(void)          __attribute__ ((weak, alias("Default_Handler")));
void FLASH_IRQHandler(void)             __attribute__ ((weak, alias("Default_Handler")));
void RCC_IRQHandler(void)               __attribute__ ((weak, alias("Default_Handler")));
void EXTI0_IRQHandler(void)             __attribute__ ((weak, alias("Default_Handler")));
void EXTI1_IRQHandler(void)             __attribute__ ((weak, alias("Default_Handler")));
void EXTI2_IRQHandler(void)             __attribute__ ((weak, alias("Default_Handler")));
void EXTI3_IRQHandler(void)             __attribute__ ((weak, alias("Default_Handler")));
void EXTI4_IRQHandler(void)             __attribute__ ((weak, alias("Default_Handler")));
void DMA1_Stream0_IRQHandler(void)      __attribute__ ((weak, alias("Default_Handler")));
void DMA1_Stream1_IRQHandler(void)      __attribute__ ((weak, alias("Default_Handler")));
void DMA1_Stream2_IRQHandler(void)      __attribute__ ((weak, alias("Default_Handler")));
void DMA1_Stream3_IRQHandler(void)      __attribute__ ((weak, alias("Default_Handler")));
void DMA1_Stream4_IRQHandler(void)      __attribute__ ((weak, alias("Default_Handler")));
void DMA1_Stream5_IRQHandler(void)      __attribute__ ((weak, alias("Default_Handler")));
void DMA1_Stream6_IRQHandler(void)      __attribute__ ((weak, alias("Default_Handler")));
void ADC_IRQHandler(void)               __attribute__ ((weak, alias("Default_Handler")));
void CAN1_TX_IRQHandler(void)           __attribute__ ((weak, alias("Default_Handler")));
void CAN1_RX0_IRQHandler(void)          __attribute__ ((weak, alias("Default_Handler")));
void CAN1_RX1_IRQHandler(void)          __attribute__ ((weak, alias("Default_Handler")));
void CAN1_SCE_IRQHandler(void)          __attribute__ ((weak, alias("Default_Handler")));
void EXTI9_5_IRQHandler(void)           __attribute__ ((weak, alias("Default_Handler")));
void TIM1_BRK_TIM9_IRQHandler(void)     __attribute__ ((weak, alias("Default_Handler")));
void TIM1_UP_TIM10_IRQHandler(void)     __attribute__ ((weak, alias("Default_Handler")));
void TIM1_TRG_COM_TIM11_IRQHandler(void)__attribute__ ((weak, alias("Default_Handler")));
void TIM1_CC_IRQHandler(void)           __attribute__ ((weak, alias("Default_Handler")));
void TIM2_IRQHandler(void)              __attribute__ ((weak, alias("Default_Handler")));
void TIM3_IRQHandler(void)              __attribute__ ((weak, alias("Default_Handler")));
void TIM4_IRQHandler(void)              __attribute__ ((weak, alias("Default_Handler")));
void I2C1_EV_IRQHandler(void)           __attribute__ ((weak, alias("Default_Handler")));
void I2C1_ER_IRQHandler(void)           __attribute__ ((weak, alias("Default_Handler")));
void I2C2_EV_IRQHandler(void)           __attribute__ ((weak, alias("Default_Handler")));
void I2C2_ER_IRQHandler(void)           __attribute__ ((weak, alias("Default_Handler")));
void SPI1_IRQHandler(void)              __attribute__ ((weak, alias("Default_Handler")));
void SPI2_IRQHandler(void)              __attribute__ ((weak, alias("Default_Handler")));
void USART1_IRQHandler(void)            __attribute__ ((weak, alias("Default_Handler")));
void USART2_IRQHandler(void)            __attribute__ ((weak, alias("Default_Handler")));
void USART3_IRQHandler(void)            __attribute__ ((weak, alias("Default_Handler")));
void EXTI15_10_IRQHandler(void)         __attribute__ ((weak, alias("Default_Handler")));
void RTC_Alarm_IRQHandler(void)         __attribute__ ((weak, alias("Default_Handler")));
void OTG_FS_WKUP_IRQHandler(void)       __attribute__ ((weak, alias("Default_Handler")));
void TIM8_BRK_TIM12_IRQHandler(void)    __attribute__ ((weak, alias("Default_Handler")));
void TIM8_UP_TIM13_IRQHandler(void)     __attribute__ ((weak, alias("Default_Handler")));
void TIM8_TRG_COM_TIM14_IRQHandler(void)__attribute__ ((weak, alias("Default_Handler")));
void TIM8_CC_IRQHandler(void)           __attribute__ ((weak, alias("Default_Handler")));
void DMA1_Stream7_IRQHandler(void)      __attribute__ ((weak, alias("Default_Handler")));
void FMC_IRQHandler(void)               __attribute__ ((weak, alias("Default_Handler")));
void SDIO_IRQHandler(void)              __attribute__ ((weak, alias("Default_Handler")));
void TIM5_IRQHandler(void)              __attribute__ ((weak, alias("Default_Handler")));
void SPI3_IRQHandler(void)              __attribute__ ((weak, alias("Default_Handler")));
void UART4_IRQHandler(void)             __attribute__ ((weak, alias("Default_Handler")));
void UART5_IRQHandler(void)             __attribute__ ((weak, alias("Default_Handler")));
void TIM6_DAC_IRQHandler(void)          __attribute__ ((weak, alias("Default_Handler")));
void TIM7_IRQHandler(void)              __attribute__ ((weak, alias("Default_Handler")));
void DMA2_Stream0_IRQHandler(void)      __attribute__ ((weak, alias("Default_Handler")));
void DMA2_Stream1_IRQHandler(void)      __attribute__ ((weak, alias("Default_Handler")));
void DMA2_Stream2_IRQHandler(void)      __attribute__ ((weak, alias("Default_Handler")));
void DMA2_Stream3_IRQHandler(void)      __attribute__ ((weak, alias("Default_Handler")));
void DMA2_Stream4_IRQHandler(void)      __attribute__ ((weak, alias("Default_Handler")));
void CAN2_TX_IRQHandler(void)           __attribute__ ((weak, alias("Default_Handler")));
void CAN2_RX0_IRQHandler(void)          __attribute__ ((weak, alias("Default_Handler")));
void CAN2_RX1_IRQHandler(void)          __attribute__ ((weak, alias("Default_Handler")));
void CAN2_SCE_IRQHandler(void)          __attribute__ ((weak, alias("Default_Handler")));
void OTG_FS_IRQHandler(void)            __attribute__ ((weak, alias("Default_Handler")));
void DMA2_Stream5_IRQHandler(void)      __attribute__ ((weak, alias("Default_Handler")));
void DMA2_Stream6_IRQHandler(void)      __attribute__ ((weak, alias("Default_Handler")));
void DMA2_Stream7_IRQHandler(void)      __attribute__ ((weak, alias("Default_Handler")));
void USART6_IRQHandler(void)            __attribute__ ((weak, alias("Default_Handler")));
void I2C3_EV_IRQHandler(void)           __attribute__ ((weak, alias("Default_Handler")));
void I2C3_ER_IRQHandler(void)           __attribute__ ((weak, alias("Default_Handler")));
void OTG_HS_EP1_OUT_IRQHandler(void)    __attribute__ ((weak, alias("Default_Handler")));
void OTG_HS_EP1_IN_IRQHandler(void)     __attribute__ ((weak, alias("Default_Handler")));
void OTG_HS_WKUP_IRQHandler(void)       __attribute__ ((weak, alias("Default_Handler")));
void OTG_HS_IRQHandler(void)            __attribute__ ((weak, alias("Default_Handler")));
void DCMI_IRQHandler(void)              __attribute__ ((weak, alias("Default_Handler")));
void FPU_IRQHandler(void)               __attribute__ ((weak, alias("Default_Handler")));
void SPI4_IRQHandler(void)              __attribute__ ((weak, alias("Default_Handler")));
void SAI1_IRQHandler(void)              __attribute__ ((weak, alias("Default_Handler")));
void SAI2_IRQHandler(void)              __attribute__ ((weak, alias("Default_Handler")));
void QuadSPI_IRQHandler(void)           __attribute__ ((weak, alias("Default_Handler")));
void HDMI_CEC_IRQHandler(void)          __attribute__ ((weak, alias("Default_Handler")));
void SPDIF_Rx_IRQHandler(void)          __attribute__ ((weak, alias("Default_Handler")));
void FMPI2C1_EV_IRQHandler(void)        __attribute__ ((weak, alias("Default_Handler")));
void FMPI2C1_ER_IRQHandler(void)        __attribute__ ((weak, alias("Default_Handler")));

uint32_t vectors[] __attribute__((section(".isr_vector"))) = {
    // --- Core Cortex-M4 Exceptions ---
    ((uint32_t)&_estack),                           // 0x0000 0000 - Initial Stack Pointer
    ((uint32_t)&Reset_Handler),                     // 0x0000 0004 - Reset
    ((uint32_t)&NMI_Handler),                       // 0x0000 0008 - NMI
    ((uint32_t)&HardFault_Handler),                 // 0x0000 000C - HardFault
    ((uint32_t)&MemManage_Handler),                 // 0x0000 0010 - MemManage
    ((uint32_t)&BusFault_Handler),                  // 0x0000 0014 - BusFault
    ((uint32_t)&UsageFault_Handler),                // 0x0000 0018 - UsageFault
    0,                                              // 0x0000 001C - Reserved
    0,                                              // 0x0000 0020 - Reserved
    0,                                              // 0x0000 0024 - Reserved
    0,                                              // 0x0000 0028 - Reserved
    ((uint32_t)&SVC_Handler),                       // 0x0000 002C - SVCall
    ((uint32_t)&DebugMon_Handler),                  // 0x0000 0030 - Debug Monitor
    0,                                              // 0x0000 0034 - Reserved
    ((uint32_t)&PendSV_Handler),                    // 0x0000 0038 - PendSV
    ((uint32_t)&SysTick_Handler),                   // 0x0000 003C - SysTick

    // --- STM32F446xx Specific Interrupts ---
    ((uint32_t)&WWDG_IRQHandler),                   // 0x0000 0040 - Position 0
    ((uint32_t)&PVD_IRQHandler),                    // 0x0000 0044 - Position 1
    ((uint32_t)&TAMP_STAMP_IRQHandler),             // 0x0000 0048 - Position 2
    ((uint32_t)&RTC_WKUP_IRQHandler),               // 0x0000 004C - Position 3
    ((uint32_t)&FLASH_IRQHandler),                  // 0x0000 0050 - Position 4
    ((uint32_t)&RCC_IRQHandler),                    // 0x0000 0054 - Position 5
    ((uint32_t)&EXTI0_IRQHandler),                  // 0x0000 0058 - Position 6
    ((uint32_t)&EXTI1_IRQHandler),                  // 0x0000 005C - Position 7
    ((uint32_t)&EXTI2_IRQHandler),                  // 0x0000 0060 - Position 8
    ((uint32_t)&EXTI3_IRQHandler),                  // 0x0000 0064 - Position 9
    ((uint32_t)&EXTI4_IRQHandler),                  // 0x0000 0068 - Position 10
    ((uint32_t)&DMA1_Stream0_IRQHandler),           // 0x0000 006C - Position 11
    ((uint32_t)&DMA1_Stream1_IRQHandler),           // 0x0000 0070 - Position 12
    ((uint32_t)&DMA1_Stream2_IRQHandler),           // 0x0000 0074 - Position 13
    ((uint32_t)&DMA1_Stream3_IRQHandler),           // 0x0000 0078 - Position 14
    ((uint32_t)&DMA1_Stream4_IRQHandler),           // 0x0000 007C - Position 15
    ((uint32_t)&DMA1_Stream5_IRQHandler),           // 0x0000 0080 - Position 16
    ((uint32_t)&DMA1_Stream6_IRQHandler),           // 0x0000 0084 - Position 17
    ((uint32_t)&ADC_IRQHandler),                    // 0x0000 0088 - Position 18
    ((uint32_t)&CAN1_TX_IRQHandler),                // 0x0000 008C - Position 19
    ((uint32_t)&CAN1_RX0_IRQHandler),               // 0x0000 0090 - Position 20
    ((uint32_t)&CAN1_RX1_IRQHandler),               // 0x0000 0094 - Position 21
    ((uint32_t)&CAN1_SCE_IRQHandler),               // 0x0000 0098 - Position 22
    ((uint32_t)&EXTI9_5_IRQHandler),                // 0x0000 009C - Position 23
    ((uint32_t)&TIM1_BRK_TIM9_IRQHandler),          // 0x0000 00A0 - Position 24
    ((uint32_t)&TIM1_UP_TIM10_IRQHandler),          // 0x0000 00A4 - Position 25
    ((uint32_t)&TIM1_TRG_COM_TIM11_IRQHandler),     // 0x0000 00A8 - Position 26
    ((uint32_t)&TIM1_CC_IRQHandler),                // 0x0000 00AC - Position 27
    ((uint32_t)&TIM2_IRQHandler),                   // 0x0000 00B0 - Position 28
    ((uint32_t)&TIM3_IRQHandler),                   // 0x0000 00B4 - Position 29
    ((uint32_t)&TIM4_IRQHandler),                   // 0x0000 00B8 - Position 30
    ((uint32_t)&I2C1_EV_IRQHandler),                // 0x0000 00BC - Position 31
    ((uint32_t)&I2C1_ER_IRQHandler),                // 0x0000 00C0 - Position 32
    ((uint32_t)&I2C2_EV_IRQHandler),                // 0x0000 00C4 - Position 33
    ((uint32_t)&I2C2_ER_IRQHandler),                // 0x0000 00C8 - Position 34
    ((uint32_t)&SPI1_IRQHandler),                   // 0x0000 00CC - Position 35
    ((uint32_t)&SPI2_IRQHandler),                   // 0x0000 00D0 - Position 36
    ((uint32_t)&USART1_IRQHandler),                 // 0x0000 00D4 - Position 37
    ((uint32_t)&USART2_IRQHandler),                 // 0x0000 00D8 - Position 38
    ((uint32_t)&USART3_IRQHandler),                 // 0x0000 00DC - Position 39
    ((uint32_t)&EXTI15_10_IRQHandler),              // 0x0000 00E0 - Position 40
    ((uint32_t)&RTC_Alarm_IRQHandler),              // 0x0000 00E4 - Position 41
    ((uint32_t)&OTG_FS_WKUP_IRQHandler),            // 0x0000 00E8 - Position 42
    ((uint32_t)&TIM8_BRK_TIM12_IRQHandler),         // 0x0000 00EC - Position 43
    ((uint32_t)&TIM8_UP_TIM13_IRQHandler),          // 0x0000 00F0 - Position 44
    ((uint32_t)&TIM8_TRG_COM_TIM14_IRQHandler),     // 0x0000 00F4 - Position 45
    ((uint32_t)&TIM8_CC_IRQHandler),                // 0x0000 00F8 - Position 46
    ((uint32_t)&DMA1_Stream7_IRQHandler),           // 0x0000 00FC - Position 47
    ((uint32_t)&FMC_IRQHandler),                    // 0x0000 0100 - Position 48
    ((uint32_t)&SDIO_IRQHandler),                   // 0x0000 0104 - Position 49
    ((uint32_t)&TIM5_IRQHandler),                   // 0x0000 0108 - Position 50
    ((uint32_t)&SPI3_IRQHandler),                   // 0x0000 010C - Position 51
    ((uint32_t)&UART4_IRQHandler),                  // 0x0000 0110 - Position 52
    ((uint32_t)&UART5_IRQHandler),                  // 0x0000 0114 - Position 53
    ((uint32_t)&TIM6_DAC_IRQHandler),               // 0x0000 0118 - Position 54
    ((uint32_t)&TIM7_IRQHandler),                   // 0x0000 011C - Position 55
    ((uint32_t)&DMA2_Stream0_IRQHandler),           // 0x0000 0120 - Position 56
    ((uint32_t)&DMA2_Stream1_IRQHandler),           // 0x0000 0124 - Position 57
    ((uint32_t)&DMA2_Stream2_IRQHandler),           // 0x0000 0128 - Position 58
    ((uint32_t)&DMA2_Stream3_IRQHandler),           // 0x0000 012C - Position 59
    ((uint32_t)&DMA2_Stream4_IRQHandler),           // 0x0000 0130 - Position 60
    0,                                              // 0x0000 0134 - Position 61 (Reserved)
    0,                                              // 0x0000 0138 - Position 62 (Reserved)
    ((uint32_t)&CAN2_TX_IRQHandler),                // 0x0000 013C - Position 63
    ((uint32_t)&CAN2_RX0_IRQHandler),               // 0x0000 0140 - Position 64
    ((uint32_t)&CAN2_RX1_IRQHandler),               // 0x0000 0144 - Position 65
    ((uint32_t)&CAN2_SCE_IRQHandler),               // 0x0000 0148 - Position 66
    ((uint32_t)&OTG_FS_IRQHandler),                 // 0x0000 014C - Position 67
    ((uint32_t)&DMA2_Stream5_IRQHandler),           // 0x0000 0150 - Position 68
    ((uint32_t)&DMA2_Stream6_IRQHandler),           // 0x0000 0154 - Position 69
    ((uint32_t)&DMA2_Stream7_IRQHandler),           // 0x0000 0158 - Position 70
    ((uint32_t)&USART6_IRQHandler),                 // 0x0000 015C - Position 71
    ((uint32_t)&I2C3_EV_IRQHandler),                // 0x0000 0160 - Position 72
    ((uint32_t)&I2C3_ER_IRQHandler),                // 0x0000 0164 - Position 73
    ((uint32_t)&OTG_HS_EP1_OUT_IRQHandler),         // 0x0000 0168 - Position 74
    ((uint32_t)&OTG_HS_EP1_IN_IRQHandler),          // 0x0000 016C - Position 75
    ((uint32_t)&OTG_HS_WKUP_IRQHandler),            // 0x0000 0170 - Position 76
    ((uint32_t)&OTG_HS_IRQHandler),                 // 0x0000 0174 - Position 77
    ((uint32_t)&DCMI_IRQHandler),                   // 0x0000 0178 - Position 78
    0,                                              // 0x0000 017C - Position 79 (Reserved)
    0,                                              // 0x0000 0180 - Position 80 (Reserved)
    ((uint32_t)&FPU_IRQHandler),                    // 0x0000 0184 - Position 81
    0,                                              // 0x0000 0188 - Position 82 (Reserved)
    0,                                              // 0x0000 018C - Position 83 (Reserved)
    ((uint32_t)&SPI4_IRQHandler),                   // 0x0000 0190 - Position 84
    0,                                              // 0x0000 0194 - Position 85 (Reserved)
    0,                                              // 0x0000 0198 - Position 86 (Reserved)
    ((uint32_t)&SAI1_IRQHandler),                   // 0x0000 019C - Position 87
    0,                                              // 0x0000 01A0 - Position 88 (Reserved)
    0,                                              // 0x0000 01A4 - Position 89 (Reserved)
    0,                                              // 0x0000 01A8 - Position 90 (Reserved)
    ((uint32_t)&SAI2_IRQHandler),                   // 0x0000 01AC - Position 91
    ((uint32_t)&QuadSPI_IRQHandler),                // 0x0000 01B0 - Position 92
    ((uint32_t)&HDMI_CEC_IRQHandler),               // 0x0000 01B4 - Position 93
    ((uint32_t)&SPDIF_Rx_IRQHandler),               // 0x0000 01B8 - Position 94
    ((uint32_t)&FMPI2C1_EV_IRQHandler),             // 0x0000 01BC - Position 95
    ((uint32_t)&FMPI2C1_ER_IRQHandler)              // 0x0000 01C0 - Position 96
};

void Default_Handler(void)
{

}

void reset_handler(void)
{
// initialize the .data and .bss section and move it to SRAM	

//initialize the std lib ( if we would i.e )

// call the main() function
}