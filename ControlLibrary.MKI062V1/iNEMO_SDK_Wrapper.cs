﻿namespace ControlLibrary.MKI062V1
{
    using System;
    using System.Runtime.InteropServices;

    internal class iNEMO_SDK_Wrapper
    {
        public int Connect(string strConnection)
        {
            return INEMO_SDK_Connect(strConnection);
        }

        public int Disconnect()
        {
            return INEMO_SDK_Disconnect();
        }

        public double GetBufferUsage()
        {
            double pPerc = 0.0;
            INEMO_SDK_GetBufferUsage(ref pPerc);
            return pPerc;
        }

        public int GetSample(ref FrameData data)
        {
            return INEMO_SDK_GetSample(ref data);
        }

        public int GetVersion(out string strVersion)
        {
            int lpnSize = 0xff;
            byte[] a = new byte[lpnSize];
            int num = INEMO_SDK_GetVersion(a, ref lpnSize);
            strVersion = "";
            for (int i = 0; (i < lpnSize) && (a[i] > 0); i++)
            {
                strVersion = strVersion + ((char) a[i]);
            }
            return num;
        }

        [DllImport("iNEMO_SDK.dll")]
        private static extern int INEMO_SDK_Connect(string lpszConnectionString);
        [DllImport("iNEMO_SDK.dll")]
        private static extern int INEMO_SDK_Disconnect();
        [DllImport("iNEMO_SDK.dll")]
        private static extern int INEMO_SDK_GetBufferUsage(ref double pPerc);
        [DllImport("iNEMO_SDK.dll")]
        private static extern int INEMO_SDK_GetSample(ref FrameData pFrame);
        [DllImport("iNEMO_SDK.dll")]
        private static extern int INEMO_SDK_GetVersion(byte[] a, ref int lpnSize);
        [DllImport("iNEMO_SDK.dll")]
        private static extern int INEMO_SDK_IsConnected();
        [DllImport("iNEMO_SDK.dll")]
        private static extern int INEMO_SDK_Start(int nFreq, int nSamples);
        [DllImport("iNEMO_SDK.dll")]
        private static extern int INEMO_SDK_Stop();
        public bool IsConnected()
        {
            return (INEMO_SDK_IsConnected() != 0);
        }

        public int Start(int nFreq, int nSamples)
        {
            return INEMO_SDK_Start(nFreq, nSamples);
        }

        public int Stop()
        {
            return INEMO_SDK_Stop();
        }
    }
}

