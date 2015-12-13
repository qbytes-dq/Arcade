/********************************************************************
 FileName:		gamepad.c
 Dependencies:	See INCLUDES section
 Processor:		PIC18 or PIC24 USB Microcontrollers
 Hardware:		The code is natively intended to be used on the following
 				hardware platforms: PICDEM™ FS USB Demo Board, 
 				PIC18F87J50 FS USB Plug-In Module, or
 				Explorer 16 + PIC24 USB PIM.  The firmware may be
 				modified for use on other USB platforms by editing the
 				HardwareProfile.h file.
 Complier:  	Microchip C18 (for PIC18) or C30 (for PIC24)
 Company:		Microchip Technology, Inc.

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

 Change History:
  Rev   Date         Description
  1.0   11/19/2004   Initial release
  2.1   02/26/2007   Updated for simplicity and to use common
                     coding style
********************************************************************/

#ifndef GAMEPAD_C
#define GAMEPAD_C

/** INCLUDES *******************************************************/
#include "GenericTypeDefs.h"
#include "Compiler.h"
#include "usb_config.h"
#include "./USB/usb_device.h"
#include "./USB/usb.h"

#include "HardwareProfile.h"
#include "adc.h"
#include "buttons.h"
#include "spinners.h"
#include "eeprom.h"

#include <delays.h>
//#include "TimeDelay.h" //DelayMs //DelayMs(DELAY_MS);  //#define DELAY_MS    1500
//GetInstructionClock


#include "./USB/usb_function_hid.h"

//#include <p18f4550.h>
#include <p18cxxx.h>
#include <portb.h>

/** CONFIGURATION **************************************************/
#if defined(PICDEM_FS_USB)      // Configuration bits for PICDEM FS USB Demo Board (based on PIC18F4550)
        #pragma config PLLDIV   = 12         // (20 MHz crystal on PICDEM FS USB board)
        #pragma config CPUDIV   = OSC1_PLL2   
        #pragma config USBDIV   = 2         // Clock source from 96MHz PLL/2

//#pragma config FOSC     = HSPLL_HS
// Drives resonator 4,8 and 16 MHz
// Drives 16 MHz crystal
// Drives 48 MHz oscilator
#pragma config FOSC = ECIO_EC   // Oscillator Selection bits (EC oscillator, port function on RA6 (ECIO))

//       #pragma config FCMEM    = OFF
        #pragma config IESO     = OFF
        #pragma config PWRT     = OFF
//        #pragma config BOR      = ON
//        #pragma config BORV     = 3
        #pragma config VREGEN   = ON      //USB Voltage Regulator
        #pragma config WDT      = OFF
        #pragma config WDTPS    = 32768
//------#pragma config MCLRE    = OFF // daq 01/05/2015
        #pragma config MCLRE    = ON
        #pragma config LPT1OSC  = OFF
        #pragma config PBADEN   = OFF	//By programming the Configuration bit,PBADEN (CONFIG3H<1>), RB4:RB0 will alternatively be configured as digital inputs on POR.
//      #pragma config CCP2MX   = ON
        #pragma config STVREN   = ON
        #pragma config LVP      = OFF
//      #pragma config ICPRT    = OFF       // Dedicated In-Circuit Debug/Programming
        #pragma config XINST    = OFF       // Extended Instruction Set
        #pragma config CP0      = OFF
        #pragma config CP1      = OFF
//      #pragma config CP2      = OFF
//      #pragma config CP3      = OFF
        #pragma config CPB      = OFF
//      #pragma config CPD      = OFF
        #pragma config WRT0     = OFF
        #pragma config WRT1     = OFF
//      #pragma config WRT2     = OFF
//      #pragma config WRT3     = OFF
        #pragma config WRTB     = OFF       // Boot Block Write Protection
        #pragma config WRTC     = OFF
//      #pragma config WRTD     = OFF
        #pragma config EBTR0    = OFF
        #pragma config EBTR1    = OFF
//      #pragma config EBTR2    = OFF
//      #pragma config EBTR3    = OFF
        #pragma config EBTRB    = OFF
   
#else
    #error No hardware board defined, see "HardwareProfile.h" and __FILE__
#endif


#define CLK LATCbits.LATC2


/** VARIABLES ******************************************************/
#pragma udata

char buffer[12];//daq
USB_HANDLE lastTransmission;

/** PRIVATE PROTOTYPES *********************************************/
static void InitializeSystem(void);
void ProcessIO(void);
void UserInit(void);
void YourHighPriorityISRCode();
void YourLowPriorityISRCode();
void Joystick(void);

