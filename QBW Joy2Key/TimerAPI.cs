﻿using System;
using System.Collections.Generic;
using System.Diagnostics;
using System.Linq;
using System.Runtime.InteropServices;
using System.Text;
using System.Threading.Tasks;

namespace QBW_Joy2Key
{
    public class TimerAPI : IDisposable
    {
        // Big help here:
        // https://msdn.microsoft.com/en-us/library/zyzhdc6b(v=vs.110).aspx

        Form1 myForm1;

        #region Winmm
        //Lib API declarations
        [DllImport("Winmm.dll", CharSet = CharSet.Auto)]
        static extern uint timeSetEvent(uint uDelay, uint uResolution, TimerCallback lpTimeProc, UIntPtr dwUser, uint fuEvent);

        [DllImport("Winmm.dll", CharSet = CharSet.Auto)]
        static extern uint timeKillEvent(uint uTimerID);
        #endregion

        //Timer type definitions
        [Flags]
        public enum fuEvent : uint
        {
            TIME_ONESHOT = 0,      //Event occurs once, after uDelay milliseconds. 
            TIME_PERIODIC = 1,
            TIME_CALLBACK_FUNCTION = 0x0000,  /* callback is function */
                                              //TIME_CALLBACK_EVENT_SET = 0x0010, /* callback is event - use SetEvent */
                                              //TIME_CALLBACK_EVENT_PULSE = 0x0020  /* callback is event - use PulseEvent */
        }

        //Delegate definition for the API callback
        delegate void TimerCallback(uint uTimerID, uint uMsg, UIntPtr dwUser, UIntPtr dw1, UIntPtr dw2);

        //IDisposable code
        private bool disposed = false;

        public void Dispose()
        {
            Dispose(true);
            GC.SuppressFinalize(this);
        }

        private void Dispose(bool disposing)
        {
            if (!this.disposed)
            {
                if (disposing)
                {
                    Stop();
                }
            }
            disposed = true;
        }

        ~TimerAPI()
        {
            Dispose(false);
        }

        /// <summary>
        /// The current timer instance ID
        /// </summary>
        uint id = 0;

        /// <summary>
        /// The callback used by the the API
        /// </summary>
        TimerCallback thisCB;

        /// <summary>
        /// The timer elapsed event 
        /// </summary>
        public event EventHandler Timer;
        protected virtual void OnTimer(EventArgs e)
        {
            if (Timer != null)
            {
                Timer(this, e);
            }

            try
            {
                myForm1.Invoke(myForm1.myDelegate);
            }
            catch (Exception ex)
            {
                Debug.WriteLine("Exit Excepiton: " + ex.Message);
            }
        }

        public TimerAPI(Form1 myForm1)
        {
            //Initialize the API callback
            thisCB = CBFunc;
            this.myForm1 = myForm1;
        }

        /// <summary>
        /// Stop the current timer instance (if any)
        /// </summary>
        public void Stop()
        {
            lock (this)
            {
                if (id != 0)
                {
                    timeKillEvent(id);
                    Debug.WriteLine("TimerAPI " + id.ToString() + " stopped");
                    id = 0;
                }
            }
        }

        /// <summary>
        /// Start a timer instance
        /// </summary>
        /// <param name="ms">Timer interval in milliseconds</param>
        /// <param name="repeat">If true sets a repetitive event, otherwise sets a one-shot</param>
        public uint Start(uint ms, bool repeat)
        {
            //Kill any existing timer
            Stop();

            //Set the timer type flags
            fuEvent f = fuEvent.TIME_CALLBACK_FUNCTION | (repeat ? fuEvent.TIME_PERIODIC : fuEvent.TIME_ONESHOT);

            lock (this)
            {
                id = timeSetEvent(ms, 0, thisCB, UIntPtr.Zero, (uint)f);
                if (id == 0)
                {
                    throw new Exception("timeSetEvent error");
                }
                Debug.WriteLine("TimerAPI " + id.ToString() + " started");
            }
            return this.id;
        }

        void CBFunc(uint uTimerID, uint uMsg, UIntPtr dwUser, UIntPtr dw1, UIntPtr dw2)
        {
            //Callback from the TimerAPI API that fires the Timer event. Note we are in a different thread here
            OnTimer(new EventArgs());
        }
    }
}
