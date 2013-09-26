/**
  * @file    iNEMO_lib.c
  * @author  ART Team IMS-Systems Lab
  * @version V2.2
  * @date    01/11/2011
  * @brief   Sensor Hardware Configuration & Setup & API.
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
#include "iNEMO_lib.h"
#include "iNEMO_conf.h"
#include "utils.h"

/**
 * @addtogroup iNEMO_Config
 * @{
 */


/* Private define */
#define BlockSize            512 /*!< Block Size in Bytes */
#define BufferWordsSize      (BlockSize >> 2)
#define NumberOfBlocks       2  /*!< For Multi Blocks operation (Read/Write) */
#define MultiBufferWordsSize ((BlockSize * NumberOfBlocks) >> 2)

#define iNEMO_OffAccX(data)    (data->sOffset[0])
#define iNEMO_OffAccY(data)    (data->sOffset[1])
#define iNEMO_OffAccZ(data)    (data->sOffset[2])

#define iNEMO_OffGyroX(data)    (data->sOffset[3])
#define iNEMO_OffGyroY(data)    (data->sOffset[4])
#define iNEMO_OffGyroZ(data)    (data->sOffset[5])

#define iNEMO_OffMagnX(data)    (data->sOffset[6])
#define iNEMO_OffMagnY(data)    (data->sOffset[7])
#define iNEMO_OffMagnZ(data)    (data->sOffset[8])

#define iNEMO_OffPress(data)    (data->sOffset[9])
#define iNEMO_OffTemp(data)     (data->sOffset[10])


#define iNEMO_GainAccX(data)     (data->uGain[0])
#define iNEMO_GainAccY(data)     (data->uGain[1])
#define iNEMO_GainAccZ(data)     (data->uGain[2])

#define iNEMO_GainGyroX(data)    (data->uGain[3])
#define iNEMO_GainGyroY(data)    (data->uGain[4])
#define iNEMO_GainGyroZ(data)    (data->uGain[5])

#define iNEMO_GainMagnX(data)    (data->uGain[6])
#define iNEMO_GainMagnY(data)    (data->uGain[7])
#define iNEMO_GainMagnZ(data)    (data->uGain[8])

#define iNEMO_GainPress(data)    (data->uGain[9])
#define iNEMO_GainTemp(data)     (data->uGain[10])




/* Private variables */
volatile TestStatus EraseStatus = FAILED, TransferStatus1 = FAILED, TransferStatus2 = FAILED;
static u32 s_Buffer_Block_Tx[BufferWordsSize];
static u32 s_Buffer_Block_Rx[BufferWordsSize];
static u32 s_Buffer_MultiBlock_Tx[MultiBufferWordsSize];
static u32 s_Buffer_MultiBlock_Rx[MultiBufferWordsSize];



/**
 * @addtogroup iNEMO_Config_Function
 *@{
 */


/**
* @brief Configure the hardware for the iNEMO platform
* */
void iNEMO_HW_Config(void)
{

#ifdef _ULED
  iNEMO_Led_Init(LED1);
#endif //_ULED

#ifdef _VCOM
  iNEMO_USB_Disconnet_Pin_Config();
  USB_Cable_Config(ENABLE);  
  Set_USBClock();
  USB_Interrupts_Config();
  USB_Init();
#endif //_VCOM


#ifdef _PRESS
  LPS001DL_I2C_Init();
  #ifdef INT1_PAD_ENABLE
  LPS001DL_INT1_Config();
  #endif //INT1_PAD_ENABLE
#endif //_PRESS

#ifdef _TEMP
  STLM75_I2C_Init();
#endif //_TEMP

#ifdef _SDIO
  SD_Init();
#endif // _SDIO

#ifdef _PBUTT
  iNEMO_Button_Init(BUTTON_KEY, BUTTON_MODE_GPIO);
#endif //_PBUTT

#ifdef _6X
  LSM303DLH_I2C_Init();
#endif

#ifdef _GYRO_RPY
  LPRYxxxAL_ADC_Init();
  LPRYxxxAL_DMA_Init();
  LPRYxxxAL_PD_ST_Init();
#endif
}

/**
* @brief  Initialize the iNEMO data structur
*/
void iNEMO_Data_Init(iNEMO_DATA* data)
{
  iNEMO_OffAccX(data)=iNEMO_Default_OffAccX;
  iNEMO_OffAccY(data)=iNEMO_Default_OffAccY;
  iNEMO_OffAccZ(data)=iNEMO_Default_OffAccZ;

  iNEMO_OffGyroX(data)=iNEMO_Default_OffGyroX;
  iNEMO_OffGyroY(data)=iNEMO_Default_OffGyroY;
  iNEMO_OffGyroZ(data)=iNEMO_Default_OffGyroZ;

  iNEMO_OffMagnX(data)=iNEMO_Default_OffMagnX;
  iNEMO_OffMagnY(data)=iNEMO_Default_OffMagnY;
  iNEMO_OffMagnZ(data)=iNEMO_Default_OffMagnZ;

  iNEMO_OffPress(data)=iNEMO_Default_OffPress;
  iNEMO_OffTemp(data)=iNEMO_Default_OffTemp;

  iNEMO_GainAccX(data)= iNEMO_Default_GainAccX;
  iNEMO_GainAccY(data)= iNEMO_Default_GainAccY;
  iNEMO_GainAccZ(data)= iNEMO_Default_GainAccZ;

  iNEMO_GainGyroX(data)=iNEMO_Default_GainGyroX;
  iNEMO_GainGyroY(data)=iNEMO_Default_GainGyroY;
  iNEMO_GainGyroZ(data)=iNEMO_Default_GainGyroZ;

  iNEMO_GainMagnX(data)=iNEMO_Default_GainMagnX;
  iNEMO_GainMagnY(data)=iNEMO_Default_GainMagnY;
  iNEMO_GainMagnZ(data)=iNEMO_Default_GainMagnZ;

  iNEMO_GainPress(data)=iNEMO_Default_GainPress;
  iNEMO_GainTemp(data)=iNEMO_Default_GainTemp;
  
}