/** VECTOR REMAPPING ***********************************************/
#if defined(__18CXX)
	//On PIC18 devices, addresses 0x00, 0x08, and 0x18 are used for
	//the reset, high priority interrupt, and low priority interrupt
	//vectors.  However, the current Microchip USB bootloader 
	//examples are intended to occupy addresses 0x00-0x7FF or
	//0x00-0xFFF depending on which bootloader is used.  Therefore,
	//the bootloader code remaps these vectors to new locations
	//as indicated below.  This remapping is only necessary if you
	//wish to program the hex file generated from this project with
	//the USB bootloader.  If no bootloader is used, edit the
	//usb_config.h file and comment out the following defines:
	//#define PROGRAMMABLE_WITH_USB_HID_BOOTLOADER
	//#define PROGRAMMABLE_WITH_USB_LEGACY_CUSTOM_CLASS_BOOTLOADER
	
	#if defined(PROGRAMMABLE_WITH_USB_HID_BOOTLOADER)
		#define REMAPPED_RESET_VECTOR_ADDRESS			0x1000
		#define REMAPPED_HIGH_INTERRUPT_VECTOR_ADDRESS	0x1008
		#define REMAPPED_LOW_INTERRUPT_VECTOR_ADDRESS	0x1018
	#elif defined(PROGRAMMABLE_WITH_USB_MCHPUSB_BOOTLOADER)	
		#define REMAPPED_RESET_VECTOR_ADDRESS			0x800
		#define REMAPPED_HIGH_INTERRUPT_VECTOR_ADDRESS	0x808
		#define REMAPPED_LOW_INTERRUPT_VECTOR_ADDRESS	0x818
	#else	
		#define REMAPPED_RESET_VECTOR_ADDRESS			0x00
		#define REMAPPED_HIGH_INTERRUPT_VECTOR_ADDRESS	0x08
		#define REMAPPED_LOW_INTERRUPT_VECTOR_ADDRESS	0x18
	#endif
	
	#if defined(PROGRAMMABLE_WITH_USB_HID_BOOTLOADER)||defined(PROGRAMMABLE_WITH_USB_MCHPUSB_BOOTLOADER)
	extern void _startup (void);        // See c018i.c in your C18 compiler dir
	#pragma code REMAPPED_RESET_VECTOR = REMAPPED_RESET_VECTOR_ADDRESS
	void _reset (void)
	{
	    _asm goto _startup _endasm
	}
	#endif
	#pragma code REMAPPED_HIGH_INTERRUPT_VECTOR = REMAPPED_HIGH_INTERRUPT_VECTOR_ADDRESS
	void Remapped_High_ISR (void)
	{
	     _asm goto YourHighPriorityISRCode _endasm
	}
	#pragma code REMAPPED_LOW_INTERRUPT_VECTOR = REMAPPED_LOW_INTERRUPT_VECTOR_ADDRESS
	void Remapped_Low_ISR (void)
	{
	     _asm goto YourLowPriorityISRCode _endasm
	}
	
	#if defined(PROGRAMMABLE_WITH_USB_HID_BOOTLOADER)||defined(PROGRAMMABLE_WITH_USB_MCHPUSB_BOOTLOADER)
	//Note: If this project is built while one of the bootloaders has
	//been defined, but then the output hex file is not programmed with
	//the bootloader, addresses 0x08 and 0x18 would end up programmed with 0xFFFF.
	//As a result, if an actual interrupt was enabled and occured, the PC would jump
	//to 0x08 (or 0x18) and would begin executing "0xFFFF" (unprogrammed space).  This
	//executes as nop instructions, but the PC would eventually reach the REMAPPED_RESET_VECTOR_ADDRESS
	//(0x1000 or 0x800, depending upon bootloader), and would execute the "goto _startup".  This
	//would effective reset the application.
	
	//To fix this situation, we should always deliberately place a 
	//"goto REMAPPED_HIGH_INTERRUPT_VECTOR_ADDRESS" at address 0x08, and a
	//"goto REMAPPED_LOW_INTERRUPT_VECTOR_ADDRESS" at address 0x18.  When the output
	//hex file of this project is programmed with the bootloader, these sections do not
	//get bootloaded (as they overlap the bootloader space).  If the output hex file is not
	//programmed using the bootloader, then the below goto instructions do get programmed,
	//and the hex file still works like normal.  The below section is only required to fix this
	//scenario.
	#pragma code HIGH_INTERRUPT_VECTOR = 0x08
	void High_ISR (void)
	{
	     _asm goto REMAPPED_HIGH_INTERRUPT_VECTOR_ADDRESS _endasm
	}
	#pragma code LOW_INTERRUPT_VECTOR = 0x18
	void Low_ISR (void)
	{
	     _asm goto REMAPPED_LOW_INTERRUPT_VECTOR_ADDRESS _endasm
	}
	#endif	//end of "#if defined(PROGRAMMABLE_WITH_USB_HID_BOOTLOADER)||defined(PROGRAMMABLE_WITH_USB_LEGACY_CUSTOM_CLASS_BOOTLOADER)"

	#pragma code

	//=====================================================================
	//=====================================================================
	//=====================================================================
	//=====================================================================
	//=====================================================================
	//=====================================================================
	//=====================================================================
	//=====================================================================
	//=====================================================================
	//=====================================================================
//http://pickandplace.wordpress.com/2012/05/16/2d-positioning-hacking-an-optical-mouse/

/*
Each port has three registers for its operation. These registers are:
--TRIS register (data direction register)
--PORT register (reads the levels on the pins of the device)
--LAT register (output latch)
*/
signed char DZ;
signed char DZR;
signed char DZC=0x7f;
//int DZD=6;
int DZD=10;

char zAxisType=0x00;

char zAxisDial;
char zAxisSlide;
char zAxisRotate;

#define SDIO_PORT               PORTCbits.RC1
#define SDIO_LAT                LATCbits.LATC1
#define SDIO_TRIS               TRISCbits.TRISC1

#define SCLK                    LATCbits.LATC0
#define SCLK_TRIS               TRISCbits.TRISC0

//#define PD                      LATCbits.LATC5
//#define PD_TRIS                 TRISCbits.TRISC5

