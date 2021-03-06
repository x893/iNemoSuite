﻿namespace KS
{
    using System;
    using System.ComponentModel;
    using System.Diagnostics;
    using System.Drawing;
    using System.Windows.Forms;

    public class KSSelector : Form
    {
        private Button buttonCancel;
        private Button buttonOk;
        private ComboBox comboBoxActiveSocket;
        private ComboBox comboBoxKitCode;
        private IContainer components;
        private bool configurationChanged;
        private KSDataProvider dataProvider;
        private KSNoneSocketEditor dcpNoneSocketEditor1;
        private KSSerialSocketEditor dcpSerialSocketEditor1;
        private KSTcpIpSocketEditor dcpTcpIpSocketEditor1;
        private KSUsbSocketEditor dcpUsbSocketEditor1;
        private ErrorProvider errorProvider1;
        private GroupBox groupBox2;
        private GroupBox groupBox3;
        private Label label1;
        private Label label2;
        private Label label3;
        private Label label4;
        private Label labelKitDescription;
        private Label labelSocketType;
        private LinkLabel linkLabelUrl;
        private PictureBox pictureBoxKitPhoto;
        private PictureBox pictureBoxSt;
        private KSKit selectedKit;
        private bool selectionChanged;
        private KSKit workingKit;

        public KSSelector()
        {
            dataProvider = new KSDataProvider();
            workingKit = null;
            selectedKit = null;
            selectionChanged = false;
            configurationChanged = false;
            InitializeComponent();
            Text = Messages.KS_CAPTION_SELECTOR;
            dcpNoneSocketEditor1.OnParamChanged = (KSNoneSocketEditor.ParamChanged) Delegate.Combine(dcpNoneSocketEditor1.OnParamChanged, new KSNoneSocketEditor.ParamChanged(OnParamChanged));
            dcpSerialSocketEditor1.OnParamChanged = (KSSerialSocketEditor.ParamChanged) Delegate.Combine(dcpSerialSocketEditor1.OnParamChanged, new KSSerialSocketEditor.ParamChanged(OnParamChanged));
            dcpTcpIpSocketEditor1.OnParamChanged = (KSTcpIpSocketEditor.ParamChanged) Delegate.Combine(dcpTcpIpSocketEditor1.OnParamChanged, new KSTcpIpSocketEditor.ParamChanged(OnParamChanged));
            dcpUsbSocketEditor1.OnParamChanged = (KSUsbSocketEditor.ParamChanged) Delegate.Combine(dcpUsbSocketEditor1.OnParamChanged, new KSUsbSocketEditor.ParamChanged(OnParamChanged));
            buttonOk.Enabled = false;
        }

        public KSSelector(string dbkFile) : this()
        {
            Configure(dbkFile, null);
        }

        public KSSelector(string dbkFile, KSKit selKit) : this()
        {
            Configure(dbkFile, selKit);
        }

        private void buttonOk_Click(object sender, EventArgs e)
        {
            try
            {
                selectionChanged = true;
                configurationChanged = true;
                if (selectedKit != null)
                {
                    selectionChanged = workingKit.Code != selectedKit.Code;
                    configurationChanged = workingKit.Socket.Param != selectedKit.Socket.Param;
                }
                selectedKit = workingKit;
            }
            catch (Exception)
            {
                selectionChanged = false;
                configurationChanged = false;
            }
        }

        private void comboBoxActiveSocket_SelectedIndexChanged(object sender, EventArgs e)
        {
            workingKit.SelectedSocket = (KSSocketAvailable) comboBoxActiveSocket.SelectedItem;
            dcpNoneSocketEditor1.Visible = false;
            dcpSerialSocketEditor1.Visible = false;
            dcpTcpIpSocketEditor1.Visible = false;
            dcpUsbSocketEditor1.Visible = false;
            switch (workingKit.Socket.Type)
            {
                case KSSocketType.None:
                    labelSocketType.Text = workingKit.Socket.ToString();
                    dcpNoneSocketEditor1.Param = workingKit.Socket.Param;
                    dcpNoneSocketEditor1.Visible = true;
                    return;

                case KSSocketType.Serial:
                    labelSocketType.Text = workingKit.Socket.ToString();
                    dcpSerialSocketEditor1.Param = workingKit.Socket.Param;
                    dcpSerialSocketEditor1.Visible = true;
                    return;

                case KSSocketType.TcpIp:
                    labelSocketType.Text = workingKit.Socket.ToString();
                    dcpTcpIpSocketEditor1.Param = workingKit.Socket.Param;
                    dcpTcpIpSocketEditor1.Visible = true;
                    return;

                case KSSocketType.Usb:
                    labelSocketType.Text = workingKit.Socket.ToString();
                    dcpUsbSocketEditor1.Param = workingKit.Socket.Param;
                    dcpUsbSocketEditor1.Visible = true;
                    return;
            }
        }

        private void comboBoxKitCode_SelectedIndexChanged(object sender, EventArgs e)
        {
            workingKit = (KSKit) comboBoxKitCode.SelectedItem;
            LookUpKit(workingKit);
        }

        public void Configure(string dbkFile, KSKit selKit)
        {
            if (dataProvider.Load(dbkFile))
            {
                selectedKit = selKit;
            }
            buttonOk.Enabled = !dataProvider.IsEmpty;
        }

        protected override void Dispose(bool disposing)
        {
            if (disposing && (components != null))
            {
                components.Dispose();
            }
            base.Dispose(disposing);
        }

        private void FillComboKitCode(KSKit selKit)
        {
            KSKit item = null;
            try
            {
                comboBoxKitCode.Items.Clear();
                for (item = dataProvider.MoveTo(KSDataProvider.CursorStep.CursorFirst); item != null; item = dataProvider.MoveTo(KSDataProvider.CursorStep.CursorNext))
                {
                    if ((selKit != null) && (item.Code == selKit.Code))
                    {
                        item.DirectSocket.Param = selKit.DirectSocket.Param;
                        item.BridgedSocket.Param = selKit.BridgedSocket.Param;
                        item.SelectedSocket = selectedKit.SelectedSocket;
                    }
                    comboBoxKitCode.Items.Add(item);
                }
                comboBoxKitCode.Enabled = !dataProvider.IsEmpty;
                if (comboBoxKitCode.Items.Contains(selKit))
                {
                    comboBoxKitCode.SelectedItem = selKit;
                }
                else
                {
                    comboBoxKitCode.SelectedIndex = comboBoxKitCode.Items.Count - 1;
                }
            }
            catch (Exception)
            {
                comboBoxKitCode.Enabled = false;
            }
        }

        private void InitializeComponent()
        {
            components = new Container();
            ComponentResourceManager resources = new ComponentResourceManager(typeof(KSSelector));
            pictureBoxKitPhoto = new PictureBox();
            comboBoxKitCode = new ComboBox();
            linkLabelUrl = new LinkLabel();
            label2 = new Label();
            label1 = new Label();
            labelKitDescription = new Label();
            groupBox2 = new GroupBox();
            label4 = new Label();
            groupBox3 = new GroupBox();
            dcpNoneSocketEditor1 = new KSNoneSocketEditor();
            dcpTcpIpSocketEditor1 = new KSTcpIpSocketEditor();
            dcpSerialSocketEditor1 = new KSSerialSocketEditor();
            dcpUsbSocketEditor1 = new KSUsbSocketEditor();
            labelSocketType = new Label();
            comboBoxActiveSocket = new ComboBox();
            label3 = new Label();
            buttonOk = new Button();
            buttonCancel = new Button();
            pictureBoxSt = new PictureBox();
            errorProvider1 = new ErrorProvider(components);
            ((ISupportInitialize) pictureBoxKitPhoto).BeginInit();
            groupBox2.SuspendLayout();
            groupBox3.SuspendLayout();
            ((ISupportInitialize) pictureBoxSt).BeginInit();
            ((ISupportInitialize) errorProvider1).BeginInit();
            base.SuspendLayout();
            pictureBoxKitPhoto.BorderStyle = BorderStyle.FixedSingle;
            pictureBoxKitPhoto.Location = new Point(12, 0x7a);
            pictureBoxKitPhoto.Margin = new Padding(0);
            pictureBoxKitPhoto.Name = "pictureBoxKitPhoto";
            pictureBoxKitPhoto.Size = new Size(160, 120);
            pictureBoxKitPhoto.TabIndex = 4;
            pictureBoxKitPhoto.TabStop = false;
            comboBoxKitCode.DropDownStyle = ComboBoxStyle.DropDownList;
            comboBoxKitCode.FormattingEnabled = true;
            comboBoxKitCode.Location = new Point(12, 0x19);
            comboBoxKitCode.Name = "comboBoxKitCode";
            comboBoxKitCode.Size = new Size(0xb9, 0x15);
            comboBoxKitCode.TabIndex = 1;
            comboBoxKitCode.SelectedIndexChanged += new EventHandler(comboBoxKitCode_SelectedIndexChanged);
            linkLabelUrl.AutoSize = true;
            linkLabelUrl.Location = new Point(12, 0xf9);
            linkLabelUrl.Name = "linkLabelUrl";
            linkLabelUrl.Size = new Size(0x48, 13);
            linkLabelUrl.TabIndex = 4;
            linkLabelUrl.TabStop = true;
            linkLabelUrl.Text = "Support Page";
            linkLabelUrl.Visible = false;
            linkLabelUrl.LinkClicked += new LinkLabelLinkClickedEventHandler(linkLabelUrl_LinkClicked);
            label2.AutoSize = true;
            label2.Location = new Point(12, 0x3b);
            label2.Name = "label2";
            label2.Size = new Size(0x42, 13);
            label2.TabIndex = 2;
            label2.Text = "Description :";
            label1.AutoSize = true;
            label1.Location = new Point(12, 10);
            label1.Name = "label1";
            label1.Size = new Size(0x26, 13);
            label1.TabIndex = 0;
            label1.Text = "Code :";
            labelKitDescription.Anchor = AnchorStyles.Right | AnchorStyles.Left | AnchorStyles.Top;
            labelKitDescription.BackColor = Color.White;
            labelKitDescription.BorderStyle = BorderStyle.FixedSingle;
            labelKitDescription.Location = new Point(12, 0x4b);
            labelKitDescription.Margin = new Padding(3);
            labelKitDescription.Name = "labelKitDescription";
            labelKitDescription.Size = new Size(0x278, 20);
            labelKitDescription.TabIndex = 3;
            labelKitDescription.TextAlign = ContentAlignment.MiddleLeft;
            groupBox2.Anchor = AnchorStyles.Right | AnchorStyles.Left | AnchorStyles.Bottom | AnchorStyles.Top;
            groupBox2.Controls.Add(label4);
            groupBox2.Controls.Add(groupBox3);
            groupBox2.Controls.Add(labelSocketType);
            groupBox2.Controls.Add(comboBoxActiveSocket);
            groupBox2.Controls.Add(label3);
            groupBox2.Location = new Point(0xb5, 0x70);
            groupBox2.Name = "groupBox2";
            groupBox2.Size = new Size(0x1cf, 0x87);
            groupBox2.TabIndex = 5;
            groupBox2.TabStop = false;
            groupBox2.Text = "Socket Configuration";
            label4.AutoSize = true;
            label4.Location = new Point(0x15, 0x1b);
            label4.Name = "label4";
            label4.Size = new Size(0x43, 13);
            label4.TabIndex = 4;
            label4.Text = "Connection :";
            groupBox3.Controls.Add(dcpNoneSocketEditor1);
            groupBox3.Controls.Add(dcpTcpIpSocketEditor1);
            groupBox3.Controls.Add(dcpSerialSocketEditor1);
            groupBox3.Controls.Add(dcpUsbSocketEditor1);
            groupBox3.Location = new Point(0x10, 0x35);
            groupBox3.Name = "groupBox3";
            groupBox3.Size = new Size(440, 0x41);
            groupBox3.TabIndex = 2;
            groupBox3.TabStop = false;
            groupBox3.Text = "Param";
            dcpNoneSocketEditor1.Location = new Point(0x65, 13);
            dcpNoneSocketEditor1.Name = "dcpNoneSocketEditor1";
            dcpNoneSocketEditor1.Param = "";
            dcpNoneSocketEditor1.Size = new Size(260, 0x2d);
            dcpNoneSocketEditor1.TabIndex = 3;
            dcpTcpIpSocketEditor1.Location = new Point(0x65, 13);
            dcpTcpIpSocketEditor1.Name = "dcpTcpIpSocketEditor1";
            dcpTcpIpSocketEditor1.Param = "0.0.0.0,0";
            dcpTcpIpSocketEditor1.Size = new Size(260, 0x2d);
            dcpTcpIpSocketEditor1.TabIndex = 1;
            dcpTcpIpSocketEditor1.Visible = false;
            dcpSerialSocketEditor1.Location = new Point(0x65, 13);
            dcpSerialSocketEditor1.Name = "dcpSerialSocketEditor1";
            dcpSerialSocketEditor1.Param = "COM92";
            dcpSerialSocketEditor1.Size = new Size(260, 0x2d);
            dcpSerialSocketEditor1.TabIndex = 0;
            dcpSerialSocketEditor1.Visible = false;
            dcpUsbSocketEditor1.Location = new Point(0x65, 13);
            dcpUsbSocketEditor1.Name = "dcpUsbSocketEditor1";
            dcpUsbSocketEditor1.Param = null;
            dcpUsbSocketEditor1.Size = new Size(260, 0x2d);
            dcpUsbSocketEditor1.TabIndex = 2;
            dcpUsbSocketEditor1.Visible = false;
            labelSocketType.BackColor = Color.White;
            labelSocketType.BorderStyle = BorderStyle.FixedSingle;
            labelSocketType.Location = new Point(0x137, 0x16);
            labelSocketType.Margin = new Padding(3);
            labelSocketType.Name = "labelSocketType";
            labelSocketType.Size = new Size(0x90, 20);
            labelSocketType.TabIndex = 1;
            labelSocketType.TextAlign = ContentAlignment.MiddleLeft;
            comboBoxActiveSocket.DropDownStyle = ComboBoxStyle.DropDownList;
            comboBoxActiveSocket.FormattingEnabled = true;
            comboBoxActiveSocket.Location = new Point(0x5e, 0x16);
            comboBoxActiveSocket.Name = "comboBoxActiveSocket";
            comboBoxActiveSocket.Size = new Size(0x84, 0x15);
            comboBoxActiveSocket.TabIndex = 3;
            comboBoxActiveSocket.SelectedIndexChanged += new EventHandler(comboBoxActiveSocket_SelectedIndexChanged);
            label3.AutoSize = true;
            label3.Location = new Point(0x10c, 0x1a);
            label3.Name = "label3";
            label3.Size = new Size(0x25, 13);
            label3.TabIndex = 0;
            label3.Text = "Type :";
            buttonOk.Anchor = AnchorStyles.Right | AnchorStyles.Bottom;
            buttonOk.DialogResult = System.Windows.Forms.DialogResult.OK;
            buttonOk.Location = new Point(0x1e8, 0x105);
            buttonOk.Name = "buttonOk";
            buttonOk.Size = new Size(0x4b, 0x17);
            buttonOk.TabIndex = 6;
            buttonOk.Text = "Ok";
            buttonOk.UseVisualStyleBackColor = true;
            buttonOk.Click += new EventHandler(buttonOk_Click);
            buttonCancel.Anchor = AnchorStyles.Right | AnchorStyles.Bottom;
            buttonCancel.DialogResult = System.Windows.Forms.DialogResult.Cancel;
            buttonCancel.Location = new Point(0x239, 0x105);
            buttonCancel.Name = "buttonCancel";
            buttonCancel.Size = new Size(0x4b, 0x17);
            buttonCancel.TabIndex = 7;
            buttonCancel.Text = "Cancel";
            buttonCancel.UseVisualStyleBackColor = true;
            pictureBoxSt.Anchor = AnchorStyles.Right | AnchorStyles.Top;
            pictureBoxSt.BorderStyle = BorderStyle.FixedSingle;
            pictureBoxSt.Cursor = Cursors.Hand;
            pictureBoxSt.Image = (Image) resources.GetObject("pictureBoxSt.Image");
            pictureBoxSt.Location = new Point(0x240, 10);
            pictureBoxSt.Name = "pictureBoxSt";
            pictureBoxSt.Size = new Size(0x44, 0x33);
            pictureBoxSt.SizeMode = PictureBoxSizeMode.StretchImage;
            pictureBoxSt.TabIndex = 9;
            pictureBoxSt.TabStop = false;
            pictureBoxSt.Click += new EventHandler(pictureBoxSt_Click);
            errorProvider1.ContainerControl = this;
            base.AutoScaleDimensions = new SizeF(6f, 13f);
            base.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            base.ClientSize = new Size(0x290, 0x128);
            base.Controls.Add(pictureBoxSt);
            base.Controls.Add(linkLabelUrl);
            base.Controls.Add(buttonCancel);
            base.Controls.Add(label2);
            base.Controls.Add(buttonOk);
            base.Controls.Add(label1);
            base.Controls.Add(groupBox2);
            base.Controls.Add(comboBoxKitCode);
            base.Controls.Add(labelKitDescription);
            base.Controls.Add(pictureBoxKitPhoto);
            base.FormBorderStyle = System.Windows.Forms.FormBorderStyle.FixedDialog;
            base.Icon = (Icon) resources.GetObject("$Icon");
            base.MaximizeBox = false;
            base.MinimizeBox = false;
            base.Name = "KSSelector";
            base.StartPosition = FormStartPosition.CenterParent;
            Text = "Kit Selector";
            base.Load += new EventHandler(KSSelector_Load);
            ((ISupportInitialize) pictureBoxKitPhoto).EndInit();
            groupBox2.ResumeLayout(false);
            groupBox2.PerformLayout();
            groupBox3.ResumeLayout(false);
            ((ISupportInitialize) pictureBoxSt).EndInit();
            ((ISupportInitialize) errorProvider1).EndInit();
            base.ResumeLayout(false);
            base.PerformLayout();
        }

        private void KSSelector_Load(object sender, EventArgs e)
        {
            selectionChanged = false;
            configurationChanged = false;
            workingKit = new KSKit(selectedKit);
            FillComboKitCode(workingKit);
        }

        private void linkLabelUrl_LinkClicked(object sender, LinkLabelLinkClickedEventArgs e)
        {
            try
            {
                Process.Start(workingKit.Url);
                errorProvider1.SetError(linkLabelUrl, "");
            }
            catch (Exception)
            {
                errorProvider1.SetError(linkLabelUrl, Messages.KS_ERROR_SUPPORT_URL);
            }
        }

        private void LookUpKit(KSKit kit)
        {
            errorProvider1.SetError(linkLabelUrl, "");
            linkLabelUrl.Visible = false;
            pictureBoxKitPhoto.Image = workingKit.Photo;
            labelKitDescription.Text = workingKit.Description;
            linkLabelUrl.Visible = workingKit.Url != "";
            comboBoxActiveSocket.Items.Clear();
            comboBoxActiveSocket.Items.Add(KSSocketAvailable.Direct);
            if (kit.BridgedSocket.Protocol.Length > 0)
            {
                comboBoxActiveSocket.Items.Add(KSSocketAvailable.Bridged);
            }
            comboBoxActiveSocket.SelectedItem = workingKit.SelectedSocket;
        }

        private void OnParamChanged(string param)
        {
            workingKit.Socket.Param = param;
        }

        private void pictureBoxSt_Click(object sender, EventArgs e)
        {
            Process.Start(Messages.KS_URL_ST);
        }

        public bool ConfigurationChanged
        {
            get
            {
                return configurationChanged;
            }
        }

        public KSKit SelectedKit
        {
            get
            {
                return selectedKit;
            }
        }

        public bool SelectionChanged
        {
            get
            {
                return selectionChanged;
            }
        }
    }
}

