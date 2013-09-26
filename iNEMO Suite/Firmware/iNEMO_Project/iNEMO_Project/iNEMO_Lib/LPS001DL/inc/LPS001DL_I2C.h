/**
  * @file    LPS001DL_I2C.h
  * @author  ART Team IMS-Systems Lab
  * @version V2.2
  * @date    01/11/2011
  * @brief   Header for LPS001DL_I2C.c file.
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
#ifndef __LPS001DL_I2C_H
#define __LPS001DL_I2C_H

#ifdef __cplusplus
 extern "C" {
#endif 

/* Includes */
#include "stm32f10x.h"
#include "HAL_LPS001DL.h"

/**
 * @defgroup LPS001DL
 * @{
*/

/**
 * @addtogroup LPS001DL_Register
 * @{
*/

/* I2C LPS001DL address */
#define LPS001DL_ADDRESS         0xBA

/**
*  @brief WHO_AM_I: Device Identification Register
*  @details Read only Default value: 0xBA
*/
#define LPS001DL_WHO_AM_I_ADDR        0x0F

/**
*  @brief CTRL_REG1: Control Register 1
*  @details <ul>
*  <li> Read/Write </li>
*  <li> Default value: 0x00 </li>
*  </ul>
*  @code
*  7 LOWPOW: lowpower  0 - normal mode  1 - low-power activated
*  6 PD: powerdown 0 - power down   1 - active mode
*  5:4 ODR1-ODR0: Output Data Rate selection:
*             ODR1 | ODR0 | Press.Out Data Rate | Temp.Out Data Rate
*             ------------------------------------------------------
*               0  |  0   |        7 Hz         |        1 Hz
*               0  |  1   |        7 Hz         |        7 Hz
*               1  |  1   |     12.5 Hz         |     12.5 Hz
*  3 DIFF_EN: Interrupt circuit enable: 0 - interrupt disabled  1 - interrupt enabled
*  2 BDU: Block Data Update: 0 - Continuos update  1 - output registers not update until MSB/LSB reading
*  1 BLE: Big/Little Endian: 0 - Little Endian  1 - Big Endian
*  0 SIM: SPI Mode selection: 0 - 4-wire  1 - 3-wire
*  @endcode
*/
#define LPS001DL_CTRL_REG1_ADDR     0x20

/**
*  @brief CTRL_REG2: Control Register 2
*  @details <ul>
*  <li>Read/Write</li>
*  <li>Default value: 0x00</li>
*  </ul>
*  @code
*  7 BOOT: Reboot memory content 0 - normal mode  1 - reboot memory content
*  6:1 RSV: reserved
*  0: 0 (bit to be kept to "0" for correct device functionality)
*  @endcode
*/
#define LPS001DL_CTRL_REG2_ADDR     0x21

/**
*  @brief CTRL_REG3: Interrupt Control Register
*  @details <ul>
*  <li>Read/Write</li>
*  <li>Default value: 0x00</li>
*  </ul>
*  @code
*  7 H_L active: Interrupt active high/low  0 - active high  1 - active low
*  6 PP_OD: push-pull/open-drain 0 - push-pull   1 - open-drain
*  5:0 Int2_cfgx - Int1_cfgx (x = 3, 2, 1) Data signal on INT2 and INT1 pad
*
*        Int1(2)_cfg3 | Int1(2)_cfg2 | Int1(2)_cfg1 | INT1(2) Pad
*        --------------------------------------------------------
*              0      |       0      |       0      | GND
*              0      |       0      |       1      | P_High
*              0      |       1      |       0      | P_Low
*              0      |       1      |       1      | P_Low OR P_High
*              1      |       0      |       0      | Pressure Data Ready (DRDY)
*              1      |       1      |       1      | Tri-state
*	@endcode
*/
#define LPS001DL_CTRL_REG3_ADDR     0x22


/**
*  @brief STATUS_REG: Status Register
*  @details <ul>
*  <li>Read Only</li>
*  <li>Default value: 0x00</li>
*  </ul>
*  @code
*  7:6 RSV: 0
*  5 P_OR: Pressure data overrun  0 - no overrun  1 - new pressure data has overwritten the previous one
*  4 T_OR: Temperature data overrun 0 - no overrun 1 - new temperature data has overwritten the previous one
*  3:2 RSV: 0
*  1 P_DA: Pressure data available 0 - no new pressure data available 1 - new pressure data available
*  0 T_DA: Temperature data available 0 - no new temperature data available 1 - new temperature data available
*  @endcode
*/
#define LPS001DL_STATUS_REG_ADDR     0x27


