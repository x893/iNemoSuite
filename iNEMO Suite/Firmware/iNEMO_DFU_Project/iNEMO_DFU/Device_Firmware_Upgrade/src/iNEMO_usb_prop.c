/**
  ******************************************************************************
  * @file    iNEMO_usb_prop.c
  * @author  ART Team IMS-Systems Lab
  * @version V3.2.1
  * @date    09/20/2010
  * @brief   All processings related to DFU demo
  *
  * @details
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
#include "usb_lib.h"
#include "usb_conf.h"
#include "iNEMO_usb_prop.h"
#include "iNEMO_usb_desc.h"
#include "usb_pwr.h"
#include "iNEMO_dfu_mal.h"
#include "iNEMO_dfu.h"
#include "iNEMO_usb_common.h"


/** @addtogroup iNEMO_DFU_Program
  * @{
  */

/** @addtogroup Device_Firmware_Upgrade
  * @{
  */

/** @addtogroup DFU_Processing
  * @{
  */

/** @defgroup DFU_Processing_Functions
  * @{
  */

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
uint32_t wBlockNum = 0, wlength = 0;
uint32_t Manifest_State = Manifest_complete;
uint32_t Pointer = ApplicationAddress;  /* Base Address to Erase, Program or Read */

DEVICE Device_Table =
  {
    EP_NUM,
    1
  };

DEVICE_PROP Device_Property =
  {
    DFU_init,
    DFU_Reset,
    DFU_Status_In,
    DFU_Status_Out,
    DFU_Data_Setup,
    DFU_NoData_Setup,
    DFU_Get_Interface_Setting,
    DFU_GetDeviceDescriptor,
    DFU_GetConfigDescriptor,
    DFU_GetStringDescriptor,
    0,                    /*DFU_EP0Buffer*/
    bMaxPacketSize0       /*Max Packet size*/
  };

USER_STANDARD_REQUESTS User_Standard_Requests =
  {
    DFU_GetConfiguration,
    DFU_SetConfiguration,
    DFU_GetInterface,
    DFU_SetInterface,
    DFU_GetStatus,
    DFU_ClearFeature,
    DFU_SetEndPointFeature,
    DFU_SetDeviceFeature,
    DFU_SetDeviceAddress
  };

ONE_DESCRIPTOR Device_Descriptor =
  {
    (uint8_t*)DFU_DeviceDescriptor,
    DFU_SIZ_DEVICE_DESC
  };

ONE_DESCRIPTOR Config_Descriptor =
  {
    (uint8_t*)DFU_ConfigDescriptor,
    DFU_SIZ_CONFIG_DESC
  };

ONE_DESCRIPTOR DFU_String_Descriptor[5] =
  {
    {       (u8*)DFU_StringLangId,          DFU_SIZ_STRING_LANGID       },
    {       (u8*)DFU_StringVendor,          DFU_SIZ_STRING_VENDOR       },
    {       (u8*)DFU_StringProduct,         DFU_SIZ_STRING_PRODUCT      },
    {       (u8*)DFU_StringSerial,          DFU_SIZ_STRING_SERIAL       },
    {       (u8*)DFU_StringInterface0,      DFU_SIZ_STRING_INTERFACE0   }
  };

/* Extern variables ----------------------------------------------------------*/
extern  uint8_t DeviceState ;
extern  uint8_t DeviceStatus[6];

/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/


/**
  * @brief  DFU init routine.
  * @param  None.
  * @retval None.
  */

void DFU_init(void)
{
  DEVICE_INFO *pInfo = &Device_Info;

  /* Update the serial number string descriptor with the data from the unique ID*/
  Get_SerialNum();

  pInfo->Current_Configuration = 0;

  /* Connect the device */
  PowerOn();

  /* Perform basic device initialization operations */
  USB_SIL_Init();

  /* Enable USB interrupts */
  USB_Interrupts_Config();

  bDeviceState = UNCONNECTED;
}


/**
  * @brief  DFU reset routine.
  * @param  None.
  * @retval None.
  */

