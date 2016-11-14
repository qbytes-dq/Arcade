#line 1 "usb_device.c"
#line 1 "usb_device.c"

#line 34 "usb_device.c"
 

 
#line 1 "C:/MCC18/v3.35/h/GenericTypeDefs.h"

#line 45 "C:/MCC18/v3.35/h/GenericTypeDefs.h"
 


#line 49 "C:/MCC18/v3.35/h/GenericTypeDefs.h"

 
#line 52 "C:/MCC18/v3.35/h/GenericTypeDefs.h"
#line 54 "C:/MCC18/v3.35/h/GenericTypeDefs.h"
#line 55 "C:/MCC18/v3.35/h/GenericTypeDefs.h"
#line 56 "C:/MCC18/v3.35/h/GenericTypeDefs.h"

#line 58 "C:/MCC18/v3.35/h/GenericTypeDefs.h"
#line 59 "C:/MCC18/v3.35/h/GenericTypeDefs.h"
#line 60 "C:/MCC18/v3.35/h/GenericTypeDefs.h"

 
#line 1 "C:/MCC18/v3.35/h/stddef.h"
 

#line 4 "C:/MCC18/v3.35/h/stddef.h"

typedef unsigned char wchar_t;


#line 10 "C:/MCC18/v3.35/h/stddef.h"
 
typedef signed short int ptrdiff_t;
typedef signed short int ptrdiffram_t;
typedef signed short long int ptrdiffrom_t;


#line 20 "C:/MCC18/v3.35/h/stddef.h"
 
typedef unsigned short int size_t;
typedef unsigned short int sizeram_t;
typedef unsigned short long int sizerom_t;


#line 34 "C:/MCC18/v3.35/h/stddef.h"
 
#line 36 "C:/MCC18/v3.35/h/stddef.h"


#line 41 "C:/MCC18/v3.35/h/stddef.h"
 
#line 43 "C:/MCC18/v3.35/h/stddef.h"

#line 45 "C:/MCC18/v3.35/h/stddef.h"
#line 62 "C:/MCC18/v3.35/h/GenericTypeDefs.h"
 

typedef enum _BOOL { FALSE = 0, TRUE } BOOL;     
typedef enum _BIT { CLEAR = 0, SET } BIT;

#line 68 "C:/MCC18/v3.35/h/GenericTypeDefs.h"
#line 69 "C:/MCC18/v3.35/h/GenericTypeDefs.h"
#line 70 "C:/MCC18/v3.35/h/GenericTypeDefs.h"

 
typedef signed int          INT;
typedef signed char         INT8;
typedef signed short int    INT16;
typedef signed long int     INT32;

 
#line 79 "C:/MCC18/v3.35/h/GenericTypeDefs.h"
#line 81 "C:/MCC18/v3.35/h/GenericTypeDefs.h"

 
typedef unsigned int        UINT;
typedef unsigned char       UINT8;
typedef unsigned short int  UINT16;
 
#line 88 "C:/MCC18/v3.35/h/GenericTypeDefs.h"
typedef unsigned short long UINT24;
#line 90 "C:/MCC18/v3.35/h/GenericTypeDefs.h"
typedef unsigned long int   UINT32;      
 
#line 93 "C:/MCC18/v3.35/h/GenericTypeDefs.h"
#line 95 "C:/MCC18/v3.35/h/GenericTypeDefs.h"

typedef union
{
    UINT8 Val;
    struct
    {
         UINT8 b0:1;
         UINT8 b1:1;
         UINT8 b2:1;
         UINT8 b3:1;
         UINT8 b4:1;
         UINT8 b5:1;
         UINT8 b6:1;
         UINT8 b7:1;
    } bits;
} UINT8_VAL, UINT8_BITS;

typedef union 
{
    UINT16 Val;
    UINT8 v[2] ;
    struct 
    {
        UINT8 LB;
        UINT8 HB;
    } byte;
    struct 
    {
         UINT8 b0:1;
         UINT8 b1:1;
         UINT8 b2:1;
         UINT8 b3:1;
         UINT8 b4:1;
         UINT8 b5:1;
         UINT8 b6:1;
         UINT8 b7:1;
         UINT8 b8:1;
         UINT8 b9:1;
         UINT8 b10:1;
         UINT8 b11:1;
         UINT8 b12:1;
         UINT8 b13:1;
         UINT8 b14:1;
         UINT8 b15:1;
    } bits;
} UINT16_VAL, UINT16_BITS;

 
#line 144 "C:/MCC18/v3.35/h/GenericTypeDefs.h"
typedef union
{
    UINT24 Val;
    UINT8 v[3] ;
    struct 
    {
        UINT8 LB;
        UINT8 HB;
        UINT8 UB;
    } byte;
    struct 
    {
         UINT8 b0:1;
         UINT8 b1:1;
         UINT8 b2:1;
         UINT8 b3:1;
         UINT8 b4:1;
         UINT8 b5:1;
         UINT8 b6:1;
         UINT8 b7:1;
         UINT8 b8:1;
         UINT8 b9:1;
         UINT8 b10:1;
         UINT8 b11:1;
         UINT8 b12:1;
         UINT8 b13:1;
         UINT8 b14:1;
         UINT8 b15:1;
         UINT8 b16:1;
         UINT8 b17:1;
         UINT8 b18:1;
         UINT8 b19:1;
         UINT8 b20:1;
         UINT8 b21:1;
         UINT8 b22:1;
         UINT8 b23:1;
    } bits;
} UINT24_VAL, UINT24_BITS;
#line 183 "C:/MCC18/v3.35/h/GenericTypeDefs.h"

typedef union
{
    UINT32 Val;
    UINT16 w[2] ;
    UINT8  v[4] ;
    struct 
    {
        UINT16 LW;
        UINT16 HW;
    } word;
    struct 
    {
        UINT8 LB;
        UINT8 HB;
        UINT8 UB;
        UINT8 MB;
    } byte;
    struct 
    {
        UINT16_VAL low;
        UINT16_VAL high;
    }wordUnion;
    struct 
    {
         UINT8 b0:1;
         UINT8 b1:1;
         UINT8 b2:1;
         UINT8 b3:1;
         UINT8 b4:1;
         UINT8 b5:1;
         UINT8 b6:1;
         UINT8 b7:1;
         UINT8 b8:1;
         UINT8 b9:1;
         UINT8 b10:1;
         UINT8 b11:1;
         UINT8 b12:1;
         UINT8 b13:1;
         UINT8 b14:1;
         UINT8 b15:1;
         UINT8 b16:1;
         UINT8 b17:1;
         UINT8 b18:1;
         UINT8 b19:1;
         UINT8 b20:1;
         UINT8 b21:1;
         UINT8 b22:1;
         UINT8 b23:1;
         UINT8 b24:1;
         UINT8 b25:1;
         UINT8 b26:1;
         UINT8 b27:1;
         UINT8 b28:1;
         UINT8 b29:1;
         UINT8 b30:1;
         UINT8 b31:1;
    } bits;
} UINT32_VAL;

 
#line 245 "C:/MCC18/v3.35/h/GenericTypeDefs.h"
#line 332 "C:/MCC18/v3.35/h/GenericTypeDefs.h"

 

 
typedef void                    VOID;

typedef char                    CHAR8;
typedef unsigned char           UCHAR8;

typedef unsigned char           BYTE;                            
typedef unsigned short int      WORD;                            
typedef unsigned long           DWORD;                           
 

typedef unsigned long long      QWORD;                           
typedef signed char             CHAR;                            
typedef signed short int        SHORT;                           
typedef signed long             LONG;                            
 

typedef signed long long        LONGLONG;                        
typedef union
{
    BYTE Val;
    struct 
    {
         BYTE b0:1;
         BYTE b1:1;
         BYTE b2:1;
         BYTE b3:1;
         BYTE b4:1;
         BYTE b5:1;
         BYTE b6:1;
         BYTE b7:1;
    } bits;
} BYTE_VAL, BYTE_BITS;

typedef union
{
    WORD Val;
    BYTE v[2] ;
    struct 
    {
        BYTE LB;
        BYTE HB;
    } byte;
    struct 
    {
         BYTE b0:1;
         BYTE b1:1;
         BYTE b2:1;
         BYTE b3:1;
         BYTE b4:1;
         BYTE b5:1;
         BYTE b6:1;
         BYTE b7:1;
         BYTE b8:1;
         BYTE b9:1;
         BYTE b10:1;
         BYTE b11:1;
         BYTE b12:1;
         BYTE b13:1;
         BYTE b14:1;
         BYTE b15:1;
    } bits;
} WORD_VAL, WORD_BITS;

typedef union
{
    DWORD Val;
    WORD w[2] ;
    BYTE v[4] ;
    struct 
    {
        WORD LW;
        WORD HW;
    } word;
    struct 
    {
        BYTE LB;
        BYTE HB;
        BYTE UB;
        BYTE MB;
    } byte;
    struct 
    {
        WORD_VAL low;
        WORD_VAL high;
    }wordUnion;
    struct 
    {
         BYTE b0:1;
         BYTE b1:1;
         BYTE b2:1;
         BYTE b3:1;
         BYTE b4:1;
         BYTE b5:1;
         BYTE b6:1;
         BYTE b7:1;
         BYTE b8:1;
         BYTE b9:1;
         BYTE b10:1;
         BYTE b11:1;
         BYTE b12:1;
         BYTE b13:1;
         BYTE b14:1;
         BYTE b15:1;
         BYTE b16:1;
         BYTE b17:1;
         BYTE b18:1;
         BYTE b19:1;
         BYTE b20:1;
         BYTE b21:1;
         BYTE b22:1;
         BYTE b23:1;
         BYTE b24:1;
         BYTE b25:1;
         BYTE b26:1;
         BYTE b27:1;
         BYTE b28:1;
         BYTE b29:1;
         BYTE b30:1;
         BYTE b31:1;
    } bits;
} DWORD_VAL;

 
typedef union
{
    QWORD Val;
    DWORD d[2] ;
    WORD w[4] ;
    BYTE v[8] ;
    struct 
    {
        DWORD LD;
        DWORD HD;
    } dword;
    struct 
    {
        WORD LW;
        WORD HW;
        WORD UW;
        WORD MW;
    } word;
    struct 
    {
         BYTE b0:1;
         BYTE b1:1;
         BYTE b2:1;
         BYTE b3:1;
         BYTE b4:1;
         BYTE b5:1;
         BYTE b6:1;
         BYTE b7:1;
         BYTE b8:1;
         BYTE b9:1;
         BYTE b10:1;
         BYTE b11:1;
         BYTE b12:1;
         BYTE b13:1;
         BYTE b14:1;
         BYTE b15:1;
         BYTE b16:1;
         BYTE b17:1;
         BYTE b18:1;
         BYTE b19:1;
         BYTE b20:1;
         BYTE b21:1;
         BYTE b22:1;
         BYTE b23:1;
         BYTE b24:1;
         BYTE b25:1;
         BYTE b26:1;
         BYTE b27:1;
         BYTE b28:1;
         BYTE b29:1;
         BYTE b30:1;
         BYTE b31:1;
         BYTE b32:1;
         BYTE b33:1;
         BYTE b34:1;
         BYTE b35:1;
         BYTE b36:1;
         BYTE b37:1;
         BYTE b38:1;
         BYTE b39:1;
         BYTE b40:1;
         BYTE b41:1;
         BYTE b42:1;
         BYTE b43:1;
         BYTE b44:1;
         BYTE b45:1;
         BYTE b46:1;
         BYTE b47:1;
         BYTE b48:1;
         BYTE b49:1;
         BYTE b50:1;
         BYTE b51:1;
         BYTE b52:1;
         BYTE b53:1;
         BYTE b54:1;
         BYTE b55:1;
         BYTE b56:1;
         BYTE b57:1;
         BYTE b58:1;
         BYTE b59:1;
         BYTE b60:1;
         BYTE b61:1;
         BYTE b62:1;
         BYTE b63:1;
    } bits;
} QWORD_VAL;

#line 547 "C:/MCC18/v3.35/h/GenericTypeDefs.h"

#line 549 "C:/MCC18/v3.35/h/GenericTypeDefs.h"
#line 37 "usb_device.c"

#line 1 "C:/PIC/Microchip Solutions/Microchip/Include/Compiler.h"

#line 51 "C:/PIC/Microchip Solutions/Microchip/Include/Compiler.h"
 

#line 54 "C:/PIC/Microchip Solutions/Microchip/Include/Compiler.h"


#line 57 "C:/PIC/Microchip Solutions/Microchip/Include/Compiler.h"
	
#line 59 "C:/PIC/Microchip Solutions/Microchip/Include/Compiler.h"
#line 62 "C:/PIC/Microchip Solutions/Microchip/Include/Compiler.h"
#line 1 "C:/MCC18/v3.35/h/p18cxxx.h"

#line 3 "C:/MCC18/v3.35/h/p18cxxx.h"

