#include <string.h>
#include <stdint.h>
#include "messageformat.h"

/* 0 . 1 . 2 . 3 . . . 7
 * | 1 | 0 | E |  SEQ   |
 * 8 . . . . . . . . .15
 * |      data msB      |
 * 16 . . . . . . . . 23
 * |      data lsB      |
 * 24 . . . 27 28 . . 31
 * |   CODE   |   CRC   |
 */
void init_msg(struct message * msg)
{
  memset(msg, '\0', sizeof(struct message));
  msg->data[0] = 0x80;
}

void set_msg_empty(struct message * msg)
{
  msg->data[0] = (msg->data[0] & 0xdf) | 0x20;
}

void set_msg_data(struct message * msg, uint16_t data)
{
  msg->data[1] = data >> 8 & 0xff;
  msg->data[2] = data & 0xff;
}

void set_msg_code(struct message * msg, uint8_t code)
{
  msg->data[3] = (msg->data[3] & 0x0f) | ((code & 0xf) << 4);
}

void set_msg_seq(struct message * msg, uint8_t seq)
{
  msg->data[0] = (msg->data[0] & 0xe0) | (seq & 0x1f);
}

static uint8_t calc_msg_crc(const struct message * msg)
{
  uint8_t xor = ((msg->data[0] >> 4) ^ (msg->data[0])
               ^ (msg->data[1] >> 4) ^ (msg->data[1])
               ^ (msg->data[2] >> 4) ^ (msg->data[2])
               ^ (msg->data[3] >> 4)) & 0xf;
  return xor;
}

void add_msg_crc(struct message * msg)
{
  uint8_t crc = calc_msg_crc(msg);
  msg->data[3] = (msg->data[3] & 0xf0) | (crc & 0x0f);
}

uint8_t test_msg(const struct message * msg)
{
  if ((msg->data[0] & 0xc0) != 0x80)
    return 0;

  if ((msg->data[3] & 0x0f) != calc_msg_crc(msg))
    return 0;

  return 1;
}

uint8_t get_msg_empty(const struct message * msg)
{
  return (msg->data[0] & 0x20) != 0;
}

uint8_t get_msg_code(const struct message * msg)
{
  return (msg->data[3] >> 4) & 0xf;
}

uint8_t get_msg_seq(const struct message * msg)
{
  return msg->data[0] & 0x1f;
}

uint16_t get_msg_data(const struct message * msg)
{
  return msg->data[1] << 8 | msg->data[2];
}