/**
* @brief  Initialize the iNEMO sensor platform
*/
void iNEMO_Config(void)
{

#ifdef _GYRO_RPY
 LPRYxxxAL_On();
 LPRYxxxAL_ST_Off();
#endif

#ifdef _6X

  LSM_Acc_ConfigTypeDef  LSM_Acc_InitStructure;
  LSM_Acc_Filter_ConfigTypeDef LSM_Acc_FilterStructure;
  LSM_Acc_InitStructure.Power_Mode = LSM_Acc_Lowpower_NormalMode;
  LSM_Acc_InitStructure.ODR = LSM_Acc_ODR_50;
  LSM_Acc_InitStructure.Axes_Enable= LSM_Acc_XYZEN;
  LSM_Acc_InitStructure.FS = LSM_Acc_FS_2;
  LSM_Acc_InitStructure.Data_Update = LSM_Acc_BDU_Continuos;
  LSM_Acc_InitStructure.Endianess=LSM_Acc_Big_Endian;

  LSM_Acc_FilterStructure.HPF_Enable=LSM_Acc_Filter_Disable;
  LSM_Acc_FilterStructure.HPF_Mode=LSM_Acc_FilterMode_Normal;
  LSM_Acc_FilterStructure.HPF_Reference=0x00;
  LSM_Acc_FilterStructure.HPF_Frequency=LSM_Acc_Filter_HPc16;

  LSM303DLH_Acc_Config(&LSM_Acc_InitStructure);
  LSM303DLH_Acc_Filter_Config(&LSM_Acc_FilterStructure);

  LSM_Magn_ConfigTypeDef LSM_Magn_InitStructure;
  LSM_Magn_InitStructure.M_ODR = LSM_Magn_ODR_30;
  LSM_Magn_InitStructure.Meas_Conf = LSM_Magn_MEASCONF_NORMAL;
  LSM_Magn_InitStructure.Gain = LSM_Magn_GAIN_1_3;
  LSM_Magn_InitStructure.Mode = LSM_Magn_MODE_CONTINUOS ;
  LSM303DLH_Magn_Config(&LSM_Magn_InitStructure);

#endif

#ifdef _ACC
  LIS331DLH_ConfigTypeDef  LIS331DLH_InitStructure;
  LIS331DLH_Filter_ConfigTypeDef LIS331DLH_FilterStructure;
  LIS331DLH_InitStructure.Power_Mode = LIS331DLH_Lowpower_NormalMode;
  LIS331DLH_InitStructure.ODR = LIS331DLH_ODR_50;
  LIS331DLH_InitStructure.Axes_Enable= LIS331DLH_XYZEN;
  LIS331DLH_InitStructure.FS = LIS331DLH_FS_2;
  LIS331DLH_InitStructure.Data_Update = LIS331DLH_BDU_Continuos;
  LIS331DLH_InitStructure.Endianess=LIS331DLH_Little_Endian;

  LIS331DLH_FilterStructure.HPF_Enable=LIS331DLH_Filter_Disable;
  LIS331DLH_FilterStructure.HPF_Mode=LIS331DLH_FilterMode_Normal;
  LIS331DLH_FilterStructure.HPF_Reference=0x00;
  LIS331DLH_FilterStructure.HPF_Frequency=LIS331DLH_Filter_HPc64;

  LIS331DLH_Config(&LIS331DLH_InitStructure);
  LIS331DLH_Filter_Config(&LIS331DLH_FilterStructure);
#endif /*_ACC */

#ifdef _MAG
  HMC5843_ConfigTypeDef HMC5843_InitStructure;
  HMC5843_InitStructure.M_ODR = HMC5843_ODR_10;
  HMC5843_InitStructure.Meas_Conf = HMC5843_MEASCONF_NORMAL;
  HMC5843_InitStructure.Gain = HMC5843_GAIN_1;
  HMC5843_InitStructure.Mode = HMC5843_MODE_CONTINUOS ;
  HMC5843_Config(&HMC5843_InitStructure);
#endif /*_MAG */

#ifdef _PRESS
  LPS001DL_ConfigTypeDef  LPS001DL_InitStructure;
  LPS001DL_InterruptTypeDef LPS001DL_InterruptStructure;
  /* LPS001DL configuration */
  LPS001DL_InitStructure.Lowpower = LPS001DL_Lowpower_Disable;
  LPS001DL_InitStructure.Output_Data_Rate = LPS001DL_Output_Data_Rate_12_12;
  LPS001DL_InitStructure.Data_Update = LPS001DL_BDU_Continuos; //LPS001DL_BDU_Single;
  LPS001DL_InitStructure.Endianess = LPS001DL_Little_Endian;

  /* LPS001DL interrupt configuration */
  LPS001DL_InterruptStructure.Mode = LPS001DL_Interrupt_Active_High;
  LPS001DL_InterruptStructure.PP_OD = LPS001DL_Interrupt_Push_Pull;
  LPS001DL_InterruptStructure.Int2_Pad_Mode =LPS001DL_Interrupt_Pressure_Low;
  LPS001DL_InterruptStructure.Int1_Pad_Mode = LPS001DL_Interrupt_Pressure_High;
  LPS001DL_InterruptStructure.Latch = LPS001DL_Interrupt_Latch_Disable;
  LPS001DL_InterruptStructure.Delta_Press_Low = LSP001DL_Interrupt_DPL_Enable;
  LPS001DL_InterruptStructure.Delta_Press_High = LSP001DL_Interrupt_DPH_Enable;

  LPS001DL_Config(&LPS001DL_InitStructure);
  LPS001DL_Interrupt_Config(&LPS001DL_InterruptStructure);
  LPS001DL_PowerDown_Cmd(DISABLE);
#endif /*_PRESS */

#ifdef _TEMP
#ifdef OS_INT_ENABLE
  STLM75_InterruptTypeDef STLM75_InterruptStructure;
  /* STLM75 interrupt configuration */
  STLM75_InterruptStructure.Mode = STLM75_Interrupt_Mode; //STLM75_Comparator_Mode;
  STLM75_InterruptStructure.Polarity = STLM75_Polarity_Low;
  STLM75_InterruptStructure.Fault_Number = Fault_Value_1;
  STLM75_InterruptStructure.Over_Limit_Value = 305;
  STLM75_InterruptStructure.Hysteresis_Value = 290;

  STLM75_Interrupt_Config(&STLM75_InterruptStructure);

#endif //OS_INT_ENABLE
#endif /*_TEMP */

}

/**
* @brief  Change a a configuration parameter of a iNEMO sensor
* @param pData : poiter to iNEMO_data structure
* @param usensor : the sensor type (0x00 = Accelerometer; 0x01 = Gyroscope; 0x02 Pitch/Roll Gyro; 0x03 Yaw Gyro; 0x04 = Pressure; 0x05 Temp)
* @ulenght : Lenght of value payload
* @param uparamter : paramenter to change
* @param pvalue : new value to set
*/
bool iNEMO_Set_Sensor(iNEMO_DATA * pdata, u8 usensor, u8 uparameter, u8 ulenght, u8* pvalue)
{
  bool isAllowed =FALSE;
 
  switch(usensor)
  {
  case 0x00 :  /*!< Accelerometer */
    isAllowed = iNEMO_Acc_Set_Config(pdata, uparameter, ulenght, pvalue);
    break;
    
  case 0x01 :  /*!< Magnetometer */
    isAllowed = iNEMO_Magn_Set_Config(pdata,uparameter,ulenght, pvalue);
    break;
    
  case 0x02  :  /*!< Roll and Pitch Gyro */
    isAllowed = iNEMO_GyroPR_Set_Config(pdata,uparameter,ulenght, pvalue);
    break;
    
  case 0x03  :   /*!< Yaw Gyro */
    isAllowed = iNEMO_GyroYaw_Set_Config(pdata,uparameter,ulenght, pvalue);
    break;
    
  case 0x04  :  /*!< Pressure Sensor*/
    isAllowed = iNEMO_Pressure_Set_Config(pdata,uparameter,ulenght, pvalue);
    break;
    
  case 0x05  : /*!< Temperature Sensor*/     
    isAllowed = iNEMO_Temp_Set_Config(pdata,uparameter,ulenght, pvalue);
    break;
    }
  
   return  isAllowed;      
}




