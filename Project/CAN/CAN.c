#include "CAN.h"

int CAN_Time = 0;

void CAN_Init(void)											//CAN初始化
{
	CAN1_Init(&CAN_HwCfgType);
}

//CAN1初始化以及配置CLK
void CAN1_Init(CAN_BpsConfigType *Config)
{
	int Wait1 = 0,Wait2 = 0,Wait3 = 0;
	if (CAN1CTL0_INITRQ == 0) 								//查询是否进入初始化状态
	{
		CAN1CTL0_INITRQ = 1;								//进入初始化状态
	}

	while (CAN1CTL1_INITAK == 0 && Wait1 < 5)				//等待进入初始化状态
	{
		Wait1++;
	}

	CAN1BTR0_SJW = 0;										//设置同步
	
	if (Config->sp == 1)	//����
	{
		CAN0BTR1_SAMP = 0;
	}
	else
	{
		CAN0BTR1_SAMP = 1;
	}

	if (Config->Bps == CAN_BPS_20K)  //配置波特率为250KHz
	{
		CAN1BTR0_BRP = 0x3F;
		CAN1BTR1 |= 0x7F;
	}
	else if (Config->Bps == CAN_BPS_50K)  //配置波特率为250KHz
	{
		CAN1BTR0_BRP = 0x1C;
		CAN1BTR1 |= 0x4F;
	}
	else if (Config->Bps == CAN_BPS_100K)  //配置波特率为250KHz
	{
		CAN1BTR0_BRP = 0x0F;
		CAN1BTR1 |= 0x2F;
	}
	else if (Config->Bps == CAN_BPS_125K)  //配置波特率为250KHz
	{
		CAN1BTR0_BRP = 0x0E;
		CAN1BTR1 |= 0x1D;
	}
	else if (Config->Bps == CAN_BPS_250K)  //配置波特率为250KHz
	{
		CAN1BTR0_BRP = 0x07;
		CAN1BTR1 |= 0x1C;
	}
	else if (Config->Bps == CAN_BPS_500K)  //配置波特率为250KHz
	{
		CAN1BTR0_BRP = 0x03;
		CAN1BTR1 |= 0x1C;
	}
	else if (Config->Bps == CAN_BPS_800K)  //配置波特率为250KHz
	{
		CAN1BTR0_BRP = 0x01;
		CAN1BTR1 |= 0x2F;
	}
	else if (Config->Bps == CAN_BPS_1000K)  //配置波特率为250KHz
	{
		CAN1BTR0_BRP = 0x01;
		CAN1BTR1 |= 0x1C;
	}
	else
	{
	}


	CAN1IDMR0 = 0xFF;										//关闭滤波器
	CAN1IDMR1 = 0xFF;
	CAN1IDMR2 = 0xFF;
	CAN1IDMR3 = 0xFF;
	CAN1IDMR4 = 0xFF;
	CAN1IDMR5 = 0xFF;
	CAN1IDMR6 = 0xFF;
	CAN1IDMR7 = 0xFF;
	CAN1CTL1  = 0xC0;										//使能MSCAN模块,设置为一般运行模式、使用总线时钟源
	CAN1CTL0  = 0x00;										//返回一般模式运行

	while (CAN1CTL1_INITAK && Wait2 < 5)					//等待回到一般运行模式
	{
		Wait2++;
	}
	while ((CAN1CTL0_SYNCH == 0) && Wait3 < 5) 				//等待总线时钟同步
	{
		Wait3++;
	}

	CAN1RIER_RXFIE = 1;										//禁止接收中断
}