#line 5 "C:/MCC18/v3.35/h/p18cxxx.h"
#line 7 "C:/MCC18/v3.35/h/p18cxxx.h"
#line 9 "C:/MCC18/v3.35/h/p18cxxx.h"
#line 11 "C:/MCC18/v3.35/h/p18cxxx.h"
#line 13 "C:/MCC18/v3.35/h/p18cxxx.h"
#line 15 "C:/MCC18/v3.35/h/p18cxxx.h"
#line 17 "C:/MCC18/v3.35/h/p18cxxx.h"
#line 19 "C:/MCC18/v3.35/h/p18cxxx.h"
#line 21 "C:/MCC18/v3.35/h/p18cxxx.h"
#line 23 "C:/MCC18/v3.35/h/p18cxxx.h"
#line 25 "C:/MCC18/v3.35/h/p18cxxx.h"
#line 27 "C:/MCC18/v3.35/h/p18cxxx.h"
#line 29 "C:/MCC18/v3.35/h/p18cxxx.h"
#line 31 "C:/MCC18/v3.35/h/p18cxxx.h"
#line 33 "C:/MCC18/v3.35/h/p18cxxx.h"
#line 35 "C:/MCC18/v3.35/h/p18cxxx.h"
#line 37 "C:/MCC18/v3.35/h/p18cxxx.h"
#line 39 "C:/MCC18/v3.35/h/p18cxxx.h"
#line 41 "C:/MCC18/v3.35/h/p18cxxx.h"
#line 43 "C:/MCC18/v3.35/h/p18cxxx.h"
#line 45 "C:/MCC18/v3.35/h/p18cxxx.h"
#line 47 "C:/MCC18/v3.35/h/p18cxxx.h"
#line 49 "C:/MCC18/v3.35/h/p18cxxx.h"
#line 51 "C:/MCC18/v3.35/h/p18cxxx.h"
#line 53 "C:/MCC18/v3.35/h/p18cxxx.h"
#line 55 "C:/MCC18/v3.35/h/p18cxxx.h"
#line 57 "C:/MCC18/v3.35/h/p18cxxx.h"
#line 59 "C:/MCC18/v3.35/h/p18cxxx.h"
#line 61 "C:/MCC18/v3.35/h/p18cxxx.h"
#line 63 "C:/MCC18/v3.35/h/p18cxxx.h"
#line 65 "C:/MCC18/v3.35/h/p18cxxx.h"
#line 67 "C:/MCC18/v3.35/h/p18cxxx.h"
#line 69 "C:/MCC18/v3.35/h/p18cxxx.h"
#line 71 "C:/MCC18/v3.35/h/p18cxxx.h"
#line 73 "C:/MCC18/v3.35/h/p18cxxx.h"
#line 75 "C:/MCC18/v3.35/h/p18cxxx.h"
#line 77 "C:/MCC18/v3.35/h/p18cxxx.h"
#line 79 "C:/MCC18/v3.35/h/p18cxxx.h"
#line 81 "C:/MCC18/v3.35/h/p18cxxx.h"
#line 83 "C:/MCC18/v3.35/h/p18cxxx.h"
#line 85 "C:/MCC18/v3.35/h/p18cxxx.h"
#line 87 "C:/MCC18/v3.35/h/p18cxxx.h"
#line 89 "C:/MCC18/v3.35/h/p18cxxx.h"
#line 91 "C:/MCC18/v3.35/h/p18cxxx.h"
#line 93 "C:/MCC18/v3.35/h/p18cxxx.h"
#line 95 "C:/MCC18/v3.35/h/p18cxxx.h"
#line 97 "C:/MCC18/v3.35/h/p18cxxx.h"
#line 99 "C:/MCC18/v3.35/h/p18cxxx.h"
#line 101 "C:/MCC18/v3.35/h/p18cxxx.h"
#line 103 "C:/MCC18/v3.35/h/p18cxxx.h"
#line 105 "C:/MCC18/v3.35/h/p18cxxx.h"
#line 107 "C:/MCC18/v3.35/h/p18cxxx.h"
#line 109 "C:/MCC18/v3.35/h/p18cxxx.h"
#line 111 "C:/MCC18/v3.35/h/p18cxxx.h"
#line 113 "C:/MCC18/v3.35/h/p18cxxx.h"
#line 115 "C:/MCC18/v3.35/h/p18cxxx.h"
#line 117 "C:/MCC18/v3.35/h/p18cxxx.h"
#line 119 "C:/MCC18/v3.35/h/p18cxxx.h"
#line 121 "C:/MCC18/v3.35/h/p18cxxx.h"
#line 123 "C:/MCC18/v3.35/h/p18cxxx.h"
#line 125 "C:/MCC18/v3.35/h/p18cxxx.h"
#line 127 "C:/MCC18/v3.35/h/p18cxxx.h"
#line 129 "C:/MCC18/v3.35/h/p18cxxx.h"
#line 131 "C:/MCC18/v3.35/h/p18cxxx.h"
#line 133 "C:/MCC18/v3.35/h/p18cxxx.h"
#line 135 "C:/MCC18/v3.35/h/p18cxxx.h"
#line 137 "C:/MCC18/v3.35/h/p18cxxx.h"
#line 139 "C:/MCC18/v3.35/h/p18cxxx.h"
#line 141 "C:/MCC18/v3.35/h/p18cxxx.h"
#line 143 "C:/MCC18/v3.35/h/p18cxxx.h"
#line 145 "C:/MCC18/v3.35/h/p18cxxx.h"
#line 147 "C:/MCC18/v3.35/h/p18cxxx.h"
#line 149 "C:/MCC18/v3.35/h/p18cxxx.h"
#line 151 "C:/MCC18/v3.35/h/p18cxxx.h"
#line 153 "C:/MCC18/v3.35/h/p18cxxx.h"
#line 155 "C:/MCC18/v3.35/h/p18cxxx.h"
#line 157 "C:/MCC18/v3.35/h/p18cxxx.h"
#line 159 "C:/MCC18/v3.35/h/p18cxxx.h"
#line 161 "C:/MCC18/v3.35/h/p18cxxx.h"
#line 163 "C:/MCC18/v3.35/h/p18cxxx.h"
#line 165 "C:/MCC18/v3.35/h/p18cxxx.h"
#line 167 "C:/MCC18/v3.35/h/p18cxxx.h"
#line 169 "C:/MCC18/v3.35/h/p18cxxx.h"
#line 171 "C:/MCC18/v3.35/h/p18cxxx.h"
#line 173 "C:/MCC18/v3.35/h/p18cxxx.h"
#line 175 "C:/MCC18/v3.35/h/p18cxxx.h"
#line 177 "C:/MCC18/v3.35/h/p18cxxx.h"
#line 179 "C:/MCC18/v3.35/h/p18cxxx.h"
#line 181 "C:/MCC18/v3.35/h/p18cxxx.h"
#line 183 "C:/MCC18/v3.35/h/p18cxxx.h"
#line 185 "C:/MCC18/v3.35/h/p18cxxx.h"
#line 187 "C:/MCC18/v3.35/h/p18cxxx.h"
#line 189 "C:/MCC18/v3.35/h/p18cxxx.h"
#line 191 "C:/MCC18/v3.35/h/p18cxxx.h"
#line 193 "C:/MCC18/v3.35/h/p18cxxx.h"
#line 195 "C:/MCC18/v3.35/h/p18cxxx.h"
#line 197 "C:/MCC18/v3.35/h/p18cxxx.h"
#line 199 "C:/MCC18/v3.35/h/p18cxxx.h"
#line 201 "C:/MCC18/v3.35/h/p18cxxx.h"
#line 203 "C:/MCC18/v3.35/h/p18cxxx.h"
#line 205 "C:/MCC18/v3.35/h/p18cxxx.h"
#line 207 "C:/MCC18/v3.35/h/p18cxxx.h"
#line 1 "C:/MCC18/v3.35/h/p18f4550.h"

#line 5 "C:/MCC18/v3.35/h/p18f4550.h"
 


#line 9 "C:/MCC18/v3.35/h/p18f4550.h"

