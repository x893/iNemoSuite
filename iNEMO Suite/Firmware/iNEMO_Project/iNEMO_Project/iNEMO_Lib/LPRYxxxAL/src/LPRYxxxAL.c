/**
  * @file    LPRYxxxAL.c
  * @author  ART Team IMS-Systems Lab
  * @version V2.2
  * @date    01/11/2011
  * @brief   This file provides a set of functions to manage the communication
  *          between STM32 ADC and LPRYxxxAL analog output using DMA.
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





#include "LPRYxxxAL.h"
#include "iNEMO_conf.h"


/**
 * @addtogroup LPR430AL_LY330ALH
 * @{
 */

/**Buffer to store ADC value*/
u16 ADC_ConvertedValue[BufferSize];


/** @defgroup Gyro_Functions
* @{
*/

/**
* @brief  Initializes the ADC peripheral used to drive the LPRYxxxAL
* @param  None
* @retval None
*/

void LPRYxxxAL_ADC_Init(void)
{
  GPIO_InitTypeDef GPIO_InitStructure;
  ADC_InitTypeDef ADC_InitStructure;

  /** IMPORTANT :check in Set_System() in main.c if ADCCLK is configured  --> (es.) RCC_ADCCLKConfig(RCC_PCLK2_Div6)*/

  /* GPIO configuration*/

  RCC_APB2PeriphClockCmd( GYRO_RCC_Port | GYRO_RCC_Periph_ADC, ENABLE);

  GPIO_InitStructure.GPIO_Pin = GYRO_LPR_PinY | GYRO_LPR_PinX | GYRO_LPR_PinREF | GYRO_LY_PinZ |GYRO_LY_PinREF;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AIN;
  GPIO_Init(GYRO_ADC_Port, &GPIO_InitStructure);

  /* GYRO_ADC configuration*/
  ADC_InitStructure.ADC_Mode = ADC_Mode_Independent;
  ADC_InitStructure.ADC_ScanConvMode = ENABLE;
  ADC_InitStructure.ADC_ContinuousConvMode = ENABLE;
  ADC_InitStructure.ADC_ExternalTrigConv = ADC_ExternalTrigConv_None;
  ADC_InitStructure.ADC_DataAlign = ADC_DataAlign_Right;
  ADC_InitStructure.ADC_NbrOfChannel =5;

  /* GYRO_ADC regular channel configuration */
  ADC_RegularChannelConfig(GYRO_ADC, GYRO_LPR_ACD_ChX, 1, ADC_SampleTime_239Cycles5);
  ADC_RegularChannelConfig(GYRO_ADC, GYRO_LPR_ACD_ChY, 2,ADC_SampleTime_239Cycles5);
  ADC_RegularChannelConfig(GYRO_ADC, GYRO_LPR_ACD_ChREF, 3,ADC_SampleTime_239Cycles5);
  ADC_RegularChannelConfig(GYRO_ADC, GYRO_LY_ACD_ChZ, 4, ADC_SampleTime_239Cycles5);
  ADC_RegularChannelConfig(GYRO_ADC, GYRO_LY_ACD_ChREF, 5,ADC_SampleTime_239Cycles5);

  ADC_Init(GYRO_ADC, &ADC_InitStructure);

  /* Enable GYRO_ADC */
  ADC_Cmd(GYRO_ADC, ENABLE);

  /* Enable GYRO_ADC reset calibration register */
  ADC_ResetCalibration(GYRO_ADC);
  /* Check the end of GYRO_ADC reset calibration register */
  while(ADC_GetResetCalibrationStatus(GYRO_ADC));

  /* Start GYRO_ADC calibration */
  ADC_StartCalibration(GYRO_ADC);
  /* Check the end of GYRO_ADC calibration */
  while(ADC_GetCalibrationStatus(GYRO_ADC));

}

/**
* @brief   Initializes the DMA peripheral used to drive the LPRYxxxAL
* @param  NONE
* @retval NONE
*/

void LPRYxxxAL_DMA_Init()
{
  DMA_InitTypeDef  DMA_InitStructure;

  RCC_AHBPeriphClockCmd(GYRO_RCC_Periph_DMA, ENABLE);

  DMA_DeInit(GYRO_DMA_Channel);
  DMA_InitStructure.DMA_PeripheralBaseAddr =(u32)GYRO_ADC_DR_Address;
  DMA_InitStructure.DMA_MemoryBaseAddr = (u32)ADC_ConvertedValue;
  DMA_InitStructure.DMA_DIR = DMA_DIR_PeripheralSRC;
  DMA_InitStructure.DMA_BufferSize = BufferSize;
  DMA_InitStructure.DMA_PeripheralInc = DMA_PeripheralInc_Disable;
  DMA_InitStructure.DMA_MemoryInc = DMA_MemoryInc_Enable;
  DMA_InitStructure.DMA_PeripheralDataSize = DMA_PeripheralDataSize_HalfWord;
  DMA_InitStructure.DMA_MemoryDataSize = DMA_MemoryDataSize_HalfWord;
  DMA_InitStructure.DMA_Mode = DMA_Mode_Circular;
  DMA_InitStructure.DMA_Priority = DMA_Priority_High;
  DMA_InitStructure.DMA_M2M = DMA_M2M_Disable;
  DMA_Init(GYRO_DMA_Channel, &DMA_InitStructure);

}