void DFU_Reset(void)
{
  /* Set DFU_DEVICE as not configured */
  Device_Info.Current_Configuration = 0;

  /* Current Feature initialization */
  pInformation->Current_Feature = DFU_ConfigDescriptor[7];

  _SetBTABLE(BTABLE_ADDRESS);

  /* Initialize Endpoint 0 */
  _SetEPType(ENDP0, EP_CONTROL);
  _SetEPTxStatus(ENDP0, EP_TX_NAK);
  _SetEPRxAddr(ENDP0, ENDP0_RXADDR);
  SetEPRxCount(ENDP0, Device_Property.MaxPacketSize);
  _SetEPTxAddr(ENDP0, ENDP0_TXADDR);
  SetEPTxCount(ENDP0, Device_Property.MaxPacketSize);
  Clear_Status_Out(ENDP0);
  SetEPRxValid(ENDP0);

  /* Set this device to response on default address */
  SetDeviceAddress(0);

  /* Set the new control state of the device to Attached */
  bDeviceState = ATTACHED;
}

/**
  * @brief  Udpade the device state to configured.
  * @param  None.
  * @retval None.
  */

void DFU_SetConfiguration(void)
{
  DEVICE_INFO *pInfo = &Device_Info;

  if (pInfo->Current_Configuration != 0)
  {
    /* Device configured */
    bDeviceState = CONFIGURED;
  }
}


/**
  * @brief  Udpade the device state to addressed.
  * @param  None.
  * @retval None.
  */

void DFU_SetDeviceAddress (void)
{
  bDeviceState = ADDRESSED;
}


/**
  * @brief  DFU status IN routine.
  * @param  None.
  * @retval None.
  */

void DFU_Status_In(void)
{}


/**
  * @brief  DFU status OUT routine.
  * @param  None.
  * @retval None.
  */

void DFU_Status_Out (void)
{
  DEVICE_INFO *pInfo = &Device_Info;
  uint32_t Addr;

  if (pInfo->USBbRequest == DFU_GETSTATUS)
  {
    if (DeviceState == STATE_dfuDNBUSY)
    {
      if (wBlockNum == 0)   /* Decode the Special Command*/
      {
        if ((MAL_Buffer[0] ==  CMD_GETCOMMANDS) && (wlength == 1))
        {}
        else if  (( MAL_Buffer[0] ==  CMD_SETADDRESSPOINTER ) && (wlength == 5))
        {
          Pointer  = MAL_Buffer[1];
          Pointer += MAL_Buffer[2] << 8;
          Pointer += MAL_Buffer[3] << 16;
          Pointer += MAL_Buffer[4] << 24;
        }
        else if (( MAL_Buffer[0] ==  CMD_ERASE ) && (wlength == 5))
        {
          Pointer  = MAL_Buffer[1];
          Pointer += MAL_Buffer[2] << 8;
          Pointer += MAL_Buffer[3] << 16;
          Pointer += MAL_Buffer[4] << 24;
          MAL_Erase(Pointer);
        }
      }

      else if (wBlockNum > 1)  // Download Command
      {
        Addr = ((wBlockNum - 2) * wTransferSize) + Pointer;
        MAL_Write(Addr, wlength);
      }
      wlength = 0;
      wBlockNum = 0;

      DeviceState =  STATE_dfuDNLOAD_SYNC;
      DeviceStatus[4] = DeviceState;
      DeviceStatus[1] = 0;
      DeviceStatus[2] = 0;
      DeviceStatus[3] = 0;
      return;
    }
    else if (DeviceState == STATE_dfuMANIFEST)/* Manifestation in progress*/
    {
      DFU_write_crc();
      return;
    }
  }
  return;
}

/**
  * @brief  Handle the data class specific requests.
  * @param  RequestNo: Request number.
  * @retval RESULT: USB_SUCCESS or USB_UNSUPPORT.
  */

RESULT DFU_Data_Setup(uint8_t RequestNo)
{
  uint8_t *(*CopyRoutine)(uint16_t);
  CopyRoutine = NULL;

  if (Type_Recipient == (CLASS_REQUEST | INTERFACE_RECIPIENT))
  {
    if (RequestNo == DFU_UPLOAD && (DeviceState == STATE_dfuIDLE
                                    || DeviceState == STATE_dfuUPLOAD_IDLE ))
    {
      CopyRoutine = UPLOAD;
    }
    else if (RequestNo == DFU_DNLOAD && (DeviceState == STATE_dfuIDLE
                                         || DeviceState == STATE_dfuDNLOAD_IDLE))
    {
      DeviceState = STATE_dfuDNLOAD_SYNC;
      CopyRoutine = DNLOAD;
    }
    else if (RequestNo == DFU_GETSTATE)
    {
      CopyRoutine = GETSTATE;
    }
    else if (RequestNo == DFU_GETSTATUS)
    {
      CopyRoutine = GETSTATUS;
    }
    else
    {
      return USB_UNSUPPORT;
    }
  }
  else
  {
    return USB_UNSUPPORT;
  }

  if (CopyRoutine == NULL)
  {
    return USB_UNSUPPORT;
  }

  pInformation->Ctrl_Info.CopyData = CopyRoutine;
  pInformation->Ctrl_Info.Usb_wOffset = 0;
  (*CopyRoutine)(0);

  return USB_SUCCESS;
}

