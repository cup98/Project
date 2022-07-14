#include "CAN.h"

int CAN_Time = 0;
CAN_MsgType CAN1_GetBufType;		//声明CAN1接收缓存

static CAN_ConfigType CAN_HwCfgType =			//设置波特率
{
	CAN_BPS_125K,
	1,
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
	0x00FFF,
	1,
	0,
	{2,2,2,2,2,2,2,2},
	8,
	0,
};

static CAN_MsgType CAN_Msg3Type =
{
	0x03,
	0,
	1,
	{3,3,3,3,3,3,3,3},
	8,
	0,
};

void CAN_Init(void)											//CAN初始�
{
	CAN1_Init(&CAN_HwCfgType);
}

//CAN1初始化以及配置CLK
void CAN1_Init(CAN_ConfigType *CAN_Cfg)
{
	int Wait1 = 0,Wait2 = 0,Wait3 = 0;
	if (CAN1CTL0_INITRQ == 0) 								//查询是否进入初始化状�
	{
		CAN1CTL0_INITRQ = 1;								//进入初始化状�
	}

	while (CAN1CTL1_INITAK == 0 && Wait1 < 5)				//等待进入初始化状�
	{
		Wait1++;
	}

	CAN1BTR0_SJW = 0;										//设置同步

	if (CAN_Cfg->sp == 1)	//����
	{
		CAN0BTR1_SAMP = 0;
	}
	else
	{
		CAN0BTR1_SAMP = 1;
	}

	switch (CAN_Cfg->Bps)
	{
		case CAN_BPS_20K:
		{
			CAN1BTR0_BRP = 0x3F;
			CAN1BTR1 |= 0x7F;
		} break;

		case CAN_BPS_50K:
		{
			CAN1BTR0_BRP = 0x1C;
			CAN1BTR1 |= 0x4F;
		} break;

		case CAN_BPS_100K:
		{
			CAN1BTR0_BRP = 0x0F;
			CAN1BTR1 |= 0x2F;
		} break;

		case CAN_BPS_125K:
		{
			CAN1BTR0_BRP = 0x0E;
			CAN1BTR1 |= 0x1D;
		} break;

		case CAN_BPS_250K:
		{
			CAN1BTR0_BRP = 0x07;
			CAN1BTR1 |= 0x1C;
		} break;

		case CAN_BPS_500K:
		{
			CAN1BTR0_BRP = 0x03;
			CAN1BTR1 |= 0x1C;
		} break;

		case CAN_BPS_800K:
		{
			CAN1BTR0_BRP = 0x01;
			CAN1BTR1 |= 0x2F;
		} break;

		case CAN_BPS_1000K:
		{
			CAN1BTR0_BRP = 0x01;
			CAN1BTR1 |= 0x1C;
		} break;
	}

	CAN1IDMR0 = 0xFF;										//关闭滤波�
	CAN1IDMR1 = 0xFF;
	CAN1IDMR2 = 0xFF;
	CAN1IDMR3 = 0xFF;
	CAN1IDMR4 = 0xFF;
	CAN1IDMR5 = 0xFF;
	CAN1IDMR6 = 0xFF;
	CAN1IDMR7 = 0xFF;
	CAN1CTL1  = 0xC0;										//使能MSCAN模块,设置为一般运行模式�使用�线时钟�
	CAN1CTL0  = 0x00;										//返回�般模式运�

	while (CAN1CTL1_INITAK && Wait2 < 5)					//等待回到�般运行模�
	{
		Wait2++;
	}
	while ((CAN1CTL0_SYNCH == 0) && Wait3 < 5) 				//等待总线时钟同步
	{
		Wait3++;
	}

	CAN1RIER_RXFIE = 1;										//禁止接收中断
}

