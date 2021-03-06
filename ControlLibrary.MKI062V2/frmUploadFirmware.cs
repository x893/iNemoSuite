﻿namespace ControlLibrary.MKI062V2
{
    using ControlLibrary;
    using System;
    using System.ComponentModel;
    using System.Drawing;
    using System.Threading;
    using System.Windows.Forms;

    public class frmUploadFirmware : Form
    {
        private Button btnBrowse;
        private Button btnClose;
        private Button btnCloseLeave;
        private Button btnUpload;
        private Button btnVerify;
        private IContainer components;
        private Label lblFile;
        private Label lblStatus;
        private bool OnlyVerify;
        public MessageToLog OnMessageToLogSettings;
        private OpenFileDialog openFileDialogDFU;
        private ProgressBar progressBar1;
        private UpGradeStatus Status;
        private DateTime TimeOutPhase;
        private const uint TimeOutPhase_MAX = 30;
        private System.Windows.Forms.Timer timer1;
        private TextBox txtFileToUpload;

        public frmUploadFirmware()
        {
            this.InitializeComponent();
            this.txtFileToUpload.Text = "";
            this.lblStatus.Text = "";
            this.Status = UpGradeStatus.STATUS_NONE;
            this.OnlyVerify = false;
        }

        private void btnBrowse_Click(object sender, EventArgs e)
        {
            this.openFileDialogDFU.FileName = "";
            if (this.openFileDialogDFU.ShowDialog() == DialogResult.OK)
            {
                if (this.openFileDialogDFU.FileName != "")
                {
                    this.btnUpload.Enabled = true;
                    this.btnVerify.Enabled = true;
                    this.txtFileToUpload.Text = this.openFileDialogDFU.FileName;
                    if (this.OnMessageToLogSettings != null)
                    {
                        this.OnMessageToLogSettings("File to upload [" + this.openFileDialogDFU.FileName + "]");
                    }
                }
                else
                {
                    this.btnUpload.Enabled = false;
                    this.btnVerify.Enabled = false;
                    this.txtFileToUpload.Text = "";
                }
            }
        }

        private void btnCloseLeave_Click(object sender, EventArgs e)
        {
            if (STDFU_EX_Wrapper.STDFU_EX_LeaveDFU() != STDFU_EX_Wrapper.STDFU_EX_Error.STDFU_EX_ERROR_NONE)
            {
                if (this.OnMessageToLogSettings != null)
                {
                    this.OnMessageToLogSettings("Error on Leave DFU");
                }
            }
            else if (this.OnMessageToLogSettings != null)
            {
                this.OnMessageToLogSettings("Leave DFU successfully");
            }
            Thread.Sleep(500);
            base.Close();
        }

        private void btnUpload_Click(object sender, EventArgs e)
        {
            this.Status = UpGradeStatus.STATUS_NONE;
            this.timer1.Enabled = true;
            this.btnBrowse.Enabled = false;
            this.btnClose.Enabled = false;
            this.btnCloseLeave.Enabled = false;
            this.btnUpload.Enabled = false;
            this.btnVerify.Enabled = false;
            this.TimeOutPhase = DateTime.Now;
            this.OnlyVerify = false;
            if (this.OnMessageToLogSettings != null)
            {
                this.OnMessageToLogSettings("Start firmware upgrading...");
            }
        }

        private void btnVerify_Click(object sender, EventArgs e)
        {
            this.OnlyVerify = true;
            this.TimeOutPhase = DateTime.Now;
            this.progressBar1.Value = 0;
            this.lblStatus.Text = "Initializing...";
            if (STDFU_EX_Wrapper.STDFU_EX_Init(this.txtFileToUpload.Text) == STDFU_EX_Wrapper.STDFU_EX_Error.STDFU_EX_ERROR_NONE)
            {
                this.Status = UpGradeStatus.STATUS_VERIFY;
            }
            else
            {
                this.Status = UpGradeStatus.STATUS_ERROR;
            }
            this.timer1.Enabled = true;
            this.btnBrowse.Enabled = false;
            this.btnClose.Enabled = false;
            this.btnCloseLeave.Enabled = false;
            this.btnUpload.Enabled = false;
            this.btnVerify.Enabled = false;
            if (this.OnMessageToLogSettings != null)
            {
                this.OnMessageToLogSettings("Start firmware verify...");
            }
        }

        protected override void Dispose(bool disposing)
        {
            if (disposing && (this.components != null))
            {
                this.components.Dispose();
            }
            base.Dispose(disposing);
        }

        private void frmUploadFirmware_FormClosing(object sender, FormClosingEventArgs e)
        {
            e.Cancel = this.timer1.Enabled;
        }

        private void InitializeComponent()
        {
            this.components = new Container();
            this.txtFileToUpload = new TextBox();
            this.lblFile = new Label();
            this.btnBrowse = new Button();
            this.progressBar1 = new ProgressBar();
            this.btnUpload = new Button();
            this.btnClose = new Button();
            this.lblStatus = new Label();
            this.openFileDialogDFU = new OpenFileDialog();
            this.timer1 = new System.Windows.Forms.Timer(this.components);
            this.btnVerify = new Button();
            this.btnCloseLeave = new Button();
            base.SuspendLayout();
            this.txtFileToUpload.Location = new Point(12, 0x1a);
            this.txtFileToUpload.Name = "txtFileToUpload";
            this.txtFileToUpload.ReadOnly = true;
            this.txtFileToUpload.Size = new Size(0x1b7, 20);
            this.txtFileToUpload.TabIndex = 0;
            this.lblFile.AutoSize = true;
            this.lblFile.Location = new Point(12, 9);
            this.lblFile.Name = "lblFile";
            this.lblFile.Size = new Size(0x4d, 13);
            this.lblFile.TabIndex = 1;
            this.lblFile.Text = "File to upgrade";
            this.btnBrowse.Location = new Point(0x178, 0x34);
            this.btnBrowse.Name = "btnBrowse";
            this.btnBrowse.Size = new Size(0x4b, 0x17);
            this.btnBrowse.TabIndex = 2;
            this.btnBrowse.Text = "Browse...";
            this.btnBrowse.UseVisualStyleBackColor = true;
            this.btnBrowse.Click += new EventHandler(this.btnBrowse_Click);
            this.progressBar1.Location = new Point(12, 0x52);
            this.progressBar1.Name = "progressBar1";
            this.progressBar1.Size = new Size(0x1b7, 0x1b);
            this.progressBar1.TabIndex = 3;
            this.btnUpload.Enabled = false;
            this.btnUpload.Location = new Point(0xcb, 0x73);
            this.btnUpload.Name = "btnUpload";
            this.btnUpload.Size = new Size(0x4b, 0x17);
            this.btnUpload.TabIndex = 4;
            this.btnUpload.Text = "Upload";
            this.btnUpload.UseVisualStyleBackColor = true;
            this.btnUpload.Click += new EventHandler(this.btnUpload_Click);
            this.btnClose.DialogResult = DialogResult.OK;
            this.btnClose.Location = new Point(0x121, 0x73);
            this.btnClose.Name = "btnClose";
            this.btnClose.Size = new Size(0x4b, 0x17);
            this.btnClose.TabIndex = 5;
            this.btnClose.Text = "Close";
            this.btnClose.UseVisualStyleBackColor = true;
            this.lblStatus.AutoSize = true;
            this.lblStatus.Font = new Font("Microsoft Sans Serif", 9.75f, FontStyle.Italic | FontStyle.Bold, GraphicsUnit.Point, 0);
            this.lblStatus.Location = new Point(12, 0x3b);
            this.lblStatus.Name = "lblStatus";
            this.lblStatus.Size = new Size(0x9e, 0x10);
            this.lblStatus.TabIndex = 6;
            this.lblStatus.Text = "Upload/Verify/Detach";
            this.openFileDialogDFU.FileName = "filename";
            this.openFileDialogDFU.Filter = "hex Files (*.hex)|*.hex|s19 Files (*.s19)|*.s19";
            this.openFileDialogDFU.InitialDirectory = "Environment.SpecialFolder.MyDocuments";
            this.timer1.Interval = 500;
            this.timer1.Tick += new EventHandler(this.timer1_Tick);
            this.btnVerify.Enabled = false;
            this.btnVerify.Location = new Point(0x75, 0x73);
            this.btnVerify.Name = "btnVerify";
            this.btnVerify.Size = new Size(0x4b, 0x17);
            this.btnVerify.TabIndex = 7;
            this.btnVerify.Text = "Verify";
            this.btnVerify.UseVisualStyleBackColor = true;
            this.btnVerify.Click += new EventHandler(this.btnVerify_Click);
            this.btnCloseLeave.DialogResult = DialogResult.OK;
            this.btnCloseLeave.Location = new Point(0x178, 0x73);
            this.btnCloseLeave.Name = "btnCloseLeave";
            this.btnCloseLeave.Size = new Size(0x4b, 0x17);
            this.btnCloseLeave.TabIndex = 5;
            this.btnCloseLeave.Text = "Leave DFU ";
            this.btnCloseLeave.UseVisualStyleBackColor = true;
            this.btnCloseLeave.Click += new EventHandler(this.btnCloseLeave_Click);
            base.AutoScaleDimensions = new SizeF(6f, 13f);
            base.AutoScaleMode = AutoScaleMode.Font;
            base.CancelButton = this.btnClose;
            base.ClientSize = new Size(0x1d3, 0x9f);
            base.Controls.Add(this.btnVerify);
            base.Controls.Add(this.lblStatus);
            base.Controls.Add(this.btnCloseLeave);
            base.Controls.Add(this.btnClose);
            base.Controls.Add(this.btnUpload);
            base.Controls.Add(this.progressBar1);
            base.Controls.Add(this.btnBrowse);
            base.Controls.Add(this.lblFile);
            base.Controls.Add(this.txtFileToUpload);
            base.FormBorderStyle = FormBorderStyle.FixedDialog;
            base.MaximizeBox = false;
            base.MinimizeBox = false;
            base.Name = "frmUploadFirmware";
            base.ShowIcon = false;
            base.ShowInTaskbar = false;
            this.Text = "Firmware Upgrade";
            base.FormClosing += new FormClosingEventHandler(this.frmUploadFirmware_FormClosing);
            base.ResumeLayout(false);
            base.PerformLayout();
        }

        private void timer1_Tick(object sender, EventArgs e)
        {
            TimeSpan span = DateTime.Now.TimeOfDay - this.TimeOutPhase.TimeOfDay;
            if (span.TotalSeconds > 30.0)
            {
                this.lblStatus.Text = this.lblStatus.Text + " (Time out)";
                this.Status = UpGradeStatus.STATUS_ERROR;
            }
            switch (this.Status)
            {
                case UpGradeStatus.STATUS_NONE:
                    this.Status = UpGradeStatus.STATUS_INIT;
                    return;

                case UpGradeStatus.STATUS_INIT:
                    this.TimeOutPhase = DateTime.Now;
                    this.lblStatus.Text = "Initializing...";
                    this.progressBar1.Value = 0;
                    if (STDFU_EX_Wrapper.STDFU_EX_Init(this.txtFileToUpload.Text) != STDFU_EX_Wrapper.STDFU_EX_Error.STDFU_EX_ERROR_NONE)
                    {
                        this.Status = UpGradeStatus.STATUS_ERROR;
                        return;
                    }
                    this.Status = UpGradeStatus.STATUS_ERASE;
                    return;

                case UpGradeStatus.STATUS_ERASE:
                    this.TimeOutPhase = DateTime.Now;
                    this.lblStatus.Text = "Erasing...";
                    if (STDFU_EX_Wrapper.STDFU_EX_Erase() != STDFU_EX_Wrapper.STDFU_EX_Error.STDFU_EX_ERROR_NONE)
                    {
                        this.Status = UpGradeStatus.STATUS_ERROR;
                        return;
                    }
                    this.Status = UpGradeStatus.STATUS_ERASE_ING;
                    return;

                case UpGradeStatus.STATUS_ERASE_ING:
                {
                    int status = 0;
                    double percent = 0.0;
                    STDFU_EX_Wrapper.STDFU_EX_Error error = STDFU_EX_Wrapper.STDFU_EX_GetStatus(ref status, ref percent);
                    this.progressBar1.Value = (int) percent;
                    if (error == STDFU_EX_Wrapper.STDFU_EX_Error.STDFU_EX_ERROR_NONE)
                    {
                        if (percent != 100.0)
                        {
                            break;
                        }
                        this.Status = UpGradeStatus.STATUS_UPGRADE;
                        return;
                    }
                    this.Status = UpGradeStatus.STATUS_ERROR;
                    return;
                }
                case UpGradeStatus.STATUS_UPGRADE:
                    this.TimeOutPhase = DateTime.Now;
                    this.lblStatus.Text = "Flashing...";
                    if (STDFU_EX_Wrapper.STDFU_EX_FlashDevice() != STDFU_EX_Wrapper.STDFU_EX_Error.STDFU_EX_ERROR_NONE)
                    {
                        this.Status = UpGradeStatus.STATUS_ERROR;
                        return;
                    }
                    this.Status = UpGradeStatus.STATUS_UPGRADE_ING;
                    return;

                case UpGradeStatus.STATUS_UPGRADE_ING:
                {
                    int num3 = 0;
                    double num4 = 0.0;
                    STDFU_EX_Wrapper.STDFU_EX_Error error2 = STDFU_EX_Wrapper.STDFU_EX_GetStatus(ref num3, ref num4);
                    this.progressBar1.Value = (int) num4;
                    if (error2 == STDFU_EX_Wrapper.STDFU_EX_Error.STDFU_EX_ERROR_NONE)
                    {
                        if (num4 != 100.0)
                        {
                            break;
                        }
                        this.Status = UpGradeStatus.STATUS_VERIFY;
                        return;
                    }
                    this.Status = UpGradeStatus.STATUS_ERROR;
                    return;
                }
                case UpGradeStatus.STATUS_VERIFY:
                    this.TimeOutPhase = DateTime.Now;
                    this.lblStatus.Text = "Verifing...";
                    if (STDFU_EX_Wrapper.STDFU_EX_Verify() != STDFU_EX_Wrapper.STDFU_EX_Error.STDFU_EX_ERROR_NONE)
                    {
                        this.Status = UpGradeStatus.STATUS_ERROR;
                        return;
                    }
                    this.Status = UpGradeStatus.STATUS_VERIFY_ING;
                    return;

                case UpGradeStatus.STATUS_VERIFY_ING:
                {
                    int num5 = 0;
                    double num6 = 0.0;
                    STDFU_EX_Wrapper.STDFU_EX_Error error3 = STDFU_EX_Wrapper.STDFU_EX_GetStatus(ref num5, ref num6);
                    this.progressBar1.Value = (int) num6;
                    if (error3 == STDFU_EX_Wrapper.STDFU_EX_Error.STDFU_EX_ERROR_NONE)
                    {
                        if (num6 != 100.0)
                        {
                            break;
                        }
                        this.Status = UpGradeStatus.STATUS_RUN_APP;
                        return;
                    }
                    this.Status = UpGradeStatus.STATUS_ERROR;
                    return;
                }
                case UpGradeStatus.STATUS_RUN_APP:
                    this.TimeOutPhase = DateTime.Now;
                    this.lblStatus.Text = "Detaching...";
                    if (STDFU_EX_Wrapper.STDFU_EX_RunApplication() != STDFU_EX_Wrapper.STDFU_EX_Error.STDFU_EX_ERROR_NONE)
                    {
                        this.Status = UpGradeStatus.STATUS_ERROR;
                        return;
                    }
                    this.Status = UpGradeStatus.STATUS_RUN_APP_ING;
                    return;

                case UpGradeStatus.STATUS_RUN_APP_ING:
                {
                    int num7 = 0;
                    double num8 = 0.0;
                    STDFU_EX_Wrapper.STDFU_EX_Error error4 = STDFU_EX_Wrapper.STDFU_EX_GetStatus(ref num7, ref num8);
                    this.progressBar1.Value = (int) num8;
                    if (error4 == STDFU_EX_Wrapper.STDFU_EX_Error.STDFU_EX_ERROR_NONE)
                    {
                        if (num8 != 100.0)
                        {
                            break;
                        }
                        this.Status = UpGradeStatus.STATUS_COMPLETED;
                        return;
                    }
                    this.Status = UpGradeStatus.STATUS_ERROR;
                    return;
                }
                case UpGradeStatus.STATUS_COMPLETED:
                {
                    this.timer1.Enabled = false;
                    this.btnBrowse.Enabled = true;
                    this.btnClose.Enabled = true;
                    this.btnCloseLeave.Enabled = true;
                    this.btnUpload.Enabled = true;
                    this.btnVerify.Enabled = true;
                    STDFU_EX_Wrapper.STDFU_EX_Release();
                    this.lblStatus.Text = "Done!";
                    string strMessage = "Firmware upgrade completed successfully";
                    string caption = "Firmware upgrade";
                    if (this.OnlyVerify)
                    {
                        strMessage = "Firmware verify completed successfully";
                        caption = "Firmware verify";
                    }
                    strMessage = strMessage + " \nDevice is in application mode.";
                    if (this.OnMessageToLogSettings != null)
                    {
                        this.OnMessageToLogSettings(strMessage);
                    }
                    MessageBox.Show(strMessage, caption, MessageBoxButtons.OK, MessageBoxIcon.Exclamation);
                    base.Close();
                    return;
                }
                case UpGradeStatus.STATUS_ERROR:
                    this.lblStatus.Text = "Error on " + this.lblStatus.Text;
                    if (STDFU_EX_Wrapper.STDFU_EX_Release() == STDFU_EX_Wrapper.STDFU_EX_Error.STDFU_EX_ERROR_NONE)
                    {
                        this.timer1.Enabled = false;
                        this.btnBrowse.Enabled = true;
                        this.btnClose.Enabled = true;
                        this.btnClose.Enabled = true;
                        this.btnUpload.Enabled = true;
                        this.btnVerify.Enabled = true;
                        this.Status = UpGradeStatus.STATUS_NONE;
                        if (this.OnMessageToLogSettings != null)
                        {
                            this.OnMessageToLogSettings(this.lblStatus.Text);
                        }
                    }
                    break;

                default:
                    return;
            }
        }

        public enum UpGradeStatus
        {
            STATUS_NONE,
            STATUS_INIT,
            STATUS_ERASE,
            STATUS_ERASE_ING,
            STATUS_UPGRADE,
            STATUS_UPGRADE_ING,
            STATUS_VERIFY,
            STATUS_VERIFY_ING,
            STATUS_RUN_APP,
            STATUS_RUN_APP_ING,
            STATUS_COMPLETED,
            STATUS_ERROR
        }
    }
}

