﻿namespace ControlLibrary.MKI062V2
{
    using System;
    using System.Runtime.InteropServices;

    [StructLayout(LayoutKind.Sequential)]
    public struct INEMO2_DeviceHandle
    {
        public const int INEMO2_DEVICE_HANDLE_INVALID = -1;
        private int hHandle;
        public int Handle
        {
            get
            {
                return this.hHandle;
            }
        }
        public void FreeHandle()
        {
            this.hHandle = -1;
        }
    }
}

