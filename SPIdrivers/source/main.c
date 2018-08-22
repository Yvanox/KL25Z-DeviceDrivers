/**/
#include "MKL25Z4.h"
#include "GPIO.h"
#include "SPI.h"
#include "DataTypeDef.h"

spi_handle_t spi_config;

void spi_gpio_init();
void spi_init_f();

void SPI0_IRQHandler()
{
	spi_irq_handler(&spi_config);
}

int main(void) {

	spi_gpio_init();
	spi_init_f();

	int i=1;

    while(1)
    {
    	while(spi_config.State != SPI_STATE_READY );

    	spi_master_tx(&spi_config, 0x21,1);
    	spi_master_tx(&spi_config, 0x22,1);
    	spi_master_tx(&spi_config, 0x23,1);
    	spi_master_tx(&spi_config, 0x24,1);

    	while(spi_config.State != SPI_STATE_READY );
    }
    return 0 ;
}

void spi_gpio_init()
{
	gpio_pin_controlreg_t spi_pin_controlreg;

	_GPIOD_CLK_GATING();

	/*Pin configuration options for the SPI*/
	spi_pin_controlreg.ps = NULL;
	spi_pin_controlreg.pe = NULL;
	spi_pin_controlreg.sre = NULL;
	spi_pin_controlreg.filter = NULL;
	spi_pin_controlreg.strength = NULL;
	spi_pin_controlreg.mux = GPIO_MUX2;
	spi_pin_controlreg.irq = NULL;
	spi_pin_controlreg.isf = NULL;

	/*This sets up the SPI pin configurations*/
	GPIO_pinControlRegister(PORTD,SPI_CLK,&spi_pin_controlreg);
	GPIO_pinControlRegister(PORTD,SPI_MOSI,&spi_pin_controlreg);
}

void spi_init_f()
{

	_SPI0_CLK_GATING();

	spi_config.Instance = SPI_0;
	spi_config.Init.BaudRateDivider = SPI_REG_BR_BAUDRATE_DIV_2;
	spi_config.Init.BaudRatePrescaler = SPI_REG_BR_PREESCALE_1;
	spi_config.Init.Direction = SPI_ENABLE_2_LINE_UNI_DIR;
	spi_config.Init.CLKPhase = SPI_SECOND_CLOCK_TRANS;
	spi_config.Init.CLKPolarity = SPI_CPOL_HIGH;
	spi_config.Init.FirstBit = SPI_TX_MSB_FIRST;
	spi_config.Init.Mode = SPI_MASTER_MODE_SEL;

	spi_config.State = SPI_STATE_READY;

	spi_init(&spi_config);
	NVIC_EnableIRQ (SPI0_IRQn);
}
