#include <p18cxxx.h>
//#include <p18f4550.h>
//#include <pic.h> 

void wait();


#define TRUE 1
#define FALSE 0

short firstCycle = FALSE; 

unsigned char data_Cnt = 0; 
unsigned long gsClkCnt = 0;
unsigned long start = 0;
 
unsigned char dcData[96] = 
{                      
                  1, 1, 1, 1, 1, 1, // Ch 15          
                  1, 1, 1, 1, 1, 1, // Ch 14          
                  1, 1, 1, 1, 1, 1, // Ch 13 
                  1, 1, 1, 1, 1, 1, // Ch 12 
                  1, 1, 1, 1, 1, 1, // Ch 11 
                  1, 1, 1, 1, 1, 1, // Ch 10 
                  1, 1, 1, 1, 1, 1, // Ch 9 
                  1, 1, 1, 1, 1, 1, // Ch 8 
                  1, 1, 1, 1, 1, 1, // Ch 7 
                  1, 1, 1, 1, 1, 1, // Ch 6 
                  1, 1, 1, 1, 1, 1, // Ch 5 
                  1, 1, 1, 1, 1, 1, // Ch 4 
                  1, 1, 1, 1, 1, 1, // Ch 3 
                  1, 1, 1, 1, 1, 1, // Ch 2 
                  1, 1, 1, 1, 1, 1, // Ch 1 
                  1, 1, 1, 1, 1, 1, // Ch 0    
}; 
                                      
unsigned char gsData[192]; 

 
 
//
#define XERR 	LATBbits.LATB0 //Error Output, not read  - Gen I/O                                
//SOUT
#define GSCLK 	LATBbits.LATB1 //CCP1 - grey scale clock
#define DCPRG 	LATBbits.LATB2 //Error Output, not read  - Gen I/O                                              
//VCC      
//GND
#define BLANK 	LATBbits.LATB3 //ResetsCounter, blanks all outs - Gen I/O
#define XLAT 	LATBbits.LATB4 //when high, writes data from input register to DC or GS registers  - Gen I/O
#define SCLK 	LATBbits.LATB5 //SPI Data Shift Clock, SCL/SCK
#define SIN 	LATBbits.LATB6 //serial data output, SDO/RX 
#define VPRG 	LATBbits.LATB7 //changes between Dot and Grey data  - Gen I/O


int gg = 0;
void wait()
{
	for (gg = 0;gg<0;gg++){Nop();}
}	
        
// daq  #byte PORTB = 0xF81  
                          
//                              
//void TLC5940_Init(); 
//void TLC5940_ClockInDC(); 
//void TLC5940_SetGS_And_GS_PWM(); 
//void changeGS(unsigned char channel, unsigned long dc); 

void clockTest()
{
//	SCLK = ~SCLK;
//	BLANK = ~BLANK;
//	VPRG = ~VPRG;
//	GSCLK = ~GSCLK;
//	XLAT = ~XLAT;
//	SIN = ~SIN;
//	XERR = ~XERR;
//	DCPRG = ~DCPRG;
}	
                          
void TLC5940_Init()        
{ 
      GSCLK=0;//   output_low(GSCLK); 
      SCLK =0;  //   output_low(SCLK);                      
      DCPRG=0;   //   output_low(DCPRG); 
      VPRG =0;  //   output_high(VPRG);      
      XLAT =0;  //   output_low(XLAT);    
      BLANK =0;  //   output_high(BLANK); 
         //   memset(gsData, 0x00, sizeof(gsData)); 
}          


