﻿namespace ControlLibrary.MKI062V2
{
    using System;
    using System.Runtime.InteropServices;

    public class INEMO2_Device
    {
        private bool m_AHRS_Enabled;
        private INEMO2_DeviceHandle m_DeviceHandle;

        public INEMO2_Device()
        {
            this.m_DeviceHandle.FreeHandle();
            this.AHRS_Enabled = false;
        }

        public INEMO2_DeviceError Connect(string strConnection)
        {
            this.m_DeviceHandle = INEMO2_Connect(strConnection);
            if (this.m_DeviceHandle.Handle == -1)
            {
                return INEMO2_DeviceError.INEMO2_ERROR_INVALID_HANDLE;
            }
            return INEMO2_DeviceError.INEMO2_ERROR_NONE;
        }

        public INEMO2_DeviceError Disconnect()
        {
            INEMO2_DeviceError error = INEMO2_Disconnect(this.m_DeviceHandle);
            this.m_DeviceHandle.FreeHandle();
            return error;
        }

        public INEMO2_DeviceError EnterDFUMode()
        {
            return INEMO2_Command(this.m_DeviceHandle, INEMO2_DeviceCommand.INEMO2_CMD_ENTER_DFU_MODE);
        }

        public double GetBufferUsage(INEMO2_DeviceBuffers typeBuffer)
        {
            double pPerc = -1.0;
            INEMO2_GetBufferUsage(this.m_DeviceHandle, typeBuffer, ref pPerc);
            return pPerc;
        }

        public INEMO2_DeviceError GetInfo(INEMO2_DeviceInfoText info, out string strVersion)
        {
            int lpnSize = 0x200;
            byte[] data = new byte[lpnSize];
            INEMO2_DeviceError error = INEMO2_GetInfoText(this.m_DeviceHandle, info, data, ref lpnSize);
            strVersion = "";
            if (error == INEMO2_DeviceError.INEMO2_ERROR_NONE)
            {
                for (int i = 0; (i < lpnSize) && (data[i] > 0); i++)
                {
                    strVersion = strVersion + ((char) data[i]);
                }
            }
            return error;
        }

        public INEMO2_DeviceError GetModules(ref INEMO2_MODULES modules)
        {
            return INEMO2_GetModules(this.m_DeviceHandle, ref modules);
        }

        public INEMO2_DeviceError GetOutput(ref INEMO2_Output OutMode)
        {
            return INEMO2_GetOutput(this.m_DeviceHandle, ref OutMode);
        }

        public INEMO2_DeviceError GetReg(INEMO2_SENSORS sensor, uint reg, ref byte[] RegValue)
        {
            RegValue = new byte[0x10];
            uint length = (uint) RegValue.Length;
            INEMO2_DeviceError error = INEMO2_GetReg(this.m_DeviceHandle, sensor, reg, RegValue, ref length);
            if ((error == INEMO2_DeviceError.INEMO2_ERROR_NONE) && (length < 0x10))
            {
                Array.Resize<byte>(ref RegValue, (int) length);
            }
            return error;
        }

        public INEMO2_DeviceError GetSample(ref INEMO2_FrameData data)
        {
            return INEMO2_GetDataSample(this.m_DeviceHandle, ref data);
        }

        public INEMO2_DeviceError GetTrace(out string strVersion)
        {
            int lpnSize = 0x200;
            byte[] traceData = new byte[lpnSize];
            INEMO2_DeviceError error = INEMO2_GetTrace(this.m_DeviceHandle, traceData, ref lpnSize);
            strVersion = "";
            if (error == INEMO2_DeviceError.INEMO2_ERROR_NONE)
            {
                for (int i = 0; (i < lpnSize) && (traceData[i] > 0); i++)
                {
                    strVersion = strVersion + ((char) traceData[i]);
                }
            }
            return error;
        }

        public INEMO2_DeviceError Identify()
        {
            return INEMO2_Identify(this.m_DeviceHandle);
        }

        [DllImport("iNEMO2_SDK.dll")]
        private static extern INEMO2_DeviceError INEMO2_Command(INEMO2_DeviceHandle hHandle, INEMO2_DeviceCommand cmd);
        [DllImport("iNEMO2_SDK.dll")]
        private static extern INEMO2_DeviceHandle INEMO2_Connect(string lpszConnectionString);
        [DllImport("iNEMO2_SDK.dll")]
        private static extern INEMO2_DeviceError INEMO2_Disconnect(INEMO2_DeviceHandle hHandle);
        [DllImport("iNEMO2_SDK.dll")]
        private static extern INEMO2_DeviceError INEMO2_GetBufferUsage(INEMO2_DeviceHandle hHandle, INEMO2_DeviceBuffers typeBuffer, ref double pPerc);
        [DllImport("iNEMO2_SDK.dll")]
        private static extern INEMO2_DeviceError INEMO2_GetDataSample(INEMO2_DeviceHandle hHandle, ref INEMO2_FrameData pFrame);
        [DllImport("iNEMO2_SDK.dll")]
        private static extern INEMO2_DeviceError INEMO2_GetInfoText(INEMO2_DeviceHandle hHandle, INEMO2_DeviceInfoText info, byte[] data, ref int lpnSize);
        [DllImport("iNEMO2_SDK.dll")]
        private static extern INEMO2_DeviceError INEMO2_GetModules(INEMO2_DeviceHandle hDevHandle, ref INEMO2_MODULES pModules);
        [DllImport("iNEMO2_SDK.dll")]
        private static extern INEMO2_DeviceError INEMO2_GetOutput(INEMO2_DeviceHandle hHandle, ref INEMO2_Output output);
        [DllImport("iNEMO2_SDK.dll")]
        private static extern INEMO2_DeviceError INEMO2_GetReg(INEMO2_DeviceHandle hDevHandle, INEMO2_SENSORS sensor, uint reg, byte[] RegValue, ref uint pSizeRegValue);
        [DllImport("iNEMO2_SDK.dll")]
        private static extern INEMO2_DeviceError INEMO2_GetTrace(INEMO2_DeviceHandle hHandle, byte[] TraceData, ref int lpnSize);
        [DllImport("iNEMO2_SDK.dll")]
        private static extern INEMO2_DeviceError INEMO2_Identify(INEMO2_DeviceHandle hDevHandle);
        [DllImport("iNEMO2_SDK.dll")]
        private static extern uint INEMO2_IsConnect(INEMO2_DeviceHandle hHandle);
        [DllImport("iNEMO2_SDK.dll")]
        private static extern INEMO2_DeviceError INEMO2_RestoreDefault(INEMO2_DeviceHandle hDevHandle, INEMO2_SENSORS sensor, uint reg);
        [DllImport("iNEMO2_SDK.dll")]
        private static extern INEMO2_DeviceError INEMO2_SetOutput(INEMO2_DeviceHandle hHandle, ref INEMO2_Output output);
        [DllImport("iNEMO2_SDK.dll")]
        private static extern INEMO2_DeviceError INEMO2_SetReg(INEMO2_DeviceHandle hDevHandle, INEMO2_SENSORS sensor, uint reg, byte[] RegValue, uint sizeRegValue);
        public bool IsConnected()
        {
            return (INEMO2_IsConnect(this.m_DeviceHandle) != 0);
        }

        public INEMO2_DeviceError ResetDevice()
        {
            return INEMO2_Command(this.m_DeviceHandle, INEMO2_DeviceCommand.INEMO2_CMD_RESET_BOARD);
        }

        public INEMO2_DeviceError RestoreDefault(INEMO2_SENSORS sensor, uint reg)
        {
            return INEMO2_RestoreDefault(this.m_DeviceHandle, sensor, reg);
        }

        public INEMO2_DeviceError SetOutput(INEMO2_Output OutMode)
        {
            return INEMO2_SetOutput(this.m_DeviceHandle, ref OutMode);
        }

        public INEMO2_DeviceError SetReg(INEMO2_SENSORS sensor, uint reg, byte[] RegValue)
        {
            return INEMO2_SetReg(this.m_DeviceHandle, sensor, reg, RegValue, (uint) RegValue.Length);
        }

        public INEMO2_DeviceError Start(INEMO2_OUTPUT_MODE mode, INEMO2_OUTPUT_DATA sensors, int nFreq, int nSamples)
        {
            INEMO2_Output output;
            output.Frequency = (uint) nFreq;
            output.Samples = (uint) nSamples;
            output.Type = INEMO2_OUTPUT_TYPE.INEMO2_OUTPUT_TYPE_USB;
            output.Data = sensors;
            output.Mode = mode;
            INEMO2_DeviceError error = INEMO2_SetOutput(this.m_DeviceHandle, ref output);
            if (error == INEMO2_DeviceError.INEMO2_ERROR_NONE)
            {
                error = INEMO2_Command(this.m_DeviceHandle, INEMO2_DeviceCommand.INEMO2_CMD_START_ACQUISTION);
            }
            return error;
        }

        public INEMO2_DeviceError Stop()
        {
            return INEMO2_Command(this.m_DeviceHandle, INEMO2_DeviceCommand.INEMO2_CMD_STOP_ACQUISTION);
        }

        public INEMO2_DeviceError Trace(bool bTrace)
        {
            if (bTrace)
            {
                return INEMO2_Command(this.m_DeviceHandle, INEMO2_DeviceCommand.INEMO2_CMD_TRACE_ON);
            }
            return INEMO2_Command(this.m_DeviceHandle, INEMO2_DeviceCommand.INEMO2_CMD_TRACE_OFF);
        }

        public bool AHRS_Enabled
        {
            get
            {
                return this.m_AHRS_Enabled;
            }
            set
            {
                this.m_AHRS_Enabled = value;
            }
        }
    }
}

