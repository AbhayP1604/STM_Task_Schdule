
#include <stdint.h>
#include <stdio.h>
#include "main.h"
#include "led.h"

/*function prototypes */
void task1_handler(void);
void task2_handler(void);
void task3_handler(void);
void task4_handler(void);
void init_systick_timer(uint32_t tick_hz);
void user_tasks_init();
__attribute ((naked)) void schdule_stack(uint32_t pScheduler_stack_top);
void enable_processor_faults();
__attribute ((naked)) void switch_sp_to_psp();
void task_delay(uint32_t task_tick);
extern void initialise_monitor_handles(void);


//global variables
// This is a Global variable(array) that holds the psp of various user t1.t2.etc tasks
uint32_t *pSRVR = (uint32_t*)0xE000E014;
// uint32_t psp_user_task[MAX_TASKS] = {T1_START_STACK,T2_START_STACK,T3_START_STACK,T4_START_STACK};
 //uint32_t task_handler[MAX_TASKS]; // to store address(s) of different task handlers;

uint32_t *pSHCSR = (uint32_t*)0xE000ED24; // to enable all the system faults/exception
uint8_t current_task = 1; // current task is 1 (0 is for idle_task)
uint32_t g_tick_count = 0;

//making a struct to organize all the attributes of user_task ( for task_state implementation )

 typedef struct {

	 uint32_t psp_user_task;
	 uint32_t block_count;
	 uint8_t current_state;
	 void (*task_handler) (void);

}TCB_t;

TCB_t user_task[MAX_TASKS];

int main(void)
{
	// 1. Move the OS Stack out of the way (You fixed this!)
		
		enable_processor_faults();
		initialise_monitor_handles();

#ifdef OLD_CODE
		// 2. Setup task pointers
		task_handler[0] = (uint32_t)task1_handler;
		task_handler[1] = (uint32_t)task2_handler;
		task_handler[2] = (uint32_t)task3_handler;
		task_handler[3] = (uint32_t)task4_handler;

#endif

		schdule_stack(SCHED_STACK_START);
		// 3. Initialize Memory (Must happen BEFORE switching to PSP!)
		user_tasks_init();
		led_init_all();


		// 4. Activate the Process Stack Pointer
		switch_sp_to_psp();

		// 5. START THE HEARTBEAT
		init_systick_timer(TICK_HZ);

		// 6. Jump into the first task
		task1_handler();

		for(;;);
}

void idle_handler(){

	while(1){
		// printf("idle task is running! \n");
	}
}

void task1_handler (void)
{
	while(1){
		led_on(LED_GREEN);
		task_delay(1000);
		
		led_off(LED_GREEN);
		task_delay(1000);
	}
}
void task2_handler (void)
{
	while(1){
		printf("This is task 2 handler \n");
		led_on(LED_ORANGE);
		task_delay(500);
		led_off(LED_ORANGE);
		task_delay(500);
	}
}

void task3_handler (void)
{
	while(1){
		printf("This is task 3 handler \n");
		led_on(LED_RED);
		task_delay(250);
		led_off(LED_RED);
		task_delay(250);
	}
}

void task4_handler (void)
{
	while(1){
		printf("This is task 4 handler \n");
		led_on(LED_BLUE);
		task_delay(125);
		led_off(LED_BLUE);
		task_delay(125);
	}
}
void init_systick_timer(uint32_t tick_hz){

	uint32_t *pSCSR = (uint32_t*)0xE000E010; //systick counter and status register

	uint32_t count_value = (SYSTICK_TIMR_CLK / tick_hz)-1; // this is every 1ms systick_timer interrupt

	//clear the bits
	*pSRVR &= ~(0x00FFFFFF);

	//load the value into psvr
	*pSRVR |= count_value;

	//set the bits
	*pSCSR |= ( 1 << 1); // enabling systick exception
	*pSCSR |= ( 1 << 2); // to use internal clock source

	// do some stuff
	*pSCSR |= ( 1 << 0); // enabling the counter


}

__attribute ((naked)) void schdule_stack(uint32_t pScheduler_stack_top){

	// printf("This is implemention of task scheduler \n");
	__asm volatile("MSR MSP,%0" : : "r"(pScheduler_stack_top)); // takes c variable and put it into a Reg -> MSP (pointing the msp to scheduler's top of stack)
	__asm volatile ("BX LR"); // exit to main

}

