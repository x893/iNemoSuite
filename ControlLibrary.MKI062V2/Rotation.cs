﻿namespace ControlLibrary.MKI062V2
{
    using System;
    using System.Runtime.InteropServices;

    [StructLayout(LayoutKind.Sequential)]
    public struct Rotation
    {
        public float Roll;
        public float Pitch;
        public float Yaw;
    }
}

