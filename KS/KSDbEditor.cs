﻿namespace KS
{
    using System;
    using System.ComponentModel;
    using System.Drawing;
    using System.Windows.Forms;

    public class KSDbEditor : Form
    {
        private Button buttonCalcUrl;
        private Button buttonLoadPhoto;
        private ComboBox comboBoxDirectSocket;
        private IContainer components;
        private GroupBox groupBox1;
        private GroupBox groupBox2;
        private GroupBox groupBox3;
        private GroupBox groupBox4;
        private Label label1;
        private Label label2;
        private Label label3;
        private Label label4;
        private Label label5;
        private Label label6;
        private Label label7;
        private Label label8;
        private OpenFileDialog openFileDialog1;
        private PictureBox pictureBoxPhoto;
        private SaveFileDialog saveFileDialog1;
        private TextBox textBoxBridgedProtocol;
        private TextBox textBoxCode;
        private TextBox textBoxDbFilePath;
        private TextBox textBoxDescription;
        private TextBox textBoxDirectProtocol;
        private TextBox textBoxUrl;
        private Timer timer1;
        private ToolStrip toolStrip1;
        private ToolStripButton toolStripButtonAdd;
        private ToolStripButton toolStripButtonCancel;
        private ToolStripButton toolStripButtonConfirm;
        private ToolStripButton toolStripButtonFirst;
        private ToolStripButton toolStripButtonLast;
        private ToolStripButton toolStripButtonLoad;
        private ToolStripButton toolStripButtonModify;
        private ToolStripButton toolStripButtonNew;
        private ToolStripButton toolStripButtonNext;
        private ToolStripButton toolStripButtonPrev;
        private ToolStripButton toolStripButtonRemove;
        private ToolStripButton toolStripButtonSave;
        private ToolStripButton toolStripButtonSaveAs;
        private ToolStripSeparator toolStripSeparator1;
        private ToolStripSeparator toolStripSeparator2;
        private ToolStripSeparator toolStripSeparator3;

		private KSDataProvider kitDataProvider = new KSDataProvider();
		private EditorState editorState = EditorState.Viewer;

        public KSDbEditor()
        {
            InitializeComponent();

            timer1.Enabled = false;
            Text = Messages.KS_CAPTION_EDITOR;
            textBoxDbFilePath.Text = "";
            comboBoxDirectSocket.Items.Clear();
            comboBoxDirectSocket.Items.Insert(0, "None");
            comboBoxDirectSocket.Items.Insert(1, "Serial");
            comboBoxDirectSocket.Items.Insert(2, "TCP/IP");
            comboBoxDirectSocket.Items.Insert(3, "USB");
            comboBoxDirectSocket.SelectedIndex = 0;
            ClearForm();
        }

        public KSDbEditor(string DbkFile) : this()
        {
            textBoxDbFilePath.Text = DbkFile;
            timer1.Enabled = true;
        }

        private void buttonCalcUrl_Click(object sender, EventArgs e)
        {
            textBoxUrl.Text = Messages.KS_URL_KIT_ROOT + textBoxCode.Text.ToLower() + ".htm";
        }

        private void buttonLoadPhoto_Click(object sender, EventArgs e)
        {
            openFileDialog1.FileName = "";
            openFileDialog1.Filter = Messages.KS_FILTER_IMAGES;
            if (openFileDialog1.ShowDialog() == DialogResult.OK)
            {
                pictureBoxPhoto.Image = Image.FromFile(openFileDialog1.FileName);
            }
        }

        private void ClearForm()
        {
            textBoxCode.Text = "";
            textBoxDescription.Text = "";
            pictureBoxPhoto.Image = null;
            textBoxUrl.Text = "";
            comboBoxDirectSocket.SelectedIndex = 0;
            textBoxDirectProtocol.Text = "";
            textBoxBridgedProtocol.Text = "";
        }

        private void dcpKitDbEditor_FormClosing(object sender, FormClosingEventArgs e)
        {
            if (kitDataProvider.IsModified && (MessageBox.Show(Messages.KS_QUESTION_SAVE, Messages.KS_CAPTION_EDITOR, MessageBoxButtons.YesNo, MessageBoxIcon.Question) == DialogResult.Yes))
            {
                toolStripButtonSaveAs_Click(null, null);
            }
        }

        private void dcpKitDbEditor_Load(object sender, EventArgs e)
        {
            UpdateControls();
        }

        protected override void Dispose(bool disposing)
        {
            if (disposing && (components != null))
            {
                components.Dispose();
            }
            base.Dispose(disposing);
        }

        private void InitializeComponent()
        {
            this.components = new Container();
            ComponentResourceManager resources = new ComponentResourceManager(typeof(KSDbEditor));
            this.label1 = new Label();
            this.textBoxDbFilePath = new TextBox();
            this.openFileDialog1 = new OpenFileDialog();
            this.saveFileDialog1 = new SaveFileDialog();
            this.toolStrip1 = new ToolStrip();
            this.toolStripButtonNew = new ToolStripButton();
            this.toolStripSeparator2 = new ToolStripSeparator();
            this.toolStripButtonLoad = new ToolStripButton();
            this.toolStripButtonSave = new ToolStripButton();
            this.toolStripButtonSaveAs = new ToolStripButton();
            this.toolStripSeparator1 = new ToolStripSeparator();
            this.toolStripButtonFirst = new ToolStripButton();
            this.toolStripButtonPrev = new ToolStripButton();
            this.toolStripButtonNext = new ToolStripButton();
            this.toolStripButtonLast = new ToolStripButton();
            this.toolStripSeparator3 = new ToolStripSeparator();
            this.toolStripButtonAdd = new ToolStripButton();
            this.toolStripButtonRemove = new ToolStripButton();
            this.toolStripButtonModify = new ToolStripButton();
            this.toolStripButtonConfirm = new ToolStripButton();
            this.toolStripButtonCancel = new ToolStripButton();
            this.groupBox1 = new GroupBox();
            this.label2 = new Label();
            this.label3 = new Label();
            this.label4 = new Label();
            this.textBoxCode = new TextBox();
            this.textBoxDescription = new TextBox();
            this.pictureBoxPhoto = new PictureBox();
            this.groupBox2 = new GroupBox();
            this.buttonCalcUrl = new Button();
            this.textBoxUrl = new TextBox();
            this.label7 = new Label();
            this.buttonLoadPhoto = new Button();
            this.timer1 = new Timer(this.components);
            this.groupBox3 = new GroupBox();
            this.textBoxDirectProtocol = new TextBox();
            this.label6 = new Label();
            this.comboBoxDirectSocket = new ComboBox();
            this.label5 = new Label();
            this.groupBox4 = new GroupBox();
            this.textBoxBridgedProtocol = new TextBox();
            this.label8 = new Label();
            this.toolStrip1.SuspendLayout();
            this.groupBox1.SuspendLayout();
            ((ISupportInitialize) this.pictureBoxPhoto).BeginInit();
            this.groupBox2.SuspendLayout();
            this.groupBox3.SuspendLayout();
            this.groupBox4.SuspendLayout();
            base.SuspendLayout();
            this.label1.AutoSize = true;
            this.label1.Location = new Point(8, 0x18);
            this.label1.Name = "label1";
            this.label1.Size = new Size(50, 13);
            this.label1.TabIndex = 0;
            this.label1.Text = "File path:";
            this.textBoxDbFilePath.Enabled = false;
            this.textBoxDbFilePath.Location = new Point(80, 0x15);
            this.textBoxDbFilePath.Name = "textBoxDbFilePath";
            this.textBoxDbFilePath.Size = new Size(0x232, 20);
            this.textBoxDbFilePath.TabIndex = 1;
            this.openFileDialog1.DefaultExt = "dbk";
            this.saveFileDialog1.DefaultExt = "dbk";
            this.toolStrip1.Items.AddRange(new ToolStripItem[] { this.toolStripButtonNew, this.toolStripSeparator2, this.toolStripButtonLoad, this.toolStripButtonSave, this.toolStripButtonSaveAs, this.toolStripSeparator1, this.toolStripButtonFirst, this.toolStripButtonPrev, this.toolStripButtonNext, this.toolStripButtonLast, this.toolStripSeparator3, this.toolStripButtonAdd, this.toolStripButtonRemove, this.toolStripButtonModify, this.toolStripButtonConfirm, this.toolStripButtonCancel });
            this.toolStrip1.Location = new Point(0, 0);
            this.toolStrip1.Name = "toolStrip1";
            this.toolStrip1.Size = new Size(0x2a1, 0x25);
            this.toolStrip1.TabIndex = 2;
            this.toolStrip1.Text = "toolStrip1";
            this.toolStripButtonNew.AutoSize = false;
            this.toolStripButtonNew.DisplayStyle = ToolStripItemDisplayStyle.Image;
            this.toolStripButtonNew.Image = (Image) resources.GetObject("toolStripButtonNew.Image");
            this.toolStripButtonNew.ImageScaling = ToolStripItemImageScaling.None;
            this.toolStripButtonNew.ImageTransparentColor = Color.Transparent;
            this.toolStripButtonNew.Margin = new Padding(0);
            this.toolStripButtonNew.Name = "toolStripButtonNew";
            this.toolStripButtonNew.Size = new Size(0x22, 0x22);
            this.toolStripButtonNew.Text = "New";
            this.toolStripButtonNew.TextImageRelation = TextImageRelation.Overlay;
            this.toolStripButtonNew.Click += new EventHandler(this.toolStripButtonNew_Click);
            this.toolStripSeparator2.Name = "toolStripSeparator2";
            this.toolStripSeparator2.Size = new Size(6, 0x25);
            this.toolStripButtonLoad.AutoSize = false;
            this.toolStripButtonLoad.DisplayStyle = ToolStripItemDisplayStyle.Image;
            this.toolStripButtonLoad.Image = (Image) resources.GetObject("toolStripButtonLoad.Image");
            this.toolStripButtonLoad.ImageScaling = ToolStripItemImageScaling.None;
            this.toolStripButtonLoad.ImageTransparentColor = Color.Transparent;
            this.toolStripButtonLoad.Margin = new Padding(0);
            this.toolStripButtonLoad.Name = "toolStripButtonLoad";
            this.toolStripButtonLoad.Size = new Size(0x22, 0x22);
            this.toolStripButtonLoad.Text = "Load";
            this.toolStripButtonLoad.Click += new EventHandler(this.toolStripButtonLoad_Click);
            this.toolStripButtonSave.AutoSize = false;
            this.toolStripButtonSave.DisplayStyle = ToolStripItemDisplayStyle.Image;
            this.toolStripButtonSave.Image = (Image) resources.GetObject("toolStripButtonSave.Image");
            this.toolStripButtonSave.ImageScaling = ToolStripItemImageScaling.None;
            this.toolStripButtonSave.ImageTransparentColor = Color.Transparent;
            this.toolStripButtonSave.Margin = new Padding(0);
            this.toolStripButtonSave.Name = "toolStripButtonSave";
            this.toolStripButtonSave.Size = new Size(0x22, 0x22);
            this.toolStripButtonSave.Text = "Save";
            this.toolStripButtonSave.Click += new EventHandler(this.toolStripButtonSave_Click);
            this.toolStripButtonSaveAs.AutoSize = false;
            this.toolStripButtonSaveAs.DisplayStyle = ToolStripItemDisplayStyle.Image;
            this.toolStripButtonSaveAs.Image = (Image) resources.GetObject("toolStripButtonSaveAs.Image");
            this.toolStripButtonSaveAs.ImageScaling = ToolStripItemImageScaling.None;
            this.toolStripButtonSaveAs.ImageTransparentColor = Color.Transparent;
            this.toolStripButtonSaveAs.Margin = new Padding(0);
            this.toolStripButtonSaveAs.Name = "toolStripButtonSaveAs";
            this.toolStripButtonSaveAs.Size = new Size(0x22, 0x22);
            this.toolStripButtonSaveAs.Text = "Save As";
            this.toolStripButtonSaveAs.Click += new EventHandler(this.toolStripButtonSaveAs_Click);
            this.toolStripSeparator1.Name = "toolStripSeparator1";
            this.toolStripSeparator1.Size = new Size(6, 0x25);
            this.toolStripButtonFirst.AutoSize = false;
            this.toolStripButtonFirst.DisplayStyle = ToolStripItemDisplayStyle.Image;
            this.toolStripButtonFirst.Image = (Image) resources.GetObject("toolStripButtonFirst.Image");
            this.toolStripButtonFirst.ImageScaling = ToolStripItemImageScaling.None;
            this.toolStripButtonFirst.ImageTransparentColor = Color.Transparent;
            this.toolStripButtonFirst.Margin = new Padding(0);
            this.toolStripButtonFirst.Name = "toolStripButtonFirst";
            this.toolStripButtonFirst.Size = new Size(0x22, 0x22);
            this.toolStripButtonFirst.Text = "First";
            this.toolStripButtonFirst.Click += new EventHandler(this.toolStripButtonFirst_Click);
            this.toolStripButtonPrev.AutoSize = false;
            this.toolStripButtonPrev.DisplayStyle = ToolStripItemDisplayStyle.Image;
            this.toolStripButtonPrev.Image = (Image) resources.GetObject("toolStripButtonPrev.Image");
            this.toolStripButtonPrev.ImageScaling = ToolStripItemImageScaling.None;
            this.toolStripButtonPrev.ImageTransparentColor = Color.Transparent;
            this.toolStripButtonPrev.Margin = new Padding(0);
            this.toolStripButtonPrev.Name = "toolStripButtonPrev";
            this.toolStripButtonPrev.Size = new Size(0x22, 0x22);
            this.toolStripButtonPrev.Text = "Previous";
            this.toolStripButtonPrev.Click += new EventHandler(this.toolStripButtonPrev_Click);
            this.toolStripButtonNext.AutoSize = false;
            this.toolStripButtonNext.DisplayStyle = ToolStripItemDisplayStyle.Image;
            this.toolStripButtonNext.Image = (Image) resources.GetObject("toolStripButtonNext.Image");
            this.toolStripButtonNext.ImageScaling = ToolStripItemImageScaling.None;
            this.toolStripButtonNext.ImageTransparentColor = Color.Transparent;
            this.toolStripButtonNext.Margin = new Padding(0);
            this.toolStripButtonNext.Name = "toolStripButtonNext";
            this.toolStripButtonNext.Size = new Size(0x22, 0x22);
            this.toolStripButtonNext.Text = "Next";
            this.toolStripButtonNext.Click += new EventHandler(this.toolStripButtonNext_Click);
            this.toolStripButtonLast.AutoSize = false;
            this.toolStripButtonLast.DisplayStyle = ToolStripItemDisplayStyle.Image;
            this.toolStripButtonLast.Image = (Image) resources.GetObject("toolStripButtonLast.Image");
            this.toolStripButtonLast.ImageScaling = ToolStripItemImageScaling.None;
            this.toolStripButtonLast.ImageTransparentColor = Color.Transparent;
            this.toolStripButtonLast.Margin = new Padding(0);
            this.toolStripButtonLast.Name = "toolStripButtonLast";
            this.toolStripButtonLast.Size = new Size(0x22, 0x22);
            this.toolStripButtonLast.Text = "Last";
            this.toolStripButtonLast.Click += new EventHandler(this.toolStripButtonLast_Click);
            this.toolStripSeparator3.Name = "toolStripSeparator3";
            this.toolStripSeparator3.Size = new Size(6, 0x25);
            this.toolStripButtonAdd.AutoSize = false;
            this.toolStripButtonAdd.DisplayStyle = ToolStripItemDisplayStyle.Image;
            this.toolStripButtonAdd.Image = (Image) resources.GetObject("toolStripButtonAdd.Image");
            this.toolStripButtonAdd.ImageScaling = ToolStripItemImageScaling.None;
            this.toolStripButtonAdd.ImageTransparentColor = Color.Transparent;
            this.toolStripButtonAdd.Name = "toolStripButtonAdd";
            this.toolStripButtonAdd.Size = new Size(0x22, 0x22);
            this.toolStripButtonAdd.Text = "Add";
            this.toolStripButtonAdd.Click += new EventHandler(this.toolStripButtonAdd_Click);
            this.toolStripButtonRemove.AutoSize = false;
            this.toolStripButtonRemove.DisplayStyle = ToolStripItemDisplayStyle.Image;
            this.toolStripButtonRemove.Image = (Image) resources.GetObject("toolStripButtonRemove.Image");
            this.toolStripButtonRemove.ImageScaling = ToolStripItemImageScaling.None;
            this.toolStripButtonRemove.ImageTransparentColor = Color.Transparent;
            this.toolStripButtonRemove.Margin = new Padding(0);
            this.toolStripButtonRemove.Name = "toolStripButtonRemove";
            this.toolStripButtonRemove.Size = new Size(0x22, 0x22);
            this.toolStripButtonRemove.Text = "Remove";
            this.toolStripButtonRemove.Click += new EventHandler(this.toolStripButtonRemove_Click);
            this.toolStripButtonModify.AutoSize = false;
            this.toolStripButtonModify.DisplayStyle = ToolStripItemDisplayStyle.Image;
            this.toolStripButtonModify.Image = (Image) resources.GetObject("toolStripButtonModify.Image");
            this.toolStripButtonModify.ImageScaling = ToolStripItemImageScaling.None;
            this.toolStripButtonModify.ImageTransparentColor = Color.Transparent;
            this.toolStripButtonModify.Margin = new Padding(0);
            this.toolStripButtonModify.Name = "toolStripButtonModify";
            this.toolStripButtonModify.Size = new Size(0x22, 0x22);
            this.toolStripButtonModify.Text = "Modify";
            this.toolStripButtonModify.Click += new EventHandler(this.toolStripButtonModify_Click);
            this.toolStripButtonConfirm.AutoSize = false;
            this.toolStripButtonConfirm.DisplayStyle = ToolStripItemDisplayStyle.Image;
            this.toolStripButtonConfirm.Image = (Image) resources.GetObject("toolStripButtonConfirm.Image");
            this.toolStripButtonConfirm.ImageScaling = ToolStripItemImageScaling.None;
            this.toolStripButtonConfirm.ImageTransparentColor = Color.Transparent;
            this.toolStripButtonConfirm.Margin = new Padding(0);
            this.toolStripButtonConfirm.Name = "toolStripButtonConfirm";
            this.toolStripButtonConfirm.Size = new Size(0x22, 0x22);
            this.toolStripButtonConfirm.Text = "Confirm";
            this.toolStripButtonConfirm.Click += new EventHandler(this.toolStripButtonConfirm_Click);
            this.toolStripButtonCancel.AutoSize = false;
            this.toolStripButtonCancel.DisplayStyle = ToolStripItemDisplayStyle.Image;
            this.toolStripButtonCancel.Image = (Image) resources.GetObject("toolStripButtonCancel.Image");
            this.toolStripButtonCancel.ImageScaling = ToolStripItemImageScaling.None;
            this.toolStripButtonCancel.ImageTransparentColor = Color.Transparent;
            this.toolStripButtonCancel.Margin = new Padding(0);
            this.toolStripButtonCancel.Name = "toolStripButtonCancel";
            this.toolStripButtonCancel.Size = new Size(0x22, 0x22);
            this.toolStripButtonCancel.Text = "Cancel";
            this.toolStripButtonCancel.Click += new EventHandler(this.toolStripButtonCancel_Click);
            this.groupBox1.Controls.Add(this.textBoxDbFilePath);
            this.groupBox1.Controls.Add(this.label1);
            this.groupBox1.Location = new Point(8, 0x2e);
            this.groupBox1.Name = "groupBox1";
            this.groupBox1.Size = new Size(0x28f, 0x38);
            this.groupBox1.TabIndex = 0;
            this.groupBox1.TabStop = false;
            this.groupBox1.Text = "DB Kit File";
            this.label2.AutoSize = true;
            this.label2.Location = new Point(8, 20);
            this.label2.Name = "label2";
            this.label2.Size = new Size(0x29, 13);
            this.label2.TabIndex = 0;
            this.label2.Text = "Code : ";
            this.label3.AutoSize = true;
            this.label3.Location = new Point(8, 0x35);
            this.label3.Name = "label3";
            this.label3.Size = new Size(0x42, 13);
            this.label3.TabIndex = 3;
            this.label3.Text = "Description :";
            this.label4.AutoSize = true;
            this.label4.Location = new Point(8, 0x88);
            this.label4.Name = "label4";
            this.label4.Size = new Size(0x29, 13);
            this.label4.TabIndex = 5;
            this.label4.Text = "Photo :";
            this.textBoxCode.Location = new Point(80, 0x10);
            this.textBoxCode.Name = "textBoxCode";
            this.textBoxCode.Size = new Size(160, 20);
            this.textBoxCode.TabIndex = 1;
            this.textBoxCode.TextChanged += new EventHandler(this.textBoxCode_TextChanged);
            this.textBoxDescription.Location = new Point(80, 0x31);
            this.textBoxDescription.Name = "textBoxDescription";
            this.textBoxDescription.Size = new Size(0x232, 20);
            this.textBoxDescription.TabIndex = 4;
            this.pictureBoxPhoto.BorderStyle = BorderStyle.FixedSingle;
            this.pictureBoxPhoto.Location = new Point(80, 0x52);
            this.pictureBoxPhoto.Margin = new Padding(0);
            this.pictureBoxPhoto.Name = "pictureBoxPhoto";
            this.pictureBoxPhoto.Size = new Size(160, 120);
            this.pictureBoxPhoto.TabIndex = 9;
            this.pictureBoxPhoto.TabStop = false;
            this.groupBox2.Controls.Add(this.groupBox4);
            this.groupBox2.Controls.Add(this.groupBox3);
            this.groupBox2.Controls.Add(this.buttonCalcUrl);
            this.groupBox2.Controls.Add(this.textBoxUrl);
            this.groupBox2.Controls.Add(this.label7);
            this.groupBox2.Controls.Add(this.buttonLoadPhoto);
            this.groupBox2.Controls.Add(this.pictureBoxPhoto);
            this.groupBox2.Controls.Add(this.label2);
            this.groupBox2.Controls.Add(this.label4);
            this.groupBox2.Controls.Add(this.textBoxDescription);
            this.groupBox2.Controls.Add(this.textBoxCode);
            this.groupBox2.Controls.Add(this.label3);
            this.groupBox2.Location = new Point(8, 0x6d);
            this.groupBox2.Name = "groupBox2";
            this.groupBox2.Size = new Size(0x28f, 0x1b6);
            this.groupBox2.TabIndex = 2;
            this.groupBox2.TabStop = false;
            this.buttonCalcUrl.Location = new Point(0xf6, 14);
            this.buttonCalcUrl.Name = "buttonCalcUrl";
            this.buttonCalcUrl.Size = new Size(0x4b, 0x17);
            this.buttonCalcUrl.TabIndex = 2;
            this.buttonCalcUrl.Text = "Calc URL";
            this.buttonCalcUrl.UseVisualStyleBackColor = true;
            this.buttonCalcUrl.Click += new EventHandler(this.buttonCalcUrl_Click);
            this.textBoxUrl.Location = new Point(80, 0xd7);
            this.textBoxUrl.Name = "textBoxUrl";
            this.textBoxUrl.Size = new Size(0x232, 20);
            this.textBoxUrl.TabIndex = 8;
            this.label7.AutoSize = true;
            this.label7.Location = new Point(8, 0xdb);
            this.label7.Name = "label7";
            this.label7.Size = new Size(0x1a, 13);
            this.label7.TabIndex = 7;
            this.label7.Text = "Url :";
            this.buttonLoadPhoto.Location = new Point(0xf6, 0xb3);
            this.buttonLoadPhoto.Name = "buttonLoadPhoto";
            this.buttonLoadPhoto.Size = new Size(0x4b, 0x17);
            this.buttonLoadPhoto.TabIndex = 6;
            this.buttonLoadPhoto.Text = "Browse";
            this.buttonLoadPhoto.UseVisualStyleBackColor = true;
            this.buttonLoadPhoto.Click += new EventHandler(this.buttonLoadPhoto_Click);
            this.timer1.Interval = 200;
            this.timer1.Tick += new EventHandler(this.timer1_Tick);
            this.groupBox3.Controls.Add(this.textBoxDirectProtocol);
            this.groupBox3.Controls.Add(this.label6);
            this.groupBox3.Controls.Add(this.comboBoxDirectSocket);
            this.groupBox3.Controls.Add(this.label5);
            this.groupBox3.Location = new Point(7, 0xff);
            this.groupBox3.Name = "groupBox3";
            this.groupBox3.Size = new Size(0x27b, 0x5f);
            this.groupBox3.TabIndex = 13;
            this.groupBox3.TabStop = false;
            this.groupBox3.Text = "Direct";
            this.textBoxDirectProtocol.Location = new Point(0x4e, 60);
            this.textBoxDirectProtocol.Name = "textBoxProtocol";
            this.textBoxDirectProtocol.Size = new Size(540, 20);
            this.textBoxDirectProtocol.TabIndex = 0x10;
            this.label6.AutoSize = true;
            this.label6.Location = new Point(6, 0x40);
            this.label6.Name = "label6";
            this.label6.Size = new Size(0x34, 13);
            this.label6.TabIndex = 15;
            this.label6.Text = "Protocol :";
            this.comboBoxDirectSocket.DropDownStyle = ComboBoxStyle.DropDownList;
            this.comboBoxDirectSocket.FormattingEnabled = true;
            this.comboBoxDirectSocket.Location = new Point(80, 0x1a);
            this.comboBoxDirectSocket.Name = "comboBoxSocket";
            this.comboBoxDirectSocket.Size = new Size(160, 0x15);
            this.comboBoxDirectSocket.TabIndex = 14;
            this.label5.AutoSize = true;
            this.label5.Location = new Point(6, 30);
            this.label5.Name = "label5";
            this.label5.Size = new Size(0x2f, 13);
            this.label5.TabIndex = 13;
            this.label5.Text = "Socket :";
            this.groupBox4.Controls.Add(this.textBoxBridgedProtocol);
            this.groupBox4.Controls.Add(this.label8);
            this.groupBox4.Location = new Point(7, 0x164);
            this.groupBox4.Name = "groupBox4";
            this.groupBox4.Size = new Size(0x27b, 70);
            this.groupBox4.TabIndex = 14;
            this.groupBox4.TabStop = false;
            this.groupBox4.Text = "Bridget (Througth ST Device Daemon) ";
            this.textBoxBridgedProtocol.Location = new Point(80, 30);
            this.textBoxBridgedProtocol.Name = "textBoxSDD";
            this.textBoxBridgedProtocol.Size = new Size(0x21a, 20);
            this.textBoxBridgedProtocol.TabIndex = 0x10;
            this.label8.AutoSize = true;
            this.label8.Location = new Point(8, 0x22);
            this.label8.Name = "label8";
            this.label8.Size = new Size(0x34, 13);
            this.label8.TabIndex = 15;
            this.label8.Text = "Protocol :";
            base.AutoScaleDimensions = new SizeF(6f, 13f);
            base.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            base.ClientSize = new Size(0x2a1, 0x22c);
            base.Controls.Add(this.toolStrip1);
            base.Controls.Add(this.groupBox1);
            base.Controls.Add(this.groupBox2);
            base.FormBorderStyle = System.Windows.Forms.FormBorderStyle.FixedSingle;
            base.Icon = (Icon) resources.GetObject("$this.Icon");
            base.MaximizeBox = false;
            base.MinimizeBox = false;
            base.Name = "KSDbEditor";
            base.StartPosition = FormStartPosition.CenterParent;
            this.Text = "Kit database Editor";
            base.Load += new EventHandler(this.dcpKitDbEditor_Load);
            base.FormClosing += new FormClosingEventHandler(this.dcpKitDbEditor_FormClosing);
            this.toolStrip1.ResumeLayout(false);
            this.toolStrip1.PerformLayout();
            this.groupBox1.ResumeLayout(false);
            this.groupBox1.PerformLayout();
            ((ISupportInitialize) this.pictureBoxPhoto).EndInit();
            this.groupBox2.ResumeLayout(false);
            this.groupBox2.PerformLayout();
            this.groupBox3.ResumeLayout(false);
            this.groupBox3.PerformLayout();
            this.groupBox4.ResumeLayout(false);
            this.groupBox4.PerformLayout();
            base.ResumeLayout(false);
            base.PerformLayout();
        }

        private void LoadDB(string DbkFile)
        {
            textBoxDbFilePath.Text = DbkFile;
            ClearForm();
            if (kitDataProvider.Load(DbkFile))
            {
                LookUpKit(kitDataProvider.MoveTo(KSDataProvider.CursorStep.CursorFirst));
            }
            else
            {
                MessageBox.Show(Messages.KS_ERROR_LOAD, Messages.KS_CAPTION_EDITOR, MessageBoxButtons.OK, MessageBoxIcon.Hand);
            }
            editorState = EditorState.Viewer;
            UpdateControls();
        }

        private void LookUpKit(KSKit kit)
        {
            ClearForm();
            if (kit != null)
            {
                textBoxCode.Text = kit.Code;
                textBoxDescription.Text = kit.Description;
                pictureBoxPhoto.Image = kit.Photo;
                textBoxUrl.Text = kit.Url;
                textBoxDirectProtocol.Text = kit.DirectSocket.Protocol;
                textBoxBridgedProtocol.Text = kit.BridgedSocket.Protocol;
                comboBoxDirectSocket.SelectedIndex = (int) kit.DirectSocket.Type;
            }
        }

        private void SaveDb()
        {
            if (!kitDataProvider.saveDb(textBoxDbFilePath.Text))
            {
                MessageBox.Show(Messages.KS_ERROR_SAVE, Messages.KS_CAPTION_EDITOR, MessageBoxButtons.OK, MessageBoxIcon.Hand);
            }
            UpdateControls();
        }

        private void textBoxCode_TextChanged(object sender, EventArgs e)
        {
            buttonCalcUrl.Enabled = textBoxCode.Text != "";
        }

        private void timer1_Tick(object sender, EventArgs e)
        {
            timer1.Enabled = false;
            LoadDB(textBoxDbFilePath.Text);
            UpdateControls();
        }

        private void toolStripButtonAdd_Click(object sender, EventArgs e)
        {
            ClearForm();
            textBoxCode.Text = Messages.KS_MASK_KIT_CODE;
            editorState = EditorState.Insert;
            UpdateControls();
        }

        private void toolStripButtonCancel_Click(object sender, EventArgs e)
        {
            LookUpKit(kitDataProvider.MoveTo(KSDataProvider.CursorStep.CursorFirst));
            editorState = EditorState.Viewer;
            UpdateControls();
        }

        private void toolStripButtonConfirm_Click(object sender, EventArgs e)
        {
            KSKit kit = new KSKit {
                Code = textBoxCode.Text.Trim().ToUpper(),
                Description = textBoxDescription.Text,
                Photo = pictureBoxPhoto.Image,
                Url = textBoxUrl.Text
            };
            kit.DirectSocket.Type = (KSSocketType) comboBoxDirectSocket.SelectedIndex;
            kit.DirectSocket.Protocol = textBoxDirectProtocol.Text;
            kit.BridgedSocket.Type = KSSocketType.TcpIp;
            kit.BridgedSocket.Protocol = textBoxBridgedProtocol.Text;
            switch (editorState)
            {
                case EditorState.Insert:
                    if (!kitDataProvider.Add(kit))
                    {
                        MessageBox.Show(Messages.KS_ERROR_ADD, Messages.KS_CAPTION_EDITOR, MessageBoxButtons.OK, MessageBoxIcon.Hand);
                        LookUpKit(kitDataProvider.MoveTo(KSDataProvider.CursorStep.CursorFirst));
                        break;
                    }
                    LookUpKit(kitDataProvider.MoveTo(KSDataProvider.CursorStep.CursorLast));
                    break;

                case EditorState.Modify:
                    if (!kitDataProvider.Update(kit))
                    {
                        MessageBox.Show(Messages.KS_ERROR_MODIFY, Messages.KS_CAPTION_EDITOR, MessageBoxButtons.OK, MessageBoxIcon.Hand);
                        LookUpKit(kitDataProvider.MoveTo(KSDataProvider.CursorStep.CursorFirst));
                    }
                    break;
            }
            editorState = EditorState.Viewer;
            UpdateControls();
        }

        private void toolStripButtonFirst_Click(object sender, EventArgs e)
        {
            LookUpKit(kitDataProvider.MoveTo(KSDataProvider.CursorStep.CursorFirst));
            UpdateControls();
        }

        private void toolStripButtonLast_Click(object sender, EventArgs e)
        {
            LookUpKit(kitDataProvider.MoveTo(KSDataProvider.CursorStep.CursorLast));
            UpdateControls();
        }

        private void toolStripButtonLoad_Click(object sender, EventArgs e)
        {
            dcpKitDbEditor_FormClosing(null, null);
            openFileDialog1.Filter = Messages.KS_FILTER_DB;
            openFileDialog1.FileName = textBoxDbFilePath.Text;
            if (openFileDialog1.ShowDialog() == DialogResult.OK)
            {
                LoadDB(openFileDialog1.FileName);
            }
        }

        private void toolStripButtonModify_Click(object sender, EventArgs e)
        {
            editorState = EditorState.Modify;
            UpdateControls();
        }

        private void toolStripButtonNew_Click(object sender, EventArgs e)
        {
            dcpKitDbEditor_FormClosing(null, null);
            kitDataProvider = new KSDataProvider();
            textBoxDbFilePath.Text = "";
            toolStripButtonAdd_Click(null, null);
        }

        private void toolStripButtonNext_Click(object sender, EventArgs e)
        {
            LookUpKit(kitDataProvider.MoveTo(KSDataProvider.CursorStep.CursorNext));
            UpdateControls();
        }

        private void toolStripButtonPrev_Click(object sender, EventArgs e)
        {
            LookUpKit(kitDataProvider.MoveTo(KSDataProvider.CursorStep.CursorPrev));
            UpdateControls();
        }

        private void toolStripButtonRemove_Click(object sender, EventArgs e)
        {
            if (MessageBox.Show(Messages.KS_QUESTION_DELETE, Messages.KS_CAPTION_EDITOR, MessageBoxButtons.YesNo, MessageBoxIcon.Question) == DialogResult.Yes)
            {
                if (kitDataProvider.Remove(textBoxCode.Text))
                {
                    LookUpKit(kitDataProvider.MoveTo(KSDataProvider.CursorStep.CursorFirst));
                }
                else
                {
                    MessageBox.Show(Messages.KS_ERROR_DELETE, Messages.KS_CAPTION_EDITOR, MessageBoxButtons.OK, MessageBoxIcon.Hand);
                }
                UpdateControls();
            }
        }

        private void toolStripButtonSave_Click(object sender, EventArgs e)
        {
            if (textBoxDbFilePath.Text != "")
            {
                SaveDb();
            }
            else
            {
                toolStripButtonSaveAs_Click(null, null);
            }
        }

        private void toolStripButtonSaveAs_Click(object sender, EventArgs e)
        {
            saveFileDialog1.Filter = Messages.KS_FILTER_DB;
            saveFileDialog1.FileName = textBoxDbFilePath.Text;
            if (saveFileDialog1.ShowDialog() == DialogResult.OK)
            {
                textBoxDbFilePath.Text = saveFileDialog1.FileName;
                SaveDb();
            }
        }

        private void UpdateControls()
        {
            textBoxDbFilePath.Enabled = false;
            switch (editorState)
            {
                case EditorState.Viewer:
                    textBoxCode.Enabled = false;
                    buttonCalcUrl.Enabled = false;
                    textBoxDescription.Enabled = false;
                    pictureBoxPhoto.Enabled = false;
                    buttonLoadPhoto.Enabled = false;
                    textBoxUrl.Enabled = false;
                    comboBoxDirectSocket.Enabled = false;
                    textBoxDirectProtocol.Enabled = false;
                    textBoxBridgedProtocol.Enabled = false;
                    toolStripButtonNew.Enabled = true;
                    toolStripButtonLoad.Enabled = true;
                    toolStripButtonSave.Enabled = kitDataProvider.IsModified;
                    toolStripButtonSaveAs.Enabled = kitDataProvider.IsModified;
                    toolStripButtonFirst.Enabled = !kitDataProvider.IsFirstKit;
                    toolStripButtonPrev.Enabled = !kitDataProvider.IsFirstKit;
                    toolStripButtonNext.Enabled = !kitDataProvider.IsLastKit;
                    toolStripButtonLast.Enabled = !kitDataProvider.IsLastKit;
                    toolStripButtonAdd.Enabled = textBoxDbFilePath.Text != "";
                    toolStripButtonRemove.Enabled = !kitDataProvider.IsEmpty;
                    toolStripButtonModify.Enabled = !kitDataProvider.IsEmpty;
                    toolStripButtonConfirm.Enabled = false;
                    toolStripButtonCancel.Enabled = false;
                    return;

                case EditorState.Insert:
                case EditorState.Modify:
                    textBoxCode.Enabled = editorState == EditorState.Insert;
                    buttonCalcUrl.Enabled = textBoxCode.Text != "";
                    textBoxDescription.Enabled = true;
                    pictureBoxPhoto.Enabled = true;
                    buttonLoadPhoto.Enabled = true;
                    textBoxUrl.Enabled = true;
                    comboBoxDirectSocket.Enabled = true;
                    textBoxDirectProtocol.Enabled = true;
                    textBoxBridgedProtocol.Enabled = true;
                    toolStripButtonNew.Enabled = false;
                    toolStripButtonLoad.Enabled = false;
                    toolStripButtonSave.Enabled = false;
                    toolStripButtonSaveAs.Enabled = false;
                    toolStripButtonFirst.Enabled = false;
                    toolStripButtonPrev.Enabled = false;
                    toolStripButtonNext.Enabled = false;
                    toolStripButtonLast.Enabled = false;
                    toolStripButtonAdd.Enabled = false;
                    toolStripButtonRemove.Enabled = false;
                    toolStripButtonModify.Enabled = false;
                    toolStripButtonConfirm.Enabled = true;
                    toolStripButtonCancel.Enabled = true;
                    return;
            }
        }

        public string DbkFile
        {
            get
            {
                return textBoxDbFilePath.Text;
            }
        }

        private enum EditorState
        {
            Viewer,
            Insert,
            Modify
        }
    }
}

