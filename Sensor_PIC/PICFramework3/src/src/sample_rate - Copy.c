#include "maindefs.h"
#include "sample_rate.h"
#include "messageformat.h"
#include "init.h"

#define SAMPPERIOD(sensor) (8 * T2_PERIOD * 1000 / SAMPRATE_##sensor)

void timer2_int_handler()
{
  static int count;
  if (count > (8 * 1000 / T2_PERIOD))
      count = 0;

/*
  if ((count % SAMPPERIOD(US1)) == 0)
  if ((count % SAMPPERIOD(US2)) == 1)
  if ((count % SAMPPERIOD(US3)) == 2)
*/
  if ((count % SAMPPERIOD(IR1)) == 3) {
      // Set the A/D GO bit
      ADCON0bits.GO = 1;
      //set_debug('f');
  }
  if ((count % SAMPPERIOD(IR2)) == 4) {
      // Set the A/D GO bit
      //ADCON0bits.GO = 1;
  }
/*
  if ((count % SAMPPERIOD(GYX)) == 5)
  if ((count % SAMPPERIOD(GYY)) == 6)
*/
  ++count;
}

void timer2_configure()
{
  /* base clock for T2 is Fosc/4 (instruction clock) == 48MHz/4 */
  /* Ignore the above comment since Mark III freq is 12MHz*/
  T2CONbits.T2CKPS = 1; /* prescale by 4 */
  //T2CONbits.T2OUTPS = 0xe; /* postscale by 15 */
  T2CONbits.T2OUTPS3 = 1;
  T2CONbits.T2OUTPS2 = 1;
  T2CONbits.T2OUTPS1 = 1;
  T2CONbits.T2OUTPS0 = 0;
  PR2 = 50; /* so .. 12MHz/4/4/15/50 = 1kHz = period 1ms */
  PIE1bits.TMR2IE = 1;
  T2CONbits.TMR2ON = 1;
}


