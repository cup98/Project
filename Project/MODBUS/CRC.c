#include "CRC.h"

unsigned int Crc16_MODBUS (unsigned int Crc16)
{
	unsigned int Crc16_Init = 0xFFFF;
	unsigned int XOROUT = 0xA001;
	int Crc16_1 , Crc16_2;
	Crc16_1 = (Crc16 >> 8);
	Crc16_2 = (Crc16 & 0x00FF);
	for (int i = 0; i < 2; ++i)
	{
		if (i == 0)
			Crc16_Init ^= Crc16_1;
		else
			Crc16_Init ^= Crc16_2;

		for (int j = 0; j < 8; j++)
		{
			if((Crc16_Init & 0x0001) == 1)
			{
				Crc16_Init >>= 1;
				Crc16_Init ^= XOROUT;
			}
			else
			{
				Crc16_Init >>= 1;
			}
		}
	}
	Crc16_Init = ((Crc16_Init & 0xFF00) << 8) |
				 ((Crc16_Init & 0x00FF) >> 8);
	return Crc16_Init;
}