/**
* @brief  Change a a configuration parameter of a iNEMO sensor
* @param pData : poiter to iNEMO_data structure
* @param parameter : paramenter to change  <ul>
 * <li>0x00 - Output data rate</li>
 * <li>0x01 Full Scale </li>
 * <li>0x02 HPF  </li>
 * <li>0x03 Offset X </li>
 * <li>0x04 Offset Y </li>
 * <li>0x05 Offset Z </li>
 * </ul>  
 * @ulenght : Lenght of value payload
 * @param value : new value to set
*/  
bool iNEMO_Acc_Set_Config( iNEMO_DATA * pdata, u8 uparameter, u8 ulenght, u8* pvalue)  
  {
    bool isAllowed=FALSE; 
    
    switch(uparameter)
    {
    case 0x00: /*!< set ODR */
     
      if(pvalue[0] < 0x04 && ulenght == 2)
      {   
        u8 uCtrl=0;;
        LSM303DLH_I2C_BufferRead(LSM_A_I2C_ADDRESS, &uCtrl, LSM_A_CTRL_REG1_ADDR, 1);
        uCtrl = (uCtrl & 0xE7) + (pvalue[0] << 3);  
        LSM303DLH_I2C_ByteWrite(LSM_A_I2C_ADDRESS, &uCtrl, LSM_A_CTRL_REG1_ADDR);
        LSM303DLH_I2C_BufferRead(LSM_A_I2C_ADDRESS, &uCtrl, LSM_A_CTRL_REG1_ADDR, 1);
        /* check if the command has been executed */
        if(((uCtrl >> 3) & 0x03) == pvalue[0])
          /* if yes  send ack  */  
          isAllowed=TRUE;
        else
          /* else send nack  */              
          isAllowed=FALSE;    
      }
      else
      {
        isAllowed=FALSE;
      }
      break;    
      
    case  0x01:  /*!< Set Full scale*/
      
      if(pvalue[0] < 0x04 &&  pvalue[0] != 0x02  && ulenght == 2 )
      {
        u8 uCtrl=0;
        LSM303DLH_I2C_BufferRead(LSM_A_I2C_ADDRESS, &uCtrl, LSM_A_CTRL_REG4_ADDR, 1);
        uCtrl =(uCtrl & 0xCF) + ((pvalue[0] & 0x03) << 4);  
        LSM303DLH_I2C_ByteWrite(LSM_A_I2C_ADDRESS, &uCtrl, LSM_A_CTRL_REG4_ADDR);
        LSM303DLH_I2C_BufferRead(LSM_A_I2C_ADDRESS, &uCtrl, LSM_A_CTRL_REG4_ADDR, 1);
        /* check if the command has been executed */        
        if(((uCtrl & 0x30) >> 4 ) == pvalue[0]) 
          /* if yes   */            
        {
          switch(pvalue[0])  
          {
            /* update Gain Value*/
          case 0x00:
              iNEMO_GainAccX(pdata)= LSM_Acc_Sensitivity_2g;
              iNEMO_GainAccY(pdata)= LSM_Acc_Sensitivity_2g;
              iNEMO_GainAccZ(pdata)= LSM_Acc_Sensitivity_2g;
          break;
          
          case 0x01:
              iNEMO_GainAccX(pdata)= LSM_Acc_Sensitivity_4g;
              iNEMO_GainAccY(pdata)= LSM_Acc_Sensitivity_4g;
              iNEMO_GainAccZ(pdata)= LSM_Acc_Sensitivity_4g;
              break;

          case 0x03:
              iNEMO_GainAccX(pdata)= LSM_Acc_Sensitivity_8g;
              iNEMO_GainAccY(pdata)= LSM_Acc_Sensitivity_8g;
              iNEMO_GainAccZ(pdata)= LSM_Acc_Sensitivity_8g; 
              break;
          }        
       
          isAllowed=TRUE;
        }
        else
          /* else  send nack  */              
          isAllowed=FALSE;
      }
      else
        isAllowed=FALSE;
      break;   
      
    case  0x02:  /* HPF enable*/
      
           if(ulenght == 3)  
          { 
            
            u8 temp=pvalue[0];
            /* 
            pvalue[0] = | RFU |RFU |Filter Enable/Disable |REF ENABLE/DISABLE |HP1 |HP0 | ODR1 |ODR0
            */
            if((temp & 0x20) == 0x20)  /* check filter ENABLE command */  
            {   
              u8 uCtrl1, uCtrl2, temp2, ref;
              LSM303DLH_I2C_BufferRead(LSM_A_I2C_ADDRESS, &uCtrl1, LSM_A_CTRL_REG1_ADDR, 1); 
              uCtrl1 =  (uCtrl1 & 0xE7) + ((temp  & 0x03) << 3);  //set ODR
              LSM303DLH_I2C_ByteWrite(LSM_A_I2C_ADDRESS, &uCtrl1, LSM_A_CTRL_REG1_ADDR);/*!<set the ODR value in the ctrl1 register*/
              LSM303DLH_I2C_BufferRead(LSM_A_I2C_ADDRESS, &uCtrl1, LSM_A_CTRL_REG1_ADDR, 1);  
              
              if((temp & 0x10) == 0x10)  /* check if reference is enabled */
              {
                LSM303DLH_I2C_BufferRead(LSM_A_I2C_ADDRESS, &temp2, LSM_A_CTRL_REG2_ADDR, 1);
                uCtrl2 = ((temp2  & 0xCC) + ((temp  & 0x0C) >> 2) + 0x30); /*  !<set cut off frequency and bits to enble filter and enable reference */   
                LSM303DLH_I2C_ByteWrite(LSM_A_I2C_ADDRESS, &uCtrl2, LSM_A_CTRL_REG2_ADDR);
                LSM303DLH_I2C_BufferRead(LSM_A_I2C_ADDRESS, &uCtrl2, LSM_A_CTRL_REG2_ADDR, 1);  
                LSM303DLH_I2C_ByteWrite(LSM_A_I2C_ADDRESS, &pvalue[1], LSM_A_REFERENCE_REG_ADDR); /*!<WRITE the refence value in the LSM_A_REFERENCE_REG_ADDR register*/        
                LSM303DLH_I2C_BufferRead(LSM_A_I2C_ADDRESS, &ref, LSM_A_REFERENCE_REG_ADDR,1);    
                temp2= ((uCtrl2 & 0x03) <<2) + (uCtrl2 & 0x30);
                temp2 = (temp2 & 0xFC) + ((uCtrl1 & 0x18) >> 3); 
                if((temp2 == temp)  && (ref==pvalue[1])) /*!< check if the command has been executed && ((uCtrl2 & 0x10) == 0x10)*/         
                 isAllowed=TRUE;
                else
                isAllowed=FALSE;           
              }
              else
              { 
                
                LSM303DLH_I2C_BufferRead(LSM_A_I2C_ADDRESS, &uCtrl2, LSM_A_CTRL_REG2_ADDR, 1);
                uCtrl2 = ((temp2  & 0xCC) + ((temp  & 0x0C) >> 2) + 0x10);  /*!< set cut off frequency and set to 1 FDS bit to enble filter */            
                LSM303DLH_I2C_ByteWrite(LSM_A_I2C_ADDRESS, &uCtrl2, LSM_A_CTRL_REG2_ADDR);
                LSM303DLH_I2C_BufferRead(LSM_A_I2C_ADDRESS, &uCtrl2, LSM_A_CTRL_REG2_ADDR, 1);  
                uCtrl1 = ((uCtrl1 & 0x18) >> 3);
                uCtrl1 = uCtrl1  + ((uCtrl2 & 0x03) <<2) ;
                uCtrl1 = uCtrl1  +  ((uCtrl2 & 0x10)<<1);
                if((uCtrl1 == temp ) && ((uCtrl2 & 0x10) == 0x10)) /*!< check if the command has been executed*/     
                  isAllowed=TRUE;
                else
                  isAllowed=FALSE;               
              }  
            }
            else /* filter disable*/
            {
                u8 uCtrl2;
                LSM303DLH_I2C_BufferRead(LSM_A_I2C_ADDRESS, &uCtrl2, LSM_A_CTRL_REG2_ADDR, 1);
                uCtrl2 = (uCtrl2  & 0xCF);  /* !< set to 0 FDS bit to disable filter */            
                LSM303DLH_I2C_ByteWrite(LSM_A_I2C_ADDRESS, &uCtrl2, LSM_A_CTRL_REG2_ADDR);  
                LSM303DLH_I2C_ByteWrite(LSM_A_I2C_ADDRESS, 0x00, LSM_A_REFERENCE_REG_ADDR);
                LSM303DLH_I2C_BufferRead(LSM_A_I2C_ADDRESS, &uCtrl2, LSM_A_CTRL_REG2_ADDR, 1);
                if((uCtrl2  & 0x10) == 0x00)
                   isAllowed=TRUE;
                else
                   isAllowed=FALSE;                    
            }
              
    }
    break;
    
    case 0x03: /* !<  set x axis offset*/
      if(ulenght == 3 )
      {
      iNEMO_OffAccX(pdata)=((s16)pvalue[0] << 8) + pvalue[1];
      isAllowed=TRUE;
      }
      else
        isAllowed=FALSE;
        
      break;
      
    case 0x04: /*!<  set y axis offset*/
      if(ulenght == 3 )
      {
      iNEMO_OffAccY(pdata)=((s16)pvalue[0] << 8) + pvalue[1];
      isAllowed=TRUE;
      }
      else
        isAllowed=FALSE;
        
      break;
      
    case 0x05: /*!< set z axis offset*/
      if(ulenght == 3 )
      {
      iNEMO_OffAccZ(pdata)=((s16)pvalue[0] << 8) + pvalue[1];
      isAllowed=TRUE;
      }
      else
        isAllowed=FALSE;
      break;
 
  }
  return isAllowed;
  }