/**
  * @brief  Handle the No data class specific requests.
  * @param  RequestNo: Request number.
  * @retval RESULT: USB_SUCCESS or USB_UNSUPPORT.
  */

RESULT DFU_NoData_Setup(uint8_t RequestNo)
{

  if (Type_Recipient == (CLASS_REQUEST | INTERFACE_RECIPIENT))
  {
    /*DFU_NDLOAD*/
    if (RequestNo == DFU_DNLOAD)
    {
      /* End of DNLOAD operation*/
      if (DeviceState == STATE_dfuDNLOAD_IDLE || DeviceState == STATE_dfuIDLE )
      {
        Manifest_State = Manifest_In_Progress;
        DeviceState = STATE_dfuMANIFEST_SYNC;
        DeviceStatus[1] = 0;
        DeviceStatus[2] = 0;
        DeviceStatus[3] = 0;
        DeviceStatus[4] = DeviceState;
        return USB_SUCCESS;
      }
    }
    /*DFU_UPLOAD*/
    else if (RequestNo == DFU_UPLOAD)
    {
      DeviceState = STATE_dfuIDLE;
      DeviceStatus[1] = 0;
      DeviceStatus[2] = 0;
      DeviceStatus[3] = 0;
      DeviceStatus[4] = DeviceState;
      return USB_SUCCESS;
    }

    /*DFU_CLRSTATUS*/
    else if (RequestNo == DFU_CLRSTATUS)
    {

      if (DeviceState == STATE_dfuERROR)
      {
        DeviceState = STATE_dfuIDLE;
        DeviceStatus[0] = STATUS_OK;/*bStatus*/
        DeviceStatus[1] = 0;
        DeviceStatus[2] = 0;
        DeviceStatus[3] = 0; /*bwPollTimeout=0ms*/
        DeviceStatus[4] = DeviceState;/*bState*/
        DeviceStatus[5] = 0;/*iString*/
      }
      else
      {   /*State Error*/
        DeviceState = STATE_dfuERROR;
        DeviceStatus[0] = STATUS_ERRUNKNOWN;/*bStatus*/
        DeviceStatus[1] = 0;
        DeviceStatus[2] = 0;
        DeviceStatus[3] = 0; /*bwPollTimeout=0ms*/
        DeviceStatus[4] = DeviceState;/*bState*/
        DeviceStatus[5] = 0;/*iString*/
      }
      return USB_SUCCESS;
    }
    /*DFU_ABORT*/
    else if (RequestNo == DFU_ABORT)
    {
      if (DeviceState == STATE_dfuIDLE || DeviceState == STATE_dfuDNLOAD_SYNC
          || DeviceState == STATE_dfuDNLOAD_IDLE || DeviceState == STATE_dfuMANIFEST_SYNC
          || DeviceState == STATE_dfuUPLOAD_IDLE )
      {
        DeviceState = STATE_dfuIDLE;
        DeviceStatus[0] = STATUS_OK;
        DeviceStatus[1] = 0;
        DeviceStatus[2] = 0;
        DeviceStatus[3] = 0; /*bwPollTimeout=0ms*/
        DeviceStatus[4] = DeviceState;
        DeviceStatus[5] = 0; /*iString*/
        wBlockNum = 0;
        wlength = 0;
      }
      return USB_SUCCESS;
    }
  }


  return USB_UNSUPPORT;

} /*!< End of DFU_NoData_Setup */


/**
  * @brief  Gets the device descriptor.
  * @param  Length: Length of Descriptor.
  * @retval The address of the device descriptor.
  */

uint8_t *DFU_GetDeviceDescriptor(uint16_t Length)
{
  return Standard_GetDescriptorData(Length, &Device_Descriptor);
}


/**
  * @brief  Gets the configuration descriptor.
  * @param  Length: Length of Descriptor.
  * @retval The address of the configuration descriptor.
  */

