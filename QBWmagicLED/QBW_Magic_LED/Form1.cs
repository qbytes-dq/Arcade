//-----------------------------------------------------------------------------
//     taskkill /f /im "QBW Magic LED HID 3.vshost.exe"
//-----------------------------------------------------------------------------
//
//  Form1.cs
//
//  USB Generic HID Demonstration 3_0_0_0
//
//  A reference test application for the usbGenericHidCommunications library
//  Copyright (C) 2011 Simon Inns
//
//  This program is free software: you can redistribute it and/or modify
//  it under the terms of the GNU General Public License as published by
//  the Free Software Foundation, either version 3 of the License, or
//  (at your option) any later version.
//
//  This program is distributed in the hope that it will be useful,
//  but WITHOUT ANY WARRANTY; without even the implied warranty of
//  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
//  GNU General Public License for more details.
//
//  You should have received a copy of the GNU General Public License
//  along with this program.  If not, see <http://www.gnu.org/licenses/>.
//
//  Web:    http://www.waitingforfriday.com
//  Email:  simon.inns@gmail.com
//
//-----------------------------------------------------------------------------

//
//  Current reference class library version:
//  usbGenericHidCommunications class library version 3.0.0.0
//

using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Windows.Forms;

using System.IO;
using System.Collections;

using System.Diagnostics;