void WriteSensor_C01(unsigned int address, unsigned int data)
{	
    unsigned int bitcounter;

    bitcounter = 0;
    address = address | 0b10000000; //Set the MSB of the adress to 1
    SDIO_LAT = 1;
    SDIO_TRIS = 0; //Output
    SCLK_TRIS = 0;
    SCLK = 1;
    while(bitcounter <8)
    {
        SCLK = 0; //Lower Clock
        Nop();
        if(address & 0b10000000 )
            SDIO_LAT  = 1;
        else
            SDIO_LAT  = 0;
        Nop();
        Nop();
        SCLK = 1; //High pulse on clock
        Nop();  //Let the sensor read the sent bit.
        address = address <<1;
        bitcounter++;
    }
    bitcounter = 0;
    while(bitcounter <8)
    {
        SCLK = 0; //Lower Clock
        Nop();
        if(data & 0b10000000 )
            SDIO_LAT  = 1;
        else
            SDIO_LAT  = 0;
        Nop();
        SCLK = 1; //High pulse on clock
        Nop();
        Nop();  //Let the sensor read the sent bit.
        data = data <<1;
        bitcounter++;
    }
} //end WriteSensor

unsigned int ReadSensor_C01(unsigned int address)
{
    unsigned int bitcounter;
    unsigned int res;
    res = 0;
    bitcounter = 0;
    address = address & 0b01111111; //Set the MSB of the adress to 0 (read)
    SDIO_LAT  = 1;
    SDIO_TRIS = 0; //Output
    SCLK = 1;
    //Start to write the address of the register we want to read from
    while(bitcounter <8)
    {
        SCLK = 0; //Lower Clock
        if(address & 0b10000000 )
            SDIO_LAT  = 1; //Change the output to match the bit we want to send
        else
            SDIO_LAT  = 0;
        SCLK = 1; //High pulse on clock
        address = address <<1; //Shift the next bit to send
        bitcounter++; //Inc the bit counter
    }
    //We have to wait at least 100us
    SDIO_TRIS = 1;
    for(bitcounter=0;bitcounter<0x10;bitcounter++)
        Nop();
    //Configure the SDIO pin as an input
    SDIO_LAT  = 1;
    SDIO_TRIS = 1; //Input
    SDIO_TRIS = 1; //Input
    bitcounter=0;
    while(bitcounter <8)
    {
        SCLK = 0; //Lower the Clock line
        //Nop(); //Works without the Nop
        SCLK = 1; //Set the Clock line
        res = res <<1; //Shift the received bit in
        if(SDIO_PORT )
            res  = res | 0b00000001; //Read the current bit
        else
            res  = res & 0b11111110;
        bitcounter++;
    }
    SDIO_TRIS = 0;
    SDIO_LAT  = 1;
    SCLK = 1;
    return (res); //Return with the read byte
}//End ReadSensor


	//=====================================================================
	//=====================================================================
	//=====================================================================
	//=====================================================================
	//=====================================================================
	//=====================================================================
	//=====================================================================
	//=====================================================================
	//=====================================================================
	//=====================================================================

//#define DY							0x02
//#define DX							0x03
#define STATUS							0x16
#define DX								0x17
#define DY								0x18
//#define DY							0x41
//#define DX							0x42

#define DataIn()  TRISEbits.TRISE1=1; TRISEbits.TRISE2=1; 
#define DataOut() TRISEbits.TRISE1=0; TRISEbits.TRISE2=1;  

#define DIRDATA		LATEbits.LATE1
#define MOUSE_DATA	PORTEbits.RE1
#define MOUSE_CLK	PORTEbits.RE2
	//=====================================================================
	// Read optical mouse movement.	
	//=====================================================================
	signed short ReadSensor_E12(register unsigned short int address){

    signed short ret = 0;
    signed short i = 0;
   
	// ==================================================
	// Write the address of the register we want to read: 
//	DataOut();
 TRISE   = 0b00000000;  // all Pins are output. 
 
    //write address of register to be read
    for(i=7;i>=0;i--){
        MOUSE_CLK = 0;      
	    Delay10TCYx(2);
        MOUSE_DATA = 1 && ((address & (1<<i)));            
	    Delay10TCYx(2);
        MOUSE_CLK = 1;
 		Delay10TCYx(5);
        }

	MOUSE_DATA = 0;

// ==================================================

	// Switch data line from OUTPUT to INPUT...direction READING
	//DataIn();
	TRISE   = 0b00000010;  // Pin input. 
	// Wait a bit...for data to load
   	Delay10TCYx(120);   //     Delay_us(100);

// ==================================================
	// Fetch the data!  //read the data
    for(i=7;i>=0;i--)  {
        MOUSE_CLK = 0; 
 		Delay10TCYx(7);
        MOUSE_CLK = 1; 
        Delay10TCYx(5);

        ret |= PORTEbits.RE1 << i;        
        }
 
	// ==================================================        
	// IR Mouse exit

	//DataOut();
	TRISE   = 0b00000000;  // all Pins are output. 
	MOUSE_DATA = 0;

   	Delay10TCYx(120);   //     Delay_us(100);
               
    return ret;
}

	//=====================================================================
	//These are your actual interrupt handling routines.
	#pragma interrupt YourHighPriorityISRCode
	void YourHighPriorityISRCode()
	{
		//Check which interrupt flag caused the interrupt.
		//Service the interrupt
		//Clear the interrupt flag
		//Etc.
		if (INTCONbits.INT0IF && 1==0)
		{

			//Clear the interrupt flag
			INTCONbits.INT0IF = 0;
		}	
	}	




	//=====================================================================
	//This return will be a "retfie fast", since this is in a #pragma interrupt section 
	#pragma interruptlow YourLowPriorityISRCode
	void YourLowPriorityISRCode()
	{
		//Check which interrupt flag caused the interrupt.
		//Service the interrupt
		//Clear the interrupt flag
		//Etc.

	    // -----------------------
	    // Low Priority Interrupts
	    // -----------------------    
	
		//    if (INTCONbits.TMR0IF)
		if (INTCONbits.T0IE && INTCONbits.T0IF)
		    {
			
			// Timer interrupt
			CLK = ~CLK;
			// 100 Hz
			TMR0H	 = 0x15;
			TMR0L	 = 0xA0;
			
			INTCONbits.INT0IF = 0;
			INTCONbits.T0IF=0;
		    }

	}	//This return will be a "retfie", since this is in a #pragma interruptlow section 

