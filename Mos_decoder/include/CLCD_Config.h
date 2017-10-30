/*
 * CLCD_Config.h
 *
 *  Created on: 2017. 8. 31.
 *      Author: student
 */

#ifndef CLCD_CONFIG_H_
#define CLCD_CONFIG_H_

GPIO_InitTypeDef  GPIO_Init_Struct;	// GPIO의 초기화를 위한 구조체형의 변수를 선언

/*지연루틴*/
void ms_delay_int_count(volatile unsigned int nTime)
{
	nTime = (nTime * 14000);
	for(; nTime > 0; nTime--);
}

void us_delay_int_count(volatile unsigned int nTime)
{
	nTime = (nTime * 12);
	for(; nTime > 0; nTime--);
}

// -- CLCD의 초기설정용 함수의 선언
void CLCD_config()
{
	//  CLCD용 GPIO (GPIOC)의 초기설정을 함
	__HAL_RCC_GPIOC_CLK_ENABLE();

	// CLCD_RS(PC8), CLCD_E(PC9, DATA 4~5(PC12~15)
	GPIO_Init_Struct.Pin = GPIO_PIN_8 | GPIO_PIN_9 | GPIO_PIN_12 | GPIO_PIN_13 | GPIO_PIN_14 | GPIO_PIN_15;
	GPIO_Init_Struct.Mode = GPIO_MODE_OUTPUT_PP;
	GPIO_Init_Struct.Pull = GPIO_NOPULL;
	GPIO_Init_Struct.Speed = GPIO_SPEED_FAST;
	HAL_GPIO_Init(GPIOC, &GPIO_Init_Struct);

	HAL_GPIO_WritePin(GPIOC, GPIO_PIN_9, GPIO_PIN_RESET);	// CLCD_E = 0
	HAL_GPIO_WritePin(GPIOC, GPIO_PIN_8, GPIO_PIN_RESET);	// CLCD_RW = 0
}

void CLCD_write(unsigned char rs, char data)
{
	HAL_GPIO_WritePin(GPIOC, GPIO_PIN_8, rs);				// CLCD_RS
	HAL_GPIO_WritePin(GPIOC, GPIO_PIN_9, GPIO_PIN_RESET);	// CLCD_E = 0
	us_delay_int_count(2);

	HAL_GPIO_WritePin(GPIOC, GPIO_PIN_12, (data>>4) & 0x1);	// CLCD_DATA = LOW_bit
	HAL_GPIO_WritePin(GPIOC, GPIO_PIN_13, (data>>5) & 0x1);
	HAL_GPIO_WritePin(GPIOC, GPIO_PIN_14, (data>>6) & 0x1);
	HAL_GPIO_WritePin(GPIOC, GPIO_PIN_15, (data>>7) & 0x1);

	HAL_GPIO_WritePin(GPIOC, GPIO_PIN_9, GPIO_PIN_SET);		// CLCD_E = 1
	us_delay_int_count(2);
	HAL_GPIO_WritePin(GPIOC, GPIO_PIN_9, GPIO_PIN_RESET);	// CLCD_E = 0
	us_delay_int_count(2);

	HAL_GPIO_WritePin(GPIOC, GPIO_PIN_12, (data>>0) & 0x1);	// CLCD_DATA = HIGH_bit
	HAL_GPIO_WritePin(GPIOC, GPIO_PIN_13, (data>>1) & 0x1);
	HAL_GPIO_WritePin(GPIOC, GPIO_PIN_14, (data>>2) & 0x1);
	HAL_GPIO_WritePin(GPIOC, GPIO_PIN_15, (data>>3) & 0x1);

	HAL_GPIO_WritePin(GPIOC, GPIO_PIN_9, GPIO_PIN_SET);		// CLCD_E = 1
	us_delay_int_count(2);
	HAL_GPIO_WritePin(GPIOC, GPIO_PIN_9, GPIO_PIN_RESET);	// CLCD_E = 0
	ms_delay_int_count(2);
}

void CLCD_init()
{
	HAL_GPIO_WritePin(GPIOC, GPIO_PIN_9, GPIO_PIN_RESET);	// CLCD_E = 0
	CLCD_write(0, 0x33);	// 4비트 설정 특수 명령
	CLCD_write(0, 0x32);	// 4비트 설정 특수 명령
	CLCD_write(0, 0x28);	// _set_function
	CLCD_write(0, 0x0F);	// _set_display
	CLCD_write(0, 0x01);	// clcd_clear
	CLCD_write(0, 0x06);	// _set_entry_mode
	CLCD_write(0, 0x02);	// Return home
}

void CLCD_String(const char* str)
{
	CLCD_write(0,0x01);
	while(*str){
		CLCD_write(1,*str);
		str++;
	}
}


#endif /* CLCD_CONFIG_H_ */
