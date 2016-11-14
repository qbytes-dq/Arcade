/*********************************************************************
 * FileName:        buttons.h
 * Dependencies:    See INCLUDES section below
 * Processor:       PIC18
 * Compiler:        C18 2.30.01+
 * Company:         sprut
 * Copyright:       2007 Joerg Bredendiek (sprut)
 *
 *
 ********************************************************************/

#ifndef GAMEPAD_H
#define GAMEPAD_H

/** I N C L U D E S **********************************************************/
#include "HardwareProfile.h"     

/** D E F I N I T I O N S ****************************************************/
//#define mZeile_0            LATCbits.LATC0
//#define mZeile_1            LATCbits.LATC1
//#define mZeile_2            LATCbits.LATC2



/** E X T E R N     **********************************************************/
//extern	BYTE		RC_Buttons0;
//extern	BYTE		RC_Buttons1;
//extern	BYTE		RC_Buttons2;

#define ARSIZE 3

extern	BYTE		PLAYER;

//extern	BYTE		MY_Spinner0;
//extern	BYTE		MY_Spinner1;
//extern	BYTE		MY_Spinner2;

/** P U B L I C  P R O T O T Y P E S *****************************************/
//void	Spinners_Init(void);
//void	Spinner_Move(void);
//void	UP_Spinner(void);
//void 	Check_Move (struct wp_char * inp);


/** P R I V A T E  P R O T O T Y P E S ***************************************/

#endif	// BUTTONS_H

/****  E N D E  *********************************************/
