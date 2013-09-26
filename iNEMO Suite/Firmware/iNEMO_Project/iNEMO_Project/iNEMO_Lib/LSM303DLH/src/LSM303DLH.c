/**
  * @file    LSM303DLH.c
  * @author  ART Team IMS-Systems Lab
  * @version V2.2
  * @date    01/11/2011
  * @brief   This file provides a set of functions needed to manage the
  *          communication between STM32 I2C master and LSM303DLH I2C slave.
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


/* Includes */
#include "LSM303DLH.h"
#include "HAL_LSM303DLH.h"
#include "iNEMO_conf.h"


/**
* @defgroup LSM303DLH
* @{
*/

/** @defgroup LSM303DLH_I2C_Function
* @{
*/

/**
* @brief  Initializes the I2C peripheral used to drive the LSM303DLH
* @param  None
* @retval None
*/
void LSM303DLH_I2C_Init(void)
{
  I2C_InitTypeDef  I2C_InitStructure;
  GPIO_InitTypeDef GPIO_InitStructure;

  /* Enable I2C and GPIO clocks */
  RCC_APB1PeriphClockCmd(LSM_I2C_RCC_Periph, ENABLE);
  RCC_APB2PeriphClockCmd(LSM_I2C_RCC_Port, ENABLE);

  /* Configure I2C pins: SCL and SDA */
  GPIO_InitStructure.GPIO_Pin =  LSM_I2C_SCL_Pin | LSM_I2C_SDA_Pin;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_OD;
  GPIO_Init(LSM_I2C_Port, &GPIO_InitStructure);

  /* I2C configuration */
  I2C_InitStructure.I2C_Mode = I2C_Mode_I2C;
  I2C_InitStructure.I2C_DutyCycle = I2C_DutyCycle_2;
  I2C_InitStructure.I2C_OwnAddress1 = 0x00;
  I2C_InitStructure.I2C_Ack = I2C_Ack_Enable;
  I2C_InitStructure.I2C_AcknowledgedAddress = I2C_AcknowledgedAddress_7bit;
  I2C_InitStructure.I2C_ClockSpeed = LSM_I2C_Speed;

  /* Apply I2C configuration after enabling it */
  I2C_Init(LSM_I2C, &I2C_InitStructure);

  /* I2C Peripheral Enable */
  I2C_Cmd(LSM_I2C, ENABLE);
}

/**
* @brief  Writes one byte to the  LSM303DLH.
* @param  slAddr : slave address LSM_A_I2C_ADDRESS or LSM_M_I2C_ADDRESS
* @param  pBuffer : pointer to the buffer  containing the data to be written to the LSM303DLH.
* @param  WriteAddr : address of the register in which the data will be written
* @retval None
*/
void LSM303DLH_I2C_ByteWrite(u8 slAddr, u8* pBuffer, u8 WriteAddr)
{
  iNEMO_ENTER_CRITICAL();
  /* Send START condition */
  I2C_GenerateSTART(LSM_I2C, ENABLE);

  /* Test on EV5 and clear it */
  while(!I2C_CheckEvent(LSM_I2C, I2C_EVENT_MASTER_MODE_SELECT));

  /* Send LSM303DLH_Magn address for write */
  I2C_Send7bitAddress(LSM_I2C, slAddr, I2C_Direction_Transmitter);

  /* Test on EV6 and clear it */
  while(!I2C_CheckEvent(LSM_I2C, I2C_EVENT_MASTER_TRANSMITTER_MODE_SELECTED));

  /* Send the LSM303DLH_Magn's internal address to write to */
  I2C_SendData(LSM_I2C, WriteAddr);

  /* Test on EV8 and clear it */
  while(!I2C_CheckEvent(LSM_I2C, I2C_EVENT_MASTER_BYTE_TRANSMITTED));

  /* Send the byte to be written */
  I2C_SendData(LSM_I2C, *pBuffer);

  /* Test on EV8 and clear it */
  while(!I2C_CheckEvent(LSM_I2C, I2C_EVENT_MASTER_BYTE_TRANSMITTED));

  /* Send STOP condition */
  I2C_GenerateSTOP(LSM_I2C, ENABLE);
  iNEMO_EXIT_CRITICAL();  
}

/**
* @brief  Reads a block of data from the LSM303DLH.
* @param  slAddr  : slave address LSM_A_I2C_ADDRESS or LSM_M_I2C_ADDRESS
* @param  pBuffer : pointer to the buffer that receives the data read from the LSM303DLH.
* @param  ReadAddr : LSM303DLH's internal address to read from.
* @param  NumByteToRead : number of bytes to read from the LSM303DLH ( NumByteToRead >1  only for the Mgnetometer readinf).
* @retval None
*/

