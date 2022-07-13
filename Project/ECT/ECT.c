#include "ECT.h"


void ECT_Init(void)
{
	ECT_TSCR1_TFFCA = 1;  //定时器标志位快速清除
 	ECT_TSCR1_TEN = 1;    //定时器使能位：1=允许定时器正常工作; 0=使主定时器不起作用(包括计数器)
 	ECT_TIOS  = 0xFF;     //指定所有通道为输出比较方式
 	ECT_TCTL1 = 0x00;	  //后四个通道设置为定时器与输出引脚断开
 	ECT_TCTL2 = 0x00;     //前四个通道设置为定时器与输出引脚断开
	ECT_DLYCT = 0x00;	  //延迟控制功能禁止
	ECT_ICOVW = 0x00;	  //对应的寄存器允许被覆盖;  NOVWx = 1, 对应的寄存器不允许覆盖
	ECT_ICSYS = 0x00;	  //禁止IC及PAC的保持寄存器
	ECT_TIE   = 0x00;     //禁止所有通道定时中断
	ECT_TSCR2 = 0x07;	  //预分频系数pr2-pr0:111,时钟周期为4us,
	ECT_TFLG1 = 0xFF;	  //清除各IC/OC中断标志位
	ECT_TFLG2 = 0xFF;     //清除自由定时器中断标志位
}
