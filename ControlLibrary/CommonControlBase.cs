﻿namespace ControlLibrary
{
    using System;

    public interface CommonControlBase
    {
        void Configure(ControlComponentConfiguration ctrlConf);
        void Copy();
        void GoTo(double timestamp);
        void GoToMax();
        void GoToMin();
        void HideControl();
        void SetVisbleDataAxe(int nYaxe, bool bVisible);
        void ShowControl();
        void ZoomIn();
        void ZoomInV();
        void ZoomOut();
        void ZoomOutV();
        void ZoomToFit();
        void ZoomToFitV();
    }
}

