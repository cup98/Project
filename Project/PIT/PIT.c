#include "PIT.h"

void PIT_Init(void)
{
	PIT0_Init();
//	PIT1_Init();
}

void PIT0_Init(void)							//初始化PIT，利用8位基准0和16位定时器0通道
{
	PITCFLMT_PITE = 0;							//关闭PIT PITTF标志位清零
	PITCE_PCE0 = 1;								//开启16位定时器0通道
	PITMUX = 0;									//16位定时器全部连接到8位基准0通道
	PITMTLD0 = 250 - 1;
	PITLD0 = 64000 - 1;							//fBUS=32MHz;T=(PITMTLD0+1)*(PITLD0+1)/fBUS = 500ms
	PITINTE_PINTE0 = 1;							//开启16位定时器0中断
	PITCFLMT_PITE = 1;
}

void PIT1_Init(void)							//初始化PIT，利用8位基准0和16位定时器0通道
{
	PITCFLMT_PITE = 0;							//关闭PIT PITTF标志位清零
	PITCE_PCE1 = 1;								//开启16位定时器1通道
	PITMUX = 0;									//16位定时器全部连接到8位基准0通道
	PITMTLD0 = 250 - 1;
	PITLD1 = 38400 - 1;							//fBUS=32MHz;T=(PITMTLD0+1)*(PITLD0+1)/fBUS = 500ms
	PITCFLMT_PITE = 0;
}

