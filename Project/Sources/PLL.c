#include "PLL.h"

void PLL_Init(void)
{
	CLKSEL_PLLSEL = 0;			//将晶振时钟设置为总线时钟
	PLLCTL_PLLON = 0;			//关PLL
	SYNR = 0x47;				//VCOFRQ[1:0]=1;STNDDIV[5:0]=7
	REFDV = 0x41;				//REFFRQ[1:0]=1;REFDIV[5:0]=1
	POSTDIV = 0x00;				//fOSC=8MHz;fVCO=64MHz;fPLL=32MHz
	PLLCTL_PLLON = 1;			//开PLL
	_asm(nop);
	_asm(nop);              	//等待连两个机器周期
	while(CRGFLG_LOCK == 0)		//等待PLL配置稳定
	{

	}
	CLKSEL_PLLSEL = 1;			//将PLL时钟设置为时钟源
}