extern volatile near unsigned char       SPPDATA;
extern volatile near unsigned char       SPPCFG;
extern volatile near struct {
  unsigned WS0:1;
  unsigned WS1:1;
  unsigned WS2:1;
  unsigned WS3:1;
  unsigned CLK1EN:1;
  unsigned CSEN:1;
  unsigned CLKCFG0:1;
  unsigned CLKCFG1:1;
} SPPCFGbits;
extern volatile near unsigned char       SPPEPS;
extern volatile near struct {
  unsigned ADDR0:1;
  unsigned ADDR1:1;
  unsigned ADDR2:1;
  unsigned ADDR3:1;
  unsigned SPPBUSY:1;
  unsigned :1;
  unsigned WRSPP:1;
  unsigned RDSPP:1;
} SPPEPSbits;
extern volatile near unsigned char       SPPCON;
extern volatile near struct {
  unsigned SPPEN:1;
  unsigned SPPOWN:1;
} SPPCONbits;
extern volatile near unsigned            UFRM;
extern volatile near unsigned char       UFRML;
extern volatile near struct {
  unsigned FRM0:1;
  unsigned FRM1:1;
  unsigned FRM2:1;
  unsigned FRM3:1;
  unsigned FRM4:1;
  unsigned FRM5:1;
  unsigned FRM6:1;
  unsigned FRM7:1;
} UFRMLbits;
extern volatile near unsigned char       UFRMH;
extern volatile near struct {
  unsigned FRM8:1;
  unsigned FRM9:1;
  unsigned FRM10:1;
} UFRMHbits;
extern volatile near unsigned char       UIR;
extern volatile near struct {
  unsigned URSTIF:1;
  unsigned UERRIF:1;
  unsigned ACTVIF:1;
  unsigned TRNIF:1;
  unsigned IDLEIF:1;
  unsigned STALLIF:1;
  unsigned SOFIF:1;
} UIRbits;
extern volatile near unsigned char       UIE;
extern volatile near struct {
  unsigned URSTIE:1;
  unsigned UERRIE:1;
  unsigned ACTVIE:1;
  unsigned TRNIE:1;
  unsigned IDLEIE:1;
  unsigned STALLIE:1;
  unsigned SOFIE:1;
} UIEbits;
extern volatile near unsigned char       UEIR;
extern volatile near struct {
  unsigned PIDEF:1;
  unsigned CRC5EF:1;
  unsigned CRC16EF:1;
  unsigned DFN8EF:1;
  unsigned BTOEF:1;
  unsigned :2;
  unsigned BTSEF:1;
} UEIRbits;
extern volatile near unsigned char       UEIE;
extern volatile near struct {
  unsigned PIDEE:1;
  unsigned CRC5EE:1;
  unsigned CRC16EE:1;
  unsigned DFN8EE:1;
  unsigned BTOEE:1;
  unsigned :2;
  unsigned BTSEE:1;
} UEIEbits;
extern volatile near unsigned char       USTAT;
extern volatile near struct {
  unsigned :1;
  unsigned PPBI:1;
  unsigned DIR:1;
  unsigned ENDP0:1;
  unsigned ENDP1:1;
  unsigned ENDP2:1;
  unsigned ENDP3:1;
} USTATbits;
extern volatile near unsigned char       UCON;
extern volatile near struct {
  unsigned :1;
  unsigned SUSPND:1;
  unsigned RESUME:1;
  unsigned USBEN:1;
  unsigned PKTDIS:1;
  unsigned SE0:1;
  unsigned PPBRST:1;
} UCONbits;
extern volatile near unsigned char       UADDR;
extern volatile near struct {
  unsigned ADDR0:1;
  unsigned ADDR1:1;
  unsigned ADDR2:1;
  unsigned ADDR3:1;
  unsigned ADDR4:1;
  unsigned ADDR5:1;
  unsigned ADDR6:1;
} UADDRbits;
extern volatile near unsigned char       UCFG;
extern volatile near struct {
  unsigned PPB0:1;
  unsigned PPB1:1;
  unsigned FSEN:1;
  unsigned UTRDIS:1;
  unsigned UPUEN:1;
  unsigned :1;
  unsigned UOEMON:1;
  unsigned UTEYE:1;
} UCFGbits;
extern volatile near unsigned char       UEP0;
extern volatile near struct {
  unsigned EPSTALL:1;
  unsigned EPINEN:1;
  unsigned EPOUTEN:1;
  unsigned EPCONDIS:1;
  unsigned EPHSHK:1;
} UEP0bits;
extern volatile near unsigned char       UEP1;
extern volatile near struct {
  unsigned EPSTALL:1;
  unsigned EPINEN:1;
  unsigned EPOUTEN:1;
  unsigned EPCONDIS:1;
  unsigned EPHSHK:1;
} UEP1bits;
extern volatile near unsigned char       UEP2;
extern volatile near struct {
  unsigned EPSTALL:1;
  unsigned EPINEN:1;
  unsigned EPOUTEN:1;
  unsigned EPCONDIS:1;
  unsigned EPHSHK:1;
} UEP2bits;
extern volatile near unsigned char       UEP3;
extern volatile near struct {
  unsigned EPSTALL:1;
  unsigned EPINEN:1;
  unsigned EPOUTEN:1;
  unsigned EPCONDIS:1;
  unsigned EPHSHK:1;
} UEP3bits;
extern volatile near unsigned char       UEP4;
extern volatile near struct {
  unsigned EPSTALL:1;
  unsigned EPINEN:1;
  unsigned EPOUTEN:1;
  unsigned EPCONDIS:1;
  unsigned EPHSHK:1;
} UEP4bits;
extern volatile near unsigned char       UEP5;
extern volatile near struct {
  unsigned EPSTALL:1;
  unsigned EPINEN:1;
  unsigned EPOUTEN:1;
  unsigned EPCONDIS:1;
  unsigned EPHSHK:1;
} UEP5bits;
extern volatile near unsigned char       UEP6;
extern volatile near struct {
  unsigned EPSTALL:1;
  unsigned EPINEN:1;
  unsigned EPOUTEN:1;
  unsigned EPCONDIS:1;
  unsigned EPHSHK:1;
} UEP6bits;
extern volatile near unsigned char       UEP7;
extern volatile near struct {
  unsigned EPSTALL:1;
  unsigned EPINEN:1;
  unsigned EPOUTEN:1;
  unsigned EPCONDIS:1;
  unsigned EPHSHK:1;
} UEP7bits;
extern volatile near unsigned char       UEP8;
extern volatile near struct {
  unsigned EPSTALL:1;
  unsigned EPINEN:1;
  unsigned EPOUTEN:1;
  unsigned EPCONDIS:1;
  unsigned EPHSHK:1;
} UEP8bits;
extern volatile near unsigned char       UEP9;
extern volatile near struct {
  unsigned EPSTALL:1;
  unsigned EPINEN:1;
  unsigned EPOUTEN:1;
  unsigned EPCONDIS:1;
  unsigned EPHSHK:1;
} UEP9bits;
extern volatile near unsigned char       UEP10;
extern volatile near struct {
  unsigned EPSTALL:1;
  unsigned EPINEN:1;
  unsigned EPOUTEN:1;
  unsigned EPCONDIS:1;
  unsigned EPHSHK:1;
} UEP10bits;
extern volatile near unsigned char       UEP11;
extern volatile near struct {
  unsigned EPSTALL:1;
  unsigned EPINEN:1;
  unsigned EPOUTEN:1;
  unsigned EPCONDIS:1;
  unsigned EPHSHK:1;
} UEP11bits;
extern volatile near unsigned char       UEP12;
extern volatile near struct {
  unsigned EPSTALL:1;
  unsigned EPINEN:1;
  unsigned EPOUTEN:1;
  unsigned EPCONDIS:1;
  unsigned EPHSHK:1;
} UEP12bits;
extern volatile near unsigned char       UEP13;
extern volatile near struct {
  unsigned EPSTALL:1;
  unsigned EPINEN:1;
  unsigned EPOUTEN:1;
  unsigned EPCONDIS:1;
  unsigned EPHSHK:1;
} UEP13bits;
extern volatile near unsigned char       UEP14;
extern volatile near struct {
  unsigned EPSTALL:1;
  unsigned EPINEN:1;
  unsigned EPOUTEN:1;
  unsigned EPCONDIS:1;
  unsigned EPHSHK:1;
} UEP14bits;
extern volatile near unsigned char       UEP15;
extern volatile near struct {
  unsigned EPSTALL:1;
  unsigned EPINEN:1;
  unsigned EPOUTEN:1;
  unsigned EPCONDIS:1;
  unsigned EPHSHK:1;
} UEP15bits;
extern volatile near unsigned char       PORTA;
extern volatile near union {
  struct {
    unsigned RA0:1;
    unsigned RA1:1;
    unsigned RA2:1;
    unsigned RA3:1;
    unsigned RA4:1;
    unsigned RA5:1;
    unsigned RA6:1;
  };
  struct {
    unsigned AN0:1;
    unsigned AN1:1;
    unsigned AN2:1;
    unsigned AN3:1;
    unsigned T0CKI:1;
    unsigned AN4:1;
    unsigned OSC2:1;
  };
  struct {
    unsigned :2;
    unsigned VREFM:1;
    unsigned VREFP:1;
    unsigned :1;
    unsigned LVDIN:1;
  };
  struct {
    unsigned :5;
    unsigned HLVDIN:1;
  };
} PORTAbits;
extern volatile near unsigned char       PORTB;
extern volatile near union {
  struct {
    unsigned RB0:1;
    unsigned RB1:1;
    unsigned RB2:1;
    unsigned RB3:1;
    unsigned RB4:1;
    unsigned RB5:1;
    unsigned RB6:1;
    unsigned RB7:1;
  };
  struct {
    unsigned INT0:1;
    unsigned INT1:1;
    unsigned INT2:1;
  };
  struct {
    unsigned :5;
    unsigned PGM:1;
    unsigned PGC:1;
    unsigned PGD:1;
  };
} PORTBbits;
extern volatile near unsigned char       PORTC;
extern volatile near union {
  struct {
    unsigned RC0:1;
    unsigned RC1:1;
    unsigned RC2:1;
    unsigned :1;
    unsigned RC4:1;
    unsigned RC5:1;
    unsigned RC6:1;
    unsigned RC7:1;
  };
  struct {
    unsigned T1OSO:1;
    unsigned T1OSI:1;
    unsigned CCP1:1;
    unsigned :3;
    unsigned TX:1;
    unsigned RX:1;
  };
  struct {
    unsigned T13CKI:1;
    unsigned :1;
    unsigned P1A:1;
    unsigned :3;
    unsigned CK:1;
    unsigned DT:1;
  };
} PORTCbits;
extern volatile near unsigned char       PORTD;
extern volatile near union {
  struct {
    unsigned RD0:1;
    unsigned RD1:1;
    unsigned RD2:1;
    unsigned RD3:1;
    unsigned RD4:1;
    unsigned RD5:1;
    unsigned RD6:1;
    unsigned RD7:1;
  };
  struct {
    unsigned SPP0:1;
    unsigned SPP1:1;
    unsigned SPP2:1;
    unsigned SPP3:1;
    unsigned SPP4:1;
    unsigned SPP5:1;
    unsigned SPP6:1;
    unsigned SPP7:1;
  };
} PORTDbits;
extern volatile near unsigned char       PORTE;
extern volatile near union {
  struct {
    unsigned RE0:1;
    unsigned RE1:1;
    unsigned RE2:1;
    unsigned RE3:1;
    unsigned :3;
    unsigned RDPU:1;
  };
  struct {
    unsigned CK1SPP:1;
    unsigned CK2SPP:1;
    unsigned OESPP:1;
  };
} PORTEbits;
extern volatile near unsigned char       LATA;
extern volatile near struct {
  unsigned LATA0:1;
  unsigned LATA1:1;
  unsigned LATA2:1;
  unsigned LATA3:1;
  unsigned LATA4:1;
  unsigned LATA5:1;
  unsigned LATA6:1;
} LATAbits;
extern volatile near unsigned char       LATB;
extern volatile near struct {
  unsigned LATB0:1;
  unsigned LATB1:1;
  unsigned LATB2:1;
  unsigned LATB3:1;
  unsigned LATB4:1;
  unsigned LATB5:1;
  unsigned LATB6:1;
  unsigned LATB7:1;
} LATBbits;
extern volatile near unsigned char       LATC;
extern volatile near struct {
  unsigned LATC0:1;
  unsigned LATC1:1;
  unsigned LATC2:1;
  unsigned :3;
  unsigned LATC6:1;
  unsigned LATC7:1;
} LATCbits;
extern volatile near unsigned char       LATD;
extern volatile near struct {
  unsigned LATD0:1;
  unsigned LATD1:1;
  unsigned LATD2:1;
  unsigned LATD3:1;
  unsigned LATD4:1;
  unsigned LATD5:1;
  unsigned LATD6:1;
  unsigned LATD7:1;
} LATDbits;
extern volatile near unsigned char       LATE;
extern volatile near struct {
  unsigned LATE0:1;
  unsigned LATE1:1;
  unsigned LATE2:1;
} LATEbits;
extern volatile near unsigned char       DDRA;
extern volatile near struct {
  unsigned RA0:1;
  unsigned RA1:1;
  unsigned RA2:1;
  unsigned RA3:1;
  unsigned RA4:1;
  unsigned RA5:1;
  unsigned RA6:1;
} DDRAbits;
extern volatile near unsigned char       TRISA;
extern volatile near struct {
  unsigned TRISA0:1;
  unsigned TRISA1:1;
  unsigned TRISA2:1;
  unsigned TRISA3:1;
  unsigned TRISA4:1;
  unsigned TRISA5:1;
  unsigned TRISA6:1;
} TRISAbits;
extern volatile near unsigned char       DDRB;
extern volatile near struct {
  unsigned RB0:1;
  unsigned RB1:1;
  unsigned RB2:1;
  unsigned RB3:1;
  unsigned RB4:1;
  unsigned RB5:1;
  unsigned RB6:1;
  unsigned RB7:1;
} DDRBbits;
extern volatile near unsigned char       TRISB;
extern volatile near struct {
  unsigned TRISB0:1;
  unsigned TRISB1:1;
  unsigned TRISB2:1;
  unsigned TRISB3:1;
  unsigned TRISB4:1;
  unsigned TRISB5:1;
  unsigned TRISB6:1;
  unsigned TRISB7:1;
} TRISBbits;
extern volatile near unsigned char       DDRC;
extern volatile near struct {
  unsigned RC0:1;
  unsigned RC1:1;
  unsigned RC2:1;
  unsigned :3;
  unsigned RC6:1;
  unsigned RC7:1;
} DDRCbits;
extern volatile near unsigned char       TRISC;
extern volatile near struct {
  unsigned TRISC0:1;
  unsigned TRISC1:1;
  unsigned TRISC2:1;
  unsigned :3;
  unsigned TRISC6:1;
  unsigned TRISC7:1;
} TRISCbits;
extern volatile near unsigned char       DDRD;
extern volatile near struct {
  unsigned RD0:1;
  unsigned RD1:1;
  unsigned RD2:1;
  unsigned RD3:1;
  unsigned RD4:1;
  unsigned RD5:1;
  unsigned RD6:1;
  unsigned RD7:1;
} DDRDbits;
extern volatile near unsigned char       TRISD;
extern volatile near struct {
  unsigned TRISD0:1;
  unsigned TRISD1:1;
  unsigned TRISD2:1;
  unsigned TRISD3:1;
  unsigned TRISD4:1;
  unsigned TRISD5:1;
  unsigned TRISD6:1;
  unsigned TRISD7:1;
} TRISDbits;
extern volatile near unsigned char       DDRE;
extern volatile near struct {
  unsigned RE0:1;
  unsigned RE1:1;
  unsigned RE2:1;
} DDREbits;
extern volatile near unsigned char       TRISE;
extern volatile near struct {
  unsigned TRISE0:1;
  unsigned TRISE1:1;
  unsigned TRISE2:1;
} TRISEbits;
extern volatile near unsigned char       OSCTUNE;
extern volatile near struct {
  unsigned TUN0:1;
  unsigned TUN1:1;
  unsigned TUN2:1;
  unsigned TUN3:1;
  unsigned TUN4:1;
  unsigned :2;
  unsigned INTSRC:1;
} OSCTUNEbits;
extern volatile near unsigned char       PIE1;
extern volatile near struct {
  unsigned TMR1IE:1;
  unsigned TMR2IE:1;
  unsigned CCP1IE:1;
  unsigned SSPIE:1;
  unsigned TXIE:1;
  unsigned RCIE:1;
  unsigned ADIE:1;
  unsigned SPPIE:1;
} PIE1bits;
extern volatile near unsigned char       PIR1;
extern volatile near struct {
  unsigned TMR1IF:1;
  unsigned TMR2IF:1;
  unsigned CCP1IF:1;
  unsigned SSPIF:1;
  unsigned TXIF:1;
  unsigned RCIF:1;
  unsigned ADIF:1;
  unsigned SPPIF:1;
} PIR1bits;
extern volatile near unsigned char       IPR1;
extern volatile near struct {
  unsigned TMR1IP:1;
  unsigned TMR2IP:1;
  unsigned CCP1IP:1;
  unsigned SSPIP:1;
  unsigned TXIP:1;
  unsigned RCIP:1;
  unsigned ADIP:1;
  unsigned SPPIP:1;
} IPR1bits;
extern volatile near unsigned char       PIE2;
extern volatile near union {
  struct {
    unsigned CCP2IE:1;
    unsigned TMR3IE:1;
    unsigned LVDIE:1;
    unsigned BCLIE:1;
    unsigned EEIE:1;
    unsigned USBIE:1;
    unsigned CMIE:1;
    unsigned OSCFIE:1;
  };
  struct {
    unsigned :2;
    unsigned HLVDIE:1;
  };
} PIE2bits;
extern volatile near unsigned char       PIR2;
extern volatile near union {
  struct {
    unsigned CCP2IF:1;
    unsigned TMR3IF:1;
    unsigned LVDIF:1;
    unsigned BCLIF:1;
    unsigned EEIF:1;
    unsigned USBIF:1;
    unsigned CMIF:1;
    unsigned OSCFIF:1;
  };
  struct {
    unsigned :2;
    unsigned HLVDIF:1;
  };
} PIR2bits;
extern volatile near unsigned char       IPR2;
extern volatile near union {
  struct {
    unsigned CCP2IP:1;
    unsigned TMR3IP:1;
    unsigned LVDIP:1;
    unsigned BCLIP:1;
    unsigned EEIP:1;
    unsigned USBIP:1;
    unsigned CMIP:1;
    unsigned OSCFIP:1;
  };
  struct {
    unsigned :2;
    unsigned HLVDIP:1;
  };
} IPR2bits;
extern volatile near unsigned char       EECON1;
extern volatile near struct {
  unsigned RD:1;
  unsigned WR:1;
  unsigned WREN:1;
  unsigned WRERR:1;
  unsigned FREE:1;
  unsigned :1;
  unsigned CFGS:1;
  unsigned EEPGD:1;
} EECON1bits;
extern volatile near unsigned char       EECON2;
extern volatile near unsigned char       EEDATA;
extern volatile near unsigned char       EEADR;
extern volatile near unsigned char       RCSTA;
extern volatile near union {
  struct {
    unsigned RX9D:1;
    unsigned OERR:1;
    unsigned FERR:1;
    unsigned ADDEN:1;
    unsigned CREN:1;
    unsigned SREN:1;
    unsigned RX9:1;
    unsigned SPEN:1;
  };
  struct {
    unsigned :3;
    unsigned ADEN:1;
  };
} RCSTAbits;
extern volatile near unsigned char       TXSTA;
extern volatile near struct {
  unsigned TX9D:1;
  unsigned TRMT:1;
  unsigned BRGH:1;
  unsigned SENDB:1;
  unsigned SYNC:1;
  unsigned TXEN:1;
  unsigned TX9:1;
  unsigned CSRC:1;
} TXSTAbits;
extern volatile near unsigned char       TXREG;
extern volatile near unsigned char       RCREG;
extern volatile near unsigned char       SPBRG;
extern volatile near unsigned char       SPBRGH;
extern volatile near unsigned char       T3CON;
extern volatile near union {
  struct {
    unsigned TMR3ON:1;
    unsigned TMR3CS:1;
    unsigned T3SYNC:1;
    unsigned T3CCP1:1;
    unsigned T3CKPS0:1;
    unsigned T3CKPS1:1;
    unsigned T3CCP2:1;
    unsigned RD16:1;
  };
  struct {
    unsigned :2;
    unsigned T3NSYNC:1;
  };
  struct {
    unsigned :2;
    unsigned NOT_T3SYNC:1;
  };
} T3CONbits;
extern volatile near unsigned char       TMR3L;
extern volatile near unsigned char       TMR3H;
extern volatile near unsigned char       CMCON;
extern volatile near struct {
  unsigned CM0:1;
  unsigned CM1:1;
  unsigned CM2:1;
  unsigned CIS:1;
  unsigned C1INV:1;
  unsigned C2INV:1;
  unsigned C1OUT:1;
  unsigned C2OUT:1;
} CMCONbits;
extern volatile near unsigned char       CVRCON;
extern volatile near union {
  struct {
    unsigned CVR0:1;
    unsigned CVR1:1;
    unsigned CVR2:1;
    unsigned CVR3:1;
    unsigned CVREF:1;
    unsigned CVRR:1;
    unsigned CVROE:1;
    unsigned CVREN:1;
  };
  struct {
    unsigned :4;
    unsigned CVRSS:1;
  };
} CVRCONbits;
extern volatile near unsigned char       CCP1AS;
extern volatile near struct {
  unsigned PSSBD0:1;
  unsigned PSSBD1:1;
  unsigned PSSAC0:1;
  unsigned PSSAC1:1;
  unsigned ECCPAS0:1;
  unsigned ECCPAS1:1;
  unsigned ECCPAS2:1;
  unsigned ECCPASE:1;
} CCP1ASbits;
extern volatile near unsigned char       ECCP1AS;
extern volatile near struct {
  unsigned PSSBD0:1;
  unsigned PSSBD1:1;
  unsigned PSSAC0:1;
  unsigned PSSAC1:1;
  unsigned ECCPAS0:1;
  unsigned ECCPAS1:1;
  unsigned ECCPAS2:1;
  unsigned ECCPASE:1;
} ECCP1ASbits;
extern volatile near unsigned char       CCP1DEL;
extern volatile near struct {
  unsigned PDC0:1;
  unsigned PDC1:1;
  unsigned PDC2:1;
  unsigned PDC3:1;
  unsigned PDC4:1;
  unsigned PDC5:1;
  unsigned PDC6:1;
  unsigned PRSEN:1;
} CCP1DELbits;
extern volatile near unsigned char       ECCP1DEL;
extern volatile near struct {
  unsigned PDC0:1;
  unsigned PDC1:1;
  unsigned PDC2:1;
  unsigned PDC3:1;
  unsigned PDC4:1;
  unsigned PDC5:1;
  unsigned PDC6:1;
  unsigned PRSEN:1;
} ECCP1DELbits;
extern volatile near unsigned char       BAUDCON;
extern volatile near union {
  struct {
    unsigned ABDEN:1;
    unsigned WUE:1;
    unsigned :1;
    unsigned BRG16:1;
    unsigned SCKP:1;
    unsigned :1;
    unsigned RCIDL:1;
    unsigned ABDOVF:1;
  };
  struct {
    unsigned :4;
    unsigned TXCKP:1;
    unsigned RXDTP:1;
    unsigned RCMT:1;
  };
} BAUDCONbits;
extern volatile near unsigned char       CCP2CON;
extern volatile near struct {
  unsigned CCP2M0:1;
  unsigned CCP2M1:1;
  unsigned CCP2M2:1;
  unsigned CCP2M3:1;
  unsigned DC2B0:1;
  unsigned DC2B1:1;
} CCP2CONbits;
extern volatile near unsigned            CCPR2;
extern volatile near unsigned char       CCPR2L;
extern volatile near unsigned char       CCPR2H;
extern volatile near unsigned char       CCP1CON;
extern volatile near struct {
  unsigned CCP1M0:1;
  unsigned CCP1M1:1;
  unsigned CCP1M2:1;
  unsigned CCP1M3:1;
  unsigned DC1B0:1;
  unsigned DC1B1:1;
  unsigned P1M0:1;
  unsigned P1M1:1;
} CCP1CONbits;
extern volatile near unsigned char       ECCP1CON;
extern volatile near struct {
  unsigned CCP1M0:1;
  unsigned CCP1M1:1;
  unsigned CCP1M2:1;
  unsigned CCP1M3:1;
  unsigned DC1B0:1;
  unsigned DC1B1:1;
  unsigned P1M0:1;
  unsigned P1M1:1;
} ECCP1CONbits;
extern volatile near unsigned            CCPR1;
extern volatile near unsigned char       CCPR1L;
extern volatile near unsigned char       CCPR1H;
extern volatile near unsigned char       ADCON2;
extern volatile near struct {
  unsigned ADCS0:1;
  unsigned ADCS1:1;
  unsigned ADCS2:1;
  unsigned ACQT0:1;
  unsigned ACQT1:1;
  unsigned ACQT2:1;
  unsigned :1;
  unsigned ADFM:1;
} ADCON2bits;
extern volatile near unsigned char       ADCON1;
extern volatile near struct {
  unsigned PCFG0:1;
  unsigned PCFG1:1;
  unsigned PCFG2:1;
  unsigned PCFG3:1;
  unsigned VCFG0:1;
  unsigned VCFG1:1;
} ADCON1bits;
extern volatile near unsigned char       ADCON0;
extern volatile near union {
  struct {
    unsigned ADON:1;
    unsigned GO_DONE:1;
    unsigned CHS0:1;
    unsigned CHS1:1;
    unsigned CHS2:1;
    unsigned CHS3:1;
  };
  struct {
    unsigned :1;
    unsigned DONE:1;
  };
  struct {
    unsigned :1;
    unsigned GO:1;
  };
  struct {
    unsigned :1;
    unsigned NOT_DONE:1;
  };
} ADCON0bits;
extern volatile near unsigned            ADRES;
extern volatile near unsigned char       ADRESL;
extern volatile near unsigned char       ADRESH;
extern volatile near unsigned char       SSPCON2;
extern volatile near struct {
  unsigned SEN:1;
  unsigned RSEN:1;
  unsigned PEN:1;
  unsigned RCEN:1;
  unsigned ACKEN:1;
  unsigned ACKDT:1;
  unsigned ACKSTAT:1;
  unsigned GCEN:1;
} SSPCON2bits;
extern volatile near unsigned char       SSPCON1;
extern volatile near struct {
  unsigned SSPM0:1;
  unsigned SSPM1:1;
  unsigned SSPM2:1;
  unsigned SSPM3:1;
  unsigned CKP:1;
  unsigned SSPEN:1;
  unsigned SSPOV:1;
  unsigned WCOL:1;
} SSPCON1bits;
extern volatile near unsigned char       SSPSTAT;
extern volatile near union {
  struct {
    unsigned BF:1;
    unsigned UA:1;
    unsigned R_W:1;
    unsigned S:1;
    unsigned P:1;
    unsigned D_A:1;
    unsigned CKE:1;
    unsigned SMP:1;
  };
  struct {
    unsigned :2;
    unsigned I2C_READ:1;
    unsigned I2C_START:1;
    unsigned I2C_STOP:1;
    unsigned I2C_DAT:1;
  };
  struct {
    unsigned :2;
    unsigned NOT_W:1;
    unsigned :2;
    unsigned NOT_A:1;
  };
  struct {
    unsigned :2;
    unsigned NOT_WRITE:1;
    unsigned :2;
    unsigned NOT_ADDRESS:1;
  };
  struct {
    unsigned :2;
    unsigned READ_WRITE:1;
    unsigned :2;
    unsigned DATA_ADDRESS:1;
  };
  struct {
    unsigned :2;
    unsigned R:1;
    unsigned :2;
    unsigned D:1;
  };
} SSPSTATbits;
extern volatile near unsigned char       SSPADD;
extern volatile near unsigned char       SSPBUF;
extern volatile near unsigned char       T2CON;
extern volatile near struct {
  unsigned T2CKPS0:1;
  unsigned T2CKPS1:1;
  unsigned TMR2ON:1;
  unsigned T2OUTPS0:1;
  unsigned T2OUTPS1:1;
  unsigned T2OUTPS2:1;
  unsigned T2OUTPS3:1;
} T2CONbits;
extern volatile near unsigned char       PR2;
extern volatile near unsigned char       TMR2;
extern volatile near unsigned char       T1CON;
extern volatile near union {
  struct {
    unsigned TMR1ON:1;
    unsigned TMR1CS:1;
    unsigned T1SYNC:1;
    unsigned T1OSCEN:1;
    unsigned T1CKPS0:1;
    unsigned T1CKPS1:1;
    unsigned T1RUN:1;
    unsigned RD16:1;
  };
  struct {
    unsigned :2;
    unsigned NOT_T1SYNC:1;
  };
} T1CONbits;
extern volatile near unsigned char       TMR1L;
extern volatile near unsigned char       TMR1H;
extern volatile near unsigned char       RCON;
extern volatile near union {
  struct {
    unsigned NOT_BOR:1;
    unsigned NOT_POR:1;
    unsigned NOT_PD:1;
    unsigned NOT_TO:1;
    unsigned NOT_RI:1;
    unsigned :1;
    unsigned SBOREN:1;
    unsigned NOT_IPEN:1;
  };
  struct {
    unsigned BOR:1;
    unsigned POR:1;
    unsigned PD:1;
    unsigned TO:1;
    unsigned RI:1;
    unsigned :2;
    unsigned IPEN:1;
  };
} RCONbits;
extern volatile near unsigned char       WDTCON;
extern volatile near union {
  struct {
    unsigned SWDTEN:1;
  };
  struct {
    unsigned SWDTE:1;
  };
} WDTCONbits;
extern volatile near unsigned char       HLVDCON;
extern volatile near union {
  struct {
    unsigned LVDL0:1;
    unsigned LVDL1:1;
    unsigned LVDL2:1;
    unsigned LVDL3:1;
    unsigned LVDEN:1;
    unsigned IRVST:1;
  };
  struct {
    unsigned LVV0:1;
    unsigned LVV1:1;
    unsigned LVV2:1;
    unsigned LVV3:1;
    unsigned :1;
    unsigned BGST:1;
  };
  struct {
    unsigned HLVDL0:1;
    unsigned HLVDL1:1;
    unsigned HLVDL2:1;
    unsigned HLVDL3:1;
    unsigned HLVDEN:1;
    unsigned :2;
    unsigned VDIRMAG:1;
  };
  struct {
    unsigned :5;
    unsigned IVRST:1;
  };
} HLVDCONbits;
extern volatile near unsigned char       LVDCON;
extern volatile near union {
  struct {
    unsigned LVDL0:1;
    unsigned LVDL1:1;
    unsigned LVDL2:1;
    unsigned LVDL3:1;
    unsigned LVDEN:1;
    unsigned IRVST:1;
  };
  struct {
    unsigned LVV0:1;
    unsigned LVV1:1;
    unsigned LVV2:1;
    unsigned LVV3:1;
    unsigned :1;
    unsigned BGST:1;
  };
  struct {
    unsigned HLVDL0:1;
    unsigned HLVDL1:1;
    unsigned HLVDL2:1;
    unsigned HLVDL3:1;
    unsigned HLVDEN:1;
    unsigned :2;
    unsigned VDIRMAG:1;
  };
  struct {
    unsigned :5;
    unsigned IVRST:1;
  };
} LVDCONbits;
extern volatile near unsigned char       OSCCON;
extern volatile near union {
  struct {
    unsigned SCS0:1;
    unsigned SCS1:1;
    unsigned IOFS:1;
    unsigned OSTS:1;
    unsigned IRCF0:1;
    unsigned IRCF1:1;
    unsigned IRCF2:1;
    unsigned IDLEN:1;
  };
  struct {
    unsigned :2;
    unsigned FLTS:1;
  };
} OSCCONbits;
extern volatile near unsigned char       T0CON;
extern volatile near struct {
  unsigned T0PS0:1;
  unsigned T0PS1:1;
  unsigned T0PS2:1;
  unsigned PSA:1;
  unsigned T0SE:1;
  unsigned T0CS:1;
  unsigned T08BIT:1;
  unsigned TMR0ON:1;
} T0CONbits;
extern volatile near unsigned char       TMR0L;
extern volatile near unsigned char       TMR0H;
extern          near unsigned char       STATUS;
extern          near struct {
  unsigned C:1;
  unsigned DC:1;
  unsigned Z:1;
  unsigned OV:1;
  unsigned N:1;
} STATUSbits;
extern          near unsigned            FSR2;
extern          near unsigned char       FSR2L;
extern          near unsigned char       FSR2H;
extern volatile near unsigned char       PLUSW2;
extern volatile near unsigned char       PREINC2;
extern volatile near unsigned char       POSTDEC2;
extern volatile near unsigned char       POSTINC2;
extern          near unsigned char       INDF2;
extern          near unsigned char       BSR;
extern          near unsigned            FSR1;
extern          near unsigned char       FSR1L;
extern          near unsigned char       FSR1H;
extern volatile near unsigned char       PLUSW1;
extern volatile near unsigned char       PREINC1;
extern volatile near unsigned char       POSTDEC1;
extern volatile near unsigned char       POSTINC1;
extern          near unsigned char       INDF1;
extern          near unsigned char       WREG;
extern          near unsigned            FSR0;
extern          near unsigned char       FSR0L;
extern          near unsigned char       FSR0H;
extern volatile near unsigned char       PLUSW0;
extern volatile near unsigned char       PREINC0;
extern volatile near unsigned char       POSTDEC0;
extern volatile near unsigned char       POSTINC0;
extern          near unsigned char       INDF0;
extern volatile near unsigned char       INTCON3;
extern volatile near union {
  struct {
    unsigned INT1IF:1;
    unsigned INT2IF:1;
    unsigned :1;
    unsigned INT1IE:1;
    unsigned INT2IE:1;
    unsigned :1;
    unsigned INT1IP:1;
    unsigned INT2IP:1;
  };
  struct {
    unsigned INT1F:1;
    unsigned INT2F:1;
    unsigned :1;
    unsigned INT1E:1;
    unsigned INT2E:1;
    unsigned :1;
    unsigned INT1P:1;
    unsigned INT2P:1;
  };
} INTCON3bits;
extern volatile near unsigned char       INTCON2;
extern volatile near union {
  struct {
    unsigned RBIP:1;
    unsigned :1;
    unsigned TMR0IP:1;
    unsigned :1;
    unsigned INTEDG2:1;
    unsigned INTEDG1:1;
    unsigned INTEDG0:1;
    unsigned NOT_RBPU:1;
  };
  struct {
    unsigned :2;
    unsigned T0IP:1;
    unsigned :4;
    unsigned RBPU:1;
  };
} INTCON2bits;
extern volatile near unsigned char       INTCON;
extern volatile near union {
  struct {
    unsigned RBIF:1;
    unsigned INT0IF:1;
    unsigned TMR0IF:1;
    unsigned RBIE:1;
    unsigned INT0IE:1;
    unsigned TMR0IE:1;
    unsigned PEIE:1;
    unsigned GIE:1;
  };
  struct {
    unsigned :1;
    unsigned INT0F:1;
    unsigned T0IF:1;
    unsigned :1;
    unsigned INT0E:1;
    unsigned T0IE:1;
    unsigned GIEL:1;
    unsigned GIEH:1;
  };
} INTCONbits;
extern          near unsigned            PROD;
extern          near unsigned char       PRODL;
extern          near unsigned char       PRODH;
extern volatile near unsigned char       TABLAT;
extern volatile near unsigned short long TBLPTR;
extern volatile near unsigned char       TBLPTRL;
extern volatile near unsigned char       TBLPTRH;
extern volatile near unsigned char       TBLPTRU;
extern volatile near unsigned short long PC;
extern volatile near unsigned char       PCL;
extern volatile near unsigned char       PCLATH;
extern volatile near unsigned char       PCLATU;
extern volatile near unsigned char       STKPTR;
extern volatile near struct {
  unsigned STKPTR0:1;
  unsigned STKPTR1:1;
  unsigned STKPTR2:1;
  unsigned STKPTR3:1;
  unsigned STKPTR4:1;
  unsigned :1;
  unsigned STKUNF:1;
  unsigned STKFUL:1;
} STKPTRbits;
extern          near unsigned short long TOS;
extern          near unsigned char       TOSL;
extern          near unsigned char       TOSH;
extern          near unsigned char       TOSU;



