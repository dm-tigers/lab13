#include "lpc17xx.h"
#include "type.h"
#include "pwm.h"
#include "myheader.h"

/******************************************************************************
** Function name:		PWM1_IRQHandler
**
** Descriptions:		PWM1 interrupt handler  (For Lab exercise it only deals with PWM1 match 0)
******************************************************************************/

void PWM1_IRQHandler (void) 
{
  // check if there is an interrupt, toggle P2.6 LED 
	//clear interrupt flag on match 0 
		LPC_PWM1->IR SETBIT(0);
		LPC_GPIO2->FIOPIN TOGGLEBIT(6);
	
	
	
  return;
}

/******************************************************************************
** Function name:		PWM_Init
**
** Descriptions:		PWM initialization, setup all GPIOs to PWM0~6,reset counter, all latches are enabled,
**								  interrupt on PWMMR0, install PWM interrupt to the VIC table.
**
** parameters:			Duty cycle
*******************************************************************************/

uint32_t PWM_Init( uint32_t cycle )
{
	uint8_t i = 0;
	/* - DONE Set PCONP register for PWM 
	   - DONE Set PClock (By default, PCLKSELx value is zero, thus PCLK for all the peripherals is 1/4 of SystemFrequency.
	   - DONE Set P2.2 - 2.5 PWM1 channel 3 to 6 outputs.
	   - DONE Reset PWM Timer Counter + the PWM Prescale Counter
	   
	   - PROB DONE Set prescaler to get 1 Khz counts/sec
	   - DONE An interrupt is generated when PWMMR0 matches the value in the PWMTC and also Reset PWMTC
	   - set PWM cycle at MR0
	   - channel 3 single edge MR3 - 500
	   - channel 4 double edge MR4 = 1000
	   - channel 5 double edge MR5 = 1500
	   - channel 6 double edge MR6 = 2000
	   - Enable PWM interrupt using NVIC function */ 
	
	LPC_SC->PCONP SETBIT(6); //POWER PWM1
	LPC_SC->PCONP SETBIT(1); //Power timer
	
	LPC_SC->PCLKSEL0 SETBIT(2); //set PClock to core clock

	
	LPC_SC->PCLKSEL0 SETBIT(12);
	
	LPC_PWM1->MCR SETBIT(0); // counter enabler
	LPC_PWM1->MCR SETBIT(1); // timer counter reset
	
	//for loop that sets P2.2 - P2.5
	for(i = 0; i < 4; i++)
	{
		LPC_PINCON->PINSEL4 SETBIT( 2 * (i+2)); // PWM_2, 4, 6, 8;
	}
	

	
	LPC_PWM1->PR H_SETBIT(100000); //set prescalar to get 1K c/s
	
	LPC_PWM1->MCR SETBIT(0); // Generate interrupt
	LPC_PWM1->MCR SETBIT(1); // Reset on interrupt
	LPC_PWM1->MCR CLRBIT(2);
	
	LPC_PWM1->MR0 = cycle;
	LPC_PWM1->PCR SETBIT(2);
	
	LPC_PWM1->MR3 = 500 - 1;
	LPC_PWM1->PCR CLRBIT(3);
	
	LPC_PWM1->MR4 = 1000 - 1;
	LPC_PWM1->PCR SETBIT(4);
	
	LPC_PWM1->MR5 = 1500 - 1;
	LPC_PWM1->PCR SETBIT(5);
	
	LPC_PWM1->MR6 = 2000 - 1;	
	LPC_PWM1->PCR SETBIT(6);
	
	NVIC_EnableIRQ(PWM1_IRQn); //enable interrupt;
	
	
	
	
	
	
  return(TRUE);

}


/******************************************************************************
** Function name:		PWM_Start
**
** Descriptions:		Enable PWM by setting the PCR, PTCR registers
**
******************************************************************************/

void PWM_Start( void )
{
	/* - channel 3 single edge, channel 4-6 double edge; channel 3-6 enable 
		 - Enable PWM Timer Counter
     - Enable	PWM  */
	
	//ENABLE CHANNELS 3 TO 6
	LPC_PWM1->PCR SETBIT(11);
	LPC_PWM1->PCR SETBIT(12);
	LPC_PWM1->PCR SETBIT(13);
	LPC_PWM1->PCR SETBIT(14);
	
	LPC_PWM1->TCR SETBIT(0);
	LPC_PWM1->TCR SETBIT(3);
	
  return;
}

/******************************************************************************
** Function name:		PWM_Stop
**
** Descriptions:		Stop all PWM channels
**
******************************************************************************/
void PWM_Stop( void )
{
  //Set PCR to 0
	//Stop all PWMs ,set TCR to 0
	LPC_PWM1->PCR = 0;
	

  
  return;
}