void user_tasks_init(){

	//initialize the address and state of tasks
	user_task[0].current_state = TASK_READY_STATE;
	user_task[1].current_state = TASK_READY_STATE;
	user_task[2].current_state = TASK_READY_STATE;
	user_task[3].current_state = TASK_READY_STATE;
	user_task[4].current_state = TASK_READY_STATE;

	user_task[0].task_handler = idle_handler;
	user_task[1].task_handler = task1_handler;
	user_task[2].task_handler = task2_handler;
	user_task[3].task_handler = task3_handler;
	user_task[4].task_handler = task4_handler;

	user_task[0].psp_user_task = IDLE_START_STACK;
	user_task[1].psp_user_task = T1_START_STACK;
	user_task[2].psp_user_task = T2_START_STACK;
	user_task[3].psp_user_task = T3_START_STACK;
	user_task[4].psp_user_task = T4_START_STACK;

	uint32_t *pPSP;
// initializing the stack frame of all tasks with dummy stack/ values (except LR)
	for(volatile uint8_t i = 0; i < MAX_TASKS; i++){

		pPSP = (uint32_t*)user_task[i].psp_user_task;
		pPSP--; //xpsr
		*pPSP =  DUMMY_XPSR; // 0x01000000 minimum value - T-bit [24bit] need to be 1 so yeah figure it out!

		pPSP--; //pc
		*pPSP = ( (uint32_t)user_task[i].task_handler | 0x01); // address of task  handler must be odd

		pPSP--; //LR
		*pPSP = 0xFFFFFFFD;

		for(volatile uint8_t j = 0; j < 13; j++){
			pPSP--; // registers dummy value - 0 (for init) r4-r11
			*pPSP = 0;
		}

		user_task[i].psp_user_task = (uint32_t)pPSP; // Storing the psp of "task X" i.e pointing to "task X's" stack after MOD

	}
}

void schedule(void){
	uint32_t *pICSR = (uint32_t *)0xE000ED04; // pends the PendSV triggerring the pendsv_handler
	*pICSR |= (1 << 28);
}

void task_delay(uint32_t task_tick){

	// disable interrupt
	INTERRUPT_DISABLE();


	if(current_task) {
		user_task[current_task].block_count = g_tick_count + task_tick;
		user_task[current_task].current_state = TASK_BLOCKED_STATE;
		schedule();
	}
	// enable interrupt
	INTERRUPT_ENABLE();
}
uint32_t get_psp_value(void){
	return user_task[current_task].psp_user_task;
}

void save_psp_value(uint32_t current_psp_value){
	user_task[current_task].psp_user_task = current_psp_value;
}

void update_task(){
 /*		-----OLD_CODE-----
	for( int i = current_task; i < MAX_TASK; i++){
		if(user_task[i].current_state != TASK_BLOCKED_STATE){
			current_task++;
			break;
		}
	}
	current_task %= MAX_TASKS; // reseting the current task to 0 ( current_task == max_task)
}
	my implementation of updating task...will work on this later! */

	int state = TASK_READY_STATE;
	for (int i = 0; i < MAX_TASKS; i++) {
		current_task++;
		current_task %= MAX_TASKS;
		state = user_task[current_task].current_state;
		if ( (state == TASK_READY_STATE) && (current_task != 0)) {
			break;
		}
	}

	if(state != TASK_READY_STATE){
		current_task = 0;
	}
}

__attribute ((naked)) void PendSV_Handler(void){

	//context switching
	 /* we are trying to switch tasks in systick_handler here
	   * - t1 -> systick-exception -> t2 -> systick-exception -> t3... etc */

		/* PHASE-1 */

		//1. get the psp value of current task
		__asm volatile("MRS r0,PSP");
		//2. using that psp value storing r4-r11
		__asm volatile("STMDB r0!, {r4-r11} "); // store multiple registers - stm , db - decrement before ( prior to write)

		/*pushing and popping of LR to save it from getting corruped
			 * {we called a function in next instruction which would
			 * override the current LR(main) value} */
		__asm volatile("PUSH {LR}");

		//3. save current value of psp - end of phase-1 of context save&switch
		__asm volatile("BL save_psp_value");

		/* PHASE-2 */

		 // 1. move to task2 stack - decided which task to move to ( which task to run next)
		__asm volatile("BL update_task");
		// get its past psp value
		__asm volatile("BL get_psp_value");
		//using that psp value retrieve SF2 ( r4-r11)
		__asm volatile("LDMIA r0!, {r4-r11}"); // load multiple register with access first increment later
		//u psp and exit - which leads to running task2 (context switched)
		__asm volatile ("MSR PSP,r0");

		__asm volatile("POP {LR}");

		__asm volatile("BX LR");

		/* exit sequence will take place itself by the processor
		 *  since psp was modified it now will exit while pointing
		 *   to task2 - task2 starts */
}