#line 1221 "C:/MCC18/v3.35/h/p18f4550.h"
 
#line 1223 "C:/MCC18/v3.35/h/p18f4550.h"
#line 1224 "C:/MCC18/v3.35/h/p18f4550.h"


#line 1227 "C:/MCC18/v3.35/h/p18f4550.h"
 
#line 1229 "C:/MCC18/v3.35/h/p18f4550.h"
#line 1230 "C:/MCC18/v3.35/h/p18f4550.h"
#line 1231 "C:/MCC18/v3.35/h/p18f4550.h"
#line 1232 "C:/MCC18/v3.35/h/p18f4550.h"

#line 1234 "C:/MCC18/v3.35/h/p18f4550.h"
#line 1235 "C:/MCC18/v3.35/h/p18f4550.h"
#line 1236 "C:/MCC18/v3.35/h/p18f4550.h"
#line 1237 "C:/MCC18/v3.35/h/p18f4550.h"
#line 1238 "C:/MCC18/v3.35/h/p18f4550.h"


#line 1242 "C:/MCC18/v3.35/h/p18f4550.h"
 
#line 1244 "C:/MCC18/v3.35/h/p18f4550.h"


#line 1247 "C:/MCC18/v3.35/h/p18f4550.h"
#line 207 "C:/MCC18/v3.35/h/p18cxxx.h"

