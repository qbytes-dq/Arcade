/************************************************************************
	HardwareProfile.h

	WFF USB Generic HID Demonstration 3
    usbGenericHidCommunication reference firmware 3_0_0_0
    Copyright (C) 2011 Simon Inns

    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <http://www.gnu.org/licenses/>.

	Email: simon.inns@gmail.com

************************************************************************/

#ifndef HARDWAREPROFILE_H
#define HARDWAREPROFILE_H

// USB stack hardware selection options ----------------------------------------------------------------

// (This section is the set of definitions required by the MCHPFSUSB framework.)

// Uncomment the following define if you wish to use the self-power sense feature 
// and define the port, pin and tris for the power sense pin below:
// #define USE_SELF_POWER_SENSE_IO
#define tris_self_power     TRISAbits.TRISA2
#if defined(USE_SELF_POWER_SENSE_IO)
	#define self_power      PORTAbits.RA2
#else
	#define self_power          1
#endif

// Uncomment the following define if you wish to use the bus-power sense feature 
// and define the port, pin and tris for the power sense pin below:
//#define USE_USB_BUS_SENSE_IO
#define tris_usb_bus_sense  TRISAbits.TRISA1
#if defined(USE_USB_BUS_SENSE_IO)
	#define USB_BUS_SENSE   PORTAbits.RA1
#else
	#define USB_BUS_SENSE       1
#endif

// Uncomment the following line to make the output HEX of this project work with the MCHPUSB Bootloader    
//#define PROGRAMMABLE_WITH_USB_MCHPUSB_BOOTLOADER

// Uncomment the following line to make the output HEX of this project work with the HID Bootloader
#define PROGRAMMABLE_WITH_USB_HID_BOOTLOADER		

// Application specific hardware definitions ------------------------------------------------------------

// Oscillator frequency (48Mhz with a 20Mhz external oscillator)
#define CLOCK_FREQ 48000000

// Device Vendor Indentifier (VID) (0x04D8 is Microchip's VID)
#define USB_VID	0x04D9

// Device Product Indentifier (PID) (0x0042)
#define USB_PID		0x0999
#define USB_PID_p0	0x0100
#define USB_PID_p1	0x0101
#define USB_PID_p2	0x0102
#define USB_PID_p3	0x0103
#define USB_PID_p4	0x0104
#define USB_PID_p5	0x0105
#define USB_PID_p6	0x0106
#define USB_PID_p7	0x0107
#define USB_PID_p8	0x0108
#define USB_PID_p9	0x0109

// Manufacturer string descriptor
//#define MSDLENGTH	10
#define MSDLENGTH	11
//#define MSD		'S','i','m','o','n',' ','I','n','n','s'
#define MSD		'Q','u','e','s','e','n','b','e','r','r','y'

// Product String descriptor
//#define PSDLENGTH	21
#define PSDLENGTH	14
//#define PSD   'W','F','F',' ','G','e','n','e','r','i','c',' ','H','I','D',' ','d','e','m','o'
//               1   2   3   4   5   6   7   8   9   0   1   2   3   4   5   6   7   8   9   0   1   2   3   4   5   6   7   8   9   0
#define PSD		'Q','-','B','e','r','r','y',' ','L','E','D',' ',35,'?'
#define PSD_p0	'Q','-','B','e','r','r','y',' ','L','E','D',' ',35,'0'
#define PSD_p1	'Q','-','B','e','r','r','y',' ','L','E','D',' ',35,'1'
#define PSD_p2	'Q','-','B','e','r','r','y',' ','L','E','D',' ',35,'2'
#define PSD_p3	'Q','-','B','e','r','r','y',' ','L','E','D',' ',35,'3'
#define PSD_p4	'Q','-','B','e','r','r','y',' ','L','E','D',' ',35,'4'
#define PSD_p5	'Q','-','B','e','r','r','y',' ','L','E','D',' ',35,'5'
#define PSD_p6	'Q','-','B','e','r','r','y',' ','L','E','D',' ',35,'6'
#define PSD_p7	'Q','-','B','e','r','r','y',' ','L','E','D',' ',35,'7'
#define PSD_p8	'Q','-','B','e','r','r','y',' ','L','E','D',' ',35,'8'
#define PSD_p9	'Q','-','B','e','r','r','y',' ','L','E','D',' ',35,'9'


// Device serial number string descriptor
#define DSNLENGTH	10

// Version 3.7.0
//#define DSN		'W','F','F','_','3','.','0'
#define DSN		'Q','B','W',' ','v','3','.','8','.','0'

// Common useful definitions
#define INPUT_PIN  1
#define OUTPUT_PIN 0
#define FLAG_FALSE 0
#define FLAG_TRUE  1

// Comment out the following line if you do not want the debug
// feature of the firmware (saves code and RAM space when off)
//
// Note: if you use this feature you must compile with the large
// memory model on (for 24-bit pointers) so that the sprintf()
// function will work correctly.  If you do not require debug it's
// recommended that you compile with the small memory model and 
// remove any references to <strings.h> and sprintf().
#define DEBUGON

// PIC to hardware pin mapping and control macros

// Led control macros
#define mInitStatusLeds()		LATA &= 0b00000001; TRISA &= 0b00000010;
#define mMouseSpeed				LATAbits.LATA2
#define mJoyZsw1				LATAbits.LATA3
#define mJoyZsw2				LATAbits.LATA4
#define mJoyDirection			LATAbits.LATA5

#define mDebugStatus			LATCbits.LATC0
#define mDebugStatus_on()		mDebugStatus = 1;
#define mDebugStatus_off()		mDebugStatus = 0;
#define mDebugStatus_Toggle()	mDebugStatus = !mDebugStatus;
#define mDebugStatus_Get()      mDebugStatus;

// Switch macros
#define mInitAllSwitches()  TRISAbits.TRISA1=1;
#define mInitSwitch0()      TRISAbits.TRISA1=1;
//#define sw0                 PORTAbits.RA1


#endif
