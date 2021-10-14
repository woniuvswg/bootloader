/*
*
*INIT codes for START ASM
*
*/

#ifndef _INIT_H_
#define _INIT_H_

int isBootFromNorFlash(void);
void copy_code_to_sdram(unsigned char *src, unsigned char *dest, unsigned int len);
void clear_bss(void);

/* bss常量，来自链接文件 */
extern int __bss_start;
extern int __bss_end;

#endif