/**
*  @brief PRESS_OUT_L: Pressure Data LSB
*  @details <ul>
*  <li>Read Only</li>
*  <li>Default value: 0x00</li>
*  </ul>
*  @code
*  7:0 POUT7-POUT0: Pressure Data LSB (if in Little Endian Mode --> BLE bit in CTRL_REG1 is 0)
*                   Pressure Data MSB (if in Big Endian Mode --> BLE bit in CTRL_REG1 is 1)
*                   @endcode
*/
#define LPS001DL_PRESS_OUT_L_ADDR     0x28

/**
*  @brief PRESS_OUT_H: Pressure Data MSB
*  @detaisl <ul>
*  <li>Read Only</li>
*  <li>Default value: 0x00</li>
*  </ul>
*  @code
*  7:0 POUT15-POUT8: Pressure Data MSB (if in Little Endian Mode --> BLE bit in CTRL_REG1 is 0)
*                   Pressure Data LSB (if in Big Endian Mode --> BLE bit in CTRL_REG1 is 1)
*  @endcode
*/
#define LPS001DL_PRESS_OUT_H_ADDR     0x29


/**
*  @brief TEMP_OUT_L: Temperature Data LSB
*  @details <ul>
*  <li>Read Only</li>
*  <li>Default value: 0x00</li>
*  </ul>
*  @code
*  7:0 TOUT7-TOUT0: Temperature Data LSB (if in Little Endian Mode --> BLE bit in CTRL_REG1 is 0)
*                   Temperature Data MSB (if in Big Endian Mode --> BLE bit in CTRL_REG1 is 1)
*  @endcode
*/
#define LPS001DL_TEMP_OUT_L_ADDR     0x2A


/**
*  @brief TEMP_OUT_H: Temperature Data MSB
*  @detail <ul>
*  <li>Read Only</li>
*  <li>Default value: 0x00</li>
*  </ul>
*  @code
*  7:0 TOUT15-TOUT8: Temperature Data MSB (if in Little Endian Mode --> BLE bit in CTRL_REG1 is 0)
*                   Temperature Data LSB (if in Big Endian Mode --> BLE bit in CTRL_REG1 is 1)
*  @endcode
*/
#define LPS001DL_TEMP_OUT_H_ADDR     0x2B


/**
*  @brief DELTA_P_L: Delta Pressure Data LSB
*  @detail <ul>
*  <li>Read Only</li>
*  <li>Default value: 0x00</li>
*  <li>DELTA_P = REF_P - PRESS_OUT</li>
*  </ul>
*  @code
*  7:0 DP7-DP0: Delta Pressure Data LSB (if in Little Endian Mode --> BLE bit in CTRL_REG1 is 0)
*               Delta Pressure Data MSB (if in Big Endian Mode --> BLE bit in CTRL_REG1 is 1)
*    @endcode
*/
#define LPS001DL_DELTA_P_L_ADDR     0x2C

/**
*  @brief DELTA_P_H: Delta Pressure Data MSB
*  @detail <ul>
*  <li>Read Only</li>
*  <li>Default value: 0x00</li>
*  </ul>
*  @code
*  7:0 DP15-DP8: Delta Pressure Data MSB (if in Little Endian Mode --> BLE bit in CTRL_REG1 is 0)
*               Delta Pressure Data LSB (if in Big Endian Mode --> BLE bit in CTRL_REG1 is 1)
*  @endcode
*/
#define LPS001DL_DELTA_P_H_ADDR     0x2D


/**
*  @brief REF_P_L: Reference Pressure Data LSB
*  @detail <ul>
*  <li>Read/Write </li>
*  <li>Default value: 0x00</li>
*  </ul>
*  @code
*  7:0 REFL7-REFL0: Reference Pressure Data LSB (if in Little Endian Mode --> BLE bit in CTRL_REG1 is 0)
*                   Reference Pressure Data MSB (if in Big Endian Mode --> BLE bit in CTRL_REG1 is 1)
*  @endcode
*/
#define LPS001DL_REF_P_L_ADDR     0x30


/**
*  @brief REF_P_H: Reference Pressure Data MSB
*  @detail <ul>
*  <li>Read/write</li>
*  <li>Default value: 0x00</li>
*  </ul>
*  @code
*  7:0 REFL15-REFL8: Reference Pressure Data MSB (if in Little Endian Mode --> BLE bit in CTRL_REG1 is 0)
*                    Reference Pressure Data LSB (if in Big Endian Mode --> BLE bit in CTRL_REG1 is 1)
*  @endcode
*/
#define LPS001DL_REF_P_H_ADDR     0x31

