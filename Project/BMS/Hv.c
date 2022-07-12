#include "Hv.h"

void Hv_Init(void)					//高压模块初始化
{

}
char Hv_Get(int object)				//获取电压值
{
	if(object == 0)					//0:BAT电压值
		return Get_V.BAT_Voltage;	//返回获取的BAT电压值

	if(object == 1)					//1:V1电压值
		return Get_V.V1_Voltage;	//返回获取的V1电压值
}