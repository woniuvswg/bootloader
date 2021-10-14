#ifndef _BOOT_H_
#define _BOOT_H_

static struct tag *params;
void setup_start_tag(void);
void setup_mem_tags(void);
int str_len(char *str);
void str_cpy(char *dest, char *src);
void setup_cmdline_tag(char *cmd);
void setup_end_tag(void);

#endif
