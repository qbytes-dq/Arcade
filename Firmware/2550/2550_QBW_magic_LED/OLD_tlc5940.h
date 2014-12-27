
#ifndef TLC5940_H
#define TLC5940_H

void wait();
void clockTest();
                              
void TLC5940_Init(); 
void TLC5940_ClockInDC(); 
void TLC5940_SetGS_And_GS_PWM(); 
void changeGS(unsigned char channel, unsigned long dc); 

#endif