#line 209 "C:/MCC18/v3.35/h/p18cxxx.h"
#line 211 "C:/MCC18/v3.35/h/p18cxxx.h"
#line 213 "C:/MCC18/v3.35/h/p18cxxx.h"
#line 215 "C:/MCC18/v3.35/h/p18cxxx.h"
#line 217 "C:/MCC18/v3.35/h/p18cxxx.h"
#line 219 "C:/MCC18/v3.35/h/p18cxxx.h"
#line 221 "C:/MCC18/v3.35/h/p18cxxx.h"
#line 223 "C:/MCC18/v3.35/h/p18cxxx.h"
#line 225 "C:/MCC18/v3.35/h/p18cxxx.h"
#line 227 "C:/MCC18/v3.35/h/p18cxxx.h"
#line 229 "C:/MCC18/v3.35/h/p18cxxx.h"
#line 231 "C:/MCC18/v3.35/h/p18cxxx.h"
#line 233 "C:/MCC18/v3.35/h/p18cxxx.h"
#line 235 "C:/MCC18/v3.35/h/p18cxxx.h"
#line 237 "C:/MCC18/v3.35/h/p18cxxx.h"
#line 239 "C:/MCC18/v3.35/h/p18cxxx.h"
#line 241 "C:/MCC18/v3.35/h/p18cxxx.h"
#line 243 "C:/MCC18/v3.35/h/p18cxxx.h"
#line 245 "C:/MCC18/v3.35/h/p18cxxx.h"
#line 247 "C:/MCC18/v3.35/h/p18cxxx.h"
#line 249 "C:/MCC18/v3.35/h/p18cxxx.h"
#line 251 "C:/MCC18/v3.35/h/p18cxxx.h"
#line 253 "C:/MCC18/v3.35/h/p18cxxx.h"
#line 255 "C:/MCC18/v3.35/h/p18cxxx.h"
#line 257 "C:/MCC18/v3.35/h/p18cxxx.h"
#line 259 "C:/MCC18/v3.35/h/p18cxxx.h"
#line 261 "C:/MCC18/v3.35/h/p18cxxx.h"
#line 263 "C:/MCC18/v3.35/h/p18cxxx.h"
#line 265 "C:/MCC18/v3.35/h/p18cxxx.h"
#line 267 "C:/MCC18/v3.35/h/p18cxxx.h"
#line 269 "C:/MCC18/v3.35/h/p18cxxx.h"
#line 271 "C:/MCC18/v3.35/h/p18cxxx.h"
#line 273 "C:/MCC18/v3.35/h/p18cxxx.h"
#line 275 "C:/MCC18/v3.35/h/p18cxxx.h"
#line 277 "C:/MCC18/v3.35/h/p18cxxx.h"
#line 279 "C:/MCC18/v3.35/h/p18cxxx.h"
#line 281 "C:/MCC18/v3.35/h/p18cxxx.h"
#line 283 "C:/MCC18/v3.35/h/p18cxxx.h"
#line 285 "C:/MCC18/v3.35/h/p18cxxx.h"
#line 287 "C:/MCC18/v3.35/h/p18cxxx.h"
#line 289 "C:/MCC18/v3.35/h/p18cxxx.h"
#line 291 "C:/MCC18/v3.35/h/p18cxxx.h"
#line 293 "C:/MCC18/v3.35/h/p18cxxx.h"
#line 295 "C:/MCC18/v3.35/h/p18cxxx.h"
#line 297 "C:/MCC18/v3.35/h/p18cxxx.h"
#line 299 "C:/MCC18/v3.35/h/p18cxxx.h"
#line 301 "C:/MCC18/v3.35/h/p18cxxx.h"
#line 303 "C:/MCC18/v3.35/h/p18cxxx.h"
#line 305 "C:/MCC18/v3.35/h/p18cxxx.h"
#line 307 "C:/MCC18/v3.35/h/p18cxxx.h"
#line 309 "C:/MCC18/v3.35/h/p18cxxx.h"
#line 311 "C:/MCC18/v3.35/h/p18cxxx.h"
#line 313 "C:/MCC18/v3.35/h/p18cxxx.h"
#line 315 "C:/MCC18/v3.35/h/p18cxxx.h"
#line 317 "C:/MCC18/v3.35/h/p18cxxx.h"
#line 319 "C:/MCC18/v3.35/h/p18cxxx.h"
#line 321 "C:/MCC18/v3.35/h/p18cxxx.h"
#line 323 "C:/MCC18/v3.35/h/p18cxxx.h"
#line 325 "C:/MCC18/v3.35/h/p18cxxx.h"
#line 327 "C:/MCC18/v3.35/h/p18cxxx.h"
#line 329 "C:/MCC18/v3.35/h/p18cxxx.h"
#line 331 "C:/MCC18/v3.35/h/p18cxxx.h"
#line 333 "C:/MCC18/v3.35/h/p18cxxx.h"
#line 335 "C:/MCC18/v3.35/h/p18cxxx.h"
#line 337 "C:/MCC18/v3.35/h/p18cxxx.h"
#line 339 "C:/MCC18/v3.35/h/p18cxxx.h"
#line 341 "C:/MCC18/v3.35/h/p18cxxx.h"
#line 343 "C:/MCC18/v3.35/h/p18cxxx.h"
#line 345 "C:/MCC18/v3.35/h/p18cxxx.h"
#line 347 "C:/MCC18/v3.35/h/p18cxxx.h"
#line 349 "C:/MCC18/v3.35/h/p18cxxx.h"
#line 351 "C:/MCC18/v3.35/h/p18cxxx.h"
#line 353 "C:/MCC18/v3.35/h/p18cxxx.h"
#line 355 "C:/MCC18/v3.35/h/p18cxxx.h"
#line 357 "C:/MCC18/v3.35/h/p18cxxx.h"
#line 359 "C:/MCC18/v3.35/h/p18cxxx.h"
#line 361 "C:/MCC18/v3.35/h/p18cxxx.h"
#line 363 "C:/MCC18/v3.35/h/p18cxxx.h"
#line 365 "C:/MCC18/v3.35/h/p18cxxx.h"
#line 367 "C:/MCC18/v3.35/h/p18cxxx.h"
#line 369 "C:/MCC18/v3.35/h/p18cxxx.h"
#line 371 "C:/MCC18/v3.35/h/p18cxxx.h"
#line 373 "C:/MCC18/v3.35/h/p18cxxx.h"
#line 375 "C:/MCC18/v3.35/h/p18cxxx.h"
#line 377 "C:/MCC18/v3.35/h/p18cxxx.h"
#line 379 "C:/MCC18/v3.35/h/p18cxxx.h"
#line 381 "C:/MCC18/v3.35/h/p18cxxx.h"
#line 383 "C:/MCC18/v3.35/h/p18cxxx.h"
#line 385 "C:/MCC18/v3.35/h/p18cxxx.h"
#line 387 "C:/MCC18/v3.35/h/p18cxxx.h"
#line 389 "C:/MCC18/v3.35/h/p18cxxx.h"
#line 391 "C:/MCC18/v3.35/h/p18cxxx.h"
#line 393 "C:/MCC18/v3.35/h/p18cxxx.h"
#line 395 "C:/MCC18/v3.35/h/p18cxxx.h"
#line 397 "C:/MCC18/v3.35/h/p18cxxx.h"
#line 399 "C:/MCC18/v3.35/h/p18cxxx.h"
#line 401 "C:/MCC18/v3.35/h/p18cxxx.h"
#line 403 "C:/MCC18/v3.35/h/p18cxxx.h"
#line 405 "C:/MCC18/v3.35/h/p18cxxx.h"
#line 407 "C:/MCC18/v3.35/h/p18cxxx.h"
#line 409 "C:/MCC18/v3.35/h/p18cxxx.h"
#line 411 "C:/MCC18/v3.35/h/p18cxxx.h"
#line 413 "C:/MCC18/v3.35/h/p18cxxx.h"
#line 415 "C:/MCC18/v3.35/h/p18cxxx.h"
#line 417 "C:/MCC18/v3.35/h/p18cxxx.h"
#line 419 "C:/MCC18/v3.35/h/p18cxxx.h"
#line 421 "C:/MCC18/v3.35/h/p18cxxx.h"
#line 423 "C:/MCC18/v3.35/h/p18cxxx.h"
#line 425 "C:/MCC18/v3.35/h/p18cxxx.h"
#line 427 "C:/MCC18/v3.35/h/p18cxxx.h"
#line 429 "C:/MCC18/v3.35/h/p18cxxx.h"
#line 431 "C:/MCC18/v3.35/h/p18cxxx.h"
#line 433 "C:/MCC18/v3.35/h/p18cxxx.h"
#line 435 "C:/MCC18/v3.35/h/p18cxxx.h"
#line 437 "C:/MCC18/v3.35/h/p18cxxx.h"
#line 439 "C:/MCC18/v3.35/h/p18cxxx.h"
#line 441 "C:/MCC18/v3.35/h/p18cxxx.h"
#line 443 "C:/MCC18/v3.35/h/p18cxxx.h"
#line 445 "C:/MCC18/v3.35/h/p18cxxx.h"
#line 447 "C:/MCC18/v3.35/h/p18cxxx.h"
#line 449 "C:/MCC18/v3.35/h/p18cxxx.h"
#line 451 "C:/MCC18/v3.35/h/p18cxxx.h"
#line 453 "C:/MCC18/v3.35/h/p18cxxx.h"
#line 455 "C:/MCC18/v3.35/h/p18cxxx.h"
#line 457 "C:/MCC18/v3.35/h/p18cxxx.h"
#line 459 "C:/MCC18/v3.35/h/p18cxxx.h"
#line 461 "C:/MCC18/v3.35/h/p18cxxx.h"
#line 463 "C:/MCC18/v3.35/h/p18cxxx.h"
#line 465 "C:/MCC18/v3.35/h/p18cxxx.h"
#line 467 "C:/MCC18/v3.35/h/p18cxxx.h"
#line 469 "C:/MCC18/v3.35/h/p18cxxx.h"
#line 471 "C:/MCC18/v3.35/h/p18cxxx.h"
#line 473 "C:/MCC18/v3.35/h/p18cxxx.h"
#line 475 "C:/MCC18/v3.35/h/p18cxxx.h"
#line 477 "C:/MCC18/v3.35/h/p18cxxx.h"
#line 479 "C:/MCC18/v3.35/h/p18cxxx.h"
#line 481 "C:/MCC18/v3.35/h/p18cxxx.h"
#line 483 "C:/MCC18/v3.35/h/p18cxxx.h"
#line 485 "C:/MCC18/v3.35/h/p18cxxx.h"
#line 487 "C:/MCC18/v3.35/h/p18cxxx.h"
#line 489 "C:/MCC18/v3.35/h/p18cxxx.h"
#line 491 "C:/MCC18/v3.35/h/p18cxxx.h"
#line 493 "C:/MCC18/v3.35/h/p18cxxx.h"
#line 495 "C:/MCC18/v3.35/h/p18cxxx.h"
#line 497 "C:/MCC18/v3.35/h/p18cxxx.h"
#line 499 "C:/MCC18/v3.35/h/p18cxxx.h"
#line 501 "C:/MCC18/v3.35/h/p18cxxx.h"
#line 503 "C:/MCC18/v3.35/h/p18cxxx.h"
#line 505 "C:/MCC18/v3.35/h/p18cxxx.h"
#line 507 "C:/MCC18/v3.35/h/p18cxxx.h"
#line 509 "C:/MCC18/v3.35/h/p18cxxx.h"
#line 511 "C:/MCC18/v3.35/h/p18cxxx.h"
#line 513 "C:/MCC18/v3.35/h/p18cxxx.h"
#line 515 "C:/MCC18/v3.35/h/p18cxxx.h"
#line 517 "C:/MCC18/v3.35/h/p18cxxx.h"
#line 519 "C:/MCC18/v3.35/h/p18cxxx.h"
#line 521 "C:/MCC18/v3.35/h/p18cxxx.h"
#line 523 "C:/MCC18/v3.35/h/p18cxxx.h"
#line 525 "C:/MCC18/v3.35/h/p18cxxx.h"
#line 527 "C:/MCC18/v3.35/h/p18cxxx.h"
#line 529 "C:/MCC18/v3.35/h/p18cxxx.h"
#line 531 "C:/MCC18/v3.35/h/p18cxxx.h"
#line 533 "C:/MCC18/v3.35/h/p18cxxx.h"
#line 535 "C:/MCC18/v3.35/h/p18cxxx.h"
#line 537 "C:/MCC18/v3.35/h/p18cxxx.h"
#line 539 "C:/MCC18/v3.35/h/p18cxxx.h"

#line 541 "C:/MCC18/v3.35/h/p18cxxx.h"
#line 62 "C:/PIC/Microchip Solutions/Microchip/Include/Compiler.h"

#line 64 "C:/PIC/Microchip Solutions/Microchip/Include/Compiler.h"
#line 65 "C:/PIC/Microchip Solutions/Microchip/Include/Compiler.h"
#line 68 "C:/PIC/Microchip Solutions/Microchip/Include/Compiler.h"
#line 71 "C:/PIC/Microchip Solutions/Microchip/Include/Compiler.h"
#line 74 "C:/PIC/Microchip Solutions/Microchip/Include/Compiler.h"
#line 77 "C:/PIC/Microchip Solutions/Microchip/Include/Compiler.h"
#line 78 "C:/PIC/Microchip Solutions/Microchip/Include/Compiler.h"
#line 80 "C:/PIC/Microchip Solutions/Microchip/Include/Compiler.h"
#line 83 "C:/PIC/Microchip Solutions/Microchip/Include/Compiler.h"
#line 85 "C:/PIC/Microchip Solutions/Microchip/Include/Compiler.h"

#line 1 "C:/MCC18/v3.35/h/stdio.h"

#line 3 "C:/MCC18/v3.35/h/stdio.h"

#line 1 "C:/MCC18/v3.35/h/stdarg.h"
 


#line 5 "C:/MCC18/v3.35/h/stdarg.h"

typedef void* va_list;
#line 8 "C:/MCC18/v3.35/h/stdarg.h"
#line 9 "C:/MCC18/v3.35/h/stdarg.h"
#line 10 "C:/MCC18/v3.35/h/stdarg.h"
#line 11 "C:/MCC18/v3.35/h/stdarg.h"
#line 12 "C:/MCC18/v3.35/h/stdarg.h"
#line 4 "C:/MCC18/v3.35/h/stdio.h"

#line 1 "C:/MCC18/v3.35/h/stddef.h"
 

#line 10 "C:/MCC18/v3.35/h/stddef.h"

#line 20 "C:/MCC18/v3.35/h/stddef.h"

#line 34 "C:/MCC18/v3.35/h/stddef.h"

#line 41 "C:/MCC18/v3.35/h/stddef.h"
#line 45 "C:/MCC18/v3.35/h/stddef.h"
#line 5 "C:/MCC18/v3.35/h/stdio.h"



#line 9 "C:/MCC18/v3.35/h/stdio.h"
 
#line 11 "C:/MCC18/v3.35/h/stdio.h"

#line 13 "C:/MCC18/v3.35/h/stdio.h"


typedef unsigned char FILE;

 
#line 19 "C:/MCC18/v3.35/h/stdio.h"
#line 20 "C:/MCC18/v3.35/h/stdio.h"

extern FILE *stderr;
extern FILE *stdout;


int putc (auto char c, auto FILE *f);
int vsprintf (auto char *buf, auto const far  rom char *fmt, auto va_list ap);
int vprintf (auto const far  rom char *fmt, auto va_list ap);
int sprintf (auto char *buf, auto const far  rom char *fmt, ...);
int printf (auto const far  rom char *fmt, ...);
int fprintf (auto FILE *f, auto const far  rom char *fmt, ...);
int vfprintf (auto FILE *f, auto const far  rom char *fmt, auto va_list ap);
int puts (auto const far  rom char *s);
int fputs (auto const far  rom char *s, auto FILE *f);

#line 36 "C:/MCC18/v3.35/h/stdio.h"
#line 86 "C:/PIC/Microchip Solutions/Microchip/Include/Compiler.h"

#line 1 "C:/MCC18/v3.35/h/stdlib.h"
 

#line 4 "C:/MCC18/v3.35/h/stdlib.h"

#line 6 "C:/MCC18/v3.35/h/stdlib.h"

#line 9 "C:/MCC18/v3.35/h/stdlib.h"
 
 

#line 16 "C:/MCC18/v3.35/h/stdlib.h"
 
double atof (const auto char *s);

#line 28 "C:/MCC18/v3.35/h/stdlib.h"
 
signed char atob (const auto char *s);


#line 39 "C:/MCC18/v3.35/h/stdlib.h"
 
int atoi (const auto char *s);

