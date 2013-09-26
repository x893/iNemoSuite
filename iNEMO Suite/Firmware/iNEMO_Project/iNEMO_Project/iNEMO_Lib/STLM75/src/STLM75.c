/**
  * @file    STLM75.c
  * @author  ART Team IMS-Systems Lab
  * @version V2.2
  * @date    01/11/2011
  * @brief   This file provides a set of functions needed to manage the
  *          communication between STM32 I2C master and STLM75 I2C slave.
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




/* Includes ------------------------------------------------------------------*/
#include "STLM75.h"
#include "HAL_STLM75.h"
#include "iNEMO_conf.h"

/**
* @addtogroup STLM75
* @{
*/

/**
* @defgroup STLM75_API
* @{
*/

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/



/**
* @brief  Initializes the I2C peripheral used to drive the STLM75
* @param  None
* @retval None
*/

void STLM75_I2C_Init(void)
{
  I2C_InitTypeDef  I2C_InitStructure;
  GPIO_InitTypeDef GPIO_InitStructure;

  /* Enable I2C and GPIO clocks */
  RCC_APB1PeriphClockCmd(TEMP_RCC_Periph_I2C, ENABLE); 
  RCC_APB2PeriphClockCmd(TEMP_RCC_Port_I2C, ENABLE);
  
  /* Configure I2C pins: SCL and SDA */
  GPIO_InitStructure.GPIO_Pin =  TEMP_I2C_SCL_Pin | TEMP_I2C_SDA_Pin;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_OD;
  GPIO_Init(TEMP_I2C_Port, &GPIO_InitStructure);
  
  /* I2C configuration */
  I2C_InitStructure.I2C_Mode = I2C_Mode_I2C;
  I2C_InitStructure.I2C_DutyCycle = I2C_DutyCycle_2;
  I2C_InitStructure.I2C_OwnAddress1 = STLM75_ADDRESS;
  I2C_InitStructure.I2C_Ack = I2C_Ack_Enable;
  I2C_InitStructure.I2C_AcknowledgedAddress = I2C_AcknowledgedAddress_7bit;
  I2C_InitStructure.I2C_ClockSpeed = TEMP_I2C_Speed;
  
    /* Apply I2C configuration after enabling it */
  I2C_Init(TEMP_I2C, &I2C_InitStructure);  
  
  /* I2C Peripheral Enable */
  I2C_Cmd(TEMP_I2C, ENABLE);
  
}

/**
* @brief  Initializes the OS/INT pin interrupt
* @param  None
* @retval None
*/

#ifdef OS_INT_ENABLE

void STLM75_INT_Config(void)
{
  NVIC_InitTypeDef NVIC_InitStructure;
  EXTI_InitTypeDef EXTI_InitStructure;
  GPIO_InitTypeDef GPIO_InitStructure;

  /* Enable INT pad GPIO clocks */
  RCC_APB2PeriphClockCmd(STLM75_INT_RCC, ENABLE);
 
  /* Configure OS/INT pin as input floating */
  GPIO_InitStructure.GPIO_Pin = STLM75_INT_Pin;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING ;
  GPIO_Init(STLM75_INT_Port, &GPIO_InitStructure);
   
  /* Connect STLM75_INT_EXTI_Line to STLM75_INT_Pin */
  GPIO_EXTILineConfig(STLM75_INT_Port_Source, STLM75_INT_Pin_Source);

  /* Configure STLM75_INT_EXTI_Line to generate an interrupt on STLM75_INT_Edge edge */  
  EXTI_InitStructure.EXTI_Line = STLM75_INT_EXTI_Line;  
  EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;
  EXTI_InitStructure.EXTI_Trigger = STLM75_INT_Edge;
  EXTI_InitStructure.EXTI_LineCmd = ENABLE;
  EXTI_Init(&EXTI_InitStructure);
  
  /* Enable the STLM75_INT_EXTI_IRQCHANNEL Interrupt */
  NVIC_InitStructure.NVIC_IRQChannel = STLM75_INT_EXTI_IRQCHANNEL;
  NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = STLM75_INT_Preemption_Priority;
  NVIC_InitStructure.NVIC_IRQChannelSubPriority = STLM75_INT_Sub_Priority;
  NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
  NVIC_Init(&NVIC_InitStructure);
}
#endif


