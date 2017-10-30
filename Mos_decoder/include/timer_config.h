/*
 * timer_config.h
 *
 *  Created on: 2017. 8. 31.
 *      Author: student
 */

#ifndef TIMER_CONFIG_H_
#define TIMER_CONFIG_H_

TIM_HandleTypeDef TimHandle;
TIM_HandleTypeDef TimHandle1;
TIM_HandleTypeDef TimHandle2;
TIM_OC_InitTypeDef TIM_OC_Init;

extern int word;
extern char sent[40];
extern char MOS[30];
extern unsigned char motor;
extern int length;
void TIMER_Config(void)
{
	__HAL_RCC_TIM2_CLK_ENABLE();
	__HAL_RCC_TIM3_CLK_ENABLE();
	__HAL_RCC_TIM5_CLK_ENABLE();


	TimHandle.Instance			= TIM2;
	TimHandle.Init.Period		= 100 - 1;
	TimHandle.Init.Prescaler	= 840000;
	TimHandle.Init.ClockDivision= TIM_CLOCKDIVISION_DIV1;
	TimHandle.Init.CounterMode	= TIM_COUNTERMODE_UP;
	HAL_TIM_Base_Init(&TimHandle);

	TimHandle1.Instance 			= TIM3;
	TimHandle1.Init.Period 			= 100 - 1;
	TimHandle1.Init.Prescaler 		= 840000;
	TimHandle1.Init.ClockDivision	= TIM_CLOCKDIVISION_DIV1;
	TimHandle1.Init.CounterMode 	= TIM_COUNTERMODE_UP;
	HAL_TIM_Base_Init(&TimHandle1);

	HAL_NVIC_SetPriority(TIM2_IRQn,7,0);
	HAL_NVIC_EnableIRQ(TIM2_IRQn);
	HAL_NVIC_SetPriority(TIM3_IRQn,8,0);
	HAL_NVIC_EnableIRQ(TIM3_IRQn);
}

int i = 0;

void  HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)
{
	if(htim->Instance == TIM2){
		count++;
	}
	else if(htim->Instance == TIM3){
		finish++;
	}

	if(finish == 150){//문장 구분
		sent[word] = '\0';
		Commeds_board();
		i = 0;
		HAL_TIM_Base_Stop_IT(&TimHandle1);
	}
	if(finish == 70){// 단어 구분
		sent[word] = MOS[0];
		word++;
		for(;i<word;i++){
			CLCD_write(1,sent[i]);
		}
	}
	if(finish == 30){
		sent[word] = MOS[match];
		word++;
		match = 1;
	}
}

/*명령어를 추가하고싶다면 이부분에 작성*/
void Commeds_board(void)//명령어 제어 함수
{
	if (!strcmp(sent,"m on "))
		motor = 1;
	if (!strcmp(sent,"m off "))
		motor = 0;


	for (i = 0; i < word; i++) {
		sent[i] = '\0';
	}
	word = 0;
}


#endif /* TIMER_CONFIG_H_ */
