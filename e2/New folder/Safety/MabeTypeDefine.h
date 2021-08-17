/**********************************************************************

  FILE        : MabeTypeDefine.h
  DATE        : 16/06/2014
  DESCRIPTION : Type define for the project

  CPU TYPE    : RX210
  AUTHOR      : J. Efren Rodriguez.
                M. Pena
  PROJECT     : TL2016
  IDE         : E2 Studio Version 2.2.0.13
  Compiler    : Renesas RX Compiler V2.01.00

  Copyright (c) 2014 Mabe TyP
  All rights reserved

**********************************************************************/

#ifndef _MABE_TYPE_DEFINE_
#define _MABE_TYPE_DEFINE_

typedef unsigned char U8;
typedef signed char I8;
typedef unsigned short U16;
typedef signed short I16;
typedef unsigned long int U32;
typedef signed long int I32;
typedef float F32;
typedef double F64;
typedef unsigned long long U64;
typedef signed long long I64;

//--------------------------------------------------------------------
//             Structure Definitions
//--------------------------------------------------------------------
struct  Ubit_def
  {
	U8  b0:1;
	U8  b1:1;
	U8  b2:1;
	U8  b3:1;
	U8  b4:1;
	U8  b5:1;
	U8  b6:1;
	U8  b7:1;
  };
union   Ubyte_def
  {
	struct  Ubit_def Ubit;
	U8      Ubyte;
  };

struct SNibble_def
  {
	U8  LSNibble:4;
	U8  MSNibble:4;
  };

union UByteNibble_def
  {
    struct  Ubit_def     Ubit;
    struct  SNibble_def  nu4byte;   //byte
	  U8  UNbyte;
  };

struct SByte_def
  {
	U8  LSByte;
	U8  MSByte;
  };

union UInt_def
  {
	struct  SByte_def  nu8byte;   //nibble byte
	U16 Uint;
  };

struct SInt_def
  {
	U16  LSInt;
	U16  MSInt;
  };

union ULongInt_def
  {
	struct  SInt_def  nu16Int;   //nibble byte
	U32     ULongInt;
  };

struct  ULongbit_def
  {
    U8  b0:1;
    U8  b1:1;
    U8  b2:1;
    U8  b3:1;
    U8  b4:1;
    U8  b5:1;
    U8  b6:1;
    U8  b7:1;
    U8  b8:1;
    U8  b9:1;
    U8  b10:1;
    U8  b11:1;
    U8  b12:1;
    U8  b13:1;
    U8  b14:1;
    U8  b15:1;
    U8  b16:1;
    U8  b17:1;
    U8  b18:1;
    U8  b19:1;
    U8  b20:1;
    U8  b21:1;
    U8  b22:1;
    U8  b23:1;
    U8  b24:1;
    U8  b25:1;
    U8  b26:1;
    U8  b27:1;
    U8  b28:1;
    U8  b29:1;
    U8  b30:1;
    U8  b31:1;
  };
union   ULongbyte_def
  {
    struct  ULongbit_def ULongbit;
    U32      ULongbyte;
  };


struct  UIntbit_def
  {
    U8  b0:1;
    U8  b1:1;
    U8  b2:1;
    U8  b3:1;
    U8  b4:1;
    U8  b5:1;
    U8  b6:1;
    U8  b7:1;
    U8  b8:1;
    U8  b9:1;
    U8  b10:1;
    U8  b11:1;
    U8  b12:1;
    U8  b13:1;
    U8  b14:1;
    U8  b15:1;
  };
union   UIntByte_def
  {
    struct  UIntbit_def UIntbit;
    U16      UIntbyte;
  };

//-----------------------------
#define C_TRUE             1
#define C_FALSE            0
//-----------------------------
#define C_ON               1
#define C_OFF              0
//-----------------------------

#define C_NOT_END            0
#define C_END                1

#define C_DISABLE           (U8) 0
#define C_ENABLE            (U8) 1

typedef enum{
  E_AC_ABSENCE_LOW,
  E_AC_ABSENCE_HIGH,
  E_AC_PRESENCE,
  E_AC_ERROR
}E_AC_Status;

typedef enum{
  E_FALSE,
  E_TRUE
}E_BoolType;

#define C_GPIO_LOW            0
#define C_GPIO_HIGH           1


typedef enum{
  E_OVERFLOW_TC2_INIT,
  E_OVERFLOW_TC2_WATER_LEVEL_INIT,
  E_OVERFLOW_TC2_PROCESS_DELTA,
  E_OVERFLOW_TC2_PAUSE,
  E_OVERFLOW_TC2_OK,
  E_OVERFLOW_TC2_FAIL
}E_OverflowTC2St;

typedef enum {
  E_CCW_INIT,                  // 0
  E_CCW_INITIAL_DELAY,         // 1
  E_CCW_POWER_ON,              // 2
  E_CCW_ENGAGE,                // 3
  E_CCW_DELAY,                 // 4
  E_CCW_PROCESS,               // 5
  E_CCW_STOPPED,               // 6
  E_CCW_INTER_DELAY,           // 7
  E_CW_PROCESS,                // 8
  E_CW_STOPPED,                // 9
  E_CCW_END,                   // 10
}E_WaterDetectMotorSt;

#endif /* _MABE_TYPE_DEFINE_ */