void TLC5940_ClockInDC() 
{ 
           unsigned long cnt = 0; 
           DCPRG = 1 ; //output_high(DCPRG); 
           VPRG = 1; //output_high(VPRG); 
           while(TRUE) 
           { 
                             if(cnt > 95) 
                             { 
                                      XLAT =1;  //output_high(XLAT); 
                                      wait();
                                      XLAT =0;  //output_low(XLAT);
                                      wait(); 
                                      break; 
                             } 
                             else 
                             { 
                                      if(dcData[cnt]) 
                                      { 
                                               SIN =1;  //output_high(SIN); 
                                      } 
                                      else        
                                      { 
                                               SIN =0;  //output_low(SIN); 
                                      } 
                                      SCLK =1;  //output_high(SCLK); 
                                      wait();
                                      SCLK =0;  //output_low(SCLK); 
                                      wait();
                                      cnt++;                  
                             }                      
           }                
} 


         
void TLC5940_SetGS_And_GS_PWM() 
{                                                   
 data_Cnt=0;// daq added.
 
         //if(bit_test(PORTB, 0)) 
         if(PORTB == 0) //???????????????????????????????
         { 
                  VPRG = 0; //output_low(VPRG); 
                  firstCycle = TRUE;                  
         }    
         BLANK=0;//output_low(BLANK); 
         while(TRUE)      
         { 
                  if(gsClkCnt > 4095) 
                  { 
                           BLANK =1;  //output_high(BLANK); 
                           XLAT =1;  //output_high(XLAT); 
                           	wait();
                           XLAT =0;  //output_low(XLAT);
                           BLANK =0;  //output_high(BLANK); 
                           	wait(); 
                           if(firstCycle) 
                           { 
                                      SCLK =1;  //output_high(SCLK); 
                                                                 wait();
                                      SCLK =0;  //output_low(SCLK); 
                                                                 wait();
                                    firstCycle = FALSE;                
                           }                        
                           break;                    
                  } 
                  else 
                  { 
                           //if(!(data_Cnt > 191)) 
                           if(data_Cnt <= 191)
                           {                  
                                    if(gsData[data_Cnt]) 
                                    { 
                                             SIN =1;  //output_high(SIN); 
                                    }            
                                    else        
                                    { 
                                             SIN =0;  //output_low(SIN); 
                                    }          
                                      SCLK =1;  //output_high(SCLK); 
  wait();
                                      SCLK =0;  //output_low(SCLK); 
  wait();
                                    data_Cnt++;                
                           } 
                  } 
                  GSCLK=1;//output_high(GSCLK);
                                             wait(); 
                  GSCLK=0;//output_low(GSCLK); 
                                             wait();
                  gsClkCnt++;    
         }                                    
} 


void changeGS(unsigned char channel, unsigned long dc) 
{                                              
         unsigned long start = 0; 
         unsigned long stop  = 0;          
         unsigned long s = 0; 
         short tmp = 0; 
         switch(channel) 
         { 
                  case 1: 
                  { 
                           start = 168; 
                           stop = 179; 
                           break;                                    
                  } 
                  case 2: 
                  { 
                           start = 156; 
                           stop = 167; 
                           break;                                    
                  }  
                  case 3: 
                  { 
                           start = 144; 
                           stop = 155; 
                           break;                                    
                  }                                        
                  case 4: 
                  { 
                           start = 132; 
                           stop = 143; 
                           break;                                    
                  } 
                  case 5: 
                  {          
                           start = 120; 
                           stop = 131; 
                           break;                                    
                  }  
                  case 6: 
                  {        
                           start = 108; 
                           stop = 119; 
                           break;                                    
                  } 
                  case 7: 
                  {        
                           start = 96; 
                           stop = 107; 
                           break;                                    
                  }  
                  case 8: 
                  {        
                           start = 84; 
                           stop = 95; 
                           break;                                    
                  }  
                  case 9: 
                  {        
                           start = 72; 
                           stop = 83; 
                           break;                                    
                  }  
                  case 10: 
                  {                      
                           start = 60; 
                           stop = 71; 
                           break;                                    
                  } 
                  case 11: 
                  {        
                           start = 48; 
                           stop = 59; 
                           break;                                    
                  }          
                  case 12:                  
                  {    
                           start = 36; 
                           stop = 47;                            
                           break;            
                  }  
                  case 13: 
                  {        
                           start = 24; 
                           stop = 35; 
                           break;                                    
                  }          
                  case 14:    
                  {          
                           start = 12; 
                           stop = 23; 
                           break;                                    
                  }          
                  case 15: 
                  { 
                           start = 0; 
                           stop = 11; 
                           break;          
                  }        
                  default: 
                  {            
                           start = 180; 
                           stop = 191; 
                           break;          
                  }      
         }
                           
         for(s = start; s <= stop; s++) 
         {     
	         // Not SURE IF THIS IS RIGHT     
	         //#define bit_test(byte,bit) (byte & (1 << bit)) // test for bit set                          
                  //tmp = bit_test(dc, (stop - s)); 
                  tmp = dc & (stop - s);
                  gsData[s] = tmp;                        
         }                                                                                                  
}