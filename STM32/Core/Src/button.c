/*
 * button.c
 *
 *  Created on: Apr 11, 2024
 *      Author: IOT
 */
#include "main.h"
#include "button.h"

static void button_dummy(void *);

static BUTTON_T gBtnObjs[] = {
	{ USER_Btn_GPIO_Port, 	USER_Btn_Pin, 	80, 	0, 		0, 		0,		button_dummy, 	{ true, 	0 	}},
	{ NULL, 						0, 					0,		0,		0,		0,		NULL,					{ true, 	0	}}
};

void button_init(void)
{

}

void button_regcbf(uint16_t idx, FUNC_CBF cbf)
{
	gBtnObjs[idx].cbf = cbf;
}
