/**
* @file    iNEMO_dfu.h
* @author  ART Team IMS-Systems Lab
* @version V3.2.1
* @date    09/20/2010
* @brief  iNEMO USB Hardware Configuration & Setup for DFU.
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
#ifndef __INEMO_DFU_H
#define __INEMO_DFU_H

/* Includes ------------------------------------------------------------------*/
#include "stm32f10x.h"


/** @addtogroup iNEMO_DFU_Program
  * @{
  */

/** @addtogroup Device_Firmware_Upgrade
  * @{
  */

/** @defgroup DFU_Functionality
  * @{
  */

/** @defgroup DFU_Configuration_Prototypes
  * @{
  */

/* Exported types ------------------------------------------------------------*/
/* Exported constants --------------------------------------------------------*/

/* Flash memory address from where user application will be loaded */
#define ApplicationAddress 0x08003000
/* Option Byte address from where read and write value to enter or leave DFU mode */
#define Option_address ((uint32_t)0x1FFFF804)
/* Enable or Disable to enter or leave DFU in Software mode */
#define Enable_SW_Mode

/* Exported macro ------------------------------------------------------------*/
/* Exported functions ------------------------------------------------------- */

void DFU_Button_Config(void);
uint8_t  DFU_Button_Read(void);
uint8_t Option_Byte_Read (void);
void Leave_DFU_SW_Mode(void);

/**
  * @}
  */ /* end of group DFU_Configuration_Prototypes */

/**
  * @}
  */ /* end of group DFU_Functionality */

/**
  * @}
  */ /* end of group Device_Firmware_Upgrade */

/**
  * @}
  */ /* end of group iNEMO_DFU_Program */

#endif /* __INEMO_DFU_H */

/******************* (C) COPYRIGHT 2010 STMicroelectronics *****END OF FILE****/