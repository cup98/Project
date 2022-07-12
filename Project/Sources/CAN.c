#include "derivative.h"
#include "CAN.h"

int CAN_TMIE = 0;

void CAN_Init(void)										//CAN1初始化
{
	CAN1_Init(&CAN_HwCfg);
}
//CAN1初始化以及配置CLK
void CAN1_Init(CAN_Config *Config)
{
	if (CAN1CTL0_INITRQ == 0)						//查询是否进入初始化状态
			CAN1CTL0_INITRQ = 1;							//进入初始化状态
	while (CAN1CTL1_INITAK == 0)				//等待进入初始化状态

	CAN1BTR0_SJW = 0;										//设置同步

	if (Config->bps == CANBps_125K)			//配置波特率为125KHz
	{																		//OSC=8MHz;Bps=8MHz/BRP/(1+TSEG1+TSEG2)
			CAN1BTR0_BRP = 0x0E;						//设置波特率预定值
			CAN1BTR1 |= 0x1D;			  				//设置TSEG1和TSEG2时间段
	}

	CAN1IDMR0 = 0xFF;										//关闭滤波器
	CAN1IDMR1 = 0xFF;
	CAN1IDMR2 = 0xFF;
	CAN1IDMR3 = 0xFF;
	CAN1IDMR4 = 0xFF;
	CAN1IDMR5 = 0xFF;
	CAN1IDMR6 = 0xFF;
	CAN1IDMR7 = 0xFF;
	CAN1CTL1 = 0xC0;										//使能MSCAN模块,设置为一般运行模式、使用总线时钟源
	CAN1CTL0 = 0x00;										//返回一般模式运行

	while (CAN1CTL1_INITAK);						//等待回到一般运行模式
	while (CAN1CTL0_SYNCH == 0);				//等待总线时钟同步

	CAN1RIER_RXFIE = 1;									//禁止接收中断
}

//CAN1发送
char CAN1_SendMsg(CAN_MsgType msg)
{
	unsigned char send_buf, sp;					//设置发送缓冲区、发送数据位数

	if (msg.len > MSG_MAXLEN)						//检查数据长度
		return FALSE;
	if (CAN1CTL0_SYNCH == 0)						//检查总线时钟
		return FALSE;
	do
	{
		CAN1TBSEL = CAN1TFLG;
		send_buf  = CAN1TBSEL;
	} while (!(send_buf));							//寻找空闲的缓冲器

	CAN1TXIDR0 = (unsigned char)(msg.id >> 3);		//写入帧ID前8位
	CAN1TXIDR1 = (unsigned char)(msg.id << 5);		//写入帧ID后3位

	if(msg.RTR)																		//判断RTR：0标准帧；1扩展帧
		CAN1TXIDR1 |= 0x10;

	for(sp = 0 ; sp < msg.len ; sp++)							//依次将数据写入寄存器
		*((&CAN1TXDSR0)+sp) = msg.data[sp];

	CAN1TXDLR  = msg.len;								//写入数据长度
	CAN1TXTBPR = msg.prty;							//写入优先级
	CAN1TFLG   = send_buf;							//清TXx标志(缓冲器准备发送)

	return TRUE;
}

//CAN1切换发送数据
void CAN1_MsgData(void)
{
	CAN_TMIE++;

  if (CAN_TMIE == 1)
  {
    CAN1_SendMsg(CanM1);
  }
  else if (CAN_TMIE == 2)
  {
    CAN1_SendMsg(CanM2);
  }
  else if (CAN_TMIE == 3)
  {
    CAN1_SendMsg(CanM3);
    CAN_TMIE = 0;
  }
 }

void CAN1_MsgCPLT(void)
{
  CAN1_SendMsg(CPIT);
}
//CAN1接收
char CAN1_GetMsg(CAN_MsgType *msg)
{
  unsigned char sp2;													//设置接收数据位数

  if(!(CAN1RFLG_RXF))													//检测接收标志
    return 0;

  if(CAN1RXIDR1_IDE)												  //检测CAN协议报文模式（标准/扩展）标识符
    return 0;														      //只接收标准帧

  if(CAN1RXIDR1&0x10)                         //判断是否为标准帧
  {
    msg->RTR = 1;
  }
  else
  {
    msg->RTR = 0;
    msg->id = (unsigned int)(CAN1RXIDR0<<3) |  //读出接收帧ID前8位
              (unsigned char)(CAN1RXIDR1>>5);  //并且与上读出接收帧ID后3位
  }

  msg->len = CAN1RXDLR;												//读出接收的数据长度

  for(sp2 = 0; sp2 < msg->len; sp2++)					//依次读出接收的每一位数据
    msg->data[sp2] = *((&CAN1RXDSR0)+sp2);

  CAN1RFLG |= 1;															//清RXF标志位(缓冲器准备接收)

  return 1;
}

void CAN1_GetToOut(void)											//读出接受到的数据再发送出来
{
  if (CAN1_GetMsg(&CanM4) == 1)
  {
    if(!CanM4.RTR)
    {
      CAN1_SendMsg(CanM4);
    }
  }
}

void Delay10ms(unsigned int i)								//延时
{
    unsigned int n,m;
    for(n=0;n<250;n++)
    {
        for(m=0;m<(80*i);m++)
        {
        }
    }
}

#pragma CODE_SEG __NEAR_SEG NON_BANKED      //CAN接收触发中断函数
void interrupt VectorNumber_Vcan1rx CAN_receive(void)
{
    CAN1_GetToOut();
}
#pragma CODE_SEG DEFAULT