#line 47 "C:/MCC18/v3.35/h/stdlib.h"
 
long atol (const auto char *s);

#line 58 "C:/MCC18/v3.35/h/stdlib.h"
 
unsigned long atoul (const auto char *s);


#line 71 "C:/MCC18/v3.35/h/stdlib.h"
 
char *btoa (auto signed char value, auto char *s);

#line 83 "C:/MCC18/v3.35/h/stdlib.h"
 
char *itoa (auto int value, auto char *s);

#line 95 "C:/MCC18/v3.35/h/stdlib.h"
 
char *ltoa (auto long value, auto char *s);

#line 107 "C:/MCC18/v3.35/h/stdlib.h"
 
char *ultoa (auto unsigned long value, auto char *s);
 


#line 112 "C:/MCC18/v3.35/h/stdlib.h"
 
 

#line 116 "C:/MCC18/v3.35/h/stdlib.h"
 
#line 118 "C:/MCC18/v3.35/h/stdlib.h"


#line 124 "C:/MCC18/v3.35/h/stdlib.h"
 
int rand (void);

#line 136 "C:/MCC18/v3.35/h/stdlib.h"
 
void srand (auto unsigned int seed);
 
#line 140 "C:/MCC18/v3.35/h/stdlib.h"
#line 149 "C:/MCC18/v3.35/h/stdlib.h"

#line 151 "C:/MCC18/v3.35/h/stdlib.h"
#line 87 "C:/PIC/Microchip Solutions/Microchip/Include/Compiler.h"

#line 1 "C:/MCC18/v3.35/h/string.h"

#line 3 "C:/MCC18/v3.35/h/string.h"

#line 7 "C:/MCC18/v3.35/h/string.h"


#line 20 "C:/MCC18/v3.35/h/string.h"
 
#line 22 "C:/MCC18/v3.35/h/string.h"


#line 25 "C:/MCC18/v3.35/h/string.h"
 
#line 27 "C:/MCC18/v3.35/h/string.h"

 

#line 39 "C:/MCC18/v3.35/h/string.h"
 
void *memcpy (auto void *s1, auto const void *s2, auto size_t n);


#line 55 "C:/MCC18/v3.35/h/string.h"
 
void *memmove (auto void *s1, auto const void *s2, auto size_t n);


#line 67 "C:/MCC18/v3.35/h/string.h"
 
char *strcpy (auto char *s1, auto const char *s2);


#line 83 "C:/MCC18/v3.35/h/string.h"
 
char *strncpy (auto char *s1, auto const char *s2, auto size_t n);


#line 97 "C:/MCC18/v3.35/h/string.h"
 
char *strcat (auto char *s1, auto const char *s2);


#line 113 "C:/MCC18/v3.35/h/string.h"
 
char *strncat (auto char *s1, auto const char *s2, auto size_t n);


#line 128 "C:/MCC18/v3.35/h/string.h"
 
signed char memcmp (auto const void *s1, auto const void *s2, auto size_t n);


#line 141 "C:/MCC18/v3.35/h/string.h"
 
signed char strcmp (auto const char *s1, auto const char *s2);


#line 147 "C:/MCC18/v3.35/h/string.h"
 


#line 161 "C:/MCC18/v3.35/h/string.h"
 
signed char strncmp (auto const char *s1, auto const char *s2, auto size_t n);


#line 167 "C:/MCC18/v3.35/h/string.h"
 


#line 183 "C:/MCC18/v3.35/h/string.h"
 
void *memchr (auto const void *s, auto unsigned char c, auto size_t n);


#line 199 "C:/MCC18/v3.35/h/string.h"
 
char *strchr (auto const char *s, auto unsigned char c);


#line 210 "C:/MCC18/v3.35/h/string.h"
 
size_t strcspn (auto const char *s1, auto const char *s2);


#line 222 "C:/MCC18/v3.35/h/string.h"
 
char *strpbrk (auto const char *s1, auto const char *s2);


#line 238 "C:/MCC18/v3.35/h/string.h"
 
char *strrchr (auto const char *s, auto unsigned char c);


#line 249 "C:/MCC18/v3.35/h/string.h"
 
size_t strspn (auto const char *s1, auto const char *s2);


#line 262 "C:/MCC18/v3.35/h/string.h"
 
char *strstr (auto const char *s1, auto const char *s2);


#line 305 "C:/MCC18/v3.35/h/string.h"
 
char *strtok (auto char *s1, auto const char *s2);


#line 321 "C:/MCC18/v3.35/h/string.h"
 
void *memset (auto void *s, auto unsigned char c, auto size_t n);


#line 339 "C:/MCC18/v3.35/h/string.h"
 
#line 341 "C:/MCC18/v3.35/h/string.h"


#line 349 "C:/MCC18/v3.35/h/string.h"
 
size_t strlen (auto const char *s);


#line 358 "C:/MCC18/v3.35/h/string.h"
 
char *strupr (auto char *s);


#line 367 "C:/MCC18/v3.35/h/string.h"
 
char *strlwr (auto char *s);



 

#line 379 "C:/MCC18/v3.35/h/string.h"
 
far  rom void *memcpypgm (auto far  rom void *s1, auto const far  rom void *s2, auto sizerom_t n);


#line 389 "C:/MCC18/v3.35/h/string.h"
 
void *memcpypgm2ram (auto void *s1, auto const far  rom void *s2, auto sizeram_t n);


#line 398 "C:/MCC18/v3.35/h/string.h"
 
far  rom void *memcpyram2pgm (auto far  rom void *s1, auto const void *s2, auto sizeram_t n);


#line 407 "C:/MCC18/v3.35/h/string.h"
 
far  rom void *memmovepgm (auto far  rom void *s1, auto const far  rom void *s2, auto sizerom_t n);


#line 417 "C:/MCC18/v3.35/h/string.h"
 
void *memmovepgm2ram (auto void *s1, auto const far  rom void *s2, auto sizeram_t n);


#line 426 "C:/MCC18/v3.35/h/string.h"
 
far  rom void *memmoveram2pgm (auto far  rom void *s1, auto const void *s2, auto sizeram_t n);


#line 434 "C:/MCC18/v3.35/h/string.h"
 
far  rom char *strcpypgm (auto far  rom char *s1, auto const far  rom char *s2);


#line 443 "C:/MCC18/v3.35/h/string.h"
 
char *strcpypgm2ram (auto char *s1, auto const far  rom char *s2);


#line 451 "C:/MCC18/v3.35/h/string.h"
 
far  rom char *strcpyram2pgm (auto far  rom char *s1, auto const char *s2);


#line 460 "C:/MCC18/v3.35/h/string.h"
 
far  rom char *strncpypgm (auto far  rom char *s1, auto const far  rom char *s2, auto sizerom_t n);


#line 470 "C:/MCC18/v3.35/h/string.h"
 
char *strncpypgm2ram (auto char *s1, auto const far  rom char *s2, auto sizeram_t n);


#line 479 "C:/MCC18/v3.35/h/string.h"
 
far  rom char *strncpyram2pgm (auto far  rom char *s1, auto const char *s2, auto sizeram_t n);


#line 487 "C:/MCC18/v3.35/h/string.h"
 
far  rom char *strcatpgm (auto far  rom char *s1, auto const far  rom char *s2);


#line 496 "C:/MCC18/v3.35/h/string.h"
 
char *strcatpgm2ram (auto char *s1, auto const far  rom char *s2);


#line 504 "C:/MCC18/v3.35/h/string.h"
 
far  rom char *strcatram2pgm (auto far  rom char *s1, auto const char *s2);


#line 513 "C:/MCC18/v3.35/h/string.h"
 
far  rom char *strncatpgm (auto far  rom char *s1, auto const far  rom char *s2, auto sizerom_t n);


#line 523 "C:/MCC18/v3.35/h/string.h"
 
char *strncatpgm2ram (auto char *s1, auto const far  rom char *s2, auto sizeram_t n);


#line 532 "C:/MCC18/v3.35/h/string.h"
 
far  rom char *strncatram2pgm (auto far  rom char *s1, auto const char *s2, auto sizeram_t n);


#line 541 "C:/MCC18/v3.35/h/string.h"
 
signed char memcmppgm (auto far  rom void *s1, auto const far  rom void *s2, auto sizerom_t n);


#line 551 "C:/MCC18/v3.35/h/string.h"
 
signed char memcmppgm2ram (auto void *s1, auto const far  rom void *s2, auto sizeram_t n);


#line 560 "C:/MCC18/v3.35/h/string.h"
 
signed char memcmpram2pgm (auto far  rom void *s1, auto const void *s2, auto sizeram_t n);


#line 568 "C:/MCC18/v3.35/h/string.h"
 
signed char strcmppgm (auto const far  rom char *s1, auto const far  rom char *s2);


#line 577 "C:/MCC18/v3.35/h/string.h"
 
signed char strcmppgm2ram (auto const char *s1, auto const far  rom char *s2);


#line 585 "C:/MCC18/v3.35/h/string.h"
 
signed char strcmpram2pgm (auto const far  rom char *s1, auto const char *s2);


#line 594 "C:/MCC18/v3.35/h/string.h"
 
signed char strncmppgm (auto const far  rom char *s1, auto const far  rom char *s2, auto sizerom_t n);


#line 604 "C:/MCC18/v3.35/h/string.h"
 
signed char strncmppgm2ram (auto char *s1, auto const far  rom char *s2, auto sizeram_t n);


#line 613 "C:/MCC18/v3.35/h/string.h"
 
signed char strncmpram2pgm (auto far  rom char *s1, auto const char *s2, auto sizeram_t n);


#line 622 "C:/MCC18/v3.35/h/string.h"
 
far  rom char *memchrpgm (auto const far  rom char *s, auto const unsigned char c, auto sizerom_t n);


#line 631 "C:/MCC18/v3.35/h/string.h"
 
far  rom char *strchrpgm (auto const far  rom char *s, auto unsigned char c);


#line 639 "C:/MCC18/v3.35/h/string.h"
 
sizerom_t strcspnpgm (auto const far  rom char *s1, auto const far  rom char *s2);


#line 647 "C:/MCC18/v3.35/h/string.h"
 
sizerom_t strcspnpgmram (auto const far  rom char *s1, auto const char *s2);


#line 655 "C:/MCC18/v3.35/h/string.h"
 
sizeram_t strcspnrampgm (auto const char *s1, auto const far  rom char *s2);


#line 663 "C:/MCC18/v3.35/h/string.h"
 
far  rom char *strpbrkpgm (auto const far  rom char *s1, auto const far  rom char *s2);


#line 671 "C:/MCC18/v3.35/h/string.h"
 
far  rom char *strpbrkpgmram (auto const far  rom char *s1, auto const char *s2);


#line 679 "C:/MCC18/v3.35/h/string.h"
 
char *strpbrkrampgm (auto const char *s1, auto const far  rom char *s2);


#line 688 "C:/MCC18/v3.35/h/string.h"
 
 


#line 696 "C:/MCC18/v3.35/h/string.h"
 
sizerom_t strspnpgm (auto const far  rom char *s1, auto const far  rom char *s2);


#line 704 "C:/MCC18/v3.35/h/string.h"
 
sizerom_t strspnpgmram (auto const far  rom char *s1, auto const char *s2);


#line 712 "C:/MCC18/v3.35/h/string.h"
 
sizeram_t strspnrampgm (auto const char *s1, auto const far  rom char *s2);


#line 720 "C:/MCC18/v3.35/h/string.h"
 
far  rom char *strstrpgm (auto const far  rom char *s1, auto const far  rom char *s2);


#line 729 "C:/MCC18/v3.35/h/string.h"
 
far  rom char *strstrpgmram (auto const far  rom char *s1, auto const char *s2);


#line 737 "C:/MCC18/v3.35/h/string.h"
 
char *strstrrampgm (auto const char *s1, auto const far  rom char *s2);


#line 745 "C:/MCC18/v3.35/h/string.h"
 
far  rom char *strtokpgm (auto far  rom char *s1, auto const far  rom char *s2);


#line 754 "C:/MCC18/v3.35/h/string.h"
 
char *strtokpgmram (auto char *s1, auto const far  rom char *s2);


#line 762 "C:/MCC18/v3.35/h/string.h"
 
far  rom char *strtokrampgm (auto far  rom char *s1, auto const char *s2);


#line 771 "C:/MCC18/v3.35/h/string.h"
 
far  rom void *memsetpgm (auto far  rom void *s, auto unsigned char c, auto sizerom_t n);


#line 778 "C:/MCC18/v3.35/h/string.h"
 
far  rom char *struprpgm (auto far  rom char *s);


#line 785 "C:/MCC18/v3.35/h/string.h"
 
far  rom char *strlwrpgm (auto far  rom char *s);


#line 792 "C:/MCC18/v3.35/h/string.h"
 
sizerom_t strlenpgm (auto const far  rom char *s);

#line 796 "C:/MCC18/v3.35/h/string.h"

#line 798 "C:/MCC18/v3.35/h/string.h"

#line 805 "C:/MCC18/v3.35/h/string.h"
#line 814 "C:/MCC18/v3.35/h/string.h"

#line 816 "C:/MCC18/v3.35/h/string.h"
#line 88 "C:/PIC/Microchip Solutions/Microchip/Include/Compiler.h"




#line 93 "C:/PIC/Microchip Solutions/Microchip/Include/Compiler.h"
#line 96 "C:/PIC/Microchip Solutions/Microchip/Include/Compiler.h"
#line 99 "C:/PIC/Microchip Solutions/Microchip/Include/Compiler.h"
#line 100 "C:/PIC/Microchip Solutions/Microchip/Include/Compiler.h"
#line 101 "C:/PIC/Microchip Solutions/Microchip/Include/Compiler.h"
#line 102 "C:/PIC/Microchip Solutions/Microchip/Include/Compiler.h"



#line 106 "C:/PIC/Microchip Solutions/Microchip/Include/Compiler.h"
#line 116 "C:/PIC/Microchip Solutions/Microchip/Include/Compiler.h"




#line 121 "C:/PIC/Microchip Solutions/Microchip/Include/Compiler.h"
#line 122 "C:/PIC/Microchip Solutions/Microchip/Include/Compiler.h"

#line 124 "C:/PIC/Microchip Solutions/Microchip/Include/Compiler.h"

	
#line 127 "C:/PIC/Microchip Solutions/Microchip/Include/Compiler.h"
#line 128 "C:/PIC/Microchip Solutions/Microchip/Include/Compiler.h"
#line 129 "C:/PIC/Microchip Solutions/Microchip/Include/Compiler.h"
#line 130 "C:/PIC/Microchip Solutions/Microchip/Include/Compiler.h"
	
	
#line 133 "C:/PIC/Microchip Solutions/Microchip/Include/Compiler.h"
#line 139 "C:/PIC/Microchip Solutions/Microchip/Include/Compiler.h"
    


#line 143 "C:/PIC/Microchip Solutions/Microchip/Include/Compiler.h"
#line 147 "C:/PIC/Microchip Solutions/Microchip/Include/Compiler.h"
#line 150 "C:/PIC/Microchip Solutions/Microchip/Include/Compiler.h"
#line 153 "C:/PIC/Microchip Solutions/Microchip/Include/Compiler.h"
#line 160 "C:/PIC/Microchip Solutions/Microchip/Include/Compiler.h"
#line 161 "C:/PIC/Microchip Solutions/Microchip/Include/Compiler.h"



