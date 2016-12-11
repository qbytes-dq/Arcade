using System;
using System.Windows.Forms;

namespace QBW_Joy2Key
{
    public partial class Form1 : Form
    {
        // Required for TimerAPI
        private TimerAPI timerAPI;
        public delegate void TimerAPI_Delegate();
        public TimerAPI_Delegate myDelegate;

        public Form1()
        {
            InitializeComponent();

            // Disable the Maximize Box
            MaximizeBox = false;
            if (this.ckbTimerInfo_StartMinimized.Checked)
            {
                this.WindowState = FormWindowState.Minimized;
            }

            // Required for TimerAPI
            this.myDelegate = new TimerAPI_Delegate(TimerAPI_Tick);
            this.TimerAPI_Start();
            this.oneSecondTimer.Enabled = true;
        }

        // ===============================================================
        // ===============================================================
        // ===============================================================
        // Required for TimerAPI
        // ===============================================================
        // ===============================================================
        // ===============================================================
        private uint timerAPI_Id;
        private int timerAPI_Cnt;
        private int timer_Cnt;

        private void TimerAPI_Start()
        {
            // Make sure it is stoped
            this.TimerAPI_Stop();

            // Reset local timer values
            this.timerAPI_Cnt = 0;
            this.txtTimerInfo_TicksReceived.Text = "0";

            // Create a new timer and start it
            this.timerAPI = new TimerAPI(this);

            uint hz = (uint)this.numTimerInfo_Hz.Value;
            uint interval = (uint)((1f / hz) * 1000);
            this.txtTimerInfo_Interval.Text = interval.ToString();
            this.timerAPI_Id = timerAPI.Start(interval, true);
            this.txtTimerInfo_Running.Text = "True";

            this.txtTimerInfo_TimerID.Text = timerAPI_Id.ToString();

            Application.DoEvents();
        }

        private void TimerAPI_Stop()
        {
            if (this.timerAPI != null)
            {
                this.timerAPI.Stop();
            }
            this.txtTimerInfo_Running.Text = "False";
            Application.DoEvents();
        }

        public void TimerAPI_Tick()
        {
            this.timerAPI_Cnt++;
            this.timer_Cnt++;
            this.txtTimerInfo_TicksReceived.Text = this.timerAPI_Cnt.ToString();
        }
        
        private void btnTimerInfo_SaveTimerValue_Click(object sender, EventArgs e)
        {
            this.TimerAPI_Stop();
            this.TimerAPI_Start();

            //TODO: Will also need to save the data here
        }

        private void oneSecondTimer_Tick(object sender, EventArgs e)
        {
            if (this.WindowState != FormWindowState.Minimized)
            {
                if (this.tabControl.SelectedTab == this.tabControl.TabPages["tabGameSystem"])
                {
                    double actualInt = 0;

                    if (timer_Cnt > 0)
                    {
                        actualInt = (1.0f / (float)this.timer_Cnt) * 1000;
                    }

                    // Show results
                    this.txtTimerInfo_ActualHz.Text = this.timer_Cnt.ToString();
                    this.txtTimerInfo_ActualInterval.Text = actualInt.ToString();
                }
            }
            // Reset for next run.
            this.timer_Cnt = 0;
        }

        private void Form1_FormClosing(object sender, FormClosingEventArgs e)
        {
            this.TimerAPI_Stop();
            this.oneSecondTimer.Enabled = true;
        }
    }
}
