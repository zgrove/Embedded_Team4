#include "maindefs.h"
#ifndef __XC8
#include <usart.h>
#else
#include <plib/usart.h>
#endif
#include "init.h"
#include "uart_tx.h"

#if defined __USE18F46J50 || defined __USE18F45J10
#else
#error "uart tx module not designed for current hardware"
#endif

/* Since uart_tx_buffer (utb) will be accessed from interrupts and main loop
 * code, there are potential concurrency problems.  To avoid these problems,
 * mask the UART TX interrupt fur the duration of the uart_tx_bytes call.
 */

static struct ring_buffer * utb;

/* return the number of bytes added to the tx buffer
 * if the buffer is full, the return will not equal l
 * -1 indicates an error condition other than buffer full
 */
int uart_tx_bytes(const void * d, int l)
{
  //set_debug('a');
  int i;
  /* given, struct ring_buffer * uart_tx_buffer (utb) */

  if (utb->size - utb->count < l) {
      //set_debug('b');
      return 0;
  }

  /* mask UART TX interrupt */
#if defined __USE18F46J50 || defined __USE18F45J10
  PIE1bits.TX1IE = 0;
#endif

  for(i = 0; i < l; ++i, utb->write = (utb->write + 1) % utb->size)
    utb->data[utb->write] = ((const unsigned char*)d)[i];
  utb->count += l;

#if defined __USE18F46J50 || defined __USE18F45J10
  /* unmask UART TX interrupt - if it was off before it needs to be on now */
  PIE1bits.TX1IE = 1;
#endif
  //set_debug('z');
  return l;
}

void uart_transmit_int_handler()
{
  unsigned char nextbyte;

  /* interrupt stuff */
#ifdef UART_DEBUG
  DEBUG0(1);
#endif

  if (utb->count > 0) {
    nextbyte = utb->data[utb->read];
    utb->data[utb->read] = '\0';
    utb->read = (utb->read + 1) % utb->size;
    utb->count--;
    if (utb->count == 0) {
      utb->read = 0;
      utb->write = 0;
    }
#if defined __USE18F46J50
    Write1USART(nextbyte);
#elif defined __USE18F45J10
    WriteUSART(nextbyte);
#endif
  } else {
    /* mask UART TX interrupt (because there's no data to be sent */
#if defined __USE18F46J50 || defined __USE18F45J10
    PIE1bits.TX1IE = 0;
#endif
  }

  /* interrupt stuff */
#ifdef UART_DEBUG
  DEBUG0(0);
#endif
}

void init_uart_transmit(struct ring_buffer * uart_tx_buffer, int buffer_len)
{
  utb = uart_tx_buffer;
  utb->read = 0;
  utb->write = 0;
  utb->count = 0;
  utb->size = buffer_len;
}

void uart_tx_config(int baud)
{
#if defined __USE18F46J50 || defined __USE18F45J10
  BAUDCONbits.BRG16 = 0;
  BAUDCONbits.WUE = 0;

  unsigned int brg = 12000000 / 16 / baud - 1;

  /*DEBUGCODE1(7);
  if (brg > 255) {
    SPBRG = F_OSC / 64 / baud - 1;
    if (SPBRG == 77)
      DEBUGCODE1(8);
    TXSTA1bits.BRGH = 0;
  } else {
    SPBRG = brg;
    TXSTA1bits.BRGH = 1;
  }
  DEBUGCODE1(7);*/

  TXSTA1bits.TX9 = 0;
  TXSTA1bits.SYNC = 0;
  TXSTA1bits.TXEN = 1;

  RCSTA1bits.SPEN = 1;
#endif
}


