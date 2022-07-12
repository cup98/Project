#ifndef __NODE_H
#define __NODE_H

#include "hidef.h"
#include "derivative.h"

typedef enum _Node_State
{
	Node_1 = 1,
	Node_2,
	Node_3,
	Node_4,
	Node_5,
} Node_State;

typedef enum _Event_ID
{
    Fault_Out = 1,
    Fault_Over,
    Time_Out,
    Time_Over,
    Pre_Out,
    Pre_Over,
} Event_ID;

typedef enum _Action
{
    Nu = 1,
    StartPre,
    StopPre,
    StartMaster,
    StopAll,
} Action;

typedef struct _State_Trans
{
    Node_State 	curState;					//当前状态
    Event_ID 	  eventId;					//事件ID
    Node_State 	nextState;					//下个状态
    Action 		  action;					//具体表现
} State_Trans;

typedef struct _State_All
{
    Node_State state;
    int transNum;
    State_Trans* transform;
} State_All;

State_Trans statetrans[] =
{
	{Node_1,Fault_Out,Node_1,Nu},
	{Node_1,Fault_Over,Node_2,StartPre},

	{Node_2,Fault_Out,Node_1,StopPre},
	{Node_2,Fault_Over,Node_3,Nu},

	{Node_3,Time_Out,Node_1,StopPre},
	{Node_3,Time_Over,Node_4,Nu},

	{Node_4,Fault_Out,Node_2,Nu},
	{Node_4,Fault_Over,Node_5,StartMaster},

	{Node_5,Pre_Out,Node_1,StopAll},
	{Node_5,Pre_Over,Node_5,Nu},
};

State_All state_all;
state_all.state = Node_1;
state_all.transNum = 8;
state_all.transform = statetrans;
//节点流程控制模块初始化函数
extern void Node_Init(void);
extern int Event_id(void);
//Node模块执行函数
extern void Node_Poll(void);

//空函数
extern void No_Act(void);



#endif