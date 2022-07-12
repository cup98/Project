#ifndef __PIT_H
#define __PIT_H

#include "derivative.h"

static CAN_MsgType CPIT =
{
	0x03,
	0,
	{10,10,10,10,10,10,10,10},
	8,
	0,
};

extern void PIT_Init(void);
extern int PIT0_Init(void);
extern int PIT1_Init(void);


#endif
