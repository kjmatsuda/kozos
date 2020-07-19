#ifndef _LIB_H_INCLUDED_
#define _LIB_H_INCLUDED_

void *k_memset(void *b, int c, long len);
void *k_memcpy(void *dst, const void *src, long len);
int k_memcmp(const void *b1, const void *b2, long len);
int k_strlen(const char *s);
char *k_strcpy(char *dst, const char *src);
int k_strcmp(const char *s1, const char *s2);
int k_strncmp(const char *s1, const char *s2, int len);

int k_putc(unsigned char c);		/* １文字送信 */
unsigned char k_getc(void);		 /* １文字受信 */
int k_puts(unsigned char *str); /* 文字列送信 */
int k_gets(unsigned char *buf); /* 文字列受信 */
int k_putxval(unsigned long value, int column); /* 数値の16進表示 */

#endif
