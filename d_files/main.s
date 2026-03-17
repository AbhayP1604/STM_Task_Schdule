	.cpu cortex-m4
	.arch armv7e-m
	.fpu softvfp
	.eabi_attribute 20, 1
	.eabi_attribute 21, 1
	.eabi_attribute 23, 3
	.eabi_attribute 24, 1
	.eabi_attribute 25, 1
	.eabi_attribute 26, 1
	.eabi_attribute 30, 6
	.eabi_attribute 34, 1
	.eabi_attribute 18, 4
	.file	"main.c"
	.text
	.global	pSRVR
	.data
	.align	2
	.type	pSRVR, %object
	.size	pSRVR, 4
pSRVR:
	.word	-536813548
	.global	pSHCSR
	.align	2
	.type	pSHCSR, %object
	.size	pSHCSR, 4
pSHCSR:
	.word	-536810204
	.global	current_task
	.type	current_task, %object
	.size	current_task, 1
current_task:
	.byte	1
	.global	g_tick_count
	.bss
	.align	2
	.type	g_tick_count, %object
	.size	g_tick_count, 4
g_tick_count:
	.space	4
	.global	user_task
	.align	2
	.type	user_task, %object
	.size	user_task, 80
user_task:
	.space	80
	.text
	.align	1
	.global	main
	.syntax unified
	.thumb
	.thumb_func
	.type	main, %function
main:
	@ args = 0, pretend = 0, frame = 0
	@ frame_needed = 1, uses_anonymous_args = 0
	push	{r7, lr}
	add	r7, sp, #0
	ldr	r0, .L3
	bl	schdule_stack
	bl	enable_processor_faults
	bl	user_tasks_init
	bl	led_init_all
	bl	switch_sp_to_psp
	mov	r0, #1000
	bl	init_systick_timer
	bl	task1_handler
.L2:
	b	.L2
.L4:
	.align	2
.L3:
	.word	536996864
	.size	main, .-main
	.section	.rodata
	.align	2
.LC0:
	.ascii	"idle task is running! \000"
	.text
	.align	1
	.global	idle_handler
	.syntax unified
	.thumb
	.thumb_func
	.type	idle_handler, %function
idle_handler:
	@ args = 0, pretend = 0, frame = 0
	@ frame_needed = 1, uses_anonymous_args = 0
	push	{r7, lr}
	add	r7, sp, #0
.L6:
	ldr	r0, .L7
	bl	puts
	b	.L6
.L8:
	.align	2
.L7:
	.word	.LC0
	.size	idle_handler, .-idle_handler
	.align	1
	.global	task1_handler
	.syntax unified
	.thumb
	.thumb_func
	.type	task1_handler, %function
task1_handler:
	@ args = 0, pretend = 0, frame = 0
	@ frame_needed = 1, uses_anonymous_args = 0
	push	{r7, lr}
	add	r7, sp, #0
.L10:
	movs	r0, #9
	bl	led_on
	mov	r0, #1000
	bl	task_delay
	movs	r0, #9
	bl	led_off
	mov	r0, #1000
	bl	task_delay
	b	.L10
	.size	task1_handler, .-task1_handler
	.align	1
	.global	task2_handler
	.syntax unified
	.thumb
	.thumb_func
	.type	task2_handler, %function
task2_handler:
	@ args = 0, pretend = 0, frame = 0
	@ frame_needed = 1, uses_anonymous_args = 0
	push	{r7, lr}
	add	r7, sp, #0
.L12:
	movs	r0, #10
	bl	led_on
	mov	r0, #500
	bl	task_delay
	movs	r0, #10
	bl	led_off
	mov	r0, #500
	bl	task_delay
	b	.L12
	.size	task2_handler, .-task2_handler
	.align	1
	.global	task3_handler
	.syntax unified
	.thumb
	.thumb_func
	.type	task3_handler, %function
task3_handler:
	@ args = 0, pretend = 0, frame = 0
	@ frame_needed = 1, uses_anonymous_args = 0
	push	{r7, lr}
	add	r7, sp, #0
