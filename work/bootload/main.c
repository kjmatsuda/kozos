#include "defines.h"
#include "interrupt.h"
#include "serial.h"
#include "xmodem.h"
#include "elf.h"
#include "lib.h"

static int init(void)
{
	/* 以下はリンカ・スクリプトで定義してあるシンボル */
	extern int erodata, data_start, edata, bss_start, ebss;

	/*
	 * データ領域とBSS領域を初期化する．この処理以降でないと，
	 * グローバル変数が初期化されていないので注意．
	 */
	kz_memcpy(&data_start, &erodata, (long)&edata - (long)&data_start);
	kz_memset(&bss_start, 0, (long)&ebss - (long)&bss_start);

	/* ソフトウエア・割り込みベクタを初期化する */
	softvec_init();

	/* シリアルの初期化 */
	serial_init(SERIAL_DEFAULT_DEVICE);

	return 0;
}

/* メモリの16進ダンプ出力 */
static int dump(char *buf, long size)
{
	long i;

	if (size < 0) {
		kz_puts("no data.\n");
		return -1;
	}
	for (i = 0; i < size; i++) {
		kz_putxval(buf[i], 2);
		if ((i & 0xf) == 15) {
			kz_puts("\n");
		} else {
			if ((i & 0xf) == 7) kz_puts(" ");
			kz_puts(" ");
		}
	}
	kz_puts("\n");

	return 0;
}

static void wait()
{
	volatile long i;
	for (i = 0; i < 300000; i++)
		;
}

int main(void)
{
	static char buf[16];
	static long size = -1;
	static unsigned char *loadbuf = NULL;
	char *entry_point;
	void (*f)(void);
	extern int buffer_start; /* リンカ・スクリプトで定義されているバッファ */

	INTR_DISABLE; /* 割込み無効にする */

	init();

	kz_puts("kzload (kozos boot loader) started.\n");

	while (1) {
		kz_puts("kzload> "); /* プロンプト表示 */
		kz_gets(buf); /* シリアルからのコマンド受信 */

		if (!kz_strcmp(buf, "load")) { /* XMODEMでのファイルのダウンロード */
			loadbuf = (char *)(&buffer_start);
			size = xmodem_recv(loadbuf);
			wait(); /* 転送アプリが終了し端末アプリに制御が戻るまで待ち合わせる */
			if (size < 0) {
	kz_puts("\nXMODEM receive error!\n");
			} else {
	kz_puts("\nXMODEM receive succeeded.\n");
			}
		} else if (!kz_strcmp(buf, "dump")) { /* メモリの16進ダンプ出力 */
			kz_puts("size: ");
			kz_putxval(size, 0);
			kz_puts("\n");
			dump(loadbuf, size);
		} else if (!kz_strcmp(buf, "run")) { /* ELF形式ファイルの実行 */
			entry_point = elf_load(loadbuf); /* メモリ上に展開(ロード) */
			if (!entry_point) {
	kz_puts("run error!\n");
			} else {
	kz_puts("starting from entry point: ");
	kz_putxval((unsigned long)entry_point, 0);
	kz_puts("\n");
	f = (void (*)(void))entry_point;
	f(); /* ここで，ロードしたプログラムに処理を渡す */
	/* ここには返ってこない */
			}
		} else {
			kz_puts("unknown.\n");
		}
	}

	return 0;
}
