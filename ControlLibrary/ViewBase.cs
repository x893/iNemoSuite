﻿namespace ControlLibrary
{
    using System;
    using System.Windows.Forms;

    public abstract class ViewBase : UserControl
    {
        public ClearEvent OnClear;
        public MessageToLog OnMessageToLog;
        public SaveEvent OnSave;

        protected ViewBase()
        {
        }

        public abstract void AddDataObject(object data);
        public abstract bool ClearData();
        public abstract bool ClearData(bool enableAsk);
        public abstract void LoadDataFile(string strFileToLoad);
        public abstract void SaveFunction(string strFileName);
        public abstract void SetVisibleFirst();

        public abstract bool DataAvailable { get; }

        public abstract DeviceSensorDataAvailable DeviceSensors { get; set; }

        public abstract bool EnableRotationDataView { get; set; }

        public abstract ToolStripItemCollection LocalMenuBarTool { get; }

        public abstract ToolStripItemCollection LocalMenuBarView { get; }

        public abstract ToolStrip LocalToolBar { get; }
    }
}

