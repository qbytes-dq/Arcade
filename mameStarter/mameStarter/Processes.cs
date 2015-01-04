using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Diagnostics;
using System.Runtime.InteropServices;

namespace mameStarter
{
    public class Processes
    {
       // [System.Runtime.InteropServices.DllImport("user32.dll")]
       // public static extern bool SetForegroundWindow(IntPtr hWnd); 

        [DllImport("user32.dll")]
        internal static extern IntPtr SetForegroundWindow(IntPtr hWnd);

        [DllImport("user32.dll")]
        internal static extern bool ShowWindow(IntPtr hWnd, int nCmdShow);

        [System.Runtime.InteropServices.DllImport("user32.dll")]
        public static extern void SwitchToThisWindow(IntPtr hWnd, bool fAltTab);
        

        //  taskkill /f /fi "USERNAME eq NT AUTHORITY\SYSTEM" /im notepad.exe 
        //  taskkill /f /im JoyToKey.exe
        public static void KillProcess(string arg)
        {
            // taskkill /F /FI "IMAGENAME eq QBW*"
            //StartExe(@"C:\Windows\System32", "taskkill.exe", "/T /F /FI \"" + fullName + "\"", ProcessWindowStyle.Normal, true);
            StartExe(@"C:\Windows\System32", "taskkill.exe", arg, ProcessWindowStyle.Normal, true);
        }

        public static int StartExe(string dir, string exe, string args, ProcessWindowStyle pws, bool wait)
        {
            return StartExe(dir, dir, exe, args, pws, wait, false);
        }

        public static int StartExe(string dir, string exe, string args, ProcessWindowStyle pws, bool wait, bool focus)
        {
            return StartExe(dir, dir, exe, args, pws, wait, focus);
        }

        public static int StartExe(string workdir, string exedir, string exe, string args, ProcessWindowStyle pws, bool wait, bool focus)
        {
            int pid = -1;

            //  http://stackoverflow.com/questions/139593/processstartinfo-hanging-on-waitforexit-why
            workdir = FileSystem.fixDir(workdir);
            exedir = FileSystem.fixDir(exedir);

            Logger.Write(Logger.LogLevels.Debug, "WorkDir: " + workdir);
            Logger.Write(Logger.LogLevels.Debug, "Running: " + exedir);
            Logger.Write(Logger.LogLevels.Debug, "Exe    : " + exe);
            Logger.Write(Logger.LogLevels.Debug, "ARGS   : " + args);
            Logger.Write(Logger.LogLevels.Debug, "Wait   : " + wait.ToString());

            ProcessStartInfo startInfo = new ProcessStartInfo();
            Process process = new Process();

            try
            {
                //ProcessStartInfo startInfo = new ProcessStartInfo();

                startInfo.WorkingDirectory = workdir;// @"C:\MAME\mame_1.38\";

                startInfo.FileName = exedir + exe;//@"C:\MAME\mame_1.38\qbert.bat";
                startInfo.Arguments = args;

                startInfo.UseShellExecute = false;
                startInfo.RedirectStandardOutput = true;
                startInfo.RedirectStandardError = true;

                //====================================
                //====================================
                //====================================
                process.StartInfo.ErrorDialog = true;
                process.StartInfo.WindowStyle = pws;
                process.StartInfo.ErrorDialog = false;
                process.StartInfo.CreateNoWindow = true;
                //====================================
                //====================================
                //====================================

                //Process process = new Process();
                process.StartInfo = startInfo;
                process.OutputDataReceived += CaptureOutput;
                process.ErrorDataReceived += CaptureError;

                process.Start();

                pid = process.Id;

                if (focus)
                {

                    // name sure it has focus.
                    //SetForegroundWindow(process.MainWindowHandle);
                    //SwitchToThisWindow(process.MainWindowHandle, true);
                    SetForegroundWindow(process.MainWindowHandle);
                    
                    
                    //ShowWindow(process.MainWindowHandle,0);
                }

                if (wait)
                {
                    process.BeginOutputReadLine();
                    process.BeginErrorReadLine();


                    process.WaitForExit();

                    Logger.Write(Logger.LogLevels.Info, "Exit code :" + process.ExitCode);
                }
            }
            catch (Exception e)
            {
                Logger.Write(Logger.LogLevels.Error, e.Message);
                Logger.Write(Logger.LogLevels.Error, process.StartInfo.FileName.ToString());
                Logger.Write(Logger.LogLevels.Error, process.StartInfo.WorkingDirectory.ToString());
                Logger.Write(Logger.LogLevels.Error, e.StackTrace);
            }

            return pid;
        }

        public static void CaptureOutput(object sender, DataReceivedEventArgs e)
        {
            Logger.Write(Logger.LogLevels.Info, e.Data);
        }

        public static void CaptureError(object sender, DataReceivedEventArgs e)
        {
            Logger.Write(Logger.LogLevels.Error, e.Data);
        }
    }
}

/*

        [DllImport("user32.dll")]
        internal static extern IntPtr SetForegroundWindow(IntPtr hWnd);

        [DllImport("user32.dll")]
        internal static extern bool ShowWindow(IntPtr hWnd, int nCmdShow);
        ... 
        Process currentProcess = Process.GetCurrentProcess();
        IntPtr hWnd = currentProcess.MainWindowHandle;
        if (hWnd != IntPtr.Zero)
        {
            SetForegroundWindow(hWnd);
            ShowWindow(hWnd, User32.SW_MAXIMIZE);
        }
 * 
 * 
 *  
    [DllImport("coredll.dll")]
        static extern bool SetForegroundWindow (IntPtr hWnd);

         private void BringToFront(Process pTemp)
         {
           SetForegroundWindow(pTemp.MainWindowHandle);
         }

*/