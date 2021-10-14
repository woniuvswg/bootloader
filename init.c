#include "init.h"
#include "nand.h"

int isBootFromNorFlash(void)
{
	volatile int *p = (volatile int *)0;
	int val;

	val = *p;
	*p = 0x12345678;
	if (*p == 0x12345678)
	{
		/* 写成功，从nand启动 */
		*p = val;
		return 0;
	}
	else
	{
		/* 写失败， 从nor 启动 */
		return 1;
	}
}

void copy_code_to_sdram(unsigned char *src, unsigned char *dest, unsigned int len)
{
	int i = 0;

	if (isBootFromNorFlash())
	{
		while (i < len)
		{
			dest[i] = src[i];
			i++;
		}
	}
	else
	{
		nand_init();
		nand_read((unsigned int)src, dest, len);
	}
}

void clear_bss(void)
{
	int *p = &__bss_start;
	for (; p < &__bss_end; p++)
	{
		*p = 0;
	}
}
