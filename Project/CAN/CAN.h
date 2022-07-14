#ifndef __CAN_H
#define __CAN_H

#include "hidef.h"
#include "derivative.h"

#define CAN_MSG_MAXLEN 8							//设置数据最大长度8字节

typedef enum _CAN_BpsType							//CAN波特率选择
{
	CAN_BPS_20K,							  		//波特率设置为250K
	CAN_BPS_50K,
	CAN_BPS_100K,
	CAN_BPS_125K,									//波特率设置为125K
	CAN_BPS_250K,							  		//波特率设置为250K
	CAN_BPS_500K,							  		//波特率设置为250K
	CAN_BPS_800K,
	CAN_BPS_1000K						  			//波特率设置为250K
} CAN_BpsType;

typedef struct _CAN_MsgType							//构造CAN通信报文结构
{
	unsigned int ID;					//仲裁帧id
	int IDE;							//IDE:0标准帧,1扩展帧
	int RTR;							//RTR:0数据帧,1远程帧
	unsigned char Data[CAN_MSG_MAXLEN];	//数据位
	unsigned char Len;					//数据长度
	unsigned char Prty;
} CAN_MsgType;

typedef struct _CAN_BpsConfigType					//选择CAN波特率
{
	CAN_BpsType Bps;
	unsigned char sp;
} CAN_BpsConfigType;


static CAN_BpsConfigType CAN_HwCfgType =			//设置波特率
{
	CAN_BPS_125K,
	1
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
extern void CAN1_Init(CAN_BpsConfigType *cfg);
extern int CAN1_SendMsg(CAN_MsgType *msg);
extern void CAN1_MsgData(void);
extern int CAN1_GetMsg(CAN_MsgType *msg);
extern void CAN1_GetToOut(void);
extern void Delay10ms(unsigned int i);
//extern void CAN1_MsgCPLT(void);


#endif

