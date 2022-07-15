#include "CAN_Cfg.h"

#include "hidef.h"
#include "derivative.h"

#define CAN0 0x0140
#define CAN1 0x0180
#define CAN2 0x01C0
#define CAN3 0x0200
#define CAN4 0x0240

#define CANCTL0   *(CAN0CTL0+)
#define CANCTL1   *(CAN0CTL1)
#define CANBRT0   *(CAN0BRT0)
#define CANBRT1   *(CAN0BRT1)
#define CANRFLG   *(CAN0RFLG)
#define CANRIER   *(CAN0RIER)
#define CANTBSEL  *(CAN0TBSE)
#define CANTFLG   *(CAN0TFLG)
#define CANTXIDR0 *(CAN0TXIDR0)
#define CANTXIDR1 *(CAN0TXIDR1)
#define CANTXIDR2 *(CAN0TXIDR2)
#define CANTXIDR3 *(CAN0TXIDR3)
#define CANIDMR0  *(CAN0IDMR0)
#define CANIDMR1  *(CAN0IDMR1)
#define CANIDMR2  *(CAN0IDMR2)
#define CANIDMR3  *(CAN0IDMR3)
#define CANIDMR4  *(CAN0IDMR4)
#define CANIDMR5  *(CAN0IDMR5)
#define CANIDMR6  *(CAN0IDMR6)
#define CANIDMR7  *(CAN0IDMR7)
#define CANRXIDR0 *(CAN0RXIDR0)
#define CANRXIDR1 *(CAN0RXIDR1)
#define CANRXIDR2 *(CAN0RXIDR2)
#define CANRXIDR3 *(CAN0RXIDR3)
#define CANRXDSR0 *(CAN0RXDSR0)
#define CANRXDLR  *(CAN0RXDLR)
#define CANTXDSR0 *(CAN0TXDSR0)
#define CANTXDLR  *(CAN0TXDLR)
#define CANTXTBPR *(CAN0TXTBPR)

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
