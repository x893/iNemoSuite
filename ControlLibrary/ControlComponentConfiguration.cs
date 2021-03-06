﻿namespace ControlLibrary
{
    using System;
    using System.Collections.Generic;
    using System.Data;
    using System.Windows.Forms;

    public class ControlComponentConfiguration
    {
        private List<AxeInformation> mAxes = new List<AxeInformation>();
        private DataTable mDataInMemory;
        private string mGroupName = "";
        private bool mShowStacked = false;
        private BindingSource mSource;

        public List<AxeInformation> Axes
        {
            get
            {
                return this.mAxes;
            }
        }

        public DataTable DataInMemory
        {
            get
            {
                return this.mDataInMemory;
            }
            set
            {
                this.mDataInMemory = value;
            }
        }

        public string GroupName
        {
            get
            {
                return this.mGroupName;
            }
            set
            {
                this.mGroupName = value;
            }
        }

        public bool ShowStacked
        {
            get
            {
                return this.mShowStacked;
            }
            set
            {
                this.mShowStacked = value;
            }
        }

        public BindingSource Source
        {
            get
            {
                return this.mSource;
            }
            set
            {
                this.mSource = value;
            }
        }
    }
}

