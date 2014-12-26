using System;
using System.Diagnostics;
using System.IO;
using System.Text;
using System.Threading;
using System.Collections.Generic;

using System.Linq;
using System.Windows.Forms;

namespace mameStarter
{

    class Properties
    {
        Dictionary<string, string> dictionary = new Dictionary<string, string>();

        public Properties(string propertyFileName)
        {
            int counter = 0;
            string line;

            // Read the file and display it line by line.
            System.IO.StreamReader file = new System.IO.StreamReader(propertyFileName);
            while((line = file.ReadLine()) != null)
            {
                if (line.Length>3 && line.Contains("=") && !line.StartsWith("#"))
                {
                    char[] splitOn = new char[] { '=' };
                    string[] split = line.Split(splitOn);

                    int len = split[0].Length;
                    int start = len + 1; // s/b 12
                    int end = line.Length - start;

                    //ServerName=prod-srv1
                    dictionary.Add(split[0], line.Substring(start, end));

                   Debug.WriteLine (line);
                   counter++;
                }
            }

            file.Close();
        }

        public string getProperty(string property)
        {
            // Order by values.
            // ... Use LINQ to specify sorting by value.
            var items = from pair in dictionary
                        orderby pair.Key ascending
                        select pair;

            // Display results.
            foreach (KeyValuePair<string, string> pair in items)
            {
                //Log("Key: " + pair.Key + "  value: " + pair.Value);
                if (pair.Key.Equals(property))
                    return pair.Value;
            }

            return null;
        }
    }

    class Program
    {
        public enum LogLevels { Debug = 1, Info =2, Warn=3, Error=4 };
        public static LogLevels logLevel = LogLevels.Debug;

        private static int j2kPID = -1;
        private static int ledPID = -1;
        private static int mamePID = -1;
        private static int batPID = -1;

