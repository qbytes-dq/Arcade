using System;
using System.Collections.Generic;
using System.Text;

namespace QBW_Joy2Key
{
    class ASCII
    {

        public static void print255()
        {
            {
                // ASCII is a 7bit code!
                //Console.OutputEncoding = Encoding.ASCII;

                int column = 0;
                for (byte counter = 32; counter < 255; counter++)
                {
                    if (column == 0)
                    {
                        Console.Write("0x{0:X}  ", counter);
                    }
                    Console.Write(" {0}  ", (char)counter);
                    if (++column > 7)
                    {
                        column = 0;
                        Console.WriteLine();
                    }
                }
            }
        }
    }
}
