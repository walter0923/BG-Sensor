#include <msp430.h>
#include "main.h"
#include "TIMER.h"
#include "GPIO.h"
#include "ADC.h"
#include "UART.h"

int select = 0;
int key_step = 1;

void GPIO_Ini(void){
  P2DIR |= BIT0;
  P2OUT = BIT0;
  P2IE = BIT0;
  P2IES |= BIT0; 
  P2IFG &= ~BIT0;
}

#pragma vector=PORT1_VECTOR
__interrupt void Port_1(void){
  if(key_step == 1){
    key_step = 2;
    keytick = 0;
  }
  P1IFG &= ~BIT0;
}

void keyProc(void){
  
  switch(key_step){
    case 1:
      break;
      
    case 2:
      if(keytick >= 100){
        if(!(P2IN & BIT0)){
          key_step = 3;
        }else{
          key_step = 1;
        }
      }
      break;
      
    case 3:
      if(DataEmpty == 0){
        DataEmpty = 1;
        Flashclear();
      }
      key_step = 1;
      break;
      
    default:
      break;
  }
}