#ifndef _TIMER_H_INCLUDED_
#define _TIMER_H_INCLUDED_

#include "defines.h"

#define TIMER_NUM 3

struct timer_common {
	volatile uint8 tstr;		// タイマスタートレジスタ
	volatile uint8 tsnc;		// タイマシンクロレジスタ
	volatile uint8 tmdr;		// タイマモードレジスタ
	volatile uint8 tolr;		// タイマアウトプットレベルセットレジスタ
	volatile uint8 tisra;		// タイマインタラプトステータスレジスタA
	volatile uint8 tisrb;		// タイマインタラプトステータスレジスタB
	volatile uint8 tisrc;		// タイマインタラプトステータスレジスタC
};

struct timer {
	volatile uint8 tcr;				// タイマコントロールレジスタ
	volatile uint8 tior;			// タイマI/Oコントロールレジスタ
	volatile uint8 tcnt_high;		// タイマカウンタ(High)
	volatile uint8 tcnt_low;		// タイマカウンタ(Low)
	volatile uint8 gra_high;		// ジェネラルレジスタA(High)
	volatile uint8 gra_low;			// ジェネラルレジスタA(Low)
	volatile uint8 grb_high;		// ジェネラルレジスタB(High)
	volatile uint8 grb_low;			// ジェネラルレジスタB(Low)
};

void timer_init(int index);

void timer_start(int index);

void timer_stop(int index);

void timer_interrupt_enable(int index);

void timer_interrupt_disable(int index);

void timer_interrupt_flg_clear(int index);

int get_timer_interrupt_interval_msec();

#ifdef CPPUTEST
void set_timer_common_reg_address(struct timer_common *p_timer_common_reg);
void set_timer_reg_address(int index, struct timer *p_timer_reg);
uint8 get_timer_common_start_register();
uint8 get_timer_common_sync_register();
uint8 get_timer_common_mode_register();
uint8 get_timer_common_output_level_set_register();
uint8 get_timer_common_intr_sts_register_a();
uint8 get_timer_common_intr_sts_register_b();
uint8 get_timer_common_intr_sts_register_c();
uint8 get_timer_ctrl_register(int index);
uint8 get_timer_io_ctrl_register(int index);
uint8 get_timer_counter_high(int index);
uint8 get_timer_counter_low(int index);
uint8 get_timer_general_register_a_high(int index);
uint8 get_timer_general_register_a_low(int index);
uint8 get_timer_general_register_b_high(int index);
uint8 get_timer_general_register_b_low(int index);
#endif

#endif
