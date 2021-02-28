#include "defines.h"
#include "kozos.h"
#include "interrupt.h"
#include "lib.h"
#include "ioport.h"

/* システム・タスクとユーザ・タスクの起動 */
static int start_threads(int argc, char *argv[])
{
	kz_run(consdrv_main, "consdrv",	1, 0, 0x200, 0, NULL);
	kz_run(command_main, "command",	8, 0, 0x200, 0, NULL);
	kz_run(timer_master_main, "timer_master",	2, 0, 0x200, 0, NULL);
	kz_run(timer_task_main, "timer_task",	3, 50, 0x200, 0, NULL);

	kz_chpri(15); /* 優先順位を下げて，アイドルスレッドに移行する */
#ifndef CPPUTEST
	INTR_ENABLE; /* 割込み有効にする */
#endif
	while (1) {
#ifndef CPPUTEST
		asm volatile ("sleep"); /* 省電力モードに移行 */
#endif
	}

	return 0;
}

int main(void)
{
#ifndef CPPUTEST
	INTR_DISABLE; /* 割込み無効にする */
#endif
	kz_puts("kozos boot succeed!\n");

	/* OSの動作開始 */
	kz_start(start_threads, "idle", 0, 0, 0x100, 0, NULL);
	/* ここには戻ってこない */

	return 0;
}
