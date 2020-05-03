/**************************************************
 * EE312 Lab 2
 *
 * Copyright 2015 University of Strathclyde
 *
 *
 **************************************************/
#include <msp430.h>
#include <driverlib.h>
#include <stdio.h>
#include "LedDriver.h"
#include "hal_LCD.h"

unsigned int adcValue = 0;
char adcVal[4];
char gramValue[4];
  
  #pragma vector=ADC_VECTOR
  __interrupt void ADC_ISR(void)
  {
    switch(__even_in_range(ADCIV,ADCIV_ADCIFG))
    {
    case ADCIV_ADCIFG:
      {
        adcValue = ADCMEM0; 
        ADCIFG &= ~ADCIFG0;
      }
      break;
    }
  }
  
  int main(void)
{
  //Default MCLK = 1MHz
  
    unsigned int i = 0;
    unsigned char dialValue = 0x01;
    unsigned int output = 0;
    
    WDTCTL = WDTPW | WDTHOLD;               // Stop watchdog timer
    SYSCFG2 |= ADCPCTL9;                   //Analogue pin A9 turn on.
  
    //Set registers
    ADCCTL0 = ADCSHT_2 | ADCON;             //UNSERSCORE uses bit value rather than user guides HEX representation
    ADCCTL1 = ADCSHP;                       //Sample and Hold mode.
    ADCCTL2 = ADCRES_1;                     //Resolution.
    ADCMCTL0 = ADCSREF_0 | ADCINCH_9;      //Reference voltage/Input channel for conversion
    ADCIE = ADCIE0;   
  
    Init_LCD();
    initialiseLedDial();
   
    char message[] = "HELLO";
  
    WDTCTL = WDTPW | WDTHOLD;               // Stop watchdog timer
    
  // Configure button S1 /S2 interrupt
  GPIO_selectInterruptEdge(GPIO_PORT_P1, GPIO_PIN3|GPIO_PIN4, GPIO_LOW_TO_HIGH_TRANSITION);
  GPIO_setAsInputPinWithPullUpResistor(GPIO_PORT_P1, GPIO_PIN3|GPIO_PIN4);
  GPIO_setAsPeripheralModuleFunctionOutputPin(GPIO_PORT_P8, GPIO_PIN1, GPIO_PRIMARY_MODULE_FUNCTION);
  
  // Disable the GPIO power-on default high-impedance mode  to activate previously configured port settings
  PMM_unlockLPM5();  
 
  __enable_interrupt();
   displayScrollText(message);
   
  while(1)
    {   
      
      ADCCTL0|=ADCENC|ADCSC;     //Sample Conversion Start      
      
      
      dialValue = dialValue * 0x02;
      
      if(0x00 == dialValue)
        dialValue = 0x01; 
      
      //Update value
      setLedDial(dialValue);
     
      //Calibration Equation Using Values obtained from scales
      if (adcValue<159)
        {
          output = 0;
        }
      else if (adcValue <344)
        {
          output = 0+((200*(adcValue- 159)/(344-159)));
        }
      else if (adcValue <415)
        {
          output = 200+((200*(adcValue- 344)/(415-344)));
        }
      else if (adcValue < 460)
        {
          output = 400+((200*(adcValue- 415)/(460-415)));
        }
      else if (adcValue < 538)
        {
          output = 600+((200*(adcValue- 460)/(538-460)));
        }
      else
        {
          showChar('G',pos6);
          showChar('M', pos1);
          showChar('A', pos2);
          showChar('X',pos3);
          showChar(' ',pos4);
        }
      
      //Refresh display (10 times for each position)
      for(i = 0; i < (adcValue/64); i++)
        {
          refreshLedDial();
        }  
    
     //Display Gram value
      sprintf(gramValue, "%04d", output);       //Converts counter integer to fill char array, padded with 0's
    
      //Allocating position of data on LCD
      showChar('G',pos6);
      showChar(gramValue[0], pos1);
      showChar(gramValue[1], pos2);
      showChar(gramValue[2],pos3);
      showChar(gramValue[3], pos4);
   }
}