/**
* @brief   Initializes the  PD(Power Down) ans ST(Self Test) GPIO pins
* @param  None
* @retval None
*/

void LPRYxxxAL_PD_ST_Init(void)
{
  GPIO_InitTypeDef GPIO_InitStructure;

  /* Enable  GPIO clocks */
  RCC_APB2PeriphClockCmd(GYRO_GPIO_RCC_Port2, ENABLE);

  /* Configure  Pins */
  GPIO_InitStructure.GPIO_Pin = GYRO_LY_PinST | GYRO_LY_PinPD | GYRO_LPR_PinST |GYRO_LY_PinPD ;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
  GPIO_Init(GYRO_GPIO_Port2, &GPIO_InitStructure);
}

/**
* @brief  Reset the two PD pins to turn on the two Gyros
* @param  None
* @retval None
*/

void LPRYxxxAL_On(void)
{
  GPIO_ResetBits(GYRO_GPIO_Port2, GYRO_LY_PinPD);
  GPIO_ResetBits(GYRO_GPIO_Port2, GYRO_LPR_PinPD);

}

/**
* @brief  Set the two PD pins to turn off the two Gyros
* @param  None
* @retval None
*/

void LPRYxxxAL_Off(void)
{
  GPIO_SetBits(GYRO_GPIO_Port2, GYRO_LY_PinPD);
  GPIO_SetBits(GYRO_GPIO_Port2, GYRO_LPR_PinPD) ;
}

/**
* @brief  Set the two PD pins to turn on the Self test funtion of two Gyros
* @param  None
* @retval None
*/

void LPRYxxxAL_ST_On(void)
{
  GPIO_SetBits(GYRO_GPIO_Port2, GYRO_LY_PinST);
  GPIO_SetBits(GYRO_GPIO_Port2, GYRO_LPR_PinST);

}

/**
* @brief  Reset the two PD pins to turn off the Self test funtion of two Gyros
* @param  None
* @retval None
*/

void LPRYxxxAL_ST_Off(void)
{
  GPIO_ResetBits(GYRO_GPIO_Port2, GYRO_LY_PinST);
  GPIO_ResetBits(GYRO_GPIO_Port2, GYRO_LPR_PinST);
}


/**
* @brief  Read the LPRYxxxAL output
* @param  out : u16 buffer to store data
* @retval None
*/

void LPRYxxxAL_Read(u16* out)
{
  iNEMO_ENTER_CRITICAL();
  /* Enable GYRO_ADC DMA */
  ADC_DMACmd(GYRO_ADC, ENABLE);
  ADC_Cmd(GYRO_ADC, ENABLE);
  DMA_Cmd(GYRO_DMA_Channel, ENABLE);
  ADC_SoftwareStartConvCmd(GYRO_ADC, ENABLE);
  while(!(DMA_GetFlagStatus(GYRO_DMA_FLAG)));
  ADC_Cmd(GYRO_ADC, DISABLE);
  ADC_SoftwareStartConvCmd(GYRO_ADC, DISABLE);
  DMA_ClearFlag(GYRO_DMA_FLAG);
  for(int i=0; i< BufferSize; i++)
  {
    *out=ADC_ConvertedValue[i];
    out++;
  }
  iNEMO_EXIT_CRITICAL();
}

/**
* @brief   Read LPRYxxxAL output, and calculate the angular rate for each axis Rate=(output_axis-output_reference)/Gyro_SensitivityLSB
*                   angular rates are positive in counterclockwise direction
* @param  out : s16 data buffer
* @retval None
*/
void LPRYxxxAL_Read_Rate(s16* out)
{
  u16 outADC[BufferSize];
  LPRYxxxAL_Read(outADC);


  out[0]=(s16)((outADC[0]-outADC[2])/Gyro_SensitivityLSB_R_300dps);
  out[1]=(s16)((outADC[1]-outADC[2])/Gyro_SensitivityLSB_P_300dps);
  out[2]=(s16)((outADC[3]-outADC[4])/Gyro_SensitivityLSB_Y_300dps);

}

/**
* @brief   Read LPRYxxxAL output, and calculate the angular rate for each axis Rate[LSB]=(output_axis-output_reference)
*                   angular rates are positive in counterclockwise direction
* @param  out : s16 data buffer
* @retval None
*/
void LPRYxxxAL_Read_RawRate(s16* out)
{
  u16 outADC[BufferSize];
  LPRYxxxAL_Read(outADC);


  out[0]=(s16)(outADC[0]-outADC[2]);
  out[1]=-(s16)(outADC[1]-outADC[2]);
  out[2]=(s16)(outADC[3]-outADC[4]);
}

/**
* @}
*/  /* end of group Gyro_Functions */ 

/**
 * @}
 */  /* end of group LPR430AL_LY330ALH */ 


/* (C) COPYRIGHT 2010 STMicroelectronics *****END OF FILE****/
