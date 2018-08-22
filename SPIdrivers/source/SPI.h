/* SPI.h
 *
 *  Created on: May 12, 2018
 *      Author: yvanox
 */

#ifndef SPI_H_
#define SPI_H_

#include "MKL25Z4.h"

/*********************************************************************
 * 																	 *
 * 					SPI Register Bit Definitions					 *
 * 																	 *
 *********************************************************************/

/*****************SPI Control Register 1 (SPIx_C1)********************/

#define SPI_REG_C1_SPIE 				( (uint32_t) 1 << 7 ) /*SPI RX buffer not empty (SPRF and MODF enabled)*/
#define SPI_REG_C1_SPE					( (uint32_t) 1 << 6 ) /*SPI enable*/
#define SPI_REG_C1_SPTIE				( (uint32_t) 1 << 5 ) /*SPI TX buffer empty (SPTEF is set)*/

#define SPI_REG_C1_MSTR					( (uint32_t) 1 << 4 ) /*Master mode / Slave mode select*/
#define SPI_MASTER_MODE_SEL				1
#define SPI_SLAVE_MODE_SEL				0

#define SPI_REG_C1_CPOL					( (uint32_t) 1 << 3 )
#define SPI_CPOL_LOW					1
#define SPI_CPOL_HIGH       			0

#define SPI_REG_C1_CPHA					( (uint32_t) 1 << 2 )
#define SPI_FIRST_CLOCK_TRANS  			1
#define SPI_SECOND_CLOCK_TRANS 			0

#define SPI_REG_C1_SSOE					( (uint32_t) 1 << 1 )

#define SPI_REG_C1_LSBFE				( (uint32_t) 1 << 0 )
#define SPI_TX_MSB_FIRST        		0
#define SPI_TX_LSB_FIRST        		1


/*****************SPI Control Register 2 (SPIx_C2)********************/

#define SPI_REG_C2_SPMIE				( (uint32_t) 1 << 7 )

#define SPI_REG_C2_MODFEN				( (uint32_t) 1 << 4 )
#define SPI_MODE_FAULT_DISABLED			0
#define SPI_MODE_FAULT_ENABLED			1

#define SPI_REG_C2_BIDIROE				( (uint32_t) 1 << 3 )
#define SPI_DATA_INPUT					0
#define SPI_DATA_OUTPUT					1

#define SPI_REG_C2_SPISWAI				( (uint32_t) 1 << 1 )
#define SPI_CLK_WORKS					0
#define SPI_CLK_STOPS					1

#define SPI_REG_C2_SPCO					( (uint32_t) 1 << 0 )
#define SPI_ENABLE_2_LINE_UNI_DIR		0
#define SPI_ENABLE_1_LINE_BIDI			1


/*****************SPI Baud Rate Register (SPIx_BR)********************/

#define SPI_REG_BR_PREESCALE_1			( (uint32_t) 0 << 4 )
#define SPI_REG_BR_PREESCALE_2			( (uint32_t) 1 << 4 )
#define SPI_REG_BR_PREESCALE_3			( (uint32_t) 2 << 4 )
#define SPI_REG_BR_PREESCALE_4			( (uint32_t) 3 << 4 )
#define SPI_REG_BR_PREESCALE_5			( (uint32_t) 4 << 4 )
#define SPI_REG_BR_PREESCALE_6			( (uint32_t) 5 << 4 )
#define SPI_REG_BR_PREESCALE_7			( (uint32_t) 6 << 4 )
#define SPI_REG_BR_PREESCALE_8			( (uint32_t) 7 << 4 )

#define SPI_REG_BR_BAUDRATE_DIV_2		( (uint32_t) 0 << 0 )
#define SPI_REG_BR_BAUDRATE_DIV_4		( (uint32_t) 1 << 0 )
#define SPI_REG_BR_BAUDRATE_DIV_8		( (uint32_t) 2 << 0 )
#define SPI_REG_BR_BAUDRATE_DIV_16		( (uint32_t) 3 << 0 )
#define SPI_REG_BR_BAUDRATE_DIV_32		( (uint32_t) 4 << 0 )
#define SPI_REG_BR_BAUDRATE_DIV_64		( (uint32_t) 5 << 0 )
#define SPI_REG_BR_BAUDRATE_DIV_128		( (uint32_t) 6 << 0 )
#define SPI_REG_BR_BAUDRATE_DIV_256		( (uint32_t) 7 << 0 )
#define SPI_REG_BR_BAUDRATE_DIV_512		( (uint32_t) 8 << 0 )


/*****************SPI Status Register (SPIx_S)***********************/

