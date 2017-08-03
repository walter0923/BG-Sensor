#include <msp430.h>
#include "main.h"
#include "TIMER.h"
#include "GPIO.h"
#include "ADC.h"
#include "UART.h"



int ledshift = 0;
unsigned int tick100us = 0;
int keytick = 0;

void TIMER_Ini(void){
  TA1CCTL0 = CCIE;                          // CCR0 interrupt enabled
  TA1CCR0 = 1000;                           // count to 1uS 
  TA1CTL = TASSEL_2 + MC_2 + TACLR;         // SMCLK, contmode, clear TAR
  LED1PWM_Ini();
  LED2PWM_Ini();
}

void LED1PWM_Ini(void){
  P8SEL |= 0x7E;                            // P8 option select
  P8DIR |= 0x7E;                            // P8 outputs

  TA0CCR0 = 2500 / PWMfrequency;                           // PWM Period
  TA0CCTL1 = OUTMOD_7;                       // CCR1 reset/set
  TA0CCR1 = 0xFF;                             // CCR1 PWM Duty Cycle	
  TA0CCTL2 = OUTMOD_7;                       // CCR2 reset/set
  TA0CCR2 = 0xFF;                             // CCR2 PWM duty cycle	
  TA0CCTL3 = OUTMOD_7;                       // CCR3 reset/set
  TA0CCR3 = 0xFF;                             // CCR3 PWM duty cycle	
  TA0CCTL4 = OUTMOD_7;                       // CCR4 reset/set
  TA0CCR4 = 0xFF;                              // CCR4 PWM duty cycle	
  TA0CTL = TBSSEL_2 + MC_1 + TBCLR;          // SMCLK, upmode, clear TB
}

void LED2PWM_Ini(void){
  P4SEL |= 0x7E;                            // P4 option select
  P4DIR |= 0x7E;                            // P4 outputs

  TBCCR0 = 2500 / PWMfrequency;                           // PWM Period
  TBCCTL1 = OUTMOD_7;                       // CCR1 reset/set
  TBCCR1 = 0xFF;                             // CCR1 PWM Duty Cycle	
  TBCCTL2 = OUTMOD_7;                       // CCR2 reset/set
  TBCCR2 = 0xFF;                             // CCR2 PWM duty cycle	
  TBCCTL3 = OUTMOD_7;                       // CCR3 reset/set
  TBCCR3 = 0xFF;                              // CCR3 PWM duty cycle	
  TBCCTL4 = OUTMOD_7;                       // CCR4 reset/set
  TBCCR4 = 0xFF;                              // CCR4 PWM duty cycle	
	
  TBCTL = TBSSEL_2 + MC_1 + TBCLR;          // SMCLK, upmode, clear TB
}

void LEDShift(void){
  switch(ledshift){
    case 3:
      //if(select){
        TA0CCR1 = 2500 / 100 * LEDa1Dutycycle;
        TA0CCR2 = 0xFF;
        TA0CCR3 = 0xFF;
        TA0CCR4 = 0xFF;
      //}else{
        TBCCR1 = 2500 / 100 * LEDb1Dutycycle;;
        TBCCR2 = 0xFF;
        TBCCR3 = 0xFF;
        TBCCR4 = 0xFF;
      //}
      break;
      
    case 2:
      //if(select){
        TA0CCR1 = 0xFF;
        TA0CCR2 = 2500 / 100 * LEDa2Dutycycle;
        TA0CCR3 = 0xFF;
        TA0CCR4 = 0xFF;
      //}else{
        TBCCR1 = 0xFF;
        TBCCR2 = 2500 / 100 * LEDb2Dutycycle;
        TBCCR3 = 0xFF;
        TBCCR4 = 0xFF;
      //}
      break;
      
    case 1:
      //if(select){
        TA0CCR1 = 0xFF;
        TA0CCR2 = 0xFF;
        TA0CCR3 = 2500 / 100 * LEDa3Dutycycle;
        TA0CCR4 = 0xFF;
      //}else{
        TBCCR1 = 0xFF;
        TBCCR2 = 0xFF;
        TBCCR3 = 2500 / 100 * LEDb3Dutycycle;
        TBCCR4 = 0xFF;
      //}
      break;
      
    case 0:
      //if(select){
        TA0CCR1 = 0xFF;
        TA0CCR2 = 0xFF;
        TA0CCR3 = 0xFF;
        TA0CCR4 = 2500 / 100 * LEDa4Dutycycle;
      //}else{
        TBCCR1 = 0xFF;
        TBCCR2 = 0xFF;
        TBCCR3 = 0xFF;
        TBCCR4 = 2500 / 100 * LEDb4Dutycycle;
      //}
      break;
      
    default:
      break;
  }
}

#pragma vector=TIMER1_A0_VECTOR
__interrupt void TIMER1_A0_ISR(void){
  tick100us++;
  keytick++;
  if(DataEmpty == 1){
    if(tick100us >= 25){              //if count over or equal 2500(250ms) 
      ledshift++;                         //switch to next LED
      ledshift %= 4;
      tick100us = 0;                    //recount
    }else if(tick100us == 10){  //Start sample at after LED on 1ms 
      //adc + flash
      ADC12CTL0 |= ADC12SC;
    }
  }
}
