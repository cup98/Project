#include "Node.h"

int fault = 0;										//举例故障为无
int node = 1;										//设置节点标志位初始为1

void Node_Init(void)								//Node模块初始化
{

}

void No_Act(void)									//Node模块执行空函数
{

}

/*void Node_Poll(void)								//Node模块执行函数
{
	switch(node)									//判断节点标志位
	{
		case 1 :									//进入节点1：判断故障节点
		{
			if(fault == 0)							//判断有无故障
			{
				PrechargeM_StartPre();				//开始预充
				node = 2;							//准备进入节点2
			}
			else 									//若有故障
			{
				No_Act();							//执行空函数
				node = 1;							//准备进入节点1
			}
		}
		break;

		case 2 :									//进入节点2：预充完成判断节点
		{
			if(fault == 0)							//判断若无故障
			{
				if(PrechargeM_IsFail() == 0)		//判断有无超时
				{
					if(PrechargeM_IsFinish() == 1)	//判断是否预充完成
					{
						PrechargeM_Change();		//闭合总正，断开预充
						node = 3;					//准备进入节点3
					}
					else 							//未完成预充
					{
						No_Act();					//执行空函数
						node = 2;					//准备进入节点2
					}
				}
				else  								//启动预充超时
				{
					PrechargeM_StopPre();			//停止预充
					node = 1;						//准备进入节点1				}
			}
			else 									//有故障
			{
				PrechargeM_StopPre();				//断开预充
				node = 1;							//准备进入节点2
			}
		}
		break;

		case 3 :									//进入节点3：放电故障判断节点
		{
			if(fault == 0)							//判断若无故障
			{
				No_Act();							//执行空函数
				node = 3;							//准备进入节点3
			}
			else 									//有故障
			{
				PrechargeM_StopMaster();			//断开总正
				PrechargeM_StopPre();				//断开预充
				node = 1 ;							//准备进入节点1
			}
		}
		break;
	}
}*/

int Event_id(void)
{
	if (fault == 0)
	{
		return 1;
		if (PrechargeM_IsFail() == 0)
		{
			return 4;
			if (PrechargeM_IsFinish() == 1)
			{
				return 5;
			}
			else
			{
				return 6;
			}
		}
		else
			return 3;
	}
	else
		return 2;
}

void Node_Poll(void)
{
	State_Trans* pTrans;
	for (int i = 0; i < state_all.transNum; ++i)
	{
		if((state_all->transform[i].curState == state_all) &&
		   (state_all->transform[i].eventId  == int Event_id()))
		{
			pTrans = &state_all->transform[i];
		}
	}
	state_all.state = pTrans->nextState;
	switch (state_all.action)
	{
    	case Nu :
    	{
    		No_Act();
    	}break;

    	case StartPre :
    	{
    		PrechargeM_StartPre();
    	}break;

    	case StopPre :
    	{
    		PrechargeM_StopPre();
    	}break;

    	case StartMaster :
    	{
    		PrechargeM_Change();
    	}break;

    	case StopAll :
    	{
			  PrechargeM_StopMaster();
		  	PrechargeM_StopPre();
    	}break;
	}
}