/**************************************************
 * LEDDriver.c
 * Drives LED display
 *
 * Copyright 2015 University of Strathclyde
 *
 *
 **************************************************/

#include "LedDriver.h"

//Current dial value
unsigned char ledValue_ = 0;
int ledspeed_=0;
unsigned int ledSpeed_ = 10000;
/**
Initialise LED Dial, setting GPIO parameters
*/
void initialiseLedDial()
{
  //GPIO 2.7
  GPIO_setAsOutputPin(GPIO_PORT_P2, GPIO_PIN7);
    
  //GPIO 5.1, 5.2, 5.3
  GPIO_setAsOutputPin(GPIO_PORT_P5, GPIO_PIN1  | GPIO_PIN2 | GPIO_PIN3);

  //GPIO 8.0
  GPIO_setAsOutputPin(GPIO_PORT_P8, GPIO_PIN0);
  }

/** 
Refresh the display
*/
void refreshLedDial()
{ 
  //unsigned char pinState = 0x00;
  //pinState = GPIO_getInputPinValue(GPIO_PORT_P1, GPIO_PIN2);
    switch(ledValue_)
      {
        case 0x01:
        GPIO_setOutputLowOnPin(GPIO_PORT_P2, GPIO_PIN7);
        GPIO_setOutputLowOnPin(GPIO_PORT_P5, GPIO_PIN1 |GPIO_PIN2|GPIO_PIN3);
        GPIO_setOutputHighOnPin(GPIO_PORT_P8, GPIO_PIN0);
        break;
        case 0x02:
        GPIO_setOutputLowOnPin(GPIO_PORT_P2, GPIO_PIN7);
        GPIO_setOutputLowOnPin(GPIO_PORT_P5, GPIO_PIN2|GPIO_PIN3);
        GPIO_setOutputLowOnPin(GPIO_PORT_P8, GPIO_PIN0);
        GPIO_setOutputHighOnPin(GPIO_PORT_P5, GPIO_PIN1);
        break;
        case 0x04:
        GPIO_setOutputLowOnPin(GPIO_PORT_P2, GPIO_PIN7);
        GPIO_setOutputLowOnPin(GPIO_PORT_P5, GPIO_PIN1|GPIO_PIN3);
        GPIO_setOutputLowOnPin(GPIO_PORT_P8, GPIO_PIN0);
        GPIO_setOutputHighOnPin(GPIO_PORT_P5, GPIO_PIN2);
        break;
        case 0x08:
        GPIO_setOutputLowOnPin(GPIO_PORT_P2, GPIO_PIN7);
        GPIO_setOutputLowOnPin(GPIO_PORT_P5, GPIO_PIN1|GPIO_PIN2);
        GPIO_setOutputLowOnPin(GPIO_PORT_P8, GPIO_PIN0);
        GPIO_setOutputHighOnPin(GPIO_PORT_P5, GPIO_PIN3);
        break;
      
        case 0x10:
        GPIO_setOutputHighOnPin(GPIO_PORT_P2, GPIO_PIN7);
        GPIO_setOutputHighOnPin(GPIO_PORT_P5, GPIO_PIN1|GPIO_PIN2);
        GPIO_setOutputHighOnPin(GPIO_PORT_P8, GPIO_PIN0);
        GPIO_setOutputLowOnPin(GPIO_PORT_P5, GPIO_PIN3);
        break;
        case 0x20:
        GPIO_setOutputHighOnPin(GPIO_PORT_P2, GPIO_PIN7);
        GPIO_setOutputHighOnPin(GPIO_PORT_P5, GPIO_PIN1|GPIO_PIN3);
        GPIO_setOutputHighOnPin(GPIO_PORT_P8, GPIO_PIN0);
        GPIO_setOutputLowOnPin(GPIO_PORT_P5, GPIO_PIN2);
        break;
        case 0x40:
        GPIO_setOutputHighOnPin(GPIO_PORT_P2, GPIO_PIN7);
        GPIO_setOutputHighOnPin(GPIO_PORT_P5, GPIO_PIN2|GPIO_PIN3);
        GPIO_setOutputHighOnPin(GPIO_PORT_P8, GPIO_PIN0);
        GPIO_setOutputLowOnPin(GPIO_PORT_P5, GPIO_PIN1);
        break;
        case 0x80:
        GPIO_setOutputHighOnPin(GPIO_PORT_P2, GPIO_PIN7);
        GPIO_setOutputHighOnPin(GPIO_PORT_P5, GPIO_PIN1|GPIO_PIN2|GPIO_PIN3);
        GPIO_setOutputLowOnPin(GPIO_PORT_P8, GPIO_PIN0);
        break;
        };
    __delay_cycles(10000);    
}

/** 
Set dial value
*/
void setLedDial(unsigned char value)
{
  ledValue_ = value;
}
