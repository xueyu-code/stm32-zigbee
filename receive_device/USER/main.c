#include "delay.h"
#include "sys.h"
#include "oled.h"
#include "bmp.h"
#include "usart.h"
#include "beep.h"
//����һЩ��������
extern u8 data_temp,data_hum;
extern u32 light_intensity;
 int main(void)
  {	
			  
	 NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2); 	 //����NVIC�жϷ���2:2λ��ռ���ȼ���2λ��Ӧ���ȼ� 
		uart_init(9600);
		delay_init();	    	 //��ʱ������ʼ��
	//		delay_ms(8000);
		OLED_Init();			//��ʼ��OLED  
		OLED_Clear()  	; 
		BEEP_Init();
		u8 data;
	while(1) 
	{		
//		data=data_temp;
		delay_ms(500);
//		OLED_ShowString();
		OLED_ShowString(70,6,"HUM",16);
		OLED_ShowNum(103,6,data_hum,3,16);
		OLED_ShowString(70,4,"TMP",16);
		OLED_ShowNum(103,4,data_temp,3,16);
		OLED_ShowString(70,2,"LUX",16);
		OLED_ShowNum(103,2,light_intensity,3,16);
//		if(data_hum>60)
//			BEEP_ON();

	
}
	}
