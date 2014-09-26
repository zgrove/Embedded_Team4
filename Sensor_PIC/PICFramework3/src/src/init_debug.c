/*
 * File:   init_debug.c
 * Author: ECE4534
 *
 * Created on September 23, 2014, 8:39 AM
 */

#include "maindefs.h"

#ifndef INIT_DEBUG_C
#define	INIT_DEBUG_C

#define DEBUG0(n) LATDbits.LATD4 = (n)

#ifdef	__cplusplus
extern "C" {
#endif

void init_debug(void){
    TRISDbits.TRISD4 = 0;
    TRISDbits.TRISD5 = 0;
    TRISDbits.TRISD6 = 0;
    TRISDbits.TRISD7 = 0;
    PORTDbits.RD4 = 0;
    PORTDbits.RD5 = 0;
    PORTDbits.RD6 = 0;
    PORTDbits.RD7 = 0;
}



#ifdef	__cplusplus
}
#endif

#endif	/* INIT_DEBUG_C */

