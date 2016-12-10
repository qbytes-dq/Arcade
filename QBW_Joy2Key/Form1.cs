using System;
using System.Windows.Forms;
using System.Diagnostics;

namespace Timers
{

    public class Form1 : System.Windows.Forms.Form
	{
        private TimerAPI timerAPI;
        public delegate void TimerAPI_Delegate();
        public TimerAPI_Delegate myDelegate;

        private uint TimerAPI_Id;
        private int TimerAPI_Cnt;

        private System.Windows.Forms.Label lblUpdatesPerSec;
		private System.Windows.Forms.NumericUpDown numberUpPerSecond;
		private System.Windows.Forms.Label lblCallBackTimer;
		private System.Windows.Forms.Label lblTicksReceived;
		private System.Windows.Forms.StatusBar statusBar1;
		private System.Windows.Forms.Label lblTimerID;
        private LinkLabel lnkStart;
        private LinkLabel lnkStop;
        private Label lblTicksReceivedCnt;
        private Label lblTimerIDNumber;
        private Label lblInterval;
        private System.ComponentModel.Container components = null;

		public Form1()
		{
			InitializeComponent();
            myDelegate = new TimerAPI_Delegate(TimerAPI_Tick);
        }

        protected override void Dispose( bool disposing )
		{
			if( disposing )
			{
				if (components != null) 
				{
					components.Dispose();
				}
			}
			base.Dispose( disposing );
		}

		#region Windows Form Designer generated code
		
