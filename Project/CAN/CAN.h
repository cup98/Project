#ifndef __CAN_H
#define __CAN_H

#include "hidef.h"
#include "derivative.h"

#define CAN_MSG_MAXLEN 8							//设置数据最大长度8字节

typedef enum _CAN_BPS_TYPE							//CAN波特率选择
{
	CANBPS_125K,									//波特率设置为125K
	CANBPS_250K,							  		//波特率设置为250K
} CAN_BPS_TYPE;

typedef struct _CAN_MsgType							//构造CAN通信报文结构
{
	unsigned int  CAN_MsgType_ID;					//仲裁帧id
	int CAN_MsgType_IDE;							//IDE:0标准帧,1扩展帧
	int CAN_MsgType_RTR;							//RTR:0数据帧,1远程帧
	unsigned char CAN_MsgType_Data[CAN_MSG_MAXLEN];	//数据位
	unsigned char CAN_MsgType_Len;					//数据长度
	unsigned char CAN_MsgType_Prty;
} CAN_MsgType;

typedef struct _CAN_BPSConfigType					//选择CAN波特率
{
	CAN_BPS_TYPE CAN_BPSConfigType_BPS;
} CAN_BPSConfigType;


static CAN_BPSConfigType CAN_HwCfg_Type =			//设置波特率
{
	CANBPS_125K,
};

static CAN_MsgType CAN_Msg1Type =					//设置CAN标准帧
{
	0x01,
	0,
	0,
	{1,1,1,1,1,1,1,1},
	8,
	0,
};

static CAN_MsgType CAN_Msg2Type =
{
	0x02,
	0,
	0,
	{2,2,2,2,2,2,2,2},
	8,
	0,
};

static CAN_MsgType CAN_Msg3Type =
{
	0x03,
	0,
	0,
	{3,3,3,3,3,3,3,3},
	8,
	0,
};

static CAN_MsgType CPITType =
{
	0x03,
	0,
	0,
	{10,10,10,10,10,10,10,10},
	8,
	0,
};

CAN_MsgType CAN_MsgType_CAN1_GetBufType;		//声明CAN1接收缓存

extern void CAN_Init(void);
extern void CAN1_Init(CAN_BPSConfigType *cfg);
extern int CAN1_SendMsg(CAN_MsgType *msg);
extern void CAN1_MsgData(void);
extern int CAN1_GetMsg(CAN_MsgType *msg);
extern void CAN1_GetToOut(void);
extern void Delay10ms(unsigned int i);
extern void CAN1_MsgCPLT(void);


#endif

