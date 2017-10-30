/*
 * This file is part of the 쨉OS++ distribution.
 *   (https://github.com/micro-os-plus)
 * Copyright (c) 2014 Liviu Ionescu.
 *
 * Permission is hereby granted, free of charge, to any person
 * obtaining a copy of this software and associated documentation
 * files (the "Software"), to deal in the Software without
 * restriction, including without limitation the rights to use,
 * copy, modify, merge, publish, distribute, sublicense, and/or
 * sell copies of the Software, and to permit persons to whom
 * the Software is furnished to do so, subject to the following
 * conditions:
 *
 * The above copyright notice and this permission notice shall be
 * included in all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
 * EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES
 * OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
 * NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT
 * HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY,
 * WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
 * FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR
 * OTHER DEALINGS IN THE SOFTWARE.
 */

// ----------------------------------------------------------------------------

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "diag/Trace.h"
#include "stm32f4xx_hal.h"
#include "CLCD_Config.h"
#include "input_button_config.h"
#include "stm32f4xx_it.h"
#include "timer_config.h"
#include "ledconfig.h"
#include "transmit.h"
#include "Uart_Config.h"
#include "piezo_config.h"

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wunused-parameter"
#pragma GCC diagnostic ignored "-Wmissing-declarations"
#pragma GCC diagnostic ignored "-Wreturn-type"

int count=0; //tim2 시간 체크 함수
int finish = 0;//tim3 시간체크 함수
unsigned char match = 0x01; //입력값에 맞는 문자 대응값
char sent[40] = {'\0',};
int word = 0;
int length = 0;
unsigned char motor = 0;

int main(int argc, char* argv[])
{
	CLCD_config();
	CLCD_init();
	Button_Config();
	TIMER_Config();
	DCMotor_Config();
	Piezo_Config();
	UART_config();

	while (1)
    {
		if (motor)
			DCMotor_Control(1);
		else
			DCMotor_Control(0);
    }
}

#pragma GCC diagnostic pop

// ----------------------------------------------------------------------------
