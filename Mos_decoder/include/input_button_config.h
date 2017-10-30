/*
 * input_button_config.h
 *
 *  Created on: 2017. 9. 5.
 *      Author: student
 */

#ifndef INPUT_BUTTON_CONFIG_H_
#define INPUT_BUTTON_CONFIG_H_

GPIO_InitTypeDef BUTTON;
extern TIM_HandleTypeDef TimHandle;
extern TIM_HandleTypeDef TimHandle1;
extern int finish;
extern int count;
extern unsigned char match;
extern uint8_t reset;


void Button_Config(void)
{
	__HAL_RCC_GPIOA_CLK_ENABLE();

	BUTTON.Pin	= GPIO_PIN_8|GPIO_PIN_11|GPIO_PIN_12;
	BUTTON.Mode	= GPIO_MODE_IT_RISING_FALLING;
	BUTTON.Pull	= GPIO_NOPULL;
	BUTTON.Speed	= GPIO_SPEED_LOW;
	HAL_GPIO_Init(GPIOA,&BUTTON);

	HAL_NVIC_SetPriority(EXTI9_5_IRQn,2,0);
	HAL_NVIC_SetPriority(EXTI15_10_IRQn,3,0);

	HAL_NVIC_EnableIRQ(EXTI9_5_IRQn);
	HAL_NVIC_EnableIRQ(EXTI15_10_IRQn);
}

unsigned char edge_check =0; //rising, falling edge 측정 함수

void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin)
{

	if(!edge_check){
		if(finish == 150||reset){// 새 문장시 CLCD 리셋
			CLCD_write(0,0x01);
			reset = 0;
		}
		finish = 0;
		HAL_TIM_Base_Stop_IT(&TimHandle1);
		HAL_TIM_Base_Start_IT(&TimHandle);
	}else{
		HAL_TIM_Base_Stop_IT(&TimHandle);
		HAL_TIM_Base_Start_IT(&TimHandle1);
		if (count < 10) { //점이면
			match = match<<1;
		} else if (count >= 10) { //선이면
			match = (match<<1)+1;
		}
		count = 0;
	}

	edge_check = ~edge_check;
}


#endif /* INPUT_BUTTON_CONFIG_H_ */
