/**
  * @file    iNEMO_AHRS.h 
  * @author  ART Team IMS-Systems Lab
  * @version V1.2.0  [FW v2.0.0]
  * @date    09/20/2010
  * @brief   This file is the header of the AHRS of iNEMO.This is the interface from your application
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




#ifndef __INEMO_AHRS
#define __INEMO_AHRS

#ifdef __cplusplus
 extern "C" {
#endif 
  

#include <stddef.h>

/** @defgroup iNEMO_AHRS
  * @{
  */

/** @defgroup iNEMO_AHRS_Structures
  * @{
  */

/**
 * @struct
 * @brief iNEMO Sensor Data Struct
 */
typedef struct
{
  unsigned int m_nCount;  /*!< It is used to perform correction at different frequencies */
  float   m_fDeltaTime;   /*!< It should trace the time difference */

  float m_fAcc[3];		/*!< The Acceleration Measurement */
  float m_fGyro[3];		/*!< The Gyroscope Measurement */
  float m_fMag[3];		/*!< The Magnitude Measurement */

  float m_fScaleFactor[9];  /*!< The Scale Factor Vector for each Measurement */
  float m_fOffset[9];		/*!< The Offset Vector for each Measurement */
} iNEMO_SENSORDATA;



/**
 * @struct
 * @brief iNEMO Euler Angle Struct
 */

typedef struct
{
  float m_fRoll;          /*!< Roll Angle */ 
  float m_fPitch;         /*!< Pitch Angle */  
  float m_fYaw;           /*!< Yaw Angle */ 
} iNEMO_EULER_ANGLES;


/**
 * @typedef
 * @brief iNEMO Quaternion Type
 */

typedef float iNEMO_QUAT[4];

/**
 * @}
 */ /* end of group iNEMO_AHRS_Structures */

/**
 * @addtogroup iNEMO_Magn_Calib_Define
 * @details Calibration of the Magnetometer:
 *  The following values have to be set accordly to the final system.
 *  Further details are available at the following link
*  http://www.ssec.honeywell.com/magnetic/datasheets/amr.pdf
 *
 * for EMF parameter, you could find online calculator at
 * http://www.ngdc.noaa.gov/geomagmodels/IGRFWMM.jsp
 *
 * @{
*/

#define   ERX    1.0f  		/*!< Ellispoid radius [x] */
#define   ERY    1.0f  		/*!< Ellispoid radius [y]*/
#define   ERZ    1.0f  		/*!< Ellispoid radius [z]*/
#define   ECCX   0.009f 	/*!< ECCX   Ellispoid center coordinate [x]*/
#define   ECCY   -0.1280f   /*!< ECCY   Ellispoid center coordinate [y]*/
#define   ECCZ   0.0f       /*!< ECCZ   Ellispoid center coordinate [z]*/

#define   EMF     0.45f /*!< Earth Magnetic Field [Gauss] in your location */


/**
 * @}
 */ /* end of group iNEMO_Magn_Calib_Define */


/* External Functions --------------------------------------------------------*/
extern void *iNEMO_Malloc(size_t size);
extern void iNEMO_Free(void *p);

/** @defgroup iNEMO_AHRS_Function
* @{
*/

/**
********************************************************************************
* @brief Initialize all the AHRS variable
* @param pSensorData : Sensor Data
* @param pAngle      : Roll, Pitch and Yaw Angles
* @param pQuat       : Quaternion
* @retval None
* @par Functions called:
* @ref iNEMO_fMatCreateZero
********************************************************************************
*/
void iNEMO_AHRS_Init(iNEMO_SENSORDATA*    pExtSensorData,
                    iNEMO_EULER_ANGLES*  pExtAngle,
                    iNEMO_QUAT*          pExtQuat);


/**
********************************************************************************
* @brief Update AHRS variables
 @param pSensorData  : Sensor Data
* @param pAngle      : Roll, Pitch and Yaw Angles
* @param pQuat       : Quaternion
* @retval None
* @par Functions called:
* @ref iNEMO_PropagateP
* @ref iNEMO_CalculateK
* @ref iNEMO_UpdateP
* @ref iNEMO_fMatCopy
********************************************************************************
*/
void iNEMO_AHRS_Update(iNEMO_SENSORDATA*    pExtSensorData,
                      iNEMO_EULER_ANGLES*  pExtAngle,
                      iNEMO_QUAT*          pExtQuat);


/**
********************************************************************************
* @brief Delete all the AHRS variables allocated dinamically
* @param pSensorData : Sensor Data
* @param pAngle      : Roll, Pitch and Yaw Angles
* @param pQuat       : Quaternion
* @retval None
* @par Functions called:
* @ref iNEMO_fMatFree
********************************************************************************
*/
void iNEMO_AHRS_DeInit(iNEMO_SENSORDATA*    pSensorData,
                      iNEMO_EULER_ANGLES*  pAngle,
                      iNEMO_QUAT*          pQuat);

/**
 * @}
 */ /* end of group iNEMO_AHRS_Function */

/**
 * @}
 */ /* end of group iNEMO_AHRS */

#endif /*__INEMO_AHRS */

/******************* (C) COPYRIGHT 2010 STMicroelectronics *****END OF FILE****/


