/**
  * @file    virtual_com.h 
  * @author  MCD Application Team & SystemsLab
  * @version V3.2.1
  * @date    09/20/2010
  * @brief   Header for iNEMO Virtual Com Setup & API.
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


/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __VIRTUAL_COM_H
#define __VIRTUAL_COM_H

#ifdef __cplusplus
 extern "C" {
#endif 

/* Includes ------------------------------------------------------------------*/
#include "stm32f10x.h"
#include "usb_lib.h"
#include "usb_conf.h"
#include "usb_desc.h"
#include "usb_istr.h"
#include "usb_prop.h"
#include "usb_pwr.h"

/** @addtogroup iNEMO_Virtual_Com
  * @{
  */

/** @addtogroup iNEMO_Virtual_Com_API
  * @{
  */

/* Exported types ------------------------------------------------------------*/
/* Exported constants --------------------------------------------------------*/
/* Define the USB Disconnect Pin*/
#define iNEMO_USB_DISCONNECT                      GPIOA  
#define iNEMO_USB_DISCONNECT_PIN                  GPIO_Pin_10
#define iNEMO_RCC_APB2Periph_GPIO_DISCONNECT      RCC_APB2Periph_GPIOA


/* Exported macro ------------------------------------------------------------*/
/* Exported define -----------------------------------------------------------*/
#define MASS_MEMORY_START     0x04002000
#define BULK_MAX_PACKET_SIZE  0x00000040
#define SERIAL_USB_BUFFER_IN_SIZE       192

/* Option Byte address from where read and write value to enter or leave DFU mode */
#define Option_address ((uint32_t)0x1FFFF804)

/* Enable or Disable to enter or leave DFU in Software mode */
#define Enable_SW_Mode

/* Exported functions ------------------------------------------------------- */
void Set_USBClock(void);
void iNEMO_USB_Disconnet_Pin_Config(void);
void Enter_DFU_SW_Mode(void);
void Reset_Device(void);
uint8_t Option_Byte_Read (void);
void USB_Cable_Config (FunctionalState NewState);
void Enter_LowPowerMode(void);
void Leave_LowPowerMode(void);
void USB_Interrupts_Config(void);
void Get_SerialNum(void);
void Virtual_Com_Write_Char(char c);
void Virtual_Com_Write_String(char *s);
void Virtual_Com_Printf(const char *str,...);
void Virtual_Com_Write_Buffer(u8* data_buffer, u8 Nb_bytes);


/* External variables --------------------------------------------------------*/


/**
  * @}
  */ /* end of group iNEMO_Virtual_Com_API */

/**
  * @}
  */ /* end of group iNEMO_Virtual_Com */

#endif  /*__VIRTUAL_COM_H*/
/******************* (C) COPYRIGHT 2010 STMicroelectronics *****END OF FILE****/
