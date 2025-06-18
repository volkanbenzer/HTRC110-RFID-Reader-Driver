#ifndef __HTRC_110_H
#define __HTRC_110_H

#include "stm32f10x_conf.h"
#include "Hardware_Init.h"

#define SCLK_HIGH		GPIO_SetBits(GPIOB,GPIO_Pin_7)
#define SCLK_LOW		GPIO_ResetBits(GPIOB,GPIO_Pin_7)

#define CLK_OUT_PIN		GPIO_ReadOutputDataBit(GPIOB,GPIO_Pin_7)

#define DIN_HIGH		GPIO_SetBits(GPIOB,GPIO_Pin_6)
#define DIN_LOW		GPIO_ResetBits(GPIOB,GPIO_Pin_6)

#define	DOUT		GPIO_ReadInputDataBit (GPIOB,GPIO_Pin_5) 


/* Constants for 'Config_PageData' */
/* Page No. */
#define CF_PAGE_0    (0)
#define CF_PAGE_1   (16)
#define CF_PAGE_2   (32)
#define CF_PAGE_3   (48)

/*Constants for configuration page 0*/
#define GAIN1        (8)
#define GAIN0        (4)
#define FILTERH      (2)
#define FILTERL      (1)

/*Constants for configuration page 1*/
#define PD_MODE      (8)
#define PD           (4)
#define HYSTERESIS   (2)
#define TXDIS        (1)

/*Constants for configuration page 2*/
#define THRESET      (8)
#define ACQAMP       (4)
#define FREEZE1      (2)
#define FREEZE0      (1)

/*Constants for configuration page 3*/
#define DISLP1       (8)
#define DISSMARTCOMP (4)
#define FSEL1        (2)
#define FSEL0        (1) 


/******************************************************************************
*******************************************************************************
*                                                                             *
* Function prototypes                                                         *
*                                                                             *
*******************************************************************************
******************************************************************************/
#define writeTagEn		GPIO_SetBits (GPIOB,GPIO_Pin_1)
#define readTagEn			GPIO_ResetBits (GPIOB,GPIO_Pin_1)


extern void Send_HTRC110_Cmd ( unsigned char RcCmd );

extern unsigned char Receive_HTRC110_Data( void );

#define READ_TAG( )   Send_HTRC110_Cmd( 0xE0 )

#define WRITE_TAG( )	Send_HTRC110_Cmd( 0xC0 )

#define WRITE_TAG_N( N ) Send_HTRC110_Cmd( 0x10 | (N) )

#define SET_CONFIG_PAGE(Config_PageData) Send_HTRC110_Cmd( 0x40| (Config_PageData) )

#define SET_SAMPLING_TIME( SampleTime ) Send_HTRC110_Cmd( 0x80| (SampleTime) )

extern unsigned char GET_CONFIG_PAGE (unsigned char Config_PageNo);

extern unsigned char GET_SAMPLING_TIME (void);

extern unsigned char READ_PHASE        (void);

extern void Ast_Adjust (unsigned char t_offset);

extern void Fast_Settling (void);

void switchOFF_HTRC110_Drivers(void);

// extern void Write_Settling (void);


//global.hta tan1ml1 #define SetTimer1( value )      Timer3_Configuration(value);//T1CONbits.TMR1ON = 0;  	PIR1bits.TMR1IF = 0;	TMR1H = ((value)>>8)&(0xFF); TMR1L = ((value&0x00FF)); time_int = 0; T1CONbits.TMR1ON = 1
//global.hta tan1ml1 #define SetTimer0( value )      Timer4_Configuration(value);//T0CONbits.TMR0ON = 0;  	INTCONbits.T0IF = 0;	TMR0H = ((value)>>8)&(0xFF); TMR0L = ((value&0x00FF)); time0_int = 0; T0CONbits.TMR0ON = 1


#endif
