﻿namespace ControlLibrary
{
    using System;
    using System.Drawing;
    using System.Windows.Forms;

    public class ToolStripSCTexBox : ToolStripControlHost
    {
        public ToolStripSCTexBox() : base(new SCTextBox())
        {
            this.TextBox.ContextMenuStrip = new ContextMenuStrip();
            base.ControlAlign = ContentAlignment.MiddleCenter;
        }

        public bool AcceptOnlyNumber
        {
            get
            {
                if (this.TextBox != null)
                {
                    return this.TextBox.AcceptOnlyNumber;
                }
                return true;
            }
            set
            {
                if (this.TextBox != null)
                {
                    this.TextBox.AcceptOnlyNumber = value;
                }
            }
        }

        public int MaxLength
        {
            get
            {
                if (this.TextBox != null)
                {
                    return this.TextBox.MaxLength;
                }
                return 0;
            }
            set
            {
                if (this.TextBox != null)
                {
                    this.TextBox.MaxLength = value;
                }
            }
        }

        public ulong MaxValue
        {
            get
            {
                if (this.TextBox != null)
                {
                    return this.TextBox.MaxValue;
                }
                return ulong.MaxValue;
            }
            set
            {
                if (this.TextBox != null)
                {
                    this.TextBox.MaxValue = value;
                }
            }
        }

        public ulong MinValue
        {
            get
            {
                if (this.TextBox != null)
                {
                    return this.TextBox.MinValue;
                }
                return 0L;
            }
            set
            {
                if (this.TextBox != null)
                {
                    this.TextBox.MinValue = value;
                }
            }
        }

        public override System.Drawing.Size Size
        {
            get
            {
                return this.TextBox.Size;
            }
            set
            {
                if (this.TextBox != null)
                {
                    this.TextBox.MinimumSize = value;
                    this.TextBox.MaximumSize = value;
                }
            }
        }

        private SCTextBox TextBox
        {
            get
            {
                return (base.Control as SCTextBox);
            }
        }

        public HorizontalAlignment TextBoxAlign
        {
            get
            {
                if (this.TextBox != null)
                {
                    return this.TextBox.TextAlign;
                }
                return HorizontalAlignment.Center;
            }
            set
            {
                if (this.TextBox != null)
                {
                    this.TextBox.TextAlign = value;
                }
            }
        }
    }
}

