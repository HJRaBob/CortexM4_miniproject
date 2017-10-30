/*
 * ledconfig.h
 *
 *  Created on: 2017. 8. 25.
 *      Author: student
 */

#ifndef LEDCONFIG_H_
#define LEDCONFIG_H_

#include "stm32f4xx_hal.h"
//#include "stm32f4xx_hal_rcc.h"
//#include "stm32f4xx_hal_gpio.h"

GPIO_InitTypeDef LED;
GPIO_InitTypeDef DCMotor;

void LED_Config(uint16_t GPIO_Pin) //use LED getting Pin number
{
	//포트의 CLK를 확인해서 클락공급을 할지 말지 결정하게 수정 필요
	__HAL_RCC_GPIOA_CLK_ENABLE();

	LED.Pin 	 = GPIO_Pin;
	LED.Mode	 = GPIO_MODE_OUTPUT_PP;
	LED.Pull	 = GPIO_NOPULL;
	LED.Speed	 = GPIO_SPEED_HIGH;
	HAL_GPIO_Init(GPIOA,&LED);
}

void DCMotor_Config(void) //use motor
{
	//포트의 CLK를 확인해서 클락공급을 할지 말지 결정하게 수정 필요
	__HAL_RCC_GPIOA_CLK_ENABLE();
	__HAL_RCC_GPIOB_CLK_ENABLE();

	//PWM 설정
	DCMotor.Pin 	 = GPIO_PIN_6;
	DCMotor.Mode	 = GPIO_MODE_OUTPUT_PP;
	DCMotor.Pull	 = GPIO_NOPULL;
	DCMotor.Speed	 = GPIO_SPEED_HIGH;
	HAL_GPIO_Init(GPIOA,&DCMotor);

	//방향 핀 설정
	DCMotor.Pin 	 = GPIO_PIN_6|GPIO_PIN_7;
	DCMotor.Mode	 = GPIO_MODE_OUTPUT_PP;
	DCMotor.Pull	 = GPIO_NOPULL;
	DCMotor.Speed	 = GPIO_SPEED_HIGH;
	HAL_GPIO_Init(GPIOB,&DCMotor);
}

void DCMotor_Control(unsigned int mode)//0:short break 1: CCW 2: CW operate
{
	HAL_GPIO_WritePin(GPIOA,GPIO_PIN_6,1); //PWM 고정
	switch(mode){
	case 0 : //short break
		HAL_GPIO_WritePin(GPIOB,GPIO_PIN_6,1);
		HAL_GPIO_WritePin(GPIOB,GPIO_PIN_7,1);
		break;
	case 1 : //CCW
		HAL_GPIO_WritePin(GPIOB,GPIO_PIN_6,0);
		HAL_GPIO_WritePin(GPIOB,GPIO_PIN_7,1);
		break;
	case 2 : //CW
		HAL_GPIO_WritePin(GPIOB,GPIO_PIN_6,1);
		HAL_GPIO_WritePin(GPIOB,GPIO_PIN_7,0);
		break;
	}
}

#endif /* LEDCONFIG_H_ */
