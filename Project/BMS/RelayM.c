#include "RelayM.h"

void RelayM_Init(void)								//继电器模块初始化
{

}

void RelayM_Control(int object ,int state)			//继电器控制函数
{
	if(object == 0)									//object=0，选中预充继电器
		ReM_Ct.Master_ReM  = state;					//把state赋值给选中目标,statey,0:断开,1:闭合
	if(object == 1)									//object=1，选中总正继电器
		ReM_Ct.Precharge_ReM = state;				//把state赋值给选中目标
}

void RelayM_Change(int object ,unsigned int state)	//继电器切换函数
{
	if(object == 0)									//object=0，选中预充继电器
		Switch_Ct.Master_Sw  = state;				//把state赋值给选中目标
	if(object == 1)									//object=1，选中总正继电器
		Switch_Ct.Precharge_Sw = state;				//把state赋值给选中目标
}
