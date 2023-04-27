#ifndef __USART2_H
#define __USART2_H
#include "stdio.h"	
#include "sys.h" 
#define USART_DEBUG		USART1		//调试打印所使用的串口组
void USART3_Init(unsigned int baud);

void Usart_SendString( unsigned char *str, unsigned short len);
void zigbee_send_son(void);
void zigbee_send_son_RST(void);
void UsartPrintf(USART_TypeDef *USARTx, char *fmt,...);
#endif


