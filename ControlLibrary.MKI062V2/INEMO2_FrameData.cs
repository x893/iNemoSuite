﻿namespace ControlLibrary.MKI062V2
{
    using System;
    using System.Runtime.InteropServices;

    [StructLayout(LayoutKind.Sequential, Pack=2)]
    public struct INEMO2_FrameData
    {
        public uint Size;
        public INEMO2_FRAME_VALID_FIELD ValidFields;
        public uint TimeStamp;
        public FrameComponents Accelometer;
        public FrameComponents Gyroscope;
        public FrameComponents Magnetic;
        public ushort Pressure;
        public short Temperature;
        public Rotation Rot;
        public Quaternion Quat;
        public double PressureInMbar
        {
            get
            {
                return (((double) this.Pressure) / 10.0);
            }
        }
        public double TemperatureInC
        {
            get
            {
                return (((double) this.Temperature) / 10.0);
            }
        }
        public double TimeStampInMillis
        {
            get
            {
                return (((double) this.TimeStamp) / 1000.0);
            }
        }
        public object[] ToObjArray()
        {
            object[] objArray = new object[] { 
                0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 
                0, 0, 0
             };
            objArray[0] = this.TimeStampInMillis;
            if ((this.ValidFields & INEMO2_FRAME_VALID_FIELD.FRAME_DATA_VALID_FIELD_ACC) > INEMO2_FRAME_VALID_FIELD.FRAME_DATA_VALID_FIELD_NONE)
            {
                objArray[1] = this.Accelometer.X;
                objArray[2] = this.Accelometer.Y;
                objArray[3] = this.Accelometer.Z;
            }
            if ((this.ValidFields & INEMO2_FRAME_VALID_FIELD.FRAME_DATA_VALID_FIELD_GYRO) > INEMO2_FRAME_VALID_FIELD.FRAME_DATA_VALID_FIELD_NONE)
            {
                objArray[4] = this.Gyroscope.X;
                objArray[5] = this.Gyroscope.Y;
                objArray[6] = this.Gyroscope.Z;
            }
            if ((this.ValidFields & INEMO2_FRAME_VALID_FIELD.FRAME_DATA_VALID_FIELD_MAG) > INEMO2_FRAME_VALID_FIELD.FRAME_DATA_VALID_FIELD_NONE)
            {
                objArray[7] = this.Magnetic.X;
                objArray[8] = this.Magnetic.Y;
                objArray[9] = this.Magnetic.Z;
            }
            if ((this.ValidFields & INEMO2_FRAME_VALID_FIELD.FRAME_DATA_VALID_FIELD_PRES) > INEMO2_FRAME_VALID_FIELD.FRAME_DATA_VALID_FIELD_NONE)
            {
                objArray[10] = this.PressureInMbar;
            }
            if ((this.ValidFields & INEMO2_FRAME_VALID_FIELD.FRAME_DATA_VALID_FIELD_TEMP) > INEMO2_FRAME_VALID_FIELD.FRAME_DATA_VALID_FIELD_NONE)
            {
                objArray[11] = this.TemperatureInC;
            }
            if ((this.ValidFields & INEMO2_FRAME_VALID_FIELD.FRAME_DATA_VALID_FIELD_ROTAT) > INEMO2_FRAME_VALID_FIELD.FRAME_DATA_VALID_FIELD_NONE)
            {
                objArray[12] = this.Rot.Roll;
                objArray[13] = this.Rot.Pitch;
                objArray[14] = this.Rot.Yaw;
            }
            if ((this.ValidFields & INEMO2_FRAME_VALID_FIELD.FRAME_DATA_VALID_FIELD_QUAT) > INEMO2_FRAME_VALID_FIELD.FRAME_DATA_VALID_FIELD_NONE)
            {
                objArray[15] = this.Quat.Q0;
                objArray[0x10] = this.Quat.Q1;
                objArray[0x11] = this.Quat.Q2;
                objArray[0x12] = this.Quat.Q3;
            }
            return objArray;
        }
    }
}

