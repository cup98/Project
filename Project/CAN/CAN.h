#ifndef __CAN_H
#define __CAN_H

#include "hidef.h"
#include "derivative.h"

#define CAN_MSG_MAXLEN 8							//设置数据最大长度8字节

typedef struct _CAN_MsgType							//构造CAN通信报文结构
{
	unsigned long ID;					//仲裁帧id
	int IDE;							//IDE:0标准帧,1扩展帧
	int RTR;							//RTR:0数据帧,1远程帧
	unsigned char Data[CAN_MSG_MAXLEN];	//数据位
	unsigned char Len;					//数据长度
	unsigned char Prty;
} CAN_MsgType;

typedef enum _CAN_Channel_CfgType							//CAN波特率选择
{
	CAN0; 							  		//波特率设置为250K
	CAN1;
	CAN2;
	CAN3; 									//波特率设置为125K
	CAN4;							  		//波特率设置为250K
} CAN_Channel_CfgType;

typedef enum _CAN_BpsCfgType							//CAN波特率选择
{
	CAN_BPS_20K,							  		//波特率设置为250K
	CAN_BPS_50K,
	CAN_BPS_100K,
	CAN_BPS_125K,									//波特率设置为125K
	CAN_BPS_250K,							  		//波特率设置为250K
	CAN_BPS_500K,							  		//波特率设置为250K
	CAN_BPS_800K,
	CAN_BPS_1000K						  			//波特率设置为250K
} CAN_BpsCfgType;

typedef struct _CAN_ConfigType					//选择CAN波特率
{
	CAN_BpsCfgType Bps;
	unsigned char sp;
} CAN_ConfigType;

void CAN_Init(void);
void CAN1_Init(CAN_ConfigType *CAN_Cfg);
int CAN1_SendMsg(CAN_MsgType *CAN_Msg);
void CAN1_SendDemo(void);
int CAN1_GetMsg(CAN_MsgType *CAN_Msg);
void CAN1_GetToSend(void);
void CAN_Delay10ms(unsigned int i);

#endif

