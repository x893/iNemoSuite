/**
  * @file    iNEMO_Button.c
  * @author  ART Team IMS-Systems Lab
  * @version V2.2
  * @date    01/11/2011
  * @brief   This file provides a set of functions to manage iNEMO push-buttons
  * @details
  *
  * THE PRESENT FIRMWARE WHICH IS FOR GUIDANCE ONLY AIMS AT PROVIDING CUSTOMERS
  * WITH CODING INFORMATION REGARDING THEIR PRODUCTS IN ORDER FOR THEM TO SAVE
  * TIME. AS A RESULT, STMICROELECTRONICS SHALL NOT BE HELD LIABLE FOR ANY
  * DIRECT, INDIRECT OR CONSEQUENTIAL DAMAGES WITH RESPECT TO ANY CLAIMS ARISING
  * FROM THE CONTENT OF SUCH FIRMWARE AND/OR THE USE MADE BY CUSTOMERS OF THE
  * CODING INFORMATION CONTAINED HEREIN IN CONNECTION WITH THEIR PRODUCTS.
  *
  * THIS SOURCE CODE IS PROTECTED BY A LICENSE.
  * FOR MORE INFORMATION PLEASE CAREFULLY READ THE LICENSE AGREEMENT FILE LOCATED
  * IN THE ROOT DIRECTORY OF THIS FIRMWARE PACKAGE.
  *
  * <h2><center>&copy; COPYRIGHT 2010 STMicroelectronics</center></h2>
  */




/* Includes ------------------------------------------------------------------*/
#include "iNEMO_Button.h"




/** @addtogroup iNEMO_Button
  * @{
  */

/** @defgroup iNEMO_Button_Functions
  * @{
  */

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
GPIO_TypeDef* BUTTON_PORT[iNEMO_BUTTONn] = {iNEMO_KEY_BUTTON_GPIO_PORT}; 

const uint16_t BUTTON_PIN[iNEMO_BUTTONn] = {iNEMO_KEY_BUTTON_PIN}; 

const uint32_t BUTTON_CLK[iNEMO_BUTTONn] = {iNEMO_KEY_BUTTON_GPIO_CLK};

const uint16_t BUTTON_EXTI_LINE[iNEMO_BUTTONn] = {iNEMO_KEY_BUTTON_EXTI_LINE};

const uint16_t BUTTON_PORT_SOURCE[iNEMO_BUTTONn] = {iNEMO_KEY_BUTTON_EXTI_PORT_SOURCE};
								 
const uint16_t BUTTON_PIN_SOURCE[iNEMO_BUTTONn] = {iNEMO_KEY_BUTTON_EXTI_PIN_SOURCE}; 

const uint16_t BUTTON_IRQn[iNEMO_BUTTONn] = {iNEMO_KEY_BUTTON_EXTI_IRQn};

const EXTITrigger_TypeDef BUTTON_EDGE[iNEMO_BUTTONn] = {iNEMO_KEY_BUTTON_EDGE};

const uint16_t BUTTON_PREEMPTION[iNEMO_BUTTONn] = {iNEMO_KEY_BUTTON_EXTI_PREEMPTION_PRIORITY};

const uint16_t BUTTON_SUBPRIORITY[iNEMO_BUTTONn] = {iNEMO_KEY_BUTTON_EXTI_SUB_PRIORITY};


/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/

/**
  * @brief  Configures Button GPIO and EXTI Line.
  * @param  Button: Specifies the Button to be configured.
  *   This parameter can be one of following parameters:   
  *     @arg BUTTON_KEY: Key Push Button 
  * @param  Button_Mode: Specifies Button mode.
  *   This parameter can be one of following parameters:   
  *     @arg BUTTON_MODE_GPIO: Button will be used as simple IO 
  *     @arg BUTTON_MODE_EXTI: Button will be connected to EXTI line with interrupt
  *                     generation capability  
  * @retval None
  */

void iNEMO_Button_Init(Button_TypeDef Button, ButtonMode_TypeDef Button_Mode)
{

  EXTI_InitTypeDef EXTI_InitStructure;
  GPIO_InitTypeDef GPIO_InitStructure;

  /* Enable Push Button GPIO clocks */
  RCC_APB2PeriphClockCmd(BUTTON_CLK[Button], ENABLE);
  
  /* Configure Push Button pin as input floating */
  GPIO_InitStructure.GPIO_Pin = BUTTON_PIN[Button];
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
  GPIO_Init(BUTTON_PORT[Button], &GPIO_InitStructure);

  if (Button_Mode == BUTTON_MODE_EXTI)   
  {
    /* Connect Button EXTI Line to Button GPIO Pin */
    GPIO_EXTILineConfig(BUTTON_PORT_SOURCE[Button], BUTTON_PIN_SOURCE[Button]);
    
    /* Configure Button EXTI line */ 
    EXTI_InitStructure.EXTI_Line = BUTTON_EXTI_LINE[Button];
    EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;
    EXTI_InitStructure.EXTI_Trigger = BUTTON_EDGE[Button];
    EXTI_InitStructure.EXTI_LineCmd = ENABLE;
    EXTI_Init(&EXTI_InitStructure);
  }
  
}



/**
  * @brief  Enables or disables the button interrupt.
  * @param  Button: Specifies the Button to be configured.
  *   This parameter can be one of following parameters:   
  *     @arg BUTTON_KEY: Key Push Button 
  * @param New State: Specifies the State.
  *   This parameter can be one of following parameters:   
  *     @arg ENABLE: Button interrupt is enabled 
  *     @arg DISABLE: Button interrupt is disabled  
  * @retval None
  */

void iNEMO_Button_Interrupt_Cmd(Button_TypeDef Button, FunctionalState NewState)
{
  NVIC_InitTypeDef NVIC_InitStructure;
  
  /* Enable and set Button EXTI Interrupt priority */
  NVIC_InitStructure.NVIC_IRQChannel = BUTTON_IRQn[Button];
  NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = BUTTON_PREEMPTION[Button];
  NVIC_InitStructure.NVIC_IRQChannelSubPriority = BUTTON_SUBPRIORITY[Button];
  NVIC_InitStructure.NVIC_IRQChannelCmd = NewState;
  NVIC_Init(&NVIC_InitStructure);
  
}



/**
  * @brief  Returns the selected Button state.
  * @param  Button: Specifies the Button to be checked.
  *   This parameter can be one of following parameters:    
  *     @arg BUTTON_KEY: Key Push Button  
  * @retval The Button GPIO pin value.
  */
uint32_t iNEMO_Button_Get_State(Button_TypeDef Button)
{
  return GPIO_ReadInputDataBit(BUTTON_PORT[Button], BUTTON_PIN[Button]);
}


/**
  * @}
  */ /* end of group iNEMO_Button_Functions */

/**
  * @}
  */ /* end of group iNEMO_Button */





/******************* (C) COPYRIGHT 2010 STMicroelectronics *****END OF FILE****/
