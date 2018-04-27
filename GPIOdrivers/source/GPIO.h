/*
 * GPIO.h
 *
 *  Created on: Mar 1, 2018
 *      Author: yvanox
 */

#ifndef GPIO_H_
#define GPIO_H_

#include "MKL25Z4.h"

/*********************************************************************
 * 																	 *
 * 				Macros used for GPIO pin control register			 *
 * 																	 *
 *********************************************************************/

/* Selects a pullup resistor 			- default: Pulldown*/
#define GPIO_PS 0x00000001
/* Enables the pullup/pulldown resistor - default: Disabled*/
#define GPIO_PE 0x00000002
/* Enables the slow slew rate 			- default: Fast slew rate */
#define GPIO_SRE 0x00000004
/* Enables the passive filter			- default: Disabled */
#define GPIO_PFE 0x00000010
/* Enables High Drive Strength			- default: Low drive strength */
#define GPIO_DSE 0x00000040

/* Enables mux type 1 (GPIO) 			- default: Pin disabled (Analog)*/
#define GPIO_MUX1 0x00000100
/* Enables mux type 2 */
#define GPIO_MUX2 0x00000200
/* Enables mux type 3 */
#define GPIO_MUX3 0x00000300
/* Enables mux type 4 */
#define GPIO_MUX4 0x00000400
/* Enables mux type 5 */
#define GPIO_MUX5 0x00000500
/* Enables mux type 6 */
#define GPIO_MUX6 0x00000600
/* Enables mux type 7 */
#define GPIO_MUX7 0x00000700

/* DMA request on rising edge		 	- default: Interrupt/DMA request disabled*/
#define GPIO_IRQC1 0x00010000
/* DMA request on falling edge */
#define GPIO_IRQC2 0x00020000
/* DMA request on either edge */
#define GPIO_IRQC3 0x00030000
/* Interrupt when logic zero */
#define GPIO_IRQC4 0x00080000
/* Interrupt on rising edge */
#define GPIO_IRQC5 0x00090000
/* Interrupt on falling edge */
#define GPIO_IRQC6 0x000A0000
/* Interrupt on either edge */
#define GPIO_IRQC7 0x000B0000
/* Interrupt when logic one */
#define GPIO_IRQC8 0x000C0000

/* Interrupt Status Flag				- default: Configured interrupt is not detected */
#define GPIO_ISF 0x01000000


/*********************************************************************
 * 																	 *
 * 				Macros used to enable GPIO clock					 *
 * 																	 *
 *********************************************************************/

/* Macros to Enable Clock for different GPIO ports in SIM register */
#define _GPIOA_CLK_GATING() (SIM->SCGC5 |= (1<< 9))
#define _GPIOB_CLK_GATING() (SIM->SCGC5 |= (1<< 10))
#define _GPIOC_CLK_GATING() (SIM->SCGC5 |= (1<< 11))
#define _GPIOD_CLK_GATING() (SIM->SCGC5 |= (1<< 12))
#define _GPIOE_CLK_GATING() (SIM->SCGC5 |= (1<< 13))

/*********************************************************************
 * 																	 *
 * 	Data structure for GPIO pin control register an interrupts		 *
 * 																	 *
 *********************************************************************/

/*
 * @brief	GPIO pin configuration structure
 * 	This structure will be filled and passed to driver by the application
 * 	to initialize the gpio pin
 */

typedef struct
{

	uint32_t ps;		/*Pull select*/

	uint32_t pe;		/*Pull enable*/

	uint32_t sre;		/*Slew rate enable*/

	uint32_t filter;	/*Passive filter enable*/

	uint32_t strength;	/*Drive strength enable*/

	uint32_t mux;		/*Pin mux control*/

	uint32_t irq;		/*Interrupt configuration*/

	uint32_t isf;		/*Interrupt status flag*/

}gpio_pin_controlreg_t;


/*
 * 	GPIO pin interrupt configuration structure
 * 	This structure will select witch interrupt mode you like
 */
typedef enum{
	PRIORITY_0,
	PRIORITY_1,
	PRIORITY_2
}Int_select;

/* Definitions to set a GPIO as an Input or Output */
typedef enum{
	GPIO_INPUT,
	GPIO_OUTPUT
}GPIO_PIN_CONFIG;


/*********************************************************************
 * 																	 *
 * 							Driver APIs								 *
 * 																	 *
 *********************************************************************/

/*
 * GPIO Application Programming interface
 * Functions used to initialize and program the GPIOs
 */

/* This function is used to set a GPIO with different parameters */
void GPIO_pinControlRegister(PORT_Type *PORTx,uint8_t pin, gpio_pin_controlreg_t* gpio_pin_controlreg);

/* This function is used to select and set a pin as input or output */
void GPIO_dataDirectionPIN(GPIO_Type *GPIOx,uint8_t pin,uint32_t state);

/* This function toggles between 1 and 0 a pin */
void GPIO_togglePIN(GPIO_Type *GPIOx, uint8_t pin);

/* This function sets the selected pin as FALSE */
void GPIO_clearPIN(GPIO_Type *GPIOx, uint8_t pin);

/* This function sets the selected pin as TRUE */
void GPIO_setPIN(GPIO_Type *GPIOx, uint8_t pin);

/* This function reads the value of the selected pin */
uint8_t GPIO_readPIN(GPIO_Type *GPIOx, uint8_t pin);

/* This function reads the value of the selected PORT */
uint32_t GPIO_readPORT(GPIO_Type *GPIOx, uint8_t pin);

/* This function writes a uint8 value to a pin. */
void GPIO_writePIN(GPIO_Type *GPIOx, uint8_t pin,uint8_t val);


/*********************************************************************
 * 																	 *
 * 					(Interrupt) Driver APIs							 *
 * 																	 *
 *********************************************************************/

/*
 * GPIO Application Programming interface for interrupts
 * Functions used to initialize and program the GPIOs interruptions
 */
void GPIO_configureInterrupt(IRQn_Type irq_no,uint32_t priority);
void GPIO_clearInterrupt(PORT_Type *PORTx);

#endif /* GPIO_H_ */
