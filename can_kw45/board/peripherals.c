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
    - interrupt_table:
      - 0: []
    - interrupts: []
 * BE CAREFUL MODIFYING THIS COMMENT - IT IS YAML SETTINGS FOR TOOLS **********/
/* clang-format on */

/* Empty initialization function (commented out)
static void NVIC_init(void) {
} */

/***********************************************************************************************************************
 * CAN0 initialization code
 **********************************************************************************************************************/
/* clang-format off */
/* TEXT BELOW IS USED AS SETTING FOR TOOLS *************************************
instance:
- name: 'CAN0'
- type: 'flexcan'
- mode: 'interrupts'
- custom_name_enabled: 'false'
- type_id: 'flexcan_5cab76b676858377b40de2b864152fd8'
- functional_group: 'BOARD_InitPeripherals'
- peripheral: 'CAN0'
- config_sets:
  - interruptsCfg:
    - messageBufferIrqs: '0'
    - interruptsEnable: ''
    - enable_irq: 'true'
    - interrupt_shared:
      - IRQn: 'CAN0_IRQn'
      - enable_interrrupt: 'enabled'
      - enable_priority: 'false'
      - priority: '2'
      - enable_custom_name: 'false'
  - fsl_flexcan:
    - can_config:
      - clockSource: 'kFLEXCAN_ClkSrcOsc'
      - clockSourceFreq: 'ClocksTool_DefaultInit'
      - wakeupSrc: 'kFLEXCAN_WakeupSrcFiltered'
      - flexibleDataRate: 'false'
      - baudRate: '500000'
      - baudRateFD: '2000000'
      - enableBRS: 'false'
      - dataSize: 'kFLEXCAN_8BperMB'
      - maxMbNum: '16'
      - enableLoopBack: 'false'
      - enableTimerSync: 'true'
      - enableSelfWakeup: 'false'
      - enableIndividMask: 'false'
      - disableSelfReception: 'false'
      - enableListenOnlyMode: 'false'
      - enableDoze: 'false'
      - enableTransceiverDelayMeasure: 'true'
      - timingConfig:
        - phaseSeg1: '7'
        - phaseSeg2: '7'
        - rJumpwidth: '2'
        - bitTime: []
        - fphaseSeg1: '4'
        - fphaseSeg2: '4'
        - frJumpwidth: '2'
        - fbitTime: []
    - enableRxFifoDMA: 'false'
    - enableRxFIFO: 'false'
    - rxFIFO:
      - idFilterTable: ''
      - idFilterNum: 'num0'
      - idFilterType: 'kFLEXCAN_RxFifoFilterTypeA'
      - priority: 'kFLEXCAN_RxFifoPrioLow'
    - enableEnhancedRxFIFO: 'false'
    - enhancedRxFIFO:
      - idFilterTable: ''
      - idFilterPairNum: '2'
      - extendIdFilterNum: '0'
      - fifoWatermarkSelection: '1'
      - dmaPerReadLength: 'kFLEXCAN_1WordPerRead'
      - priority: 'kFLEXCAN_RxFifoPrioLow'
    - channels:
      - 0:
        - mbID: '0'
        - mbType: 'mbRx'
        - rxMb:
          - id: '0'
          - format: 'kFLEXCAN_FrameFormatStandard'
          - type: 'kFLEXCAN_FrameTypeData'
      - 1:
        - mbID: '1'
        - mbType: 'mbTx'
        - rxMb:
          - id: '0'
          - format: 'kFLEXCAN_FrameFormatStandard'
          - type: 'kFLEXCAN_FrameTypeData'
    - enablePNConfig: 'false'
    - pn_config:
      - enableTimeout: 'false'
      - inputTimeoutValue: '0'
      - enableMatch: 'false'
      - matchSrc: 'kFLEXCAN_PNMatSrcID'
      - matchNum: '1'
      - idMatchMode: 'kFLEXCAN_PNMatModeEqual'
      - dataMatchMode: 'kFLEXCAN_PNMatModeEqual'
      - idFilterIDE: 'kFLEXCAN_FrameFormatStandard'
      - idFilterRTR: 'kFLEXCAN_DataFrameType'
      - idLowerValue: '0'
      - idUpperValue: '0'
      - lengthLower: '0'
      - lengthUpper: '0'
      - payloadLower:
        - 0:
          - byte: '0'
        - 1:
          - byte: '0'
        - 2:
          - byte: '0'
        - 3:
          - byte: '0'
        - 4:
          - byte: '0'
        - 5:
          - byte: '0'
        - 6:
          - byte: '0'
        - 7:
          - byte: '0'
      - payloadUpper:
        - 0:
          - byte: '0'
        - 1:
          - byte: '0'
        - 2:
          - byte: '0'
        - 3:
          - byte: '0'
        - 4:
          - byte: '0'
        - 5:
          - byte: '0'
        - 6:
          - byte: '0'
        - 7:
          - byte: '0'
 * BE CAREFUL MODIFYING THIS COMMENT - IT IS YAML SETTINGS FOR TOOLS **********/
/* clang-format on */
const flexcan_config_t CAN0_config = {
  .wakeupSrc = kFLEXCAN_WakeupSrcFiltered,
  .bitRate = 500000UL,
  .bitRateFD = 2000000UL,
  .maxMbNum = 16U,
  .enableLoopBack = false,
  .enableTimerSync = true,
  .enableSelfWakeup = false,
  .enableIndividMask = false,
  .disableSelfReception = false,
  .enableListenOnlyMode = false,
  .enableDoze = false,
  .enablePretendedeNetworking = false,
  .enableTransceiverDelayMeasure = true,
  .timingConfig = {
    .preDivider = 3,
    .propSeg = 0,
    .phaseSeg1 = 6,
    .phaseSeg2 = 6,
    .rJumpwidth = 1,
    .fpropSeg = 0,
  }
};
/* Message buffer 0 configuration structure */
const flexcan_rx_mb_config_t CAN0_rx_mb_config_0 = {
  .id = FLEXCAN_ID_STD(0UL),
  .format = kFLEXCAN_FrameFormatStandard,
  .type = kFLEXCAN_FrameTypeData
};

static void CAN0_init(void) {
  FLEXCAN_Init(CAN0_PERIPHERAL, &CAN0_config, CAN0_CLOCK_SOURCE);
  /* Message buffer 0 initialization */
  FLEXCAN_SetRxMbConfig(CAN0_PERIPHERAL, 0, &CAN0_rx_mb_config_0, true);
  /* Message buffer 1 initialization */
  FLEXCAN_SetTxMbConfig(CAN0_PERIPHERAL, 1, true);
  /* Enable interrupt CAN0_IRQn request in the NVIC. */
  EnableIRQ(CAN0_FLEXCAN_IRQN);
}

/***********************************************************************************************************************
 * Initialization functions
 **********************************************************************************************************************/
void BOARD_InitPeripherals(void)
{
  /* Initialize components */
  CAN0_init();
}

/***********************************************************************************************************************
 * BOARD_InitBootPeripherals function
 **********************************************************************************************************************/
void BOARD_InitBootPeripherals(void)
{
  BOARD_InitPeripherals();
}
