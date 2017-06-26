#include <msp430.h>

void ADC_Ini(void){
  P6SEL |= 0x03;                            // P6.0 ADC option select
  P1DIR |= BIT0 + BIT1;                            // P1.0 output

  ADC12CTL1 = ADC12SHP+ADC12CONSEQ_1;       // Use sampling timer, sequence
  ADC12MCTL0 = ADC12INCH_0;                 // ref+=AVcc, channel = A0
  ADC12MCTL1 = ADC12INCH_1+ADC12EOS;        // ref+=AVcc, channel = A1
  ADC12IE = 0x08;                           // Enable ADC12IFG.3
  
  __delay_cycles(10000); 
}

#pragma vector=ADC12_VECTOR
__interrupt void ADC12ISR (void){
  
}