/**
*  @brief THS_P_L: Threshold Pressure Data LSB
*  @detail <ul>
*  <li>Read/write</li>
*  <li>Default value: 0x00</li>
*  </ul>
*  @code
*  7:0 THS7-THS0: Threshold Pressure Data LSB (if in Little Endian Mode --> BLE bit in CTRL_REG1 is 0)
*                 Threshold Pressure Data MSB (if in Big Endian Mode --> BLE bit in CTRL_REG1 is 1)
*  @endcode
*/
#define LPS001DL_THS_P_L_ADDR     0x32


/**
*  @breif THS_P_H: Threshold Pressure Data MSB
*  @detail <ul>
*  <li>Read/write</li>
*  <li>Default value: 0x00</li>
*  </ul>
*  @code
*  7:0 THS15-THS8: Threshold Pressure Data MSB (if in Little Endian Mode --> BLE bit in CTRL_REG1 is 0)
*                  Threshold Pressure Data LSB (if in Big Endian Mode --> BLE bit in CTRL_REG1 is 1)
*  @endcode
*/
#define LPS001DL_THS_P_H_ADDR     0x33


/**
*  @brief INTERRUPT_CFG: Interrupt Configuration Register
*  *  @detail <ul>
*  <li>Read/write</li>
*  <li>Default value: 0x00</li>
*  </ul>
*  @code
*  7:3 RSV: reserved
*  2: LIR: Latch Interrupt Request into INT_SOURCE reg 0 - int. req not latched  1 - int. req latched
*  1: PL_E: Interrupt on pressure low 0 - int. disable 1 - int. enable when pressure
*                                     is lower than preset threshold
*  0: PH_E: Interrupt on pressure high 0 - int. disable 1 - int. enable when pressure
*                                     is higher than preset threshold
*  @endcode
*/

#define LPS001DL_INTERRUPT_CONFIG_ADDR     0x34


/**
*  @brief INT_SOURCE: Interrupt Source Register
*  @detail <ul>
*  <li>Read only</li>
*  <li>Default value: 0x00</li>
*  </ul>
*  @code
*  7:3 RSV: reserved
*  2: IA: Interrupt Active 0 - no int. has been generated  1 - one or more int. generated
*  1: PL: Delta pressure low 0 - no int. has been generated 1 - Low Delta pressure event generated
*  0: PH: Delta pressure high 0 - no int. has been generated 1 - High Delta pressure event generated
*  @endcode
*/
#define LPS001DL_INT_SOURCE_ADDR     0x35

/**
*  @brief INT_ACK: Interrupt Dummy Register
*  @detail <ul>
*  <li>Read only</li>
*  <li>Default value: 0x00</li>
*  <li>If LIR bit in INTERRUPT_CFG register is set to '1', a reading at this address clears INT_SOURCE register</li>
*  </ul>
*  @code
*  7:0 RSV: reserved
*  @endcode
*/
#define LPS001DL_INT_ACK_ADDR     0x36

/**
 * @}
 */  /* end of group LPS001DL_Register */

/**
 * @addtogroup LPS001DL_Structures
 * @{
 */

/**
 * @brief LPS001Dl configuration structure
 */
typedef struct
{
  u8 Lowpower;  /*!<Lowpwer enable or disable */
  u8 Output_Data_Rate;   /*!< See table 14 LPS001DL datasheet */
  u8 Data_Update;  /*!<Continuos update or update until MSB and LSB reading */
  u8 Endianess; /*!<Little or Big Endian */
}LPS001DL_ConfigTypeDef; //-->  use define below to choose the options (see table for more details)

/**
 * @brief LPS001Dl Interrupt configuration structure
 */
typedef struct
{
//  u16 LPS001DL_Int_Enable;
  u8 Mode; /*!<Active high or active low*/
  u8 PP_OD; /*!<Push-pull or Open-Drain */
  u8 Int2_Pad_Mode; /*!<See table 15 LPS001DL datasheet*/
  u8 Int1_Pad_Mode; /*!<See table 15 LPS001DL datasheet*/
  u8 Latch; /*!<Latch enable or disable*/
  u8 Delta_Press_Low; /*!<DPL enable or disable*/
  u8 Delta_Press_High; /*!<DPH enable or disable*/
}LPS001DL_InterruptTypeDef; // -->  use define below to choose the options (see table for more details)

/**
 * @}
 */  /* end of group LPS001DL_Structures */

/**
 * @addtogroup LPS001DL_Configuration_Define
 * @{
 */