		private void InitializeComponent()
		{
            this.lblUpdatesPerSec = new System.Windows.Forms.Label();
            this.numberUpPerSecond = new System.Windows.Forms.NumericUpDown();
            this.lblCallBackTimer = new System.Windows.Forms.Label();
            this.lblTicksReceived = new System.Windows.Forms.Label();
            this.statusBar1 = new System.Windows.Forms.StatusBar();
            this.lblTimerID = new System.Windows.Forms.Label();
            this.lnkStart = new System.Windows.Forms.LinkLabel();
            this.lnkStop = new System.Windows.Forms.LinkLabel();
            this.lblTicksReceivedCnt = new System.Windows.Forms.Label();
            this.lblTimerIDNumber = new System.Windows.Forms.Label();
            this.lblInterval = new System.Windows.Forms.Label();
            ((System.ComponentModel.ISupportInitialize)(this.numberUpPerSecond)).BeginInit();
            this.SuspendLayout();
            // 
            // lblUpdatesPerSec
            // 
            this.lblUpdatesPerSec.Location = new System.Drawing.Point(7, 94);
            this.lblUpdatesPerSec.Name = "lblUpdatesPerSec";
            this.lblUpdatesPerSec.Size = new System.Drawing.Size(165, 20);
            this.lblUpdatesPerSec.TabIndex = 13;
            this.lblUpdatesPerSec.Text = "Updates per second (Hz)";
            this.lblUpdatesPerSec.TextAlign = System.Drawing.ContentAlignment.MiddleRight;
            // 
            // numberUpPerSecond
            // 
            this.numberUpPerSecond.BorderStyle = System.Windows.Forms.BorderStyle.FixedSingle;
            this.numberUpPerSecond.Location = new System.Drawing.Point(178, 94);
            this.numberUpPerSecond.Minimum = new decimal(new int[] {
            1,
            0,
            0,
            0});
            this.numberUpPerSecond.Name = "numberUpPerSecond";
            this.numberUpPerSecond.Size = new System.Drawing.Size(59, 20);
            this.numberUpPerSecond.TabIndex = 11;
            this.numberUpPerSecond.Value = new decimal(new int[] {
            40,
            0,
            0,
            0});
            // 
            // lblCallBackTimer
            // 
            this.lblCallBackTimer.Location = new System.Drawing.Point(16, 8);
            this.lblCallBackTimer.Name = "lblCallBackTimer";
            this.lblCallBackTimer.Size = new System.Drawing.Size(120, 16);
            this.lblCallBackTimer.TabIndex = 18;
            this.lblCallBackTimer.Text = "CallBack Timer";
            // 
            // lblTicksReceived
            // 
            this.lblTicksReceived.Location = new System.Drawing.Point(136, 8);
            this.lblTicksReceived.Name = "lblTicksReceived";
            this.lblTicksReceived.Size = new System.Drawing.Size(96, 16);
            this.lblTicksReceived.TabIndex = 19;
            this.lblTicksReceived.Text = "Ticks Received";
            // 
            // statusBar1
            // 
            this.statusBar1.Location = new System.Drawing.Point(0, 205);
            this.statusBar1.Name = "statusBar1";
            this.statusBar1.Size = new System.Drawing.Size(368, 16);
            this.statusBar1.TabIndex = 20;
            // 
            // lblTimerID
            // 
            this.lblTimerID.Location = new System.Drawing.Point(256, 8);
            this.lblTimerID.Name = "lblTimerID";
            this.lblTimerID.Size = new System.Drawing.Size(96, 16);
            this.lblTimerID.TabIndex = 19;
            this.lblTimerID.Text = "Timer ID";
            // 
            // lnkStart
            // 
            this.lnkStart.Location = new System.Drawing.Point(16, 52);
            this.lnkStart.Name = "lnkStart";
            this.lnkStart.Size = new System.Drawing.Size(40, 16);
            this.lnkStart.TabIndex = 22;
            this.lnkStart.TabStop = true;
            this.lnkStart.Text = "Start";
            this.lnkStart.LinkClicked += new System.Windows.Forms.LinkLabelLinkClickedEventHandler(this.lnkStart_LinkClicked);
            // 
            // lnkStop
            // 
            this.lnkStop.Location = new System.Drawing.Point(88, 52);
            this.lnkStop.Name = "lnkStop";
            this.lnkStop.Size = new System.Drawing.Size(40, 16);
            this.lnkStop.TabIndex = 23;
            this.lnkStop.TabStop = true;
            this.lnkStop.Text = "Stop";
            this.lnkStop.LinkClicked += new System.Windows.Forms.LinkLabelLinkClickedEventHandler(this.lnkStop_LinkClicked);
            // 
            // lblTicksReceivedCnt
            // 
            this.lblTicksReceivedCnt.Location = new System.Drawing.Point(136, 54);
            this.lblTicksReceivedCnt.Name = "lblTicksReceivedCnt";
            this.lblTicksReceivedCnt.Size = new System.Drawing.Size(96, 16);
            this.lblTicksReceivedCnt.TabIndex = 25;
            this.lblTicksReceivedCnt.Text = "0";
            // 
            // lblTimerIDNumber
            // 
            this.lblTimerIDNumber.Location = new System.Drawing.Point(256, 54);
            this.lblTimerIDNumber.Name = "lblTimerIDNumber";
            this.lblTimerIDNumber.Size = new System.Drawing.Size(96, 16);
            this.lblTimerIDNumber.TabIndex = 26;
            this.lblTimerIDNumber.Text = "0";
            // 
            // lblInterval
            // 
            this.lblInterval.Location = new System.Drawing.Point(243, 96);
            this.lblInterval.Name = "lblInterval";
            this.lblInterval.Size = new System.Drawing.Size(113, 18);
            this.lblInterval.TabIndex = 27;
            this.lblInterval.Text = "Interval (Ms)";
            this.lblInterval.TextAlign = System.Drawing.ContentAlignment.MiddleRight;
            // 
            // Form1
            // 
            this.AutoScaleBaseSize = new System.Drawing.Size(5, 13);
            this.ClientSize = new System.Drawing.Size(368, 221);
            this.Controls.Add(this.lblInterval);
            this.Controls.Add(this.lnkStart);
            this.Controls.Add(this.lnkStop);
            this.Controls.Add(this.lblTicksReceivedCnt);
            this.Controls.Add(this.lblTimerIDNumber);
            this.Controls.Add(this.statusBar1);
            this.Controls.Add(this.lblTicksReceived);
            this.Controls.Add(this.lblCallBackTimer);
            this.Controls.Add(this.lblUpdatesPerSec);
            this.Controls.Add(this.numberUpPerSecond);
            this.Controls.Add(this.lblTimerID);
            this.Name = "Form1";
            this.StartPosition = System.Windows.Forms.FormStartPosition.CenterScreen;
            this.Text = "QBW Joy 2 Key";
            this.FormClosing += new System.Windows.Forms.FormClosingEventHandler(this.Form1_FormClosing);
            ((System.ComponentModel.ISupportInitialize)(this.numberUpPerSecond)).EndInit();
            this.ResumeLayout(false);

		}
		#endregion

		[STAThread]
		static void Main() 
		{
			Application.Run(new Form1());
		}

        private void Form1_FormClosing(object sender, FormClosingEventArgs e)
        {
            lnkStop_LinkClicked(null, null);
            Debug.WriteLine("Form CLosing!!!");
        }

        private void lnkStart_LinkClicked(object sender, LinkLabelLinkClickedEventArgs e)
        {
            // Make sure it is stoped
            lnkStop_LinkClicked(null, null);

            // Reset local timer values
            this.TimerAPI_Cnt = 0;
            this.lblTicksReceivedCnt.Text = "0";

            // Create a new timer and start it
            timerAPI = new TimerAPI(this);

            uint hz = (uint)this.numberUpPerSecond.Value;
            uint interval = (uint)((1f / hz) * 1000);
            lblInterval.Text = interval + " mS Interval";
            TimerAPI_Id = timerAPI.Start(interval, true);
            lblTimerIDNumber.Text = TimerAPI_Id.ToString();
        }

        private void lnkStop_LinkClicked(object sender, LinkLabelLinkClickedEventArgs e)
        {
            if (timerAPI != null)
            {
                timerAPI.Stop();
            }
        }

        public void TimerAPI_Tick()
        {
            TimerAPI_Cnt++;
            this.lblTicksReceivedCnt.Text = this.TimerAPI_Cnt.ToString();
        }
    }
}
