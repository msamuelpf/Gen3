/*
 * interrupt_timing.h
 *
 *  Created on: Jul 15, 2013
 *      Author: 212327362
 */

#ifndef INTERRUPT_TIMING_H_
#define INTERRUPT_TIMING_H_

//#define MEASURE_INTERRUPTS

#if defined(MEASURE_INTERRUPTS)
#define     INTERRUPT_TIMING_SETUP  \
                                    PORTC.PMR.BIT.B2 = 0;\
                                    PORTC.PDR.BIT.B2 = 1;\
                                    PORTC.PODR.BIT.B2 = 0;

// Set a debug pin high during ISR, low at other times
#define     ENTER_ISR               PORTC.PODR.BIT.B2 = 1;
#define     EXIT_ISR                PORTC.PODR.BIT.B2 = 0;

#else
// No ISR timing so just blank definitions
#define     INTERRUPT_TIMING_SETUP
#define     ENTER_ISR
#define     EXIT_ISR
#endif

#endif /* INTERRUPT_TIMING_H_ */
