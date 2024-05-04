/*******************************************************************************
 Rue Mohr  May 2024
 
 Corrupt 1 bit ADC, 2/10 bits are fixed to meet start/stop bit positioning.
 
 For this a "4kHz lowpass" was made using 20nF (0.02uF) and a 2.7k resistor
 
 Reset should have a 10k pullup.
 Use a 0.1uF capacitor and a voltage divider of two 47k resistors to bias the input
 at 2.5V.
 pass that thru a low pass made of the 2.7k and .02uF cap, run that result to pin 5 of the tiny13
 
 
 serial data is out pin 3.
 Run a feedback from pin 3, thru a low pass made of the 2.7k resistor and .02uF cap, to pin 6 of the tiny13.
 
 The comparator is used in the tiny13 to determine the 8 data bits of the serial data in real time.
 The number of nops in bitDelay may need to be tweaked for your tiny13 to get the baud rate trimmed right.
 ("it works for me")
 
 no input signal should generate alternating bits enough to do timing trimming (add a few nops for lower frequency, 
 remove a few for higher frequency)
 
 You can save the serial data stream to a file for playback later using the same RC filter on the data line.
 Hopefully, you got this from the github page where I also posted the schematics.
 
*******************************************************************************/
 
/*

5 PB0   AIN0
6 PB1   AIN1
7 PB2  
8     (VCC)
4     (GND) 
2 PB3    
3 PB4  TxD    
1 PB5 (RESET)   


                       tiny13 generic pinout:
                            +-----U-----+    
               RESET    PB5 | o         | VCC
               ADC3     PB3 |           | PB2 ADC1 
               ADC2     PB4 |   Tiny13  | PB1 OC0B
                        GND |           | PB0 OC0A
                            +-----------+    





*/


#include <avr/io.h>
#include "avrcommon.h"


void configComp(void);
void bitDelay(void);


int main (void) {


  // Set clock prescaler: 0 gives full 9.6 MHz from internal oscillator.
  CLKPR = (1 << CLKPCE);
  CLKPR = 0;  

  // set up directions 

  DDRB  = (INPUT << PB0 | INPUT << PB1 |INPUT << PB2 |INPUT << PB3 |OUTPUT << PB4 |INPUT << PB5 );
  
 
 configComp();
 
    
  while(1) {        
     // start bit
     ClearBit(4, PORTB);
     bitDelay();
     
     // D0
     if (IsHigh(ACO, ACSR)) SetBit(4, PORTB); else ClearBit(4, PORTB);
     bitDelay();
     
     // D1
     if (IsHigh(ACO, ACSR)) SetBit(4, PORTB); else ClearBit(4, PORTB);
     bitDelay();
     
     // D2
     if (IsHigh(ACO, ACSR)) SetBit(4, PORTB); else ClearBit(4, PORTB);
     bitDelay();
     
     // D3
     if (IsHigh(ACO, ACSR)) SetBit(4, PORTB); else ClearBit(4, PORTB);
     bitDelay();
     
     // D4
     if (IsHigh(ACO, ACSR)) SetBit(4, PORTB); else ClearBit(4, PORTB);
     bitDelay();
     
     // D5
     if (IsHigh(ACO, ACSR)) SetBit(4, PORTB); else ClearBit(4, PORTB);
     bitDelay();
     
     // D6
     if (IsHigh(ACO, ACSR)) SetBit(4, PORTB); else ClearBit(4, PORTB);
     bitDelay();
     
     // D7
     if (IsHigh(ACO, ACSR)) SetBit(4, PORTB); else ClearBit(4, PORTB);
     bitDelay();
     
     // stop bit
     SetBit(4, PORTB);
     bitDelay();
  }     
  
}

void bitDelay(void) {
  NOP(); NOP(); NOP(); NOP(); NOP(); NOP(); NOP(); NOP(); 
  NOP(); NOP(); NOP(); NOP(); NOP(); NOP(); NOP(); NOP(); 
  NOP(); NOP(); NOP(); NOP(); NOP(); NOP(); NOP(); NOP(); 
  NOP(); NOP(); NOP(); NOP(); NOP(); NOP(); NOP(); NOP(); 
  NOP(); NOP(); NOP(); NOP(); NOP(); NOP(); NOP(); NOP(); 
  NOP(); NOP(); NOP(); NOP(); NOP(); NOP(); NOP(); NOP(); 
  NOP(); NOP(); NOP(); NOP(); NOP(); NOP(); NOP(); NOP(); 
  NOP(); NOP(); NOP(); NOP(); NOP(); NOP(); NOP(); NOP();   
  NOP(); NOP(); NOP(); NOP(); NOP(); NOP(); NOP(); NOP(); 
  NOP(); NOP(); NOP();
}


/*
  ACBG 0  (ACSR)
  
  ACME 0  (ADCSRB)
  ADEN x
  
  ACD  0  (ACSR)


*/
void configComp(void) {

  ClearBit( ACD,  ACSR);
  ClearBit( ACBG, ACSR);
  ClearBit( ACME, ADCSRB);

}