void LSM303DLH_I2C_BufferRead(u8 slAddr, u8* pBuffer, u8 ReadAddr, u16 NumByteToRead)
{
  iNEMO_ENTER_CRITICAL();
  /* While the bus is busy */
  while(I2C_GetFlagStatus(LSM_I2C, I2C_FLAG_BUSY));

  /* Send START condition */
  I2C_GenerateSTART(LSM_I2C, ENABLE);

  /* Test on EV5 and clear it */
  while(!I2C_CheckEvent(LSM_I2C, I2C_EVENT_MASTER_MODE_SELECT));

  /* Send LSM303DLH_Magn address for write */
  I2C_Send7bitAddress(LSM_I2C, slAddr, I2C_Direction_Transmitter);

  /* Test on EV6 and clear it */
  while(!I2C_CheckEvent(LSM_I2C, I2C_EVENT_MASTER_TRANSMITTER_MODE_SELECTED));

  /* Clear EV6 by setting again the PE bit */
  I2C_Cmd(LSM_I2C, ENABLE);

  /* Send the LSM303DLH_Magn's internal address to write to */
  I2C_SendData(LSM_I2C, ReadAddr);

  /* Test on EV8 and clear it */
  while(!I2C_CheckEvent(LSM_I2C, I2C_EVENT_MASTER_BYTE_TRANSMITTED));

  /* Send STRAT condition a second time */
  I2C_GenerateSTART(LSM_I2C, ENABLE);

  /* Test on EV5 and clear it */
  while(!I2C_CheckEvent(LSM_I2C, I2C_EVENT_MASTER_MODE_SELECT));

  /* Send LSM303DLH address for read */
  I2C_Send7bitAddress(LSM_I2C, slAddr, I2C_Direction_Receiver);

  /* Test on EV6 and clear it */
  while(!I2C_CheckEvent(LSM_I2C, I2C_EVENT_MASTER_RECEIVER_MODE_SELECTED));

  /* While there is data to be read */
  while(NumByteToRead)
  {
    if(NumByteToRead == 1)
    {
      /* Disable Acknowledgement */
      I2C_AcknowledgeConfig(LSM_I2C, DISABLE);

      /* Send STOP Condition */
      I2C_GenerateSTOP(LSM_I2C, ENABLE);
    }

    /* Test on EV7 and clear it */
    if(I2C_CheckEvent(LSM_I2C, I2C_EVENT_MASTER_BYTE_RECEIVED))
    {
      /* Read a byte from the LSM303DLH */
      *pBuffer = I2C_ReceiveData(LSM_I2C);

      /* Point to the next location where the byte read will be saved */
      pBuffer++;

      /* Decrement the read bytes counter */
      NumByteToRead--;
    }
  }

  /* Enable Acknowledgement to be ready for another reception */
  I2C_AcknowledgeConfig(LSM_I2C, ENABLE);
  iNEMO_EXIT_CRITICAL();
}
/**
 * @}
 */ /* end of group LSM303DLH_I2C_Function */

/**
 * @addtogroup Accelerometer
 * @{
 */


/**
* @defgroup Accelerometer_Function
* @{
*/

/**
* @brief  Set configuration of Linear Acceleration measurement of LSM303DLH
* @param  LSM_Acc_Config_Struct : pointer to a LSM_Acc_ConfigTypeDef structure that contains the configuration setting for the Accelerometer LSM303DLH.
* @retval None
*/

void LSM303DLH_Acc_Config(LSM_Acc_ConfigTypeDef *LSM_Acc_Config_Struct)
{
  u8 CRTL1 = 0x00;
  u8 CRTL4  =  0x00;


  CRTL1 |= (u8) (LSM_Acc_Config_Struct->Power_Mode | LSM_Acc_Config_Struct->ODR| LSM_Acc_Config_Struct->Axes_Enable);
  CRTL4 |= (u8) (LSM_Acc_Config_Struct->FS | LSM_Acc_Config_Struct->Data_Update| LSM_Acc_Config_Struct->Endianess);

  LSM303DLH_I2C_ByteWrite(LSM_A_I2C_ADDRESS, &CRTL1, LSM_A_CTRL_REG1_ADDR);
  LSM303DLH_I2C_ByteWrite(LSM_A_I2C_ADDRESS, &CRTL4, LSM_A_CTRL_REG4_ADDR);
}

