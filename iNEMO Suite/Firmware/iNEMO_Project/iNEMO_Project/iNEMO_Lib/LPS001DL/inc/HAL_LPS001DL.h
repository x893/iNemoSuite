/**
  * @file    HAL_LPS001DL.h
  * @author  ART Team IMS-Systems Lab
  * @version V2.2
  * @date    01/11/2011
  * @brief   Hardware Abstraction Layer for LPS001DL.
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
#ifndef __HAL_LPS001DL_H
#define __HAL_LPS001DL_H

#ifdef __cplusplus
 extern "C" {
#endif 
  

/* Includes ------------------------------------------------------------------*/
#include "stm32f10x.h"
#include "iNEMO_conf.h"

/**
 * @addtogroup LPS001DL
 * @{
 */

/**
 * @addtogroup LPS001DL_I2C_Define
 * @{
 */
#define PRESS_I2C                  I2C2
#define PRESS_RCC_Periph_I2C       RCC_APB1Periph_I2C2
#define PRESS_I2C_Port             GPIOB
#define PRESS_I2C_SCL_Pin          GPIO_Pin_10
#define PRESS_I2C_SDA_Pin          GPIO_Pin_11
#define PRESS_RCC_Port_I2C         RCC_APB2Periph_GPIOB


#define PRESS_I2C_Speed              100000
/**
*@}
*/ /* end of group LPS001DL_I2C_Define */ 

/**
 *@addtogroup LPS001DL_Interrupt_Port_Defines
 *@{
*/

#ifdef INT1_PAD_ENABLE
#define LPS001DL_INT1_Port                  GPIOA
#define LPS001DL_INT1_RCC                   RCC_APB2Periph_GPIOA
#define LPS001DL_INT1_Pin                   GPIO_Pin_9
#define LPS001DL_INT1_Port_Source           GPIO_PortSourceGPIOA
#define LPS001DL_INT1_Pin_Source            GPIO_PinSource9
#define LPS001DL_INT1_EXTI_Line             EXTI_Line9
#define LPS001DL_INT1_Edge                  EXTI_Trigger_Rising /*!<It must be coherent with Mode field of LPS001DL_InterruptTypeDef structure */
#define LPS001DL_INT1_EXTI_IRQCHANNEL        EXTI9_5_IRQn
#define LPS001DL_INT1_Preemption_Priority   12
#define LPS001DL_INT1_Sub_Priority          0
#endif /*!<INT1_PAD_ENABLE */



/**
*@}
*/ /* end of group LPS001DL_Interrupt_Port_Defines */ 

/**
 * @}
 */ /* end of group LPS001DL */


#endif /* __HAL_LPS001DL_H */

/******************* (C) COPYRIGHT 2010 STMicroelectronics *****END OF FILE****/
