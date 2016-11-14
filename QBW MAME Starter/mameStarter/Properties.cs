using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Diagnostics;

namespace mameStarter
{
    public class Properties
    {
        Dictionary<string, string> dictionary = new Dictionary<string, string>();

        public Properties(string propertyFileName)
        {
            int counter = 0;
            string line;

            // Read the file and display it line by line.
            System.IO.StreamReader file = new System.IO.StreamReader(propertyFileName);
            while ((line = file.ReadLine()) != null)
            {
                if (line.Length > 3 && line.Contains("=") && !line.StartsWith("#"))
                {
                    char[] splitOn = new char[] { '=' };
                    string[] split = line.Split(splitOn);

                    int len = split[0].Length;
                    int start = len + 1; // s/b 12
                    int end = line.Length - start;

                    //ServerName=prod-srv1
                    dictionary.Add(split[0], line.Substring(start, end));

                    Debug.WriteLine(line);
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
}
