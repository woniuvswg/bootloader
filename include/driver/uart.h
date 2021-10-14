#ifndef _UART_H_
#define _UART_H_

/* uart0 control registers */
#define rULCON0 (*((volatile unsigned char *)0x50000000))		//UART channel 0 line control register
#define rUCON0 (*((volatile unsigned long *)0x50000004))		//UART channel 0 control register
#define rUFCON0 (*((volatile unsigned char *)0x50000008))		//UART channel 0 FIFO control register
#define rUMCON0 (*((volatile unsigned char *)0x5000000C))		//UART channel 0 Modem control register
#define rUTRSTAT0 (*((volatile unsigned char *)0x50000010))		//UART channel 0 Tx/Rx status register
#define rUERSTAT0 (*((volatile unsigned char *)0x50000014))		//UART channel 0 Rx error status register
#define rUFSTAT0 (*((volatile unsigned long *)0x50000018))		//UART channel 0 FIFO status register
#define rUMSTAT0 (*((volatile unsigned char *)0x5000001C))		//UART channel 0 modem status register
/* little endian */
#define rUTXH0 (*((volatile unsigned char *)0x50000020))		//UART channel 0 transmit buffer register 
#define rURXH0 (*((volatile unsigned char *)0x50000024))		//UART channel 0 receive buffer register
/*
*UBRDIVn = (int)(40000000 / (115200 x 16) ) -1
*= (int)(21.7) -1 [round to the nearest whole number]
*= 22 -1 = 21
*/
#define rUBRDIV0 (*((volatile unsigned long *)0x50000028))		//Baud rate divisior register 0


/* UART0 gpio h port gph2 gph3  */
#define rGPHCON (*((volatile unsigned long *)0x56000070))		//Configures the pins of port H
#define rGPHDAT (*((volatile unsigned long *)0x56000074))		//The data register for port H
#define rGPHUP (*((volatile unsigned long *)0x56000078))		//pull-up disable register for port H

/* 波特率设置 */
#define PCLK            50000000    // init.c中的clock_init函数设置PCLK为50MHz
#define UART_CLK        PCLK        //  UART0的时钟源设为PCLK
#define UART_BAUD_RATE  115200      // 波特率
#define UART_BRD        ((UART_CLK  / (UART_BAUD_RATE * 16)) - 1)

/*发送状态设置*/
#define TXD0READY   (1<<2)

void uart0_init(void);
void put_char(unsigned char c);
void put_string(char *str);
void put_hex(unsigned int val);

#endif