#elif defined(__C30__)
    #if defined(PROGRAMMABLE_WITH_USB_HID_BOOTLOADER)
        /*
         *	ISR JUMP TABLE
         *
         *	It is necessary to define jump table as a function because C30 will
         *	not store 24-bit wide values in program memory as variables.
         *
         *	This function should be stored at an address where the goto instructions 
         *	line up with the remapped vectors from the bootloader's linker script.
         *  
         *  For more information about how to remap the interrupt vectors,
         *  please refer to AN1157.  An example is provided below for the T2
         *  interrupt with a bootloader ending at address 0x1400
         */
        void __attribute__ ((address(0x1404))) ISRTable(){
        
        	asm("reset"); //reset instruction to prevent runaway code
        	asm("goto %0"::"i"(&_T2Interrupt));  //T2Interrupt's address
        }
    #endif
#endif




/** DECLARATIONS ***************************************************/
#pragma code

/********************************************************************
 * Function:        void main(void)
 *
 * PreCondition:    None
 *
 * Input:           None
 *
 * Output:          None
 *
 * Side Effects:    None
 *
 * Overview:        Main program entry point.
 *
 * Note:            None
 *******************************************************************/
	//=====================================================================
	//=====================================================================
	//=====================================================================

#if defined(__18CXX)
void main(void)
#else
int main(void)
#endif
{

    RCONbits.IPEN = 1;            // Enable interrupt priority 
    INTCONbits.PEIE = 1;          // interrupts allowed
    INTCONbits.GIE = 1;             
    INTCONbits.GIEH = 1;
    INTCONbits.GIEL = 1;
	
	//T0CON = 0b10111111;           // 16 bit timer, prescaler 1:256, TMR0 on
	//            1 = enable 
	//             1 = 8 bit
	//                0 =  use pre-scale
	
	//Timer0
	//Prescaler 1:2; TMR0 Preload = 5536; Actual Interrupt Time : 10 ms
	// 100 Hz
	  T0CON	 = 0x80;
	  TMR0H	 = 0x15;
	  TMR0L	 = 0xA0;


    INTCON2bits.TMR0IP = 0;       // interrupt priority 0
    INTCONbits.TMR0IE = 1;        // timer0 interrupt enabled

    // Clear the peripheral interrupt flags
    PIR1 = 0;
	// ===========================
	//http://ww1.microchip.com/downloads/en/devicedoc/51295e.pdf
	//OpenRB0INT (PORTB_CHANGE_INT_ON &
	//			PORTB_PULLUPS_OFF &
	//			RISING_EDGE_INT);
	// ============================
    InitializeSystem();
    
    // ==================================================
	// wait for TSPTT - opti mouse reset spio
 	TRISE   = 0b00000000;  // all Pins are output. 
 	
 	MOUSE_DATA = 0;
 		
 	MOUSE_CLK = 1;       
	Delay100TCYx(5);  	
 	MOUSE_CLK = 0;       
	Delay100TCYx(5);
 	MOUSE_CLK = 1;
 	
    Delay10KTCYx(255);
    Delay10KTCYx(255);
    Delay10KTCYx(255);
    Delay10KTCYx(255);
    // ==================================================

    while(1)
    {
		// Check bus status and service USB interrupts.
        USBDeviceTasks(); // Interrupt or polling method.  If using polling, must call
        				  // this function periodically.  This function will take care
        				  // of processing and responding to SETUP transactions 
        				  // (such as during the enumeration process when you first
        				  // plug in).  USB hosts require that USB devices should accept
        				  // and process SETUP packets in a timely fashion.  Therefore,
        				  // when using polling, this function should be called 
        				  // frequently (such as once about every 100 microseconds) at any
        				  // time that a SETUP packet might reasonably be expected to
        				  // be sent by the host to your device.  In most cases, the
        				  // USBDeviceTasks() function does not take very long to
        				  // execute (~50 instruction cycles) before it returns.
    				  
		// Check the spinners for movement....
		Spinner_Move();

		// Application-specific tasks.
		// Application related code may be added here, or in the ProcessIO() function.
        ProcessIO(); 
        
        // Show clock
		//CLK = ~CLK;  //	LATCbits.LATC2


		
    }//end while
}//end main

	//=====================================================================
	//=====================================================================
	//=====================================================================

