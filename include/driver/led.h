#ifndef _LED_H_
#define _LED_H_
/* 控制led灯的GPIO寄存器 */
#define rGPBCON (*((volatile unsigned long *)0x56000010))		//Configures the pins of port B
#define rGPBDAT (*((volatile unsigned long *)0x56000014))		//The data register for port B
void led_on(void);
#endif
