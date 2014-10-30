#ifndef T5_UART_TX_H
#define T5_UART_TX_H

#define UARTTXBUFLEN    64

/* ring buffer for the uart send
 */
struct ring_buffer
{
  unsigned char * data;
  int size;     /* total capacity of data array */
  int count;    /* number of defined elements */
  int read;     /* index from which data will be read */
  int write;    /* index at which data will be written */
  /* read == write is ambiguous.
   * if count == 0, empty.
   * otherwise, count == size, full
   */
};

int uart_tx_bytes(const void * d, int l);
void uart_transmit_int_handler();
void init_uart_transmit(struct ring_buffer * uart_tx_buffer, int buffer_len);

void uart_tx_config(int baud);

#endif /* T5_UART_TX_H */
