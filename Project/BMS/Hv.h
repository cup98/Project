#ifndef __HV_H
#define __HV_H

#include "hidef.h"
#include "derivative.h"

/*typedef enum _Get_Object
{
	BAT,
	V1,
} Get_Object;*/

typedef struct _Get_Voltage			//构建电压值结构体
{
	int BAT_Voltage;				//BAT电压
	int V1_Voltage;					//V1电压
} Get_Voltage;

Get_Voltage Get_V =					//举例电压值
{
	90.0,							//BAT电压为90.0V
	91.0,							//V1电压为91.0V
};


//高压管理模块初始化函数
extern void Hv_Init();
//获取电压函数
extern char Hv_Get(int object);		//获取当前BAT或V1电压

#endif