/********************************************************************
 * Function:        static void InitializeSystem(void)
 *
 * PreCondition:    None
 *
 * Input:           None
 *
 * Output:          None
 *
 * Side Effects:    None
 *
 * Overview:        InitializeSystem is a centralize initialization
 *                  routine. All required USB initialization routines
 *                  are called from here.
 *
 *                  User application initialization routine should
 *                  also be called from here.                  
 *
 * Note:            None
 *******************************************************************/
static void InitializeSystem(void)
{
    #if (defined(__18CXX))
        ADCON1 |= 0x0F;                 // Default all pins to digital
    #elif defined(__C30__)
        AD1PCFGL = 0xFFFF;
    #endif


//	The USB specifications require that USB peripheral devices must never source
//	current onto the Vbus pin.  Additionally, USB peripherals should not source
//	current on D+ or D- when the host/hub is not actively powering the Vbus line.
//	When designing a self powered (as opposed to bus powered) USB peripheral
//	device, the firmware should make sure not to turn on the USB module and D+
//	or D- pull up resistor unless Vbus is actively powered.  Therefore, the
//	firmware needs some means to detect when Vbus is being powered by the host.
//	A 5V tolerant I/O pin can be connected to Vbus (through a resistor), and
// 	can be used to detect when Vbus is high (host actively powering), or low
//	(host is shut down or otherwise not supplying power).  The USB firmware
// 	can then periodically poll this I/O pin to know when it is okay to turn on
//	the USB module/D+/D- pull up resistor.  When designing a purely bus powered
//	peripheral device, it is not possible to source current on D+ or D- when the
//	host is not actively providing power on Vbus. Therefore, implementing this
//	bus sense feature is optional.  This firmware can be made to use this bus
//	sense feature by making sure "USE_USB_BUS_SENSE_IO" has been defined in the
//	HardwareProfile.h file.    
    #if defined(USE_USB_BUS_SENSE_IO)
    tris_usb_bus_sense = INPUT_PIN; // See HardwareProfile.h
    #endif
    
//	If the host PC sends a GetStatus (device) request, the firmware must respond
//	and let the host know if the USB peripheral device is currently bus powered
//	or self powered.  See chapter 9 in the official USB specifications for details
//	regarding this request.  If the peripheral device is capable of being both
//	self and bus powered, it should not return a hard coded value for this request.
//	Instead, firmware should check if it is currently self or bus powered, and
//	respond accordingly.  If the hardware has been configured like demonstrated
//	on the PICDEM FS USB Demo Board, an I/O pin can be polled to determine the
//	currently selected power source.  On the PICDEM FS USB Demo Board, "RA2" 
//	is used for	this purpose.  If using this feature, make sure "USE_SELF_POWER_SENSE_IO"
//	has been defined in HardwareProfile.h, and that an appropriate I/O pin has been mapped
//	to it in HardwareProfile.h.
    #if defined(USE_SELF_POWER_SENSE_IO)
    tris_self_power = INPUT_PIN;	// See HardwareProfile.h
    #endif
    
    // This must be before USBDeviceInit so SetPlayer will work!!!
    // This must be before USBDeviceInit so SetPlayer will work!!!
    // This must be before USBDeviceInit so SetPlayer will work!!!
    UserInit();

    USBDeviceInit();	//usb_device.c.  Initializes USB module SFRs and firmware
    					//variables to known states.
}//end InitializeSystem



/******************************************************************************
 * Function:        void UserInit(void)
 *
 * PreCondition:    None
 *
 * Input:           None
 *
 * Output:          None
 *
 * Side Effects:    None
 *
 * Overview:        This routine should take care of all of the demo code
 *                  initialization that is required.
 *
 * Note:            
 *
 *****************************************************************************/
void UserInit(void)
{
	//ADC initialisieren
	Init_ADC();

	//Buttons initialisieren
	Button_Init();

	// Spinner initialisation
	Spinners_Init();

	// Set device ID, PlayerID
	SetPlayer(EEPROM_getPlayer());

    //initialize the variable holding the handle for the last transmission
    lastTransmission = 0;

}//end UserInit


unsigned char overflow_test_inc(unsigned char a, unsigned char b)
 {
    unsigned int result = a + b;
    return result < a || result < b;
 }
 
 unsigned char overflow_test_dec(unsigned char a, unsigned char b)
 {
    unsigned int result = a - b;
    return result > a;
 }

/********************************************************************
 * Function:        void ProcessIO(void)
 *	
 * PreCondition:    None
 *
 * Input:           None
 *
 * Output:          None
 *
 * Side Effects:    None
 *
 * Overview:        This function is a place holder for other user
 *                  routines. It is a mixture of both USB and
 *                  non-USB tasks.
 *
 * Note:            None
 *******************************************************************/
void ProcessIO(void)
{   
    // User Application USB tasks
    if((USBDeviceState < CONFIGURED_STATE)||(USBSuspendControl==1)) return;

    //Call the function that behaves like a joystick   
    Joystick();        
}//end ProcessIO

