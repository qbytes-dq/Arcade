/********************************************************************
 FileName:     	HardwareProfile - PICDEM FSUSB.h
 Dependencies:  See INCLUDES section
 Processor:     PIC18 USB Microcontrollers
 Hardware:      PICDEM FSUSB
 Compiler:      Microchip C18
 Company:       Microchip Technology, Inc.

 Software License Agreement:

 The software supplied herewith by Microchip Technology Incorporated
 (the “Company”) for its PIC® Microcontroller is intended and
 supplied to you, the Company’s customer, for use solely and
 exclusively on Microchip PIC Microcontroller products. The
 software is owned by the Company and/or its supplier, and is
 protected under applicable copyright laws. All rights are reserved.
 Any use in violation of the foregoing restrictions may subject the
 user to criminal sanctions under applicable laws, as well as to
 civil liability for the breach of the terms and conditions of this
 license.

 THIS SOFTWARE IS PROVIDED IN AN “AS IS” CONDITION. NO WARRANTIES,
 WHETHER EXPRESS, IMPLIED OR STATUTORY, INCLUDING, BUT NOT LIMITED
 TO, IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A
 PARTICULAR PURPOSE APPLY TO THIS SOFTWARE. THE COMPANY SHALL NOT,
 IN ANY CIRCUMSTANCES, BE LIABLE FOR SPECIAL, INCIDENTAL OR
 CONSEQUENTIAL DAMAGES, FOR ANY REASON WHATSOEVER.

********************************************************************
 File Description:

This was released with Microchip Solutions examples. Originally for the 18F4550
but was edited for a 18F2550 for use with a 

Chromation Systems 48 Channel Mono / 16 Channel RGB LED Controller

Modifications to the source project are required for this to work correctly

********************************************************************/

#ifndef ChromSys16RGBUSB_HardwareProfile_H
#define ChromSys16RGBUSB_HardwareProfile_H


////THIS IS NOT AN OPTION ON THIS CONTROLLER
//    //#define USE_SELF_POWER_SENSE_IO
//    #define tris_self_power     TRISAbits.TRISA2    // Input
//    #if defined(USE_SELF_POWER_SENSE_IO)
//    #define self_power          PORTAbits.RA2
//    #else
//    #define self_power          1
//    #endif
//
//
////USB Sense is enabled on this controller on RC0
//    //#define USE_USB_BUS_SENSE_IO
//    #define tris_usb_bus_sense  TRISCbits.TRISC0    // Input
//    #if defined(USE_USB_BUS_SENSE_IO)
//    #define USB_BUS_SENSE       PORTCbits.RC0
//    #else
// //   #define USB_BUS_SENSE       1
//    #endif


    //Uncomment the following line to make the output HEX of this  
    //  project work with the MCHPUSB Bootloader    
 //   #define PROGRAMMABLE_WITH_USB_MCHPUSB_BOOTLOADER
	
    //Uncomment the following line to make the output HEX of this 
    //  project work with the HID Bootloader
 //   #define PROGRAMMABLE_WITH_USB_HID_BOOTLOADER		


    #define CLOCK_FREQ 48000000
    #define GetSystemClock() (CLOCK_FREQ)


/**DEVICE HARDWARE DESCRIPTION ***************************/
//These are device IDs for the proprietary program ColorMotion

#define HardwareID 160 //48 Channel TLC / 16 RGB mode
#define FirmwareV 1

/**CONFIGURATION ***************************/

        #pragma config PLLDIV   = 5         // (20 MHz crystal on PICDEM FS USB board)
        #pragma config CPUDIV   = OSC1_PLL2   
        #pragma config USBDIV   = 2         // Clock source from 96MHz PLL/2
        #pragma config FOSC     = HSPLL_HS
        #pragma config FCMEN    = OFF
        #pragma config IESO     = OFF
        #pragma config PWRT     = OFF
        #pragma config BOR      = OFF
        #pragma config BORV     = 3
        #pragma config VREGEN   = ON      //USB Voltage Regulator
        #pragma config WDT      = OFF
        #pragma config WDTPS    = 32768
        #pragma config MCLRE    = ON
        #pragma config LPT1OSC  = OFF
        #pragma config PBADEN   = OFF
        #pragma config STVREN   = ON
        #pragma config LVP      = OFF
        #pragma config XINST    = OFF       // Extended Instruction Set
        #pragma config CP0      = ON
        #pragma config CP1      = ON
 	 #pragma config CP2      = ON
	 #pragma config CP3      = ON
        #pragma config CPB      = ON
        #pragma config WRT0     = OFF
        #pragma config WRT1     = OFF
        #pragma config WRTB     = OFF       // Boot Block Write Protection
        #pragma config WRTC     = OFF
        #pragma config EBTR0    = OFF
        #pragma config EBTR1    = OFF
        #pragma config EBTRB    = OFF

    
/** SWITCHES *********************************************************/

#define Switch1 PORTBbits.RB4
#define Switch2 PORTBbits.RB3
#define Switch3 PORTBbits.RB2

/** OUTPUT PINS*********************************************************/

#define SCLK LATBbits.LATB1 //SPI Data Shift Clock, SCL/SCK
#define BLANK LATAbits.LATA2 //ResetsCounter, blanks all outs - Gen I/O
#define VPRG LATAbits.LATA3 //changes between Dot and Grey data  - Gen I/O
#define GSCLK LATCbits.LATC2 //CCP1 - grey scale clock
#define XLAT LATBbits.LATB5 //when high, writes data from input register to DC or GS registers  - Gen I/O
#define SIN LATCbits.LATC7 //serial data output, SDO/RX 
#define XERR LATAbits.LATA1 //Error Output, not read  - Gen I/O

/** CONSTANTS*********************************************************/

#define XLATCOUNTH 		0xF4 //62,719
#define XLATCOUNTL 		0xFF
#define NumTLC5940 3 //Change to the amount of TLCs in series

#define DCred 63
#define DCgreen 50
#define DCblue 63

#define FlaTMRconst 60 //used to scale certian patterns

#endif  //HARDWARE_PROFILE_18F2550_H
