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
    public class FileSystem
    {
        /// <summary>
        /// Get directory list.
        /// </summary>
        public static void getDirectoryList(string path, string searchPattern)  ///@"C:\MAME\mame_1.38\roms\", "*.zip"
        {
            try
            {
                // Only get files that begin with the letter "c." 
                string[] dirs = Directory.GetFiles(path, searchPattern);
                Console.WriteLine("The number of files is: {0}.", dirs.Length);
                foreach (string dir in dirs)
                {
                    Logger.Write(Logger.LogLevels.Debug, dir);
                }
            }
            catch (Exception e)
            {
                Logger.Write(Logger.LogLevels.Error, "The process failed: " + e.ToString());
            }
        }

        /// <summary>
        /// Check to see if file exists.
        /// </summary>
        public static bool doesFileExist(string path, string fileName)
        {
            return doesFileExist(path, fileName, true);
        }

        public static bool doesFileExist(string path, string fileName, bool showNotFound)
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
                        Logger.Write(Logger.LogLevels.Warn, "File does not exist: " + curFile);
                    }
                    return false;
                }
            }
            catch (Exception e)
            {
                Logger.Write(Logger.LogLevels.Error, "oops:::" + e.ToString());
                return false;
            }
        }

        public static string fixDir(string dir)
        {
            if (dir.EndsWith(@"\"))
            {
                dir = dir.Substring(0, dir.Length - 1);
            }
            dir += @"\";
            return dir;
        }
    }
}
