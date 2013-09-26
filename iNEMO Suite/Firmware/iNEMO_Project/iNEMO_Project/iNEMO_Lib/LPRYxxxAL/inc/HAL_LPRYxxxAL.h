/**
  * @file    HAL_LPRYxxxAL.h
  * @author  ART Team IMS-Systems Lab
  * @version V2.2
  * @date    01/11/2011
  * @brief   Hardware Abstraction Layer for LPYRxxxAL gyroscope of iNEMO_v2.
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



/* Define to prevent recursive inclusion */
#ifndef __HAL_LPRYxxxAL_H
#define __HAL_LPRYxxxAL_H

#ifdef __cplusplus
 extern "C" {
#endif 
  

/* Includes */
#include "stm32f10x.h"
#include "iNEMO_conf.h"

/**
 * @addtogroup LPR430AL_LY330ALH
 * @{
 */

/** @defgroup Gyro_ADC_Define
  * @{
  */
#define GYRO_ADC                  ADC1
#define GYRO_RCC_Periph_ADC       RCC_APB2Periph_ADC1
#define GYRO_ADC_Port             GPIOC
#define GYRO_ADC_DR_Address       ((u32)0x4001244C)
#define GYRO_RCC_Port             RCC_APB2Periph_GPIOC

/**
  * @}
  */ /* end of group Gyro_ADC_Define */ 


/** @defgroup Gyro_DMA_Define
  *@{
  */
#define GYRO_DMA                  DMA1
#define GYRO_RCC_Periph_DMA       RCC_AHBPeriph_DMA1
#define GYRO_DMA_Channel          DMA1_Channel1
#define GYRO_DMA_IRQChannel       DMA1_Channel1_IRQChannel
#define GYRO_DMA_FLAG             DMA1_FLAG_TC1
/**
  *@}
  */ /* end of group Gyro_DMA_Define */ 

/** @defgroup Gyro_GPIO_Define
  *@{
  */
#define GYRO_GPIO_Port2            GPIOB   /*!< GPIO for ST and PD/SLEEP pin*/
#define GYRO_GPIO_RCC_Port2        RCC_APB2Periph_GPIOB

#define GYRO_LY_PinZ              GPIO_Pin_4
#define GYRO_LY_PinREF            GPIO_Pin_5
#define GYRO_LY_PinST             GPIO_Pin_14   /*!< GPIO port B*/
#define GYRO_LY_PinPD             GPIO_Pin_15   /*!< GPIO port B*/


#define GYRO_LPR_PinY             GPIO_Pin_1
#define GYRO_LPR_PinX             GPIO_Pin_0
#define GYRO_LPR_PinREF           GPIO_Pin_2
#define GYRO_LPR_PinST            GPIO_Pin_1    /*!< GPIO port B*/
#define GYRO_LPR_PinPD            GPIO_Pin_5    /*!< GPIO port B*/

#define GYRO_LY_ACD_ChZ           ADC_Channel_14
#define GYRO_LY_ACD_ChREF         ADC_Channel_15

#define GYRO_LPR_ACD_ChY          ADC_Channel_11
#define GYRO_LPR_ACD_ChX          ADC_Channel_10
#define GYRO_LPR_ACD_ChREF        ADC_Channel_12

/**
*@}
*/ /* end of group Gyro_GPIO_Define */ 

/**
 * @}
 */ /* end of group LPR430AL_LY330ALH */ 


#endif /*__HAL_LPRYxxxAL_H */

/******************* (C) COPYRIGHT 2010 STMicroelectronics *****END OF FILE****/
