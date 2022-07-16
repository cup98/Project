#include "CAN.h"
#include "CAN_Cfg.h"

int CAN_Time = 0;
CAN_MsgType CAN1_GetBufType;		//声明CAN1接收缓存

unsigned char  *CANCTL0;
unsigned char  *CANCTL1;
unsigned char  *CANBTR0;
unsigned char  *CANBTR1;
unsigned char  *CANRFLG;
unsigned char  *CANRIER;
unsigned char  *CANTBSEL; 
unsigned char  *CANTFLG;
unsigned char  *CANTXIDR0;
unsigned char  *CANTXIDR1;
unsigned char  *CANTXIDR2;
unsigned char  *CANTXIDR3;
unsigned char  *CANIDMR0; 
unsigned char  *CANIDMR1; 
unsigned char  *CANIDMR2; 
unsigned char  *CANIDMR3; 
unsigned char  *CANIDMR4; 
unsigned char  *CANIDMR5; 
unsigned char  *CANIDMR6; 
unsigned char  *CANIDMR7; 
unsigned char  *CANRXIDR0;
unsigned char  *CANRXIDR1;
unsigned char  *CANRXIDR2;
unsigned char  *CANRXIDR3;
unsigned char  *CANRXDSR0;
unsigned char  *CANRXDLR; 
unsigned char  *CANTXDSR0;
unsigned char  *CANTXDLR;
unsigned char  *CANTXTBPR;
               
void CAN_RegAdd_Cfg(int channel)
{
	CANCTL0 = ((&CAN0CTL0) + channel * 0x40);
	CANCTL1 = ((&CAN0CTL1) + channel * 0x40);
	CANBTR0 = ((&CAN0BTR0) + channel * 0x40);
	CANBTR1 = ((&CAN0BTR1) + channel * 0x40);
	CANRFLG = ((&CAN0RFLG) + channel * 0x40);
  CANRIER = ((&CAN0RIER) + channel * 0x40);
	CANTBSEL = ((&CAN0TBSEL) + channel * 0x40);
	CANTFLG = ((&CAN0TFLG) + channel * 0x40);
	CANTXIDR0 = ((&CAN0TXIDR0) + channel * 0x40);
	CANTXIDR1 = ((&CAN0TXIDR1) + channel * 0x40);
	CANTXIDR2 = ((&CAN0TXIDR2) + channel * 0x40);
	CANTXIDR3 = ((&CAN0TXIDR3) + channel * 0x40);
  CANIDMR0 = ((&CAN0IDMR0) + channel * 0x40);
  CANIDMR1 = ((&CAN0IDMR1) + channel * 0x40);
  CANIDMR2 = ((&CAN0IDMR2) + channel * 0x40);
  CANIDMR3 = ((&CAN0IDMR3) + channel * 0x40);
  CANIDMR4 = ((&CAN0IDMR4) + channel * 0x40);
	CANIDMR5 = ((&CAN0IDMR5) + channel * 0x40);
	CANIDMR6 = ((&CAN0IDMR6) + channel * 0x40);
  CANIDMR7 = ((&CAN0IDMR7) + channel * 0x40);
  CANRXIDR0 = ((&CAN0RXIDR0) + channel * 0x40);
  CANRXIDR1 = ((&CAN0RXIDR1) + channel * 0x40);
	CANRXIDR2 = ((&CAN0RXIDR2) + channel * 0x40);
  CANRXIDR3 = ((&CAN0RXIDR3) + channel * 0x40);
	CANRXDSR0 = ((&CAN0RXDSR0) + channel * 0x40);
	CANRXDLR = ((&CAN0RXDLR) + channel * 0x40);
	CANTXDSR0 = ((&CAN0TXDSR0) + channel * 0x40);
	CANTXDLR = ((&CAN0TXDLR) + channel * 0x40);
	CANTXTBPR = ((&CAN0TXTBPR) + channel * 0x40);
}

void CAN_Init(void)											//CAN初始�
{
	CAN1_Init(&CAN1_HwCfgType);	
}

