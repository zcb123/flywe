/*******************************************************************************************
										    �� ��
    ����Ŀ�����������ѧϰʹ�ã�����������ֲ�޸ģ������뱣����������Ϣ����ֲ�����г�������
	
���ɹ�����BUG��������������κ����Ρ��������ã�

* ����汾��V1.01
* �������ڣ�2018-8-18
* �������ߣ���ŭ��С��
* ��Ȩ���У��������������Ϣ�������޹�˾
*******************************************************************************************/
#include "main.h"

void System_Init(void)
{
	NvicConfig(); //ϵͳ�ж����ȼ�����
	LED_Init();	//�û�ָʾ�Ƴ�ʼ��
	Delay_Init(); //ϵͳ��ʱ��ʼ��
	USART_init(115200);	//���Դ��ڳ�ʼ��
	IIC_GPIO_Init(); //ģ��IIC��ʼ��
	TIM_Init();	//ϵͳʱ����ʼ��
//	Exit_Init(); //�ⲿ�жϳ�ʼ��
//	SI24R1_Init(); //SI24R1(2.4G)��ʼ�����죩
	MPU6050_Init(); //MPU6050��ʼ�����̣� 
//	FBM320_Init(); //FBM320��ʼ��(��ѹ����) 
//	MOTOR_Init(); //��������ʼ��
//	BATT_Init(); //��ص�ѹ����ʼ��
//	PID_ReadFlash(); //Flash�е����ݶ�ȡ
//	PidParameter_init(); //PID������ʼ��
	RGB_LED_Off();	//��ʼ���ر�����RGB��
	
	printf("System Init Finish\n");
}

void Task_Schedule(void)
{
	static int s32count= 0;
	
		if(IMU_Scan) //2.5Hz
		{
			s32count++;
			Batt_Scan = 0;
			LED_Run();
			//printf("\nSystem %d\r\n",s32count);
			Prepare_Data(); //��ȡ��̬������������
			IMUupdate(&Gyr_rad,&Acc_filt,&Att_Angle); //��Ԫ����̬����
			printf("\n%d,%f,%f,%f\r\n",s32count,Att_Angle.rol,Att_Angle.pit,Att_Angle.yaw);
			//ANO_DT_Send_Status(Att_Angle.rol,Att_Angle.pit,Att_Angle.yaw,0,0,Airplane_Enable);
		}
#if 0
	if(ANO_Scan) //500Hz
		{
			ANO_Scan = 0;
			ANO_DT_Data_Exchange(); //�������ݵ���λ��
		}
		if(IMU_Scan) //100Hz
		{
			IMU_Scan  = 0;
			Prepare_Data(); //��ȡ��̬������������
			IMUupdate(&Gyr_rad,&Acc_filt,&Att_Angle); //��Ԫ����̬����
			Control(&Att_Angle,&Gyr_rad,&RC_Control,Airplane_Enable); //��̬����
		}
		if(LED_Scan) //10Hz
		{
			LED_Scan = 0;
			LED_Run();
			if(!Airplane_Enable&&Run_flag)
			{
				RGB_LED_Runing(); //�ɻ�����״̬��
			}
			BATT_Alarm_LED(); //��ص͵�ѹ����	  
		}
		if(IRQ_Scan) //5Hz
		{
			IRQ_Scan = 0;
			SI24R1_SingalCheck(); //2.4Gͨ�ż��
			SendToRemote(); //�������ݸ�ң����
		}
		if(Batt_Scan) //2.5Hz
		{
			Batt_Scan = 0;
			SI24R1_GetAddr(); //����2.4G��ַ
			LowVoltage_Alarm();	//�͵�������
		}
#endif
}


