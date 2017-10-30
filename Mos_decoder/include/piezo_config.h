/*
 * piezo_config.h
 *
 *  Created on: 2017. 9. 7.
 *      Author: student
 */

#ifndef PIEZO_CONFIG_H_
#define PIEZO_CONFIG_H_

GPIO_InitTypeDef PIEZO;
int period;
int buf;

void Piezo_Config(void)
{
	__HAL_RCC_GPIOB_CLK_ENABLE();

	PIEZO.Pin	= GPIO_PIN_15;
	PIEZO.Mode	= GPIO_MODE_OUTPUT_PP;
	HAL_GPIO_Init(GPIOB,&PIEZO);
}

void line_sig(void) {
	for (period = 0x1000; period >= 1; period--) { //frequency is incresing
		GPIOB->ODR = 0x8000;
		buf = 1000;
		while (buf--)
			; //High value time

		GPIOB->ODR = 0x0000;
		buf = 1000;
		while (buf--)
			; //Low value time -> duty rate is same
	}
}

void dot_sig(void) {
	for (period = 0x100; period >= 1; period--) { //frequency is incresing
		GPIOB->ODR = 0x8000;
		buf = 1000;
		while (buf--)
			; //High value time

		GPIOB->ODR = 0x0000;
		buf = 1000;
		while (buf--)
			; //Low value time -> duty rate is same
	}
}

#endif /* PIEZO_CONFIG_H_ */