#line 165 "C:/PIC/Microchip Solutions/Microchip/Include/Compiler.h"
#line 38 "usb_device.c"

#line 1 "C:/PIC/Microchip Solutions/Microchip/Include/./USB/usb_ch9.h"

#line 10 "C:/PIC/Microchip Solutions/Microchip/Include/./USB/usb_ch9.h"
 


#line 43 "C:/PIC/Microchip Solutions/Microchip/Include/./USB/usb_ch9.h"
 




#line 49 "C:/PIC/Microchip Solutions/Microchip/Include/./USB/usb_ch9.h"









#line 59 "C:/PIC/Microchip Solutions/Microchip/Include/./USB/usb_ch9.h"
#line 60 "C:/PIC/Microchip Solutions/Microchip/Include/./USB/usb_ch9.h"
#line 61 "C:/PIC/Microchip Solutions/Microchip/Include/./USB/usb_ch9.h"
#line 62 "C:/PIC/Microchip Solutions/Microchip/Include/./USB/usb_ch9.h"
#line 63 "C:/PIC/Microchip Solutions/Microchip/Include/./USB/usb_ch9.h"
#line 64 "C:/PIC/Microchip Solutions/Microchip/Include/./USB/usb_ch9.h"
#line 65 "C:/PIC/Microchip Solutions/Microchip/Include/./USB/usb_ch9.h"
#line 66 "C:/PIC/Microchip Solutions/Microchip/Include/./USB/usb_ch9.h"
#line 67 "C:/PIC/Microchip Solutions/Microchip/Include/./USB/usb_ch9.h"



#line 74 "C:/PIC/Microchip Solutions/Microchip/Include/./USB/usb_ch9.h"
 
typedef struct   _USB_DEVICE_DESCRIPTOR
{
    BYTE bLength;               
    BYTE bDescriptorType;       
    WORD bcdUSB;                
    BYTE bDeviceClass;          
    BYTE bDeviceSubClass;       
    BYTE bDeviceProtocol;       
    BYTE bMaxPacketSize0;       
    WORD idVendor;              
    WORD idProduct;             
    WORD bcdDevice;             
    BYTE iManufacturer;         
    BYTE iProduct;              
    BYTE iSerialNumber;         
    BYTE bNumConfigurations;    
} USB_DEVICE_DESCRIPTOR;




#line 100 "C:/PIC/Microchip Solutions/Microchip/Include/./USB/usb_ch9.h"
 
typedef struct   _USB_CONFIGURATION_DESCRIPTOR
{
    BYTE bLength;               
    BYTE bDescriptorType;       
    WORD wTotalLength;          
    BYTE bNumInterfaces;        
    BYTE bConfigurationValue;   
    BYTE iConfiguration;        
    BYTE bmAttributes;          
    BYTE bMaxPower;             
} USB_CONFIGURATION_DESCRIPTOR;


#line 115 "C:/PIC/Microchip Solutions/Microchip/Include/./USB/usb_ch9.h"
#line 116 "C:/PIC/Microchip Solutions/Microchip/Include/./USB/usb_ch9.h"
#line 117 "C:/PIC/Microchip Solutions/Microchip/Include/./USB/usb_ch9.h"




#line 125 "C:/PIC/Microchip Solutions/Microchip/Include/./USB/usb_ch9.h"
 
typedef struct   _USB_INTERFACE_DESCRIPTOR
{
    BYTE bLength;               
    BYTE bDescriptorType;       
    BYTE bInterfaceNumber;      
    BYTE bAlternateSetting;     
    BYTE bNumEndpoints;         
    BYTE bInterfaceClass;       
    BYTE bInterfaceSubClass;    
    BYTE bInterfaceProtocol;    
    BYTE iInterface;            
} USB_INTERFACE_DESCRIPTOR;




#line 146 "C:/PIC/Microchip Solutions/Microchip/Include/./USB/usb_ch9.h"
 
typedef struct   _USB_ENDPOINT_DESCRIPTOR
{
    BYTE bLength;               
    BYTE bDescriptorType;       
    BYTE bEndpointAddress;      
    BYTE bmAttributes;          
    WORD wMaxPacketSize;        
    BYTE bInterval;             
} USB_ENDPOINT_DESCRIPTOR;



#line 160 "C:/PIC/Microchip Solutions/Microchip/Include/./USB/usb_ch9.h"
#line 161 "C:/PIC/Microchip Solutions/Microchip/Include/./USB/usb_ch9.h"







#line 169 "C:/PIC/Microchip Solutions/Microchip/Include/./USB/usb_ch9.h"
#line 170 "C:/PIC/Microchip Solutions/Microchip/Include/./USB/usb_ch9.h"
#line 171 "C:/PIC/Microchip Solutions/Microchip/Include/./USB/usb_ch9.h"
#line 172 "C:/PIC/Microchip Solutions/Microchip/Include/./USB/usb_ch9.h"


#line 175 "C:/PIC/Microchip Solutions/Microchip/Include/./USB/usb_ch9.h"
#line 176 "C:/PIC/Microchip Solutions/Microchip/Include/./USB/usb_ch9.h"
#line 177 "C:/PIC/Microchip Solutions/Microchip/Include/./USB/usb_ch9.h"
#line 178 "C:/PIC/Microchip Solutions/Microchip/Include/./USB/usb_ch9.h"


#line 181 "C:/PIC/Microchip Solutions/Microchip/Include/./USB/usb_ch9.h"
#line 182 "C:/PIC/Microchip Solutions/Microchip/Include/./USB/usb_ch9.h"
#line 183 "C:/PIC/Microchip Solutions/Microchip/Include/./USB/usb_ch9.h"


#line 186 "C:/PIC/Microchip Solutions/Microchip/Include/./USB/usb_ch9.h"
#line 187 "C:/PIC/Microchip Solutions/Microchip/Include/./USB/usb_ch9.h"
#line 188 "C:/PIC/Microchip Solutions/Microchip/Include/./USB/usb_ch9.h"
#line 189 "C:/PIC/Microchip Solutions/Microchip/Include/./USB/usb_ch9.h"
#line 190 "C:/PIC/Microchip Solutions/Microchip/Include/./USB/usb_ch9.h"
#line 191 "C:/PIC/Microchip Solutions/Microchip/Include/./USB/usb_ch9.h"
#line 192 "C:/PIC/Microchip Solutions/Microchip/Include/./USB/usb_ch9.h"




#line 200 "C:/PIC/Microchip Solutions/Microchip/Include/./USB/usb_ch9.h"
 
typedef struct   _USB_OTG_DESCRIPTOR
{
    BYTE bLength;               
    BYTE bDescriptorType;       
    BYTE bmAttributes;          
} USB_OTG_DESCRIPTOR;


















typedef struct   _USB_STRING_DSC
{
    BYTE   bLength;             
    BYTE   bDescriptorType;     

} USB_STRING_DESCRIPTOR;













typedef struct   _USB_DEVICE_QUALIFIER_DESCRIPTOR
{
    BYTE bLength;               
    BYTE bType;                 
    WORD bcdUSB;                
    BYTE bDeviceClass;          
    BYTE bDeviceSubClass;       
    BYTE bDeviceProtocol;       
    BYTE bMaxPacketSize0;       
    BYTE bNumConfigurations;    
    BYTE bReserved;             

} USB_DEVICE_QUALIFIER_DESCRIPTOR;












typedef struct   SetupPkt
{
    union                           
    {                               
        BYTE bmRequestType;         
        struct
        {
            BYTE    recipient:  5;  
            BYTE    type:       2;  
            BYTE    direction:  1;  
        };
    }requestInfo;

    BYTE    bRequest;               
    UINT16  wValue;                 
    UINT16  wIndex;                 
    UINT16  wLength;                

} SETUP_PKT, *PSETUP_PKT;










#line 299 "C:/PIC/Microchip Solutions/Microchip/Include/./USB/usb_ch9.h"
#line 300 "C:/PIC/Microchip Solutions/Microchip/Include/./USB/usb_ch9.h"
#line 301 "C:/PIC/Microchip Solutions/Microchip/Include/./USB/usb_ch9.h"
#line 302 "C:/PIC/Microchip Solutions/Microchip/Include/./USB/usb_ch9.h"
#line 303 "C:/PIC/Microchip Solutions/Microchip/Include/./USB/usb_ch9.h"
#line 304 "C:/PIC/Microchip Solutions/Microchip/Include/./USB/usb_ch9.h"
#line 305 "C:/PIC/Microchip Solutions/Microchip/Include/./USB/usb_ch9.h"
#line 306 "C:/PIC/Microchip Solutions/Microchip/Include/./USB/usb_ch9.h"
#line 307 "C:/PIC/Microchip Solutions/Microchip/Include/./USB/usb_ch9.h"
#line 308 "C:/PIC/Microchip Solutions/Microchip/Include/./USB/usb_ch9.h"
#line 309 "C:/PIC/Microchip Solutions/Microchip/Include/./USB/usb_ch9.h"
#line 310 "C:/PIC/Microchip Solutions/Microchip/Include/./USB/usb_ch9.h"
#line 311 "C:/PIC/Microchip Solutions/Microchip/Include/./USB/usb_ch9.h"
#line 312 "C:/PIC/Microchip Solutions/Microchip/Include/./USB/usb_ch9.h"
#line 313 "C:/PIC/Microchip Solutions/Microchip/Include/./USB/usb_ch9.h"
#line 314 "C:/PIC/Microchip Solutions/Microchip/Include/./USB/usb_ch9.h"

#line 316 "C:/PIC/Microchip Solutions/Microchip/Include/./USB/usb_ch9.h"
#line 317 "C:/PIC/Microchip Solutions/Microchip/Include/./USB/usb_ch9.h"




#line 322 "C:/PIC/Microchip Solutions/Microchip/Include/./USB/usb_ch9.h"
#line 323 "C:/PIC/Microchip Solutions/Microchip/Include/./USB/usb_ch9.h"
#line 324 "C:/PIC/Microchip Solutions/Microchip/Include/./USB/usb_ch9.h"




#line 329 "C:/PIC/Microchip Solutions/Microchip/Include/./USB/usb_ch9.h"
#line 330 "C:/PIC/Microchip Solutions/Microchip/Include/./USB/usb_ch9.h"



#line 334 "C:/PIC/Microchip Solutions/Microchip/Include/./USB/usb_ch9.h"
#line 335 "C:/PIC/Microchip Solutions/Microchip/Include/./USB/usb_ch9.h"



#line 339 "C:/PIC/Microchip Solutions/Microchip/Include/./USB/usb_ch9.h"
#line 340 "C:/PIC/Microchip Solutions/Microchip/Include/./USB/usb_ch9.h"
#line 341 "C:/PIC/Microchip Solutions/Microchip/Include/./USB/usb_ch9.h"
#line 342 "C:/PIC/Microchip Solutions/Microchip/Include/./USB/usb_ch9.h"
#line 343 "C:/PIC/Microchip Solutions/Microchip/Include/./USB/usb_ch9.h"
#line 344 "C:/PIC/Microchip Solutions/Microchip/Include/./USB/usb_ch9.h"
#line 345 "C:/PIC/Microchip Solutions/Microchip/Include/./USB/usb_ch9.h"
#line 346 "C:/PIC/Microchip Solutions/Microchip/Include/./USB/usb_ch9.h"
#line 347 "C:/PIC/Microchip Solutions/Microchip/Include/./USB/usb_ch9.h"
#line 348 "C:/PIC/Microchip Solutions/Microchip/Include/./USB/usb_ch9.h"
#line 349 "C:/PIC/Microchip Solutions/Microchip/Include/./USB/usb_ch9.h"

#line 351 "C:/PIC/Microchip Solutions/Microchip/Include/./USB/usb_ch9.h"
#line 352 "C:/PIC/Microchip Solutions/Microchip/Include/./USB/usb_ch9.h"
#line 353 "C:/PIC/Microchip Solutions/Microchip/Include/./USB/usb_ch9.h"



#line 357 "C:/PIC/Microchip Solutions/Microchip/Include/./USB/usb_ch9.h"
#line 358 "C:/PIC/Microchip Solutions/Microchip/Include/./USB/usb_ch9.h"
#line 359 "C:/PIC/Microchip Solutions/Microchip/Include/./USB/usb_ch9.h"
#line 360 "C:/PIC/Microchip Solutions/Microchip/Include/./USB/usb_ch9.h"
#line 361 "C:/PIC/Microchip Solutions/Microchip/Include/./USB/usb_ch9.h"
#line 362 "C:/PIC/Microchip Solutions/Microchip/Include/./USB/usb_ch9.h"
#line 363 "C:/PIC/Microchip Solutions/Microchip/Include/./USB/usb_ch9.h"
#line 364 "C:/PIC/Microchip Solutions/Microchip/Include/./USB/usb_ch9.h"
#line 365 "C:/PIC/Microchip Solutions/Microchip/Include/./USB/usb_ch9.h"



#line 369 "C:/PIC/Microchip Solutions/Microchip/Include/./USB/usb_ch9.h"
#line 370 "C:/PIC/Microchip Solutions/Microchip/Include/./USB/usb_ch9.h"
#line 371 "C:/PIC/Microchip Solutions/Microchip/Include/./USB/usb_ch9.h"



#line 375 "C:/PIC/Microchip Solutions/Microchip/Include/./USB/usb_ch9.h"
#line 376 "C:/PIC/Microchip Solutions/Microchip/Include/./USB/usb_ch9.h"
#line 377 "C:/PIC/Microchip Solutions/Microchip/Include/./USB/usb_ch9.h"
#line 378 "C:/PIC/Microchip Solutions/Microchip/Include/./USB/usb_ch9.h"


#line 381 "C:/PIC/Microchip Solutions/Microchip/Include/./USB/usb_ch9.h"
#line 382 "C:/PIC/Microchip Solutions/Microchip/Include/./USB/usb_ch9.h"
#line 383 "C:/PIC/Microchip Solutions/Microchip/Include/./USB/usb_ch9.h"



#line 387 "C:/PIC/Microchip Solutions/Microchip/Include/./USB/usb_ch9.h"


#line 390 "C:/PIC/Microchip Solutions/Microchip/Include/./USB/usb_ch9.h"

#line 392 "C:/PIC/Microchip Solutions/Microchip/Include/./USB/usb_ch9.h"
 

#line 39 "usb_device.c"

#line 1 "C:/PIC/Microchip Solutions/Microchip/Include/./USB/USB.h"

#line 14 "C:/PIC/Microchip Solutions/Microchip/Include/./USB/USB.h"
 


#line 49 "C:/PIC/Microchip Solutions/Microchip/Include/./USB/USB.h"
 




#line 55 "C:/PIC/Microchip Solutions/Microchip/Include/./USB/USB.h"









             

#line 1 "C:/PIC/Microchip Solutions/Microchip/Include/usb/usb_common.h"

#line 9 "C:/PIC/Microchip Solutions/Microchip/Include/usb/usb_common.h"
 


#line 45 "C:/PIC/Microchip Solutions/Microchip/Include/usb/usb_common.h"
 





