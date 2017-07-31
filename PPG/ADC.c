#include <msp430.h>
#include "main.h"
#include "TIMER.h"
#include "GPIO.h"
#include "ADC.h"
#include "UART.h"

long int *Flash_ptrA;                        // Flash pointer

void ADC_Ini(void){
  P6SEL |= 0x03;                            // P6.0 ADC option select
  //REFCTL0 |= REFMSTR+REFVSEL_2+REFON+REFTCOFF; 
  ADC12CTL0 |= ADC12ON + ADC12MSC + ADC12SHT03;                  // sampling time is 16 ADCCLK
  ADC12CTL1 = ADC12SSEL_1 + ADC12DIV_3 + ADC12SHP + ADC12CONSEQ_0;       // Use sampling timer, sequence
                                                                         // sampling source ACLK = 32K Hz Divide by 4
  ADC12MCTL0 = ADC12INCH_0;                 // ref+=AVcc, channel = A0
  //ADC12MCTL1 = ADC12INCH_1+ADC12EOS;        // ref+=AVcc, channel = A1
  ADC12IE = 0x01;                           // Enable ADC12IFG.1
  ADC12CTL0 |= ADC12ENC;
  
  __delay_cycles(10000); 
}

void Flashclear(void){
  __disable_interrupt();
  Flash_ptrA =(long int *)  0x020000;
  FCTL1 = FWKEY+MERAS; 
  *Flash_ptrA = 0;
  __enable_interrupt();
}

#pragma vector=ADC12_VECTOR
__interrupt void ADC12ISR (void){
  static unsigned int cont = 0;
  __disable_interrupt();
  FCTL3 = FWKEY;
  FCTL1 = FWKEY+WRT;
  *Flash_ptrA = ADC12MEM0;
  Flash_ptrA ++;
  cont ++;
  if(cont >= 6000){
    Flash_ptrA = (long int *)  0x020000;
    DataEmpty = 0;
  }
  __enable_interrupt();
}