namespace WFF_Generic_HID_Demo_3
    {
    public partial class Form1 : Form
        {

        public enum LogLevels { Debug = 1, Info, Warn, Error };
        public static LogLevels logLevel = LogLevels.Debug;

        // Create an instance of the USB reference device
        private usbDemoDevice theUsbDemoDevice; // ID is not 0-9.

        private usbDemoDevice theUsbDemoDevice_0;
        private usbDemoDevice theUsbDemoDevice_1;
        private usbDemoDevice theUsbDemoDevice_2;
        private usbDemoDevice theUsbDemoDevice_3;
        private usbDemoDevice theUsbDemoDevice_4;
        private usbDemoDevice theUsbDemoDevice_5;
        private usbDemoDevice theUsbDemoDevice_6;
        private usbDemoDevice theUsbDemoDevice_7;
        private usbDemoDevice theUsbDemoDevice_8;
        private usbDemoDevice theUsbDemoDevice_9;


        ArrayList myArrayList = new ArrayList();


        public Form1(string[] args)
            {

            InitializeComponent();

            Logger(LogLevels.Info, "=========================================================");

            //if (args.Length == 0)
            //{
            //    args = new string[1];
            //    args[0] = "default.txt";
            //}
           
            myArrayList.AddRange(args);

            // ================================================================================
            // Default device
            // ================================================================================
            // Create the USB reference device object (passing VID and PID)
            theUsbDemoDevice = new usbDemoDevice(0x04D9, 0x0999);
            // Add a listener for usb events
            theUsbDemoDevice.usbEvent += new usbDemoDevice.usbEventsHandler(usbEvent_receiver);
            // Perform an initial search for the target device
            theUsbDemoDevice.findTargetDevice();

            // ================================================================================
            // Device 0
            // ================================================================================
            // Create the USB reference device object (passing VID and PID)
            theUsbDemoDevice_0 = new usbDemoDevice(0x04D9, 0x0100);
            // Add a listener for usb events
            theUsbDemoDevice_0.usbEvent += new usbDemoDevice.usbEventsHandler(usbEvent_receiver_0);
            // Perform an initial search for the target device
            theUsbDemoDevice_0.findTargetDevice();


            // ================================================================================
            // Device 1
            // ================================================================================
            // Create the USB reference device object (passing VID and PID)
            theUsbDemoDevice_1 = new usbDemoDevice(0x04D9, 0x0101);
 //           theUsbDemoDevice_1 = new usbDemoDevice(0x04D8, 0x0340);
            // Add a listener for usb events
            theUsbDemoDevice_1.usbEvent += new usbDemoDevice.usbEventsHandler(usbEvent_receiver_1);
            // Perform an initial search for the target device
            theUsbDemoDevice_1.findTargetDevice();


            // ================================================================================
            // Device 2
            // ================================================================================
            // Create the USB reference device object (passing VID and PID)
            theUsbDemoDevice_2 = new usbDemoDevice(0x04D9, 0x0102);
            // Add a listener for usb events
            theUsbDemoDevice_2.usbEvent += new usbDemoDevice.usbEventsHandler(usbEvent_receiver_2);
            // Perform an initial search for the target device
            theUsbDemoDevice_2.findTargetDevice();


            // ================================================================================
            // Device 3
            // ================================================================================
            // Create the USB reference device object (passing VID and PID)
            theUsbDemoDevice_3 = new usbDemoDevice(0x04D9, 0x0103);
            // Add a listener for usb events
            theUsbDemoDevice_3.usbEvent += new usbDemoDevice.usbEventsHandler(usbEvent_receiver_3);
            // Perform an initial search for the target device
            theUsbDemoDevice_3.findTargetDevice();


            // ================================================================================
            // Device 4
            // ================================================================================
            // Create the USB reference device object (passing VID and PID)
            theUsbDemoDevice_4 = new usbDemoDevice(0x04D9, 0x0104);
            // Add a listener for usb events
            theUsbDemoDevice_4.usbEvent += new usbDemoDevice.usbEventsHandler(usbEvent_receiver_4);
            // Perform an initial search for the target device
            theUsbDemoDevice_4.findTargetDevice();


            // ================================================================================
            // Device 5
            // ================================================================================
            // Create the USB reference device object (passing VID and PID)
            theUsbDemoDevice_5 = new usbDemoDevice(0x04D9, 0x0105);
            // Add a listener for usb events
            theUsbDemoDevice_5.usbEvent += new usbDemoDevice.usbEventsHandler(usbEvent_receiver_5);
            // Perform an initial search for the target device
            theUsbDemoDevice_5.findTargetDevice();


            // ================================================================================
            // Device 6
            // ================================================================================
            // Create the USB reference device object (passing VID and PID)
            theUsbDemoDevice_6 = new usbDemoDevice(0x04D9, 0x0106);
            // Add a listener for usb events
            theUsbDemoDevice_6.usbEvent += new usbDemoDevice.usbEventsHandler(usbEvent_receiver_6);
            // Perform an initial search for the target device
            theUsbDemoDevice_6.findTargetDevice();


            // ================================================================================
            // Device 7
            // ================================================================================
            // Create the USB reference device object (passing VID and PID)
            theUsbDemoDevice_7 = new usbDemoDevice(0x04D9, 0x0107);
            // Add a listener for usb events
            theUsbDemoDevice_7.usbEvent += new usbDemoDevice.usbEventsHandler(usbEvent_receiver_7);
            // Perform an initial search for the target device
            theUsbDemoDevice_7.findTargetDevice();


            // ================================================================================
            // Device 8
            // ================================================================================
            // Create the USB reference device object (passing VID and PID)
            theUsbDemoDevice_8 = new usbDemoDevice(0x04D9, 0x0108);
            // Add a listener for usb events
            theUsbDemoDevice_8.usbEvent += new usbDemoDevice.usbEventsHandler(usbEvent_receiver_8);
            // Perform an initial search for the target device
            theUsbDemoDevice_8.findTargetDevice();

            // ================================================================================
            // Device 9
            // ================================================================================
            // Create the USB reference device object (passing VID and PID)
            theUsbDemoDevice_9 = new usbDemoDevice(0x04D9, 0x0109);
            // Add a listener for usb events
            theUsbDemoDevice_9.usbEvent += new usbDemoDevice.usbEventsHandler(usbEvent_receiver_9);
            // Perform an initial search for the target device
            theUsbDemoDevice_9.findTargetDevice();
            }

        // Listener for USB events 999 DEFAULT 
        private void usbEvent_receiver(object o, EventArgs e)
        {
            if (theUsbDemoDevice != null)

            // Check the status of the USB device and update the form accordingly
            if (theUsbDemoDevice.isDeviceAttached)
            {
                // Device is currently attached
                    chkAttached999.Checked = true;
                    this.updateDebutTextBox("USB Device #? is attached.\r\n");
                }
                else
                {
                // Device is currently unattached
                    chkAttached999.Checked = false;
                chkError999.Checked = false;
                this.updateDebutTextBox("USB Device #? is UNattached.\r\n");
            }
        }

        // Listener for USB events 0
        private void usbEvent_receiver_0(object o, EventArgs e)
        {
            if (theUsbDemoDevice_0 != null)

            // Check the status of the USB device and update the form accordingly
            if (theUsbDemoDevice_0.isDeviceAttached)
            {
                // Device is currently attached
                chkAttached0.Checked = true;
                this.updateDebutTextBox("USB Device #0 is attached.\r\n");
            }
            else
            {
                // Device is currently unattached
                chkAttached0.Checked = false;
                chkError0.Checked = false;
                this.updateDebutTextBox("USB Device #0 is UNattached.\r\n");
            }
        }

        // Listener for USB events 1
        private void usbEvent_receiver_1(object o, EventArgs e)
        {
            if (theUsbDemoDevice_1 != null)

            // Check the status of the USB device and update the form accordingly
            if (theUsbDemoDevice_1.isDeviceAttached)
            {
                // Device is currently attached
                chkAttached1.Checked = true;
                this.updateDebutTextBox("USB Device #1 is attached.\r\n");
            }
            else
            {
                // Device is currently unattached
                chkAttached1.Checked = false;
                chkError1.Checked = false;
                this.updateDebutTextBox("USB Device #1 is UNattached.\r\n");
            }
        }

        // Listener for USB events 2
        private void usbEvent_receiver_2(object o, EventArgs e)
        {
            if (theUsbDemoDevice_2 != null)

            // Check the status of the USB device and update the form accordingly
            if (theUsbDemoDevice_2.isDeviceAttached)
            {
                // Device is currently attached
                chkAttached2.Checked = true;
                this.updateDebutTextBox("USB Device #2 is attached.\r\n");
            }
            else
            {
                // Device is currently unattached
                chkAttached2.Checked = false;
                chkError2.Checked = false;
                this.updateDebutTextBox("USB Device #2 is UNattached.\r\n");
            }
        }

        // Listener for USB events 3
        private void usbEvent_receiver_3(object o, EventArgs e)
        {
            if (theUsbDemoDevice_3 != null)

            // Check the status of the USB device and update the form accordingly
            if (theUsbDemoDevice_3.isDeviceAttached)
            {
                // Device is currently attached
                chkAttached3.Checked = true;
                this.updateDebutTextBox("USB Device #3 is attached.\r\n");
            }
            else
            {
                // Device is currently unattached
                chkAttached3.Checked = false;
                chkError3.Checked = false;
                this.updateDebutTextBox("USB Device #3 is UNattached.\r\n");

            }
        }

        // Listener for USB events 4
        private void usbEvent_receiver_4(object o, EventArgs e)
        {
            if (theUsbDemoDevice_4 != null)
            // Check the status of the USB device and update the form accordingly
            if (theUsbDemoDevice_4.isDeviceAttached)
            {
                // Device is currently attached
                chkAttached4.Checked = true;
                this.updateDebutTextBox("USB Device #4 is attached.\r\n");
            }
            else
            {
               // Device is currently unattached
                chkAttached4.Checked = false;
                 chkError4.Checked = false;
                 this.updateDebutTextBox("USB Device #4 is UNattached.\r\n");

            }
        }

        // Listener for USB events 5
        private void usbEvent_receiver_5(object o, EventArgs e)
        {
            if (theUsbDemoDevice_5 != null)

            // Check the status of the USB device and update the form accordingly
            if (theUsbDemoDevice_5.isDeviceAttached)
            {
                // Device is currently attached
                chkAttached5.Checked = true;
                this.updateDebutTextBox("USB Device #5 is attached.\r\n");
            }
            else
            {
               // Device is currently unattached
                chkAttached5.Checked = false;
                 chkError5.Checked = false;
                 this.updateDebutTextBox("USB Device #5 is UNattached.\r\n");

            }
        }

        // Listener for USB events 6
        private void usbEvent_receiver_6(object o, EventArgs e)
        {
            if (theUsbDemoDevice_6 != null)

            // Check the status of the USB device and update the form accordingly
            if (theUsbDemoDevice_6.isDeviceAttached)
            {
                // Device is currently attached
                chkAttached6.Checked = true;
                this.updateDebutTextBox("USB Device #6 is attached.\r\n");
            }
            else
            {
               // Device is currently unattached
                 chkAttached6.Checked = false;
                chkError6.Checked = false;
                this.updateDebutTextBox("USB Device #6 is UNattached.\r\n");

            }
        }

        // Listener for USB events 7
        private void usbEvent_receiver_7(object o, EventArgs e)
        {
            if (theUsbDemoDevice_7 != null)

            // Check the status of the USB device and update the form accordingly
            if (theUsbDemoDevice_7.isDeviceAttached)
            {
                // Device is currently attached
                chkAttached7.Checked = true;
                this.updateDebutTextBox("USB Device #7 is attached.\r\n");
            }
            else
            {
                // Device is currently unattached
                chkAttached7.Checked = false;
                chkError7.Checked = false;
                this.updateDebutTextBox("USB Device #7 is UNattached.\r\n");

            }
        }

        // Listener for USB events 8
        private void usbEvent_receiver_8(object o, EventArgs e)
        {
            if (theUsbDemoDevice_8 != null)

            // Check the status of the USB device and update the form accordingly
            if (theUsbDemoDevice_8.isDeviceAttached)
            {
                // Device is currently attached
                chkAttached8.Checked = true;
                this.updateDebutTextBox("USB Device #8 is attached.\r\n");
            }
            else
            {
               // Device is currently unattached
                chkAttached8.Checked = false;
                 chkError8.Checked = false;
                 this.updateDebutTextBox("USB Device #8 is UNattached.\r\n");

            }
        }

        // Listener for USB events 9
        private void usbEvent_receiver_9(object o, EventArgs e)
        {
            if (theUsbDemoDevice_9 != null)

            // Check the status of the USB device and update the form accordingly
            if (theUsbDemoDevice_9.isDeviceAttached)
            {
                // Device is currently attached
                chkAttached9.Checked = true;
                this.updateDebutTextBox("USB Device #9 is attached.\r\n");
            }
            else
            {
               // Device is currently unattached
                 chkAttached9.Checked = false;
                chkError9.Checked = false;
                this.updateDebutTextBox("USB Device #9 is UNattached.\r\n");

            }


  //          this.toggleLedStateButton.Enabled = true;
        }

        private usbDemoDevice getDemoDevice()
        {
            usbDemoDevice temp_UsbDemoDevice = theUsbDemoDevice;

            if (rdSelected0.Checked)
                temp_UsbDemoDevice = theUsbDemoDevice_0;
            if (rdSelected1.Checked)
                temp_UsbDemoDevice = theUsbDemoDevice_1;
            if (rdSelected2.Checked)
                temp_UsbDemoDevice = theUsbDemoDevice_2;
            if (rdSelected3.Checked)
                temp_UsbDemoDevice = theUsbDemoDevice_3;
            if (rdSelected4.Checked)
                temp_UsbDemoDevice = theUsbDemoDevice_4;
            if (rdSelected5.Checked)
                temp_UsbDemoDevice = theUsbDemoDevice_5;
            if (rdSelected6.Checked)
                temp_UsbDemoDevice = theUsbDemoDevice_6;
            if (rdSelected7.Checked)
                temp_UsbDemoDevice = theUsbDemoDevice_7;
            if (rdSelected8.Checked)
                temp_UsbDemoDevice = theUsbDemoDevice_8;
            if (rdSelected9.Checked)
                temp_UsbDemoDevice = theUsbDemoDevice_9;

            return temp_UsbDemoDevice;
        }

        private void updateDebutTextBox(string txt)
        {
            try
            {
                Logger(LogLevels.Debug, txt);

                this.debugTextBox.AppendText(txt);
            }
            catch
            {
                // eat it, we are ending????
            }
        }

        // Link label to website clicked
        private void linkLabel1_LinkClicked_1(object sender, LinkLabelLinkClickedEventArgs e)
            {
            // Specify that the link was visited.
            this.linkLabel1.LinkVisited = true;

            // Navigate to a URL.
            System.Diagnostics.Process.Start("http://www.waitingforfriday.com");
            }

        // Toggle LED state button pressed
        private void toggleLedStateButton_Click(object sender, EventArgs e)
            {
                if (getDemoDevice().isDeviceAttached)
                    {
                        getDemoDevice().toggleLedState();
                    }
            }

        // Timer 1 has ticked, poll the USB device for status
        private void errorStateCollectionTimer_Tick(object sender, EventArgs e)
        {
            //this.updateDebutTextBox("errorStateCollectionTimer_Tick\r\n");

            // Device 0
            if (theUsbDemoDevice_0.isDeviceAttached)
            {
                // Read the push button state
                bool buttonState = theUsbDemoDevice_0.readPushButtonState();
                chkError0.Checked = buttonState;
            }

            // Device 1
            if (theUsbDemoDevice_1.isDeviceAttached)
            {
                // Read the push button state
                bool buttonState = theUsbDemoDevice_1.readPushButtonState();
                chkError1.Checked = buttonState;
            }

            // Device 2
            if (theUsbDemoDevice_2.isDeviceAttached)
            {
                // Read the push button state
                bool buttonState = theUsbDemoDevice_2.readPushButtonState();
                chkError2.Checked = buttonState;
            }

            // Device 3
            if (theUsbDemoDevice_3.isDeviceAttached)
            {
                // Read the push button state
                bool buttonState = theUsbDemoDevice_3.readPushButtonState();
                chkError3.Checked = buttonState;
            }

            // Device 4
            if (theUsbDemoDevice_4.isDeviceAttached)
            {
                // Read the push button state
                bool buttonState = theUsbDemoDevice_4.readPushButtonState();
                chkError4.Checked = buttonState;
            }

            // Device 5
            if (theUsbDemoDevice_5.isDeviceAttached)
            {
                // Read the push button state
                bool buttonState = theUsbDemoDevice_5.readPushButtonState();
                chkError5.Checked = buttonState;
            }

            // Device 6
            if (theUsbDemoDevice_6.isDeviceAttached)
            {
                // Read the push button state
                bool buttonState = theUsbDemoDevice_6.readPushButtonState();
                chkError6.Checked = buttonState;
            }

            // Device 7
            if (theUsbDemoDevice_7.isDeviceAttached)
            {
                // Read the push button state
                bool buttonState = theUsbDemoDevice_7.readPushButtonState();
                chkError7.Checked = buttonState;
            }

            // Device 8
            if (theUsbDemoDevice_8.isDeviceAttached)
            {
                // Read the push button state
                bool buttonState = theUsbDemoDevice_8.readPushButtonState();
                chkError8.Checked = buttonState;
            }

            // Device 9
            if (theUsbDemoDevice_9.isDeviceAttached)
            {
                // Read the push button state
                bool buttonState = theUsbDemoDevice_9.readPushButtonState();
                chkError9.Checked = buttonState;
            }

            // Device 999
            if (theUsbDemoDevice.isDeviceAttached)
            {
                // Read the push button state
                bool buttonState = theUsbDemoDevice.readPushButtonState();
                chkError999.Checked = buttonState;
            }
        }

        // Timer 1 has ticked, poll the USB device for status
        private void ledStateCollectionTimer_Tick(object sender, EventArgs e)
        {
            //this.updateDebutTextBox("ledStateCollectionTimer_Tick\r\n");

            // Device 0
            if (theUsbDemoDevice_0.isDeviceAttached)
            {
                // Read the LED state
                bool ledState = theUsbDemoDevice_0.readLedState();
                chkLED0.Checked = ledState;
            }

            // Device 1
            if (theUsbDemoDevice_1.isDeviceAttached)
            {
                // Read the LED state
                bool ledState = theUsbDemoDevice_1.readLedState();
                chkLED1.Checked = ledState;
            }

            // Device 2
            if (theUsbDemoDevice_2.isDeviceAttached)
            {
                // Read the LED state
                bool ledState = theUsbDemoDevice_2.readLedState();
                chkLED2.Checked = ledState;
            }

            // Device 3
            if (theUsbDemoDevice_3.isDeviceAttached)
            {
                // Read the LED state
                bool ledState = theUsbDemoDevice_3.readLedState();
                chkLED3.Checked = ledState;
            }

            // Device 4
            if (theUsbDemoDevice_4.isDeviceAttached)
            {
                // Read the LED state
                bool ledState = theUsbDemoDevice_4.readLedState();
                chkLED4.Checked = ledState;
            }

            // Device 5
            if (theUsbDemoDevice_5.isDeviceAttached)
            {
                // Read the LED state
                bool ledState = theUsbDemoDevice_5.readLedState();
                chkLED5.Checked = ledState;
            }

            // Device 6
            if (theUsbDemoDevice_6.isDeviceAttached)
            {
                // Read the LED state
                bool ledState = theUsbDemoDevice_6.readLedState();
                chkLED6.Checked = ledState;
            }

            // Device 7
            if (theUsbDemoDevice_7.isDeviceAttached)
            {
                // Read the LED state
                bool ledState = theUsbDemoDevice_7.readLedState();
                chkLED7.Checked = ledState;
            }

            // Device 8
            if (theUsbDemoDevice_8.isDeviceAttached)
            {
                // Read the LED state
                bool ledState = theUsbDemoDevice_8.readLedState();
                chkLED8.Checked = ledState;
            }

            // Device 9
            if (theUsbDemoDevice_9.isDeviceAttached)
            {
                // Read the LED state
                bool ledState = theUsbDemoDevice_9.readLedState();
                chkLED9.Checked = ledState;
            }

            // Device 999
            if (theUsbDemoDevice.isDeviceAttached)
            {
                // Read the LED state
                bool ledState = theUsbDemoDevice.readLedState();
                chkLED999.Checked = ledState;
            }
        }

        String sTrig = "TRIGGER";

        // Collect debug timer has ticked
        private void debugCollectionTimer_Tick(object sender, EventArgs e)
            {
                //this.updateDebutTextBox("debugCollectionTimer_Tick\r\n");

                String debugString;

                // Only collect debug if the device is attached
                if (theUsbDemoDevice.isDeviceAttached)
                {
                    // Collect the debug information from the device
                    debugString = theUsbDemoDevice.collectDebug();

                    // Display the debug information
                    if (debugString != String.Empty)
                    {
                        if (debugString.ToUpper().Contains(sTrig))
                        {
                            chkTrig0.Checked = true;
                        }
                        this.updateDebutTextBox(debugString);
                    }
                }

                // =================================================
                // Only collect debug if the device is attached
                if (theUsbDemoDevice_0.isDeviceAttached)
                {
                    // Collect the debug information from the device
                    debugString = theUsbDemoDevice_0.collectDebug();

                    // Display the debug information
                    if (debugString != String.Empty)
                    {
                        if (debugString.ToUpper().Contains(sTrig))
                        {
                            chkTrig0.Checked = true;
                        }

                        this.updateDebutTextBox(debugString);
                    }
                }

                // =================================================
                // Only collect debug if the device is attached
                if (theUsbDemoDevice_1.isDeviceAttached)
                {
                    // Collect the debug information from the device
                    debugString = theUsbDemoDevice_1.collectDebug();

                    // Display the debug information
                    if (debugString != String.Empty)
                    {
                        if (debugString.ToUpper().Contains(sTrig))
                        {
                            chkTrig0.Checked = true;
                        }

                        this.updateDebutTextBox(debugString);
                    }
                }

                // =================================================
                // Only collect debug if the device is attached
                if (theUsbDemoDevice_2.isDeviceAttached)
                {
                    // Collect the debug information from the device
                    debugString = theUsbDemoDevice_2.collectDebug();

                    // Display the debug information
                    if (debugString != String.Empty)
                    {
                        if (debugString.ToUpper().Contains(sTrig))
                        {
                            chkTrig0.Checked = true;
                        }
                        this.updateDebutTextBox(debugString);
                    }
                }

                // =================================================
                // Only collect debug if the device is attached
                if (theUsbDemoDevice_3.isDeviceAttached)
                {
                    // Collect the debug information from the device
                    debugString = theUsbDemoDevice_3.collectDebug();

                    // Display the debug information
                    if (debugString != String.Empty)
                    {
                        if (debugString.ToUpper().Contains(sTrig))
                        {
                            chkTrig0.Checked = true;
                        }
                        this.updateDebutTextBox(debugString);
                    }
                }

                // =================================================
                // Only collect debug if the device is attached
                if (theUsbDemoDevice_4.isDeviceAttached)
                {
                    // Collect the debug information from the device
                    debugString = theUsbDemoDevice_4.collectDebug();

                    // Display the debug information
                    if (debugString != String.Empty)
                    {
                        if (debugString.ToUpper().Contains(sTrig))
                        {
                            chkTrig0.Checked = true;
                        }
                        this.updateDebutTextBox(debugString);
                    }
                }

                // =================================================
                // Only collect debug if the device is attached
                if (theUsbDemoDevice_5.isDeviceAttached)
                {
                    // Collect the debug information from the device
                    debugString = theUsbDemoDevice_5.collectDebug();

                    // Display the debug information
                    if (debugString != String.Empty)
                    {
                        if (debugString.ToUpper().Contains(sTrig))
                        {
                            chkTrig0.Checked = true;
                        }
                        this.updateDebutTextBox(debugString);
                    }
                }

                // =================================================
                // Only collect debug if the device is attached
                if (theUsbDemoDevice_6.isDeviceAttached)
                {
                    // Collect the debug information from the device
                    debugString = theUsbDemoDevice_6.collectDebug();

                    // Display the debug information
                    if (debugString != String.Empty)
                    {
                        if (debugString.ToUpper().Contains(sTrig))
                        {
                            chkTrig0.Checked = true;
                        }
                        this.updateDebutTextBox(debugString);
                    }
                }

                // =================================================
                // Only collect debug if the device is attached
                if (theUsbDemoDevice_7.isDeviceAttached)
                {
                    // Collect the debug information from the device
                    debugString = theUsbDemoDevice_7.collectDebug();

                    // Display the debug information
                    if (debugString != String.Empty)
                    {
                        if (debugString.ToUpper().Contains(sTrig))
                        {
                            chkTrig0.Checked = true;
                        }
                        this.updateDebutTextBox(debugString);
                    }
                }

                // =================================================
                // Only collect debug if the device is attached
                if (theUsbDemoDevice_8.isDeviceAttached)
                {
                    // Collect the debug information from the device
                    debugString = theUsbDemoDevice_8.collectDebug();

                    // Display the debug information
                    if (debugString != String.Empty)
                    {
                        if (debugString.ToUpper().Contains(sTrig))
                        {
                            chkTrig0.Checked = true;
                        }
                        this.updateDebutTextBox(debugString);
                    }
                }

                // =================================================
                // Only collect debug if the device is attached
                if (theUsbDemoDevice_9.isDeviceAttached)
                {
                    // Collect the debug information from the device
                    debugString = theUsbDemoDevice_9.collectDebug();

                    // Display the debug information
                    if (debugString != String.Empty)
                    {
                        if (debugString.ToUpper().Contains(sTrig))
                        {
                            chkTrig0.Checked = true;
                        }
                        this.updateDebutTextBox(debugString);
                    }
                }                
            // =================================================
            }

        private void toggleLedSaw_Click(object sender, EventArgs e)
        {
            // #define SAW_UP			0x91
            if (getDemoDevice().isDeviceAttached)
            {
                int step = 2;
                int delay = 1;

                Byte[] outputBuffer = new Byte[62];

                // ============================================================
                for (int lpp = 0; lpp < 48; lpp += 9)
                {
                    // Blue
                    delay *= step;
                    outputBuffer[0] = (byte)lpp;
                    outputBuffer[1] = 0x10;
                    outputBuffer[2] = (byte)delay;
                    getDemoDevice().ledCMD(0x91, outputBuffer);

                    if (lpp == 45) { break; }

                    // Green
                    //                   delay += step;
                    outputBuffer[0] = (byte)(lpp + 4);
                    outputBuffer[1] = 0x10;
                    outputBuffer[2] = (byte)delay;
                    getDemoDevice().ledCMD(0x91, outputBuffer);

                    // Red
                    //                    delay += step;
                    outputBuffer[0] = (byte)(lpp + 8);
                    outputBuffer[1] = 0x10;
                    outputBuffer[2] = (byte)delay;
                    getDemoDevice().ledCMD(0x91, outputBuffer);
                }
            }
        }


        private void toggleLedTrigSawUp_Click(object sender, EventArgs e)
        {
            //
            //Received command 0x0 from host.
            //TLC_CMD - 0x0 0x93 0x16 0x10 0x8 0x0 from host.
            //TRIGGER

            // #define SAW_UP_TRIG			0x93
            if (getDemoDevice().isDeviceAttached)
            {
                int step = 2;
                int delay = 4;
                int lpp = (45 / 2);

                Byte[] outputBuffer = new Byte[62];


                delay *= step;
                outputBuffer[0] = (byte)lpp;
                outputBuffer[1] = 0x10;
                outputBuffer[2] = (byte)delay;
                getDemoDevice().ledCMD(0x93, outputBuffer);
            }
        }


        private void toggleLedTrigSawDown_Click(object sender, EventArgs e)
        {
            //Received command 0x0 from host.
            //TLC_CMD - 0x0 0x94 0x16 0x10 0x8 0x0 from host.
            //TRIGGER

            // #define SAW_UP_TRIG			0x94
            if (getDemoDevice().isDeviceAttached)
            {
                int step = 2;
                int delay = 4;
                int lpp = (45 / 2);

                Byte[] outputBuffer = new Byte[62];


                    delay *= step;
                    outputBuffer[0] = (byte)lpp;
                    outputBuffer[1] = 0x10;
                    outputBuffer[2] = (byte)delay;
                    getDemoDevice().ledCMD(0x94, outputBuffer);
            }
        }


        private void toggleDotCorrect_Click(object sender, EventArgs e)
        {
            if (getDemoDevice().isDeviceAttached)
            {
                Byte[] outputBuffer = new Byte[62];

                //63,21,32
                outputBuffer[0] = 32; 
                outputBuffer[2] = 63;
                outputBuffer[1] = 21;

                getDemoDevice().ledCMD(0xDC, outputBuffer);

            }
        }

        private void toggleDotCorrectRed_Click(object sender, EventArgs e)
        {
            if (getDemoDevice().isDeviceAttached)
            {
                Byte[] outputBuffer = new Byte[62];

                //63,21,32
                outputBuffer[0] = 1;
                outputBuffer[1] = 1;
                outputBuffer[2] = 63;
                getDemoDevice().ledCMD(0xDC, outputBuffer);

            }
        }

        private void toggleDotCorrectBlue_Click(object sender, EventArgs e)
        {
            if (getDemoDevice().isDeviceAttached)
            {
                Byte[] outputBuffer = new Byte[62];

                //63,21,32
                outputBuffer[0] = 63;
                outputBuffer[1] = 1;
                outputBuffer[2] = 1;
                getDemoDevice().ledCMD(0xDC, outputBuffer);

            }
        }

        private void toggleDotCorrectGreen_Click(object sender, EventArgs e)
        {
            if (getDemoDevice().isDeviceAttached)
            {
                Byte[] outputBuffer = new Byte[62];

                //63,21,32
                outputBuffer[0] = 1;
                outputBuffer[1] = 63;
                outputBuffer[2] = 1;
                getDemoDevice().ledCMD(0xDC, outputBuffer);

            }
        }

        private void btnOutputClear_Click(object sender, EventArgs e)
        {
            debugTextBox.Text = "";
        }

        private void btnStg2Byte_Click(object sender, EventArgs e)
        {
            try
            {
                String HexString = txtData.Text.Replace(" ", "");
                int NumberChars = HexString.Length;
                byte[] bytes = new byte[NumberChars / 2];
                for (int i = 0; i < NumberChars; i += 2)
                {
                    bytes[i / 2] = Convert.ToByte(HexString.Substring(i, 2), 16);
                }


                string formatString = String.Format("{0,10:X}{1,10:X}{2,10:X} \r\n", bytes[0], bytes[1], bytes[2]);

                //debugTextBox.Text += formatString;

                bool suc = getDemoDevice().ledCMD2(bytes);
                if (!suc)
                    debugTextBox.Text += "CMD failed.";
            }

            catch
            {
                debugTextBox.Text += "Error converting Hex String.\r\n";
            }
        }

        private void btnSetPID_Click(object sender, EventArgs e)
        {
            try
            {
                String HexString = txtData.Text.Replace(" ", "");
                int NumberChars = HexString.Length;
                byte[] bytes = new byte[NumberChars / 2];
                for (int i = 0; i < NumberChars; i += 2)
                {
                    bytes[i / 2] = Convert.ToByte(HexString.Substring(i, 2), 16);
                }


                string formatString = String.Format("{0,10:X} \r\n", bytes[0]);

                //debugTextBox.Text += formatString;

                bool suc = getDemoDevice().PID_SET(bytes);
                if (!suc)
                    debugTextBox.Text += "PID not set.";
            }

            catch
            {
                debugTextBox.Text += "Error converting Hex String.\r\n";
            }
        }

        private void btnGetPID_Click(object sender, EventArgs e)
        {
            try
            {
                String HexString = txtData.Text.Replace(" ", "");
                int NumberChars = HexString.Length;
                byte[] bytes = new byte[NumberChars / 2];
                for (int i = 0; i < NumberChars; i += 2)
                {
                    bytes[i / 2] = Convert.ToByte(HexString.Substring(i, 2), 16);
                }


                string formatString = String.Format("{0,10:X} \r\n", bytes[0]);

                //debugTextBox.Text += formatString;

                bool suc = getDemoDevice().PID_GET(bytes);

                if (!suc)
                    debugTextBox.Text += "PID get failed.";
            }

            catch
            {
                debugTextBox.Text += "Error converting Hex String.\r\n";
            }
        }


        private bool runFile = false;
        private bool stopFile = false;

        private void setRunFile(bool value)
        {
            runFile = value;
            this.btnRunFile.Enabled = !value;
            this.btnStopFile.Enabled = value;
        }

        private void btnStopFile_Click(object sender, EventArgs e)
        {
            stopFile = true;
        }

        private void btnRunFile_Click(object sender, EventArgs e)
        {
            string file = "./led/" + txtData.Text;
            if (File.Exists(file))
            {
                RunFile(txtData.Text);
            }
            else
            {
                RunFile(@"default.txt");
            }
        }

        private void RunFile(string filename)
        {
            stopFile = false;
            setRunFile(true);

            while (runFile)
            {
                Logger(LogLevels.Info, "Runfile:::" + filename);
                debugTextBox.Text += "+-+-+-+-+-+-+-+-+Runfile::: " + filename + ".\r\n";

                // Was STOP button clicked?
                if (stopFile)
                {
                    break;
                }

                runFile = false; // assume a single run...

                List<string> fileLines = new List<string>();

                if (File.Exists("./led/"+filename))
                {

                    using (var reader = new StreamReader("./led/" + filename))
                    {
                        string line2;
                        while ((line2 = reader.ReadLine()) != null)
                        {
                            fileLines.Add(line2);
                        }
                    }
                }
                else
                {
                    debugTextBox.Text += "SKIPPING --> File NOT found::: " + "./led/" + filename + ".\r\n";
                    Logger(LogLevels.Error, "SKIPPING --> File NOT found::: " + "./led/" + filename + ".");
                }

                int counter = 0;
 
                foreach (string line in fileLines)
                {
                    if (chkPrintLines.Checked)
                    {
                        debugTextBox.Text += "fileLine: " + line + ".\r\n";
                        Logger(LogLevels.Debug, "fileLine: " + line);
                    }

                    Application.DoEvents();

                    // Was STOP button clicked?
                    if (stopFile)
                    {
                        break;
                    }

                    //this.Refresh();
                    //System.Threading.Thread.Yield();
                    Application.DoEvents();

                    if (line.Length > 0)
                    {
                        try
                        {
                            switch (line.ToUpper().Substring(0, 1))
                            {
                                case ("#"):// # indicates a comment line
                                    {                                        
                                        break;
                                    }

                                case ("C"):// dot correct
                                    {
                                        // 20 3F 15
                                        byte r = 0x20; // 32;
                                        byte g = 0x3f; // 63;
                                        byte b = 0x15; // 21;

                                        if (getDemoDevice().isDeviceAttached)
                                        {
                                            String HexString = line.Replace(" ", "");
                                            if (HexString.Length == 7)
                                            {
                                                HexString = HexString.Substring(1, 6);
                                                int NumberChars = HexString.Length;
                                                byte[] bytes = new byte[NumberChars / 2];
                                                for (int i = 0; i < NumberChars; i += 2)
                                                {
                                                    bytes[i / 2] = Convert.ToByte(HexString.Substring(i, 2), 16);
                                                }
                                                r = bytes[0];
                                                g = bytes[1];
                                                b = bytes[2];
                                            }

                                            Byte[] outputBuffer = new Byte[62];

                                            //63,21,32
                                            outputBuffer[2] = r;
                                            outputBuffer[1] = g;
                                            outputBuffer[0] = b;

                                            getDemoDevice().ledCMD(0xDC, outputBuffer);
                                        }
                                        break;
                                    }
                                case ("D"):// D = device select
                                    {
                                        setDevice(line, counter);
                                        break;
                                    }
                                case ("T"):// T = Trigger 
                                    {
                                        chkPndTrig0.Checked = true;
                                        setDevice(line, counter);
                                        break;
                                    }
                                case ("J"): // J = Joystick direction 04 or 08
                                    {
                                        string dir = line.Substring(2, 2);
                                        if (dir.Equals("04"))
                                        {
                                            direction = 0x08;
                                            this.btnDirection_Click(null, null);
                                        }
                                        else
                                        {
                                            direction = 0x04;
                                            this.btnDirection_Click(null, null);
                                        }
                                        break;
                                    }
                                case ("~"):// Tilda is a pause
                                    {
                                        int delay = 1000;
                                        if (line.Length > 2)
                                        {
                                            bool res = int.TryParse(line.Substring(1, line.Length - 1), out delay);
                                        }
                                        System.Threading.Thread.Sleep(delay);
                                        break;
                                    }
                                case (">"): // > = next file to run
                                    {
                                        filename = line.Substring(1, line.Length - 1);
                                        runFile = true;
                                        setRunFile(true);
                                        break;
                                    }
                                case ("^"): // >> = sub file to run
                                    {
                                        filename = line.Substring(1, line.Length - 1);
                                        Logger(LogLevels.Debug, "SubFile: " + filename);
                                        runFile = true;
                                        setRunFile(true);
                                        RunFile(filename);
                                        break;
                                    }

                                default:
                                    {
                                        String HexString = line.Replace(" ", "");
                                        int NumberChars = HexString.Length;
                                        byte[] bytes = new byte[NumberChars / 2];
                                        for (int i = 0; i < NumberChars; i += 2)
                                        {
                                            bytes[i / 2] = Convert.ToByte(HexString.Substring(i, 2), 16);
                                        }


                                        if (bytes[0] == 0x93 || bytes[0] == 0x94)
                                        {
                                            chkPndTrig0.Checked = true;
                                        }



                                        string formatString = String.Format("{0,10:X}{1,10:X}{2,10:X} \r\n", bytes[0], bytes[1], bytes[2]);

                                        //debugTextBox.Text += formatString;

                                        getDemoDevice().ledCMD2(bytes);
                                        break;
                                    }
                            }

                            //
                            while (isPendTrig())
                            {
                                // 
                                if (stopFile || chkTrig0.Checked == true)
                                {
                                    chkPndTrig0.Checked = false;
                                    chkTrig0.Checked = false;
                                    break;
                                }
                                //
                                Application.DoEvents();
                            }
                        }
                        catch
                        {
                            string msg = String.Format("Error on line: {0} CMD: {1} \r\n", counter, line);
                            debugTextBox.Text += msg; //"Error converting Hex String.\r\n";
                            
                            Logger(LogLevels.Error, msg);
                        }
                    }
                    counter++;
                } // end readLine loop
            } // end runFile loop
            setRunFile(false);
        }

        private bool isPendTrig()
        {
            if (chkPndTrig0.Checked || chkPndTrig1.Checked || chkPndTrig2.Checked)
                return true;
            return false;
        }

        private void setDevice(String line, int counter)
        {
            String DeviceString = line.Substring(2, 2);
            switch (DeviceString)
            {
                case "00": rdSelected0.Checked = true; ; break;
                case "01": rdSelected1.Checked = true; ; break;
                case "02": rdSelected2.Checked = true; ; break;
                case "03": rdSelected3.Checked = true; ; break;
                case "04": rdSelected4.Checked = true; ; break;
                default: 
                        debugTextBox.Text += String.Format("Error on line: {0} CMD: {1} \r\n", counter, line);
                        break;
            }
        }

        private void Form1_Load(object sender, EventArgs e)
        {
            // RUN FILE HERE
            if (myArrayList.Count > 0)
            {
                string fileName = (string)myArrayList[0];
                Logger(LogLevels.Info, "Arg[0]: " + fileName);
                RunFile(fileName);

#if (!DEBUG)
                Logger(LogLevels.Info, "Exit(0)");
                Environment.Exit(0);
#endif
            }
        }

        private void Form1_FormClosed(object sender, FormClosedEventArgs e)
        {
            theUsbDemoDevice = null;
            theUsbDemoDevice_1 = null;
            theUsbDemoDevice_2 = null;
            theUsbDemoDevice_3 = null;
            theUsbDemoDevice_4 = null;
            theUsbDemoDevice_5 = null;
            theUsbDemoDevice_6 = null;
            theUsbDemoDevice_7 = null;
            theUsbDemoDevice_8 = null;
            theUsbDemoDevice_9 = null;
        }

        private void btnArgs_Click(object sender, EventArgs e)
        {
            string printString = "List Elements:";

            foreach (object o in myArrayList)
            {
                // Add the fields you want to show here
                printString += "\n\t" + o.ToString();
            }

            MessageBox.Show(printString);
        }

        private Byte direction = 0x00;

        private void btnDirection_Click(object sender, EventArgs e)
        {
            if (getDemoDevice().isDeviceAttached)
            {
                if (direction == 0x04)
                {
                    direction = 0x08;
                    btnDirection.Text = "Direction = 8";
                }
                else
                {
                    direction = 0x04;
                    btnDirection.Text = "Direction = 4";
                }

                getDemoDevice().setJoyDirection(direction);
            }
        }


        private Byte sense = 0x00;
        private void btnMouseSense_Click(object sender, EventArgs e)
        {
            if (getDemoDevice().isDeviceAttached)
            {
                if (sense == 0x01)
                {
                    sense = 0x00;
                    btnMouseSense.Text = "Mouse Sense = L";
                }
                else
                {
                    sense = 0x01;
                    btnMouseSense.Text = "Mouse Sense = H";
                }

                getDemoDevice().setMouseSense(sense);
            }
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
                    if (level.CompareTo(logLevel) > 0)
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
            string sYear = DateTime.Now.Year.ToString();
            string sMonth = DateTime.Now.Month.ToString();
            string sDay = DateTime.Now.Day.ToString();
            sErrorTime = "hid." + sYear + sMonth + sDay + ".log";
        }


        // end of class
        }
    // end of form
    }
