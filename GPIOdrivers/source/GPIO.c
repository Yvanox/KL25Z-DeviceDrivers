/*
 * GPIO.c
 *
 *  Created on: Mar 1, 2018
 *      Author: yvanox
 */

#include "GPIO.h"


/*********************************************************************
 * 																	 *
 * 							Driver APIs								 *
 * 																	 *
 *********************************************************************/

void GPIO_pinControlRegister(PORT_Type *PORTx,uint8_t pin, gpio_pin_controlreg_t* gpio_pin_controlreg)
{
	PORTx->PCR[pin] |= gpio_pin_controlreg->ps;			/* The value of ps is passed to PCR (PinControlRegister) Array*/
	PORTx->PCR[pin] |= gpio_pin_controlreg->pe;			/* The value of ps is passed to PCR (PinControlRegister) Array*/
	PORTx->PCR[pin] |= gpio_pin_controlreg->sre;		/* The value of ps is passed to PCR (PinControlRegister) Array*/
	PORTx->PCR[pin] |= gpio_pin_controlreg->filter;		/* The value of ps is passed to PCR (PinControlRegister) Array*/
	PORTx->PCR[pin] |= gpio_pin_controlreg->strength;	/* The value of ps is passed to PCR (PinControlRegister) Array*/
	PORTx->PCR[pin] |= gpio_pin_controlreg->mux;		/* The value of ps is passed to PCR (PinControlRegister) Array*/
	PORTx->PCR[pin] |= gpio_pin_controlreg->irq;		/* The value of ps is passed to PCR (PinControlRegister) Array*/
	PORTx->PCR[pin] |= gpio_pin_controlreg->isf;		/* The value of ps is passed to PCR (PinControlRegister) Array*/
}


void GPIO_dataDirectionPIN(GPIO_Type *GPIOx,uint8_t pin,uint32_t state)
{
	GPIOx->PDDR |= (state<<(pin));	/* The value of the state is passed to PDDR pin */
}

void GPIO_togglePIN(GPIO_Type *GPIOx, uint8_t pin)
{
	GPIOx->PTOR |= (1<<pin);		/* The PTOR direction pin is enabled */
}

void GPIO_clearPIN(GPIO_Type *GPIOx, uint8_t pin)
{
	GPIOx->PCOR |= (1<<pin);		/* The PCOR direction pin is enabled */
}

void GPIO_setPIN(GPIO_Type *GPIOx, uint8_t pin)
{
	GPIOx->PSOR |= (1<<pin);		/* The PSOR direction pin is enabled */
}

uint8_t GPIO_readPIN(GPIO_Type *GPIOx, uint8_t pin)
{
	uint8_t value;
	/* Read from the PDIR register then right shift by the value of pin number to
	   get the input status value of the pin to lsb*/
	value = ((GPIOx->PDIR >> pin) & 0x00000001);

	return value;
}

uint32_t GPIO_readPORT(GPIO_Type *GPIOx, uint8_t pin)
{
	uint32_t value;

	value = GPIOx->PDIR;	/* Read from the PDIR register and save it to value, then return the result*/

	return value;
}

void GPIO_writePIN(GPIO_Type *GPIOx, uint8_t pin,uint8_t val)
{
	if(val)
		GPIOx->PDOR |= (1<<pin);	/* If a uint8 value is present, write it to the selected pin */
	else
		GPIOx->PDOR &= ~(1<<pin);	/* else delete the contents of the pin */
}


/*********************************************************************
 * 																	 *
 * 					(Interrupt) Driver APIs							 *
 * 																	 *
 *********************************************************************/

void GPIO_configureInterrupt(IRQn_Type irq_no,uint32_t priority)
{
	NVIC_EnableIRQ (irq_no);
	NVIC_SetPriority (irq_no, priority);
}

void GPIO_clearInterrupt(PORT_Type *PORTx)
{
	PORTx->ISFR = 0xFFFFFFF;
}