/**
* @brief  Change a  configuration parameter of a iNEMO magnetometer
* @param parameter : paramenter to change  <ul>
 * <li>0x00 - Output data rate</li>
 * <li>0x01 Full Scale </li>
 * <li>0x02 MAGN operationg mode </li>
 * <li>0x03 Offset X </li>
 * <li>0x04 Offset Y </li>
 * <li>0x05 Offset Z </li>
 * </ul>  
* @param value : new value to set
*/  
  
bool iNEMO_Magn_Set_Config( iNEMO_DATA * pdata, u8 uparameter, u8 ulenght, u8* pvalue)  
  {
    bool isAllowed=FALSE;
    switch(uparameter)
    {
    case 0x00: /*!<  set ODR */
      if(pvalue[0] < 0x07 && ulenght == 2)
      {
        u8 uCtrl;
        LSM303DLH_I2C_BufferRead(LSM_M_I2C_ADDRESS, &uCtrl, LSM_M_CRA_REG_ADDR, 1);      
        uCtrl = (uCtrl & 0xE3) + (pvalue[0]  << 2);  
        LSM303DLH_I2C_ByteWrite(LSM_M_I2C_ADDRESS, &uCtrl, LSM_M_CRA_REG_ADDR);
        LSM303DLH_I2C_BufferRead(LSM_M_I2C_ADDRESS, &uCtrl, LSM_M_CRA_REG_ADDR, 1);
        /* check if the command has been executed */
        if(((uCtrl >>2)  & 0x07) == pvalue[0]) 
          /* if yes  send ack  */  
          isAllowed=TRUE;
        else
          /* else send nack  */              
          isAllowed=FALSE;
        
      }
      else
      {
        isAllowed=FALSE;
      }
      break;    
      
    case  0x01:  /*!< Set Full scale*/
      
      if(pvalue[0] < 0x08 &&  pvalue[0] > 0x00  && ulenght == 2 )
      {
        u8 uCtrl;
        uCtrl =(pvalue[0] << 5) & 0xE0;  
        LSM303DLH_I2C_ByteWrite(LSM_M_I2C_ADDRESS, &uCtrl, LSM_M_CRB_REG_ADDR);
        LSM303DLH_I2C_BufferRead(LSM_M_I2C_ADDRESS, &uCtrl, LSM_M_CRB_REG_ADDR, 1);
        /* check if the command has been executed */
        if(((uCtrl >>5)  & 0x07) == pvalue[0])         
        {
          switch(pvalue[0])  
          {
          case 0x01:
            iNEMO_GainMagnX(pdata)= LSM_Magn_Sensitivity_XY_1_3Ga;
            iNEMO_GainMagnY(pdata)= LSM_Magn_Sensitivity_XY_1_3Ga;
            iNEMO_GainMagnZ(pdata)= LSM_Magn_Sensitivity_XY_1_3Ga;
            break;
            
          case 0x02:
            iNEMO_GainMagnX(pdata)= LSM_Magn_Sensitivity_XY_1_9Ga;
            iNEMO_GainMagnY(pdata)= LSM_Magn_Sensitivity_XY_1_9Ga;
            iNEMO_GainMagnZ(pdata)= LSM_Magn_Sensitivity_Z_1_9Ga;
            break;
            
          case 0x03:
            iNEMO_GainMagnX(pdata)= LSM_Magn_Sensitivity_XY_2_5Ga;
            iNEMO_GainMagnY(pdata)= LSM_Magn_Sensitivity_XY_2_5Ga;
            iNEMO_GainMagnZ(pdata)= LSM_Magn_Sensitivity_Z_2_5Ga; 
            break;
            
          case 0x04:
            iNEMO_GainMagnX(pdata)= LSM_Magn_Sensitivity_XY_4Ga;
            iNEMO_GainMagnY(pdata)= LSM_Magn_Sensitivity_XY_4Ga;
            iNEMO_GainMagnZ(pdata)= LSM_Magn_Sensitivity_Z_4Ga; 
            break;   
            
          case 0x05:
            iNEMO_GainMagnX(pdata)= LSM_Magn_Sensitivity_XY_4_7Ga;
            iNEMO_GainMagnY(pdata)= LSM_Magn_Sensitivity_XY_4_7Ga;
            iNEMO_GainMagnZ(pdata)= LSM_Magn_Sensitivity_Z_4_7Ga; 
            break;          
            
          case 0x06:
            iNEMO_GainMagnX(pdata)= LSM_Magn_Sensitivity_XY_5_6Ga;
            iNEMO_GainMagnY(pdata)= LSM_Magn_Sensitivity_XY_5_6Ga;
            iNEMO_GainMagnZ(pdata)= LSM_Magn_Sensitivity_Z_5_6Ga; 
            break;  

          case 0x07:
            iNEMO_GainMagnX(pdata)= LSM_Magn_Sensitivity_XY_8_1Ga;
            iNEMO_GainMagnY(pdata)= LSM_Magn_Sensitivity_XY_8_1Ga;
            iNEMO_GainMagnZ(pdata)= LSM_Magn_Sensitivity_Z_8_1Ga; 
            break;             
            
          }        
          
          isAllowed=TRUE;
        }
        else
          /* else  send nack  */              
          isAllowed=FALSE;
      }
      else
        isAllowed=FALSE;
      break;   
      
    case  0x02:  /*!<  Magn operating mode*/
      
      if(pvalue[0] < 0x03 && ulenght == 2)
      {
        u8 uCtrl;
        LSM303DLH_I2C_BufferRead(LSM_M_I2C_ADDRESS, &uCtrl, LSM_M_CRA_REG_ADDR, 1);
        uCtrl = (uCtrl & 0xFC) + pvalue[0];  
        LSM303DLH_I2C_ByteWrite(LSM_M_I2C_ADDRESS, &uCtrl, LSM_M_CRA_REG_ADDR);
        LSM303DLH_I2C_BufferRead(LSM_M_I2C_ADDRESS, &uCtrl, LSM_M_CRA_REG_ADDR, 1);
        /* check if the command has been executed */
        if(((uCtrl & 0x03) == pvalue[0])) 
          /* if yes  send ack  */  
          isAllowed=TRUE;
        else
          /* else send nack  */              
          isAllowed=FALSE;
        
      }
      else
      {
        isAllowed=FALSE;
      }
      break; 
    
    case 0x03: /*!< set x axis offset*/
      if(ulenght == 3 )
      {
      iNEMO_OffMagnX(pdata)=((s16)pvalue[0] << 8) + pvalue[1];
      isAllowed=TRUE;
      }
      else
        isAllowed=FALSE;
        
      break;
      
    case 0x04: /*!<  set y axis offset*/
      if(ulenght == 3 )
      {
      iNEMO_OffMagnY(pdata)=((s16)pvalue[0] << 8) + pvalue[1];
      isAllowed=TRUE;
      }
      else
        isAllowed=FALSE;
        
      break;
      
    case 0x05: /*!<  set z axis offset*/
      if(ulenght == 3 )
      {
      iNEMO_OffMagnZ(pdata)=((s16)pvalue[0] << 8) + pvalue[1];
      isAllowed=TRUE;
      }
      else
        isAllowed=FALSE;
      break;
 
  }
  return isAllowed;
}



/**
* @brief  Change a  configuration parameter of a iNEMO gyro roll-pitch
* @param parameter : paramenter to change  <ul>
 * <li>0x00 Full Scale </li>
 * <li>0x01 Offset X </li>
 * <li>0x02 Offset Y </li>
 * </ul>  
* @param value : new value to set
*/  
  
