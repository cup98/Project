#include "derivative.h"

void PIT_Init(void)
{
	PIT0_Init();
	PIT1_Init();
}

int PIT0_Init(void)								//初始化PIT，利用8位基准0和16位定时器0通道
{
	PITCFLMT_PITE = 0;							//关闭PIT PITTF标志位清零
	PITCE_PCE0 = 1;								//开启16位定时器0通道
	PITMUX = 0;									//16位定时器全部连接到8位基准0通道
	PITMTLD0 = 250 - 1;
	PITLD0 = 64000 - 1;							//fBUS=32MHz;T=(PITMTLD0+1)*(PITLD0+1)/fBUS = 500ms
	PITINTE_PINTE0 = 1;							//开启16位定时器0中断
	PITCFLMT_PITE = 1;
}

int PIT1_Init(void)								//初始化PIT，利用8位基准0和16位定时器0通道
{
	PITCFLMT_PITE = 0;							//关闭PIT PITTF标志位清零
	PITCE_PCE1 = 1;								//开启16位定时器1通道
	PITMUX = 0;									//16位定时器全部连接到8位基准0通道
	PITMTLD0 = 250 - 1;
	PITLD1 = 38400 - 1;							//fBUS=32MHz;T=(PITMTLD0+1)*(PITLD0+1)/fBUS = 500ms
	PITCFLMT_PITE = 0;
}

#pragma CODE_SEG __NEAR_SEG NON_BANKED

void interrupt VectorNumber_Vpit0 PIT0(void)	//中断服务函数
{
    PITTF_PTF0 = 1;
    //CAN1_MsgData();					//PIT0中断
    CAN1_GetToOut();
}

#pragma CODE_SEG DEFAULT

#pragma CODE_SEG __NEAR_SEG NON_BANKED

void interrupt VectorNumber_Vpit1 PIT1(void)	//中断服务函数
{
    PITTF_PTF1 = 1;
    Time_Flag();						//PIT1中断
    CAN1_MsgCPLT();
}

#pragma CODE_SEG DEFAULT