/**
* @brief  Set interrupt configuration of STLM75
* @param  STLM75_Interrupt_Struct: pointer to a STLM75_InterruptTypeDef structure that
*         contains the interrupt configuration setting for the STLM75.
* @retval None
*/

#ifdef OS_INT_ENABLE

void STLM75_Interrupt_Config(STLM75_InterruptTypeDef *STLM75_Interrupt_Struct)
{
  u8 tmpreg1 = 0x00;
  
  tmpreg1 |= (u8)(STLM75_Interrupt_Struct->Mode | STLM75_Interrupt_Struct->Polarity |
                  ((STLM75_Interrupt_Struct->Fault_Number)<<3));
  
  STLM75_Write(&tmpreg1, CONF_REG_ADDR, 1);
  STLM75_Set_Over_Limit(STLM75_Interrupt_Struct->Over_Limit_Value);
  STLM75_Set_Hysteresis(STLM75_Interrupt_Struct->Hysteresis_Value);
  
}
#endif

/**
* @brief  Read temperature data registers
* @param  pBuffer : pointer to the buffer that receives the temperature
*                   data read from the STLM75. It will give in pBuffer the TMSB byte
*                   and in pBuffer++ the TLSB byte. Temperature data are expressed as
*                   2's complement numbers.
* @retval None
*/


void STLM75_Read_Temperature_Regs(u8* pBuffer)
{

  u8 temp[2]={0,0};
  STLM75_Read(&temp[0], TEMP_REG_ADDR, 2);
  *pBuffer=temp[0];  
  pBuffer++;
  *pBuffer=temp[1];
  
}


/**
* @brief  Read temperature registers and put in a signed 16-bit variable
* @param  out : variable where put the raw data
* @retval None
*/

void STLM75_Read_Raw_Data(s16* out)
{

  u8 temp[2]={0,0};
  STLM75_Read(&temp[0], TEMP_REG_ADDR, 2);
  *out = (s16)(((u16)temp[0] << 8) + temp[1]);
  
}


/**
* @brief  Read temperature data
* @param  refvalue : Temperature data expressed as
*                    2's complement numbers and in tenth of °C
* @retval None
*/

void STLM75_Read_Temperature_Signed(s16* refvalue)
{
  u8 tmp = 0;
  u8 temp[2]={0,0};
  s16 value = 0x00;
  STLM75_Read(&temp[0], TEMP_REG_ADDR, 2);
  tmp = (temp[1]>>7) + (temp[0]<<1);
  value = (s16)((((u16)(temp[0]&0x80))<<8) + (u16)(tmp));
  *refvalue = (s16)(value*T_Resolution);  // expressed in decimal of °C
     
}

/**
* @brief  Enables or disables the lowpower mode for STLM75
* @param  refvalue : NewState: new state for the lowpower mode.
*         This parameter can be one of following parameters:
*         @arg ENABLE
*         @arg DISABLE
* @retval None
*/

void STLM75_Lowpower_Cmd(FunctionalState NewState)
{
  u8 tmpreg = 0x00;
  STLM75_Read(&tmpreg, CONF_REG_ADDR, 1);
  if(NewState==ENABLE)
    tmpreg |= 0x01;
  else
    tmpreg &= 0xF7;
  STLM75_Write(&tmpreg, CONF_REG_ADDR, 1);
}

/**
* @brief  Set temperature over-limit reference
* @param  refvalue : temperature threshold value expressed in tenth of °C
*                    with step of 5 tenth of °C
* @retval None
*/

