/**
  ******************************************************************************
  * @file    iNEMO_usb_common.c
  * @author  ART Team IMS-Systems Lab
  * @version V3.2.1
  * @date    09/20/2010
  * @brief   This file provides
  *            - set of firmware functions to manage some common iNEMO USB Functionality
  *
  * @details
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
#include "stm32f10x.h"
#include "usb_lib.h"
#include "usb_pwr.h"
#include "iNEMO_usb_common.h"


/** @addtogroup iNEMO_DFU_Program
  * @{
  */

/** @addtogroup Common
  * @{
  */

/** @addtogroup iNEMO_USB_Common
  * @{
  */

/** @defgroup iNEMO_USB_Common_Functions
  * @{
  */

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Extern variables ----------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/

/**
  * @brief  Configure USB_DISCONNECT Pin
  * @param  None
  * @retval None
  */
void iNEMO_USB_Disconnet_Pin_Config(void)
{
  GPIO_InitTypeDef GPIO_InitStructure;

  /* Enable "DISCONNECT" GPIO clock */
  RCC_APB2PeriphClockCmd(iNEMO_RCC_APB2Periph_GPIO_DISCONNECT, ENABLE);

  /* Configure USB pull-up */
  GPIO_InitStructure.GPIO_Pin = iNEMO_USB_DISCONNECT_PIN;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
  GPIO_Init(iNEMO_USB_DISCONNECT, &GPIO_InitStructure);

  USB_Cable_Config(DISABLE);
}



/**
  * @brief  Configures USB Clock input(48MHz)
  * @param  None
  * @retval None
  */
void Set_USBClock(void)
{
  /* Select USBCLK source */
  RCC_USBCLKConfig(RCC_USBCLKSource_PLLCLK_1Div5);
  
  /* Enable the USB clock */
  RCC_APB1PeriphClockCmd(RCC_APB1Periph_USB, ENABLE);
}

/**
  * @brief  Power-off system clocks and power while entering suspend mode
  * @param  None
  * @retval None
  */
void Enter_LowPowerMode(void)
{
  /* Set the device state to suspend */
  bDeviceState = SUSPENDED;
}


/**
  * @brief  Restores system clocks and power while exiting suspend mode
  * @param  None
  * @retval None
  */
void Leave_LowPowerMode(void)
{
  DEVICE_INFO *pInfo = &Device_Info;

  /* Set the device state to the correct state */
  if (pInfo->Current_Configuration != 0)
  {
    /* Device configured */
    bDeviceState = CONFIGURED;
  }
  else
  {
    bDeviceState = ATTACHED;
  }
}

/**
  * @brief  Software Connection/Disconnection of USB Cable
  * @param  NewState: new state 
  *   This parameter can be one of following parameters:
  *     @arg ENABLE
  *     @arg DISABLE
  * @retval None
  */
void USB_Cable_Config (FunctionalState NewState)
{

  if (NewState != DISABLE)
  {
    GPIO_SetBits(iNEMO_USB_DISCONNECT, iNEMO_USB_DISCONNECT_PIN);
  }
  else
  {
    GPIO_ResetBits(iNEMO_USB_DISCONNECT, iNEMO_USB_DISCONNECT_PIN);
  }

}



/**
  * @brief  Configures the USB interrupts
  * @param  None
  * @retval None
  */
void USB_Interrupts_Config(void)
{
  NVIC_InitTypeDef NVIC_InitStructure;

  NVIC_InitStructure.NVIC_IRQChannel = iNEMO_USB_IRQn;
  NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = iNEMO_USB_PREEMPTION_PRIORITY;
  NVIC_InitStructure.NVIC_IRQChannelSubPriority = iNEMO_USB_SUB_PRIORITY;
  NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
  NVIC_Init(&NVIC_InitStructure);

}

/**
  * @}
  */ /* end of group iNEMO_USB_Common_Functions */

/**
  * @}
  */ /* end of group iNEMO_USB_Common */

/**
  * @}
  */ /* end of group Common */

/**
  * @}
  */ /* end of group iNEMO_DFU_Program */

/******************* (C) COPYRIGHT 2010 STMicroelectronics *****END OF FILE****/
