// http://www.ccsinfo.com/forum/viewtopic.php?t=50238


//#device *= 16 
//#device ADC = 10    

#include <p18cxxx.h>
//#include <p18f4550.h>
//#include <pic.h>



//#fuses H4, NOWDT, PUT, PROTECT, NOSTVREN 
//#fuses NOCPB, NOWRT, NOWRTB NOEBTRB, NOEBTR                                                          
//#fuses BROWNOUT, CPD, NOOSCSEN, BORV20                                                  
//#fuses NOLVP, NODEBUG, NOWRTC, NOWRTD 
                                                                                                  
                                          
//#use delay(clock = 40MHz) 
                                                                                                      

#include "TLC5940.c"                        
 
// Ensure we have the correct target PIC device family
//#if !defined(__18F4550) && !defined(__18F2550)
//	#error "This firmware only supports either the PIC18F4550 or PIC18F2550 microcontrollers."
//#endif

// PIC18F4550/PIC18F2550 configuration for the WFF Generic HID test device
//#pragma config PLLDIV=12, CPUDIV=OSC1_PLL2, USBDIV=2, FOSC=HSPLL_HS// FCMEM=OFF
#pragma config PLLDIV   = 12         // 20Mhz external oscillator
#pragma config CPUDIV   = OSC1_PLL2   
#pragma config USBDIV   = 2         // Clock source from 96MHz PLL/2
#pragma config FOSC     = HSPLL_HS
#pragma config FCMEN    = OFF
#pragma config IESO     = OFF
#pragma config PWRT     = OFF
#pragma config BOR      = ON
#pragma config BORV     = 3
#pragma config VREGEN   = ON
#pragma config WDT      = OFF
#pragma config WDTPS    = 32768
#pragma config MCLRE    = ON
#pragma config LPT1OSC  = OFF
#pragma config PBADEN   = OFF
// #pragma config CCP2MX   = ON
#pragma config STVREN   = ON
#pragma config LVP      = OFF
// #pragma config ICPRT    = OFF
#pragma config XINST    = OFF
#pragma config CP0      = OFF
#pragma config CP1      = OFF
// #pragma config CP2      = OFF
// #pragma config CP3      = OFF
#pragma config CPB      = OFF
// #pragma config CPD      = OFF
#pragma config WRT0     = OFF
#pragma config WRT1     = OFF
// #pragma config WRT2     = OFF
// #pragma config WRT3     = OFF
#pragma config WRTB     = OFF
#pragma config WRTC     = OFF
// #pragma config WRTD     = OFF
#pragma config EBTR0    = OFF
#pragma config EBTR1    = OFF
// #pragma config EBTR2    = OFF
// #pragma config EBTR3    = OFF
#pragma config EBTRB    = OFF


#define reload1  63035 
#define reload2  40000 
                

short update_flag = 0; 
short pol = 1; 
signed long d = 0; 
              
                                
void setup(); 


#int_timer1  

void update() 
{ 
         set_timer1(reload1); 
         update_flag = 1;                      
} 

                    
#int_timer0 

void update_cycle() 
{  
                  set_timer0(reload2);  
                  if(pol)                                                        
                  { 
                           d += 5;                                                                                                                    
                           if(d == 4095) 
                           { 
                                    pol = 0;                                                                      
                                    d = 4095;                                                                
                           } 
                  }                
                  else 
                  {                                                                                            
                           d -= 5;          
                           if(d <= 0) 
                           { 
                                    pol = 1; 
                                    d = 0;    
                           }                
                  }                        
} 


void main() 
{                        
         setup(); 
         while(TRUE) 
         {                  
                  if(update_flag) 
                  {                                                    
                           setup_timer_1(T1_disabled);  
                           TLC5940_SetGS_And_GS_PWM(); 
                           set_timer1(reload1);  
                           setup_timer_1(T1_internal); 
                           update_flag = 0;                          
                  } 
                  
                  changeGS(0, d); 
                  changeGS(2, d); 
                  changeGS(4, d); 
                  changeGS(6, d);  
                                                                                          
                  changeGS(1, (4095 - d)); 
                  changeGS(3, (4095 - d)); 
                  changeGS(5, (4095 - d)); 
                  changeGS(7, (4095 - d));                        
                  
                  changeGS(8, d);                                                  
                  changeGS(10, d); 
                  changeGS(12, d);                                                                            
                  changeGS(14, d);                                                                  
                            
                  changeGS(9, (4095 - d)); 
                  changeGS(11, (4095 - d)); 
                  changeGS(13, (4095 - d));                                
                  changeGS(15, (4095 - d));              
         };                                                                                  
}                                                                                                    
                          
                
void setup() 
{ 
   disable_interrupts(global);  
   setup_WDT(WDT_off); 
   setup_adc_ports(no_analogs); 
   setup_adc(ADC_off); 
   setup_timer_0(T0_internal); 
   setup_timer_1(T1_internal);  
   setup_timer_2(T2_DISABLED,255,1); 
   setup_timer_3(T3_DISABLED);    
   setup_CCP1(CCP_off); 
   setup_CCP2(CCP_off); 
   setup_SPI(SPI_DISABLED);                                                                                  
   set_timer0(reload2); 
   set_timer1(reload1);  
   set_timer2(0); 
   set_timer3(0); 
   delay_ms(100); 
   enable_interrupts(global);    
   enable_interrupts(int_timer1); 
   enable_interrupts(int_timer0);  
   TLC5940_Init(); 
   TLC5940_ClockInDC(); 
}