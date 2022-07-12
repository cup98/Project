#ifndef __PRECHARGEM_H
#define __PRECHARGEM_H

#include "hidef.h"
#include "derivative.h"

extern void Time_Flag(void);

//初始化函数
extern void PrechargeM_Init();

//启动预充函数
extern void PrechargeM_StartPre();				//闭合预充开关

//停止预充函数
extern void PrechargeM_StopPre();				//断开预充开关

//闭合总正函数
extern void PrechargeM_StartMaster();

//断开总正函数
extern void PrechargeM_StopMaster();

//继电器切换函数
extern void PrechargeM_Change();				//闭合综合总正，断开预充

//预充完成判断函数
extern int PrechargeM_IsFinish();				//判断V1电压是否大于BAT电压的95%

//超时判断函数
extern int PrechargeM_IsFail(void);				//判断自启动预充至此刻的时间是否超过3秒

#endif