//CAN1发�
int CAN1_SendMsg(CAN_MsgType *CAN_Msg)
{
	unsigned char send_buf, sp ;							//设置发�缓冲区、发送数据位�
  	int Reflag;

	if (CAN_Msg->Len > CAN_MSG_MAXLEN)				//�查数据长�
	{
		Reflag = 0;
	}

	if (CAN1CTL0_SYNCH == 0)								//�查�线时钟
	{
		Reflag = 0;
	}

	do
	{
		CAN1TBSEL = CAN1TFLG;
		send_buf  = CAN1TBSEL;
	} while (!(send_buf));									//寻找空闲的缓冲器

	/*��չ֡ID����*/
	if (CAN_Msg->IDE)
	{
  		CAN1TXIDR0 =  (unsigned long)(CAN_Msg->ID >> 21);
  		CAN1TXIDR1 =  (unsigned long)(CAN_Msg->ID >> 13) & 0xE0;
  		CAN1TXIDR1 |= 0x18;
  		CAN1TXIDR1 |= (unsigned long)(CAN_Msg->ID >> 15) & 0x07;
  		CAN1TXIDR2 =  (unsigned long)(CAN_Msg->ID >> 7);
  		CAN1TXIDR3 =  (unsigned long)(CAN_Msg->ID << 1);
  		if (CAN_Msg->RTR)								//判断IDE�0标准�,1远程�
		{
			CAN1TXIDR3 |= 0x01;
		}
		else
		{
			CAN1TXIDR3 &= 0xFE;
		}
	}
	else
	{/*��׼֡ID����*/
  		CAN1TXIDR0 =  (unsigned long)(CAN_Msg->ID >> 3);
  		CAN1TXIDR1 =  (unsigned long)(CAN_Msg->ID << 5);
  		CAN1TXIDR1 &= 0xF7;
  		if (CAN_Msg->RTR)								//判断IDE�0标准�,1远程�
		{
			CAN1TXIDR1 |= 0x10;
		}
		else
		{
			CAN1TXIDR1 &= 0xEF;
		}
	}

	for (sp = 0 ; sp < CAN_Msg->Len ; sp++)			//依次将数据写入寄存器
	{
		*((&CAN1TXDSR0) + sp) = CAN_Msg->Data[sp];
	}

	CAN1TXDLR  = CAN_Msg->Len;						//写入数据长度
	CAN1TXTBPR = CAN_Msg->Prty;						//写入优先�
	CAN1TFLG   = send_buf;									//清TXx标志(缓冲器准备发�)

	Reflag = 1;
	return Reflag;
	
}

//CAN1接收
int CAN1_GetMsg(CAN_MsgType *CAN_Msg)
{
  	unsigned char sp;										  //设置接收数据位数
    int Reflag;

  	if (!(CAN1RFLG_RXF))									  //�测接收标�
  	{
  		Reflag = 0;
  	}

  	if ((CAN1RXIDR1 & 0x08) == 0x08)                         			  //判断是否为标准帧
  	{
        CAN_Msg->ID = ((unsigned long)(CAN1RXIDR0 & 0xff)) << 21;
  	    CAN_Msg->ID = CAN_Msg->ID | (((unsigned long)(CAN1RXIDR1 & 0xe0)) << 13);
	      CAN_Msg->ID = CAN_Msg->ID | (((unsigned long)(CAN1RXIDR1 & 0x07)) << 15);
	      CAN_Msg->ID = CAN_Msg->ID | (((unsigned long)(CAN1RXIDR2 & 0xff)) << 7);
	      CAN_Msg->ID = CAN_Msg->ID | (((unsigned long)(CAN1RXIDR3 & 0xfe)) >> 1);
        CAN_Msg->IDE = 1;

        if (CAN1RXIDR3 & 0x01)                         			  //判断是否为远程帧
  		{
  	  		CAN_Msg->RTR = 1;
  		}
  		else
  		{
  	  		CAN_Msg->RTR = 0;
 		}
  	}
  	else
  	{
  	  	CAN_Msg->ID  = (unsigned long)(CAN1RXIDR0 << 3) | //读出接收帧ID�8�
            	  	   (unsigned long)(CAN1RXIDR1 >> 5) ; //并且与上读出接收帧ID�3�
        CAN_Msg->IDE = 0;
        if (CAN1RXIDR1 & 0x10)                         			  //判断是否为远程帧
  		{
  	  		CAN_Msg->RTR = 1;
  		}
  		else
  		{
  	  		CAN_Msg->RTR = 0;
 		}
 	}

  	CAN_Msg->Len = CAN1RXDLR;						  //读出接收的数据长�

  	for (sp = 0; sp < CAN_Msg->Len; sp++)			  //依次读出接收的每�位数�
  	{
  		CAN_Msg->Data[sp] = *((&CAN1RXDSR0) + sp);
  	}

  	CAN1RFLG |= 1;											  //清RXF标志�(缓冲器准备接�)

    Reflag = 1;
  	return Reflag;
}

//CAN1切换发�数�
void CAN1_SendDemo(void)
{
	CAN_Time++;

  	if (CAN_Time == 1)
  	{
  	  	if(CAN1_SendMsg(&CAN_Msg1Type) == 1) 
  	  	{
  	  	}
  	}
  	else if (CAN_Time == 2)
  	{
  	  	if(CAN1_SendMsg(&CAN_Msg2Type) == 1) 
  	  	{
  	  	}
  	}
 	else if (CAN_Time == 3)
  	{
    	if(CAN1_SendMsg(&CAN_Msg3Type) == 1)
    	{
    	}
    	CAN_Time = 0;
  	}
	else
	{
	}
}

void CAN1_GetToSend(void)									  //读出接受到的数据再发送出�
{
  	if (CAN1_GetMsg(&CAN1_GetBufType) == 1)
  	{
      	if(CAN1_SendMsg(&CAN1_GetBufType) == 1)
      	{
      	}
  	}
}

void CAN_Delay10ms(unsigned int i)								  //延时
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
    CAN1_GetToSend();
}
#pragma CODE_SEG DEFAULT


