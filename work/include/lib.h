#ifndef _LIB_H_INCLUDED_
#define _LIB_H_INCLUDED_

void *kz_memset(void *b, int c, long len);
void *kz_memcpy(void *dst, const void *src, long len);
int kz_memcmp(const void *b1, const void *b2, long len);
int kz_strlen(const char *s);
char *kz_strcpy(char *dst, const char *src);
int kz_strcmp(const char *s1, const char *s2);
int kz_strncmp(const char *s1, const char *s2, int len);

int kz_putc(unsigned char c);		/* １文字送信 */
unsigned char kz_getc(void);		 /* １文字受信 */
int kz_puts(unsigned char *str); /* 文字列送信 */
int kz_gets(unsigned char *buf); /* 文字列受信 */
int kz_putxval(unsigned long value, int column); /* 数値の16進表示 */

#endif