void STLM75_Set_Over_Limit(s16 refvalue)
{
  s16 temp;
  u8 tempbuffer[2];
  u8 tmp1, tmp2;
  temp = (s16) (refvalue/T_Resolution);
  tmp1 = (u8)(temp>>8);
  tmp2 = (u8)(temp);
  tempbuffer[0] =tmp1 + (tmp2>>1);
  tempbuffer[1]= tmp2<<7;
  STLM75_Write(&tempbuffer[0], TOS_REG_ADDR, 2);
  
}

/**
* @brief  Set Hysteresis threshold
* @param  refvalue : Hysteresis threshold value expressed in tenth of °C
*                    with step of 5 tenth of °C
* @retval None
*/

void STLM75_Set_Hysteresis(s16 refvalue)
{
  s16 temp;
  u8 tempbuffer[2];
  u8 tmp1, tmp2;
  temp = (s16) (refvalue/T_Resolution);
  tmp1 = (u8)(temp>>8);
  tmp2 = (u8)(temp);
  tempbuffer[0] =tmp1 + (tmp2>>1);
  tempbuffer[1]= tmp2<<7;
  STLM75_Write(&tempbuffer[0], THYS_REG_ADDR, 2);
  
}

/**
* @brief  Set the command/Pointer register
* @param  eRegPointer : pointer value to write in the Command/Pointer
*                       register the buffer that receives the data read
*                       from the STLM75.
* @retval None
*/

void STLM75_SetPointer(u8 eRegPointer)
{
  iNEMO_ENTER_CRITICAL();    
  I2C_GenerateSTART(TEMP_I2C, ENABLE);
  
  /* Test on EV5 and clear it */
  while(!I2C_CheckEvent(TEMP_I2C, I2C_EVENT_MASTER_MODE_SELECT));
  
  /* Send STLM75 address for write */
  I2C_Send7bitAddress(TEMP_I2C, STLM75_ADDRESS, I2C_Direction_Transmitter);
  
  /* Test on EV6 and clear it */
  while(!I2C_CheckEvent(TEMP_I2C, I2C_EVENT_MASTER_TRANSMITTER_MODE_SELECTED));
  
  /* Set Pointer Byte */
  I2C_SendData(TEMP_I2C, eRegPointer);
  
  /* Test on EV8 and clear it */
  while(!I2C_CheckEvent(TEMP_I2C, I2C_EVENT_MASTER_BYTE_TRANSMITTED));
  
  I2C_GenerateSTOP(TEMP_I2C, ENABLE);
  iNEMO_EXIT_CRITICAL();    
}

/**
* @brief  Writes one or more byte to the STLM75 registers.
* @param  pBuffer : pointer to the buffer  containing the data to be 
*                    written into STLM75.
* @param  WriteAddr : STLM75's internal address to write to.
* @param  NumByteToWrite: Number of bytes to write
* @retval None
*/

void STLM75_Write(u8* pBuffer, u8 WriteAddr, u8 NumByteToWrite)
{
  iNEMO_ENTER_CRITICAL();    
  /* Send STRAT condition */
  I2C_GenerateSTART(TEMP_I2C, ENABLE);

  /* Test on EV5 and clear it */
  while(!I2C_CheckEvent(TEMP_I2C, I2C_EVENT_MASTER_MODE_SELECT));  
  
  /* Send STLM75 address for write */
  I2C_Send7bitAddress(TEMP_I2C, STLM75_ADDRESS, I2C_Direction_Transmitter);
  
  /* Test on EV6 and clear it */
  while(!I2C_CheckEvent(TEMP_I2C, I2C_EVENT_MASTER_TRANSMITTER_MODE_SELECTED));
  
  /* Send the STLM75's internal address to write to */
  I2C_SendData(TEMP_I2C, WriteAddr);
  
  /* Test on EV8 and clear it */
  while(!I2C_CheckEvent(TEMP_I2C, I2C_EVENT_MASTER_BYTE_TRANSMITTED));

  
  while(NumByteToWrite)
  {
    /* Send the byte to be written */
    I2C_SendData(TEMP_I2C, *pBuffer);
    
    /* Test on EV8 and clear it */
    while(!I2C_CheckEvent(TEMP_I2C, I2C_EVENT_MASTER_BYTE_TRANSMITTED));
    
    pBuffer++;
    NumByteToWrite--;
  }
  
  /* Send STOP condition */
  I2C_GenerateSTOP(TEMP_I2C, ENABLE);
  iNEMO_EXIT_CRITICAL();    
  
}

