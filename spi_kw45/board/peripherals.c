/***********************************************************************************************************************
 * This file was generated by the MCUXpresso Config Tools. Any manual edits made to this file
 * will be overwritten if the respective MCUXpresso Config Tools is used to update this file.
 **********************************************************************************************************************/

/* clang-format off */
/* TEXT BELOW IS USED AS SETTING FOR TOOLS *************************************
!!GlobalInfo
product: Peripherals v14.0
processor: KW45B41Z83xxxA
package_id: KW45B41Z83AFTA
mcu_data: ksdk2_0
processor_version: 15.0.0
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
 * DMA0 initialization code
 **********************************************************************************************************************/
/* clang-format off */
/* TEXT BELOW IS USED AS SETTING FOR TOOLS *************************************
instance:
- name: 'DMA0'
- type: 'dma3'
- mode: 'general'
- custom_name_enabled: 'false'
- type_id: 'dma3_935613750389296f2fe5ef032de60db8'
- functional_group: 'BOARD_InitPeripherals'
- peripheral: 'DMA0'
- config_sets:
  - config:
    - common_settings:
      - vars: []
      - enableMasterIdReplication: 'true'
      - enableHaltOnError: 'true'
      - enableRoundRobinArbitration: 'fixedPriority'
      - enableDebugMode: 'false'
      - globalChannelLink: 'enable'
    - dma_table:
      - 0: []
      - 1: []
    - edma_channels: []
    - quick_selection: 'default'
 * BE CAREFUL MODIFYING THIS COMMENT - IT IS YAML SETTINGS FOR TOOLS **********/
/* clang-format on */
const edma_config_t DMA0_config = {
  .enableMasterIdReplication = true,
  .enableHaltOnError = true,
  .enableRoundRobinArbitration = false,
  .enableDebugMode = false
};

/* Empty initialization function (commented out)
static void DMA0_init(void) {
} */

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
- type_id: 'nvic_57b5eef3774cc60acaede6f5b8bddc67'
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
 * LPSPI0 initialization code
 **********************************************************************************************************************/
/* clang-format off */
/* TEXT BELOW IS USED AS SETTING FOR TOOLS *************************************
instance:
- name: 'LPSPI0'
- type: 'lpspi'
- mode: 'edma'
- custom_name_enabled: 'false'
- type_id: 'lpspi_6e21a1e0a09f0a012d683c4f91752db8'
- functional_group: 'BOARD_InitPeripherals'
- peripheral: 'LPSPI0'
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
      - whichPcs: 'kLPSPI_Pcs0'
      - pcsActiveHighOrLow: 'kLPSPI_PcsActiveLow'
      - pinCfg: 'kLPSPI_SdiInSdoOut'
      - dataOutConfig: 'kLpspiDataOutRetained'
      - enableInputDelay: 'false'
    - allPcsPolarityEnable: 'false'
    - allPcsPolarity:
      - kLPSPI_Pcs1Active: 'kLPSPI_PcsActiveLow'
      - kLPSPI_Pcs2Active: 'kLPSPI_PcsActiveLow'
      - kLPSPI_Pcs3Active: 'kLPSPI_PcsActiveLow'
  - edma:
    - channels:
      - enableReceive: 'true'
      - receive:
        - uid: '1714696349024'
        - eDMAn: '0'
        - eDMA_source: 'kDmaRequestLPSPI0Rx'
        - init_channel_priority: 'false'
        - edma_channel_Preemption:
          - enableChannelPreemption: 'false'
          - enablePreemptAbility: 'false'
          - arbitrationGroup: '0'
          - channelPriority: '0'
        - enable_custom_name: 'false'
      - enableTransmit: 'true'
      - transmit:
        - uid: '1714696349025'
        - eDMAn: '1'
        - eDMA_source: 'kDmaRequestLPSPI0Tx'
        - init_channel_priority: 'false'
        - edma_channel_Preemption:
          - enableChannelPreemption: 'false'
          - enablePreemptAbility: 'false'
          - arbitrationGroup: '0'
          - channelPriority: '0'
        - enable_custom_name: 'false'
    - transfer:
      - callback:
        - name: ''
        - userData: ''
    - quick_selection: 'qs_edma'
 * BE CAREFUL MODIFYING THIS COMMENT - IT IS YAML SETTINGS FOR TOOLS **********/
/* clang-format on */
const lpspi_master_config_t LPSPI0_config = {
  .baudRate = 500000UL,
  .bitsPerFrame = 8UL,
  .cpol = kLPSPI_ClockPolarityActiveHigh,
  .cpha = kLPSPI_ClockPhaseFirstEdge,
  .direction = kLPSPI_MsbFirst,
  .pcsToSckDelayInNanoSec = 1000UL,
  .lastSckToPcsDelayInNanoSec = 1000UL,
  .betweenTransferDelayInNanoSec = 1000UL,
  .whichPcs = kLPSPI_Pcs0,
  .pcsActiveHighOrLow = kLPSPI_PcsActiveLow,
  .pinCfg = kLPSPI_SdiInSdoOut,
  .dataOutConfig = kLpspiDataOutRetained,

};
edma_handle_t LPSPI0_RX_Handle;
edma_handle_t LPSPI0_TX_Handle;
lpspi_master_edma_handle_t LPSPI0_handle;

static void LPSPI0_init(void) {
  LPSPI_MasterInit(LPSPI0_PERIPHERAL, &LPSPI0_config, LPSPI0_CLOCK_FREQ);
  /* Set the kDmaRequestLPSPI0Rx request */
  EDMA_SetChannelMux(LPSPI0_RX_DMA_BASEADDR, LPSPI0_RX_DMA_CHANNEL, LPSPI0_RX_DMA_REQUEST);
  /* Set the kDmaRequestLPSPI0Tx request */
  EDMA_SetChannelMux(LPSPI0_TX_DMA_BASEADDR, LPSPI0_TX_DMA_CHANNEL, LPSPI0_TX_DMA_REQUEST);
  /* Create the eDMA LPSPI0_RX_Handle handle */
  EDMA_CreateHandle(&LPSPI0_RX_Handle, LPSPI0_RX_DMA_BASEADDR, LPSPI0_RX_DMA_CHANNEL);
  /* Create the eDMA LPSPI0_TX_Handle handle */
  EDMA_CreateHandle(&LPSPI0_TX_Handle, LPSPI0_TX_DMA_BASEADDR, LPSPI0_TX_DMA_CHANNEL);
  LPSPI_MasterTransferCreateHandleEDMA(LPSPI0_PERIPHERAL, &LPSPI0_handle, NULL, NULL, &LPSPI0_RX_Handle, &LPSPI0_TX_Handle);
}

/***********************************************************************************************************************
 * Initialization functions
 **********************************************************************************************************************/
void BOARD_InitPeripherals(void)
{
  /* Global initialization */
  EDMA_Init(DMA0_DMA_BASEADDR, &DMA0_config);

  /* Initialize components */
  LPSPI0_init();
}

/***********************************************************************************************************************
 * BOARD_InitBootPeripherals function
 **********************************************************************************************************************/
void BOARD_InitBootPeripherals(void)
{
  BOARD_InitPeripherals();
}