#define SPI_REG_S_SPRF_FLAG				( (uint32_t) 1 << 7 )
#define SPI_REG_S_SPMF_FLAG				( (uint32_t) 1 << 6 )
#define SPI_REG_S_SPTEF_FLAG			( (uint32_t) 1 << 5 )
#define SPI_REG_S_MODF_FLAG				( (uint32_t) 1 << 4 )


/* SPI device base address */
#define SPI_0 SPI0
#define SPI_1 SPI1

#define SPI_IS_BUSY 1
#define SPI_IS_NOT_BUSY 0


/*****************SPI Clock Enable***********************/

#define _SPI0_CLK_GATING() (SIM->SCGC4 |= (1<< 22))
#define _SPI1_CLK_GATING() (SIM->SCGC4 |= (1<< 23))

#define  RESET  0
#define  SET  !RESET


/******************************************************************************
 *                                                                            *
 *                      2. Data Structures used by SPI Driver                 *
 *                                                                            *
 ******************************************************************************/


/***********HAL SPI State structure definition********************/

typedef enum
{
  SPI_STATE_RESET      = 0x00,  /*  SPI not yet initialized or disabled                */
  SPI_STATE_READY      = 0x01,  /*  SPI initialized and ready for use                  */
  SPI_STATE_BUSY       = 0x02,  /*  SPI process is ongoing                             */
  SPI_STATE_BUSY_TX    = 0x12,  /*  Data Transmission process is ongoing               */
  SPI_STATE_BUSY_RX    = 0x22,  /*  Data Reception process is ongoing                  */
  SPI_STATE_BUSY_TX_RX = 0x32,  /*  Data Transmission and Reception process is ongoing */
  SPI_STATE_ERROR      = 0x03   /*  SPI error state                                    */
}hal_spi_state_t;


/************SPI Configuration Structure definition************/

typedef struct
{
  uint32_t Mode;               /*  Specifies the SPI operating mode. */


  uint32_t Direction;          /*  Specifies the SPI Directional mode state. */

  uint32_t DataSize;           /*  Specifies the SPI data size. */


  uint32_t CLKPolarity;        /*  Specifies the serial clock steady state. */


  uint32_t CLKPhase;           /*  Specifies the clock active edge for the bit capture. */


  uint32_t BaudRatePrescaler;  /*  Specifies the Baud Rate prescaler value which will be
                                    used to configure the transmit and receive SCK clock. */

  uint32_t BaudRateDivider;  /*  Specifies the Baud Rate divider value which will be
                                     used to configure the transmit and receive SCK clock. */


  uint32_t FirstBit;           /*  Specifies whether data transfers start from MSB or LSB bit. */

}spi_init_t;


/*************SPI handle Structure definition**************/

typedef struct __spi_handle_t
{
  SPI_Type	                 *Instance;       /* SPI registers base address */

  spi_init_t                   Init;          /* SPI communication parameters */

  uint8_t                    *pTxBuffPtr;     /* Pointer to SPI Tx transfer Buffer */

  uint16_t                   TxXferSize;      /* SPI Tx transfer size */

  uint16_t                   TxXferCount;     /* SPI Tx Transfer Counter */

  uint8_t                    *pRxBuffPtr;     /* Pointer to SPI Rx transfer Buffer */

  uint16_t                   RxXferSize;      /* SPI Rx transfer size */

  uint16_t                   RxXferCount;     /* SPI Rx Transfer Counter */

  hal_spi_state_t  				State;                     /* SPI communication state */

}spi_handle_t;


/*********************************************************************
 * 																	 *
 * 							Driver APIs								 *
 * 																	 *
 *********************************************************************/

/*API used to do initialize the given SPI device*/
void spi_init(spi_handle_t *spi_handle);

/*API used to do master data transmission*/
void spi_master_tx(spi_handle_t *spi_handle,uint8_t *buffer, uint32_t len);

/*API used to do slave data transmission*/
void spi_slave_tx(spi_handle_t *spi_handle, uint8_t *rcv_buffer, uint32_t len);

/*API used to do master data reception*/
void spi_master_rx(spi_handle_t *spi_handle,uint8_t *rx_buffer, uint32_t len);

/*API used to do slave data reception*/
void spi_slave_rx(spi_handle_t *spi_handle, uint8_t *rcv_buffer, uint32_t len);


/*********************************************************************
 * 																	 *
 * 					(Interrupt) Driver APIs							 *
 * 																	 *
 *********************************************************************/

/*This function handles SPI interrupt request*/
void spi_irq_handler(spi_handle_t *hspi);

#endif