/**
* @brief  Set configuration of  Internal High Pass Filter of  LSM303DLH for the linear acceleration
* @param  LSM303DLH_Filter_ConfigTypeDef : pointer to a LSM303DLH_ConfigTypeDef structure that
*           contains the configuration setting for the LSM303DLH.
* @retval None
*/

void LSM303DLH_Acc_Filter_Config(LSM_Acc_Filter_ConfigTypeDef *LSM_Acc_Filter_Config_Struct)
{
  u8 CRTL2 = 0x00;
  u8 REF  =  0x00;


  CRTL2 |= (u8) (LSM_Acc_Filter_Config_Struct->HPF_Enable | LSM_Acc_Filter_Config_Struct->HPF_Mode| LSM_Acc_Filter_Config_Struct->HPF_Frequency);
  REF |= (u8) (LSM_Acc_Filter_Config_Struct->HPF_Reference);

  LSM303DLH_I2C_ByteWrite(LSM_A_I2C_ADDRESS, &CRTL2, LSM_A_CTRL_REG2_ADDR);
  LSM303DLH_I2C_ByteWrite(LSM_A_I2C_ADDRESS, &REF, LSM_A_REFERENCE_REG_ADDR);
}

/**
* @brief  Change the lowpower mode for Accelerometer of LSM303DLH
* @param  LowPowerMode : new state for the lowpower mode. This parameter can be: LSM303DLH_Lowpower_x see LSM303DLH_SPI.h file
* @retval None
*/
void LSM303DLH_Acc_Lowpower_Cmd(u8 LowPowerMode)
{
  u8 tmpreg;
  LSM303DLH_I2C_BufferRead(LSM_A_I2C_ADDRESS, &tmpreg, LSM_A_CTRL_REG1_ADDR, 1);
  tmpreg &= 0x1F;
  tmpreg |= LowPowerMode;
  LSM303DLH_I2C_ByteWrite(LSM_A_I2C_ADDRESS,&tmpreg, LSM_A_CTRL_REG1_ADDR);
}

/**
* @brief  Change the ODR(Output data rate) for Acceleromter of LSM303DLH
* @param  DataRateValue : new ODR value. This parameter can be: LSM303DLH_ODR_x see LSM303DLH_SPI.h file
* @retval None
*/

void LSM303DLH_Acc_DataRate_Cmd(u8 DataRateValue)
{
  u8 tmpreg;
  LSM303DLH_I2C_BufferRead(LSM_A_I2C_ADDRESS, &tmpreg, LSM_A_CTRL_REG1_ADDR, 1);
  tmpreg &= 0xE7;
  tmpreg |= DataRateValue;
  LSM303DLH_I2C_ByteWrite(LSM_A_I2C_ADDRESS,&tmpreg, LSM_A_CTRL_REG1_ADDR);
}

/**
* @brief  Change the Full Scale of LSM303DLH
* @param  FS_value : new full scale value. This parameter can be: LSM303DLH_FS_x  see LSM303DLH_SPI.h file
* @retval None
*/

void LSM303DLH_Acc_FullScale_Cmd(u8 FS_value)
{
  u8 tmpreg;
  LSM303DLH_I2C_BufferRead(LSM_A_I2C_ADDRESS, &tmpreg, LSM_A_CTRL_REG4_ADDR, 1);
  tmpreg &= 0xCF;
  tmpreg |= FS_value;
  LSM303DLH_I2C_ByteWrite(LSM_A_I2C_ADDRESS,&tmpreg, LSM_A_CTRL_REG4_ADDR);
}

/**
* @brief  Reboot memory content of LSM303DLH
* @param  None
* @retval None
*/

void LSM303DLH_Acc_Reboot_Cmd(void)
{
  u8 tmpreg;
  LSM303DLH_I2C_BufferRead(LSM_A_I2C_ADDRESS, &tmpreg, LSM_A_CTRL_REG2_ADDR, 1);
  tmpreg |= 0x80;
  LSM303DLH_I2C_ByteWrite(LSM_A_I2C_ADDRESS,&tmpreg, LSM_A_CTRL_REG2_ADDR);
}

/**
* @brief  Read LSM303DLH linear acceleration output register
* @param  out : buffer to store data
* @retval None
*/

void LSM_Acc_Read_OutReg(u8* out)
{
  LSM303DLH_I2C_BufferRead(LSM_A_I2C_ADDRESS, out, (LSM_A_OUT_X_L_ADDR | 0x80), 6);
}