#line 52 "C:/PIC/Microchip Solutions/Microchip/Include/usb/usb_common.h"


#line 1 "C:/MCC18/v3.35/h/limits.h"

#line 9 "C:/MCC18/v3.35/h/limits.h"
 


#line 13 "C:/MCC18/v3.35/h/limits.h"

#line 15 "C:/MCC18/v3.35/h/limits.h"
#line 16 "C:/MCC18/v3.35/h/limits.h"

#line 18 "C:/MCC18/v3.35/h/limits.h"
#line 19 "C:/MCC18/v3.35/h/limits.h"
#line 20 "C:/MCC18/v3.35/h/limits.h"

 
#line 23 "C:/MCC18/v3.35/h/limits.h"
#line 26 "C:/MCC18/v3.35/h/limits.h"
#line 27 "C:/MCC18/v3.35/h/limits.h"
#line 28 "C:/MCC18/v3.35/h/limits.h"
#line 29 "C:/MCC18/v3.35/h/limits.h"

#line 31 "C:/MCC18/v3.35/h/limits.h"
#line 32 "C:/MCC18/v3.35/h/limits.h"
#line 33 "C:/MCC18/v3.35/h/limits.h"

#line 35 "C:/MCC18/v3.35/h/limits.h"
#line 36 "C:/MCC18/v3.35/h/limits.h"
#line 37 "C:/MCC18/v3.35/h/limits.h"

#line 39 "C:/MCC18/v3.35/h/limits.h"
#line 40 "C:/MCC18/v3.35/h/limits.h"
#line 41 "C:/MCC18/v3.35/h/limits.h"

 
#line 44 "C:/MCC18/v3.35/h/limits.h"
#line 45 "C:/MCC18/v3.35/h/limits.h"
#line 46 "C:/MCC18/v3.35/h/limits.h"

 
#line 49 "C:/MCC18/v3.35/h/limits.h"
#line 50 "C:/MCC18/v3.35/h/limits.h"

#line 52 "C:/MCC18/v3.35/h/limits.h"











#line 54 "C:/PIC/Microchip Solutions/Microchip/Include/usb/usb_common.h"

#line 1 "C:/MCC18/v3.35/h/GenericTypeDefs.h"

#line 45 "C:/MCC18/v3.35/h/GenericTypeDefs.h"
 

#line 52 "C:/MCC18/v3.35/h/GenericTypeDefs.h"
#line 54 "C:/MCC18/v3.35/h/GenericTypeDefs.h"
#line 56 "C:/MCC18/v3.35/h/GenericTypeDefs.h"
#line 58 "C:/MCC18/v3.35/h/GenericTypeDefs.h"
#line 60 "C:/MCC18/v3.35/h/GenericTypeDefs.h"
#line 79 "C:/MCC18/v3.35/h/GenericTypeDefs.h"
#line 81 "C:/MCC18/v3.35/h/GenericTypeDefs.h"
#line 88 "C:/MCC18/v3.35/h/GenericTypeDefs.h"
#line 90 "C:/MCC18/v3.35/h/GenericTypeDefs.h"
#line 93 "C:/MCC18/v3.35/h/GenericTypeDefs.h"
#line 95 "C:/MCC18/v3.35/h/GenericTypeDefs.h"
#line 144 "C:/MCC18/v3.35/h/GenericTypeDefs.h"
#line 183 "C:/MCC18/v3.35/h/GenericTypeDefs.h"
#line 245 "C:/MCC18/v3.35/h/GenericTypeDefs.h"
#line 332 "C:/MCC18/v3.35/h/GenericTypeDefs.h"
#line 549 "C:/MCC18/v3.35/h/GenericTypeDefs.h"
#line 55 "C:/PIC/Microchip Solutions/Microchip/Include/usb/usb_common.h"











#line 67 "C:/PIC/Microchip Solutions/Microchip/Include/usb/usb_common.h"
#line 68 "C:/PIC/Microchip Solutions/Microchip/Include/usb/usb_common.h"
#line 69 "C:/PIC/Microchip Solutions/Microchip/Include/usb/usb_common.h"
#line 70 "C:/PIC/Microchip Solutions/Microchip/Include/usb/usb_common.h"
#line 71 "C:/PIC/Microchip Solutions/Microchip/Include/usb/usb_common.h"
#line 72 "C:/PIC/Microchip Solutions/Microchip/Include/usb/usb_common.h"
#line 73 "C:/PIC/Microchip Solutions/Microchip/Include/usb/usb_common.h"
#line 74 "C:/PIC/Microchip Solutions/Microchip/Include/usb/usb_common.h"
#line 75 "C:/PIC/Microchip Solutions/Microchip/Include/usb/usb_common.h"
#line 76 "C:/PIC/Microchip Solutions/Microchip/Include/usb/usb_common.h"
#line 77 "C:/PIC/Microchip Solutions/Microchip/Include/usb/usb_common.h"
#line 78 "C:/PIC/Microchip Solutions/Microchip/Include/usb/usb_common.h"
#line 79 "C:/PIC/Microchip Solutions/Microchip/Include/usb/usb_common.h"
#line 80 "C:/PIC/Microchip Solutions/Microchip/Include/usb/usb_common.h"
#line 81 "C:/PIC/Microchip Solutions/Microchip/Include/usb/usb_common.h"

#line 83 "C:/PIC/Microchip Solutions/Microchip/Include/usb/usb_common.h"
#line 84 "C:/PIC/Microchip Solutions/Microchip/Include/usb/usb_common.h"
#line 85 "C:/PIC/Microchip Solutions/Microchip/Include/usb/usb_common.h"
#line 86 "C:/PIC/Microchip Solutions/Microchip/Include/usb/usb_common.h"
#line 87 "C:/PIC/Microchip Solutions/Microchip/Include/usb/usb_common.h"
#line 88 "C:/PIC/Microchip Solutions/Microchip/Include/usb/usb_common.h"
#line 89 "C:/PIC/Microchip Solutions/Microchip/Include/usb/usb_common.h"
#line 90 "C:/PIC/Microchip Solutions/Microchip/Include/usb/usb_common.h"
#line 91 "C:/PIC/Microchip Solutions/Microchip/Include/usb/usb_common.h"
#line 92 "C:/PIC/Microchip Solutions/Microchip/Include/usb/usb_common.h"
#line 93 "C:/PIC/Microchip Solutions/Microchip/Include/usb/usb_common.h"
#line 94 "C:/PIC/Microchip Solutions/Microchip/Include/usb/usb_common.h"



#line 98 "C:/PIC/Microchip Solutions/Microchip/Include/usb/usb_common.h"
#line 99 "C:/PIC/Microchip Solutions/Microchip/Include/usb/usb_common.h"
#line 100 "C:/PIC/Microchip Solutions/Microchip/Include/usb/usb_common.h"
#line 101 "C:/PIC/Microchip Solutions/Microchip/Include/usb/usb_common.h"
#line 102 "C:/PIC/Microchip Solutions/Microchip/Include/usb/usb_common.h"
#line 103 "C:/PIC/Microchip Solutions/Microchip/Include/usb/usb_common.h"
#line 104 "C:/PIC/Microchip Solutions/Microchip/Include/usb/usb_common.h"
#line 105 "C:/PIC/Microchip Solutions/Microchip/Include/usb/usb_common.h"
#line 106 "C:/PIC/Microchip Solutions/Microchip/Include/usb/usb_common.h"
#line 107 "C:/PIC/Microchip Solutions/Microchip/Include/usb/usb_common.h"
#line 108 "C:/PIC/Microchip Solutions/Microchip/Include/usb/usb_common.h"
#line 109 "C:/PIC/Microchip Solutions/Microchip/Include/usb/usb_common.h"

#line 111 "C:/PIC/Microchip Solutions/Microchip/Include/usb/usb_common.h"

#line 113 "C:/PIC/Microchip Solutions/Microchip/Include/usb/usb_common.h"










#line 138 "C:/PIC/Microchip Solutions/Microchip/Include/usb/usb_common.h"
 

typedef union
{
    BYTE    bitmap;
    struct
    {
        BYTE ep_num:    4;
        BYTE zero_pkt:  1;
        BYTE dts:       1;
        BYTE force_dts: 1;
        BYTE direction: 1;
    }field;

} TRANSFER_FLAGS;




#line 160 "C:/PIC/Microchip Solutions/Microchip/Include/usb/usb_common.h"
 
#line 162 "C:/PIC/Microchip Solutions/Microchip/Include/usb/usb_common.h"
#line 163 "C:/PIC/Microchip Solutions/Microchip/Include/usb/usb_common.h"
#line 164 "C:/PIC/Microchip Solutions/Microchip/Include/usb/usb_common.h"
#line 165 "C:/PIC/Microchip Solutions/Microchip/Include/usb/usb_common.h"
#line 166 "C:/PIC/Microchip Solutions/Microchip/Include/usb/usb_common.h"
#line 167 "C:/PIC/Microchip Solutions/Microchip/Include/usb/usb_common.h"
#line 168 "C:/PIC/Microchip Solutions/Microchip/Include/usb/usb_common.h"
#line 169 "C:/PIC/Microchip Solutions/Microchip/Include/usb/usb_common.h"
#line 170 "C:/PIC/Microchip Solutions/Microchip/Include/usb/usb_common.h"
#line 171 "C:/PIC/Microchip Solutions/Microchip/Include/usb/usb_common.h"
#line 172 "C:/PIC/Microchip Solutions/Microchip/Include/usb/usb_common.h"
#line 173 "C:/PIC/Microchip Solutions/Microchip/Include/usb/usb_common.h"
#line 174 "C:/PIC/Microchip Solutions/Microchip/Include/usb/usb_common.h"
#line 175 "C:/PIC/Microchip Solutions/Microchip/Include/usb/usb_common.h"
#line 176 "C:/PIC/Microchip Solutions/Microchip/Include/usb/usb_common.h"
#line 177 "C:/PIC/Microchip Solutions/Microchip/Include/usb/usb_common.h"



#line 183 "C:/PIC/Microchip Solutions/Microchip/Include/usb/usb_common.h"
 
#line 185 "C:/PIC/Microchip Solutions/Microchip/Include/usb/usb_common.h"
#line 186 "C:/PIC/Microchip Solutions/Microchip/Include/usb/usb_common.h"
#line 187 "C:/PIC/Microchip Solutions/Microchip/Include/usb/usb_common.h"
#line 188 "C:/PIC/Microchip Solutions/Microchip/Include/usb/usb_common.h"
#line 189 "C:/PIC/Microchip Solutions/Microchip/Include/usb/usb_common.h"
#line 190 "C:/PIC/Microchip Solutions/Microchip/Include/usb/usb_common.h"
#line 191 "C:/PIC/Microchip Solutions/Microchip/Include/usb/usb_common.h"
#line 192 "C:/PIC/Microchip Solutions/Microchip/Include/usb/usb_common.h"
#line 193 "C:/PIC/Microchip Solutions/Microchip/Include/usb/usb_common.h"
#line 194 "C:/PIC/Microchip Solutions/Microchip/Include/usb/usb_common.h"
#line 195 "C:/PIC/Microchip Solutions/Microchip/Include/usb/usb_common.h"



#line 202 "C:/PIC/Microchip Solutions/Microchip/Include/usb/usb_common.h"
 
#line 204 "C:/PIC/Microchip Solutions/Microchip/Include/usb/usb_common.h"




#line 213 "C:/PIC/Microchip Solutions/Microchip/Include/usb/usb_common.h"
 

typedef enum
{
    
    EVENT_NONE = 0,
    
    
    
    EVENT_TRANSFER,
    
    
    
    EVENT_SOF,                  
    
    
    EVENT_RESUME,
    
    
    
    EVENT_SUSPEND,
                  
    
    
    EVENT_RESET,                
    
    
    
    
    EVENT_ATTACH,      
             
    
    
    EVENT_DETACH,               
    
    
    EVENT_HUB_ATTACH,           
    
    
    EVENT_STALL,     
               
    
    
    EVENT_SETUP,                
    
    
    EVENT_VBUS_SES_REQUEST,     
    
    
    
    
    EVENT_VBUS_OVERCURRENT,     
    
    
    
    
    
    EVENT_VBUS_REQUEST_POWER,   
    
    
    
    
    EVENT_VBUS_RELEASE_POWER,   
    
    
    
    
    
    
    
    
    EVENT_VBUS_POWER_AVAILABLE, 
    
    
    
    EVENT_UNSUPPORTED_DEVICE,   
    
    
    
    EVENT_CANNOT_ENUMERATE,     
    
    
    
    EVENT_CLIENT_INIT_ERROR,    
    
    
    
    
    
    EVENT_OUT_OF_MEMORY,        
    
    
    EVENT_UNSPECIFIED_ERROR,    

    
    EVENT_GENERIC_BASE  = 100,      

    EVENT_MSD_BASE      = 200,      

    EVENT_HID_BASE      = 300,      

    EVENT_PRINTER_BASE  = 400,      
    
    EVENT_USER_BASE     = 10000,    
                                    

    
    
    EVENT_BUS_ERROR     = 65535U    

} USB_EVENT;




#line 333 "C:/PIC/Microchip Solutions/Microchip/Include/usb/usb_common.h"
 

typedef struct _transfer_event_data
{
    TRANSFER_FLAGS  flags;          
    UINT32          size;           
    BYTE            pid;            

} USB_TRANSFER_EVENT_DATA;




#line 350 "C:/PIC/Microchip Solutions/Microchip/Include/usb/usb_common.h"
 

typedef struct _vbus_power_data
{
    BYTE            port;           
    BYTE            current;        
} USB_VBUS_POWER_EVENT_DATA;




#line 365 "C:/PIC/Microchip Solutions/Microchip/Include/usb/usb_common.h"
 









#line 404 "C:/PIC/Microchip Solutions/Microchip/Include/usb/usb_common.h"
 

typedef BOOL (*USB_EVENT_HANDLER) ( USB_EVENT event, void *data, unsigned int size );









#line 438 "C:/PIC/Microchip Solutions/Microchip/Include/usb/usb_common.h"
 

   
#line 442 "C:/PIC/Microchip Solutions/Microchip/Include/usb/usb_common.h"
#line 443 "C:/PIC/Microchip Solutions/Microchip/Include/usb/usb_common.h"
#line 444 "C:/PIC/Microchip Solutions/Microchip/Include/usb/usb_common.h"
#line 446 "C:/PIC/Microchip Solutions/Microchip/Include/usb/usb_common.h"

#line 448 "C:/PIC/Microchip Solutions/Microchip/Include/usb/usb_common.h"
#line 450 "C:/PIC/Microchip Solutions/Microchip/Include/usb/usb_common.h"
#line 451 "C:/PIC/Microchip Solutions/Microchip/Include/usb/usb_common.h"
#line 453 "C:/PIC/Microchip Solutions/Microchip/Include/usb/usb_common.h"
#line 454 "C:/PIC/Microchip Solutions/Microchip/Include/usb/usb_common.h"
#line 455 "C:/PIC/Microchip Solutions/Microchip/Include/usb/usb_common.h"
#line 457 "C:/PIC/Microchip Solutions/Microchip/Include/usb/usb_common.h"