bool iNEMO_GyroPR_Set_Config( iNEMO_DATA * pdata, u8 uparameter, u8 ulenght, u8* pvalue)  
  {
    bool isAllowed=FALSE;
    switch(uparameter)
    {
    case 0x00: /*!<  set FS */
      if((pvalue[0]==0x04 || pvalue[0]==0x08) && ulenght == 2)
      {
          switch(pvalue[0])  
          {
          case 0x04: /*!<  300dps*/
            iNEMO_GainGyroX(pdata)= Gyro_SensitivityLSB_R_300dps;
            iNEMO_GainGyroY(pdata)= Gyro_SensitivityLSB_P_300dps;
            isAllowed=TRUE;
            break;
            
          case 0x08: /*!<  1200dps*/
            iNEMO_GainGyroX(pdata)= Gyro_SensitivityLSB_R_1200dps;
            iNEMO_GainGyroY(pdata)= Gyro_SensitivityLSB_P_1200dps;
            isAllowed=TRUE;
            break;
          }        
      }
      else
        isAllowed=FALSE;
      break;  
    
    case 0x01: /*!<  set x axis offset*/
      if(ulenght == 3 )
      {
      iNEMO_OffGyroX(pdata)=((s16)pvalue[0] << 8) + pvalue[1];
      isAllowed=TRUE;
      }
      else
        isAllowed=FALSE;
        
      break;
      
    case 0x02: /*!<  set y axis offset*/
      if(ulenght == 3 )
      {
      iNEMO_OffGyroY(pdata)=((s16)pvalue[0] << 8) + pvalue[1];
      isAllowed=TRUE;
      }
      else
        isAllowed=FALSE;
      break;
  }
  return isAllowed;
}

/**
* @brief  Change a  configuration parameter of a iNEMO gyro Yaw
* @param parameter : paramenter to change  <ul>
 * <li>0x00 Full Scale </li>
 * <li>0x01 Offset X </li>
 * <li>0x02 Offset Y </li>
 * </ul>  
* @param value : new value to set
*/  
  
bool iNEMO_GyroYaw_Set_Config( iNEMO_DATA * pdata, u8 uparameter, u8 ulenght, u8* pvalue)  
  {
    bool isAllowed=FALSE;
    switch(uparameter)
    {
    case 0x00: /*!<  set FS */
      if(pvalue[0] == 0x04 && ulenght == 2)
      {
          switch(pvalue[0])  
          {
          case 0x04: /* 300dps*/
            iNEMO_GainGyroZ(pdata)= Gyro_SensitivityLSB_Y_300dps;
            isAllowed=TRUE;
            break;
            
          }        
      }
      else
        isAllowed=FALSE;
      break;  
    
    case 0x01: /*!<  set z axis offset*/
      if(ulenght == 3 )
      {
      iNEMO_OffGyroZ(pdata)=((s16)pvalue[0] << 8) + pvalue[1];
      isAllowed=TRUE;
      }
      else
        isAllowed=FALSE;
        
      break;
 
  }
  return isAllowed;
}


/**
* @brief  Change a  configuration parameter of a iNEMO pressure sensor
* @param parameter : paramenter to change  <ul>
* <li>0x00 - Output data rate</li>
* <li>0x01 Offset </li>
* </ul>  
* @param value : new value to set
*/  

bool iNEMO_Pressure_Set_Config( iNEMO_DATA * pdata, u8 uparameter, u8 ulenght, u8* pvalue)  
{
  bool isAllowed=FALSE;
  switch(uparameter)
  {    
    
  case  0x00:  /*!<  ODR */
    if((pvalue[0] == 0x03 || pvalue[0] == 0x01) && ulenght == 2)
    {
      u8 uCtrl;
      LPS001DL_Read(&uCtrl, LPS001DL_CTRL_REG1_ADDR, 1);
      uCtrl = (uCtrl & 0xCF) + ( pvalue[0] << 4);  
      LPS001DL_Write(&uCtrl, LPS001DL_CTRL_REG1_ADDR, 1);
      LPS001DL_Read(&uCtrl, LPS001DL_CTRL_REG1_ADDR, 1);
      /* check if the command has been executed */
      if(((uCtrl & 0x30)>>4) == pvalue[0]) 
        /* if yes  send ack  */  
        isAllowed=TRUE;
      else
        /* else send nack  */              
        isAllowed=FALSE;
    }
    else
    {
      isAllowed=FALSE;
    }
    break; 
      
  case 0x01: /*!<  set pressure offset*/
    if(ulenght == 3)
    {
      iNEMO_OffPress(pdata)=((s16)pvalue[0] << 8) + pvalue[1];
      isAllowed=TRUE;
    }
    else
      isAllowed=FALSE;
    break;
    
  }
  return isAllowed;
}

/**
* @brief  Change a  configuration parameter of a iNEMO temerature sensor
* @param parameter : paramenter to change  <ul>
* <li>0x00 Offset </li>
* </ul>  
* @param value : new value to set
*/  

bool iNEMO_Temp_Set_Config( iNEMO_DATA * pdata, u8 uparameter, u8 ulenght, u8* pvalue)  
{
  bool isAllowed=FALSE;
  switch(uparameter)
  {    
      
  case 0x00: /*!<  set temperature offset*/
    if(ulenght == 3)
    {
      iNEMO_OffTemp(pdata)=((s16)pvalue[0] << 8) + pvalue[1];
      isAllowed=TRUE;
    }
    else
      isAllowed=FALSE;
    break;
    
  }
  return isAllowed;
}


/**
* @brief  Get a configuration parameter of a iNEMO sensor
* @param pData : poiter to iNEMO_data structure
* @param usensor : the sensor type (0x00 = Accelerometer; 0x01 = Gyroscope; 0x02 Pitch/Roll Gyro; 0x03 Yaw Gyro; 0x04 = Pressure; 0x05 Temp)
* @param uparamter : paramenter to get
*/
bool iNEMO_Get_Sensor_Param(iNEMO_DATA * pdata, u8 usensor, u8 uparameter, u8* pvalue)
{
  bool isAllowed =FALSE;
 
  switch(usensor)
  {
  case 0x00 :  /*!<  Accelerometer */  
    isAllowed = iNEMO_Acc_Get_Config(pdata, uparameter, pvalue);
    break;
    
  case 0x01 :  /*!<  Magnetometer */
    isAllowed = iNEMO_Magn_Get_Config(pdata,uparameter, pvalue);
    break;
    
  case 0x02  :  /*!<  Roll and Pitch Gyro */
    isAllowed = iNEMO_GyroPR_Get_Config(pdata,uparameter, pvalue);
    break;
    
  case 0x03  :   /*!<  Yaw Gyro */
    isAllowed = iNEMO_GyroY_Get_Config(pdata,uparameter, pvalue);
    break;
    
  case 0x04  :  /*!<  Pressure Sensor*/
    isAllowed = iNEMO_Pressure_Get_Config(pdata,uparameter, pvalue);
    break;
    
  case 0x05  : /*!<  Temperature Sensor*/     
    isAllowed = iNEMO_Temp_Get_Config(pdata,uparameter, pvalue);
    break;
    }
   return  isAllowed;      
}

