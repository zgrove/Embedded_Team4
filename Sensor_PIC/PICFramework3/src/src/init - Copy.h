/* 
 * File:   init.h
 * Author: Zak Grove
 *
 * Created on September 30, 2014, 8:08 PM
 */

#include "maindefs.h";

#ifndef INIT_H
#define	INIT_H

// Initializes A/D bits
void init_ad(void);

// Initializes Debug bits
void init_debug(void);

// Sets debug bits depending on where its called
void set_debug(unsigned char);


#endif	/* INIT_H */

