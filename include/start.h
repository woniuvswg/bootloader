#ifndef _START_H_
#define _START_H_

/* CPU时钟频率*/
#define S3C2440_MPLL_200MHZ ((0X5c<<12)|(0x01<<4)|(0x02))
#define S3C2440_MPLL_400MHZ ((0X5c<<12)|(0x01<<4)|(0x01))

/* 内存控制寄存器基址*/
#define MEM_CTL_BASE 0x48000000

/* 看门狗寄存器 */
#define rWTCON 0x53000000

/* 时钟寄存器 */
#define rCLKDIV 0x4C000014
#define rMPLLCON 0x4c000004

/* 内存 */
#define MEM_TOP 0x34000000
#define MEM_BASE 0X30000000

#endif