//CAN1发送
int CAN1_SendMsg(CAN_MsgType *msg)
{
	unsigned char send_buf, sp ;							//设置发送缓冲区、发送数据位数
  	int Reflag;

	if (msg->Len > CAN_MSG_MAXLEN)				//检查数据长度
	{
		Reflag = 0;
	}
	else
	{
	}

	if (CAN1CTL0_SYNCH == 0)								//检查总线时钟
	{
		Reflag = 0;
	}
	else
	{
	}

	do
	{
		CAN1TBSEL = CAN1TFLG;
		send_buf  = CAN1TBSEL;
	} while (!(send_buf));									//寻找空闲的缓冲器

	CAN1TXIDR0 = (unsigned char)(msg->ID >> 3);	//写入帧ID前8位
	CAN1TXIDR1 = (unsigned char)(msg->ID << 5);	//写入帧ID后3位

	if (msg->IDE)								//判断IDE：0标准帧,1远程帧
	{
		CAN1TXIDR1 |= 0x10;
	}
	else
	{
	}

	for (sp = 0 ; sp < msg->Len ; sp++)			//依次将数据写入寄存器
	{
		*((&CAN1TXDSR0) + sp) = msg->Data[sp];
	}

	CAN1TXDLR  = msg->Len;						//写入数据长度
	CAN1TXTBPR = msg->Prty;						//写入优先级
	CAN1TFLG   = send_buf;									//清TXx标志(缓冲器准备发送)

	Reflag = 1;
	return Reflag;
}

//CAN1切换发送数据
void CAN1_MsgData(void)
{
	CAN_Time++;

  	if (CAN_Time == 1)
  	{
  	  	CAN1_SendMsg(&CAN_Msg1Type);
  	}
  	else if (CAN_Time == 2)
  	{
  	  	CAN1_SendMsg(&CAN_Msg2Type);
  	}
 	else if (CAN_Time == 3)
  	{
    	CAN1_SendMsg(&CAN_Msg3Type);
    	CAN_Time = 0;
  	}
	else
	{
	}
}

/*void CAN1_MsgCPLT(void)
{
  	CAN1_SendMsg(CPIT);
}*/

//CAN1接收
int CAN1_GetMsg(CAN_MsgType *msg)
{
  	unsigned char sp;										  //设置接收数据位数
    int Reflag;

  	if (!(CAN1RFLG_RXF))									  //检测接收标志
  	{
  		Reflag = 0;
  	}
  	else
	{
	}

   	if (CAN1RXIDR1_IDE)										  //检测CAN协议报文模式（标准/扩展）标识符
  	{
   		Reflag = 0;										  	  //只接收标准帧
   	}
	else
	{
	}

  	if (CAN1RXIDR1 & 0x10)                         			  //判断是否为标准帧
  	{
  	  	msg->IDE = 1;
  	}
  	else
  	{
  	  	msg->IDE = 0;
  	  	msg->ID  = (unsigned char)(CAN1RXIDR0 << 3) | //读出接收帧ID前8位
            	  			   (unsigned char)(CAN1RXIDR1 >> 5) ; //并且与上读出接收帧ID后3位
 	}

 	if (CAN1RXIDR1 & 0x08)                         			  //判断是否为远程帧
  	{
  	  	msg->RTR = 1;
  	}
  	else
  	{
  	  	msg->RTR = 0;
 	}

  	msg->Len = CAN1RXDLR;						  //读出接收的数据长度

  	for (sp = 0; sp < msg->Len; sp++)			  //依次读出接收的每一位数据
  	{
  		msg->Data[sp] = *((&CAN1RXDSR0) + sp);
  	}

  	CAN1RFLG |= 1;											  //清RXF标志位(缓冲器准备接收)

    Reflag = 1;
  	return Reflag;
}

void CAN1_GetToOut(void)									  //读出接受到的数据再发送出来
{
  	if (CAN1_GetMsg(&CAN_MsgType_CAN1_GetBufType) == 1)
  	{
    	if (!(CAN_MsgType_CAN1_GetBufType.IDE))
    	{
      		CAN1_SendMsg(&CAN_MsgType_CAN1_GetBufType);
    	}
    	else
		{
		}
  	}
	else
	{
	}
}

void Delay10ms(unsigned int i)								  //延时
{
    unsigned int n,m;
    for (n=0; n<250; n++)
    {
        for (m=0; m<(80*i); m++)
        {
        }
    }
}

//CAN接收触发中断函数
#pragma CODE_SEG __NEAR_SEG NON_BANKED
void interrupt VectorNumber_Vcan1rx CAN_receive(void)
{
    CAN1_GetToOut();
}
#pragma CODE_SEG DEFAULT