void Joystick(void)
{
	// Flip LED on each transmission to the host --  daq
//	CLK = ~CLK;  //	LATCbits.LATC2

	UP_ADC();
	
    if(HIDTxHandleBusy(lastTransmission) == 0)
    {	
		//UP_ADC();
		UP_Button();
	
		// Update spinner counts
		UP_Spinner();
		
		// X, Y & Z
		hid_report_in[0] = J_ButtonsX;// X-Achse
		hid_report_in[1] = J_ButtonsY;// Y-Achse
//		hid_report_in[2] = MY_Spinner[0];// Z-Achse
		
		// X, Y & Z Rotate
		hid_report_in[3] = ADC_Out_0;  //PORTA;//ADC_Out_3;	// Rx-Rotate
		hid_report_in[4] = ADC_Out_1;  //~PORTA;//ADC_Out_4;// Ry-Rotatee		
//		hid_report_in[3] = ReadSensor_C01(DX);	// Rx-Rotate
//		hid_report_in[4] = ReadSensor_C01(DY);	// Ry-Rotatee
//		hid_report_in[3] = ReadSensor_C56(DX);	// Rx-Rotate
//		hid_report_in[4] = ReadSensor_C56(DY);	// Ry-Rotatee


//#define MOUSE_CLK PORTEbits.RE2
//LATEbits.LATE2=0;
//MOUSE_CLK = ~MOUSE_CLK;

//		hid_report_in[5] = MY_Spinner[1];//ADC_Out_2;	// Rz-Rotate


//hid_report_in[7] = 	ReadSensor_E12(DY)+128;	// Slide


		// Slider & Dial
		DZR = DZ = ReadSensor_E12(DX);

		//hid_report_in[7] += (DZ/DZD);	// Slide
		zAxisSlide += (DZ/DZD);	// Slide
		
		if (DZ < 0x80)
		{// Increment
			if (overflow_test_inc((signed char) DZC, (signed char) (DZ/DZD)))
				DZC = 255;
			else
				DZC += (DZ/DZD);
		}		
		else
		{// Decrement
			DZ = ~DZ;//Inverse the number. (change FF to abs(-1))
			if (overflow_test_dec((signed char) DZC, (signed char) (DZ/DZD)))
				DZC = 0;
			else
				DZC -= (DZ/DZD);
		}		

	zAxisDial = DZC;	       // Dial
	zAxisRotate = DZR + 128;   // Rz-Rotate

zAxisType = (~RC_Buttons2) & 0b00000011;
if (zAxisType == 0b00000000)
{
		hid_report_in[2] = 0x80;// Z-Achse is hard coded center
}
else 
if (zAxisType == 0b00000001)
{
		hid_report_in[2] = zAxisRotate;// Z-Achse is Dial w/center -->|<-- (Auto center)
}
else 
if (zAxisType == 0b00000010)
{
		hid_report_in[2] = zAxisDial;// Z-Achse is Slide  |<---->| (Side to Side)
} 
else
{//(zAxisType == 0x11)
		hid_report_in[2] = zAxisSlide;// Z-Achse is Rotate >-----> (Loop around)
}

hid_report_in[5] = 0x00;
hid_report_in[6] = 0x00;
hid_report_in[7] = 0x00;

//		hid_report_in[8]++;// = ReadSensor_E12(DY)+128;	// Dial   ???? what is the???

		//===============???
//		hid_report_in[8] = readRegister(0xAA);//ADC_Out_5;	// ??????
		
		// button sets 1, 2 & 3
		hid_report_in[9]  = RC_Buttons0;	    //PortB; Einzeltaster -- Single button
	    hid_report_in[10] = RC_Buttons1;	//PortD; Einzeltaster -- Single button	
//		hid_report_in[11] = zAxisType;
		hid_report_in[11] = 0x00;
//		hid_report_in[11] = ReadSensor_E12(STATUS);	// Status
		
	   	//Send the x byte packet over USB to the host.
		//lastTransmission = HIDTxPacket(HID_EP, (BYTE*)hid_report_in, 0x0c); //0x09);
		lastTransmission = HIDTxPacket(HID_EP, (BYTE*)hid_report_in, sizeof(hid_report_in));
    }
    return;		
}//end Joystick()


// ******************************************************************************************************
// ************** USB Callback Functions ****************************************************************
// ******************************************************************************************************
// The USB firmware stack will call the callback functions USBCBxxx() in response to certain USB related
// events.  For example, if the host PC is powering down, it will stop sending out Start of Frame (SOF)
// packets to your device.  In response to this, all USB devices are supposed to decrease their power
// consumption from the USB Vbus to <2.5mA each.  The USB module detects this condition (which according
// to the USB specifications is 3+ms of no bus activity/SOF packets) and then calls the USBCBSuspend()
// function.  You should modify these callback functions to take appropriate actions for each of these
// conditions.  For example, in the USBCBSuspend(), you may wish to add code that will decrease power
// consumption from Vbus to <2.5mA (such as by clock switching, turning off LEDs, putting the
// microcontroller to sleep, etc.).  Then, in the USBCBWakeFromSuspend() function, you may then wish to
// add code that undoes the power saving things done in the USBCBSuspend() function.

// The USBCBSendResume() function is special, in that the USB stack will not automatically call this
// function.  This function is meant to be called from the application firmware instead.  See the
// additional comments near the function.

/******************************************************************************
 * Function:        void USBCBSuspend(void)
 *
 * PreCondition:    None
 *
 * Input:           None
 *
 * Output:          None
 *
 * Side Effects:    None
 *
 * Overview:        Call back that is invoked when a USB suspend is detected
 *
 * Note:            None
 *****************************************************************************/
