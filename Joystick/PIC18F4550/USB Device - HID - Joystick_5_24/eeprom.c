//#include <p18f4550.h>
//#include <pic.h>
#include <p18cxxx.h>
#include <delays.h>
#include <portb.h>//functions to control pull-up resistors and interrupts

#include <pconfig.h>
#include <delays.h>

void EEPROM_putc(unsigned char address, unsigned char data)
{
	unsigned char INTCON_SAVE;

	EEADR  = address;
	EEDATA = data;

	EECON1bits.EEPGD= 0; // 0 = Access data EEPROM memory
	EECON1bits.CFGS = 0; // 0 = Access Flash program or DATA EEPROM memory
	EECON1bits.WREN = 1; // enable writes to internal EEPROM

	INTCON_SAVE=INTCON; // Save INTCON register contants
	INTCON=0; 			// Disable interrupts, Next two lines SHOULD run without interrupts
	
	EECON2=0x55;		// Required sequence for write to internal EEPROM
	EECON2=0xaa;		// Required sequence for write to internal EEPROM

	EECON1bits.WR=1;    // begin write to internal EEPROM
	INTCON=INTCON_SAVE; //Now we can safely enable interrupts if previously used
	
	Nop();

	while (PIR2bits.EEIF==0)//Wait till write operation complete
	{
		Nop();
	}

	EECON1bits.WREN=0; // Disable writes to EEPROM on write complete (EEIF flag on set PIR2 )
	PIR2bits.EEIF=0; //Clear EEPROM write complete flag. (must be cleared in software. So we do it here)

}

// This function reads data from address given in internal EEPROM of PIC 
unsigned char EEPROM_getc(unsigned char address)
{
	EEADR=address;
	EECON1bits.EEPGD= 0; // 0 = Access data EEPROM memory
	EECON1bits.CFGS = 0; // 0 = Access Flash program or DATA EEPROM memory
    EECON1bits.RD   = 1; // EEPROM Read
   	return EEDATA;       // return data
}

unsigned char EEPROM_getPlayer_old()
{
	unsigned char data = 0;	
	unsigned char addr = 0x00;;
	
	// Read the data....	
	data = EEPROM_getc(addr); // Read EEPROM address 0x12 in to variable C
	
	data += 1;
	
	if (data > 9)
		{data = 1;}
	
	EEPROM_putc(addr,data); //Write 0x?? to EEPROM address 0x12
	Nop();

	data = EEPROM_getc(addr); // Read EEPROM address 0x12 in to variable C
	return data;			
}

unsigned char EEPROM_getPlayer()
{
	unsigned char addr = 0x00;
	unsigned char data = (~PORTB) & 0x0f;
	unsigned char player = EEPROM_getc(addr); // Read EEPROM address 0x00 in to variable C	
		
	// Changing PLAYER ID
	if (data >= 1 && data <= 9)
	{		
		EEPROM_putc(addr,data); //Write 0x?? to EEPROM address 0x00
		Nop();
		
		player = data;
	}
	
	// Validate PLAYER ID  -- Incase EEPROM init > 0x09
	if (player > 9)
	{
		// Set player to ZERO to not interfear.
		player = 0;
		EEPROM_putc(addr,player); //Write 0x?? to EEPROM address 0x00
		Nop();		
	}	
	
	return EEPROM_getc(addr);			
}