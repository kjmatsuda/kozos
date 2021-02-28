#include "defines.h"
#include "kozos.h"
#include "intr.h"
#include "interrupt.h"
#include "lib.h"
#include "timer.h"

static void timer_intr(void)
{
	// 割込み発生フラグクリア
	timer_interrupt_flg_clear(0);

	// 周期タスクのタイマー残り時間を減算
	kx_dec_wait_time(get_timer_interrupt_interval_msec());
}

int timer_master_main(int argc, char *argv[])
{
	kz_setintr(SOFTVEC_TYPE_TIMER, timer_intr);		/* 割込みハンドラ設定 */

	// タイマー初期化
	timer_init(0);
	timer_start(0);
	kz_puts("timer_init done.\n");

	return 0;
}
