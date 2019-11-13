#include "headfile.h"

#include "MPU_ForUser.h"		//ֻ�������ͷ�ļ�

int main(void)
{
	get_clk();
	OLED_Init();
	
	LED_P6x8Str(0,0,"Yaw=");
	LED_P6x8Str(0,1,"Pitch=");
	LED_P6x8Str(0,2,"Roll=");	
	
	MPU_Init_ForUser();		//		MPU9250��ʼ��
	
	pint_init(PINT_CH0, A3, FALLING);		//MPU9250��INT����������A3�ϣ�����Ϊ�½��ش���
	set_irq_priority(PIN_INT0_IRQn,0);//�������ȼ� Խ�����ȼ�Խ��
	enable_irq(PIN_INT0_IRQn);		//���������ж�
	
	EnableInterrupts;		//���������ж�
	while(1)		
	{
	}
}

//��MPU9250��FIFO����׼����ʱ������INT�����õͣ�����A3�����½����жϣ���ʱ�������жϷ������ڶ�ȡ���ݣ�
//��ֱ�����Ļ����԰ѿ��ƴ������������,�������ڽ���MPU9250_Config.h�ļ��ڵ�DEFAULT_MPU_HZ����
void PIN_INT0_DriverIRQHandler(void)															
{
		PINT_IST_FLAG_CLEAR(PINT_CH0);
		disable_irq(PIN_INT0_IRQn);		//��ʱ�ر��ж�

		Refresh_MPUTeam(DMP_MPL);//�ȴ����ݶ�ȡ���
		OLED_P6x8Flo(50, 0, MPU_Data.Yaw, -3);		//��ʾ
		OLED_P6x8Flo(50, 1, MPU_Data.Pitch, -3);	
		OLED_P6x8Flo(50, 2, MPU_Data.Roll, -3);
	
	/*********************������Լ��Ŀ��ƴ���**********************
	
	**************************************************************/
		
		enable_irq(PIN_INT0_IRQn);	//�����ж�
}