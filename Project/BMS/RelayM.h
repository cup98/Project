#ifndef __RELAYM_H
#define __RELAYM_H

#include "hidef.h"
#include "derivative.h"

/*typedef enum _Ctl_Object
{
	Master,
	Precharg,
} Ctl_Object;*/

typedef struct _ReM_Ctl				//构建继电器控制结构体
{
	int Master_ReM;					//总正控制
	int Precharge_ReM;				//预充控制
} ReM_Ctl;

typedef struct _Switch_Ctl			//构建开关切换结构体
{
	int Master_Sw;					//总正切换
	int Precharge_Sw;				//预充切换
} Switch_Ctl;

ReM_Ctl ReM_Ct =					//初始控制继电器
{
	0,
	0,
};

Switch_Ctl Switch_Ct =				//初始切换开关
{
	0,
	0,
};

//继电器模块初始化函数
extern void RelayM_Init();

//控制继电器开关函数
extern void RelayM_Control(int object ,int state);		//控制总正和预充继电器的开关

//切换开关函数
extern void RelayM_Change(int object ,int state);		//控制总正和预充开关的切换

#endif