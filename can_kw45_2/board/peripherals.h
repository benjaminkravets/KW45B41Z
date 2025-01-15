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
#include "fsl_lpuart.h"
#include "fsl_clock.h"
#include "fsl_flexcan.h"
#include "fsl_lpit.h"

#if defined(__cplusplus)
extern "C" {
#endif /* __cplusplus */

/***********************************************************************************************************************
 * Definitions
 **********************************************************************************************************************/
/* Definitions for BOARD_InitPeripherals functional group */
/* Definition of peripheral ID */
#define LPUART0_PERIPHERAL LPUART0
/* Definition of the clock source frequency */
#define LPUART0_CLOCK_SOURCE 16000000UL
/* LPUART0 interrupt vector ID (number). */
#define LPUART0_SERIAL_RX_TX_IRQN LPUART0_IRQn
/* LPUART0 interrupt handler identifier. */
#define LPUART0_SERIAL_RX_TX_IRQHANDLER LPUART0_IRQHandler
/* Definition of peripheral ID */
#define CAN0_PERIPHERAL CAN0
/* Definition of the clock source frequency */
#define CAN0_CLOCK_SOURCE 32000000UL
/* BOARD_InitPeripherals defines for LPIT0 */
/* Definition of peripheral ID. */
#define LPIT0_PERIPHERAL LPIT0
/* Definition of clock source frequency. */
#define LPIT0_CLK_FREQ 6000000UL
/* Definition of ticks count for channel Channel_0. */
#define LPIT0_CHANNEL_0_TICKS 5999999U
/* Definition of channel kLPIT_Chnl_0 ID */
#define LPIT0_CHANNEL_0 kLPIT_Chnl_0

/***********************************************************************************************************************
 * Global variables
 **********************************************************************************************************************/
extern const lpuart_config_t LPUART0_config;
extern const flexcan_config_t CAN0_config;
/* Message buffer 0 configuration structure */
extern const flexcan_rx_mb_config_t CAN0_rx_mb_config_0;
extern flexcan_enhanced_rx_fifo_config_t CAN0_enhanced_rx_fifo_config;
extern void * EnRxTableId;
extern const lpit_config_t LPIT0_config;
extern const lpit_chnl_params_t LPIT0_Channel_0_struct;

/***********************************************************************************************************************
 * Initialization functions
 **********************************************************************************************************************/

void BOARD_InitPeripherals(void);

/***********************************************************************************************************************
 * BOARD_InitBootPeripherals function
 **********************************************************************************************************************/
void BOARD_InitBootPeripherals(void);

#if defined(__cplusplus)
}
#endif

#endif /* _PERIPHERALS_H_ */
