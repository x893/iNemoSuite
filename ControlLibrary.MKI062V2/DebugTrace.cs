﻿namespace ControlLibrary.MKI062V2
{
    using ControlLibrary.Properties;
    using System;
    using System.ComponentModel;
    using System.Drawing;
    using System.IO;
    using System.Windows.Forms;

    public class DebugTrace : Form
    {
        private ColumnHeader columnHeaderData;
        private ColumnHeader columnHeaderTS;
        private IContainer components;
        public INEMO2_Device Device;
        private ListView listViewDataTrace;
        private SaveFileDialog saveLogFileDialog;
        private Timer timer1;
        private ToolStrip toolStrip1;
        private ToolStripButton toolStripButtonClear;
        private ToolStripButton toolStripButtonSave;
        private ToolStripButton toolStripButtonStart;
        private ToolStripButton toolStripButtonStop;
        private ToolStripSeparator toolStripSeparator1;

        public DebugTrace()
        {
            this.InitializeComponent();
            this.listViewDataTrace.Items.Clear();
            this.Device = null;
            this.toolStripButtonStop.Enabled = false;
            this.toolStripButtonStart.Enabled = true;
            this.toolStripButtonSave.Enabled = false;
            this.toolStripButtonClear.Enabled = false;
        }

        private void AddDataLog(string str)
        {
            this.toolStripButtonSave.Enabled = true;
            this.toolStripButtonClear.Enabled = true;
            this.listViewDataTrace.Items.Add(this.listViewDataTrace.Items.Count.ToString()).SubItems.Add(str);
            this.listViewDataTrace.Items[this.listViewDataTrace.Items.Count - 1].EnsureVisible();
            this.listViewDataTrace.Refresh();
        }

        private void ClearDataTrace()
        {
            this.listViewDataTrace.Items.Clear();
            this.toolStripButtonSave.Enabled = false;
            this.toolStripButtonClear.Enabled = false;
        }

        private void DebugTrace_FormClosing(object sender, FormClosingEventArgs e)
        {
            this.toolStripButtonStop.PerformClick();
        }

        protected override void Dispose(bool disposing)
        {
            if (disposing && (this.components != null))
            {
                this.components.Dispose();
            }
            base.Dispose(disposing);
        }

        private void InitializeComponent()
        {
            this.components = new Container();
            ComponentResourceManager manager = new ComponentResourceManager(typeof(DebugTrace));
            this.toolStrip1 = new ToolStrip();
            this.toolStripSeparator1 = new ToolStripSeparator();
            this.listViewDataTrace = new ListView();
            this.columnHeaderTS = new ColumnHeader();
            this.columnHeaderData = new ColumnHeader();
            this.timer1 = new Timer(this.components);
            this.toolStripButtonSave = new ToolStripButton();
            this.toolStripButtonClear = new ToolStripButton();
            this.toolStripButtonStart = new ToolStripButton();
            this.toolStripButtonStop = new ToolStripButton();
            this.saveLogFileDialog = new SaveFileDialog();
            this.toolStrip1.SuspendLayout();
            base.SuspendLayout();
            this.toolStrip1.Items.AddRange(new ToolStripItem[] { this.toolStripButtonSave, this.toolStripButtonClear, this.toolStripSeparator1, this.toolStripButtonStart, this.toolStripButtonStop });
            this.toolStrip1.Location = new Point(0, 0);
            this.toolStrip1.Name = "toolStrip1";
            this.toolStrip1.Size = new Size(0x250, 0x19);
            this.toolStrip1.TabIndex = 0;
            this.toolStrip1.Text = "toolStrip1";
            this.toolStripSeparator1.Name = "toolStripSeparator1";
            this.toolStripSeparator1.Size = new Size(6, 0x19);
            this.listViewDataTrace.Columns.AddRange(new ColumnHeader[] { this.columnHeaderTS, this.columnHeaderData });
            this.listViewDataTrace.Dock = DockStyle.Fill;
            this.listViewDataTrace.FullRowSelect = true;
            this.listViewDataTrace.Location = new Point(0, 0x19);
            this.listViewDataTrace.Name = "listViewDataTrace";
            this.listViewDataTrace.Size = new Size(0x250, 0x100);
            this.listViewDataTrace.TabIndex = 1;
            this.listViewDataTrace.UseCompatibleStateImageBehavior = false;
            this.listViewDataTrace.View = View.Details;
            this.columnHeaderTS.Text = "Count";
            this.columnHeaderTS.Width = 0x45;
            this.columnHeaderData.Text = "Text Data";
            this.columnHeaderData.Width = 530;
            this.timer1.Interval = 500;
            this.timer1.Tick += new EventHandler(this.timer1_Tick);
            this.toolStripButtonSave.DisplayStyle = ToolStripItemDisplayStyle.Image;
            this.toolStripButtonSave.Image = Resources.document_save_as;
            this.toolStripButtonSave.ImageTransparentColor = Color.Magenta;
            this.toolStripButtonSave.Name = "toolStripButtonSave";
            this.toolStripButtonSave.Size = new Size(0x17, 0x16);
            this.toolStripButtonSave.Text = "Save logged trace";
            this.toolStripButtonSave.Click += new EventHandler(this.toolStripButtonSave_Click);
            this.toolStripButtonClear.DisplayStyle = ToolStripItemDisplayStyle.Image;
            this.toolStripButtonClear.Image = Resources.Clear;
            this.toolStripButtonClear.ImageTransparentColor = Color.Magenta;
            this.toolStripButtonClear.Name = "toolStripButtonClear";
            this.toolStripButtonClear.Size = new Size(0x17, 0x16);
            this.toolStripButtonClear.Text = "Clear log trace";
            this.toolStripButtonClear.Click += new EventHandler(this.toolStripButtonClear_Click);
            this.toolStripButtonStart.DisplayStyle = ToolStripItemDisplayStyle.Image;
            this.toolStripButtonStart.Image = Resources.StartAcquistion;
            this.toolStripButtonStart.ImageTransparentColor = Color.Magenta;
            this.toolStripButtonStart.Name = "toolStripButtonStart";
            this.toolStripButtonStart.Size = new Size(0x17, 0x16);
            this.toolStripButtonStart.Text = "Start trace";
            this.toolStripButtonStart.Click += new EventHandler(this.toolStripButtonStart_Click);
            this.toolStripButtonStop.DisplayStyle = ToolStripItemDisplayStyle.Image;
            this.toolStripButtonStop.Image = Resources.StopAcquistion;
            this.toolStripButtonStop.ImageTransparentColor = Color.Magenta;
            this.toolStripButtonStop.Name = "toolStripButtonStop";
            this.toolStripButtonStop.Size = new Size(0x17, 0x16);
            this.toolStripButtonStop.Text = "Stop trace";
            this.toolStripButtonStop.Click += new EventHandler(this.toolStripButtonStop_Click);
            this.saveLogFileDialog.DefaultExt = "log";
            this.saveLogFileDialog.Filter = "Log file (*.log)|*.log";
            this.saveLogFileDialog.InitialDirectory = "Environment.SpecialFolder.MyDocuments";
            base.AutoScaleDimensions = new SizeF(6f, 13f);
            base.AutoScaleMode = AutoScaleMode.Font;
            base.ClientSize = new Size(0x250, 0x119);
            base.Controls.Add(this.listViewDataTrace);
            base.Controls.Add(this.toolStrip1);
            base.Icon = (Icon) manager.GetObject("$this.Icon");
            base.Name = "DebugTrace";
            base.StartPosition = FormStartPosition.CenterParent;
            this.Text = "Trace";
            base.FormClosing += new FormClosingEventHandler(this.DebugTrace_FormClosing);
            this.toolStrip1.ResumeLayout(false);
            this.toolStrip1.PerformLayout();
            base.ResumeLayout(false);
            base.PerformLayout();
        }

        private void ReadAllDataTrace()
        {
            for (string str = ""; this.Device.GetTrace(out str) == INEMO2_DeviceError.INEMO2_ERROR_NONE; str = "")
            {
                this.AddDataLog(str);
            }
        }

        private void timer1_Tick(object sender, EventArgs e)
        {
            this.ReadAllDataTrace();
        }

        private void toolStripButtonClear_Click(object sender, EventArgs e)
        {
            if ((this.listViewDataTrace.Items.Count >= 0) && (MessageBox.Show("There are data in trace window not saved. \nDo you want to clear the log anyway?", "Information", MessageBoxButtons.YesNo, MessageBoxIcon.Asterisk) == DialogResult.Yes))
            {
                this.ClearDataTrace();
            }
        }

        private void toolStripButtonSave_Click(object sender, EventArgs e)
        {
            this.saveLogFileDialog.FileName = this.StringTraceFileName;
            if (this.saveLogFileDialog.ShowDialog() == DialogResult.OK)
            {
                StreamWriter writer = new StreamWriter(this.saveLogFileDialog.FileName);
                if (writer != null)
                {
                    writer.Write("Count\t");
                    writer.Write("Message");
                    writer.WriteLine();
                    lock (this.listViewDataTrace)
                    {
                        foreach (ListViewItem item in this.listViewDataTrace.Items)
                        {
                            writer.Write(item.Text + "\t");
                            writer.Write(item.SubItems[1].Text);
                            writer.WriteLine();
                        }
                        writer.Close();
                        this.ClearDataTrace();
                    }
                }
            }
        }

        private void toolStripButtonStart_Click(object sender, EventArgs e)
        {
            if (this.Device.Trace(true) == INEMO2_DeviceError.INEMO2_ERROR_NONE)
            {
                this.toolStripButtonStop.Enabled = true;
                this.toolStripButtonStart.Enabled = false;
                this.timer1.Start();
            }
            else
            {
                this.AddDataLog("TRACE not supported");
            }
        }

        private void toolStripButtonStop_Click(object sender, EventArgs e)
        {
            if (this.timer1.Enabled)
            {
                this.Device.Trace(false);
                this.toolStripButtonStop.Enabled = false;
                this.toolStripButtonStart.Enabled = true;
                this.ReadAllDataTrace();
                this.timer1.Stop();
            }
        }

        private string StringTraceFileName
        {
            get
            {
                return ("iNEMO2_TRACE_" + DateTime.Now.Year.ToString() + DateTime.Now.Month.ToString("d2") + DateTime.Now.Day.ToString("d2") + "_" + DateTime.Now.Hour.ToString("d2") + DateTime.Now.Minute.ToString("d2") + DateTime.Now.Second.ToString("d2"));
            }
        }
    }
}

