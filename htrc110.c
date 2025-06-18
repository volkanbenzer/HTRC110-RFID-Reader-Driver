#include "stm32f10x_conf.h"
#include "htrc110.h"
#include "Global.h"
#include "string.h"
#include <stdio.h>



uint32_t HTRC_Timer2us = 0;

void Send_HTRC110_Cmd (unsigned char RcCmd)
{
   unsigned char counter;

   // Initialization of serial interface 
   DIN_LOW;    				
   SCLK_LOW;
	 delayUs(2);
   SCLK_HIGH;
   delayUs(4);
   DIN_HIGH;
   delayUs(2);
   SCLK_LOW;

   if( (RcCmd & 0xC0) == 0xC0 ) counter = 3;	 //  This is a 3-bit command 
   else                         counter = 8;	 //... Resp. a 8-bit command 
	
	do
	{
	    if( RcCmd & 0x80 )    	// Decide whether 0 or 1 has to be sent
	    	DIN_HIGH;
	    else
        DIN_LOW;
			
  		delayUs(2);
      SCLK_HIGH;           // Make this bit valid for the HTRC110
			
      delayUs(2);
	    SCLK_LOW;
			
	    delayUs(3);
	    RcCmd  <<= 1;	    	// Next bit
	}
	while (--counter);
   DIN_LOW; 
}

unsigned char Receive_HTRC110_Data( void )
{
	unsigned char InputByte=0, counter=8;

	// Poll DOUT, while SCLK is high
	do	        	  
	{
           InputByte <<= 1;
           SCLK_HIGH;                	// Activate DOUT
           //Delay10TCYx(1);
					 delayUs(625);
           if ( DOUT ) InputByte|=0x01; 	// And store the information
           SCLK_LOW;
           //Delay10TCYx(1);
					 delayUs(625);
	}
	while (--counter);    					// Needs to be done 8 times
	return InputByte;
}

unsigned char GET_CONFIG_PAGE (unsigned char Config_PageNo)
{
	Send_HTRC110_Cmd(0x04|Config_PageNo);
	return Receive_HTRC110_Data ();
}

unsigned char GET_SAMPLING_TIME (void)
{
	Send_HTRC110_Cmd(0x02);
	return Receive_HTRC110_Data ();
}

unsigned char READ_PHASE (void)
{
	Send_HTRC110_Cmd(0x08);
	return Receive_HTRC110_Data ();
}

void Ast_Adjust (unsigned char t_offset)
{
	unsigned char t_antenna;

	t_antenna = READ_PHASE();
	t_antenna <<= 1;
	t_antenna += t_offset;
	t_antenna &= 0x3F;
	SET_SAMPLING_TIME(t_antenna);
}

uint8_t t_offset_val = 0;

void Fast_Settling (void)
{

  SET_CONFIG_PAGE(CF_PAGE_2 + THRESET + FREEZE0);
 
	
	
	//t_offset_val = 121;
	
	//Ast_Adjust(t_offset_val);
	SET_SAMPLING_TIME(0x07);
	delayUs(200);
	
  SET_CONFIG_PAGE(CF_PAGE_2+THRESET+FREEZE1+FREEZE0);
	delayUs(250);
   
  SET_CONFIG_PAGE(CF_PAGE_2);
//    SET_CONFIG_PAGE(CF_PAGE_2+THRESET+FREEZE1+FREEZE0);
//    
//    Delay1KTCYx(10);	// 5ms
//    
//    SET_CONFIG_PAGE(CF_PAGE_2+THRESET);

//    Delay1KTCYx(2);	// 1ms
//    
//    SET_CONFIG_PAGE(CF_PAGE_2);
}  


void switchOFF_HTRC110_Drivers(void)
{
   	SET_CONFIG_PAGE(CF_PAGE_1+TXDIS);    /* switch off HTRC110 drivers/RF-field */
}

void Serial_Com1(unsigned char sdata)
{		
		while (USART_GetFlagStatus(USART1, USART_FLAG_TXE) == RESET);
		USART_SendData(USART1, sdata);
}

