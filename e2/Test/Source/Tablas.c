/***********************************************************************/
/*                                                                     */
/*  FILE        :Tablas.c                                          	   */
/*  DATE        :22/05/14                                              */
/*  DESCRIPTION :Defines the tables used by the project                */
/*  CPU TYPE    :RL78G13                                               */
/*  AUTHOR      :Carlos Humberto Reyes Andres                          */
/*                                                                     */
/*  PROJECT     : Hidra washer machine Control                         */
/*                                                                     */
/*  Copyright 2014 Mabe TyP                                            */
/*  All rights reserved                                                */
/*                                                                     */
/***********************************************************************/

#include "Ram.h"
#include "Tablas.h"

#ifdef C_EFX1870P001
const U8 T_VERSION[] = {"Kraken24 UserInterface"}; // Software Version -> 
                                                // Raw Flash Checksum: 
                                                // ID code 00000000000000
const U8 T_DATETIME[] = __DATE__ "  " __TIME__;                         
const U8 T_HARDWARE_ID[] ={0};
const U8 T_MODEL[] ={4};
const U8 T_SW_PART_NUMBER[] = {"EFX1870P001R002"};
const U8  T_GROUP_NO    = {1};
const U8  T_REVISION_NO = {2};
#endif

#ifdef C_EFX2009P001
const U8 T_VERSION[] = {"Centauro LA UserInterface"}; // Software Version -> 
                                                // Raw Flash Checksum: 
                                                // ID code 00000000000000
const U8 T_DATETIME[] = __DATE__ "  " __TIME__;                         
const U8 T_HARDWARE_ID[] ={1};
const U8 T_MODEL[] ={4};
const U8 T_SW_PART_NUMBER[] = {"EFX2009P001R000"};
const U8  T_GROUP_NO    = {1};
const U8  T_REVISION_NO = {0};
#endif

const U8  T_DISPLAY_VAL[] = 
              {	  
                // 0x00	 0x01  0x02	 0x03  0x04
                  0xC0, 0xF9, 0xA4, 0xB0, 0x99,
								// 0x05	 0x06  0x07	 0x08  0x09
                  0x92, 0x82, 0xF8, 0x80, 0x90,
								// 0x0A	 0x0B  0x0C	 0x0D  0x0E
								  0x88, 0x83, 0xA7, 0xA1, 0x86,
								// 0x0F	 0x10  0x11	 0x12  0x13
								  0x8E, 0x90, 0x89, 0xF1, 0xC7,
								// 0x14	 0x15  0x16	 0x17  0x18
								  0xAB, 0x8C, 0xAF, 0x87, 0xC1,
								// 0x19	 0x1A  0x1B	 0x1C  0x1D
								  0x91, 0xFF, 0xFE, 0xFD, 0xFB,
								// 0x1E	 0x1F  0x20	 0x21  0x22
								  0xF7, 0xEF, 0xDF, 0xBF, 0xE9,
								// 0x23	0x24   0x25  0x26  0x27
								  0xCF, 0xFC, 0xF3, 0xE7, 0xDE
              };
/*                                                                        */
/*                                   g f e d c b a                        */
/*                             0 = 1 1 0 0 0 0 0 0 = 0xC0  d 0  -> h 0x00 */
/*                             1 = 1 1 1 1 1 0 0 1 = 0xF9  d 1  -> h 0x01 */
/*                             2 = 1 0 1 0 0 1 0 0 = 0xA4  d 2  -> h 0x02 */
/*                             3 = 1 0 1 1 0 0 0 0 = 0xB0  d 3  -> h 0x03 */
/*                             4 = 1 0 0 1 1 0 0 1 = 0x99  d 4  -> h 0x04 */
/*          _a__               5 = 1 0 0 1 0 0 1 0 = 0x92  d 5  -> h 0x05 */
/*       f/    /               6 = 1 0 0 0 0 0 1 0 = 0x82  d 6  -> h 0x06 */
/*       /_g__/b               7 = 1 1 1 1 1 0 0 0 = 0xF8  d 7  -> h 0x07 */
/*     e/    /                 8 = 1 0 0 0 0 0 0 0 = 0x80  d 8  -> h 0x08 */
/*     /____/c  . p            9 = 1 0 0 1 0 0 0 0 = 0x90  d 9  -> h 0x09 */
/*       d                     A = 1 0 0 0 1 0 0 0 = 0x88  d 10 -> h 0x0A */
/*                             b = 1 0 0 0 0 0 1 1 = 0x83  d 11 -> h 0x0B */
/*                             c = 1 0 1 0 0 1 1 1 = 0xA7  d 12 -> h 0x0C */
/*                             d = 1 0 1 0 0 0 0 1 = 0xA1  d 13 -> h 0x0D */
/*                             E = 1 0 0 0 0 1 1 0 = 0x86  d 14 -> h 0x0E */
/*                             F = 1 0 0 0 1 1 1 0 = 0x8E  d 15 -> h 0x0F */
/*                             g = 1 0 0 1 0 0 0 0 = 0x90  d 16 -> h 0x10 */
/*                             H = 1 0 0 0 1 0 0 1 = 0x89  d 17 -> h 0x11 */
/*                             J = 1 1 1 1 0 0 0 1 = 0xF1  d 18 -> h 0x12 */
/*                             L = 1 1 0 0 0 1 1 1 = 0xC7  d 19 -> h 0x13 */
/*                             n = 1 0 1 0 1 0 1 1 = 0xAB  d 20 -> h 0x14 */
/*                             P = 1 0 0 0 1 1 0 0 = 0x8C  d 21 -> h 0x15 */
/*                             r = 1 0 1 0 1 1 1 1 = 0xAF  d 22 -> h 0x16 */
/*                             t = 1 0 0 0 0 1 1 1 = 0x87  d 23 -> h 0x17 */
/*                             u = 1 1 0 0 0 0 0 1 = 0xC1  d 24 -> h 0x18 */
/*                             y = 1 0 0 1 0 0 0 1 = 0x91  d 25 -> h 0x19 */
/*                               = 1 1 1 1 1 1 1 1 = 0xFF  d 26 -> h 0x1A */
/*                             - = 1 1 1 1 1 1 1 0 = 0xFE  d 27 -> h 0x1B */
/*                             | = 1 1 1 1 1 1 0 1 = 0xFD  d 28 -> h 0x1C */
/*                             | = 1 1 1 1 1 0 1 1 = 0xFB  d 29 -> h 0x1D */
/*                             _ = 1 1 1 1 0 1 1 1 = 0xF7  d 30 -> h 0x1E */
/*                             | = 1 1 1 0 1 1 1 1 = 0xEF  d 31 -> h 0x1F */
/*                             | = 1 1 0 1 1 1 1 1 = 0xDF  d 32 -> h 0x20 */
/*                             - = 1 0 1 1 1 1 1 1 = 0xBE  d 33 -> h 0x21 */
/*                            il = 1 1 1 0 1 0 0 1 = 0xE9  d 34 -> h 0x22 */
/*                            l_ = 1 1 0 0 1 1 1 1 = 0xCF  d 35 -> h 0x23 */
/*							           segAB = 1 1 1 1 1 1 0 0 = 0xFC  d 36 -> h 0x24 */
/*            	 					 segCD = 1 1 1 1 0 0 1 1 = 0xF3  d 37 -> h 0x25 */
/*					           		 segDE = 1 1 1 0 0 1 1 1 = 0xE7  d 38 -> h 0x26 */
/*          							 segFA = 1 1 0 1 1 1 1 0 = 0xDE  d 39 -> h 0x27 */
