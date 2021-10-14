#include "led.h"

void led_on(void)
{
	/* 打开4个led灯 */
	//put the all led port to output mode
	rGPBCON = (0x55<<10);
	//put the all led data to 0
	rGPBDAT = (0x0<<5);
}
