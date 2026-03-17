#include<stdint.h>
#include "led.h"



void delay(uint32_t count)
{
  for(volatile uint32_t i = 0 ; i < count ; i++);
}

void led_init_all(void)
{

	uint32_t *pRccAhb1enr = (uint32_t*)0x40023830; // enable ahb1
	uint32_t *pGpiodModeReg = (uint32_t*)0x40020000; // access mode_reg for gpio_a


	*pRccAhb1enr |= ( 1 << 0); // 1: IO port A clock enabled (GPIO_A)
	//configure LED_GREEN
	//clear the bits
	*pGpiodModeReg &= ~( 0x3 << (2 * LED_GREEN) );
	*pGpiodModeReg &= ~( 0x3 << (2 * LED_ORANGE) );
	*pGpiodModeReg &= ~( 0x3 << (2 * LED_RED) );
	*pGpiodModeReg &= ~( 0x3 << (2 * LED_BLUE) );

	// now set the pins to output mode
	*pGpiodModeReg |= ( 1 << (2 * LED_GREEN));
	*pGpiodModeReg |= ( 1 << (2 * LED_ORANGE));
	*pGpiodModeReg |= ( 1 << (2 * LED_RED));
	*pGpiodModeReg |= ( 1 << (2 * LED_BLUE));

#if 0
	//configure the output type
	*pGpioOpTypeReg |= ( 1 << (2 * LED_GREEN));
	*pGpioOpTypeReg |= ( 1 << (2 * LED_ORANGE));
	*pGpioOpTypeReg |= ( 1 << (2 * LED_RED));
	*pGpioOpTypeReg |= ( 1 << (2 * LED_BLUE));
#endif

    led_off(LED_GREEN);
    led_off(LED_ORANGE);
    led_off(LED_RED);
    led_off(LED_BLUE);



}

void led_on(uint8_t led_no)
{
  uint32_t *pGpiodDataReg = (uint32_t*)0x40020014;
  *pGpiodDataReg |= ( 1 << led_no);

}

void led_off(uint8_t led_no)
{
	  uint32_t *pGpiodDataReg = (uint32_t*)0x40020014;
	  *pGpiodDataReg &= ~( 1 << led_no);

}
