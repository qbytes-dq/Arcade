namespace QBW_Joy2Key
{
    partial class Form1
    {
        /// <summary>
        /// Required designer variable.
        /// </summary>
        private System.ComponentModel.IContainer components = null;

        /// <summary>
        /// Clean up any resources being used.
        /// </summary>
        /// <param name="disposing">true if managed resources should be disposed; otherwise, false.</param>
        protected override void Dispose(bool disposing)
        {
            if (disposing && (components != null))
            {
                components.Dispose();
            }
            base.Dispose(disposing);
        }

        #region Windows Form Designer generated code

        /// <summary>
        /// Required method for Designer support - do not modify
        /// the contents of this method with the code editor.
        /// </summary>
        private void InitializeComponent()
        {
            this.components = new System.ComponentModel.Container();
            System.ComponentModel.ComponentResourceManager resources = new System.ComponentModel.ComponentResourceManager(typeof(Form1));
            this.tabControl = new System.Windows.Forms.TabControl();
            this.tabGameSystem = new System.Windows.Forms.TabPage();
            this.lblTimerInfo_TimerID = new System.Windows.Forms.Label();
            this.txtTimerInfo_TimerID = new System.Windows.Forms.TextBox();
            this.lblTimerInfo_TicksReceived = new System.Windows.Forms.Label();
            this.txtTimerInfo_TicksReceived = new System.Windows.Forms.TextBox();
            this.textBox2 = new System.Windows.Forms.TextBox();
            this.btnTimerInfo_AddGame = new System.Windows.Forms.Button();
            this.btnTimerInfo_SaveTimerValue = new System.Windows.Forms.Button();
            this.numTimerInfo_Hz = new System.Windows.Forms.NumericUpDown();
            this.comboBox1 = new System.Windows.Forms.ComboBox();
            this.lblTimerInfoSystem = new System.Windows.Forms.Label();
            this.label1 = new System.Windows.Forms.Label();
            this.txtTimerInfo_ActualHz = new System.Windows.Forms.TextBox();
            this.lblTimerInfo_ActualInterval = new System.Windows.Forms.Label();
            this.lblTimerInfo_Running = new System.Windows.Forms.Label();
            this.txtTimerInfo_ActualInterval = new System.Windows.Forms.TextBox();
            this.txtTimerInfo_Running = new System.Windows.Forms.TextBox();
            this.txtTimerInfo_Interval = new System.Windows.Forms.TextBox();
            this.lblTimerInfo_Hz = new System.Windows.Forms.Label();
            this.lblTimerInfo_Interval = new System.Windows.Forms.Label();
            this.tabJoySticks = new System.Windows.Forms.TabPage();
            this.lblJoySticks = new System.Windows.Forms.Label();
            this.tabJoyStick_X = new System.Windows.Forms.TabPage();
            this.label2 = new System.Windows.Forms.Label();
            this.oneSecondTimer = new System.Windows.Forms.Timer(this.components);
            this.ckbTimerInfo_StartMinimized = new System.Windows.Forms.CheckBox();
            this.button1 = new System.Windows.Forms.Button();
            this.checkBox1 = new System.Windows.Forms.CheckBox();
            this.tabControl.SuspendLayout();
            this.tabGameSystem.SuspendLayout();
            ((System.ComponentModel.ISupportInitialize)(this.numTimerInfo_Hz)).BeginInit();
            this.tabJoySticks.SuspendLayout();
            this.tabJoyStick_X.SuspendLayout();
            this.SuspendLayout();
            // 
            // tabControl
            // 
            this.tabControl.Anchor = ((System.Windows.Forms.AnchorStyles)((((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Bottom) 
            | System.Windows.Forms.AnchorStyles.Left) 
            | System.Windows.Forms.AnchorStyles.Right)));
            this.tabControl.Controls.Add(this.tabGameSystem);
            this.tabControl.Controls.Add(this.tabJoySticks);
            this.tabControl.Controls.Add(this.tabJoyStick_X);
            this.tabControl.Location = new System.Drawing.Point(13, 13);
            this.tabControl.Name = "tabControl";
            this.tabControl.SelectedIndex = 0;
            this.tabControl.Size = new System.Drawing.Size(632, 369);
            this.tabControl.TabIndex = 0;
            // 
            // tabGameSystem
            // 
            this.tabGameSystem.Controls.Add(this.ckbTimerInfo_StartMinimized);
            this.tabGameSystem.Controls.Add(this.lblTimerInfo_TimerID);
            this.tabGameSystem.Controls.Add(this.txtTimerInfo_TimerID);
            this.tabGameSystem.Controls.Add(this.lblTimerInfo_TicksReceived);
            this.tabGameSystem.Controls.Add(this.txtTimerInfo_TicksReceived);
            this.tabGameSystem.Controls.Add(this.textBox2);
            this.tabGameSystem.Controls.Add(this.btnTimerInfo_AddGame);
            this.tabGameSystem.Controls.Add(this.btnTimerInfo_SaveTimerValue);
            this.tabGameSystem.Controls.Add(this.numTimerInfo_Hz);
            this.tabGameSystem.Controls.Add(this.comboBox1);
            this.tabGameSystem.Controls.Add(this.lblTimerInfoSystem);
            this.tabGameSystem.Controls.Add(this.label1);
            this.tabGameSystem.Controls.Add(this.txtTimerInfo_ActualHz);
            this.tabGameSystem.Controls.Add(this.lblTimerInfo_ActualInterval);
            this.tabGameSystem.Controls.Add(this.lblTimerInfo_Running);
            this.tabGameSystem.Controls.Add(this.txtTimerInfo_ActualInterval);
            this.tabGameSystem.Controls.Add(this.txtTimerInfo_Running);
            this.tabGameSystem.Controls.Add(this.txtTimerInfo_Interval);
            this.tabGameSystem.Controls.Add(this.lblTimerInfo_Hz);
            this.tabGameSystem.Controls.Add(this.lblTimerInfo_Interval);
            this.tabGameSystem.Location = new System.Drawing.Point(4, 22);
            this.tabGameSystem.Name = "tabGameSystem";
            this.tabGameSystem.Padding = new System.Windows.Forms.Padding(3);
            this.tabGameSystem.Size = new System.Drawing.Size(624, 343);
            this.tabGameSystem.TabIndex = 0;
            this.tabGameSystem.Text = "Game System";
            this.tabGameSystem.UseVisualStyleBackColor = true;
            // 
            // lblTimerInfo_TimerID
            // 
            this.lblTimerInfo_TimerID.AutoSize = true;
            this.lblTimerInfo_TimerID.Location = new System.Drawing.Point(342, 196);
            this.lblTimerInfo_TimerID.Name = "lblTimerInfo_TimerID";
            this.lblTimerInfo_TimerID.Size = new System.Drawing.Size(55, 13);
            this.lblTimerInfo_TimerID.TabIndex = 19;
            this.lblTimerInfo_TimerID.Text = "Thread ID";
            // 
            // txtTimerInfo_TimerID
            // 
            this.txtTimerInfo_TimerID.Enabled = false;
            this.txtTimerInfo_TimerID.Location = new System.Drawing.Point(500, 189);
            this.txtTimerInfo_TimerID.Name = "txtTimerInfo_TimerID";
            this.txtTimerInfo_TimerID.Size = new System.Drawing.Size(100, 20);
            this.txtTimerInfo_TimerID.TabIndex = 18;
            this.txtTimerInfo_TimerID.TextAlign = System.Windows.Forms.HorizontalAlignment.Center;
            // 
            // lblTimerInfo_TicksReceived
            // 
            this.lblTimerInfo_TicksReceived.AutoSize = true;
            this.lblTimerInfo_TicksReceived.Location = new System.Drawing.Point(342, 222);
            this.lblTimerInfo_TicksReceived.Name = "lblTimerInfo_TicksReceived";
            this.lblTimerInfo_TicksReceived.Size = new System.Drawing.Size(82, 13);
            this.lblTimerInfo_TicksReceived.TabIndex = 17;
            this.lblTimerInfo_TicksReceived.Text = "Ticks Received";
            // 
            // txtTimerInfo_TicksReceived
            // 
            this.txtTimerInfo_TicksReceived.Enabled = false;
            this.txtTimerInfo_TicksReceived.Location = new System.Drawing.Point(500, 215);
            this.txtTimerInfo_TicksReceived.Name = "txtTimerInfo_TicksReceived";
            this.txtTimerInfo_TicksReceived.Size = new System.Drawing.Size(100, 20);
            this.txtTimerInfo_TicksReceived.TabIndex = 16;
            this.txtTimerInfo_TicksReceived.TextAlign = System.Windows.Forms.HorizontalAlignment.Center;
            // 
            // textBox2
            // 
            this.textBox2.Location = new System.Drawing.Point(125, 35);
            this.textBox2.Name = "textBox2";
            this.textBox2.Size = new System.Drawing.Size(130, 20);
            this.textBox2.TabIndex = 15;
            this.textBox2.Text = "Add system name here";
            // 
            // btnTimerInfo_AddGame
            // 
            this.btnTimerInfo_AddGame.Location = new System.Drawing.Point(13, 88);
            this.btnTimerInfo_AddGame.Name = "btnTimerInfo_AddGame";
            this.btnTimerInfo_AddGame.Size = new System.Drawing.Size(260, 23);
            this.btnTimerInfo_AddGame.TabIndex = 14;
            this.btnTimerInfo_AddGame.Text = "Add Gaming System";
            this.btnTimerInfo_AddGame.UseVisualStyleBackColor = true;
            // 
            // btnTimerInfo_SaveTimerValue
            // 
            this.btnTimerInfo_SaveTimerValue.Location = new System.Drawing.Point(345, 88);
            this.btnTimerInfo_SaveTimerValue.Name = "btnTimerInfo_SaveTimerValue";
            this.btnTimerInfo_SaveTimerValue.Size = new System.Drawing.Size(255, 23);
            this.btnTimerInfo_SaveTimerValue.TabIndex = 13;
            this.btnTimerInfo_SaveTimerValue.Text = "Save Timer Values for Gaming System";
            this.btnTimerInfo_SaveTimerValue.UseVisualStyleBackColor = true;
            this.btnTimerInfo_SaveTimerValue.Click += new System.EventHandler(this.btnTimerInfo_SaveTimerValue_Click);
            // 
            // numTimerInfo_Hz
            // 
            this.numTimerInfo_Hz.Location = new System.Drawing.Point(500, 6);
            this.numTimerInfo_Hz.Minimum = new decimal(new int[] {
            1,
            0,
            0,
            0});
            this.numTimerInfo_Hz.Name = "numTimerInfo_Hz";
            this.numTimerInfo_Hz.Size = new System.Drawing.Size(117, 20);
            this.numTimerInfo_Hz.TabIndex = 12;
            this.numTimerInfo_Hz.TextAlign = System.Windows.Forms.HorizontalAlignment.Center;
            this.numTimerInfo_Hz.Value = new decimal(new int[] {
            40,
            0,
            0,
            0});
            // 
            // comboBox1
            // 
            this.comboBox1.FormattingEnabled = true;
            this.comboBox1.Items.AddRange(new object[] {
            "MAME",
            "Atari 2600",
            "Wii",
            "NES",
            "SNES"});
            this.comboBox1.Location = new System.Drawing.Point(125, 5);
            this.comboBox1.Name = "comboBox1";
            this.comboBox1.Size = new System.Drawing.Size(148, 21);
            this.comboBox1.TabIndex = 11;
            this.comboBox1.Text = "Load from conf";
            // 
            // lblTimerInfoSystem
            // 
            this.lblTimerInfoSystem.AutoSize = true;
            this.lblTimerInfoSystem.Location = new System.Drawing.Point(10, 13);
            this.lblTimerInfoSystem.Name = "lblTimerInfoSystem";
            this.lblTimerInfoSystem.Size = new System.Drawing.Size(80, 13);
            this.lblTimerInfoSystem.TabIndex = 10;
            this.lblTimerInfoSystem.Text = "Gaming System";
            // 
            // label1
            // 
            this.label1.AutoSize = true;
            this.label1.Location = new System.Drawing.Point(342, 248);
            this.label1.Name = "label1";
            this.label1.Size = new System.Drawing.Size(149, 13);
            this.label1.TabIndex = 9;
            this.label1.Text = "Actual Times Per Second (Hz)";
            // 
            // txtTimerInfo_ActualHz
            // 
            this.txtTimerInfo_ActualHz.Enabled = false;
            this.txtTimerInfo_ActualHz.Location = new System.Drawing.Point(500, 241);
            this.txtTimerInfo_ActualHz.Name = "txtTimerInfo_ActualHz";
            this.txtTimerInfo_ActualHz.Size = new System.Drawing.Size(100, 20);
            this.txtTimerInfo_ActualHz.TabIndex = 8;
            this.txtTimerInfo_ActualHz.TextAlign = System.Windows.Forms.HorizontalAlignment.Center;
            // 
            // lblTimerInfo_ActualInterval
            // 
            this.lblTimerInfo_ActualInterval.AutoSize = true;
            this.lblTimerInfo_ActualInterval.Location = new System.Drawing.Point(342, 274);
            this.lblTimerInfo_ActualInterval.Name = "lblTimerInfo_ActualInterval";
            this.lblTimerInfo_ActualInterval.Size = new System.Drawing.Size(99, 13);
            this.lblTimerInfo_ActualInterval.TabIndex = 7;
            this.lblTimerInfo_ActualInterval.Text = "Actual Interval (mS)";
            // 
            // lblTimerInfo_Running
            // 
            this.lblTimerInfo_Running.AutoSize = true;
            this.lblTimerInfo_Running.Location = new System.Drawing.Point(342, 170);
            this.lblTimerInfo_Running.Name = "lblTimerInfo_Running";
            this.lblTimerInfo_Running.Size = new System.Drawing.Size(117, 13);
            this.lblTimerInfo_Running.TabIndex = 6;
            this.lblTimerInfo_Running.Text = "Joystick Timer Running";
            // 
            // txtTimerInfo_ActualInterval
            // 
            this.txtTimerInfo_ActualInterval.Enabled = false;
            this.txtTimerInfo_ActualInterval.Location = new System.Drawing.Point(500, 267);
            this.txtTimerInfo_ActualInterval.Name = "txtTimerInfo_ActualInterval";
            this.txtTimerInfo_ActualInterval.Size = new System.Drawing.Size(100, 20);
            this.txtTimerInfo_ActualInterval.TabIndex = 5;
            this.txtTimerInfo_ActualInterval.TextAlign = System.Windows.Forms.HorizontalAlignment.Center;
            // 
            // txtTimerInfo_Running
            // 
            this.txtTimerInfo_Running.Enabled = false;
            this.txtTimerInfo_Running.Location = new System.Drawing.Point(500, 163);
            this.txtTimerInfo_Running.Name = "txtTimerInfo_Running";
            this.txtTimerInfo_Running.Size = new System.Drawing.Size(100, 20);
            this.txtTimerInfo_Running.TabIndex = 4;
            this.txtTimerInfo_Running.TextAlign = System.Windows.Forms.HorizontalAlignment.Center;
            // 
            // txtTimerInfo_Interval
            // 
            this.txtTimerInfo_Interval.Enabled = false;
            this.txtTimerInfo_Interval.Location = new System.Drawing.Point(500, 32);
            this.txtTimerInfo_Interval.Name = "txtTimerInfo_Interval";
            this.txtTimerInfo_Interval.Size = new System.Drawing.Size(100, 20);
            this.txtTimerInfo_Interval.TabIndex = 3;
            this.txtTimerInfo_Interval.TextAlign = System.Windows.Forms.HorizontalAlignment.Center;
            // 
            // lblTimerInfo_Hz
            // 
            this.lblTimerInfo_Hz.AutoSize = true;
            this.lblTimerInfo_Hz.Location = new System.Drawing.Point(342, 8);
            this.lblTimerInfo_Hz.Name = "lblTimerInfo_Hz";
            this.lblTimerInfo_Hz.Size = new System.Drawing.Size(116, 13);
            this.lblTimerInfo_Hz.TabIndex = 1;
            this.lblTimerInfo_Hz.Text = "Times Per Second (Hz)";
            // 
            // lblTimerInfo_Interval
            // 
            this.lblTimerInfo_Interval.AutoSize = true;
            this.lblTimerInfo_Interval.Location = new System.Drawing.Point(342, 35);
            this.lblTimerInfo_Interval.Name = "lblTimerInfo_Interval";
            this.lblTimerInfo_Interval.Size = new System.Drawing.Size(66, 13);
            this.lblTimerInfo_Interval.TabIndex = 0;
            this.lblTimerInfo_Interval.Text = "Interval (mS)";
            // 
            // tabJoySticks
            // 
            this.tabJoySticks.Controls.Add(this.checkBox1);
            this.tabJoySticks.Controls.Add(this.lblJoySticks);
            this.tabJoySticks.Location = new System.Drawing.Point(4, 22);
            this.tabJoySticks.Name = "tabJoySticks";
            this.tabJoySticks.Padding = new System.Windows.Forms.Padding(3);
            this.tabJoySticks.Size = new System.Drawing.Size(624, 343);
            this.tabJoySticks.TabIndex = 1;
            this.tabJoySticks.Text = "JoySticks";
            this.tabJoySticks.UseVisualStyleBackColor = true;
            // 
            // lblJoySticks
            // 
            this.lblJoySticks.AutoSize = true;
            this.lblJoySticks.Location = new System.Drawing.Point(27, 39);
            this.lblJoySticks.Name = "lblJoySticks";
            this.lblJoySticks.Size = new System.Drawing.Size(612, 13);
            this.lblJoySticks.TabIndex = 1;
            this.lblJoySticks.Text = "This will be a list of all joysticks that can be added to the game or have been a" +
    "dded.  Also include a checkbox to indicate activity";
            // 
            // tabJoyStick_X
            // 
            this.tabJoyStick_X.Controls.Add(this.button1);
            this.tabJoyStick_X.Controls.Add(this.label2);
            this.tabJoyStick_X.Location = new System.Drawing.Point(4, 22);
            this.tabJoyStick_X.Name = "tabJoyStick_X";
            this.tabJoyStick_X.Size = new System.Drawing.Size(624, 343);
            this.tabJoyStick_X.TabIndex = 2;
            this.tabJoyStick_X.Text = "JoyStick (1)";
            this.tabJoyStick_X.UseVisualStyleBackColor = true;
            // 
            // label2
            // 
            this.label2.AutoSize = true;
            this.label2.Location = new System.Drawing.Point(38, 95);
            this.label2.Name = "label2";
            this.label2.Size = new System.Drawing.Size(284, 13);
            this.label2.TabIndex = 2;
            this.label2.Text = "This will be the joystick and its values for the specific game";
            // 
            // oneSecondTimer
            // 
            this.oneSecondTimer.Interval = 1000;
            this.oneSecondTimer.Tick += new System.EventHandler(this.oneSecondTimer_Tick);
            // 
            // ckbTimerInfo_StartMinimized
            // 
            this.ckbTimerInfo_StartMinimized.AutoSize = true;
            this.ckbTimerInfo_StartMinimized.Location = new System.Drawing.Point(345, 65);
            this.ckbTimerInfo_StartMinimized.Name = "ckbTimerInfo_StartMinimized";
            this.ckbTimerInfo_StartMinimized.Size = new System.Drawing.Size(97, 17);
            this.ckbTimerInfo_StartMinimized.TabIndex = 21;
            this.ckbTimerInfo_StartMinimized.Text = "Start Minimized";
            this.ckbTimerInfo_StartMinimized.UseVisualStyleBackColor = true;
            // 
            // button1
            // 
            this.button1.Location = new System.Drawing.Point(229, 248);
            this.button1.Name = "button1";
            this.button1.Size = new System.Drawing.Size(100, 23);
            this.button1.TabIndex = 3;
            this.button1.Text = "Remove Joystick";
            this.button1.UseVisualStyleBackColor = true;
            // 
            // checkBox1
            // 
            this.checkBox1.AutoSize = true;
            this.checkBox1.Location = new System.Drawing.Point(489, 306);
            this.checkBox1.Name = "checkBox1";
            this.checkBox1.Size = new System.Drawing.Size(100, 17);
            this.checkBox1.TabIndex = 5;
            this.checkBox1.Text = "Joystick activity";
            this.checkBox1.UseVisualStyleBackColor = true;
            // 
            // Form1
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(657, 394);
            this.Controls.Add(this.tabControl);
            this.FormBorderStyle = System.Windows.Forms.FormBorderStyle.FixedDialog;
            this.Icon = ((System.Drawing.Icon)(resources.GetObject("$this.Icon")));
            this.Name = "Form1";
            this.Text = "QBW Joy2Key";
            this.FormClosing += new System.Windows.Forms.FormClosingEventHandler(this.Form1_FormClosing);
            this.tabControl.ResumeLayout(false);
            this.tabGameSystem.ResumeLayout(false);
            this.tabGameSystem.PerformLayout();
            ((System.ComponentModel.ISupportInitialize)(this.numTimerInfo_Hz)).EndInit();
            this.tabJoySticks.ResumeLayout(false);
            this.tabJoySticks.PerformLayout();
            this.tabJoyStick_X.ResumeLayout(false);
            this.tabJoyStick_X.PerformLayout();
            this.ResumeLayout(false);

        }

        #endregion

        private System.Windows.Forms.TabControl tabControl;
        private System.Windows.Forms.TabPage tabGameSystem;
        private System.Windows.Forms.Label label1;
        private System.Windows.Forms.TextBox txtTimerInfo_ActualHz;
        private System.Windows.Forms.Label lblTimerInfo_ActualInterval;
        private System.Windows.Forms.Label lblTimerInfo_Running;
        private System.Windows.Forms.TextBox txtTimerInfo_ActualInterval;
        private System.Windows.Forms.TextBox txtTimerInfo_Running;
        private System.Windows.Forms.TextBox txtTimerInfo_Interval;
        private System.Windows.Forms.Label lblTimerInfo_Hz;
        private System.Windows.Forms.Label lblTimerInfo_Interval;
        private System.Windows.Forms.TabPage tabJoySticks;
        private System.Windows.Forms.ComboBox comboBox1;
        private System.Windows.Forms.Label lblTimerInfoSystem;
        private System.Windows.Forms.Label lblJoySticks;
        private System.Windows.Forms.TabPage tabJoyStick_X;
        private System.Windows.Forms.NumericUpDown numTimerInfo_Hz;
        private System.Windows.Forms.TextBox textBox2;
        private System.Windows.Forms.Button btnTimerInfo_AddGame;
        private System.Windows.Forms.Button btnTimerInfo_SaveTimerValue;
        private System.Windows.Forms.Label label2;
        private System.Windows.Forms.Label lblTimerInfo_TimerID;
        private System.Windows.Forms.TextBox txtTimerInfo_TimerID;
        private System.Windows.Forms.Label lblTimerInfo_TicksReceived;
        private System.Windows.Forms.TextBox txtTimerInfo_TicksReceived;
        private System.Windows.Forms.Timer oneSecondTimer;
        private System.Windows.Forms.CheckBox ckbTimerInfo_StartMinimized;
        private System.Windows.Forms.CheckBox checkBox1;
        private System.Windows.Forms.Button button1;
    }
}

