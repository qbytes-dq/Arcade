using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

using System.Diagnostics;
using System.Windows.Forms;
using System.Threading;

namespace MameButtons
{

    class Config
    {
        Dictionary<string, string> dictionary = new Dictionary<string, string>();

        public Config(RichTextBox rtb, Label lblROM)
        {
            string line;
            bool romFound = false;
            rtb.Text = "";

            String[] args = Environment.GetCommandLineArgs();

            if (args.Length < 2)
            {
                Logger.Write(Logger.LogLevels.Error, "No ARG(s) provided.");
                lblROM.Text = "romFileName";
            }
            else
            {
                String romFileName = args[1];
                lblROM.Text = romFileName;

                //Logger.Write(Logger.LogLevels.Info, "EXE: " + args[0]);  contains:: MameButtons.exe
                Logger.Write(Logger.LogLevels.Info, "ROM: " + romFileName);

                // Read the file and display button line by line.
                System.IO.StreamReader file = new System.IO.StreamReader("controls.ini");
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

                                int maxLen = 17;
                                string gamename = split[1];
                                int len = split[1].Length;
                                if (len > maxLen)
                                    len = maxLen;
                                lblROM.Text = split[1].Substring(0,len);
                            }
                            else
                            if (line.Contains("_"))
                            {// Controls
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
                                Logger.Write(Logger.LogLevels.Debug, line);
                            }
                        }

                    }
                }
                file.Close();

                if (!romFound)
                {
                    rtb.AppendText("ROM not defined in 'controls.ini'");
                }
            }
        }
    }
}