/**
* @brief   Read LSM303DLH output register, and calculate the raw  acceleration [LSB] ACC= (out_h*256+out_l)/16 (12 bit rappresentation)
* @param  out : buffer to store data
* @retval None
*/

void LSM303DLH_Acc_Read_RawData(s16* out)
{
  u8 buffer[6];
  u8 crtl4;
  
  LSM303DLH_I2C_BufferRead(LSM_A_I2C_ADDRESS, &crtl4, LSM_A_CTRL_REG4_ADDR, 1);
  
  LSM303DLH_I2C_BufferRead(LSM_A_I2C_ADDRESS, &buffer[0], LSM_A_OUT_X_L_ADDR, 1);
  LSM303DLH_I2C_BufferRead(LSM_A_I2C_ADDRESS, &buffer[1], LSM_A_OUT_X_H_ADDR, 1);
  LSM303DLH_I2C_BufferRead(LSM_A_I2C_ADDRESS, &buffer[2], LSM_A_OUT_Y_L_ADDR, 1);
  LSM303DLH_I2C_BufferRead(LSM_A_I2C_ADDRESS, &buffer[3], LSM_A_OUT_Y_H_ADDR, 1);
  LSM303DLH_I2C_BufferRead(LSM_A_I2C_ADDRESS, &buffer[4], LSM_A_OUT_Z_L_ADDR, 1);
  LSM303DLH_I2C_BufferRead(LSM_A_I2C_ADDRESS, &buffer[5], LSM_A_OUT_Z_H_ADDR, 1);
  
  /* check in the control register4 the data alignment*/
  if(!(crtl4 & 0x40))
  {
    for(int i=0; i<3; i++)
    {
      out[i]=(s16)(((u16)buffer[2*i+1] << 8) + buffer[2*i]);
    }
  }
  else
  {  
    for(int i=0; i<3; i++)
      out[i]=((s16)((u16)buffer[2*i] << 8) + buffer[2*i+1])/16;
  }
}


/**
* @brief   Read LSM303DLH output register, and calculate the acceleration ACC=SENSITIVITY* (out_h*256+out_l)/16 (12 bit rappresentation)
* @param  out : buffer to store data
* @retval None
*/

void LSM303DLH_Acc_Read_Acc(s16* out)
{
  u8 buffer[6];
  u8 crtl4;

  LSM303DLH_I2C_BufferRead(LSM_A_I2C_ADDRESS, &crtl4, LSM_A_CTRL_REG4_ADDR, 1);

  LSM303DLH_I2C_BufferRead(LSM_A_I2C_ADDRESS, &buffer[0], LSM_A_OUT_X_L_ADDR, 1);
  LSM303DLH_I2C_BufferRead(LSM_A_I2C_ADDRESS, &buffer[1], LSM_A_OUT_X_H_ADDR, 1);
  LSM303DLH_I2C_BufferRead(LSM_A_I2C_ADDRESS, &buffer[2], LSM_A_OUT_Y_L_ADDR, 1);
  LSM303DLH_I2C_BufferRead(LSM_A_I2C_ADDRESS, &buffer[3], LSM_A_OUT_Y_H_ADDR, 1);
  LSM303DLH_I2C_BufferRead(LSM_A_I2C_ADDRESS, &buffer[4], LSM_A_OUT_Z_L_ADDR, 1);
  LSM303DLH_I2C_BufferRead(LSM_A_I2C_ADDRESS, &buffer[5], LSM_A_OUT_Z_H_ADDR, 1);

  /* check in the control register4 the data alignment*/
  if(!(crtl4 & 0x40))
  {
    /* switch the sensitivity value set in the CRTL4*/
    switch(crtl4 & 0x30)
    {
    case 0x00:
      for(int i=0; i<3; i++)
      {
        out[i]=(s16)(((u16)buffer[2*i+1] << 8) + buffer[2*i])/LSM_Acc_Sensitivity_2g;
      }
      break;
    case 0x10:
      for(int i=0; i<3; i++)
        out[i]=(s16)(((u16)buffer[2*i+1] << 8) + buffer[2*i])/LSM_Acc_Sensitivity_4g;
      break;
    case 0x30:
      for(int i=0; i<3; i++)
        out[i]=(s16)(((u16)buffer[2*i+1] << 8) + buffer[2*i])/LSM_Acc_Sensitivity_8g;
    }
  }
  else
  {
    switch(crtl4 & 0x30)
    {
    case 0x00:
      for(int i=0; i<3; i++)
        out[i]=((s16)((u16)buffer[2*i] << 8) + buffer[2*i+1])/(16*LSM_Acc_Sensitivity_2g);
      break;
    case 0x10:
      for(int i=0; i<3; i++)
        out[i]=((s16)((u16)buffer[2*i] << 8) + buffer[2*i+1])/(16*LSM_Acc_Sensitivity_4g);
      break;
    case 0x30:
      for(int i=0; i<3; i++)
        out[i]=((s16)((u16)buffer[2*i] << 8) + buffer[2*i+1])/(16*LSM_Acc_Sensitivity_8g);
      break;
    }
  }
}

