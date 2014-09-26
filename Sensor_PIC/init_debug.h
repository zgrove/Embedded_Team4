/* 
 * File:   init_debug.h
 * Author: ECE4534
 *
 * Created on September 23, 2014, 8:39 AM
 */

#include "maindefs.h"

#ifndef INIT_DEBUG_H
#define	INIT_DEBUG_H

#ifdef	__cplusplus
extern "C" {
#endif

void init_debug(){
    PORTDbits.RD0 = 0;
    PORTDbits.RD1 = 0;
    PORTDbits.RD2 = 0;
    PORTDbits.RD3 = 0;
    PORTDbits.RD4 = 0;
    PORTDbits.RD5 = 0;
    PORTDbits.RD6 = 0;
    PORTDbits.RD7 = 0;
}



#ifdef	__cplusplus
}
#endif

#endif	/* INIT_DEBUG_H */

