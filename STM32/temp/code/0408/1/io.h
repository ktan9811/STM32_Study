/*
 * io.h
 *
 *  Created on: Mar 29, 2024
 *      Author: iot00
 */

#ifndef SRC_IO_H_
#define SRC_IO_H_

#include <stdbool.h>

#ifdef __cplusplus
extern "C" {
#endif

int __io_putchar(int ch);
//void led1_on(void);
//void led1_off(void);
//void led2_onoff(bool on_flag);

bool led_onoff(uint8_t led_no, bool flag);
bool led_onoff_2(uint8_t led_no, bool flag);

#ifdef __cplusplus
}
#endif

#endif /* SRC_IO_H_ */