/**
* @brief  Get a configuration parameter of a iNEMO accelerometer
* @param parameter : paramenter to change  <ul>
 * <li>0x00 - Output data rate</li>
 * <li>0x01 Full Scale </li>
 * <li>0x02 HPF  </li>
 * <li>0x03 Offset X </li>
 * <li>0x04 Offset Y </li>
 * <li>0x05 Offset Z </li>
 * </ul>  
* @param value : new value to set
*/  
bool iNEMO_Acc_Get_Config( iNEMO_DATA * pdata, u8 uparameter, u8* pvalue)  
  {
    bool isAllowed=FALSE;
     /* pValue temp[0]=lengh of payload, temp[1]=sensor,  temp[2]=parameter, temp[3]=payload1, temp[4]=payload2(if any)*/ 
    pvalue[1]=0x00;    
    
    switch(uparameter)
    {
    case 0x00: /* set ODR */
        pvalue[0]=3;
        pvalue[2]=0x00;
        LSM303DLH_I2C_BufferRead(LSM_A_I2C_ADDRESS, &pvalue[3], LSM_A_CTRL_REG1_ADDR, 1);
        pvalue[3]=((pvalue[3] >> 3) & 0x03); 
        isAllowed=TRUE; 
        break;
        
    case  0x01:  /* Set Full scale*/
        pvalue[0]=3;
        pvalue[2]=0x1;
        LSM303DLH_I2C_BufferRead(LSM_A_I2C_ADDRESS, &pvalue[3], LSM_A_CTRL_REG4_ADDR, 1);
        pvalue[3]=((pvalue[3] & 0x30) >> 4 );
        isAllowed=TRUE; 
        break;        
        
    case  0x02:  /* HPF */
      /* 
      return:
      temp[0]=payload lenght
      temp[1] = | RFU |RFU |Filter Enable/Disable |REF ENABLE/DISABLE |HP1 |HP0 | ODR1 |ODR0
      temp[2] = referemce value
      */
      {
      u8  ctrl, temp=0;
      pvalue[0]=4;
      pvalue[2]=0x02;
      LSM303DLH_I2C_BufferRead(LSM_A_I2C_ADDRESS, &ctrl, LSM_A_CTRL_REG1_ADDR, 1); // read ODR
      temp =  (ctrl & 0x18)>> 3 ;  
      LSM303DLH_I2C_BufferRead(LSM_A_I2C_ADDRESS, &ctrl, LSM_A_CTRL_REG2_ADDR, 1);
      temp = (temp & 0xF3) + ((ctrl & 0x03) << 2);  
      if((ctrl  & 0x60) == 0x20)   /*  reference enabled*/
      temp = temp + 0x10;
      if((ctrl  & 0x10) == 0x10)  /* filter  enabled */
      temp = temp + 0x20;  
      pvalue[3]=temp;
      LSM303DLH_I2C_BufferRead(LSM_A_I2C_ADDRESS, &pvalue[4], LSM_A_REFERENCE_REG_ADDR,1);    /*!<read the refence value in the LSM_A_REFERENCE_REG_ADDR register*/        
      isAllowed=TRUE;        
      break;
      }
    case 0x03: /* set x axis offset*/
      /* 
      return:
      temp[0]=payload lenght
      temp[3] = offset MSB
      temp[4] = offset LSB
      */      
      pvalue[0]=4;
      pvalue[2]=0x03;
      s16_to_u8_buffer(&iNEMO_OffAccX(pdata), &pvalue[3]);
      isAllowed=TRUE;
      break;
      
    case 0x04: /* set y axis offset*/
     /* 
      return:
      temp[0]=payload lenght
      temp[3] = offset MSB
      temp[4] = offset LSB
      */  
      pvalue[0]=4;
      pvalue[2]=0x04;      
      s16_to_u8_buffer(&iNEMO_OffAccY(pdata), &pvalue[3]);
      isAllowed=TRUE;
      break;
      
    case 0x05: /* set z axis offset*/
      /* 
      return:
      temp[0]=payload lenght
      temp[3] = offset MSB
      temp[4] = offset LSB
      */  
      { s16 temp=iNEMO_OffAccZ(pdata);
      pvalue[0]=4;
      pvalue[2]=0x05;      
      s16_to_u8_buffer(&temp, &pvalue[3]);
      isAllowed=TRUE;
      }
      break;
     
  }
  return isAllowed;
  }


/**
* @brief  Get a configuration parameter of a iNEMO magnetometer
* @param parameter : paramenter to change  <ul>
 * <li>0x00 Output data rate</li>
 * <li>0x01 Full Scale </li>
 * <li>0x02 MAGN operationg mode </li>
 * <li>0x03 Offset X </li>
 * <li>0x04 Offset Y </li>
 * <li>0x05 Offset Z </li>
 * </ul>  
* @param value : new value to set
*/  
  
bool iNEMO_Magn_Get_Config( iNEMO_DATA * pdata, u8 uparameter,  u8* pvalue)  
  {
    bool isAllowed=FALSE;
      /* 
      return:
      temp[0]=payload lenght
      temp[1] = sensor
      temp[2] = paramter      
      temp[3] = payload1
      temp[4] = payload2
      */         
    pvalue[1]=0x01;    
    switch(uparameter)
    {
    case 0x00: /* Get ODR */
      pvalue[0]=3;
      pvalue[2]=0x00;
      LSM303DLH_I2C_BufferRead(LSM_M_I2C_ADDRESS, &pvalue[3], LSM_M_CRA_REG_ADDR, 1);
      pvalue[3]=(pvalue[3] >>2)  & 0x07;
      isAllowed=TRUE;    
      break;    
      
    case  0x01:  /* Get Full scale*/
      pvalue[0]=3;   
      pvalue[2]=0x01;      
      LSM303DLH_I2C_BufferRead(LSM_M_I2C_ADDRESS, &pvalue[3], LSM_M_CRB_REG_ADDR, 1);
      pvalue[3]=(pvalue[3] >>5)  & 0x07;
      isAllowed=TRUE;
      break;   
      
    case  0x02:  /* Magn operating mode*/
      pvalue[0]=3; 
      pvalue[2]=0x02;      
      LSM303DLH_I2C_BufferRead(LSM_M_I2C_ADDRESS, &pvalue[3], LSM_M_CRA_REG_ADDR, 1);
      pvalue[3]= pvalue[3] & 0x03;    
      isAllowed=TRUE;
      break; 
    
    case 0x03: /* set x axis offset*/
      pvalue[0]=4;
      pvalue[2]=0x03;      
      s16_to_u8_buffer(&iNEMO_OffMagnX(pdata), &pvalue[3]);     
      isAllowed=TRUE;
      break;
      
    case 0x04: /* set y axis offset*/
      pvalue[0]=4;
      pvalue[2]=0x04;      
      s16_to_u8_buffer(&iNEMO_OffMagnY(pdata), &pvalue[3]);     
      isAllowed=TRUE;
      break;
      
    case 0x05: /* set z axis offset*/ 
      pvalue[0]=4;
      pvalue[2]=0x05;      
      s16_to_u8_buffer(&iNEMO_OffMagnZ(pdata), &pvalue[3]);   
      isAllowed=TRUE;
      break;
  }
  return isAllowed;
}

/**
* @brief  Get a configuration parameter of a iNEMO Gyro Pitch and Roll
* @param parameter : paramenter to change  <ul>
 * <li>0x00 Full Scale </li>
 * <li>0x01 Offset X </li>
 * <li>0x02 Offset Y </li>
 * </ul>  
* @param value : new value to set
*/  
  
bool iNEMO_GyroPR_Get_Config(iNEMO_DATA * pdata, u8 uparameter,  u8* pvalue)  
  {
    bool isAllowed=FALSE;
     /* 
      return:
      temp[0] = payload lenght
      temp[1] = sensor
      temp[2] = parameter      
      temp[3] = payload1
      temp[4] = payload2
      */  
    pvalue[1]=0x02;
    switch(uparameter)
    {
      case 0x00:  /* Full Scale*/
      /* 
      temp[3] = gain --> 0x04 = 300dps  ; 0x08 =1200dps 
      */ 
      pvalue[0]=3;
      pvalue[2]=0x00;
      if(iNEMO_GainGyroX(pdata) > (u16)Gyro_SensitivityLSB_R_300dps)
      {
       
        pvalue[3]=0x04;     
        isAllowed=TRUE;
      }
      else if(iNEMO_GainGyroX(pdata)==Gyro_SensitivityLSB_R_1200dps)
      {
        pvalue[3]=0x08;  
        isAllowed=TRUE;
      }
      else
        isAllowed=FALSE;
      break;
 
    case 0x01:  /* set x axis offset*/
      /* 
      temp[3] = offset MSB
      temp[4] = offset LSB
      */ 
      pvalue[0]=4;
      pvalue[2]=0x01;
      s16_to_u8_buffer(&iNEMO_OffGyroX(pdata), &pvalue[3]);      
      isAllowed=TRUE;
      break;
      
    case 0x02: /* set y axis offset*/
      /* 
      temp[3] = offset MSB
      temp[4] = offset LSB
      */ 
      pvalue[0]=4;
      pvalue[2]=0x02;
      s16_to_u8_buffer(&iNEMO_OffGyroY(pdata), &pvalue[3]);   
      isAllowed=TRUE;
      break;
  }
  return isAllowed;
}


