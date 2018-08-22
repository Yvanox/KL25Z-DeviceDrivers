/*
 * SPI.c
 *
 *  Created on: Aug 18, 2018
 *      Author: yvanox
 */

#include "SPI.h"


/*********************************************************************
 * 																	 *
 * 						Helper Functions							 *
 * 																	 *
 *********************************************************************/

void spi_enable(SPI_Type *SPIx)
{
	if(!(SPIx->C1 & SPI_REG_C1_SPE))
		SPIx->C1 |= SPI_REG_C1_SPE;
}

void spi_disable(SPI_Type *SPIx)
{
		SPIx->C1 &= ~SPI_REG_C1_SPE;
}

void spi_phase_and_polarity(SPI_Type *SPIx, uint32_t phase, uint32_t polarity)
{
	if(phase)
	{
		SPIx->C1 |= SPI_REG_C1_CPHA;
	}
	else
	{
		SPIx->C1 &= ~SPI_REG_C1_CPHA;
	}

	if(polarity)
	{
		SPIx->C1 |= SPI_REG_C1_CPOL;
	}
	else
	{
		SPIx->C1 &= ~SPI_REG_C1_CPOL;
	}
}

void spi_device_mode(SPI_Type *SPIx, uint32_t master)
{
	if(master)
	{
		SPIx->C1 |= SPI_REG_C1_MSTR;
	}
	else
	{
		SPIx->C1 &= ~SPI_REG_C1_MSTR;
	}
}

void spi_format(SPI_Type *SPIx, uint32_t lsbfirst)
{
	if(lsbfirst)
	{
		SPIx->C1 |= SPI_REG_C1_LSBFE;
	}
	else
	{
		SPIx->C1 &= ~SPI_REG_C1_LSBFE;
	}
}

void spi_configure_MODFEN(SPI_Type *SPIx, uint32_t modfen)
{
	if(modfen)
	{
		SPIx->C2 |= SPI_REG_C2_MODFEN;
	}
	else
	{
		SPIx->C2 &= ~SPI_REG_C2_MODFEN;
	}
}

void spi_configure_SSOE(SPI_Type *SPIx, uint32_t ssoe)
{
	if(ssoe)
	{
		SPIx->C1 |= SPI_REG_C1_SSOE;
	}
	else
	{
		SPIx->C1 &= ~SPI_REG_C1_SSOE;
	}
}

void spi_configure_baudrate(SPI_Type *SPIx, uint32_t bdvalue)
{
	SPIx->BR |= bdvalue;
}

void spi_configure_preescale(SPI_Type *SPIx, uint32_t preescale)
{
	SPIx->BR |= preescale;
}

void hal_spi_configure_direction(SPI_Type *SPIx, uint32_t direction)
{
	if (direction)
	{
		SPIx->C2 |= SPI_REG_C2_SPCO;
	}
	else
	{
		SPIx->C2 &= ~SPI_REG_C2_SPCO;
	}
}

static void spi_enable_txe_interrput(SPI_Type *SPIx)
{
	SPIx->C1 |= SPI_REG_C1_SPTIE;
}

static void spi_disable_txe_interrput(SPI_Type *SPIx)
{
	SPIx->C1 &= ~SPI_REG_C1_SPTIE;
}

static void spi_tx_close_interrupt(spi_handle_t *hspi)
{
	spi_disable_txe_interrput(hspi->Instance);

	if (hspi->Init.Mode && (hspi->State != SPI_STATE_BUSY_RX))
	hspi->State = SPI_STATE_READY;

	//spi_disable(hspi->Instance);
	//spi_enable(hspi->Instance);
}

static void spi_enable_rxne_interrput(SPI_Type *SPIx)
{
	SPIx->C1 |= SPI_REG_C1_SPIE;
}

static void spi_disable_rxne_interrput(SPI_Type *SPIx)
{
	SPIx->C1 &= ~SPI_REG_C1_SPIE;
}

static void spi_rx_close_interrupt(spi_handle_t *hspi)
{

	spi_disable_rxne_interrput(hspi->Instance);
	hspi->State = SPI_STATE_READY;

	//spi_disable(hspi->Instance);
	//spi_enable(hspi->Instance);
}


/*********************************************************************
 * 																	 *
 * 							Driver APIs								 *
 * 																	 *
 *********************************************************************/