uint8_t *DFU_GetConfigDescriptor(uint16_t Length)
{
  return Standard_GetDescriptorData (Length, &Config_Descriptor);
}


/**
  * @brief  Gets the string descriptors according to the needed index.
  * @param  Length: Length of Descriptor.
  * @retval The address of the string descriptor.
  */

uint8_t *DFU_GetStringDescriptor(uint16_t Length)
{
  uint8_t wValue0 = pInformation->USBwValue0;

  if (wValue0 > 8)
  {
    return NULL;
  }
  else
  {
    return Standard_GetDescriptorData(Length, &DFU_String_Descriptor[wValue0]);
  }
}



/**
  * @brief  tests the interface and the alternate setting according to the
  *         supported one.
  * @param  Interface: interface number.
  * @param  AlternateSetting: Alternate Setting number.
  * @retval RESULT: USB_SUCCESS or USB_UNSUPPORT.
  */

RESULT DFU_Get_Interface_Setting(uint8_t Interface, uint8_t AlternateSetting)
{
  if (AlternateSetting > 3)
  {
    return USB_UNSUPPORT;   /* In this application we don't have more than 3 AlternateSettings */
  }
  else if (Interface > 2)
  {
    return USB_UNSUPPORT; /* In this application we have only 1 interfaces */
  }

  return USB_SUCCESS;
}


/**
  * @brief  Upload routine.
  * @param  Length: 
  * @retval Pointer to data.
  */

uint8_t *UPLOAD(uint16_t Length)
{
  DEVICE_INFO *pInfo = &Device_Info;
  uint8_t B1, B0;
  uint16_t offset, returned;
  uint8_t *Phy_Addr = NULL;
  uint32_t Addr = 0;

  B0 = pInfo->USBwValues.bw.bb0;
  B1 = pInfo->USBwValues.bw.bb1;
  wBlockNum = (uint16_t)B1;
  wBlockNum = wBlockNum * 0x100;
  wBlockNum += (uint16_t)B0; /* wBlockNum value updated*/

  B0 = pInfo->USBwLengths.bw.bb0;
  B1 =  pInfo->USBwLengths.bw.bb1;
  wlength = (uint16_t)B0;
  wlength = wlength * 0x100;
  wlength += (uint16_t)B1; /* wlength value updated*/

  offset = pInformation->Ctrl_Info.Usb_wOffset;

  if (wBlockNum == 0)  /* Get Command */
  {
    if (wlength > 3)
    {
      DeviceState = STATE_dfuIDLE ;
    }
    else
    {
      DeviceState = STATE_dfuUPLOAD_IDLE;
    }

    DeviceStatus[4] = DeviceState;
    DeviceStatus[1] = 0;
    DeviceStatus[2] = 0;
    DeviceStatus[3] = 0;

    MAL_Buffer[0] = CMD_GETCOMMANDS;
    MAL_Buffer[1] = CMD_SETADDRESSPOINTER;
    MAL_Buffer[2] = CMD_ERASE;

    if (Length == 0)
    {
      pInformation->Ctrl_Info.Usb_wLength = 3 ;
      return NULL;
    }

    return(&MAL_Buffer[0]);
  }
  else if (wBlockNum > 1)
  {
    DeviceState = STATE_dfuUPLOAD_IDLE ;
    DeviceStatus[4] = DeviceState;
    DeviceStatus[1] = 0;
    DeviceStatus[2] = 0;
    DeviceStatus[3] = 0;
    Addr = ((wBlockNum - 2) * wTransferSize) + Pointer;  /* Change is Accelerated*/

    Phy_Addr = MAL_Read(Addr, wlength);
    returned = wlength - offset;

    if (Length == 0)
    {
      pInformation->Ctrl_Info.Usb_wLength = returned ;
      return NULL;
    }
    return(Phy_Addr + offset);
  }
  else  /* unsupported wBlockNum */
  {
    DeviceState = STATUS_ERRSTALLEDPKT;
    DeviceStatus[4] = DeviceState;
    DeviceStatus[1] = 0;
    DeviceStatus[2] = 0;
    DeviceStatus[3] = 0;

    return NULL;
  }
}


/**
  * @brief  Download routine.
  * @param  Length: 
  * @retval Pointer to data.
  */

