#define T2_PERIOD         1 /* timer2 period in ms */

/* units are # of reads per 8 seconds */
#define SAMPRATE_US1    80 /* 100ms => 80/8 = 10 => for period => 1/10 = .1 = 100ms */
#define SAMPRATE_US2    80
#define SAMPRATE_US3    80
#define SAMPRATE_IR1    80  /* 800ms */
#define SAMPRATE_IR2    16  /* 500ms */
#define SAMPRATE_GYX    40 /* 200ms */
#define SAMPRATE_GYY    40

void timer2_int_handler();

