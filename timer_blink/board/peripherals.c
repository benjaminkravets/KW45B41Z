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
processor_version: 15.1.0
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
 * LPIT0 initialization code
 **********************************************************************************************************************/
/* clang-format off */
/* TEXT BELOW IS USED AS SETTING FOR TOOLS *************************************
instance:
- name: 'LPIT0'
- type: 'lpit'
- mode: 'LPIT_GENERAL'
- custom_name_enabled: 'false'
- type_id: 'lpit_8e4186d834c8d9f4b6c0dadcc9dc2f05'
- functional_group: 'BOARD_InitPeripherals'
- peripheral: 'LPIT0'
- config_sets:
  - fsl_lpit:
    - lpitConfig:
      - enableRunInDebug: 'false'
      - enableRunInDoze: 'false'
    - timingConfig:
      - clockSource: 'AsyncPeripheralClock'
      - clockSourceFreq: 'ClocksTool_DefaultInit'
    - channels:
      - 0:
        - lpitChannelPrefixID: 'Channel_0'
        - channelNumber: '0'
        - enableChain: 'false'
        - timerMode: 'kLPIT_PeriodicCounter'
        - timerPeriod: '1s'
        - lpit_trigger_select_t: 'internal_trigger_0'
        - enableReloadOnTriggerBool: 'false'
        - enableStopOnTimeout: 'false'
        - enableStartOnTriggerBool: 'false'
        - startTimer: 'true'
        - enableInterrupt: 'true'
    - enableSharedInterrupt: 'true'
    - sharedInterrupt:
      - IRQn: 'LPIT0_IRQn'
      - enable_interrrupt: 'enabled'
      - enable_priority: 'false'
      - priority: '0'
      - enable_custom_name: 'false'
 * BE CAREFUL MODIFYING THIS COMMENT - IT IS YAML SETTINGS FOR TOOLS **********/
/* clang-format on */
const lpit_chnl_params_t LPIT0_Channel_0_struct = {
  .chainChannel = false,
  .timerMode = kLPIT_PeriodicCounter,
  .triggerSource = kLPIT_TriggerSource_Internal,
  .triggerSelect = kLPIT_Trigger_TimerChn0,
  .enableReloadOnTrigger = false,
  .enableStopOnTimeout = false,
  .enableStartOnTrigger = false
};
const lpit_config_t LPIT0_config = {
  .enableRunInDebug = false,
  .enableRunInDoze = false
};

static void LPIT0_init(void) {
  /* Initialize the LPIT. */
  LPIT_Init(LPIT0_PERIPHERAL, &LPIT0_config);
  /* Setup channel 0. */
  LPIT_SetupChannel(LPIT0_PERIPHERAL, LPIT0_CHANNEL_0, &LPIT0_Channel_0_struct);
  /* Set channel 0 period to 96000000 ticks. */
  LPIT_SetTimerPeriod(LPIT0_PERIPHERAL, LPIT0_CHANNEL_0, LPIT0_CHANNEL_0_TICKS);
  /* Enable interrupts from channel Channel_0. */
  LPIT_EnableInterrupts(LPIT0_PERIPHERAL, kLPIT_Channel0TimerInterruptEnable);
  /* Enable interrupt LPIT0_IRQN request in the NVIC */
  EnableIRQ(LPIT0_IRQN);
  /* Start channel 0. */
  LPIT_StartTimer(LPIT0_PERIPHERAL, LPIT0_CHANNEL_0);
}

/***********************************************************************************************************************
 * Initialization functions
 **********************************************************************************************************************/
void BOARD_InitPeripherals(void)
{
  /* Initialize components */
  LPIT0_init();
}

/***********************************************************************************************************************
 * BOARD_InitBootPeripherals function
 **********************************************************************************************************************/
void BOARD_InitBootPeripherals(void)
{
  BOARD_InitPeripherals();
}
