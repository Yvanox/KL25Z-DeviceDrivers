/*
 * main.c
 *
 *  Created on: Mar 1, 2018
 *      Author: yvanox
 */

#include "MKL25Z4.h"
#include "GPIO.h"
#include "DataTypeDef.h"

void led_init();

void PORTA_IRQHandler()
{

	uint32_t i;

	if(GPIO_readPIN(GPIOA,BIT1)==0)
	{
	for(i=0;i<500000;i++);
	GPIO_togglePIN(GPIOD, BLUE_LED);
	GPIO_clearInterrupt(PORTA);
	}
	if(GPIO_readPIN(GPIOA,BIT2)==0)
	{
	for(i=0;i<500000;i++);
	GPIO_togglePIN(GPIOB, GREEN_LED);
	GPIO_clearInterrupt(PORTA);
	}
	if(GPIO_readPIN(GPIOA,BIT5)==0)
	{
	for(i=0;i<500000;i++);
	GPIO_togglePIN(GPIOB, RED_LED);
	GPIO_clearInterrupt(PORTA);
	}

}

int main()
{
//	uint32_t i;

	led_init();

	while(1)
	{

		/*for(i=0;i<500000;i++);
		GPIO_clearPIN(GPIOB,RED_LED);
		for(i=0;i<500000;i++);
		GPIO_setPIN(GPIOB,RED_LED);*/

		/*for(i=0;i<500000;i++);
		GPIO_clearPIN(GPIOB,GREEN_LED);
		for(i=0;i<500000;i++);
		GPIO_setPIN(GPIOB,GREEN_LED);*/

		//for(i=0;i<500000;i++);
		//GPIO_clearPIN(GPIOD,BLUE_LED);
		//for(i=0;i<500000;i++);
		//GPIO_setPIN(GPIOD,BLUE_LED);

	}
	return 0;
}

void led_init()
{
	_GPIOD_CLK_GATING();
	_GPIOB_CLK_GATING();
	_GPIOA_CLK_GATING();

	gpio_pin_controlreg_t led_pin_control_reg;

	led_pin_control_reg.ps = NULL;
	led_pin_control_reg.pe = NULL;
	led_pin_control_reg.sre = NULL;
	led_pin_control_reg.filter = NULL;
	led_pin_control_reg.strength = NULL;
	led_pin_control_reg.mux = GPIO_MUX1;
	led_pin_control_reg.irq = NULL;
	led_pin_control_reg.isf = NULL;

	gpio_pin_controlreg_t btn_pin_control_reg;

	btn_pin_control_reg.ps = NULL;
	btn_pin_control_reg.pe = NULL;
	btn_pin_control_reg.sre = NULL;
	btn_pin_control_reg.filter = NULL;
	btn_pin_control_reg.strength = NULL;
	btn_pin_control_reg.mux = GPIO_MUX1;
	btn_pin_control_reg.irq = GPIO_IRQC6;
	btn_pin_control_reg.isf = NULL;

	GPIO_pinControlRegister(PORTB,RED_LED,&led_pin_control_reg);
	GPIO_pinControlRegister(PORTB,GREEN_LED,&led_pin_control_reg);
	GPIO_pinControlRegister(PORTD,BLUE_LED,&led_pin_control_reg);

	GPIO_pinControlRegister(PORTA,BIT1,&btn_pin_control_reg);
	GPIO_pinControlRegister(PORTA,BIT2,&btn_pin_control_reg);
	GPIO_pinControlRegister(PORTA,BIT5,&btn_pin_control_reg);


	GPIO_dataDirectionPIN(GPIOB,RED_LED,GPIO_OUTPUT);
	GPIO_dataDirectionPIN(GPIOB,GREEN_LED,GPIO_OUTPUT);
	GPIO_dataDirectionPIN(GPIOD,BLUE_LED,GPIO_OUTPUT);

	GPIO_dataDirectionPIN(GPIOA,BIT1,GPIO_INPUT);
	GPIO_dataDirectionPIN(GPIOA,BIT2,GPIO_INPUT);
	GPIO_dataDirectionPIN(GPIOA,BIT5,GPIO_INPUT);

	GPIO_setPIN(GPIOB, RED_LED);
	GPIO_setPIN(GPIOB, GREEN_LED);
	GPIO_setPIN(GPIOD, BLUE_LED);

	GPIO_configureInterrupt(PORTA_IRQn,PRIORITY_2);

}
