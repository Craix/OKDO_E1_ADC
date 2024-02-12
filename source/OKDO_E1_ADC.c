#include <stdio.h>

#include "board.h"
#include "peripherals.h"
#include "pin_mux.h"
#include "clock_config.h"
#include "LPC55S69_cm33_core0.h"
#include "fsl_debug_console.h"
#include "fsl_power.h"
#include "oled.h"

#define I2C_OLED ((I2C_Type *)I2C1_BASE)

#define BARPOS1 16
#define BARPOS2 24
#define BARSIZE 128

#define BARMODE PB_CENTER

char sbuff[32];

lpadc_conv_result_t g_LpadcResultConfigStruct;
uint16_t adcCh1, adcCh2;

float Xval, Yval;

/* ADC0_IRQn interrupt handler */
void ADC0_IRQHANDLER(void)
{

	LPADC_GetConvResult(ADC0, &g_LpadcResultConfigStruct, 0U);
	adcCh1=g_LpadcResultConfigStruct.convValue;

	LPADC_GetConvResult(ADC0, &g_LpadcResultConfigStruct, 0U);
	adcCh2=g_LpadcResultConfigStruct.convValue;
}

void PowerControl(float X, float Y)
{
	Yval = X - Y;
	Xval = -(X + Y);
}

/*
 * @brief Application entry point.
 */

int main(void)
{
	/* Disable LDOGPADC power down */
	POWER_DisablePD(kPDRUNCFG_PD_LDOGPADC);

	/* Init board hardware. */
	BOARD_InitBootPins();
	BOARD_InitBootClocks();
	BOARD_InitBootPeripherals();

	#ifndef BOARD_INIT_DEBUG_CONSOLE_PERIPHERAL
	/* Init FSL debug console. */
	BOARD_InitDebugConsole();
	#endif

	/* Initialize OLED */
	OLED_Init(I2C_OLED);
	OLED_Progressbar_Frame(0, BARPOS1, BARSIZE, BARMODE);
	OLED_Progressbar_Frame(0, BARPOS2, BARSIZE, BARMODE);

	while(1)
	{
		Xval = (adcCh1/32768.0)-1;
		Yval = (adcCh2/32768.0)-1;

		Xval = ((int)(Xval *100))/100.0;
		Yval = ((int)(Yval *100))/100.0;

		sprintf(sbuff, "X:%5.2f Y:%5.2f", Xval, Yval);

		PowerControl(Xval, Yval);

		OLED_Puts(0, 0, sbuff);
		OLED_Progressbar_Value(0, BARPOS1, BARSIZE, BARMODE, Xval);
		OLED_Progressbar_Value(0, BARPOS2, BARSIZE, BARMODE, Yval);
		OLED_Refresh_Gram();
	}

	return 0 ;
}
