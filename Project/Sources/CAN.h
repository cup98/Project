#ifndef __CAN_H
#define __CAN_H

#include "hidef.h"
#include "derivative.h"

#define MSG_MAXLEN 8					//设置数据最大长度8字节
int flag = 0;


typedef enum _CAN_ClkSoureType			//CAN时钟源选择
{
	CANCLK_OSC,							//晶振时钟源
	CANCLK_PLL,							//PLL时钟源
} CAN_ClkSoureType;

typedef enum _CAN_BpsType				//CAN波特率选择
{
	CANBps_125K,						//波特率设置为125K
	CANBps_250K,						//波特率设置为250K
} CAN_BpsType;

typedef struct _CAN_MsgType				//构造CAN通信报文结构
{
	unsigned int id;					//仲裁帧id
	unsigned char RTR;					//RTR:0标准帧,1远程帧
	unsigned char data[MSG_MAXLEN];		//数据位
	unsigned char len;					//数据长度
	unsigned char prty;
} CAN_MsgType;

typedef struct _CAN_Config				//选择CAN波特率
{
	CAN_BpsType bps;
} CAN_Config;


static CAN_Config CAN_HwCfg =			//设置波特率
{
	CANBps_125K,
};

static CAN_MsgType CanM1 =				//设置CAN标准帧
{
	0x01,
	0,
	{1,1,1,1,1,1,1,1},
	8,
	0,
};

static CAN_MsgType CanM2 =
{
	0x02,
	0,
	{2,2,2,2,2,2,2,2},
	8,
	0,
};

static CAN_MsgType CanM3 =
{
	0x03,
	0,
	{3,3,3,3,3,3,3,3},
	8,
	0,
};

static CAN_MsgType CPIT =
{
	0x03,
	0,
	{10,10,10,10,10,10,10,10},
	8,
	0,
};
/*static CAN_MsgType CanM3 =
{
	0x03,
	0,
	{3,3,3,3,3,3,3,3},
	8,
	0,
};
static CAN_MsgType CanM3 =
{
	0x03,
	0,
	{3,3,3,3,3,3,3,3},
	8,
	0,
};*/

CAN_MsgType CanM4;

extern void CAN_Init();
extern void CAN1_Init(CAN_Config *cfg);
extern char CAN1_SendMsg(CAN_MsgType msg);
extern void CAN1_MsgData();
extern char CAN1_GetMsg(CAN_MsgType *msg);
extern void CAN1_GetToOut();
extern void Delay10ms(unsigned int i);
extern void CAN1_MsgCPLT(void);


#endif

