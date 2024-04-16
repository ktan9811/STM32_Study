/*
 * app.c
 *
 *  Created on: Apr 8, 2024
 *      Author: iot00
 */
#include <stdbool.h>
#include <stdio.h>
#include "button.h"
#include "main.h"

void button_callback(void *arg);
void button_callback_2(void *arg);

void button_callback_2(void *arg)
{
	static uint8_t count = 0;

	BUTTON_STS *pSts = (BUTTON_STS *)arg;

	if (pSts->edge == true) printf("rising\r\n");
	else if (pSts->edge == false) {
		printf("falling : period = %d\r\n", pSts->pushed_count);
	}

	printf("2.count = %d\r\n", count);
	count++;
	count %= 10;
	if (count == 0) {
		button_regcbf(0, button_callback);
		printf("cbf changed to callback\r\n");
	}
}
void button_callback(void *arg)
{
	static uint8_t count = 0;

	BUTTON_STS *pSts = (BUTTON_STS *)arg;

	if (pSts->edge == true) printf("rising\r\n");
	else if (pSts->edge == false) {
		printf("falling : period = %d\r\n", pSts->pushed_count);
	}

	printf("1.count = %d\r\n", count);
	count++;
	count %= 10;
	if (count == 0) {
		button_regcbf(0, button_callback_2);
		printf("cbf changed to callback_2\r\n");
	}
}

void app(void)
{
	uint32_t tick_prev, tick_curr;

	button_init();
	button_regcbf(0, button_callback);

	tick_prev = tick_curr = HAL_GetTick();
	while (1) {
		tick_curr = HAL_GetTick();
		if (tick_curr - tick_prev >= 1) {
			button_check();
			tick_prev = tick_curr;
		}
	}
}


#if 0
#define bsp_delay(x)			HAL_Delay(x)

bool bsp_read_btn1(void)
{
	return HAL_GPIO_ReadPin(USER_Btn_GPIO_Port, USER_Btn_Pin) == GPIO_PIN_SET ? true : false;
}

void app(void)
{
	bool sts;

	HAL_Delay(1);
	printf("System Started...\r\n");

	while (1) {
		bsp_delay(200);

		sts = bsp_read_btn1();
		if (sts == true) printf("Blue button Pushed\r\n");
	}
}

#endif
