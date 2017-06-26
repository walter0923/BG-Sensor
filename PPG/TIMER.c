#include <msp430.h>
#include "TIMER.h"

void TIMER_Ini(void){
  TA1CCTL0 = CCIE;                          // CCR0 interrupt enabled
  TA1CCR0 = 1200;                           // count to 1uS 
  TA1CTL = TASSEL_2 + MC_2 + TACLR;         // SMCLK, contmode, clear TAR
}

void LED1PWM_Ini(void){
  P8SEL |= 0x7E;                            // P8 option select
  P8DIR |= 0x7E;                            // P8 outputs

  TA0CCR0 = 512-1;                           // PWM Period
  TA0CCTL1 = OUTMOD_7;                       // CCR1 reset/set
  TA0CCR1 = 0;                             // CCR1 PWM Duty Cycle	
  TA0CCTL2 = OUTMOD_7;                       // CCR2 reset/set
  TA0CCR2 = 0;                             // CCR2 PWM duty cycle	
  TA0CCTL3 = OUTMOD_7;                       // CCR3 reset/set
  TA0CCR3 = 0;                              // CCR3 PWM duty cycle	
  TA0CCTL4 = OUTMOD_7;                       // CCR4 reset/set
  TA0CCR4 = 0;                              // CCR4 PWM duty cycle	
  TA0CTL = TBSSEL_2 + MC_1 + TBCLR;          // SMCLK, upmode, clear TB
}

void LED2PWM_Ini(void){
  P4SEL |= 0x7E;                            // P4 option select
  P4DIR |= 0x7E;                            // P4 outputs

  TBCCR0 = 512-1;                           // PWM Period
  TBCCTL1 = OUTMOD_7;                       // CCR1 reset/set
  TBCCR1 = 0;                             // CCR1 PWM Duty Cycle	
  TBCCTL2 = OUTMOD_7;                       // CCR2 reset/set
  TBCCR2 = 0;                             // CCR2 PWM duty cycle	
  TBCCTL3 = OUTMOD_7;                       // CCR3 reset/set
  TBCCR3 = 0;                              // CCR3 PWM duty cycle	
  TBCCTL4 = OUTMOD_7;                       // CCR4 reset/set
  TBCCR4 = 0;                              // CCR4 PWM duty cycle	
	
  TBCTL = TBSSEL_2 + MC_1 + TBCLR;          // SMCLK, upmode, clear TB
}

#pragma vector=TIMER1_A0_VECTOR
__interrupt void TIMER1_A0_ISR(void){
  
}