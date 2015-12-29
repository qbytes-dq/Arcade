using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

using System.Diagnostics;
using System.Windows.Forms;
using System.Threading;
using System.IO;

namespace MameButtons
{

    class Config
    {
        bool error = false;

        public bool hasError()
        {
            return error;
        }

        Dictionary<string, string> dictionary = new Dictionary<string, string>();

        public Config(RichTextBox rtb, Label lblROM)
        {
            string line;
            bool romFound = false;
            rtb.Text = "";

            String[] args = Environment.GetCommandLineArgs();
            // Read the file and display button line by line.
            System.IO.StreamReader file = null;
            string directory1 = "";
            string file1 = "";

            try
            {

                if (args.Length < 3)
                {
                    lblROM.Text = "romFileName";
                    string error = "Invalid ARG(s) provided. Expected %rom% :system=%systemtype%";
                    Logger.Write(Logger.LogLevels.Error, error);
                    throw new Exception(error);
                }

                string romIn = "";
                string system = "HyperSpin";
                //      string rom = "";
                //      string ext = "";

                // Concatenate all args to a single string
                //string rom = args[0]; arg 1 is command line.
                for (int lpx = 1; lpx < args.Length; lpx++)
                {
                    romIn += args[lpx];
                    if ((lpx + 1) < args.Length)
                        romIn += " ";
                }

                // ========================================
                char[] delimiterChars = { ':' };
                char[] trimChars = { ' ' };
                string[] words = romIn.Split(delimiterChars);

                String romFileName = "default";
                foreach (string s in words)
                {
                    string[] arg = s.Split('=');
                    if (arg[0].Equals("led"))
                    {
                        romFileName = arg[1].Trim(trimChars);
                    }
                    else
                        if (arg[0].Equals("system"))
                        {
                            system = arg[1].Trim(trimChars);
                        }
                }

                //String romFileName = args[1];
                lblROM.Text = romFileName;

                //Logger.Write(Logger.LogLevels.Info, "EXE: " + args[0]);  contains:: MameButtons.exe
                Logger.Write(Logger.LogLevels.Info, "ROM: " + romFileName);



                //file = new System.IO.StreamReader("controls.ini");
                directory1 = Form1.dir + @"\systems\";
                file1 = system + ".ini";
                file = new System.IO.StreamReader(directory1 + file1);

                while ((line = file.ReadLine()) != null)
                {
                    if (line.ToUpper().StartsWith("["))
                    {
                        if (romFound)
                        {
                            break;
                        }
                        if (line.ToUpper().Contains(romFileName.ToUpper()))
                        {
                            romFound = true;
                        }
                    }
                    else
                    {

                        if (romFound && line.Length > 3 && line.Contains("=") && !line.StartsWith("#"))
                        {
                            if (line.StartsWith("gamename"))
                            {//gamename
                                char[] splitOn = new char[] { '=' };
                                string[] split = line.Split(splitOn);

                                lblROM.Text = split[1];
                            }
                            else
                                if (line.Contains("_"))
                                {// Controls

                                    //rtb.AppendText("------------------\n"); 

                                    char[] splitOn = new char[] { '=' };
                                    string[] split = line.Split(splitOn);

                                    rtb.AppendText(split[0]
                                        .Replace("_LIGHTGUN", "_GUN")
                                        .Replace("_JOYSTICKLEFT", "_JOY.L")
                                        .Replace("_JOYSTICKRIGHT", "_JOY.R")
                                        .Replace("_JOYSTICK", "_JOY")
                                        .Replace("_BUTTON", "_B")
                                        .Replace("_TRACKBALL", "_BALL")
                                        .Replace("_UP", "_U")
                                        .Replace("_DOWN", "_D")
                                        .Replace("_LEFT", "_L")
                                        .Replace("_RIGHT", "_R")
                                        );
                                    rtb.AppendText("=");
                                    rtb.AppendText(split[1]);
                                    rtb.AppendText("\n");

                                    Logger.Write(Logger.LogLevels.Info, line);
                                }
                        }

                    }
                }

                if (!romFound)
                {
                    error = true;
                    rtb.AppendText("ROM not defined in 'controls.ini'\n");
                    Logger.Write(Logger.LogLevels.Error, "ROM not defined in 'controls.ini'");
                }
            }

            catch (DirectoryNotFoundException e)
            {
                error = true;
                rtb.AppendText("Directory not found:\n " + directory1);
                Logger.Write(Logger.LogLevels.Error, "'Directory not found:\n" + directory1 + "\n" + e.StackTrace.ToString());
            }
            catch (FileNotFoundException e)
            {
                error = true;
                rtb.AppendText("'" + file1 + "' not found: \n");
                Logger.Write(Logger.LogLevels.Error, "'" + file1 + "' not found: " + "\n" + e.StackTrace.ToString());
            }
            catch (Exception e)
            {
                error = true;
                rtb.AppendText("Ooops, check this out....\n" + e.Message.ToString() + "\n");
                Logger.Write(Logger.LogLevels.Error, "Ooops, check this out....: " + e.StackTrace.ToString());
            }
            finally
            {
                if (file != null)
                    file.Close();

                string tmp = lblROM.Text;
                int maxLen = 17;
                string gamename = tmp;
                int len = tmp.Length;
                if (len > maxLen)
                    len = maxLen;
                lblROM.Text = tmp.Substring(0, len);
            }
        }
        //}
    }
}