uint8_t *DNLOAD (uint16_t Length)
{
  DEVICE_INFO             *pInfo = &Device_Info;
  uint8_t         B1, B0;
  uint16_t          offset, returned;

  B0 = pInfo->USBwValues.bw.bb0;
  B1 = pInfo->USBwValues.bw.bb1;
  wBlockNum = (uint16_t)B1;
  wBlockNum = wBlockNum * 0x100;
  wBlockNum += (uint16_t)B0;
  B0 = pInfo->USBwLengths.bw.bb0;
  B1 =  pInfo->USBwLengths.bw.bb1;
  wlength = (uint16_t)B0;
  wlength = wlength * 0x100;
  wlength += (uint16_t)B1;

  offset = pInfo->Ctrl_Info.Usb_wOffset;

  DeviceState = STATE_dfuDNLOAD_SYNC;
  DeviceStatus[4] = DeviceState;

  returned = wlength - offset;

  if (Length == 0)
  {
    pInformation->Ctrl_Info.Usb_wLength = returned ;
    return NULL;
  }

  return((uint8_t*)MAL_Buffer + offset);
}


/**
  * @brief  Get State request routine.
  * @param  Length: 
  * @retval Pointer to data.
  */

uint8_t *GETSTATE(uint16_t Length)
{
  if (Length == 0)
  {
    pInformation->Ctrl_Info.Usb_wLength = 1 ;
    return NULL;
  }
  else
    return(&DeviceState);
}

/**
  * @brief  Get Status request routine.
  * @param  Length: 
  * @retval Pointer to data.
  */

uint8_t *GETSTATUS(uint16_t Length)
{
  switch (DeviceState)
  {
    case   STATE_dfuDNLOAD_SYNC:
      if (wlength != 0)
      {
        DeviceState = STATE_dfuDNBUSY;
        DeviceStatus[4] = DeviceState;
        if ((wBlockNum == 0) && (MAL_Buffer[0] == CMD_ERASE))
        {
          MAL_GetStatus(Pointer, 0, DeviceStatus);
        }
        else
        {
          MAL_GetStatus(Pointer, 1, DeviceStatus);
        }
      }
      else  /* (wlength==0)*/
      {
        DeviceState = STATE_dfuDNLOAD_IDLE;
        DeviceStatus[4] = DeviceState;
        DeviceStatus[1] = 0;
        DeviceStatus[2] = 0;
        DeviceStatus[3] = 0;

      }
      break;
    case   STATE_dfuMANIFEST_SYNC :
      if (Manifest_State == Manifest_In_Progress)
      {
        DeviceState = STATE_dfuMANIFEST;
        DeviceStatus[4] = DeviceState;
        DeviceStatus[1] = 1;             /*bwPollTimeout = 1ms*/
        DeviceStatus[2] = 0;
        DeviceStatus[3] = 0;
        //break;
      }
      else if (Manifest_State == Manifest_complete && Config_Descriptor.Descriptor[20]
               & 0x04)
      {
        DeviceState = STATE_dfuIDLE;
        DeviceStatus[4] = DeviceState;
        DeviceStatus[1] = 0;
        DeviceStatus[2] = 0;
        DeviceStatus[3] = 0;
        //break;
      }
      break;
    default :
      break;
  }

  if (Length == 0)
  {
    pInformation->Ctrl_Info.Usb_wLength = 6 ;
    return NULL;
  }
  else
    return(&(DeviceStatus[0]));
}


/**
  * @brief  DFU Write CRC routine.
  * @param  None. 
  * @retval None.
  */

void DFU_write_crc(void)
{
  Manifest_State = Manifest_complete;

  if (Config_Descriptor.Descriptor[20] & 0x04)
  {
    DeviceState = STATE_dfuMANIFEST_SYNC;
    DeviceStatus[4] = DeviceState;
    DeviceStatus[1] = 0;
    DeviceStatus[2] = 0;
    DeviceStatus[3] = 0;
    return;
  }
  else
  {
    DeviceState = STATE_dfuMANIFEST_WAIT_RESET;
    DeviceStatus[4] = DeviceState;
    DeviceStatus[1] = 0;
    DeviceStatus[2] = 0;
    DeviceStatus[3] = 0;

    Reset_Device();

    return;
  }
}


/**
  * @}
  */ /* end of group DFU_Processing_Functions */

/**
  * @}
  */ /* end of group DFU_Processing */

/**
  * @}
  */ /* end of group Device_Firmware_Upgrade */

/**
  * @}
  */ /* end of group iNEMO_DFU_Program */


/******************* (C) COPYRIGHT 2010 STMicroelectronics *****END OF FILE****/