void USBCBSuspend(void)
{
	//Example power saving code.  Insert appropriate code here for the desired
	//application behavior.  If the microcontroller will be put to sleep, a
	//process similar to that shown below may be used:
	
	//ConfigureIOPinsForLowPower();
	//SaveStateOfAllInterruptEnableBits();
	//DisableAllInterruptEnableBits();
	//EnableOnlyTheInterruptsWhichWillBeUsedToWakeTheMicro();	//should enable at least USBActivityIF as a wake source
	//Sleep();
	//RestoreStateOfAllPreviouslySavedInterruptEnableBits();	//Preferrably, this should be done in the USBCBWakeFromSuspend() function instead.
	//RestoreIOPinsToNormal();									//Preferrably, this should be done in the USBCBWakeFromSuspend() function instead.

	//IMPORTANT NOTE: Do not clear the USBActivityIF (ACTVIF) bit here.  This bit is 
	//cleared inside the usb_device.c file.  Clearing USBActivityIF here will cause 
	//things to not work as intended.	
	

//    #if defined(__C30__)
//    #if 0
//        U1EIR = 0xFFFF;
//        U1IR = 0xFFFF;
//        U1OTGIR = 0xFFFF;
//        IFS5bits.USB1IF = 0;
//        IEC5bits.USB1IE = 1;
//        U1OTGIEbits.ACTVIE = 1;
//        U1OTGIRbits.ACTVIF = 1;
//        TRISA &= 0xFF3F;
//        LATAbits.LATA6 = 1;
//        Sleep();
//        LATAbits.LATA6 = 0;
//    #endif
//    #endif
}


/******************************************************************************
 * Function:        void _USB1Interrupt(void)
 *
 * PreCondition:    None
 *
 * Input:           None
 *
 * Output:          None
 *
 * Side Effects:    None
 *
 * Overview:        This function is called when the USB interrupt bit is set
 *					In this example the interrupt is only used when the device
 *					goes to sleep when it receives a USB suspend command
 *
 * Note:            None
 *****************************************************************************/
#if 0
void __attribute__ ((interrupt)) _USB1Interrupt(void)
{
    #if !defined(self_powered)
        if(U1OTGIRbits.ACTVIF)
        {
            //LATAbits.LATA7 = 1;
        
            IEC5bits.USB1IE = 0;
            U1OTGIEbits.ACTVIE = 0;
            IFS5bits.USB1IF = 0;
        
            //USBClearInterruptFlag(USBActivityIFReg,USBActivityIFBitNum);
            USBClearInterruptFlag(USBIdleIFReg,USBIdleIFBitNum);
            //USBSuspendControl = 0;
            //LATAbits.LATA7 = 0;
        }
    #endif
}
#endif

/******************************************************************************
 * Function:        void USBCBWakeFromSuspend(void)
 *
 * PreCondition:    None
 *
 * Input:           None
 *
 * Output:          None
 *
 * Side Effects:    None
 *
 * Overview:        The host may put USB peripheral devices in low power
 *					suspend mode (by "sending" 3+ms of idle).  Once in suspend
 *					mode, the host may wake the device back up by sending non-
 *					idle state signalling.
 *					
 *					This call back is invoked when a wakeup from USB suspend 
 *					is detected.
 *
 * Note:            None
 *****************************************************************************/
void USBCBWakeFromSuspend(void)
{
	// If clock switching or other power savings measures were taken when
	// executing the USBCBSuspend() function, now would be a good time to
	// switch back to normal full power run mode conditions.  The host allows
	// a few milliseconds of wakeup time, after which the device must be 
	// fully back to normal, and capable of receiving and processing USB
	// packets.  In order to do this, the USB module must receive proper
	// clocking (IE: 48MHz clock must be available to SIE for full speed USB
	// operation).
}

/********************************************************************
 * Function:        void USBCB_SOF_Handler(void)
 *
 * PreCondition:    None
 *
 * Input:           None
 *
 * Output:          None
 *
 * Side Effects:    None
 *
 * Overview:        The USB host sends out a SOF packet to full-speed
 *                  devices every 1 ms. This interrupt may be useful
 *                  for isochronous pipes. End designers should
 *                  implement callback routine as necessary.
 *
 * Note:            None
 *******************************************************************/
void USBCB_SOF_Handler(void)
{
    // No need to clear UIRbits.SOFIF to 0 here.
    // Callback caller is already doing that.
}

/*******************************************************************
 * Function:        void USBCBErrorHandler(void)
 *
 * PreCondition:    None
 *
 * Input:           None
 *
 * Output:          None
 *
 * Side Effects:    None
 *
 * Overview:        The purpose of this callback is mainly for
 *                  debugging during development. Check UEIR to see
 *                  which error causes the interrupt.
 *
 * Note:            None
 *******************************************************************/
void USBCBErrorHandler(void)
{
    // No need to clear UEIR to 0 here.
    // Callback caller is already doing that.

	// Typically, user firmware does not need to do anything special
	// if a USB error occurs.  For example, if the host sends an OUT
	// packet to your device, but the packet gets corrupted (ex:
	// because of a bad connection, or the user unplugs the
	// USB cable during the transmission) this will typically set
	// one or more USB error interrupt flags.  Nothing specific
	// needs to be done however, since the SIE will automatically
	// send a "NAK" packet to the host.  In response to this, the
	// host will normally retry to send the packet again, and no
	// data loss occurs.  The system will typically recover
	// automatically, without the need for application firmware
	// intervention.
	
	// Nevertheless, this callback function is provided, such as
	// for debugging purposes.
}


