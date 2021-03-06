﻿namespace ControlLibrary
{
    using System;
    using System.Drawing;
    using System.Runtime.CompilerServices;
    using System.Windows.Forms;

    public class SingleSelection
    {
        private System.Windows.Forms.Button button;
        private Color buttonBackColor = Color.Red;
        private bool mEabled;
        private ToolStripMenuItem mnuControlMenu;
        private bool mSelected;
        public ControlSelectEvent OnSelected;
        private System.Windows.Forms.UserControl prntControl;
        private System.Windows.Forms.UserControl userControl;

        public SingleSelection(System.Windows.Forms.Button btn, System.Windows.Forms.UserControl ctrl, ToolStripMenuItem mnu, System.Windows.Forms.UserControl parent)
        {
            this.Button = btn;
            this.UserControl = ctrl;
            this.MenuControl = mnu;
            this.ParentControl = parent;
            if (this.ParentControl != null)
            {
                this.ParentControl.Controls.Add(ctrl);
            }
            if (this.Button != null)
            {
                this.Button.Click += new EventHandler(this.Button_Click);
            }
            if (this.MenuControl != null)
            {
                this.MenuControl.Click += new EventHandler(this.Button_Click);
            }
        }

        private void Button_Click(object sender, EventArgs e)
        {
            if (this.OnSelected != null)
            {
                this.OnSelected(this);
            }
        }

        public void SetBigButton(bool bBig)
        {
            if (this.button != null)
            {
                Size size;
                if (bBig)
                {
                    size = new Size(0x40, 0x40);
                }
                else
                {
                    size = new Size(0x20, 0x20);
                }
                this.button.Size = size;
            }
        }

        public Color BackColor
        {
            get
            {
                return this.buttonBackColor;
            }
            set
            {
                this.buttonBackColor = value;
            }
        }

        public System.Windows.Forms.Button Button
        {
            get
            {
                return this.button;
            }
            set
            {
                this.button = value;
            }
        }

        public bool Enable
        {
            get
            {
                return this.mEabled;
            }
            set
            {
                this.mEabled = value;
                if (this.Button != null)
                {
                    this.Button.Enabled = this.mEabled;
                }
                if (this.UserControl != null)
                {
                    this.UserControl.Enabled = this.mEabled;
                    if (!this.mEabled)
                    {
                        this.Selected = false;
                    }
                }
                if (this.MenuControl != null)
                {
                    this.MenuControl.Enabled = this.mEabled;
                }
            }
        }

        public ToolStripMenuItem MenuControl
        {
            get
            {
                return this.mnuControlMenu;
            }
            set
            {
                this.mnuControlMenu = value;
            }
        }

        public System.Windows.Forms.UserControl ParentControl
        {
            get
            {
                return this.prntControl;
            }
            set
            {
                this.prntControl = value;
            }
        }

        public bool Selected
        {
            get
            {
                return this.mSelected;
            }
            set
            {
                this.mSelected = value;
                if (this.mSelected)
                {
                    this.Button.BackColor = this.UserControl.BackColor;
                    ((CommonControlBase) this.UserControl).ShowControl();
                    this.UserControl.BringToFront();
                }
                else
                {
                    this.Button.BackColor = this.prntControl.BackColor;
                    ((CommonControlBase) this.UserControl).HideControl();
                }
            }
        }

        public System.Windows.Forms.UserControl UserControl
        {
            get
            {
                return this.userControl;
            }
            set
            {
                this.userControl = value;
            }
        }

        public delegate void ControlSelectEvent(SingleSelection sel);
    }
}

