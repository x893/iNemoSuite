﻿namespace iNEMO_Application
{
    using iNEMO_Application.Properties;
    using System;
    using System.ComponentModel;
    using System.Drawing;
    using System.Windows.Forms;

    public class Splash : Form
    {
        private IContainer components;
        private Label label1;
        private Timer timer1;

        public Splash()
        {
            this.InitializeComponent();
            this.timer1.Interval = 0x9c4;
            this.timer1.Enabled = true;
            this.label1.Text = "Version " + Application.ProductVersion;
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
            this.timer1 = new Timer(this.components);
            this.label1 = new Label();
            base.SuspendLayout();
            this.timer1.Tick += new EventHandler(this.timer1_Tick);
            this.label1.AutoSize = true;
            this.label1.Location = new Point(0x20, 0x1b5);
            this.label1.Name = "label1";
            this.label1.Size = new Size(0x23, 13);
            this.label1.TabIndex = 0;
            this.label1.Text = "label1";
            base.AutoScaleDimensions = new SizeF(6f, 13f);
            base.AutoScaleMode = AutoScaleMode.Font;
            this.BackColor = Color.White;
            this.BackgroundImage = Resources.splash;
            base.ClientSize = new Size(0x239, 480);
            base.ControlBox = false;
            base.Controls.Add(this.label1);
            base.FormBorderStyle = FormBorderStyle.None;
            base.MaximizeBox = false;
            base.MinimizeBox = false;
            base.Name = "Splash";
            base.ShowIcon = false;
            base.ShowInTaskbar = false;
            base.StartPosition = FormStartPosition.CenterScreen;
            base.TopMost = true;
            base.TransparencyKey = Color.Gray;
            base.ResumeLayout(false);
            base.PerformLayout();
        }

        private void timer1_Tick(object sender, EventArgs e)
        {
            base.Close();
        }
    }
}

