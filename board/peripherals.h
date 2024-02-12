/***********************************************************************************************************************
 * This file was generated by the MCUXpresso Config Tools. Any manual edits made to this file
 * will be overwritten if the respective MCUXpresso Config Tools is used to update this file.
 **********************************************************************************************************************/

#ifndef _PERIPHERALS_H_
#define _PERIPHERALS_H_

/***********************************************************************************************************************
 * Included files
 **********************************************************************************************************************/
#include "fsl_common.h"
#include "fsl_i2c.h"
#include "fsl_lpadc.h"
#include "fsl_ctimer.h"
#include "fsl_clock.h"

#if defined(__cplusplus)
extern "C" {
#endif /* __cplusplus */

/***********************************************************************************************************************
 * Definitions
 **********************************************************************************************************************/
/* Definitions for BOARD_InitPeripherals_cm33_core0 functional group */
/* BOARD_InitPeripherals_cm33_core0 defines for FLEXCOMM1 */
/* Definition of peripheral ID */
#define FLEXCOMM1_PERIPHERAL ((I2C_Type *)FLEXCOMM1)
/* Definition of the clock source frequency */
#define FLEXCOMM1_CLOCK_SOURCE 12000000UL
/* Alias for ADC0 peripheral */
#define ADC0_PERIPHERAL ADC0
/* ADC0 interrupt vector ID (number). */
#define ADC0_IRQN ADC0_IRQn
/* ADC0 interrupt handler identifier. */
#define ADC0_IRQHANDLER ADC0_IRQHandler
/* Command 1 - First */
#define ADC0_FIRST 1U
/* Trigger 5 - First_ */
#define ADC0_FIRST_ 5U
/* Definition of peripheral ID */
#define CTIMER0_PERIPHERAL CTIMER0
/* Timer tick frequency in Hz (input frequency of the timer) */
#define CTIMER0_TICK_FREQ 96000000UL
/* Timer tick period in ns (input period of the timer) */
#define CTIMER0_TICK_PERIOD 10UL
/* Definition of PWM period channel. */
#define CTIMER0_PWM_PERIOD_CH kCTIMER_Match_0
/* Definition of channel 3 ID */
#define CTIMER0_MATCH_0_CHANNEL kCTIMER_Match_3

/***********************************************************************************************************************
 * Global variables
 **********************************************************************************************************************/
extern const i2c_master_config_t FLEXCOMM1_config;
extern const lpadc_config_t ADC0_config;
extern lpadc_conv_command_config_t ADC0_commandsConfig[1];
extern lpadc_conv_trigger_config_t ADC0_triggersConfig[1];
extern const ctimer_config_t CTIMER0_config;
extern const ctimer_match_config_t CTIMER0_Match_0_config;

/***********************************************************************************************************************
 * Initialization functions
 **********************************************************************************************************************/

void BOARD_InitPeripherals_cm33_core0(void);

/***********************************************************************************************************************
 * BOARD_InitBootPeripherals function
 **********************************************************************************************************************/
void BOARD_InitBootPeripherals(void);

#if defined(__cplusplus)
}
#endif

#endif /* _PERIPHERALS_H_ */
