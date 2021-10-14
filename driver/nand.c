#include "nand.h"

void delay(count)
{
	volatile int i;
	for (i = 0; i < count; i++);
}

void nand_init(void)
{
	/* 设置时序 */
	rNFCONF = (TACLS<<12)|(TWRPH0<<8)|(TWRPH1<<4);
	/* 使能nand flash控制器，初始化ECC，禁止片选 */
	rNFCONT = (1<<4)|(1<<1)|(1<<0);
}

void nand_select(void)
{
	rNFCONT &= ~(1<<1);
}

void nand_unselect(void)
{
	rNFCONT |= (1<<1);
}

void nand_cmd(unsigned char cmd)
{
	rNFCMD = cmd;
	delay(10);
}

void nand_addr(unsigned int addr)
{
	unsigned int col = addr %2048;		//列地址
	unsigned int page = addr / 2048;	//页地址

	rNFADDR = col & 0xff;
	delay(10);
	rNFADDR = (col>>8) & 0xff;
	delay(10);

	rNFADDR = page & 0xff;
	delay(10);
	rNFADDR = (page>>8) & 0xff;
	delay(10);
	rNFADDR = (page>>16) & 0xff;
	delay(10);
}

void nand_wait_ready(void)
{
	while (!(rNFSTAT & 1));
}

unsigned char nand_data(void)
{
	return rNFDATA;
}

void nand_read(unsigned int addr, unsigned char *buf, unsigned int len)
{
	int col = addr % 2048;
	int i = 0;

	/* 选中 */
	nand_select();

	while (i < len)
	{
		/* 发出读命令 */
		nand_cmd(0x00);
		/* 发出地址：5步发出 */
		nand_addr(addr);
		/* 发出读命令 */
		nand_cmd(0x30);
		/* 判断状态 */
		nand_wait_ready();
		/* 读数据 */
		for (;(col < 2048) && (i < len); col++)
		{
			buf[i] = nand_data();
			i++;
			addr++;
		}
		col = 0;
	}

	/* 取消选中 */
	nand_unselect();
}