/*
 * main.h
 *
 *  Created on: Mar 11, 2026
 *      Author: Abhayp16
 *
 *
 */

#if 1

/* Stack memory mapping calculations */
#define SIZE_TASK_STACK			1024U
#define SIZE_SCHED_STACK		1024U

#define SRAM_START				0x20000000
#define SIZEOF_SRAM				((128) * (1024))
#define SRAM_END				( SRAM_START) + (SIZEOF_SRAM )

#define T1_START_STACK			SRAM_END
#define T2_START_STACK			( (SRAM_END) - (1 * SIZE_TASK_STACK) )
#define T3_START_STACK			( (SRAM_END) - (2 * SIZE_TASK_STACK) )
#define T4_START_STACK			( (SRAM_END) - (3 * SIZE_TASK_STACK) )
#define IDLE_START_STACK		( (SRAM_END) - (4 * SIZE_TASK_STACK) )

#define SCHED_STACK_START		( (SRAM_END) - (5 * SIZE_TASK_STACK) )

#define TICK_HZ 				1000U
#define HSI_CLK  				16000000U
#define SYSTICK_TIMR_CLK		HSI_CLK
#define MAX_TASKS				5
#define DUMMY_XPSR 				0x01000000

#define TASK_READY_STATE 		0XFF
#define TASK_BLOCKED_STATE 		0X00


#define INTERRUPT_DISABLE() do{ __asm volatile("MOV R0,#0x1"); __asm volatile("MSR PRIMASK,R0"); }while(0);
#define INTERRUPT_ENABLE()  do{ __asm volatile("MOV R0,#0x0"); __asm volatile("MSR PRIMASK,R0"); }while(0);

#endif
