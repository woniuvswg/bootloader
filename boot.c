#include "led.h"
#include "uart.h"
#include "setup.h"
#include "nand.h"
#include "boot.h"

int main(void)
{
	void (*theKernel)(int zero, int arch, unsigned int params);
	volatile unsigned int *p = (volatile unsigned int *)0x30008000;
	/* 打开led灯 */
	led_on();
	/* 初始化串口 */
	uart0_init();
	put_char('\0');
	put_string("\n");
	put_string("Boot to kernel function\n");
	put_string("Copy kernel from nand\n");

	/* 从nand里把内核读入内存，nand地址0x60000的zImage，内存地址为0x30008000 */
	nand_read(0x60000, (unsigned char *)0x30008000, 0x300000);
	put_hex(0x1234ABCD);
	put_string("\n");
	put_hex(*p);
	put_string("\n");

	/* 设置内核启动参数 */
	put_string("Set boot params\n");
	setup_start_tag();
	setup_mem_tags();
	setup_cmdline_tag("noinitrd root=/dev/mtdblock3 init=/linuxrc console=ttySAC0");
	setup_end_tag();

	/* boot to kernel */
	put_string("Booting kernel......\n");
	theKernel = (void (*)(int, int, unsigned int))0x30008000;
	/* arch type 1999 */
	theKernel(0, 1999, 0x30000100);

	/* 如果一切正常， 就不会执行到这里了 */
	put_string("Error!\n");

	return -1;
	
}

void setup_start_tag(void)
{
	params->hdr.tag = ATAG_CORE;
    params->hdr.size = tag_size (tag_core);

    params->u.core.flags = 0;
    params->u.core.pagesize = 0;
    params->u.core.rootdev = 0;

    params = tag_next (params);
}

void setup_mem_tags(void)
{
	params->hdr.tag = ATAG_MEM;
    params->hdr.size = tag_size (tag_mem32);

    params->u.mem.start = 0x30000000;
    params->u.mem.size  = 64*1024*1024;

    params = tag_next (params);
}

int str_len(char *str)
{
	int i = 0;
    while (str[i])
    {
        i++;
    }
    return i;
}

void str_cpy(char *dest, char *src)
{
	while ((*dest++ = *src++) != '\0');
}

void setup_cmdline_tag(char *cmd)
{
	int len = str_len(cmd) + 1;

    params->hdr.tag  = ATAG_CMDLINE;
    params->hdr.size = (sizeof (struct tag_header) + len + 3) >> 2;

    str_cpy (params->u.cmdline.cmdline, cmd);

    params = tag_next (params);
}

void setup_end_tag(void)
{
	params->hdr.tag = ATAG_NONE;
    params->hdr.size = 0;
}


