/**
  * @file    HAL_STLM75.h
  * @author  ART Team IMS-Systems Lab
  * @version V2.2
  * @date    01/11/2011
  * @brief   Hardware Abstraction Layer for STLM75.
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



/* Define to prevent recursive inclusion*/
#ifndef __HAL_STLM75_H
#define __HAL_STLM75_H

#ifdef __cplusplus
 extern "C" {
#endif 
  

/* Includes ------------------------------------------------------------------*/
#include "stm32f10x.h"
#include "iNEMO_conf.h"

/**
* @defgroup STLM75
* @{
*/


/**
* @defgroup  STLM75_I2C_Define
* @{
*/

#define TEMP_I2C                  I2C2	
#define TEMP_RCC_Periph_I2C       RCC_APB1Periph_I2C2
#define TEMP_I2C_Port             GPIOB
#define TEMP_I2C_SCL_Pin          GPIO_Pin_10
#define TEMP_I2C_SDA_Pin          GPIO_Pin_11
#define TEMP_RCC_Port_I2C         RCC_APB2Periph_GPIOB

#define TEMP_I2C_Speed              100000

/**
*@}
*/ /* end of group STLM75_I2C_Define */ 


/**
* @defgroup STLM75_Interrupt_Pin_Define
* @{
*/

#ifdef OS_INT_ENABLE
#define STLM75_INT_Port                  GPIOB
#define STLM75_INT_RCC                   RCC_APB2Periph_GPIOB
#define STLM75_INT_Pin                   GPIO_Pin_1
#define STLM75_INT_Port_Source           GPIO_PortSourceGPIOB
#define STLM75_INT_Pin_Source            GPIO_PinSource1
#define STLM75_INT_EXTI_Line             EXTI_Line1
#define STLM75_INT_Edge                  EXTI_Trigger_Falling 
#define STLM75_INT_EXTI_IRQCHANNEL       EXTI1_IRQn
#define STLM75_INT_Preemption_Priority   12
#define STLM75_INT_Sub_Priority          0
#endif //OS_INT_ENABLE

/**
*@}
*/ /* end of group STLM75_Interrupt_Pin_Define */

/**
*@}
*/ /* end of group STLM75 */


#endif /* __HAL_STLM75_H */

/******************* (C) COPYRIGHT 2010 STMicroelectronics *****END OF FILE****/