void CAN1_Init(CAN_ConfigType *CAN_Cfg)
{
	int Wait1 = 0,Wait2 = 0,Wait3 = 0;
	CAN_RegAdd_Cfg(CAN_Cfg->Channel);
	
	if ((*CANCTL0 & 0x01) == 0) 								//查询是否进入初始化状�
	{
		*CANCTL0 |= 1;								//进入初始化状�
	}

	while (((*CANCTL1 & 0x01) == 0) && Wait1 < 5)				//等待进入初始化状�
	{
		Wait1++;
	}

	*CANBTR0 |= 0xC0;										//设置同步

	if (CAN_Cfg->sp == 1)	//����
	{
		*CANBTR1 &= 0x7F;
	}
	else
	{
		*CANBTR1 |= 0x80;
	}

  *CANBTR0 |= 0xC0;
	switch (CAN_Cfg->Bps)
	{
		case CAN_BPS_20K:
		{
			*CANBTR0  = 0x3F;
			*CANBTR1 |= 0x7F;
		} break;

		case CAN_BPS_50K:
		{
			*CANBTR0  = 0x1C;
			*CANBTR1 |= 0x4F;
		} break;

		case CAN_BPS_100K:
		{
			*CANBTR0  = 0x0F;
			*CANBTR1 |= 0x2F;
		} break;

		case CAN_BPS_125K:
		{
			*CANBTR0  = 0x0E;
			*CANBTR1 |= 0x1D;
		} break;

		case CAN_BPS_250K:
		{
			*CANBTR0  = 0x07;
			*CANBTR1 |= 0x1C;
		} break;

		case CAN_BPS_500K:
		{
			*CANBTR0  = 0x03;
			*CANBTR1 |= 0x1C;
		} break;

		case CAN_BPS_800K:
		{
			*CANBTR0  = 0x01;
			*CANBTR1 |= 0x2F;
		} break;

		case CAN_BPS_1000K:
		{
			*CANBTR0  = 0x01;
			*CANBTR1 |= 0x1C;
		} break;
	}

	*CANIDMR0 = 0xFF;										//关闭滤波�
	*CANIDMR1 = 0xFF;
	*CANIDMR2 = 0xFF;
	*CANIDMR3 = 0xFF;
	*CANIDMR4 = 0xFF;
	*CANIDMR5 = 0xFF;
	*CANIDMR6 = 0xFF;
	*CANIDMR7 = 0xFF;
	*CANCTL1  = 0xC0;										//使能MSCAN模块,设置为一般运行模式�使用�线时钟�
	*CANCTL0  = 0x00;										//返回�般模式运�

	while ((*CANCTL1 & 0x01 == 0x01) && Wait2 < 5)					//等待回到�般运行模�
	{
		Wait2++;
	}
	while (((*CANCTL0 & 0x10) == 0x00) && Wait3 < 5) 				//等待总线时钟同步
	{
		Wait3++;
	}

	CAN1RIER_RXFIE |= 0x01;										//禁止接收中断
}  

//CAN1发�
int CAN1_SendMsg(CAN_ConfigType *CAN_Cfg,CAN_MsgType *CAN_Msg)
{
	unsigned char send_buf = 0, sp = 0;
	int Reflag;
	CAN_RegAdd_Cfg(CAN_Cfg->Channel);
								//设置发�缓冲区、发送数据位�
	if (CAN_Msg->Len > CAN_MSG_MAXLEN)				//�查数据长�
	{
		Reflag = 0;
	}

	if (((*CANCTL0) & 0x10) == 0)								//�查�线时钟
	{
		Reflag = 0;
	}

	do
	{
		*CANTBSEL = *CANTFLG;
		send_buf  = CAN1TBSEL;	//������*CANTBSEL����Ͳ���
	} while (!send_buf);									//寻找空闲的缓冲器

	/*��չ֡ID����*/
	if (CAN_Msg->IDE)
	{
  		*CANTXIDR0 =  (unsigned char)(CAN_Msg->ID >> 21);
  		*CANTXIDR1 =  (unsigned char)(CAN_Msg->ID >> 13) & 0xE0;
  		*CANTXIDR1 |= 0x18;
  		*CANTXIDR1 |= (unsigned char)(CAN_Msg->ID >> 15) & 0x07;
  		*CANTXIDR2 =  (unsigned char)(CAN_Msg->ID >> 7);
  		*CANTXIDR3 =  (unsigned char)(CAN_Msg->ID << 1);
  		if (CAN_Msg->RTR)								//判断IDE�0标准�,1远程�
		{
			*CANTXIDR3 |= 0x01;
		}
		else
		{
			*CANTXIDR3 &= 0xFE;
		}
	}
	else
	{/*��׼֡ID����*/
  		*CANTXIDR0 =  (unsigned char)(CAN_Msg->ID >> 3);
  		*CANTXIDR1 =  (unsigned char)(CAN_Msg->ID << 5);
  		*CANTXIDR1 &= 0xF7;

  		if (CAN_Msg->RTR)								//判断IDE�0标准�,1远程�
		{
			*CANTXIDR1 |= 0x10;
		}
		else
		{
			*CANTXIDR1 &= 0xEF;
		}
	}

	for (sp = 0 ; sp < CAN_Msg->Len ; sp++)			//依次将数据写入寄存器
	{
		*(CANTXDSR0 + sp) = CAN_Msg->Data[sp];
	}

	*CANTXDLR  = CAN_Msg->Len;						//写入数据长度
	*CANTXTBPR = CAN_Msg->Prty;						//写入优先�
	*CANTFLG  = send_buf;									//清TXx标志(缓冲器准备发�)

	Reflag = 1;
	return Reflag;
}

