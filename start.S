#include "start.h"


.text
.global _start
_start:

	/* 关闭看门狗 */
	ldr r0, =rWTCON
	mov r1, #0
	str r1, [r0]

	/* 设置时钟 */
	// 设置时钟分频比 1:4:8
	ldr r0, =rCLKDIV
	mov r1, #0x05
	str r1, [r0]

	//HDIVN非0，cpu总线模式要改为异步模式
	mrc p15, 0, r1, c1, c0, 0       /* 读出控制寄存器 */ 
    orr r1, r1, #0xc0000000         /* 设置为“asynchronous bus mode” */
    mcr p15, 0, r1, c1, c0, 0       /* 写入控制寄存器 */

	// 设置pclk 位50M
	ldr r0, =rMPLLCON
	ldr r1, =S3C2440_MPLL_400MHZ
	str r1, [r0]

	/* 启动ICache 
	mrc p15,0,r0,c1,c0,0 @ read control reg
    orr r0, r0,#(1<<12)
    mcr p15,0,r0,c1,c0,0 @write it back
	*/
    /* 初始化sdram */
    ldr r0, =MEM_CTL_BASE
    adr r1, sdram_config
    add r3, r0, #(13*4)
1:
	ldr r2, [r1], #4
	str r2, [r0], #4
	cmp r0, r3
	bne 1b

	/* 设置栈指针 */
	ldr sp, =MEM_TOP

	/* 重定位：把bootloader 本身的代码从nor或者nand复制到sdram */
	mov r0, #0;				//复制函数的第一个参数
	ldr r1, =_start			//第二个参数，链接文件的链接地址：0x33f80000
	ldr r2, =__bss_start	//复制代码结束地址
	sub r2, r2, r1			//第三个参数：代码得长度

	bl copy_code_to_sdram

	/* 把初始化参数段清零 */
	bl clear_bss

	/* 执行入口函数main*/
	ldr lr, =halt
	ldr pc, =main
halt:
	b halt

sdram_config:
	.long 0x22011110     //BWSCON
    .long 0x00000700     //BANKCON0
    .long 0x00000700     //BANKCON1
    .long 0x00000700     //BANKCON2
    .long 0x00000700     //BANKCON3  
    .long 0x00000700     //BANKCON4
    .long 0x00000700     //BANKCON5
    .long 0x00018005     //BANKCON6
    .long 0x00018005     //BANKCON7
    .long 0x008C04F4     // REFRESH
    .long 0x000000B1     //BANKSIZE
    .long 0x00000030     //MRSRB6
    .long 0x00000030     //MRSRB7

	
