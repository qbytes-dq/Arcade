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

        public static string dir = Directory.GetCurrentDirectory();

        private static int j2kPID = -1;
        private static int ledPID = -1;
        private static int btnPID = -1;

        private static int mamePID = -1;
 //       private static int batPID = -1;

        static void Main(string[] args)
        {
            try
            {
                if (args.Length < 2)
                {
                    throw new Exception("USAGE: mameStarter %rom% -system=%system%");
                }

                Properties starterProperties = new Properties("mameStarter.properties");
                string tryLevel = starterProperties.getProperty("debugLevel");

                // Read logLevel property to set the logging detail...
                //http://msdn.microsoft.com/en-us/library/dd991317%28v=vs.110%29.aspx
                tryLevel = starterProperties.getProperty("debugLevel");
                if (!Enum.TryParse(tryLevel, true, out logLevel))
                {   //logLevel = LogLevels.DEBUG
                    Logger.Write(Logger.LogLevels.Error, "Property value: '" + tryLevel + "' is not a valid 'debugLevel'.");
                }

                Logger.Write(Logger.LogLevels.Info, "===========================================================");
                Logger.Write(Logger.LogLevels.Info, "===========================================================");
                Logger.Write(Logger.LogLevels.Info, "===========================================================");
                Logger.Write(Logger.LogLevels.Debug, "Starting");

                string romIn = "";
                string rom = "";
                string ext = "";

                // Concatenate all args to a single string
                //string rom = args[0];
                for (int lpx = 0; lpx < args.Length; lpx++)
                {
                    romIn += args[lpx];
                    if ((lpx + 1) < args.Length)
                        romIn += " ";
                }

                string system = " :system=";
                int systemPos = romIn.LastIndexOf(system);
                if (systemPos < 0)
                {
                    throw new Exception("System Type missing");
                }
                string systemType = romIn.Substring(systemPos + system.Length); ;
                //string dir = Directory.GetCurrentDirectory();
                //Directory.SetCurrentDirectory(dir + "\\" + systemType);
                //Properties gameProperties = new Properties("mameStarter.properties");
                Directory.SetCurrentDirectory(dir + @"\systems");
                Properties gameProperties = new Properties( systemType + ".properties");


                romIn = (romIn.Substring(0,systemPos));

                int pos = romIn.LastIndexOf(@".");
                if (pos < 0)
                {
                    throw new Exception("ROM extension missing");
                }

                rom = romIn.Substring(0, pos);
                ext = romIn.Substring(pos + 1);

                string mPathZip = rom + "." + ext;


                #region QBW-LED '%rom%'
                // ========================================================================
                // Kill HyperSpin LED
                // Start the Game LED
                // ========================================================================
                Processes.KillProcess(starterProperties.getProperty("ledKill"));

                // Start the LED based on ROM
                //string ledWorkDir = starterProperties.getProperty("ledWorkDir");
                string ledPath = starterProperties.getProperty("ledPath");
                string ledExec = starterProperties.getProperty("ledExec");
                //string ledGame = starterProperties.getProperty("ledGame");
                //string ledExt = starterProperties.getProperty("ledExt");


                ledPID = Processes.StartExe(ledPath, ledExec, " :led=" + rom + ".txt" + system + systemType, ProcessWindowStyle.Normal, false);

                ////FileSystem.doesFileExist(ledGame, (rom + ledExt))
                //string concat = rom + ledExt;
                //if (FileSystem.doesFileExist(ledGame, concat))
                //{// Rom LED file found
                //    ledPID = Processes.StartExe(ledWorkDir, ledPath, ledExec, concat, ProcessWindowStyle.Minimized, false, false);
                //}
                //else
                //{// Rom LED file NOT found...using default file.
                //    ledPID = Processes.StartExe(ledPath, ledExec, "default" + ledExt, ProcessWindowStyle.Minimized, false);
                //}
                #endregion

                #region QBW-Button
                // ========================================================================
                // Kill the QBW Button if it is running
                // ========================================================================
                Processes.KillProcess(starterProperties.getProperty("buttonKill"));

                // Start the Button based on ROM
                string buttonPath = starterProperties.getProperty("buttonPath");
                string buttonExec = starterProperties.getProperty("buttonExec");

                btnPID = Processes.StartExe(buttonPath, buttonExec, " :led=" + rom + " " + system + systemType, ProcessWindowStyle.Normal, false);
                #endregion

                #region Find ROM
                // ========================================================================
                // Find the ROM to execute
                // ========================================================================
                int cnt = 1;
                string mamePath = null;
                string mameRomPath = null;
                string mameExe = null;
                string mameOpt = null;
 //               bool incRomPath = false;
                bool romFound = false;

                string romPath = "roms";
                string romTest = "roms_untested";

                mameOpt = gameProperties.getProperty(rom + "Opt");
                if (mameOpt == null)
                {
                    mameOpt = gameProperties.getProperty("mameOpt");
                }

                string runPath = null;
                string runExe = null;

                while (gameProperties.getProperty("mame" + cnt) != null)
                {
                    mamePath = gameProperties.getProperty("mame" + cnt);
                    mameExe = gameProperties.getProperty("mame" + cnt + "exe");
//                    incRomPath = "true".Equals(gameProperties.getProperty("mame" + cnt + "useRomPath"));
                    mameRomPath = gameProperties.getProperty("mame" + cnt + "romPath");
                    if (mameRomPath == null)
                    {
                        mameRomPath = "";
                    }
                    // Do we have a ZIP file
                    // ROMs can exist in:
                    // -> root folder = romPath
                    // -> roms folder = romTest
                    // -> untested folder == ""
                    // -> properties file mameRomPath
                    if (FileSystem.doesFileExist(FileSystem.fixDir(mamePath) + romPath, mPathZip, false) ||
                        FileSystem.doesFileExist(FileSystem.fixDir(mamePath) + romTest, mPathZip, false) ||
                        FileSystem.doesFileExist(FileSystem.fixDir(mameRomPath) + "", mPathZip, false) ||
                        FileSystem.doesFileExist(FileSystem.fixDir(mamePath) + "", mPathZip, false))
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
                    cnt++;
                }
                #endregion

                #region start MAME
                // ========================================================================
                // MAME run the ROM, or NOT
                // ========================================================================

                if (!romFound)
                {
                    throw new Exception("ROM not found: '" + mameRomPath + mPathZip + "' error.");
                }

                // Do we need joystick 2 keyboard???
                bool joy2keyAll = "true".Equals(gameProperties.getProperty("j2k_All"));
                bool joy2keyRom = "true".Equals(gameProperties.getProperty(rom));

                Logger.Write(Logger.LogLevels.Debug, "J2k_all: " + joy2keyAll);
                Logger.Write(Logger.LogLevels.Debug, "J2k_rom: " + joy2keyRom);

                if (joy2keyRom || joy2keyAll)
                {   // Start Joy2Key
                    Logger.Write(Logger.LogLevels.Debug, "Running J2k");

                    string joyPath = starterProperties.getProperty("joyPath");
                    string joyExec = starterProperties.getProperty("joyExec");

                    //j2kPID = Processes.StartExe(joyPath, joyExec, joyArgs, ProcessWindowStyle.Minimized, false);
                    j2kPID = Processes.StartExe(joyPath, joyExec, systemType, ProcessWindowStyle.Minimized, false);
                    Thread.Sleep(2000);
                }

                // Run GAME exe
                Logger.Write(Logger.LogLevels.Info, "-----------------------------------------------------------");

                bool removeExt = "true".Equals(gameProperties.getProperty("removeExt"));
                if (removeExt)
                {
                    mPathZip = rom;
                }

                string quote = "";
                bool quoteRom = "true".Equals(gameProperties.getProperty("quoteROM"));
                if (quoteRom)
                {
                    quote = "\"";
                }

 //               if (!incRomPath)
 //               {
 //                   mameRomPath = "";
 //               }
                Logger.Write(Logger.LogLevels.Info, "MAME: " + runPath + @"\" + runExe + " " + mameOpt + " " + quote + mameRomPath + mPathZip + quote);
                // StartExe(@"C:\MAME\mame_1.38\", "mame.exe", rom, ProcessWindowStyle.Normal, true);
                //success = StartExe(mamePath, mameExe, rom, ProcessWindowStyle.Normal, true);


                mamePID = Processes.StartExe(runPath, runExe, mameOpt + " " + quote + mameRomPath + mPathZip + quote, ProcessWindowStyle.Maximized, true, false);
                //if (!success)
                if (mamePID == -1)
                {
                    MessageBox.Show("Failed running MAME '" + mPathZip + "'." + "\n" +
                    //    "\nWork: " + ledWorkDir +
                        "\nPath: " + runPath +
                        "\nEXE : " + runExe +
                        "\nROM : " + mPathZip +
                        "\n\nmameOpt : " + mameOpt
                        , "ERROR", MessageBoxButtons.OK);
                }
                // Start from CMD prompt
                //StartExe(@"C:\",@"C:\Windows\System32","cmd.exe",@"/c " + fixDir(mameBatch) + rom + ".bat", ProcessWindowStyle.Normal, true);

                if (j2kPID != -1)
                {
                    // Kill Joy2Key
                    Logger.Write(Logger.LogLevels.Debug, "Killing J2k");
                    Processes.KillProcess(starterProperties.getProperty("joyKill"));
                }
                #endregion

                #region QBW-LED 'default'
                // ========================================================================
                // Kill  the game  LED
                // Start HyperSpin LED
                // ========================================================================
                Processes.KillProcess(starterProperties.getProperty("ledKill"));

                // Start using default file.
                if (ledPID != -1)
                {
//                    ledPID = Processes.StartExe(ledPath, ledExec, "default" + ledExt, ProcessWindowStyle.Normal, false);
//                    ledPID = Processes.StartExe(ledPath, ledExec, ":system=HyperSpin :led=default.txt", ProcessWindowStyle.Normal, false);
                    ledPID = Processes.StartExe(ledPath, ledExec, " :led=default.txt" + system + "HyperSpin", ProcessWindowStyle.Normal, false);
                }
                #endregion

                #region Kill QBW-Button
                // ========================================================================
                // Kill the QBW Button if it is running
                // ========================================================================
                if (btnPID != -1)
                {
                    Processes.KillProcess(starterProperties.getProperty("buttonKill"));
                }

                #endregion
                Logger.Write(Logger.LogLevels.Debug, "Ending");
            }
            catch (Exception ex)
            {
                Logger.Write(Logger.LogLevels.Error, ex.Message);
                Logger.Write(Logger.LogLevels.Error, ex.StackTrace.ToString());

                MessageBox.Show("Failed running GAME '" + ex.Message + "'." + "\n", "ERROR", MessageBoxButtons.OK);
            }
        }
    }
}