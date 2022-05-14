#ifndef _LIBPIGPIO
#define _LIBPIGPIO

/* DEBUG MODE
 * 0 : debug mode disabled
 * 1 : debug mode enabled, messages will be displayed
 */
#define GPIO_DEBUG 0

/* LIBARIES */
#include <stdio.h>
#include <string.h>
#include <ctype.h>

/* DEFINES */
#define LIBPIGPIO_PATH "/sys/class/gpio/gpio"
#define LIBPIGPIO_PATH_LENGTH 50
#define LIBPIGPIO_GPIO_LENGTH 10
#define LIBPIGPIO_DIR_LENGTH 4


/* FUNCTIONS */

int libpigpio_open (char gpio [LIBPIGPIO_GPIO_LENGTH]); // error code: 1

int libpigpio_close (char gpio [LIBPIGPIO_GPIO_LENGTH]); // error code: 2

int libpigpio_write_direction (char gpio [LIBPIGPIO_GPIO_LENGTH], char direction [LIBPIGPIO_DIR_LENGTH]); // error code: 3

int libpigpio_read_direction (char gpio [LIBPIGPIO_GPIO_LENGTH], char *direction); // error code: 4

int libpigpio_init (char gpio [LIBPIGPIO_GPIO_LENGTH], char direction [LIBPIGPIO_DIR_LENGTH]);

int libpigpio_write_value (char gpio [LIBPIGPIO_GPIO_LENGTH], char value [LIBPIGPIO_DIR_LENGTH]); // error code: 5

int libpigpio_read_value (char gpio [LIBPIGPIO_GPIO_LENGTH], char *value); // error code: 6

#endif // _LIBPIGPIO