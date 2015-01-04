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
    class Program
    {
        public enum LogLevels { Debug = 1, Info = 2, Warn = 3, Error = 4 };
        public static LogLevels logLevel = LogLevels.Debug;

        private static int j2kPID = -1;
        private static int ledPID = -1;
        private static int btnPID = -1;

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
                Logger.Write(Logger.LogLevels.Error, "Property value: '" + tryLevel + "' is not a valid 'debugLevel'.");
            }

            Logger.Write(Logger.LogLevels.Info, "===========================================================");
            Logger.Write(Logger.LogLevels.Info, "===========================================================");
            Logger.Write(Logger.LogLevels.Info, "===========================================================");
            Logger.Write(Logger.LogLevels.Debug, "Starting");

            if (args.Length > 0)
            {
                string rom = args[0];

                if (rom.Contains(@"."))
                {
                    int pos = rom.IndexOf(@".");
                    rom = rom.Substring(0, pos);
                }

                #region QBW-LED '%rom%'
                // ========================================================================
                // Kill/Start the QBW LED if it is running
                // ========================================================================
                Processes.KillProcess(properties.getProperty("ledKill"));

                // Start the LED based on ROM
                string ledPath = properties.getProperty("ledPath");
                string ledExec = properties.getProperty("ledExec");
                string ledGame = properties.getProperty("ledGame");
                string ledExt = properties.getProperty("ledExt");

                //FileSystem.doesFileExist(ledGame, (rom + ledExt))
                string concat = rom + ledExt;
                if (FileSystem.doesFileExist(ledGame, concat))
                {// Rom LED file found
                    ledPID = Processes.StartExe(ledPath, ledExec, rom + ledExt, ProcessWindowStyle.Minimized, false);
                }
                else
                {// Rom LED file NOT found...using default file.
                    ledPID = Processes.StartExe(ledPath, ledExec, "default" + ledExt, ProcessWindowStyle.Minimized, false);
                }
                #endregion

                #region QBW-Button
                // ========================================================================
                // Kill the QBW Button if it is running
                // ========================================================================
                Processes.KillProcess(properties.getProperty("buttonKill"));

                // Start the Button based on ROM
                string buttonPath = properties.getProperty("buttonPath");
                string buttonExec = properties.getProperty("buttonExec");

                btnPID = Processes.StartExe(buttonPath, buttonExec, rom, ProcessWindowStyle.Normal, false);
                #endregion

                #region Find ROM
                // ========================================================================
                // Find the ROM to execute
                // ========================================================================
                int cnt = 1;
                string mamePath = null;
                string mameExe = null;
                string mameOpt = null;
                bool romFound = false;

                string romPath = "roms";
                string romTest = "roms_untested";

                mameOpt = properties.getProperty(rom + "Opt");
                if (mameOpt == null)
                {
                    mameOpt = properties.getProperty("mameOpt");
                }

                string runPath = null;
                string runExe = null;

                while (properties.getProperty("mame" + cnt) != null)
                {
                    mamePath = properties.getProperty("mame" + cnt);
                    mameExe = properties.getProperty("mame" + cnt + "exe");

                    // Do we have a ZIP file
                    string mPathZip = rom + ".zip";
                    if (FileSystem.doesFileExist(FileSystem.fixDir(mamePath) + romPath, mPathZip, false) ||
                        FileSystem.doesFileExist(FileSystem.fixDir(mamePath) + romTest, mPathZip, false))
                    {
                        if (romFound)
                        {
                            Logger.Write(Logger.LogLevels.Error, "Multi ROM found::");
                            Logger.Write(Logger.LogLevels.Error, "---> " + runPath);
                            Logger.Write(Logger.LogLevels.Error, "---> " + FileSystem.fixDir(mamePath) + mPathZip);
                        }

                        // Use this...
                        runPath = mamePath;
                        runExe = mameExe;

                        romFound = true;
                    }

                    // Do we have a 7Z file
                    string mPath7z = rom + ".7z";
                    if (FileSystem.doesFileExist(FileSystem.fixDir(mamePath) + romPath, mPath7z, false) ||
                        FileSystem.doesFileExist(FileSystem.fixDir(mamePath) + romTest, mPath7z, false)
                        )
                    {
                        if (romFound)
                        {
                            Logger.Write(Logger.LogLevels.Error, ":Multi ROM found::");
                            Logger.Write(Logger.LogLevels.Error, "---> " + runPath);
                            Logger.Write(Logger.LogLevels.Error, "---> " + FileSystem.fixDir(mamePath) + mPath7z);
                        }

                        // Use this...
                        runPath = mamePath;
                        runExe = mameExe;

                        romFound = true;
                        //                        runRom = fixDir(mamePath) + mPath7z;
                    }
                    cnt++;
                }
                #endregion

                #region start MAME
                // ========================================================================
                // MAME run the ROM, or NOT
                // ========================================================================

                if (romFound)
                {
                    // Do we need joystick 2 keyboard???
                    bool joy2key = "true".Equals(properties.getProperty(rom));

                    if (joy2key)
                    {   // Start Joy2Key
                        Logger.Write(Logger.LogLevels.Debug, "Running J2k");

                        string joyPath = properties.getProperty("joyPath");
                        string joyExec = properties.getProperty("joyExec");
                        j2kPID = Processes.StartExe(joyPath, joyExec, rom, ProcessWindowStyle.Minimized, false);
                        Thread.Sleep(2000);
                    }

                    // Run MAME exe
                    Logger.Write(Logger.LogLevels.Info, "-----------------------------------------------------------");
                    Logger.Write(Logger.LogLevels.Info, "MAME: " + runPath + @"\" + runExe + " " + rom + " " + mameOpt);
                    // StartExe(@"C:\MAME\mame_1.38\", "mame.exe", rom, ProcessWindowStyle.Normal, true);
                    //success = StartExe(mamePath, mameExe, rom, ProcessWindowStyle.Normal, true);
                    mamePID = Processes.StartExe(runPath, runExe, rom + " " + mameOpt, ProcessWindowStyle.Maximized, true, false);
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
                        Logger.Write(Logger.LogLevels.Debug, "Killing J2k");
                        Processes.KillProcess(properties.getProperty("joyKill"));
                    }
                }
                else
                {
                    // MessageBox no rom to execute.
                    Logger.Write(Logger.LogLevels.Error, "ROM not found: " + rom);
                    MessageBox.Show("ROM not found '" + rom + "'.", "ERROR", MessageBoxButtons.OK);
                }
                #endregion

                #region QBW-LED 'default'
                // ========================================================================
                // Kill/Start the QBW LED if it is running
                // ========================================================================
                Processes.KillProcess(properties.getProperty("ledKill"));

                // Start using default file.
                ledPID = Processes.StartExe(ledPath, ledExec, "default" + ledExt, ProcessWindowStyle.Normal, false);
                #endregion

                #region Kill QBW-Button
                // ========================================================================
                // Kill the QBW Button if it is running
                // ========================================================================
                Processes.KillProcess(properties.getProperty("buttonKill"));
                #endregion
            }
            else
            {
                // no args past in, no need to start anything......
                // Need a message box here....
                Logger.Write(Logger.LogLevels.Error, "No args provided");
                MessageBox.Show("No args provided!!!", "ERROR", MessageBoxButtons.OK);
            }
            Logger.Write(Logger.LogLevels.Debug, "Ending");
        }
    }
}