/**
* @brief  Writes one or more byte to the STLM75 registers.
* @param  pBuffer : pointer to the buffer that receives the data read 
*                    from the STLM75.
* @param  ReadAddr : STLM75's internal address to read from.
* @param  NumByteToRead:number of bytes to read from the STLM75.
* @retval None
*/

void STLM75_Read(u8* pBuffer, u8 ReadAddr, u8 NumByteToRead)
{
  iNEMO_ENTER_CRITICAL();  
    /* While the bus is busy */
  while(I2C_GetFlagStatus(TEMP_I2C, I2C_FLAG_BUSY));
  
  /* Send START condition */
  I2C_GenerateSTART(TEMP_I2C, ENABLE);
  
  /* Test on EV5 and clear it */
  while(!I2C_CheckEvent(TEMP_I2C, I2C_EVENT_MASTER_MODE_SELECT));
   
  /* Send STLM75 address for write */
  I2C_Send7bitAddress(TEMP_I2C, STLM75_ADDRESS, I2C_Direction_Transmitter);

  /* Test on EV6 and clear it */
  while(!I2C_CheckEvent(TEMP_I2C, I2C_EVENT_MASTER_TRANSMITTER_MODE_SELECTED));
  
  /* Clear EV6 by setting again the PE bit */
  I2C_Cmd(TEMP_I2C, ENABLE); 

  if(NumByteToRead>1)
  {
    I2C_AcknowledgeConfig(I2C2, ENABLE);
  }  
  
  /* Send the STLM75's internal address to write to */
  I2C_SendData(TEMP_I2C, ReadAddr);  

  /* Test on EV8 and clear it */
  while(!I2C_CheckEvent(TEMP_I2C, I2C_EVENT_MASTER_BYTE_TRANSMITTED));
  
  /* Send START condition a second time */  
  I2C_GenerateSTART(TEMP_I2C, ENABLE);
  
  /* Test on EV5 and clear it */
  while(!I2C_CheckEvent(TEMP_I2C, I2C_EVENT_MASTER_MODE_SELECT));
  
  /* Send STLM75 address for read */
  I2C_Send7bitAddress(TEMP_I2C, STLM75_ADDRESS, I2C_Direction_Receiver);
  
  /* Test on EV6 and clear it */
  while(!I2C_CheckEvent(TEMP_I2C, I2C_EVENT_MASTER_RECEIVER_MODE_SELECTED));
  
  /* While there is data to be read */
  while(NumByteToRead)  
  {
    if(NumByteToRead == 1)
    {
      /* Disable Acknowledgement */
      I2C_AcknowledgeConfig(TEMP_I2C, DISABLE);
      
      /* Send STOP Condition */
      I2C_GenerateSTOP(TEMP_I2C, ENABLE);
    }

    /* Test on EV7 and clear it */
    if(I2C_CheckEvent(TEMP_I2C, I2C_EVENT_MASTER_BYTE_RECEIVED))  
    {      
      /* Read a byte from the STLM75 */
      *pBuffer = I2C_ReceiveData(TEMP_I2C);

      /* Point to the next location where the byte read will be saved */
      pBuffer++; 
      
      /* Decrement the read bytes counter */
      NumByteToRead--;        
    }   
  }

  /* Enable Acknowledgement to be ready for another reception */
  I2C_AcknowledgeConfig(TEMP_I2C, ENABLE);  
  iNEMO_EXIT_CRITICAL();    
}

/**
 * @}
 */ /* end of group STLM75_API */

/**
*@}
*/ /* end of group STLM75 */



/******************* (C) COPYRIGHT 2010 STMicroelectronics *****END OF FILE****/
