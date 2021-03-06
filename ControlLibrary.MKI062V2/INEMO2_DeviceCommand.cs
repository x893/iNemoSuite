﻿namespace ControlLibrary.MKI062V2
{
    using System;

    public enum INEMO2_DeviceCommand : uint
    {
        INEMO2_CMD_ENTER_DFU_MODE = 6,
        INEMO2_CMD_LED_OFF = 8,
        INEMO2_CMD_LED_ON = 7,
        INEMO2_CMD_RESET_BOARD = 5,
        INEMO2_CMD_START_ACQUISTION = 1,
        INEMO2_CMD_STOP_ACQUISTION = 2,
        INEMO2_CMD_TRACE_OFF = 4,
        INEMO2_CMD_TRACE_ON = 3
    }
}

