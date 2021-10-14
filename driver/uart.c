#include "uart.h"

void uart0_init(void)
{
	rGPHCON  |= 0xa0;    // GPH2,GPH3用作TXD0,RXD0
    rGPHUP   = 0x0c;     // GPH2,GPH3内部上拉

    rULCON0  = 0x03;     // 8N1(8个数据位，无较验，1个停止位)
    rUCON0   = 0x05;     // 查询方式，UART时钟源为PCLK
    rUFCON0  = 0x00;     // 不使用FIFO
    rUMCON0  = 0x00;     // 不使用流控
    rUBRDIV0 = UART_BRD; // 波特率为115200
}

void put_char(unsigned char c)
{
	if (c == '\n')
	{
		while(!(rUTRSTAT0 & TXD0READY));		//等待，直到发送缓冲区中的数据已经全部发送出去 
		rUTXH0 = '\r';						//向UTXH0寄存器中写入数据，UART即自动将它发送出去
	}
	while(!(rUTRSTAT0 & TXD0READY));
		rUTXH0 = c;
}

void put_string(char * str)
{
	while (*str)
	{
		put_char(*str++);
	}
}

void put_hex(unsigned int val)
{
	int i;
	int j;

	put_string("0x");

	for (i = 0; i < 8; i++)
	{
		j = (val >> ((7 - i)*4)) & 0xf;
		if ((j >= 0) && (j <= 9))
		{
			put_char('0' + j);
		}
		else
		{
			put_char('A' + j - 0xa);
		}
	}
}