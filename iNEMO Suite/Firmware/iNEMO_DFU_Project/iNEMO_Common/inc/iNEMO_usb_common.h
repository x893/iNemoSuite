/**
*
* @file    iNEMO_usb_common.h
* @author  ART Team IMS-Systems Lab
* @version V3.2.1
* @date    09/20/2010
* @brief   iNEMO USB Common Hardware Configuration & Setup.
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
*
*/
/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __INEMO_USB_COMMON_H
#define __INEMO_USB_COMMON_H

/* Includes ------------------------------------------------------------------*/
#include "stm32f10x.h"

/** @addtogroup iNEMO_DFU_Program
  * @{
  */

/** @addtogroup Common
  * @{
  */

/** @defgroup iNEMO_USB_Common
  * @{
  */

/** @defgroup iNEMO_USB_Common_Prototypes
  * @{
  */


/* Exported types ------------------------------------------------------------*/
/* Exported constants --------------------------------------------------------*/

/* Define the USB Disconnect Pin*/
#define iNEMO_USB_DISCONNECT                      GPIOA  
#define iNEMO_USB_DISCONNECT_PIN                  GPIO_Pin_10
#define iNEMO_RCC_APB2Periph_GPIO_DISCONNECT      RCC_APB2Periph_GPIOA


#define iNEMO_USB_IRQn                    USB_LP_CAN1_RX0_IRQn
#define iNEMO_USB_PREEMPTION_PRIORITY     14
#define iNEMO_USB_SUB_PRIORITY            0

/* Exported macro ------------------------------------------------------------*/
/* Exported functions ------------------------------------------------------- */
void Set_USBClock(void);
void Enter_LowPowerMode(void);
void Leave_LowPowerMode(void);
void iNEMO_USB_Disconnet_Pin_Config(void);
void USB_Cable_Config (FunctionalState NewState);
void USB_Interrupts_Config(void);
void Reset_Device(void);
void Get_SerialNum(void);

/**
  * @}
  */ /* end of group iNEMO_USB_Common_Prototypes */

/**
  * @}
  */ /* end of group iNEMO_USB_Common */

/**
  * @}
  */ /* end of group Common */

/**
  * @}
  */ /* end of group iNEMO_DFU_Program */


#endif /* __INEMO_USB_COMMON_H */

/******************* (C) COPYRIGHT 2010 STMicroelectronics *****END OF FILE****/