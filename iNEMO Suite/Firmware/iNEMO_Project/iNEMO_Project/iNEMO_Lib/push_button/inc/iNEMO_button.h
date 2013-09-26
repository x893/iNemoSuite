/**
  * @file    iNEMO_Button.h
  * @author  ART Team IMS-Systems Lab
  * @version V2.2
  * @date    01/11/2011
  * @brief   iNEMO Button Hardware Configuration & Setup
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
#ifndef __INEMO_BUTTON_H
#define __INEMO_BUTTON_H

#ifdef __cplusplus
 extern "C" {
#endif 


/* Includes ------------------------------------------------------------------*/
#include "stm32f10x.h"



/** @defgroup iNEMO_Button
  * @{
  */

/** @defgroup iNEMO_Button_Prototypes
  * @{
  */


/* Exported types ------------------------------------------------------------*/
typedef enum 
{  
  BUTTON_KEY = 0
} Button_TypeDef;

typedef enum 
{  
  BUTTON_MODE_GPIO = 0,
  BUTTON_MODE_EXTI = 1
} ButtonMode_TypeDef;

/* Exported constants --------------------------------------------------------*/

/** Define the key push-button pin */  
#define iNEMO_BUTTONn                                 1
  
#define iNEMO_KEY_BUTTON_PIN                          GPIO_Pin_13
#define iNEMO_KEY_BUTTON_GPIO_PORT                    GPIOC
#define iNEMO_KEY_BUTTON_GPIO_CLK                     RCC_APB2Periph_GPIOC
#define iNEMO_KEY_BUTTON_EXTI_LINE                    EXTI_Line13
#define iNEMO_KEY_BUTTON_EXTI_PORT_SOURCE             GPIO_PortSourceGPIOC
#define iNEMO_KEY_BUTTON_EXTI_PIN_SOURCE              GPIO_PinSource13
#define iNEMO_KEY_BUTTON_EDGE                         EXTI_Trigger_Rising
#define iNEMO_KEY_BUTTON_EXTI_IRQn                    EXTI15_10_IRQn
#define iNEMO_KEY_BUTTON_EXTI_PREEMPTION_PRIORITY     12
#define iNEMO_KEY_BUTTON_EXTI_SUB_PRIORITY            0

/* Exported macro ------------------------------------------------------------*/


/* Exported functions ------------------------------------------------------- */
void iNEMO_Button_Init(Button_TypeDef Button, ButtonMode_TypeDef Button_Mode);
void iNEMO_Button_Interrupt_Cmd(Button_TypeDef Button, FunctionalState NewState);
uint32_t iNEMO_Button_Get_State(Button_TypeDef Button);

/**
  * @}
  */ /* end of group iNEMO_Button_Prototypes */

/**
  * @}
  */ /* end of group iNEMO_Button */


#endif /* __INEMO_BUTTON_H */

/******************* (C) COPYRIGHT 2010 STMicroelectronics *****END OF FILE****/