/**
*@}
*/ /* end of group Accelerometer_Function */


/**
 * @}
 */ /* end of group Accelerometer */

/**
 * @addtogroup Magnetometer
 * @{
 */

/**
* @defgroup Magnetometer_Function
* @{
*/

/**
* @brief  Set configuration of Magnetic field measurement of LSM303DLH
* @param  LSM_Magn_Config_Struct :  pointer to LSM_Magn_ConfigTypeDef structure that
*                  contains the configuration setting for the LSM303DLH_Magn.
* @retval None
*/

void LSM303DLH_Magn_Config(LSM_Magn_ConfigTypeDef *LSM_Magn_Config_Struct)
{
  u8 CRTLA = 0x00;
  u8 CRTLB = 0x00;
  u8 MODE = 0x00;

  CRTLA |= (u8) (LSM_Magn_Config_Struct->M_ODR | LSM_Magn_Config_Struct->Meas_Conf);
  CRTLB |= (u8) (LSM_Magn_Config_Struct->Gain);
  MODE  |= (u8) (LSM_Magn_Config_Struct->Mode);

  LSM303DLH_I2C_ByteWrite(LSM_M_I2C_ADDRESS, &CRTLA, LSM_M_CRA_REG_ADDR);  //CRTL_REGA
  LSM303DLH_I2C_ByteWrite(LSM_M_I2C_ADDRESS, &CRTLB, LSM_M_CRB_REG_ADDR);  //CRTL_REGB
  LSM303DLH_I2C_ByteWrite(LSM_M_I2C_ADDRESS, &MODE, LSM_M_MR_REG_ADDR);       //Mode register

}

#ifdef _MAG_DRDY

/**
* @brief  Initializes the  MAG_DRDY pin interrupt
* @param  None
* @retval None
*/

void LSM303DLH_Magn_DRDY_Config(void)
{
  NVIC_InitTypeDef NVIC_InitStructure;
  EXTI_InitTypeDef EXTI_InitStructure;
  GPIO_InitTypeDef GPIO_InitStructure;

  /* Enable _MAG_DRDY pad GPIO clocks */
  RCC_APB2PeriphClockCmd(LSM_M_DRDY_RCC_Port, ENABLE);

  /* Configure MAG_DRDY pin as input floating */
  GPIO_InitStructure.GPIO_Pin = LSM_M_DRDY_Pin;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
  GPIO_Init(LSM_M_DRDY_Port, &GPIO_InitStructure);

  /* Connect MAG_DRDY_EXTI_Line to MAG_DRDY Pin */
  GPIO_EXTILineConfig(LSM_M_DRDY_Port_Source, LSM_M_DRDY_Pin_Source);

  /* Configure MAG_DRDY_EXTI_Line to generate an interrupt on MAG_DRDY_Edge edge */
  EXTI_InitStructure.EXTI_Line = LSM_M_DRDY_EXTI_Line;
  EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;
  EXTI_InitStructure.EXTI_Trigger = LSM_M_DRDY_Edge;
  EXTI_InitStructure.EXTI_LineCmd = ENABLE;
  EXTI_Init(&EXTI_InitStructure);

  /* Enable the MAG_DRDY_EXTI_IRQCHANNEL Interrupt */
  NVIC_InitStructure.NVIC_IRQChannel = LSM_M_DRDY_EXTI_IRQCHANNEL;
  NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = LSM_M_DRDY_Preemption_Priority;
  NVIC_InitStructure.NVIC_IRQChannelSubPriority = LSM_M_DRDY_Sub_Priority;
  NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
  NVIC_Init(&NVIC_InitStructure);
}
#endif /*_MAG_DRDY*/

/**
* @brief  Read LSM303DLH magnetic field output register
* @param  out : buffer to store data
* @retval None
*/