/**
* @brief  Get a configuration parameter of a iNEMO Gyro Pitch and Roll
* @param parameter : paramenter to change  <ul>
 * <li>0x00 Full Scale </li>
 * <li>0x01 Offset X </li>
 * <li>0x02 Offset Y </li>
 * </ul>  
* @param value : new value to set
*/  
  
bool iNEMO_GyroY_Get_Config(iNEMO_DATA * pdata, u8 uparameter,  u8* pvalue)  
  {
    bool isAllowed=FALSE;
    /* 
      return:
      temp[0]=payload lenght
      temp[1] = sensor
      temp[2] = parameter      
      temp[3] = payload1
      temp[4] = payload2
      */ 
    pvalue[1]=0x03;
    switch(uparameter)
    {
      case 0x00:  /* Full Scale*/
      /* 
      temp[3] = gain --> 0x00 = 300dps  
      */ 
      pvalue[0]=3;
      pvalue[2]=0x00;
/*      if(iNEMO_GainGyroZ(pdata)==(u16)Gyro_SensitivityLSB_Y_300dps)  //TODO
      {
  */       
        pvalue[3]= 0x04;     
        isAllowed=TRUE;
/*      }
      else
        isAllowed=FALSE; */
      break;
 
    case 0x01:  /* set x axis offset*/
      /* 
      return:
      temp[3] = offset MSB
      temp[4] = offset LSB
      */ 
      pvalue[0]=4;
      pvalue[2]=0x01;
      s16_to_u8_buffer(&iNEMO_OffGyroZ(pdata), &pvalue[3]);     
      isAllowed=TRUE;
      break;
  }
  return isAllowed;
}

/**
* @brief  Get a configuration parameter of a iNEMO Pressure Sensor
* @param parameter : paramenter to change  <ul>
 * <li>0x00 ODR </li>
 * <li>0x01 Offset  </li>
 * </ul>  
 * @param value :  value to get
*/ 
bool iNEMO_Pressure_Get_Config( iNEMO_DATA * pdata, u8 uparameter, u8* pvalue)  
{
      bool isAllowed=FALSE;
    /* 
      return:
      temp[0]=payload lenght
      temp[1] = sensor
      temp[2] = parameter      
      temp[3] = payload1
      temp[4] = payload2
      */ 
    pvalue[1]=0x04;
  switch(uparameter)
  {      
  case  0x00:  /*!<  ODR */
      pvalue[0]=3;
      pvalue[2]=0x00;
      LPS001DL_Read(&pvalue[3], LPS001DL_CTRL_REG1_ADDR, 1);
      pvalue[3]=(pvalue[3] & 0x30)>>4; 
      isAllowed=TRUE;
    break; 
      
  case 0x01: /*!<  set pressure offset*/
      pvalue[0]=4;
      pvalue[2]=0x01;
      s16_to_u8_buffer(&iNEMO_OffPress(pdata), &pvalue[3]);     
      isAllowed=TRUE;
      break;    
  }
  return isAllowed;
}

/**
* @brief  Get a configuration parameter of a iNEMO Temperature Sensor
* @param parameter : paramenter to change  <ul>
 * <li>0x01 Offset  </li>
 * </ul>  
 * @param value :  value to get
*/ 
bool iNEMO_Temp_Get_Config( iNEMO_DATA * pdata, u8 uparameter, u8* pvalue)  
{
    bool isAllowed=FALSE;
    /* 
      return:
      temp[0]=payload lenght
      temp[1] = sensor
      temp[2] = paramter      
      temp[3] = payload1
      temp[4] = payload2
      */ 
    pvalue[1]=0x05;
  switch(uparameter)
  {      
  case 0x00: /*!<  set pressure offset*/
      pvalue[0]=4;
      pvalue[2]=0x00;
      s16_to_u8_buffer(&iNEMO_OffTemp(pdata), &pvalue[3]);   
      isAllowed=TRUE;
      break;    
  }
  return isAllowed;
}


/**
* @brief  Change a a configuration parameter of a iNEMO sensor
* @param pData : poiter to iNEMO_data structure
* @param usensor : the sensor type (0x00 = Accelerometer; 0x01 = Gyroscope; 0x02 Pitch/Roll Gyro; 0x03 Yaw Gyro; 0x04 = Pressure; 0x05 Temp)
* @ulenght : Lenght of value payload
* @param uparamter : paramenter to change
* @param pvalue : new value to set
*/
bool iNEMO_Restore_DefaultParam(iNEMO_DATA * pdata, u8 usensor, u8 uparameter, u8* pvalue)
{
  bool isAllowed =FALSE;
  switch(usensor)
  {
  case 0x00 :  /*!<  Accelerometer */
    switch(uparameter)
    {
    case 0x00: /*!<  set ODR */
      pvalue[0]=3;
      pvalue[1]=iNEMO_Default_AccODR;
      isAllowed = iNEMO_Acc_Set_Config(pdata, uparameter, 2, &pvalue[1]);
      break;
      
    case 0x01: /*!<  set FS */
      pvalue[0]=3;
      pvalue[1]=iNEMO_Default_AccFS;
      isAllowed = iNEMO_Acc_Set_Config(pdata, uparameter, 2, &pvalue[1]);
      break;
      
    case 0x02: /*!<  set HPS */ 
      pvalue[0]=4;  
      pvalue[1]=iNEMO_Default_AccHPF;
      isAllowed = iNEMO_Acc_Set_Config(pdata, uparameter, 3, &pvalue[1]);
      break;    
      
    case 0x03: /*!<  Set x offset*/
      pvalue[0]=4;  
      pvalue[1]=(u8)((iNEMO_Default_OffAccX & 0xFF00)>>8);
      pvalue[2]=(u8)(iNEMO_Default_OffAccX & 0x00FF);
      isAllowed = iNEMO_Acc_Set_Config(pdata, uparameter, 3, &pvalue[1]);
      break;
      
    case 0x04: /*!<  Set y offset*/
      pvalue[0]=4;  
      pvalue[1]=(u8)((iNEMO_Default_OffAccY & 0xFF00)>>8);
      pvalue[2]=(u8)(iNEMO_Default_OffAccY & 0x00FF);
      isAllowed = iNEMO_Acc_Set_Config(pdata, uparameter, 3, &pvalue[1]);
      break;    
      
    case 0x05: /*!<  Set z offset*/
      pvalue[0]=4;  
      pvalue[1]=(u8)((iNEMO_Default_OffAccZ & 0xFF00)>>8);
      pvalue[2]=(u8)(iNEMO_Default_OffAccZ & 0x00FF);
      isAllowed = iNEMO_Acc_Set_Config(pdata, uparameter, 3, &pvalue[1]);
      break;    
    }
    break;
    
  case 0x01 :  /*!<  Magnetometer */
    switch(uparameter)
    {
    case 0x00: /*!<  set ODR */
      pvalue[0]=3;
      pvalue[1]=iNEMO_Default_MagnODR;
      isAllowed = iNEMO_Magn_Set_Config(pdata, uparameter, 2, &pvalue[1]);
      break;
      
    case 0x01: /*!<  set ODR */
      pvalue[0]=3;
      pvalue[1]=iNEMO_Default_MagnFS;
      isAllowed = iNEMO_Magn_Set_Config(pdata, uparameter, 2, &pvalue[1]);
      break;
      
    case 0x02: /*!<  set Mode */ 
      pvalue[0]=4;  
      pvalue[1]=iNEMO_Default_MagnMD;
      isAllowed = iNEMO_Magn_Set_Config(pdata, uparameter, 2, &pvalue[1]);
      break;    
      
    case 0x03: /*!<  Set x offset*/
      pvalue[0]=4;  
      pvalue[1]=(u8)((iNEMO_Default_OffMagnX & 0xFF00)>>8);
      pvalue[2]=(u8)(iNEMO_Default_OffMagnX & 0x00FF);
      isAllowed = iNEMO_Magn_Set_Config(pdata, uparameter, 3, &pvalue[1]);
      break;
      
    case 0x04: /*!<  Set y offset*/
      pvalue[0]=4;  
      pvalue[1]=(u8)((iNEMO_Default_OffMagnY & 0xFF00)>>8);
      pvalue[2]=(u8)(iNEMO_Default_OffMagnY & 0x00FF);
      isAllowed = iNEMO_Magn_Set_Config(pdata, uparameter, 3, &pvalue[1]);
      break;    
      
    case 0x05: /*!<  Set z offset*/
      pvalue[0]=4;  
      pvalue[1]=(u8)((iNEMO_Default_OffMagnZ & 0xFF00)>>8);
      pvalue[2]=(u8)(iNEMO_Default_OffMagnZ & 0x00FF);
      isAllowed = iNEMO_Magn_Set_Config(pdata, uparameter, 3, &pvalue[1]);
      break;   
    }
    break;
    
  case 0x02  :  /*!<  Roll and Pitch Gyro */
    switch(uparameter)
    {
      
    case 0x00: /*!<Full Scal*/
      pvalue[0]=3;  
      pvalue[1]=0x04; /* 300dps*/
      isAllowed = iNEMO_GyroPR_Set_Config(pdata, uparameter, 3, &pvalue[1]);
      break;
      
    case 0x01: /*!<Set x offset*/
      pvalue[0]=4;  
      pvalue[1]=(u8)((iNEMO_Default_OffGyroX & 0xFF00)>>8);
      pvalue[2]=(u8)(iNEMO_Default_OffGyroX & 0x00FF);
      isAllowed = iNEMO_GyroPR_Set_Config(pdata, uparameter, 3, &pvalue[1]);
      break;
      
    case 0x02: /*!<Set y offset*/
      pvalue[0]=4;  
      pvalue[1]=(u8)((iNEMO_Default_OffGyroY & 0xFF00)>>8);
      pvalue[2]=(u8)(iNEMO_Default_OffGyroY & 0x00FF);
      isAllowed = iNEMO_GyroPR_Set_Config(pdata, uparameter, 3, &pvalue[1]);
      break;    
      
    }
    break;
    
    
  case 0x03  :   /*!<Yaw Gyro */
    switch(uparameter)
    {
      
    case 0x00: /*!<  Full Scal*/
      pvalue[0]=3;  
      pvalue[1]=0x04; /*!<300dps*/
      isAllowed = iNEMO_GyroYaw_Set_Config(pdata, uparameter, 3, &pvalue[1]);
      break;
      
    case 0x01: /*!<Set z offset*/
      pvalue[0]=4;  
      pvalue[1]=(u8)((iNEMO_Default_OffGyroZ & 0xFF00)>>8);
      pvalue[2]=(u8)(iNEMO_Default_OffGyroZ & 0x00FF);
      isAllowed = iNEMO_GyroYaw_Set_Config(pdata, uparameter, 3, &pvalue[1]);
      break;   
    }
    break;
    
  case 0x04  :  /*!<  Pressure Sensor*/
    switch(uparameter)
    {
    case 0x00: /*!<  set ODR */
      pvalue[0]=3;
      pvalue[1]=iNEMO_Default_PressODR;
      isAllowed = iNEMO_Pressure_Set_Config(pdata,uparameter,2, &pvalue[1]);
      break;
    case 0x01: /*!<  Set z offset*/
      pvalue[0]=4;  
      pvalue[1]=(u8)((iNEMO_Default_OffPress & 0xFF00)>>8);
      pvalue[2]=(u8)(iNEMO_Default_OffPress & 0x00FF);
      isAllowed = iNEMO_Pressure_Set_Config(pdata, uparameter, 3, &pvalue[1]);
      break;   
    }
    
    break;
    
  case 0x05  : /*!<  Temperature Sensor*/    
    switch(uparameter)
    {
    case 0x00: /*!<  set ODR */
      pvalue[0]=4;  
      pvalue[1]=(u8)((iNEMO_Default_OffTemp & 0xFF00)>>8);
      pvalue[2]=(u8)(iNEMO_Default_OffTemp & 0x00FF);
      isAllowed = iNEMO_Temp_Set_Config(pdata, uparameter, 3, &pvalue[1]);
      break;   
    } 
    break;
  }
  return  isAllowed;      
}


