/**
  * @file    LPRYxxxAL.h
  * @author  ART Team IMS-Systems Lab
  * @version V2.2
  * @date    01/11/2011
  * @brief   Header for LPRYxxxAL.c file  of iNEMO_v2
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



/** Define to prevent recursive inclusion */
#ifndef __LPRYxxxAL_H
#define __LPRYxxx0AL_H

#ifdef __cplusplus
 extern "C" {
#endif 
  
/** Includes*/
#include "stm32f10x.h"
#include "HAL_LPRYxxxAL.h"


/**
 * @defgroup LPR430AL_LY330ALH
 * @{
 */


/** @defgroup Gyro_Sensitivity_Define
  * @{
  */

#define Gyro_Sensitivity_Y_300dps       3.752   /*!< Yaw axis Sensitivity [ mV/dps ] see LY330ALH datasheet */
#define Gyro_SensitivityLSB_Y_300dps     4.62    /*!< Yaw axis Sensitivity [ LSB/dps] */

#define Gyro_Sensitivity_P_300dps        3.33    /*!<300dps Full Scale Pitch axis Sensitivity [ mV/dps ]see LPR430AL datasheet*/
#define Gyro_SensitivityLSB_P_300dps     4.13   /*!<300dps Full Scale Pitch axis Sensitivity [ LSB/dps ]*/

#define Gyro_Sensitivity_R_300dps        3.33    /*!< 300dps Full Scale  Roll axis Sensitivity [ mV/dps ]see LPR430AL datasheet*/
#define Gyro_SensitivityLSB_R_300dps     4.13   /*!< 300dps Full Scale Roll  axis Sensitivity [ LSB/dps ]*/

#define Gyro_Sensitivity_R_1200dps        0.83    /*!< 1200 dps  full scale Roll axis Sensitivity [ mV/dps ]see LPR430AL datasheet*/
#define Gyro_SensitivityLSB_R_1200dps     1.03   /*!< 1200dps full scale Roll axis Sensitivity [ LSB/dps ]*/

#define Gyro_Sensitivity_P_1200dps        0.83    /*!< 1200 dps  full scale Pitch axis Sensitivity [ mV/dps ]see LPR430AL datasheet*/
#define Gyro_SensitivityLSB_P_1200dps     1.03   /*!< 1200 dps  full scale Pitch axis Sensitivity [ LSB/dps ]*/

#define BufferSize  5
#define AxisNumber  3
/**
*@}
*/ /* end of group Gyro_Sensitivity_Define */ 



/** @defgroup Gyro_Functions
  * @{
  */
void LPRYxxxAL_ADC_Init(void);
void LPRYxxxAL_DMA_Init(void);
void LPRYxxxAL_PD_ST_Init(void);
void LPRYxxxAL_On(void);
void LPRYxxxAL_Off(void);
void LPRYxxxAL_ST_On(void);
void LPRYxxxAL_ST_Off(void);
void LPRYxxxAL_Read(u16* out);
void LPRYxxxAL_Read_Rate(s16* out);
void LPRYxxxAL_Read_RawRate(s16* out);
/**
  * @}
  */  /* end of group Gyro_Functions */ 

/**
 * @}
 */ /* end of group LPR430AL_LY330ALH */

#endif /* __LPRYxxxAL_H */


/******************* (C) COPYRIGHT 2010 STMicroelectronics *****END OF FILE****/
