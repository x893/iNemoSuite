﻿namespace ControlLibrary
{
    using System;
    using System.ComponentModel;
    using System.Windows.Forms;

    public abstract class CommunicationBase : Component
    {
        private string mCommunicationConfiguration;
        private string mCommunicationModule;
        private string mCommunicationPort;
        private bool mDeviceConnected;
        private DateTime mStartAcquisition;
        public CoomunicationSettings_Change OnCommunicationSettings_Change;
        public DataReceived OnDataReceived;
        public MessageToLog OnMessageToLog;
        public ControlLibrary.StartAcquisition OnStart;
        public StopAcquistion OnStop;
        public TCPState_Change OnTCPState_Change;

		public abstract string DeviceNickName { get; }
		public abstract DeviceSensorDataAvailable DeviceSensors { get; }
		public abstract DeviceManaged DeviceType { get; }
		public abstract string FirmwareVersion { get; }
		public abstract string HardwareVersion { get; }
		public abstract bool IsModeAHRSEnabled { get; }
		public abstract ToolStripItemCollection LocalMenuBarTool { get; }
		public abstract ToolStrip LocalToolBar { get; }
		public abstract string MCUID { get; }

        protected CommunicationBase()
        {
        }

        public abstract void Clear();

        public string AcquisitionInfo
        {
            get
            {
                string str = "";
                if (DeviceNickName != "")
                    str = DeviceNickName + "_";
                string str2 = str;
                return (str2 + StartAcquisition.Year.ToString() + StartAcquisition.Month.ToString("d2") + StartAcquisition.Day.ToString("d2") + "_" + StartAcquisition.Hour.ToString("d2") + StartAcquisition.Minute.ToString("d2") + StartAcquisition.Second.ToString("d2"));
            }
        }

        public abstract string CommSettingsInfo { get; }

		public string CommunicationConfiguration
		{
			get { return mCommunicationConfiguration; }
			set { mCommunicationConfiguration = value; }
		}

		public string CommunicationModule
		{
			get { return mCommunicationModule; }
			set { mCommunicationModule = value; }
		}

		public string CommunicationPort
		{
			get { return mCommunicationPort; }
			set
			{
				mCommunicationPort = value;
				if (OnCommunicationSettings_Change != null)
					OnCommunicationSettings_Change();
			}
		}

		protected string ConnectionString
		{
			get
			{
				string str = CommunicationConfiguration.Replace("@0", CommunicationModule);
				string[] strArray = CommunicationPort.Split(",".ToCharArray());
				for (int i = 1; i <= strArray.Length; i++)
					str = str.Replace("@" + i, strArray[i - 1]);
				return str;
			}
		}

		public bool DeviceConnected
		{
			get { return mDeviceConnected; }
			set { mDeviceConnected = value; }
		}

		protected DateTime StartAcquisition
		{
			get { return mStartAcquisition; }
			set { mStartAcquisition = value; }
		}
    }
}