void global_tick_update(void) {
	g_tick_count++;
}

void unblock_task(void){
	for(int i = 1; i < MAX_TASKS; i++){

		if(user_task[i].current_state != TASK_READY_STATE){

			if(user_task[i].block_count == g_tick_count) {

				user_task[i].current_state = TASK_READY_STATE;
			}
		}
	}
}

void SysTick_Handler(void){

	//g_tick_counter update
	global_tick_update();
	unblock_task();

	//calling to PendSV if we do change the task state of a function
	uint32_t *pICSR = (uint32_t *)0xE000ED04; // pends the PendSV triggerring the pendsv_handler
	*pICSR |= (1 << 28);

}


void enable_processor_faults(){
	//enabling the fault exceptions
	//hard fault exception is enabled by default

	  /* MEM fault exception
	     Usage fault exception
         Bus fault exception   */

	*pSHCSR &= ~(0x7 << 16); // clear bits
	*pSHCSR |=  (0x1 << 16); // MEM fault
	*pSHCSR |=  (0x1 << 17); // bus bits
	*pSHCSR |=  (0x1 << 18); // usage bits

}


void HardFault_Handler(void) {
	printf("This is Hard_fault exception! \n");
	while(1);
}
void MemManage_Handler (void){
	printf("This is Memory_fault exception! \n");
		while(1);
}
void BusFault_Handler(void) {
	volatile uint32_t *const pCFSR = (uint32_t*)0xE000ED28; // read only`
	volatile uint32_t *const pBFAR = (uint32_t*)0xE000ED38; // read only
	
	uint32_t BF_type = ((*pCFSR & ~(0xFFFF00FF)) >> 8 ); // capturing only the bfsr bits to know the kind of bus fault occured 
	printf("This is Bus_fault exception! of type 0x%lx \n", BF_type);
	printf(" The error is at address = 0x%lX \n", *pBFAR);  
		while(1);
}

__attribute__ ((naked)) void UsageFault_Handler(void){

	__asm ("MRS r0,MSP");
	__asm("B UsageFault_Handler_c");

}
void UsageFault_Handler_c(uint32_t *pBaseStackFrame) {

	uint32_t *pUFSR = (uint32_t*)0xE000ED2A; // UFSR register pointer
	printf("This is Usage_fault exception! \n");
	// flush(stdout);
	printf(" %lx value of UFSR \n", (*pUFSR & 0xFFFF) );
	// flush(stdout);
	printf("The value of MSP[0] is: %lx \n", pBaseStackFrame[0]);
	// flush(stdout);
	printf("The value of MSP[1]  r1 is: %lx \n", pBaseStackFrame[1]);
	printf("The value of MSP[2]  r2 is: %lx \n", pBaseStackFrame[2]);
	printf("The value of MSP[3]  r3 is: %lx \n", pBaseStackFrame[3]);
	printf("The value of MSP[4] r12 is: %lx \n", pBaseStackFrame[4]);
	printf("The value of MSP[5]  lr is: %lx \n", pBaseStackFrame[5]);
	printf("The value of MSP[6]  PC is: %lx \n", pBaseStackFrame[6]);
	printf("The value of MSP[6]  xPSR is: %lx \n", pBaseStackFrame[7]);

	// flush(stdout);
		while(1);

}

__attribute ((naked)) void switch_sp_to_psp(){

	// initialize the psp with task1 stack start
	__asm volatile("PUSH {LR}"); // to prevent the LR from getting corrupted
	// getting the psp value ( stack pointer ) to know where to point the Actual PSP register to ->
	__asm volatile("BL get_psp_value");
	__asm volatile("MSR PSP,r0");
	__asm volatile("POP {LR}"); // LR brought back alive

	// change sp to psp using control register
	__asm volatile("MOV r0,0x02");
	__asm volatile("MSR control,r0");
	__asm volatile("BX LR"); //  going back to main

}



