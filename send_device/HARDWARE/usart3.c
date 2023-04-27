#include "usart3.h"
#include <stdarg.h>
#include <string.h>
#include <stdio.h>
#include "delay.h"
void USART3_Init(unsigned int baud)
{

	GPIO_InitTypeDef gpio_initstruct;
	USART_InitTypeDef usart_initstruct;
	NVIC_InitTypeDef nvic_initstruct;
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART3, ENABLE);
	
	//PB10	TXD
	gpio_initstruct.GPIO_Mode = GPIO_Mode_AF_PP;
	gpio_initstruct.GPIO_Pin = GPIO_Pin_10;
	gpio_initstruct.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOB, &gpio_initstruct);
	
	//PB11	RXD
	gpio_initstruct.GPIO_Mode = GPIO_Mode_IN_FLOATING;
	gpio_initstruct.GPIO_Pin = GPIO_Pin_11;
	gpio_initstruct.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOB, &gpio_initstruct);
	
	usart_initstruct.USART_BaudRate = baud;
	usart_initstruct.USART_HardwareFlowControl = USART_HardwareFlowControl_None;		//无硬件流控
	usart_initstruct.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;						//接收和发送
	usart_initstruct.USART_Parity = USART_Parity_No;									//无校验
	usart_initstruct.USART_StopBits = USART_StopBits_1;								//1位停止位
	usart_initstruct.USART_WordLength = USART_WordLength_8b;							//8位数据位
	USART_Init(USART3, &usart_initstruct);
	
	USART_Cmd(USART3, ENABLE);														//使能串口
	
	USART_ITConfig(USART3, USART_IT_RXNE, ENABLE);									//使能接收中断
	
	nvic_initstruct.NVIC_IRQChannel = USART3_IRQn;
	nvic_initstruct.NVIC_IRQChannelCmd = ENABLE;
	nvic_initstruct.NVIC_IRQChannelPreemptionPriority = 0;
	nvic_initstruct.NVIC_IRQChannelSubPriority = 0;
	NVIC_Init(&nvic_initstruct);

}

u8 zihbee_return;

u8 tem,hum;
u32 light_intensity;
u8 zigbee_receiove_buf[100];
u8 zigbee_buf[20];
u8 zigbee_son_flag_1=0,zigbee_receive_len=0;
void zigbee_send_son(void)
	 {
	 u16 i,j,len=2;
	zigbee_buf[0]=0xFC;
	zigbee_buf[len++]=0x02;
	zigbee_buf[len++]=0x01; 
		 
	  zigbee_buf[len++]=0xbb;
		zigbee_buf[len++]=tem;
		zigbee_buf[len++]=hum;		 		 
		 zigbee_buf[len++]=light_intensity>>8;
		 zigbee_buf[len++]=light_intensity;
     zigbee_buf[len++]=zihbee_return;
		 zigbee_buf[len++]=0xbb;
     zigbee_buf[1]=len-2;
 	for(j=0;j<len;j++)//循环发送数据
	{
	  while(USART_GetFlagStatus(USART3,USART_FLAG_TC)==RESET);  //等待上次传输完成 
		USART_SendData(USART3,zigbee_buf[j]); 	 //发送数据到串口3 
	}

}

void zigbee_send_son_RST(void)
	 { 
u8 j;		 
	zigbee_buf[0]=0xFD;
	zigbee_buf[1]=0x01;
	zigbee_buf[2]=0x12; 
		 
	zigbee_buf[3]=0xff;
 	for(j=0;j<4;j++)//循环发送数据
	{
	  while(USART_GetFlagStatus(USART3,USART_FLAG_TC)==RESET);  //等待上次传输完成 
		USART_SendData(USART3,zigbee_buf[j]); 	 //发送数据到串口3 
	}		
	zigbee_buf[0]=0xFe;
	zigbee_buf[1]=0x01;
	zigbee_buf[2]=0xfe;
	zigbee_buf[3]=0xFf;
 	for(j=0;j<4;j++)//循环发送数据
	{
	  while(USART_GetFlagStatus(USART3,USART_FLAG_TC)==RESET);  //等待上次传输完成 
		USART_SendData(USART3,zigbee_buf[j]); 	 //发送数据到串口3 
	}
		delay_ms(5000);
	 }

//void USART3_IRQHandler(void)
//{
//	u8 res;	    
//	if(USART_GetITStatus(USART3, USART_IT_RXNE) != RESET)//接收到数据
//	{	 
//	   res =USART_ReceiveData(USART3);	
//	}
//}

	