void LSM303DLH_Magn_ReadOut(u8* out)
{
  LSM303DLH_I2C_BufferRead(LSM_M_I2C_ADDRESS, out, LSM_M_OUT_X_H_ADDR, 6);
}

/**
* @brief  Read LSM303DLH output register, and calculate the magnetic field Magn[Ga]=(out_h*256+out_l)*1000/ SENSITIVITY
* @param  out : buffer to store data
* @retval None
*/

void LSM303DLH_Magn_Read_Magn(s16* out)
{
  u8 buffer[6];
  u8 crtlB;

  LSM303DLH_I2C_BufferRead(LSM_M_I2C_ADDRESS, &crtlB, LSM_M_CRB_REG_ADDR, 1);
  LSM303DLH_I2C_BufferRead(LSM_M_I2C_ADDRESS, buffer, LSM_M_OUT_X_H_ADDR, 6);

  /** switch the sensitivity set in the CRTLB*/
  switch(crtlB & 0xE0)
  {
  case 0x40:
    for(int i=0; i<2; i++)
      out[i]=((s16)((u16)buffer[2*i] << 8) + buffer[2*i+1])*1000/LSM_Magn_Sensitivity_XY_1_3Ga;
    out[2]=((s16)((u16)buffer[4] << 8) + buffer[5])*1000/LSM_Magn_Sensitivity_Z_1_3Ga;
    break;
  case 0x60:
    for(int i=0; i<2; i++)
      out[i]=((s16)((u16)buffer[2*i] << 8) + buffer[2*i+1])*1000/LSM_Magn_Sensitivity_XY_1_9Ga;
    out[2]=((s16)((u16)buffer[4] << 8) + buffer[5])*1000/LSM_Magn_Sensitivity_Z_1_9Ga;
    break;
  case 0x80:
    for(int i=0; i<2; i++)
      out[i]=(s16)(((u16)buffer[2*i] << 8) + buffer[2*i+1])*1000/LSM_Magn_Sensitivity_XY_2_5Ga;
    out[2]=((s16)((u16)buffer[4] << 8) + buffer[5])*1000/LSM_Magn_Sensitivity_Z_2_5Ga;
    break;
  case 0xA0:
    for(int i=0; i<2; i++)
      out[i]=(s16)(((u16)buffer[2*i] << 8) + buffer[2*i+1])*1000/LSM_Magn_Sensitivity_XY_4Ga;
    out[2]=((s16)((u16)buffer[4] << 8) + buffer[5])*1000/LSM_Magn_Sensitivity_Z_4Ga;
    break;
  case 0xB0:
    for(int i=0; i<2; i++)
      out[i]=(s16)(((u16)buffer[2*i] << 8) + buffer[2*i+1])*1000/LSM_Magn_Sensitivity_XY_4_7Ga;
    out[2]=((s16)((u16)buffer[4] << 8) + buffer[5])*1000/LSM_Magn_Sensitivity_Z_4_7Ga;
    break;
  case 0xC0:
    for(int i=0; i<2; i++)
      out[i]=(s16)(((u16)buffer[2*i] << 8) + buffer[2*i+1])*1000/LSM_Magn_Sensitivity_XY_5_6Ga;
    out[2]=((s16)((u16)buffer[4] << 8) + buffer[5])*1000/LSM_Magn_Sensitivity_Z_5_6Ga;
    break;
  case 0xE0:
    for(int i=0; i<2; i++)
      out[i]=(s16)(((u16)buffer[2*i] << 8) + buffer[2*i+1])*1000/LSM_Magn_GAIN_8_1;
    out[2]=((s16)((u16)buffer[4] << 8) + buffer[5])*1000/LSM_Magn_Sensitivity_Z_8_1Ga;
    break;
  }
}



/**
* @brief  Read LSM303DLH magnetic field output register and compute the s16 value
* @param  out : buffer to store data
* @retval None
*/

void LSM303DLH_Magn_Read_RawData(s16* out)
{
  u8 buffer[6];

  LSM303DLH_I2C_BufferRead(LSM_M_I2C_ADDRESS, buffer, LSM_M_OUT_X_H_ADDR, 6);
  
  for(int i=0; i<3; i++)
      out[i]=((s16)((u16)buffer[2*i] << 8) + buffer[2*i+1]);
}
/**
*@}
*/ /* end of group Magnetometer_Function */

/**
 * @}
 */ /* end of group Magnetometer */

/**
*@}
*/ /* end of group LSM303DLH */

/******************* (C) COPYRIGHT 2010 STMicroelectronics *****END OF FILE****/