#define P_Sensitivity     16  /*!< Pressure Sensitivity [LSb/mbar] */
#define T_Sensitivity     64  /*!< Temperature Sensitivity LSb/C */
#define P_Conversion      1.6//0.625 /*!< (1/P_Sensitivity)x10 => Pressure_Data x P_conversion = Pressure in mbar/10 */
#define T_Conversion      0.15625 /*!<(1/T_Sensitivity)x10 => Temperature_Data x T_Conversion = Temperature in °C/10*/
#define P_0               10132.5  /*!<Pressure value in dmbar at zero level */
#define H_p               7290    /*!< Constant (expressed in meter) for
                                  altitude-pressure conversion according to the formula:
                                  z[m]=H_p * ln(P_0/P)*/


#define LPS001DL_Output_Data_Rate_7_1            ((u8)0x00)
#define LPS001DL_Output_Data_Rate_7_7            ((u8)0x10)
#define LPS001DL_Output_Data_Rate_12_12          ((u8)0x30)

#define LPS001DL_Lowpower_Enable                 ((u8)0x80)
#define LPS001DL_Lowpower_Disable                ((u8)0x00)

#define LPS001DL_Little_Endian                   ((u8)0x00)
#define LPS001DL_Big_Endian                      ((u8)0x02)

#define LPS001DL_BDU_Continuos                   ((u8)0x00)
#define LPS001DL_BDU_Single                      ((u8)0x04)

#define LPS001DL_Interrupt_Enable                ((u8)0x08)
#define LPS001DL_Interrupt_Disable               ((u8)0x00)

#define LPS001DL_Interrupt_Active_High           ((u8)0x00)
#define LPS001DL_Interrupt_Active_Low            ((u8)0x80)
#define LPS001DL_Interrupt_Push_Pull             ((u8)0x00)
#define LPS001DL_Interrupt_Open_Drain            ((u8)0x40)

#define LPS001DL_Interrupt_Pressure_Gnd          ((u8)0x00)
#define LPS001DL_Interrupt_Pressure_High         ((u8)0x01)
#define LPS001DL_Interrupt_Pressure_Low          ((u8)0x02)
#define LPS001DL_Interrupt_Pressure_High_Low     ((u8)0x03)
#define LPS001DL_Interrupt_Pressure_Data_Ready   ((u8)0x04)
#define LPS001DL_Interrupt_Pressure_Tri_State    ((u8)0x07)

#define LPS001DL_Interrupt_Latch_Enable          ((u8)0x04)
#define LPS001DL_Interrupt_Latch_Disable         ((u8)0x00)

#define LSP001DL_Interrupt_DPL_Enable            ((u8)0x02)
#define LSP001DL_Interrupt_DPL_Disable           ((u8)0x00)

#define LSP001DL_Interrupt_DPH_Enable            ((u8)0x01)
#define LSP001DL_Interrupt_DPH_Disable           ((u8)0x00)

/**
 * @}
 */ /* end of group LPS001DL_Configuration_Define */
 


/* Exported functions  */

void LPS001DL_I2C_Init(void);
void LPS001DL_INT1_Config(void);
void LPS001DL_Config(LPS001DL_ConfigTypeDef *LPS001DL_Config_Struct);
void LPS001DL_Interrupt_Config(LPS001DL_InterruptTypeDef *LPS001DL_Interrupt_Struct);
void LPS001DL_Interrupt_Cmd(FunctionalState NewState);
void LPS001DL_Lowpower_Cmd(FunctionalState NewState);
void LPS001DL_PowerDown_Cmd(FunctionalState NewState);
void LPS001DL_Reboot_Cmd(void);
void LPS001DL_Read_Pressure_Regs(u8* pBuffer);
void LPS001DL_Read_Temperature_Regs(u8* pBuffer);
void LPS001DL_Set_Reference(u16 refvalue);
void LPS001DL_Set_Threshold(u16 refvalue);
void LPS001DL_Get_Altitude(u16* altitude);
void LPS001DL_Get_Pressure(u16* pressure);
void LPS001DL_Get_Raw_Pressure(u16* pressure);
void LPS001DL_Get_Temperature(s16* temperature);
void LPS001DL_Write(u8* pBuffer, u8 WriteAddr, u8 NumByteToWrite);
void LPS001DL_Read(u8* pBuffer, u8 ReadAddr, u8 NumByteToRead);

/**
 * @}
 */ /* end of group LPS001DL */


#endif /* __LPS001DL_I2C_H */

/******************* (C) COPYRIGHT 2010 STMicroelectronics *****END OF FILE****/
