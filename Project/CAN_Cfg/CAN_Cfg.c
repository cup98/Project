#include "CAN_Cfg.h"

#include "hidef.h"
#include "derivative.h"


CAN_MsgType CAN_Msg1Type =					//è®¾ç½®CANæ ‡å‡†å¸§
{
	0x01F,
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

CAN_ConfigType CAN_HwCfgType =			//è®¾ç½®æ³¢ç‰¹çŽ‡
{
	CAN_BPS_125K,
	1,
};
