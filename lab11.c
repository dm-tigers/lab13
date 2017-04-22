/****************************************************************************
 *   $Id:: pwmtest.c 6097 2011-01-07 04:31:25Z nxp12832                     $
 *   Project: NXP LPC17xx PWM example
 *
 *   Description:
 *     This file contains PWM test modules, main entry, to test PWM APIs.
 *
 ****************************************************************************
 * Software that is described herein is for illustrative purposes only
 * which provides customers with programming information regarding the
 * products. This software is supplied "AS IS" without any warranties.
 * NXP Semiconductors assumes no responsibility or liability for the
 * use of the software, conveys no license or title under any patent,
 * copyright, or mask work right to the product. NXP Semiconductors
 * reserves the right to make changes in the software without
 * notification. NXP Semiconductors also make no representation or
 * warranty that such application will be suitable for the specified
 * use without further testing or modification.
****************************************************************************/
#include "lpc17xx.h"
#include "type.h"
#include "pwm.h"
#include "myheader.h"

int main (void)
{	    
  uint32_t cycle = 2000;
  
	// Set Pin 2.6 as GPIO output
	LPC_GPIO2->FIODIR |= 1<<6;
	
	// Set Pin 2.6 to off
	LPC_GPIO2->FIOCLR |= 1<<6;
	
	//Call PWM_Init(cycle)and PWM_Start()
	PWM_Init(cycle);
	PWM_Start();

  while ( 1 );
}

/******************************************************************************
**                            End Of File
******************************************************************************/
