#ifndef T5_MSGFMT_H
#define T5_MSGFMT_H

#include <stdint.h>

#define MESSAGEFORMAT_VERSION 102

#define MSG_CODE_US1    1
#define MSG_CODE_US2    2
#define MSG_CODE_US3    3
#define MSG_CODE_IR1    4
#define MSG_CODE_IR2    5
#define MSG_CODE_GYX    6
#define MSG_CODE_GYY    7
#define MSG_CODE_ENC1   8
#define MSG_CODE_ENC2   8
#define MSG_CODE_MOTOR  0xf

/* yes this is a magic number but functions are all hard coded too
 */
struct message {
  uint8_t data[4];
};

void init_msg(struct message * msg);
void set_msg_empty(struct message * msg);
void set_msg_data(struct message * msg, uint16_t data);
void set_msg_code(struct message * msg, uint8_t code);
void set_msg_seq(struct message * msg, uint8_t seq);
void add_msg_crc(struct message * msg);

uint8_t test_msg(const struct message * msg);

uint8_t get_msg_empty(const struct message * msg);
uint8_t get_msg_code(const struct message * msg);
uint8_t get_msg_seq(const struct message * msg);
uint16_t get_msg_data(const struct message * msg);

#endif /* T5_MSGFMT_H */

