/*
 * uart.c
 *
 *  Created on: Apr 11, 2024
 *      Author: iot00
 */
#include <stdbool.h>
#include <stdio.h>
#include "uart.h"

extern UART_HandleTypeDef huart2;		// idx = 0
extern UART_HandleTypeDef huart3;		// idx = 1

#define D_BUF_OBJ_MAX	3
static uint8_t rxdata[D_BUF_OBJ_MAX];
static BUF_T gBufObjs[D_BUF_OBJ_MAX];

//static void (*uart_cbf[D_BUF_OBJ_MAX])(void *);
//typedef void (*UART_CBF)(void *);
static UART_CBF uart_cbf[D_BUF_OBJ_MAX];

void uart_init(void)
{
	for (int i=0; i<D_BUF_OBJ_MAX; i++) {
		gBufObjs[i].idx = 0;
		gBufObjs[i].flag = false;
	}

	// 인터럽트 방식 수신 시작 : 1바이트
	HAL_UART_Receive_IT(&huart2, (uint8_t *)&rxdata[E_UART_0], 1); // uart 2
	HAL_UART_Receive_IT(&huart3, (uint8_t *)&rxdata[E_UART_1], 1);	// uart 3
}

bool uart_regcbf(uint8_t idx, UART_CBF cbf)
{
	if (idx > D_BUF_OBJ_MAX) return false;
	uart_cbf[idx] = cbf;
	return true;
}

//void uart_thread(void *arg)
//{
//	for (int i=0; i<D_BUF_OBJ_MAX; i++) {
//		if (gBufObjs[i].flag == true) {
//			if (uart_cbf != NULL) uart_cbf((void *)&gBufObjs[i]);
//			gBufObjs[i].idx = 0;
//			gBufObjs[i].flag = false;
//		}
//	}
//}

// 인터럽트 서비스 루틴 (ISR)
void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart)
{
	volatile uint8_t rxd;

	if (huart == &huart2) {	// idx = 0
		rxd = rxdata[E_UART_0];
		HAL_UART_Receive_IT(huart, (uint8_t *)&rxdata[E_UART_0], 1);

		if (uart_cbf[0] != NULL) uart_cbf[E_UART_0]((void *)&gBufObjs[E_UART_0]);
	}

	if (huart == &huart3) { // idx = 1
		rxd = rxdata[E_UART_1];
		HAL_UART_Receive_IT(huart, (uint8_t *)&rxdata[E_UART_1], 1);

		BUF_T *p = (BUF_T *)&gBufObjs[E_UART_1];
		if (p->flag == false) {
			p->buf[p->idx] = rxd;
			//p->idx++;
			//p->idx %= D_BUF_MAX;
			if (p->idx < D_BUF_MAX) p->idx++;

			if (rxd == '\r' || rxd == '\n') {
				p->buf[p->idx] = 0; //'\0';
				p->flag = true;
				if (uart_cbf[1] != NULL) uart_cbf[1]((void *)&gBufObjs[E_UART_1]);
				p->idx = 0;
				p->flag = false;
			}
		}
	}
}
