/*
 * io.c
 *
 *  Created on: Mar 29, 2024
 *      Author: iot00
 */

#include "main.h"
#include "io.h"

extern UART_HandleTypeDef huart3;
#define D_PRINTF_UART_HANDLE	huart3

int __io_putchar(int ch)
{
	HAL_UART_Transmit(&D_PRINTF_UART_HANDLE, (uint8_t *)&ch, 1, 0xffff);
	return ch;
}
//
//#define PORTB_BASE			0x40020400
//#define ODR_OFFSET			0x14
//
//// uint8_t aa = (uint8_t)0x12345678;
//
//void led1_on(void)
//{
//	// 0x40020414
//	*(uint32_t *)(PORTB_BASE + ODR_OFFSET) |= (0x1 << 0);
//}
//
//void led1_off(void)
//{
//	*(uint32_t *)(PORTB_BASE + ODR_OFFSET) &= ~(0x1 << 0);
//}
//
//// #include <stdbool.h>
//void led2_onoff(bool on_flag)
//{
//#define LD2_PORTB_BSRR_ADDR		0x40020418
//#define LD2_BIT							7
//
//	uint32_t bsrr_addr = LD2_PORTB_BSRR_ADDR;
//	uint32_t bit = on_flag ? (0x1<<LD2_BIT) : (0x1<<(16+LD2_BIT));
//
//	*(uint32_t *)bsrr_addr = bit;
//}

typedef struct {
	uint32_t bsrr_addr;
	uint16_t on, off;
} LED_T;

#define LED_MAX			3
const LED_T gLedObjs[LED_MAX] = {
	{	0x40020418, 	0, 		16+0 		},
	{	0x40020418,	7,	 	16+7		},
	{	0x40020418,	14,		16+14	}
};

bool led_onoff(uint8_t led_no, bool flag)
{
	if (led_no > LED_MAX) return false;
	*(uint32_t *)gLedObjs[led_no].bsrr_addr = flag ? (0x1 << gLedObjs[led_no].on) : (0x1 << gLedObjs[led_no].off);
	return true;
}

bool led_onoff_2(uint8_t led_no, bool flag)
{
	LED_T *p;
	if (led_no > LED_MAX) return false;
	p = (LED_T *)&gLedObjs[led_no];
	*(uint32_t *)p->bsrr_addr = flag ? (0x1 << p->on) : (0x1 << p->off);
	return true;
}
