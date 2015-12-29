using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Windows.Forms;

using System.Runtime.InteropServices;

using System.Diagnostics;
using System.IO;
using System.Threading;



namespace MameButtons
{
    public partial class Form1 : Form
    {
        public static string dir = Directory.GetCurrentDirectory();

        Config config = null;

        [DllImport("user32.dll", SetLastError = true)]
        [return: MarshalAs(UnmanagedType.Bool)]
        static extern bool BringWindowToTop(HandleRef hWnd);

        static readonly IntPtr HWND_TOPMOST = new IntPtr(-1);
        static readonly IntPtr HWND_NOTOPMOST = new IntPtr(-2);
        static readonly IntPtr HWND_TOP = new IntPtr(0);
        static readonly IntPtr HWND_BOTTOM = new IntPtr(1);
        const UInt32 SWP_NOSIZE = 0x0001;
        const UInt32 SWP_NOMOVE = 0x0002;
        const UInt32 TOPMOST_FLAGS = 0x0000;//SWP_NOMOVE | SWP_NOSIZE;

        [DllImport("user32.dll")]
        [return: MarshalAs(UnmanagedType.Bool)]
        static extern bool SetWindowPos(IntPtr hWnd, IntPtr hWndInsertAfter, int X, int Y, int cx, int cy, uint uFlags);

//        protected override bool ShowWithoutActivation
//        {
//            get { return true; }
//        }

//const UInt32 WS_EX_LAYERED = 0x00080000;
//const UInt32 WS_EX_NOACTIVATE = 0x08000000;
//const UInt32 WS_EX_TOOLWINDOW = 0x00000080;
//const UInt32 WS_EX_TRANSPARENT = 0x00000020;
//        protected override CreateParams CreateParams
//        {
//            get
//            {
//                CreateParams baseParams = base.CreateParams;

//                baseParams.ExStyle |= (int)(
//                  WS_EX_NOACTIVATE |
//                  WS_EX_TOOLWINDOW);

//                return baseParams;
//            }
//        }


        // // http://stackoverflow.com/questions/156046/show-a-form-without-stealing-focus


        private const int SW_SHOWNOACTIVATE = 4;
 //       private const int HWND_TOPMOST = -1;
        private const uint SWP_NOACTIVATE = 0x0010;

        //[DllImport("user32.dll", EntryPoint = "SetWindowPos")]
        //static extern bool SetWindowPos(
        //     int hWnd,             // Window handle
        //     int hWndInsertAfter,  // Placement-order handle
        //     int X,                // Horizontal position
        //     int Y,                // Vertical position
        //     int cx,               // Width
        //     int cy,               // Height
        //     uint uFlags);         // Window positioning flags

        [DllImport("user32.dll")]
        static extern bool ShowWindow(IntPtr hWnd, int nCmdShow);

        void ShowInactiveTopmost(Form frm)
        {
            ShowWindow(frm.Handle, SW_SHOWNOACTIVATE);

            //SetWindowPos(frm.Handle.ToInt32(), HWND_TOPMOST,frm.Left, frm.Top, frm.Width, frm.Height,SWP_NOACTIVATE);
        }

        public Form1()
        {
            InitializeComponent();

//     this.TopMost = true;

            string tryLevel = Properties.Settings.Default.debugLevel;
            if (!Enum.TryParse(tryLevel, true, out Logger.logLevel))
            {   //logLevel = LogLevels.DEBUG
                Logger.Write(Logger.LogLevels.Error, "Property value: '" + tryLevel + "' is not a valid 'debugLevel'.");
            }

            config = new Config(richTextBox1, lblROM);

            btnTopMost_Click(null, null);
        }

        int cnt = 0;
        private void btnTopMost_Click(object sender, EventArgs e)
        {
            ShowInactiveTopmost(this);

            int x = Properties.Settings.Default.X;
            int y = Properties.Settings.Default.Y;

            //this.DesktopLocation = new Point(x, y);
            //this.Location = new Point(x, y);
            SetWindowPos(this.Handle, HWND_TOPMOST, x, y, 0, 0, SWP_NOACTIVATE);

            string sCnt = cnt.ToString();
            //richTextBox1.AppendText(sCnt);
            richTextBox1.AppendText("=");


            //HandleRef hWnd = Process.GetCurrentProcess().MainWindowHandle;
            //BringWindowToTop(hWnd);
            if (config.hasError())
            {
                cnt++;
            }

            if (++cnt >= 20)
            {
                timer1.Enabled = false;

                if (config.hasError())
                {
                    btnClose_Click(null, null);
                }
            }
        }

        private void btnClose_Click(object sender, EventArgs e)
        {
            //Thread.CurrentThread.Abort();
            Environment.Exit(0);
        }

        private void richTextBox1_MouseDoubleClick(object sender, MouseEventArgs e)
        {
            Environment.Exit(0);
        }

        ToolTip t1 = new ToolTip();
        private void richTextBox1_MouseHover(object sender, EventArgs e)
        {
            t1.Show("'Double CLick'\n to exit.", richTextBox1);
        }
    }
}
