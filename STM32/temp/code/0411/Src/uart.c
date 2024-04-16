/*
 * uart.c
 *
 *  Created on: Apr 11, 2024
 *      Author: iot00
 */
#include <stdbool.h>
#include <stdio.h>
#include "uart.h"

extern UART_HandleTypeDef huart3;

static uint8_t rxd;
static bool rxd_flag = false;

//#define D_BUF_MAX	100
//typedef struct {
//  uint8_t buf[D_BUF_MAX+1];
//  uint8_t idx;
//  uint8_t flag;
//} BUF_T;
//
//static BUF_T gBufObjs[3];

void uart_init(void)
{
	HAL_UART_Receive_IT(&huart3, (uint8_t *)&rxd, 1);
}

void uart_thread(void *arg)
{
	if (rxd_flag == true) {
		rxd_flag = false;
		printf("rxd:%c\r\n", rxd);
	}
}

void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart)
{
	rxd_flag = true;
	HAL_UART_Receive_IT(&huart3, (uint8_t *)&rxd, 1);
}
