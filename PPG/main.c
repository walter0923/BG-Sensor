#include <msp430.h>
#include "main.h"
#include "TIMER.h"


void main(void){
  WDTCTL = WDTPW+WDTHOLD;
  SetVcoreUp(PMMCOREV_1); 
  SetVcoreUp(PMMCOREV_2);                     // Set VCore to 1.8MHz for 20MHz

  P7SEL |= 0x03;                            // Select XT1
  UCSCTL6 &= ~(XT1OFF);                     // XT1 On
  UCSCTL6 |= XTS + XT1DRIVE_3;              //Hight frequency mode

  do
  {
    UCSCTL7 &= ~(XT2OFFG + XT1LFOFFG + XT1HFOFFG + DCOFFG);
                                            // Clear XT2,XT1,DCO fault flags
    SFRIFG1 &= ~OFIFG;                      // Clear fault flags
  }while (SFRIFG1&OFIFG);                   // Test oscillator fault flag

  UCSCTL4 = SELA_0 + SELS_0 + SELM_0;       // Select ACLK = LFXT1
                                            //       SMCLK = LFXT1
                                            //        MCLK = LFXT1

  TIMER_Ini();
  LED1PWM_Ini();
  LED2PWM_Ini();
  
  while(1){
    
  }
}

void SetVcoreUp (unsigned int level){
  // Open PMM registers for write
  PMMCTL0_H = PMMPW_H;              
  // Set SVS/SVM high side new level
  SVSMHCTL = SVSHE + SVSHRVL0 * level + SVMHE + SVSMHRRL0 * level;
  // Set SVM low side to new level
  SVSMLCTL = SVSLE + SVMLE + SVSMLRRL0 * level;
  // Wait till SVM is settled
  while ((PMMIFG & SVSMLDLYIFG) == 0);
  // Clear already set flags
  PMMIFG &= ~(SVMLVLRIFG + SVMLIFG);
  // Set VCore to new level
  PMMCTL0_L = PMMCOREV0 * level;
  // Wait till new level reached
  if ((PMMIFG & SVMLIFG))
    while ((PMMIFG & SVMLVLRIFG) == 0);
  // Set SVS/SVM low side to new level
  SVSMLCTL = SVSLE + SVSLRVL0 * level + SVMLE + SVSMLRRL0 * level;
  // Lock PMM registers for write access
  PMMCTL0_H = 0x00;
}