void spi_init(spi_handle_t *spi_handle)
{
	/* configure the phase and polartiy */
		spi_phase_and_polarity(spi_handle->Instance, spi_handle->Init.CLKPhase, spi_handle->Init.CLKPolarity );

		/* Configure the spi device mode */
		spi_device_mode(spi_handle->Instance, spi_handle->Init.Mode );

		/* Configure the spi data size */
		spi_format(spi_handle->Instance,spi_handle->Init.FirstBit);

		/* Configure the  SPI deivce speed */
		spi_configure_baudrate(spi_handle->Instance,spi_handle->Init.BaudRateDivider);
		spi_configure_preescale(spi_handle->Instance,spi_handle->Init.BaudRatePrescaler);

		/* Configure the SPI device direction */
		hal_spi_configure_direction(spi_handle->Instance,spi_handle->Init.Direction);
}


void spi_master_tx(spi_handle_t *spi_handle,uint8_t *buffer, uint32_t len)
{
	spi_handle->pTxBuffPtr = buffer;
	spi_handle->TxXferCount = len;
	spi_handle->TxXferSize = len;

	spi_handle->RxXferCount = 0;
	spi_handle->RxXferSize = 0 ;

	spi_handle->State = SPI_STATE_BUSY_TX;

	spi_enable(spi_handle->Instance);
	spi_enable_txe_interrput(spi_handle->Instance);
}

void spi_slave_tx(spi_handle_t *spi_handle, uint8_t *rcv_buffer, uint32_t len)
{
	/* populate the pointers and lenght information to TX the data */
	spi_handle->pTxBuffPtr   = rcv_buffer;
	spi_handle->TxXferSize   = len;
	spi_handle->TxXferCount  = len;

	/* pointers to handle dummy rx, you can reuse the same pointer */
	spi_handle->pRxBuffPtr = rcv_buffer;
	spi_handle->RxXferSize   = len;
	spi_handle->RxXferCount  = len;

	spi_handle->State = SPI_STATE_BUSY_RX;

	spi_enable(spi_handle->Instance);

	/*Enable TX and RX interrupt*/
	spi_enable_rxne_interrupt(spi_handle->Instance);
	spi_enable_txe_interrupt(spi_handle->Instance);
}

void spi_master_rx(spi_handle_t *spi_handle,uint8_t *rx_buffer, uint32_t len)
{
	uint32_t i,aux;

	/*Dummy TX*/
	spi_handle->pTxBuffPtr = rx_buffer;
	spi_handle->TxXferCount = len;
	spi_handle->TxXferSize = len;

	/*Data is RXed from the TX buffer*/
	spi_handle->pRxBuffPtr = rx_buffer;
	spi_handle->RxXferCount = len;
	spi_handle->RxXferSize = len;

	/*Driver is busy in RX*/
	spi_handle->State = SPI_STATE_BUSY_RX;

	spi_enable(spi_handle->Instance);

	/*Reads the data before interrupt so D register is empty*/
	aux = spi_handle->Instance->D;

	/*Enable TX and RX interrupt*/
	spi_enable_rxne_interrupt(spi_handle->Instance);
	spi_enable_txe_interrupt(spi_handle->Instance);

}

void spi_slave_rx(spi_handle_t *spi_handle, uint8_t *rcv_buffer, uint32_t len)
{
	spi_handle->pRxBuffPtr = rcv_buffer;
	spi_handle->RxXferCount = len;
	spi_handle->RxXferSize = len;

	spi_handle->State = SPI_STATE_BUSY_RX;

	spi_enable(spi_handle->Instance);
	spi_enable_rxne_interrput(spi_handle->Instance);
}


/*********************************************************************
 * 																	 *
 * 					(Interrupt) Driver APIs							 *
 * 																	 *
 *********************************************************************/

void spi_irq_handler(spi_handle_t *hspi)
{
	uint32_t aux1 = 0, aux2 = 0;

	aux1 = (hspi->Instance->S & SPI_REG_S_SPRF_FLAG);
	aux2 = (hspi->Instance->C1 & SPI_REG_C1_SPIE);

	if((aux1 != RESET) && (aux2 != RESET))
	{
		spi_handle_rx_interrupt(hspi);

		return;
	}

	aux1 = (hspi->Instance->S & SPI_REG_S_SPTEF_FLAG);

	if((aux1 != RESET))
	{
		spi_handle_tx_interrupt(hspi);

		return;
	}
}

void spi_handle_tx_interrupt(spi_handle_t *hspi)
{
	if(hspi->TxXferCount == 1)
	{
	hspi->Instance->D = hspi->pTxBuffPtr++;
	}

	hspi->TxXferCount--;

	if(hspi->TxXferCount == 0)
	{
		spi_tx_close_interrupt(hspi);
	}
}

void spi_handle_rx_interrupt(spi_handle_t *hspi)
{
	if(hspi->TxXferCount == 1)
	{
	(*hspi->pRxBuffPtr++) = hspi->Instance->D;
	}
	hspi->RxXferCount--;

	if(hspi->RxXferCount == 0)
	{
		spi_rx_close_interrupt(hspi);
	}
}
