﻿namespace ControlLibrary.MKI062V2
{
    using System;

    public enum INEMO2_FRAME_VALID_FIELD : uint
    {
        FRAME_DATA_VALID_FIELD_ACC = 1,
        FRAME_DATA_VALID_FIELD_ALL = 0x7f,
        FRAME_DATA_VALID_FIELD_ALL_SENS = 0x1f,
        FRAME_DATA_VALID_FIELD_GYRO = 2,
        FRAME_DATA_VALID_FIELD_MAG = 4,
        FRAME_DATA_VALID_FIELD_NONE = 0,
        FRAME_DATA_VALID_FIELD_PRES = 8,
        FRAME_DATA_VALID_FIELD_QUAT = 0x40,
        FRAME_DATA_VALID_FIELD_ROTAT = 0x20,
        FRAME_DATA_VALID_FIELD_TEMP = 0x10
    }
}