.L14:
	movs	r0, #11
	bl	led_on
	movs	r0, #250
	bl	task_delay
	movs	r0, #11
	bl	led_off
	movs	r0, #250
	bl	task_delay
	b	.L14
	.size	task3_handler, .-task3_handler
	.align	1
	.global	task4_handler
	.syntax unified
	.thumb
	.thumb_func
	.type	task4_handler, %function
task4_handler:
	@ args = 0, pretend = 0, frame = 0
	@ frame_needed = 1, uses_anonymous_args = 0
	push	{r7, lr}
	add	r7, sp, #0
.L16:
	movs	r0, #12
	bl	led_on
	movs	r0, #125
	bl	task_delay
	movs	r0, #12
	bl	led_off
	movs	r0, #125
	bl	task_delay
	b	.L16
	.size	task4_handler, .-task4_handler
	.align	1
	.global	init_systick_timer
	.syntax unified
	.thumb
	.thumb_func
	.type	init_systick_timer, %function
init_systick_timer:
	@ args = 0, pretend = 0, frame = 16
	@ frame_needed = 1, uses_anonymous_args = 0
	@ link register save eliminated.
	push	{r7}
	sub	sp, sp, #20
	add	r7, sp, #0
	str	r0, [r7, #4]
	ldr	r3, .L18
	str	r3, [r7, #12]
	ldr	r2, .L18+4
	ldr	r3, [r7, #4]
	udiv	r3, r2, r3
	subs	r3, r3, #1
	str	r3, [r7, #8]
	ldr	r3, .L18+8
	ldr	r3, [r3]
	ldr	r2, [r3]
	ldr	r3, .L18+8
	ldr	r3, [r3]
	and	r2, r2, #-16777216
	str	r2, [r3]
	ldr	r3, .L18+8
	ldr	r3, [r3]
	ldr	r1, [r3]
	ldr	r3, .L18+8
	ldr	r3, [r3]
	ldr	r2, [r7, #8]
	orrs	r2, r2, r1
	str	r2, [r3]
	ldr	r3, [r7, #12]
	ldr	r3, [r3]
	orr	r2, r3, #2
	ldr	r3, [r7, #12]
	str	r2, [r3]
	ldr	r3, [r7, #12]
	ldr	r3, [r3]
	orr	r2, r3, #4
	ldr	r3, [r7, #12]
	str	r2, [r3]
	ldr	r3, [r7, #12]
	ldr	r3, [r3]
	orr	r2, r3, #1
	ldr	r3, [r7, #12]
	str	r2, [r3]
	nop
	adds	r7, r7, #20
	mov	sp, r7
	@ sp needed
	pop	{r7}
	bx	lr
.L19:
	.align	2
.L18:
	.word	-536813552
	.word	16000000
	.word	pSRVR
	.size	init_systick_timer, .-init_systick_timer
	.align	1
	.global	schdule_stack
	.syntax unified
	.thumb
	.thumb_func
	.type	schdule_stack, %function
schdule_stack:
	@ Naked Function: prologue and epilogue provided by programmer.
	@ args = 0, pretend = 0, frame = 0
	@ frame_needed = 1, uses_anonymous_args = 0
	mov	r3, r0
	.syntax unified
@ 144 "main.c" 1
	MSR MSP,r3
@ 0 "" 2
@ 145 "main.c" 1
	BX LR
@ 0 "" 2
	.thumb
	.syntax unified
	nop
	.size	schdule_stack, .-schdule_stack
	.align	1
	.global	user_tasks_init
	.syntax unified
	.thumb
	.thumb_func
	.type	user_tasks_init, %function
user_tasks_init:
	@ args = 0, pretend = 0, frame = 8
	@ frame_needed = 1, uses_anonymous_args = 0
	@ link register save eliminated.
	push	{r7}
	sub	sp, sp, #12
	add	r7, sp, #0
	ldr	r3, .L26
	movs	r2, #255
	strb	r2, [r3, #8]
	ldr	r3, .L26
	movs	r2, #255
	strb	r2, [r3, #24]
	ldr	r3, .L26
	movs	r2, #255
	strb	r2, [r3, #40]
	ldr	r3, .L26
	movs	r2, #255
	strb	r2, [r3, #56]
	ldr	r3, .L26
	movs	r2, #255
	strb	r2, [r3, #72]
	ldr	r3, .L26
	ldr	r2, .L26+4
	str	r2, [r3, #12]
	ldr	r3, .L26
	ldr	r2, .L26+8
	str	r2, [r3, #28]
	ldr	r3, .L26
	ldr	r2, .L26+12
	str	r2, [r3, #44]
	ldr	r3, .L26
	ldr	r2, .L26+16
	str	r2, [r3, #60]
	ldr	r3, .L26
	ldr	r2, .L26+20
	str	r2, [r3, #76]
	ldr	r3, .L26
	ldr	r2, .L26+24
	str	r2, [r3]
	ldr	r3, .L26
	ldr	r2, .L26+28
	str	r2, [r3, #16]
	ldr	r3, .L26
	ldr	r2, .L26+32
	str	r2, [r3, #32]
	ldr	r3, .L26
	ldr	r2, .L26+36
	str	r2, [r3, #48]
	ldr	r3, .L26
	ldr	r2, .L26+40
	str	r2, [r3, #64]
	movs	r3, #0
	strb	r3, [r7, #3]
	b	.L22
.L25:
	ldrb	r3, [r7, #3]
	uxtb	r3, r3
	ldr	r2, .L26
	lsls	r3, r3, #4
	add	r3, r3, r2
	ldr	r3, [r3]
	str	r3, [r7, #4]
	ldr	r3, [r7, #4]
	subs	r3, r3, #4
	str	r3, [r7, #4]
	ldr	r3, [r7, #4]
	mov	r2, #16777216
	str	r2, [r3]
	ldr	r3, [r7, #4]
	subs	r3, r3, #4
	str	r3, [r7, #4]
	ldrb	r3, [r7, #3]
	uxtb	r3, r3
	ldr	r2, .L26
	lsls	r3, r3, #4
	add	r3, r3, r2
	adds	r3, r3, #12
	ldr	r3, [r3]
	orr	r2, r3, #1
	ldr	r3, [r7, #4]
	str	r2, [r3]
	ldr	r3, [r7, #4]
	subs	r3, r3, #4
	str	r3, [r7, #4]
	ldr	r3, [r7, #4]
	mvn	r2, #2
	str	r2, [r3]
	movs	r3, #0
	strb	r3, [r7, #2]
	b	.L23
.L24:
	ldr	r3, [r7, #4]
	subs	r3, r3, #4
	str	r3, [r7, #4]
	ldr	r3, [r7, #4]
	movs	r2, #0
	str	r2, [r3]
	ldrb	r3, [r7, #2]
	uxtb	r3, r3
	adds	r3, r3, #1
	uxtb	r3, r3
	strb	r3, [r7, #2]
.L23:
	ldrb	r3, [r7, #2]
	uxtb	r3, r3
	cmp	r3, #12
	bls	.L24
	ldrb	r3, [r7, #3]
	uxtb	r3, r3
	ldr	r2, [r7, #4]
	ldr	r1, .L26
	lsls	r3, r3, #4
	add	r3, r3, r1
	str	r2, [r3]
	ldrb	r3, [r7, #3]
	uxtb	r3, r3
	adds	r3, r3, #1
	uxtb	r3, r3
	strb	r3, [r7, #3]
.L22:
	ldrb	r3, [r7, #3]
	uxtb	r3, r3
	cmp	r3, #4
	bls	.L25
	nop
	nop
	adds	r7, r7, #12
	mov	sp, r7
	@ sp needed
	pop	{r7}
	bx	lr
.L27:
	.align	2
.L26:
	.word	user_task
	.word	idle_handler
	.word	task1_handler
	.word	task2_handler
	.word	task3_handler
	.word	task4_handler
	.word	536997888
	.word	537001984
	.word	537000960
	.word	536999936
	.word	536998912
	.size	user_tasks_init, .-user_tasks_init
	.align	1
	.global	schedule
	.syntax unified
	.thumb
	.thumb_func
	.type	schedule, %function
schedule:
	@ args = 0, pretend = 0, frame = 8
	@ frame_needed = 1, uses_anonymous_args = 0
	@ link register save eliminated.
	push	{r7}
	sub	sp, sp, #12
	add	r7, sp, #0
	ldr	r3, .L29
	str	r3, [r7, #4]
	ldr	r3, [r7, #4]
	ldr	r3, [r3]
	orr	r2, r3, #268435456
	ldr	r3, [r7, #4]
	str	r2, [r3]
	nop
	adds	r7, r7, #12
	mov	sp, r7
	@ sp needed
	pop	{r7}
	bx	lr
.L30:
	.align	2
.L29:
	.word	-536810236
	.size	schedule, .-schedule
	.align	1
	.global	task_delay
	.syntax unified
	.thumb
	.thumb_func
	.type	task_delay, %function
task_delay:
	@ args = 0, pretend = 0, frame = 8
	@ frame_needed = 1, uses_anonymous_args = 0
	push	{r7, lr}
	sub	sp, sp, #8
	add	r7, sp, #0
	str	r0, [r7, #4]
	.syntax unified
@ 202 "main.c" 1
	MOV R0,#0x1
@ 0 "" 2
@ 202 "main.c" 1
	MSR PRIMASK,R0
@ 0 "" 2
	.thumb
	.syntax unified
	ldr	r3, .L33
	ldrb	r3, [r3]	@ zero_extendqisi2
	cmp	r3, #0
	beq	.L32
	ldr	r3, .L33+4
	ldr	r2, [r3]
	ldr	r3, .L33
	ldrb	r3, [r3]	@ zero_extendqisi2
	mov	r0, r3
	ldr	r3, [r7, #4]
	add	r2, r2, r3
	ldr	r1, .L33+8
	lsls	r3, r0, #4
	add	r3, r3, r1
	adds	r3, r3, #4
	str	r2, [r3]
	ldr	r3, .L33
	ldrb	r3, [r3]	@ zero_extendqisi2
	ldr	r2, .L33+8
	lsls	r3, r3, #4
	add	r3, r3, r2
	adds	r3, r3, #8
	movs	r2, #0
	strb	r2, [r3]
	bl	schedule
.L32:
	.syntax unified
@ 211 "main.c" 1
	MOV R0,#0x0
@ 0 "" 2
@ 211 "main.c" 1
	MSR PRIMASK,R0
@ 0 "" 2
	.thumb
	.syntax unified
	nop
	adds	r7, r7, #8
	mov	sp, r7
	@ sp needed
	pop	{r7, pc}
.L34:
	.align	2
.L33:
	.word	current_task
	.word	g_tick_count
	.word	user_task
	.size	task_delay, .-task_delay
	.align	1
	.global	get_psp_value
	.syntax unified
	.thumb
	.thumb_func
	.type	get_psp_value, %function
get_psp_value:
	@ args = 0, pretend = 0, frame = 0
	@ frame_needed = 1, uses_anonymous_args = 0
	@ link register save eliminated.
	push	{r7}
	add	r7, sp, #0
	ldr	r3, .L37
	ldrb	r3, [r3]	@ zero_extendqisi2
	ldr	r2, .L37+4
	lsls	r3, r3, #4
	add	r3, r3, r2
	ldr	r3, [r3]
	mov	r0, r3
	mov	sp, r7
	@ sp needed
	pop	{r7}
	bx	lr
.L38:
	.align	2
.L37:
	.word	current_task
	.word	user_task
	.size	get_psp_value, .-get_psp_value
	.align	1
	.global	save_psp_value
	.syntax unified
	.thumb
	.thumb_func
	.type	save_psp_value, %function
save_psp_value:
	@ args = 0, pretend = 0, frame = 8
	@ frame_needed = 1, uses_anonymous_args = 0
	@ link register save eliminated.
	push	{r7}
	sub	sp, sp, #12
	add	r7, sp, #0
	str	r0, [r7, #4]
	ldr	r3, .L40
	ldrb	r3, [r3]	@ zero_extendqisi2
	ldr	r2, .L40+4
	lsls	r3, r3, #4
	add	r3, r3, r2
	ldr	r2, [r7, #4]
	str	r2, [r3]
	nop
	adds	r7, r7, #12
	mov	sp, r7
	@ sp needed
	pop	{r7}
	bx	lr
.L41:
	.align	2
.L40:
	.word	current_task
	.word	user_task
	.size	save_psp_value, .-save_psp_value
	.align	1
	.global	update_task
	.syntax unified
	.thumb
	.thumb_func
	.type	update_task, %function
update_task:
	@ args = 0, pretend = 0, frame = 8
	@ frame_needed = 1, uses_anonymous_args = 0
	@ link register save eliminated.
	push	{r7}
	sub	sp, sp, #12
	add	r7, sp, #0
	movs	r3, #255
	str	r3, [r7, #4]
	movs	r3, #0
	str	r3, [r7]
	b	.L43
.L46:
	ldr	r3, .L50
	ldrb	r3, [r3]	@ zero_extendqisi2
	adds	r3, r3, #1
	uxtb	r2, r3
	ldr	r3, .L50
	strb	r2, [r3]
	ldr	r3, .L50
	ldrb	r2, [r3]	@ zero_extendqisi2
	ldr	r3, .L50+4
	umull	r1, r3, r3, r2
	lsrs	r1, r3, #2
	mov	r3, r1
	lsls	r3, r3, #2
	add	r3, r3, r1
	subs	r3, r2, r3
	uxtb	r2, r3
	ldr	r3, .L50
	strb	r2, [r3]
	ldr	r3, .L50
	ldrb	r3, [r3]	@ zero_extendqisi2
	ldr	r2, .L50+8
	lsls	r3, r3, #4
	add	r3, r3, r2
	adds	r3, r3, #8
	ldrb	r3, [r3]	@ zero_extendqisi2
	str	r3, [r7, #4]
	ldr	r3, [r7, #4]
	cmp	r3, #255
	bne	.L44
	ldr	r3, .L50
	ldrb	r3, [r3]	@ zero_extendqisi2
	cmp	r3, #0
	bne	.L48
.L44:
	ldr	r3, [r7]
	adds	r3, r3, #1
	str	r3, [r7]
.L43:
	ldr	r3, [r7]
	cmp	r3, #4
	ble	.L46
	b	.L45
.L48:
	nop
.L45:
	ldr	r3, [r7, #4]
	cmp	r3, #255
	beq	.L49
	ldr	r3, .L50
	movs	r2, #0
	strb	r2, [r3]
.L49:
	nop
	adds	r7, r7, #12
	mov	sp, r7
	@ sp needed
	pop	{r7}
	bx	lr
.L51:
	.align	2
.L50:
	.word	current_task
	.word	-858993459
	.word	user_task
	.size	update_task, .-update_task
	.align	1
	.global	PendSV_Handler
	.syntax unified
	.thumb
	.thumb_func
	.type	PendSV_Handler, %function
PendSV_Handler:
	@ Naked Function: prologue and epilogue provided by programmer.
	@ args = 0, pretend = 0, frame = 0
	@ frame_needed = 1, uses_anonymous_args = 0
	.syntax unified
@ 257 "main.c" 1
	MRS r0,PSP
@ 0 "" 2
@ 259 "main.c" 1
	STMDB r0!, {r4-r11} 
@ 0 "" 2
@ 264 "main.c" 1
	PUSH {LR}
@ 0 "" 2
@ 267 "main.c" 1
	BL save_psp_value
@ 0 "" 2
@ 272 "main.c" 1
	BL update_task
@ 0 "" 2
@ 274 "main.c" 1
	BL get_psp_value
@ 0 "" 2
@ 276 "main.c" 1
	LDMIA r0!, {r4-r11}
@ 0 "" 2
@ 278 "main.c" 1
	MSR PSP,r0
@ 0 "" 2
@ 280 "main.c" 1
	POP {LR}
@ 0 "" 2
@ 282 "main.c" 1
	BX LR
@ 0 "" 2
	.thumb
	.syntax unified
	nop
	.size	PendSV_Handler, .-PendSV_Handler
	.align	1
	.global	global_tick_update
	.syntax unified
	.thumb
	.thumb_func
	.type	global_tick_update, %function
global_tick_update:
	@ args = 0, pretend = 0, frame = 0
	@ frame_needed = 1, uses_anonymous_args = 0
	@ link register save eliminated.
	push	{r7}
	add	r7, sp, #0
	ldr	r3, .L54
	ldr	r3, [r3]
	adds	r3, r3, #1
	ldr	r2, .L54
	str	r3, [r2]
	nop
	mov	sp, r7
	@ sp needed
	pop	{r7}
	bx	lr
.L55:
	.align	2
.L54:
	.word	g_tick_count
	.size	global_tick_update, .-global_tick_update
	.align	1
	.global	unblock_task
	.syntax unified
	.thumb
	.thumb_func
	.type	unblock_task, %function
unblock_task:
	@ args = 0, pretend = 0, frame = 8
	@ frame_needed = 1, uses_anonymous_args = 0
	@ link register save eliminated.
	push	{r7}
	sub	sp, sp, #12
	add	r7, sp, #0
	movs	r3, #1
	str	r3, [r7, #4]
	b	.L57
.L59:
	ldr	r2, .L60
	ldr	r3, [r7, #4]
	lsls	r3, r3, #4
	add	r3, r3, r2
	adds	r3, r3, #8
	ldrb	r3, [r3]	@ zero_extendqisi2
	cmp	r3, #255
	beq	.L58
	ldr	r2, .L60
	ldr	r3, [r7, #4]
	lsls	r3, r3, #4
	add	r3, r3, r2
	adds	r3, r3, #4
	ldr	r2, [r3]
	ldr	r3, .L60+4
	ldr	r3, [r3]
	cmp	r2, r3
	bne	.L58
	ldr	r2, .L60
	ldr	r3, [r7, #4]
	lsls	r3, r3, #4
	add	r3, r3, r2
	adds	r3, r3, #8
	movs	r2, #255
	strb	r2, [r3]
.L58:
	ldr	r3, [r7, #4]
	adds	r3, r3, #1
	str	r3, [r7, #4]
.L57:
	ldr	r3, [r7, #4]
	cmp	r3, #4
	ble	.L59
	nop
	nop
	adds	r7, r7, #12
	mov	sp, r7
	@ sp needed
	pop	{r7}
	bx	lr
.L61:
	.align	2
.L60:
	.word	user_task
	.word	g_tick_count
	.size	unblock_task, .-unblock_task
	.align	1
	.global	SysTick_Handler
	.syntax unified
	.thumb
	.thumb_func
	.type	SysTick_Handler, %function
SysTick_Handler:
	@ args = 0, pretend = 0, frame = 8
	@ frame_needed = 1, uses_anonymous_args = 0
	push	{r7, lr}
	sub	sp, sp, #8
	add	r7, sp, #0
	bl	global_tick_update
	bl	unblock_task
	ldr	r3, .L63
	str	r3, [r7, #4]
	ldr	r3, [r7, #4]
	ldr	r3, [r3]
	orr	r2, r3, #268435456
	ldr	r3, [r7, #4]
	str	r2, [r3]
	nop
	adds	r7, r7, #8
	mov	sp, r7
	@ sp needed
	pop	{r7, pc}
.L64:
	.align	2
.L63:
	.word	-536810236
	.size	SysTick_Handler, .-SysTick_Handler
	.align	1
	.global	enable_processor_faults
	.syntax unified
	.thumb
	.thumb_func
	.type	enable_processor_faults, %function
enable_processor_faults:
	@ args = 0, pretend = 0, frame = 0
	@ frame_needed = 1, uses_anonymous_args = 0
	@ link register save eliminated.
	push	{r7}
	add	r7, sp, #0
	ldr	r3, .L66
	ldr	r3, [r3]
	ldr	r2, [r3]
	ldr	r3, .L66
	ldr	r3, [r3]
	bic	r2, r2, #458752
	str	r2, [r3]
	ldr	r3, .L66
	ldr	r3, [r3]
	ldr	r2, [r3]
	ldr	r3, .L66
	ldr	r3, [r3]
	orr	r2, r2, #65536
	str	r2, [r3]
	ldr	r3, .L66
	ldr	r3, [r3]
	ldr	r2, [r3]
	ldr	r3, .L66
	ldr	r3, [r3]
	orr	r2, r2, #131072
	str	r2, [r3]
	ldr	r3, .L66
	ldr	r3, [r3]
	ldr	r2, [r3]
	ldr	r3, .L66
	ldr	r3, [r3]
	orr	r2, r2, #262144
	str	r2, [r3]
	nop
	mov	sp, r7
	@ sp needed
	pop	{r7}
	bx	lr
.L67:
	.align	2
.L66:
	.word	pSHCSR
	.size	enable_processor_faults, .-enable_processor_faults
	.section	.rodata
	.align	2
.LC1:
	.ascii	"This is Hard_fault exception! \000"
	.text
	.align	1
	.global	HardFault_Handler
	.syntax unified
	.thumb
	.thumb_func
	.type	HardFault_Handler, %function
HardFault_Handler:
	@ args = 0, pretend = 0, frame = 0
	@ frame_needed = 1, uses_anonymous_args = 0
	push	{r7, lr}
	add	r7, sp, #0
	ldr	r0, .L70
	bl	puts
.L69:
	b	.L69
.L71:
	.align	2
.L70:
	.word	.LC1
	.size	HardFault_Handler, .-HardFault_Handler
	.section	.rodata
	.align	2
.LC2:
	.ascii	"This is Memory_fault exception! \000"
	.text
	.align	1
	.global	MemManage_Handler
	.syntax unified
	.thumb
	.thumb_func
	.type	MemManage_Handler, %function
MemManage_Handler:
	@ args = 0, pretend = 0, frame = 0
	@ frame_needed = 1, uses_anonymous_args = 0
	push	{r7, lr}
	add	r7, sp, #0
	ldr	r0, .L74
	bl	puts
.L73:
	b	.L73
.L75:
	.align	2
.L74:
	.word	.LC2
	.size	MemManage_Handler, .-MemManage_Handler
	.section	.rodata
	.align	2
.LC3:
	.ascii	"This is Bus_fault exception! \000"
	.text
	.align	1
	.global	BusFault_Handler
	.syntax unified
	.thumb
	.thumb_func
	.type	BusFault_Handler, %function
BusFault_Handler:
	@ args = 0, pretend = 0, frame = 0
	@ frame_needed = 1, uses_anonymous_args = 0
	push	{r7, lr}
	add	r7, sp, #0
	ldr	r0, .L78
	bl	puts
.L77:
	b	.L77
.L79:
	.align	2
.L78:
	.word	.LC3
	.size	BusFault_Handler, .-BusFault_Handler
	.align	1
	.global	UsageFault_Handler
	.syntax unified
	.thumb
	.thumb_func
	.type	UsageFault_Handler, %function
UsageFault_Handler:
	@ Naked Function: prologue and epilogue provided by programmer.
	@ args = 0, pretend = 0, frame = 0
	@ frame_needed = 1, uses_anonymous_args = 0
	.syntax unified
@ 350 "main.c" 1
	MRS r0,MSP
@ 0 "" 2
@ 351 "main.c" 1
	B UsageFault_Handler_c
@ 0 "" 2
	.thumb
	.syntax unified
	nop
	.size	UsageFault_Handler, .-UsageFault_Handler
	.section	.rodata
	.align	2
.LC4:
	.ascii	"This is Usage_fault exception! \000"
	.align	2
.LC5:
	.ascii	" %lx value of UFSR \012\000"
	.align	2
.LC6:
	.ascii	"The value of MSP[0] is: %lx \012\000"
	.align	2
.LC7:
	.ascii	"The value of MSP[1]  r1 is: %lx \012\000"
	.align	2
.LC8:
	.ascii	"The value of MSP[2]  r2 is: %lx \012\000"
	.align	2
.LC9:
	.ascii	"The value of MSP[3]  r3 is: %lx \012\000"
	.align	2
.LC10:
	.ascii	"The value of MSP[4] r12 is: %lx \012\000"
	.align	2
.LC11:
	.ascii	"The value of MSP[5]  lr is: %lx \012\000"
	.align	2
.LC12:
	.ascii	"The value of MSP[6]  PC is: %lx \012\000"
	.align	2
.LC13:
	.ascii	"The value of MSP[6]  xPSR is: %lx \012\000"
	.text
	.align	1
	.global	UsageFault_Handler_c
	.syntax unified
	.thumb
	.thumb_func
	.type	UsageFault_Handler_c, %function
UsageFault_Handler_c:
	@ args = 0, pretend = 0, frame = 16
	@ frame_needed = 1, uses_anonymous_args = 0
	push	{r7, lr}
	sub	sp, sp, #16
	add	r7, sp, #0
	str	r0, [r7, #4]
	ldr	r3, .L83
	str	r3, [r7, #12]
	ldr	r0, .L83+4
	bl	puts
	ldr	r3, .L83+8
	ldr	r3, [r3]
	ldr	r3, [r3, #8]
	mov	r0, r3
	bl	fflush
	ldr	r3, [r7, #12]
	ldr	r3, [r3]
	uxth	r3, r3
	mov	r1, r3
	ldr	r0, .L83+12
	bl	printf
	ldr	r3, .L83+8
	ldr	r3, [r3]
	ldr	r3, [r3, #8]
	mov	r0, r3
	bl	fflush
	ldr	r3, [r7, #4]
	ldr	r3, [r3]
	mov	r1, r3
	ldr	r0, .L83+16
	bl	printf
	ldr	r3, .L83+8
	ldr	r3, [r3]
	ldr	r3, [r3, #8]
	mov	r0, r3
	bl	fflush
	ldr	r3, [r7, #4]
	adds	r3, r3, #4
	ldr	r3, [r3]
	mov	r1, r3
	ldr	r0, .L83+20
	bl	printf
	ldr	r3, [r7, #4]
	adds	r3, r3, #8
	ldr	r3, [r3]
	mov	r1, r3
	ldr	r0, .L83+24
	bl	printf
	ldr	r3, [r7, #4]
	adds	r3, r3, #12
	ldr	r3, [r3]
	mov	r1, r3
	ldr	r0, .L83+28
	bl	printf
	ldr	r3, [r7, #4]
	adds	r3, r3, #16
	ldr	r3, [r3]
	mov	r1, r3
	ldr	r0, .L83+32
	bl	printf
	ldr	r3, [r7, #4]
	adds	r3, r3, #20
	ldr	r3, [r3]
	mov	r1, r3
	ldr	r0, .L83+36
	bl	printf
	ldr	r3, [r7, #4]
	adds	r3, r3, #24
	ldr	r3, [r3]
	mov	r1, r3
	ldr	r0, .L83+40
	bl	printf
	ldr	r3, [r7, #4]
	adds	r3, r3, #28
	ldr	r3, [r3]
	mov	r1, r3
	ldr	r0, .L83+44
	bl	printf
	ldr	r3, .L83+8
	ldr	r3, [r3]
	ldr	r3, [r3, #8]
	mov	r0, r3
	bl	fflush
.L82:
	b	.L82
.L84:
	.align	2
.L83:
	.word	-536810198
	.word	.LC4
	.word	_impure_ptr
	.word	.LC5
	.word	.LC6
	.word	.LC7
	.word	.LC8
	.word	.LC9
	.word	.LC10
	.word	.LC11
	.word	.LC12
	.word	.LC13
	.size	UsageFault_Handler_c, .-UsageFault_Handler_c
	.align	1
	.global	switch_sp_to_psp
	.syntax unified
	.thumb
	.thumb_func
	.type	switch_sp_to_psp, %function
switch_sp_to_psp:
	@ Naked Function: prologue and epilogue provided by programmer.
	@ args = 0, pretend = 0, frame = 0
	@ frame_needed = 1, uses_anonymous_args = 0
	.syntax unified
@ 379 "main.c" 1
	PUSH {LR}
@ 0 "" 2
@ 381 "main.c" 1
	BL get_psp_value
@ 0 "" 2
@ 382 "main.c" 1
	MSR PSP,r0
@ 0 "" 2
@ 383 "main.c" 1
	POP {LR}
@ 0 "" 2
@ 386 "main.c" 1
	MOV r0,0x02
@ 0 "" 2
@ 387 "main.c" 1
	MSR control,r0
@ 0 "" 2
@ 388 "main.c" 1
	BX LR
@ 0 "" 2
	.thumb
	.syntax unified
	nop
	.size	switch_sp_to_psp, .-switch_sp_to_psp
	.ident	"GCC: (GNU Arm Embedded Toolchain 10.3-2021.10) 10.3.1 20210824 (release)"
