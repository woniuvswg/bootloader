#ifndef _NAND_H_
#define _NAND_H_
/* nand flash control register */
#define rNFCONF		(*(volatile unsigned long *)0x4E000000)		//NAND Flash configuration
#define rNFCONT		(*(volatile unsigned long *)0x4E000004)      //NAND Flash control
#define rNFCMD		(*(volatile unsigned char *)0x4E000008)      //NAND Flash command
#define rNFADDR		(*(volatile unsigned char *)0x4E00000C)      //NAND Flash address
#define rNFDATA		(*(volatile unsigned char *)0x4E000010)      //NAND Flash data
#define rNFDATA8	(*(volatile unsigned char *)0x4E000010)     //NAND Flash data
#define NFDATA		(0x4E000010)      						//NAND Flash data address
#define rNFMECCD0	(*(volatile unsigned long *)0x4E000014)      //NAND Flash ECC for Main Area
#define rNFMECCD1	(*(volatile unsigned long *)0x4E000018)
#define rNFSECCD	(*(volatile unsigned long *)0x4E00001C)		//NAND Flash ECC for Spare Area
#define rNFSTAT		(*(volatile unsigned char *)0x4E000020)		//NAND Flash operation status
#define rNFESTAT0	(*(volatile unsigned long *)0x4E000024)
#define rNFESTAT1	(*(volatile unsigned long *)0x4E000028)
#define rNFMECC0	(*(volatile unsigned long *)0x4E00002C)
#define rNFMECC1	(*(volatile unsigned long *)0x4E000030)
#define rNFSECC		(*(volatile unsigned long *)0x4E000034)
#define rNFSBLK		(*(volatile unsigned long *)0x4E000038)		//NAND Flash Start block address
#define rNFEBLK		(*(volatile unsigned long *)0x4E00003C)		//NAND Flash End block address
/* nand初始化值 */
#define TACLS   0
#define TWRPH0  1
#define TWRPH1  0

void delay(int count);
void nand_init(void);
void nand_select(void);
void nand_unselect(void);
void nand_cmd(unsigned char cmd);
void nand_addr(unsigned int addr);
void nand_wait_ready(void);
unsigned char nand_data(void);
void nand_read(unsigned int addr, unsigned char *buf, unsigned int len);

#endif