        static void Main(string[] args)
        {
            Properties properties = new Properties("mameStarter.properties");

            // Read logLevel property to set the logging detail...
            //http://msdn.microsoft.com/en-us/library/dd991317%28v=vs.110%29.aspx
            string tryLevel = properties.getProperty("debugLevel");
            if (!Enum.TryParse(tryLevel, true, out logLevel))
            {   //logLevel = LogLevels.DEBUG
                Logger(LogLevels.Error, "Property value: '" + tryLevel +"' is not a valid 'debugLevel'.");
            }

            //bool success = true;
            Logger(LogLevels.Info, "===========================================================");
            Logger(LogLevels.Info, "===========================================================");
            Logger(LogLevels.Info, "===========================================================");
            Logger(LogLevels.Debug, "Starting");

            if (args.Length > 0)
            {
                string rom = args[0];

                if (rom.EndsWith(@"."))
                    rom = rom.Substring(0,rom.Length -1);

                // ========================================================================
                // Kill the QBW LED if it is running
                // ========================================================================
                KillProcess(properties.getProperty("ledKill"));

                // Start the LED based on ROM
                string ledPath = properties.getProperty("ledPath");
                string ledExec = properties.getProperty("ledExec");
                string ledGame = properties.getProperty("ledGame");
                string ledExt = properties.getProperty("ledExt");

                if (doesFileExist(ledGame, rom + ledExt))
                {// Rom LED file found
                    ledPID = StartExe(ledPath, ledExec, rom + ledExt, ProcessWindowStyle.Minimized, false);
                }
                else
                {// Rom LED file NOT found...using default file.
                    ledPID = StartExe(ledPath, ledExec, "default" + ledExt, ProcessWindowStyle.Minimized, false);
                }

                // ========================================================================
                // Find the ROM to execute
                // ========================================================================
                int cnt = 1;
                string mamePath = null;
                string mameExe = null;
                string mameOpt = null;
                bool romFound = false;
 //               string runRom = null;
                string romPath = "roms";

                mameOpt = properties.getProperty("mameOpt");

                string runPath = null;
                string runExe = null;

                while (properties.getProperty("mame" + cnt) != null)
                {
                    mamePath = properties.getProperty("mame" + cnt);
                    mameExe = properties.getProperty("mame" + cnt + "exe");

                    // Do we have a ZIP file
                    string mPathZip = rom + ".zip";
                    if (doesFileExist(fixDir(mamePath) + romPath, mPathZip, false))
                    {
                        if (romFound)
                        {
                            Logger(LogLevels.Error, "Multi ROM found::");
//                            Logger(LogLevels.Error, "---> " + runRom);
                            Logger(LogLevels.Error, "---> " + fixDir(mamePath) + mPathZip);
                        }

                        // Use this...
                        runPath = mamePath;
                        runExe = mameExe;

                        romFound = true;
 //                       runRom = fixDir(mamePath) + mPathZip;
                    }

                    // Do we have a 7Z file
                    string mPath7z = rom + ".7z";
                    if (doesFileExist(fixDir(mamePath) + romPath, mPath7z, false))
                    {
                        if (romFound)
                        {
                            Logger(LogLevels.Error, ":Multi ROM found::");
 //                           Logger(LogLevels.Error, "---> " + runRom);
                            Logger(LogLevels.Error, "---> " + fixDir(mamePath) + mPath7z);
                        }

                        // Use this...
                        runPath = mamePath;
                        runExe = mameExe;

                        romFound = true;
//                        runRom = fixDir(mamePath) + mPath7z;
                    }
                    cnt++;
                }

                //mamePath = tempPath;
                //mameExe = tempExe;

                // ========================================================================
                // MAME run the ROM, or NOT
                // ========================================================================

                if (romFound)
                {
                    // Do we need joystick 2 keyboard???
                    bool joy2key = "true".Equals(properties.getProperty(rom));

                    if (joy2key)
                    {   // Start Joy2Key
                        Logger(LogLevels.Debug, "Running J2k");

                        string joyPath = properties.getProperty("joyPath");
                        string joyExec = properties.getProperty("joyExec");
                        j2kPID = StartExe(joyPath, joyExec, rom, ProcessWindowStyle.Minimized, false);
                        Thread.Sleep(2000);
                    }

                    // Run MAME exe
                    Logger(LogLevels.Info, "-----------------------------------------------------------");
                    Logger(LogLevels.Info, "MAME: " + runPath + @"\" + runExe + " " + rom + " " + mameOpt);
                    // StartExe(@"C:\MAME\mame_1.38\", "mame.exe", rom, ProcessWindowStyle.Normal, true);
                    //success = StartExe(mamePath, mameExe, rom, ProcessWindowStyle.Normal, true);
                    mamePID = StartExe(runPath, runExe, rom + " " + mameOpt, ProcessWindowStyle.Maximized, true);
                    //if (!success)
                    if (mamePID == -1)
                    {
                        MessageBox.Show("Failed running MAME '" + rom + "'." + "\n" +
                            "\nPath: " + runPath +
                            "\nEXE : " + runExe +
                            "\nROM : " + rom +
                            "\n\nmameOpt : " + mameOpt
                            , "ERROR", MessageBoxButtons.OK);
                    }
                    // Start from CMD prompt
                    //StartExe(@"C:\",@"C:\Windows\System32","cmd.exe",@"/c " + fixDir(mameBatch) + rom + ".bat", ProcessWindowStyle.Normal, true);

                    if (joy2key)
                    {
                        if (j2kPID != -1)
                        {

                        }
                        // Kill Joy2Key
                        Logger(LogLevels.Debug, "Killing J2k");
                        KillProcess(properties.getProperty("joyKill"));
                    }
                }
                else
                {
                    // MessageBox no rom to execute.
                    Logger(LogLevels.Error, "ROM not found: " + rom);
                    MessageBox.Show("ROM not found '" + rom + "'.", "ERROR", MessageBoxButtons.OK);
                }


                // ========================================================================
                // Kill the QBW LED if it is running
                // ========================================================================
                KillProcess(properties.getProperty("ledKill"));

                // Start using default file.
                ledPID = StartExe(ledPath, ledExec, "default" + ledExt, ProcessWindowStyle.Normal, false);
            }
            else
            {
                // no args past in, no need to start anything......
                // Need a message box here....
                Logger(LogLevels.Error,"No args provided");
                MessageBox.Show("No args provided!!!", "ERROR", MessageBoxButtons.OK);
            }
                Logger(LogLevels.Debug,"Ending");
        }

        //  taskkill /f /fi "USERNAME eq NT AUTHORITY\SYSTEM" /im notepad.exe 
        //  taskkill /f /im JoyToKey.exe
        static void KillProcess(string arg)
        {
            // taskkill /F /FI "IMAGENAME eq QBW*"
            //StartExe(@"C:\Windows\System32", "taskkill.exe", "/T /F /FI \"" + fullName + "\"", ProcessWindowStyle.Normal, true);
            StartExe(@"C:\Windows\System32", "taskkill.exe" , arg, ProcessWindowStyle.Normal, true);
        }

        /// <summary>
        /// Get directory list.
        /// </summary>
        static void getDirectoryList()
        {
            try
            {
                // Only get files that begin with the letter "c." 
                string[] dirs = Directory.GetFiles(@"C:\MAME\mame_1.38\roms\", "*.zip");
                Console.WriteLine("The number of files starting with c is {0}.", dirs.Length);
                foreach (string dir in dirs)
                {
                    Logger(LogLevels.Debug,  dir);
                }
            }
            catch (Exception e)
            {
                Logger(LogLevels.Error, "The process failed: " + e.ToString());
            }
        }


        /// <summary>
        /// Check to see if file exists.
        /// </summary>
        static bool doesFileExist(string path, string fileName)
        {
            return doesFileExist(path, fileName, true);
        }


        static bool doesFileExist(string path, string fileName, bool showNotFound)
        {
            path = fixDir(path);
            string curFile = path + fileName;
            try
            {
                if (File.Exists(curFile))
                {
                    return true;
                }
                else
                {
                    if (showNotFound)
                    {
                        Logger(LogLevels.Warn, "File does not exist: " + curFile);
                    }
                    return false;
                }
            }
            catch (Exception e)
            {
                Logger(LogLevels.Error, "oops" + e.ToString());
                return false;
            }
        }

        // =========================================================================================
        // =========================================================================================
        // =========================================================================================
        // =========================================================================================
        public static string fixDir(string dir)
        {
            if (dir.EndsWith(@"\"))
            {
                dir = dir.Substring(0, dir.Length - 1);
            }
            dir += @"\";
            return dir;
        }


        //public static bool StartExe(string dir, string exe, string args, ProcessWindowStyle pws, bool wait)
        public static int StartExe(string dir, string exe, string args, ProcessWindowStyle pws, bool wait)
        {
            return StartExe(dir, dir, exe, args, pws, wait);
        }


        //StartExe1(@"C:\MAME\mame_1.38\", @"C:\MAME\mame_1.38\", "qbert" + ".bat", "", ProcessWindowStyle.Normal, true);
        //public static bool StartExe(string workdir, string exedir, string exe, string args, ProcessWindowStyle pws, bool wait)
        public static int StartExe(string workdir, string exedir, string exe, string args, ProcessWindowStyle pws, bool wait)
        {
           // bool success = true;
            int pid = -1;

            //  http://stackoverflow.com/questions/139593/processstartinfo-hanging-on-waitforexit-why
            workdir = fixDir(workdir);
            exedir = fixDir(exedir);

            Logger(LogLevels.Debug,"WorkDir: " + workdir);
            Logger(LogLevels.Debug, "Running: " + exedir);
            Logger(LogLevels.Debug, "Exe    : " + exe);
            Logger(LogLevels.Debug, "ARGS   : " + args);
            Logger(LogLevels.Debug, "Wait   : " + wait.ToString());

            ProcessStartInfo startInfo = new ProcessStartInfo();
            Process process = new Process();

            try
            {
                if (pws == null)
                {
                    pws = ProcessWindowStyle.Normal;
                }

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

                if (wait)
                {
                    process.BeginOutputReadLine();
                    process.BeginErrorReadLine();
                    process.WaitForExit();

                    Logger(LogLevels.Info, "Exit code :" + process.ExitCode);
                }
            }
            catch (Exception e)
            {
//                success = false;

                Logger(LogLevels.Error, e.Message);
                Logger(LogLevels.Error, process.StartInfo.FileName.ToString());
                Logger(LogLevels.Error, process.StartInfo.WorkingDirectory.ToString());
                Logger(LogLevels.Error, e.StackTrace);
            }

            //return success;
            return pid;
        }
        
        static void CaptureOutput(object sender, DataReceivedEventArgs e)
        {
            Logger(LogLevels.Info, e.Data);
        }

        static void CaptureError(object sender, DataReceivedEventArgs e)
        {
            Logger(LogLevels.Error, e.Data);
        }

        private static string sPathName = @".\";
        private static string sLogFormat;
        private static string sErrorTime;

        private static object oLock = new object();

        public static void Logger(LogLevels level, string sErrMsg)
        {
            
            lock (oLock)
            {
                if (sErrMsg != null && sErrMsg.Length > 0)
                {
                    if (level.CompareTo(logLevel) >= 0)
                    {
                        CreateFileVars();

                        StreamWriter sw = new StreamWriter(sPathName + sErrorTime, true);
                        sw.WriteLine(sLogFormat + level.ToString() + " -- " + sErrMsg);
                        sw.Flush();
                        sw.Close();

                        Debug.WriteLine(sErrMsg);
                    }
                }
            }
           // oLock = null;
        }

        public static void CreateFileVars()
        {
            //sLogFormat used to create log files format :
            // dd/mm/yyyy hh:mm:ss AM/PM ==> Log Message
            //sLogFormat = DateTime.Now.ToShortDateString().ToString()+" "+DateTime.Now.ToLongTimeString().ToString()+" ==> ";
            sLogFormat = DateTime.Now.ToString("yyyy/MM/dd HH:mm:ss.fff ::: ");
            //this variable used to create log filename format "
            //for example filename : ErrorLogYYYYMMDD
            string sYear    = DateTime.Now.Year.ToString();
            string sMonth    = DateTime.Now.Month.ToString();
            string sDay    = DateTime.Now.Day.ToString();
            sErrorTime = "mameStarter." + sYear+sMonth+sDay + ".log";
        }
    }
}