/*******************************************************************
 * Function:        void USBCBCheckOtherReq(void)
 *
 * PreCondition:    None
 *
 * Input:           None
 *
 * Output:          None
 *
 * Side Effects:    None
 *
 * Overview:        When SETUP packets arrive from the host, some
 * 					firmware must process the request and respond
 *					appropriately to fulfill the request.  Some of
 *					the SETUP packets will be for standard
 *					USB "chapter 9" (as in, fulfilling chapter 9 of
 *					the official USB specifications) requests, while
 *					others may be specific to the USB device class
 *					that is being implemented.  For example, a HID
 *					class device needs to be able to respond to
 *					"GET REPORT" type of requests.  This
 *					is not a standard USB chapter 9 request, and 
 *					therefore not handled by usb_device.c.  Instead
 *					this request should be handled by class specific 
 *					firmware, such as that contained in usb_function_hid.c.
 *
 * Note:            None
 *******************************************************************/
void USBCBCheckOtherReq(void)
{
    USBCheckHIDRequest();
}//end


/*******************************************************************
 * Function:        void USBCBStdSetDscHandler(void)
 *
 * PreCondition:    None
 *
 * Input:           None
 *
 * Output:          None
 *
 * Side Effects:    None
 *
 * Overview:        The USBCBStdSetDscHandler() callback function is
 *					called when a SETUP, bRequest: SET_DESCRIPTOR request
 *					arrives.  Typically SET_DESCRIPTOR requests are
 *					not used in most applications, and it is
 *					optional to support this type of request.
 *
 * Note:            None
 *******************************************************************/
void USBCBStdSetDscHandler(void)
{
    // Must claim session ownership if supporting this request
}//end


/*******************************************************************
 * Function:        void USBCBInitEP(void)
 *
 * PreCondition:    None
 *
 * Input:           None
 *
 * Output:          None
 *
 * Side Effects:    None
 *
 * Overview:        This function is called when the device becomes
 *                  initialized, which occurs after the host sends a
 * 					SET_CONFIGURATION (wValue not = 0) request.  This 
 *					callback function should initialize the endpoints 
 *					for the device's usage according to the current 
 *					configuration.
 *
 * Note:            None
 *******************************************************************/
void USBCBInitEP(void)
{
    //enable the HID endpoint
    USBEnableEndpoint(HID_EP,USB_IN_ENABLED|USB_HANDSHAKE_ENABLED|USB_DISALLOW_SETUP);
//daq    USBEnableEndpoint(HID_EP_J1,USB_IN_ENABLED|USB_HANDSHAKE_ENABLED|USB_DISALLOW_SETUP);
}

/********************************************************************
 * Function:        void USBCBSendResume(void)
 *
 * PreCondition:    None
 *
 * Input:           None
 *
 * Output:          None
 *
 * Side Effects:    None
 *
 * Overview:        The USB specifications allow some types of USB
 * 					peripheral devices to wake up a host PC (such
 *					as if it is in a low power suspend to RAM state).
 *					This can be a very useful feature in some
 *					USB applications, such as an Infrared remote
 *					control	receiver.  If a user presses the "power"
 *					button on a remote control, it is nice that the
 *					IR receiver can detect this signalling, and then
 *					send a USB "command" to the PC to wake up.
 *					
 *					The USBCBSendResume() "callback" function is used
 *					to send this special USB signalling which wakes 
 *					up the PC.  This function may be called by
 *					application firmware to wake up the PC.  This
 *					function should only be called when:
 *					
 *					1.  The USB driver used on the host PC supports
 *						the remote wakeup capability.
 *					2.  The USB configuration descriptor indicates
 *						the device is remote wakeup capable in the
 *						bmAttributes field.
 *					3.  The USB host PC is currently sleeping,
 *						and has previously sent your device a SET 
 *						FEATURE setup packet which "armed" the
 *						remote wakeup capability.   
 *
 *					This callback should send a RESUME signal that
 *                  has the period of 1-15ms.
 *
 * Note:            Interrupt vs. Polling
 *                  -Primary clock
 *                  -Secondary clock ***** MAKE NOTES ABOUT THIS *******
 *                   > Can switch to primary first by calling USBCBWakeFromSuspend()
 
 *                  The modifiable section in this routine should be changed
 *                  to meet the application needs. Current implementation
 *                  temporary blocks other functions from executing for a
 *                  period of 1-13 ms depending on the core frequency.
 *
 *                  According to USB 2.0 specification section 7.1.7.7,
 *                  "The remote wakeup device must hold the resume signaling
 *                  for at lest 1 ms but for no more than 15 ms."
 *                  The idea here is to use a delay counter loop, using a
 *                  common value that would work over a wide range of core
 *                  frequencies.
 *                  That value selected is 1800. See table below:
 *                  ==========================================================
 *                  Core Freq(MHz)      MIP         RESUME Signal Period (ms)
 *                  ==========================================================
 *                      48              12          1.05
 *                       4              1           12.6
 *                  ==========================================================
 *                  * These timing could be incorrect when using code
 *                    optimization or extended instruction mode,
 *                    or when having other interrupts enabled.
 *                    Make sure to verify using the MPLAB SIM's Stopwatch
 *                    and verify the actual signal on an oscilloscope.
 *******************************************************************/
void USBCBSendResume(void)
{
    static WORD delay_count;
    
    USBResumeControl = 1;                // Start RESUME signaling
    
    delay_count = 1800U;                // Set RESUME line for 1-13 ms
    do
    {
        delay_count--;
    }while(delay_count);
    USBResumeControl = 0;
}


/** EOF mouse.c *************************************************/
#endif
