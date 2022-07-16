#include "CAN_Cfg.h"

#include "hidef.h"
#include "derivative.h"

CAN_MsgType CAN_Msg1Type =					//è®¾ç½®CANæ ‡å‡†å¸§
{
	0x01,
	0,
	0,
	{1,1,1,1,1,1,1,1},
	8,
	0,
};

CAN_MsgType CAN_Msg2Type =
{
	0x1FFFFFFF,
	1,
	0,
	{2,2,2,2,2,2,2,2},
	8,
	0,
};

CAN_MsgType CAN_Msg3Type =
{
	0x03,
	0,
	1,
	{3,3,3,3,3,3,3,3},
	8,
	0,
};

CAN_ConfigType CAN0_HwCfgType =			//è®¾ç½®æ³¢ç‰¹çŽ‡
{
	CAN0,
	CAN_BPS_125K,
	1,
};

CAN_ConfigType CAN1_HwCfgType =			//è®¾ç½®æ³¢ç‰¹çŽ‡
{
	CAN1,
	CAN_BPS_125K,
	1,
};

CAN_ConfigType CAN2_HwCfgType =			//è®¾ç½®æ³¢ç‰¹çŽ‡
{
	CAN2,
	CAN_BPS_125K,
	1,
};

CAN_ConfigType CAN3_HwCfgType =			//è®¾ç½®æ³¢ç‰¹çŽ‡
{
	CAN3,
	CAN_BPS_125K,
	1,
};

CAN_ConfigType CAN4_HwCfgType =			//è®¾ç½®æ³¢ç‰¹çŽ‡
{
	CAN4,
	CAN_BPS_125K,
	1,
};



