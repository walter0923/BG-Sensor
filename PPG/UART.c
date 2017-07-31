#include <msp430.h>
#include "main.h"
#include "TIMER.h"
#include "GPIO.h"
#include "ADC.h"
#include "UART.h"

void UART_Ini(void){
  P3SEL = 0x30;                             // P3.4,5 = USCI_A0 TXD/RXD
  UCA0CTL1 |= UCSWRST;                      // **Put state machine in reset**
  UCA0CTL1 |= UCSSEL_2;                     // SMCLK
  UCA0BR0 = 226;                              // 12MHz 9600 (see User's Guide)
  UCA0BR1 = 4;                              // 12MHz 9600
  UCA0MCTL |= UCBRS_0 + UCBRF_0;            // Modulation UCBRSx=1, UCBRFx=0
  UCA0CTL1 &= ~UCSWRST;                     // **Initialize USCI state machine**
  UCA0IE |= UCRXIE;                         // Enable USCI_A0 RX interrupt

}
  
void UARTRx(char data){
  static int datastep = 1;
  switch(datastep){
  case 1:
    if(data == 'f'){
      datastep = 2;
    }else if(data == 's'){
      datastep = 26;
    }
    break;
    
  case 2:
    if(data == 'u'){
      datastep = 3;
    }else{
      datastep = 1;
    }
    break;
    
  case 3:
    if(data == 'c'){
      datastep = 4;
    }else{
      datastep = 1;
    }
    break;
    
  case 4:
    if(data == 'k'){
      datastep = 5;
    }else{
      datastep = 1;
    }
    break;
    
  case 5:
    if(data == ' '){
      datastep = 6;
    }else{
      datastep = 1;
    }
    break;
    
  case 6:
    if(data == 'a'){
      datastep = 7;
    }else{
      datastep = 1;
    }
    break;
    
  case 7:
    if(data == 'l'){
      datastep = 8;
    }else{
      datastep = 1;
    }
    break;
    
  case 8:
    if(data == 'i'){
      datastep = 9;
    }else{
      datastep = 1;
    }
    break;
    
  case 9:
    if(data == 'c'){
      datastep = 10;
    }else{
      datastep = 1;
    }
    break;
    
  case 10:
    if(data == 'e'){
      datastep = 11;
    }else{
      datastep = 1;
    }
    break;
    
  case 11:
    if(data == 'b'){
      datastep = 12;
    }else{
      datastep = 1;
    }
    break;
    
  case 12:
    if(data == 'a'){
      datastep = 13;
    }else{
      datastep = 1;
    }
    break;
    
  case 13:
    if(data == 'b'){
      datastep = 14;
    }else{
      datastep = 1;
    }
    break;
    
  case 14:
    if(data == 'y'){
      datastep = 15;
    }else{
      datastep = 1;
    }
    break;
    
  case 15:
    if(data == ' '){
      datastep = 16;
    }else{
      datastep = 1;
    }
    break;
    
  case 16:
    if(data == 'p'){
      datastep = 17;
    }else{
      datastep = 1;
    }
    break;
    
  case 17:
    if(data == 'i'){
      datastep = 18;
    }else{
      datastep = 1;
    }
    break;
    
  case 18:
    if(data == 'n'){
      datastep = 19;
    }else{
      datastep = 1;
    }
    break;
    
  case 19:
    if(data == 'k'){
      datastep = 20;
    }else{
      datastep = 1;
    }
    break;
    
  case 20:
    if(data == ' '){
      datastep = 21;
    }else{
      datastep = 1;
    }
    break;
    
  case 21:
    if(data == 'p'){
      datastep = 22;
    }else{
      datastep = 1;
    }
    break;
    
  case 22:
    if(data == 'u'){
      datastep = 23;
    }else{
      datastep = 1;
    }
    break;
    
  case 23:
    if(data == 's'){
      datastep = 24;
    }else{
      datastep = 1;
    }
    break;
    
  case 24:
    if(data == 's'){
      datastep = 25;
    }else{
      datastep = 1;
    }
    break;
    
  case 25:
    if(data == 'y'){
      //
      datastep = 1;
    }
    break;
    
  case 26:
    if(data == 't'){
      datastep = 27;
    }else{
      datastep = 1;
    }
    break;
    
  case 27:
    if(data == 'a'){
      datastep = 28;
    }else{
      datastep = 1;
    }
    break;
    
  case 28:
    if(data == 'r'){
      datastep = 29;
    }else{
      datastep = 1;
    }
    break;
    
  case 29:
    if(data == 't'){
      //
      datastep = 1;
    }
    break;
    
  default:
    break;
  }
  
}
#pragma vector=USCI_A0_VECTOR
  __interrupt void USCI_A0_ISR(void){
  UARTRx(UCA0RXBUF);
}

void DataSend(void){
  unsigned int i;
  Flash_ptrA =(long int *)  0x020000;
  for(i = 0; i < 6000; i ++){
    while(UCA0STAT & UCBUSY){;}
    UCA0TXBUF = *Flash_ptrA + i;
  }
}