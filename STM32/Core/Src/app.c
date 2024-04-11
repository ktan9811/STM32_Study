/*
 * app.c
 *
 *  Created on: Apr 11, 2024
 *      Author: IOT
 */
#include "main.h"
#include "button.h"
#include "app.h"

void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin)
{
  /* Prevent unused argument(s) compilation warning */
  //UNUSED(GPIO_Pin);
  HAL_GPIO_TogglePin(LD1_GPIO_Port, LD1_Pin);
  /* NOTE: This function Should not be modified, when the callback is needed,
           the HAL_GPIO_EXTI_Callback could be implemented in the user file
   */
}
void button_callback(void *arg)
{
	HAL_GPIO_TogglePin(LD1_GPIO_Port, LD1_Pin);
}

typedef struct {
	uint32_t period, count;
	bool flag;
	void (*cbf)(void);
} THR_T; // thread type

volatile THR_T gThrObjs[]  = {
	{ .period = 1, 		.cbf = NULL	},
	{ .period = 500, 	.cbf = NULL		},
	{ .cbf = NULL			}
};

static void init(void){
	button_regcbf(0, button_callback);
}

void app(void){
	init();
	while(1){
		// Check Thread
		{
			if (gThrObjs[thr_idx].flag == true) {						// if flag True -> exe
						gThrObjs[thr_idx].flag = false;
						gThrObjs[thr_idx].cbf();
			}

			thr_idx++;
			if (gThrObjs[thr_idx].cbf == NULL) thr_idx = 0;
		}

	}
}
