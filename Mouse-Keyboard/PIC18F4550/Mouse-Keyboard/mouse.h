
/********************************************************************

********************************************************************/

#ifndef MOUSE_H
#define MOUSE_H

// Letters
static unsigned char  	a 		= 4;
static unsigned char  	b		= 5;	
static unsigned char   	c		= 6;
static unsigned char  	d		= 7;
static unsigned char  	e		= 8;
static unsigned char  	f		= 9;
static unsigned char  	g		= 10;
static unsigned char  	h		= 11;
static unsigned char  	i		= 12;
static unsigned char  	j		= 13;
static unsigned char  	k		= 14;
static unsigned char  	l		= 15;
static unsigned char  	m		= 16;
static unsigned char  	n		= 17;
static unsigned char  	o		= 18;
static unsigned char  	p		= 19;
static unsigned char  	q		= 20;
static unsigned char  	r		= 21;
static unsigned char  	s		= 22;
static unsigned char  	t		= 23;
static unsigned char  	u		= 24;
static unsigned char  	v		= 25;
static unsigned char  	w		= 26;
static unsigned char  	x		= 27;
static unsigned char  	y		= 28;
static unsigned char   	z		= 29;

// Numbers
static unsigned char   one		= 30;
static unsigned char   two		= 31;
static unsigned char   three	= 32;
static unsigned char   four		= 33;
static unsigned char   five		= 34;
static unsigned char   six 		= 35;
static unsigned char   seven	= 36;
static unsigned char   eight	= 37;
static unsigned char   nine		= 38;
static unsigned char   zero		= 39;
 
// 
static unsigned char   enter	= 40;
static unsigned char   escape	= 41;
static unsigned char   backspace= 42;
static unsigned char   tab		= 43;
static unsigned char   spacebar	= 44;
static unsigned char   underscore=45;
static unsigned char   equals	= 46;
static unsigned char   leftbrace= 47;
static unsigned char   rightbrace=48;
static unsigned char   backslash= 49;
static unsigned char   hash		= 50;
static unsigned char   semicolon= 51;

//
static unsigned char   comma	= 54;
static unsigned char   period	= 55;
static unsigned char   slash	= 56;

//
static unsigned char   capslock	= 57;
 
// F-keys
static unsigned char   f01		= 58;
static unsigned char   f02		= 59;
static unsigned char   f03		= 60;
static unsigned char   f04		= 61;
static unsigned char   f05		= 62;
static unsigned char   f06		= 63;
static unsigned char   f07		= 64;
static unsigned char   f08 		= 65;
static unsigned char   f09		= 66;
static unsigned char   f10		= 67;
static unsigned char   f11		= 68;
static unsigned char   f12		= 69;

//
static unsigned char   home		= 74;
static unsigned char   pageup	= 75;
static unsigned char   delete   = 76;			
static unsigned char   pagedown	= 78;
static unsigned char   rightarrow=79;
static unsigned char   leftarrow= 80;
static unsigned char   downarrow= 81;
static unsigned char   uparrow	= 82;

// Modifier bytes
static unsigned char  None		= 0b00000000;
static unsigned char  LeftCtrl	= 0b00000001;
static unsigned char  LeftShift = 0b00000010;
static unsigned char  LeftAlt	= 0b00000100;
static unsigned char  LeftGUI	= 0b00001000;
static unsigned char  RightCtrl	= 0b00010000;
static unsigned char  RightShift= 0b00100000;
static unsigned char  RightAlt	= 0b01000000;
static unsigned char  RightGUI	= 0b10000000;

static unsigned char  LeftMouse	= 0b00000001;
static unsigned char  RightMouse= 0b00000010;

#endif //MOUSE_H