/**
* @brief Test SDIO
*/
#ifdef _SDIO

TestStatus Test_SDIO(void)
{
    NVIC_InitTypeDef NVIC_InitStructure;
    SD_CardInfo SDCardInfo;
    SD_Error Status = SD_OK;

	NVIC_InitStructure.NVIC_IRQChannel = SDIO_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 11;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&NVIC_InitStructure);


	/* SD Init   */
	Status = SD_Init();

	if (Status == SD_OK)
	{
		/*  Read CSD/CID MSD registers  */
		Status = SD_GetCardInfo(&SDCardInfo);
	}

	if (Status == SD_OK)
	{
		/* Select Card  -*/
		Status = SD_SelectDeselect((u32) (SDCardInfo.RCA << 16));
	}

	if (Status == SD_OK)
	{
		Status = SD_EnableWideBusOperation(SDIO_BusWide_4b);
	}

	/*  Block Erase  */
	if (Status == SD_OK)
	{
		/* Erase NumberOfBlocks Blocks of WRITE_BL_LEN(512 Bytes) */
		Status = SD_Erase(0x00, (BlockSize * NumberOfBlocks));
	}

	/* Set Device Transfer Mode to DMA */
	if (Status == SD_OK)
	{
		Status = SD_SetDeviceMode(SD_DMA_MODE);
	}

	if (Status == SD_OK)
	{
		Status = SD_ReadMultiBlocks(0x00, s_Buffer_MultiBlock_Rx, BlockSize, NumberOfBlocks);
	}

	if (Status == SD_OK)
	{
		EraseStatus = eBuffercmp(s_Buffer_MultiBlock_Rx, MultiBufferWordsSize);
	}

	/*  Block Read/Write  */
	/* Fill the buffer to send */
	Fill_Buffer(s_Buffer_Block_Tx, BufferWordsSize, 0xFFFF);


	if (Status == SD_OK)
	{
		/* Write block of 512 bytes on address 0 */
		Status = SD_WriteBlock(0x00, s_Buffer_Block_Tx, BlockSize);
	}

	if (Status == SD_OK)
	{
		/* Read block of 512 bytes from address 0 */
		Status = SD_ReadBlock(0x00, s_Buffer_Block_Rx, BlockSize);
	}

	if (Status == SD_OK)
	{
		/* Check the corectness of written dada */
		TransferStatus1 = Buffercmp(s_Buffer_Block_Tx, s_Buffer_Block_Rx, BufferWordsSize);
	}

	/*  Multiple Block Read/Write */
	/* Fill the buffer to send */
	Fill_Buffer(s_Buffer_MultiBlock_Tx, MultiBufferWordsSize, 0x0);

	if (Status == SD_OK)
	{
		/* Write multiple block of many bytes on address 0 */
		Status = SD_WriteMultiBlocks(0x00, s_Buffer_MultiBlock_Tx, BlockSize, NumberOfBlocks);
	}

	if (Status == SD_OK)
	{
		/* Read block of many bytes from address 0 */
		Status = SD_ReadMultiBlocks(0x00, s_Buffer_MultiBlock_Rx, BlockSize, NumberOfBlocks);
	}

	if (Status == SD_OK)
	{
		/* Check the corectness of written dada */
		TransferStatus2 = Buffercmp(s_Buffer_MultiBlock_Tx, s_Buffer_MultiBlock_Rx, MultiBufferWordsSize);
	}
	if(EraseStatus==PASSED && TransferStatus1==PASSED && TransferStatus2==PASSED)
		return PASSED;
	else
		return FAILED;

}


#else

/* If the _SDIO macro is not defined in iNEMO_conf.h file, the test simply return FAILED*/
TestStatus Test_SDIO(void) {
	return FAILED;
}
#endif

/**
 * @}
 */  /* end of group iNEMO_Config_Function */

/**
 * @}
 */  /* end of group iNEMO_Config */

/******************* (C) COPYRIGHT 2010 STMicroelectronics *****END OF FILE****/
