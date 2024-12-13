/***********************************************************************************************************************
 * This file was generated by the MCUXpresso Config Tools. Any manual edits made to this file
 * will be overwritten if the respective MCUXpresso Config Tools is used to update this file.
 **********************************************************************************************************************/

/* clang-format off */
/* TEXT BELOW IS USED AS SETTING FOR TOOLS *************************************
!!GlobalInfo
product: Peripherals v15.0
processor: KW45B41Z83xxxA
package_id: KW45B41Z83AFTA
mcu_data: ksdk2_0
processor_version: 16.3.0
board: KW45B41Z-EVK
functionalGroups:
- name: BOARD_InitPeripherals
  UUID: b82e970b-aefd-4c28-bb14-af73e85818df
  called_from_default_init: true
  selectedCore: cm33
 * BE CAREFUL MODIFYING THIS COMMENT - IT IS YAML SETTINGS FOR TOOLS **********/

/* TEXT BELOW IS USED AS SETTING FOR TOOLS *************************************
component:
- type: 'system'
- type_id: 'system_54b53072540eeeb8f8e9343e71f28176'
- global_system_definitions:
  - user_definitions: ''
  - user_includes: ''
  - global_init: ''
 * BE CAREFUL MODIFYING THIS COMMENT - IT IS YAML SETTINGS FOR TOOLS **********/

/* TEXT BELOW IS USED AS SETTING FOR TOOLS *************************************
component:
- type: 'uart_cmsis_common'
- type_id: 'uart_cmsis_common_9cb8e302497aa696fdbb5a4fd622c2a8'
- global_USART_CMSIS_common:
  - quick_selection: 'default'
 * BE CAREFUL MODIFYING THIS COMMENT - IT IS YAML SETTINGS FOR TOOLS **********/

/* TEXT BELOW IS USED AS SETTING FOR TOOLS *************************************
component:
- type: 'gpio_adapter_common'
- type_id: 'gpio_adapter_common_57579b9ac814fe26bf95df0a384c36b6'
- global_gpio_adapter_common:
  - quick_selection: 'default'
 * BE CAREFUL MODIFYING THIS COMMENT - IT IS YAML SETTINGS FOR TOOLS **********/
/* clang-format on */

/***********************************************************************************************************************
 * Included files
 **********************************************************************************************************************/
#include "peripherals.h"

/***********************************************************************************************************************
 * BOARD_InitPeripherals functional group
 **********************************************************************************************************************/
/***********************************************************************************************************************
 * NVIC initialization code
 **********************************************************************************************************************/
/* clang-format off */
/* TEXT BELOW IS USED AS SETTING FOR TOOLS *************************************
instance:
- name: 'NVIC'
- type: 'nvic'
- mode: 'general'
- custom_name_enabled: 'false'
- type_id: 'nvic'
- functional_group: 'BOARD_InitPeripherals'
- peripheral: 'NVIC'
- config_sets:
  - nvic:
    - interrupt_table: []
    - interrupts: []
 * BE CAREFUL MODIFYING THIS COMMENT - IT IS YAML SETTINGS FOR TOOLS **********/
/* clang-format on */

/* Empty initialization function (commented out)
static void NVIC_init(void) {
} */

/***********************************************************************************************************************
 * LPSPI1 initialization code
 **********************************************************************************************************************/
/* clang-format off */
/* TEXT BELOW IS USED AS SETTING FOR TOOLS *************************************
instance:
- name: 'LPSPI1'
- type: 'lpspi'
- mode: 'polling'
- custom_name_enabled: 'false'
- type_id: 'lpspi_2.6.0'
- functional_group: 'BOARD_InitPeripherals'
- peripheral: 'LPSPI1'
- config_sets:
  - main:
    - mode: 'kLPSPI_Master'
    - clockSource: 'LpspiClock'
    - clockSourceFreq: 'GetIpFreq'
    - master:
      - baudRate: '500000'
      - bitsPerFrame: '8'
      - cpol: 'kLPSPI_ClockPolarityActiveHigh'
      - cpha: 'kLPSPI_ClockPhaseFirstEdge'
      - direction: 'kLPSPI_MsbFirst'
      - pcsToSckDelayInNanoSec: '1000'
      - lastSckToPcsDelayInNanoSec: '1000'
      - betweenTransferDelayInNanoSec: '1000'
      - whichPcs: 'kLPSPI_Pcs3'
      - pcsActiveHighOrLow: 'kLPSPI_PcsActiveLow'
      - pinCfg: 'kLPSPI_SdiInSdoOut'
      - pcsFunc: 'kLPSPI_PcsAsCs'
      - dataOutConfig: 'kLpspiDataOutRetained'
      - enableInputDelay: 'false'
    - set_FifoWaterMarks: 'false'
    - fifoWaterMarks:
      - txWatermark: '0'
      - rxWatermark: '0'
    - allPcsPolarityEnable: 'false'
    - allPcsPolarity:
      - kLPSPI_Pcs0Active: 'kLPSPI_PcsActiveLow'
      - kLPSPI_Pcs1Active: 'kLPSPI_PcsActiveLow'
      - kLPSPI_Pcs2Active: 'kLPSPI_PcsActiveLow'
 * BE CAREFUL MODIFYING THIS COMMENT - IT IS YAML SETTINGS FOR TOOLS **********/
/* clang-format on */
const lpspi_master_config_t LPSPI1_config = {
  .baudRate = 500000UL,
  .bitsPerFrame = 8UL,
  .cpol = kLPSPI_ClockPolarityActiveHigh,
  .cpha = kLPSPI_ClockPhaseFirstEdge,
  .direction = kLPSPI_MsbFirst,
  .pcsToSckDelayInNanoSec = 1000UL,
  .lastSckToPcsDelayInNanoSec = 1000UL,
  .betweenTransferDelayInNanoSec = 1000UL,
  .whichPcs = kLPSPI_Pcs3,
  .pcsActiveHighOrLow = kLPSPI_PcsActiveLow,
  .pinCfg = kLPSPI_SdiInSdoOut,
  .pcsFunc = kLPSPI_PcsAsCs,
  .dataOutConfig = kLpspiDataOutRetained,
  .enableInputDelay = false
};

static void LPSPI1_init(void) {
  LPSPI_MasterInit(LPSPI1_PERIPHERAL, &LPSPI1_config, LPSPI1_CLOCK_FREQ);
}

/***********************************************************************************************************************
 * Initialization functions
 **********************************************************************************************************************/
void BOARD_InitPeripherals(void)
{
  /* Initialize components */
  LPSPI1_init();
}

/***********************************************************************************************************************
 * BOARD_InitBootPeripherals function
 **********************************************************************************************************************/
void BOARD_InitBootPeripherals(void)
{
  BOARD_InitPeripherals();
}
