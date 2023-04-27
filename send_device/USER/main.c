#include "delay.h"
#include "sys.h"
#include "usart.h"
#include "string.h" 
#include "myiic.h"
#include "bh1750.h"
#include "adc.h"
#include "math.h"
#include "dht11.h"
#include "stdlib.h"
#include "oled.h"
#include "bmp.h"
//����һЩ��������
u8 zihbee_return;
u8 data_temp,data_hum;
u32 light_intensity;
u8 zigbee_receiove_buf[100];
u8 zigbee_buf[20];
u8 zigbee_son_flag_1=0,zigbee_receive_len=0;
//���ݴ������
void zigbee_send_son(void)
	 {
	 u16 i,j,len=2;
	zigbee_buf[0]=0xFC;
	zigbee_buf[len++]=0x02; //len=3
	zigbee_buf[len++]=0x01; //len=4
		 
	  zigbee_buf[len++]=0xbb;
		zigbee_buf[len++]=data_temp;
		zigbee_buf[len++]=data_hum;		 		 
		 zigbee_buf[len++]=light_intensity>>8;
		 zigbee_buf[len++]=light_intensity;
     zigbee_buf[len++]=zihbee_return;
		 zigbee_buf[len++]=0xbb;
     zigbee_buf[1]=len-2;
 	for(j=0;j<len;j++)//ѭ����������
	{
	  while(USART_GetFlagStatus(USART1,USART_FLAG_TC)==RESET);  //�ȴ��ϴδ������ 
		USART_SendData(USART1,zigbee_buf[j]); 	 //�������ݵ�����1
	}

}
int main(void)
{		
//	u8 data_hum,data_temp;
  NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
 	delay_init();	    	 //��ʱ������ʼ��	  
	uart_init(9600);	
	OLED_Init();
	OLED_Clear();
	bh1750_iic_init();//��ʼ��BH1750
	while(DHT11_Init())
	{;}
	while(1){	
		//��ʾʪ��ֵ
		delay_ms(200);
		data_hum=DHT11_Read_hum();
		OLED_ShowString(80,6,"HUM");
		OLED_ShowNum(103,6,data_hum,3,16);
		//��ʾ�¶�ֵ
		delay_ms(200);
		data_temp=DHT11_Read_temp();
		OLED_ShowString(80,4,"TMP");
		OLED_ShowNum(103,4,data_temp,3,16);
		//��ʾBH1750��ֵ
		OLED_ShowString(76,2,"LUX");
		OLED_ShowNum(103,2,Conversion(),3,16);
		delay_ms(1000);
		light_intensity=Conversion();
		//��������
//		printf("%d %d %f\r\n",data_hum,data_temp,Conversion());
		zigbee_send_son();
		
	}	
 }
