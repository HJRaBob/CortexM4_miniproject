/*
 * Uart_Config.h
 *
 *  Created on: 2017. 9. 6.
 *      Author: student
 */

#ifndef UART_CONFIG_H_
#define UART_CONFIG_H_

UART_HandleTypeDef UartHandle;
extern TIM_HandleTypeDef TimHandle2;

#define RxBufferSize	 0xFF
uint8_t RxBuffer[RxBufferSize];

uint8_t reset = 0;
extern int finish;
extern char sent[40];
extern int word;
extern int tim;
int j=0;
int boz = 0;
int asci=0;

void UART_config(void)
{
	__HAL_RCC_GPIOA_CLK_ENABLE();
	__HAL_RCC_USART2_CLK_ENABLE();

	GPIO_Init_Struct.Pin		= GPIO_PIN_2|GPIO_PIN_3;
	GPIO_Init_Struct.Mode		= GPIO_MODE_AF_PP;
	GPIO_Init_Struct.Pull		= GPIO_NOPULL;
	GPIO_Init_Struct.Speed		= GPIO_SPEED_FREQ_VERY_HIGH;
	GPIO_Init_Struct.Alternate	= GPIO_AF7_USART2;
	HAL_GPIO_Init(GPIOA,&GPIO_Init_Struct);

	UartHandle.Instance			= USART2;
	UartHandle.Init.BaudRate	= 9600;
	UartHandle.Init.WordLength	= UART_WORDLENGTH_8B;
	UartHandle.Init.StopBits	= UART_STOPBITS_1;
	UartHandle.Init.Parity		= UART_PARITY_NONE;
	UartHandle.Init.HwFlowCtl	= UART_HWCONTROL_NONE;
	UartHandle.Init.Mode		= UART_MODE_TX_RX;
	UartHandle.Init.OverSampling= UART_OVERSAMPLING_16;

	HAL_UART_Init(&UartHandle);

	HAL_NVIC_SetPriority(USART2_IRQn,4,0);
	HAL_NVIC_EnableIRQ(USART2_IRQn);

	HAL_UART_Receive_IT(&UartHandle,(uint8_t*)RxBuffer,1);
}

unsigned int k = 0;

void transmit(char input)
{
	sent[word]  = input;
	CLCD_write(1,sent[word]);
	asci = c_trans(sent[word]);
	for(j=0;j<tim;j++){
		boz = (asci>>(j*4))&0x01;
		if(boz == 1){
			line_sig();
		}else{
			dot_sig();
		}
		for (k = 1400000; k >= 1; k--);
	}
	word++;
}


void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart)
{
	if(reset||finish == 150){
		CLCD_write(0,0x01);
		reset = 0;
		finish = 0;
	}
	if(*RxBuffer == '.'){
		sent[word] = ' ';
		CLCD_write(1,sent[word]);
		word++;
		sent[word] = '\0';
		Commeds_board();
		reset = 1;
	}else{
		transmit(*RxBuffer);
	}

	HAL_UART_Receive_IT(&UartHandle,(uint8_t*)RxBuffer,1);
}


#endif /* UART_CONFIG_H_ */