//CAN1接收
int CAN1_GetMsg(CAN_ConfigType *CAN_Cfg,CAN_MsgType *CAN_Msg)
{
  	unsigned char sp;										  //设置接收数据位数
    int Reflag;
    CAN_RegAdd_Cfg(CAN_Cfg->Channel);
    
  	if (!((*CANRFLG) & 0x01))									  //�测接收标�
  	{
  		Reflag = 0;
  	}

  	if (((*CANRXIDR1) & 0x08) == 0x08)                         			  //判断是否为标准帧
  	{
      CAN_Msg->ID = ((unsigned long)((*CANRXIDR0) & 0xFF)) << 21;
  	  CAN_Msg->ID = CAN_Msg->ID | (((unsigned long)((*CANRXIDR1) & 0xE0)) << 13);
	    CAN_Msg->ID = CAN_Msg->ID | (((unsigned long)((*CANRXIDR1) & 0x07)) << 15);
	    CAN_Msg->ID = CAN_Msg->ID | (((unsigned long)((*CANRXIDR2) & 0xFF)) << 7);
	    CAN_Msg->ID = CAN_Msg->ID | (((unsigned long)((*CANRXIDR3) & 0xFE)) >> 1);
      CAN_Msg->IDE = 1;

      if ((*CANRXIDR3) & 0x01)                         			  //判断是否为远程帧
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
  	  	CAN_Msg->ID  = (unsigned long)((*CANRXIDR0) << 3) | //读出接收帧ID�8�
            	  	   (unsigned long)((*CANRXIDR1) >> 5) ; //并且与上读出接收帧ID�3�
        CAN_Msg->IDE = 0;
        if ((*CANRXIDR1) & 0x10)                         			  //判断是否为远程帧
  		{
  	  		CAN_Msg->RTR = 1;
  		}
  		else
  		{
  	  		CAN_Msg->RTR = 0;
 		}
 	}

  	CAN_Msg->Len = *CANRXDLR;						  //读出接收的数据长�

  	for (sp = 0; sp < CAN_Msg->Len; sp++)			  //依次读出接收的每�位数�
  	{
  		CAN_Msg->Data[sp] = *(CANRXDSR0 + sp);
  	}

  	*CANRFLG = 0x01;											  //清RXF标志�(缓冲器准备接�)

    Reflag = 1;
  	return Reflag;
}

//CAN1切换发�数�
void CAN1_SendDemo(void)
{
	CAN_Time++;
  	if (CAN_Time == 1)
  	{
  	  	if(CAN1_SendMsg(&CAN1_HwCfgType, &CAN_Msg1Type) == 1);
  	  	{
  	  	}
  	}
  	else if (CAN_Time == 2)
  	{
  	  	if(CAN1_SendMsg(&CAN1_HwCfgType, &CAN_Msg2Type) == 1)
  	  	{
  	  	}
  	}
 	else if (CAN_Time == 3)
  	{
    	if(CAN1_SendMsg(&CAN1_HwCfgType, &CAN_Msg3Type) == 1)
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
  	if (CAN1_GetMsg(&CAN1_HwCfgType, &CAN1_GetBufType) == 1)
  	{
      	if(CAN1_SendMsg(&CAN1_HwCfgType, &CAN1_GetBufType) == 1)
      	{
      	  //break;
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


#pragma CODE_SEG __NEAR_SEG NON_BANKED

void interrupt VectorNumber_Vpit0 PIT0(void)	//中断服务函数
{
    PITTF_PTF0 = 1;
    CAN1_SendDemo();							//PIT0中断
    //CAN1_GetToSend();
}

#pragma CODE_SEG DEFAULT

