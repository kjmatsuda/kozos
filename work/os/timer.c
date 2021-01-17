#include "defines.h"
#include "timer.h"

#define TIMER_NUM 3

#define TIMER_COMMON ((volatile struct timer_common *)0xffff60)
#define TIMER0 ((volatile struct timer *)0xffff68)
#define TIMER1 ((volatile struct timer *)0xffff70)
#define TIMER2 ((volatile struct timer *)0xffff78)

#define TIMER_INTERRUPT_ENABLE_BIT	 (4)

#define TIMER_INTERRUPT_INTERVAL_MSEC	 (10)

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

static struct {
	volatile struct timer *p_timer;
} l_timer_regs[TIMER_NUM] = {
	{ TIMER0 },
	{ TIMER1 },
	{ TIMER2 },
};

static struct timer_common *l_timer_common_reg = TIMER_COMMON;

void timer_init(int index)
{
	// 割込み周期を10msecにしたい。システムクロックφは25MHz
	// 分周比 1 / 4 、GRを62500 にしたら10msec周期で割込みがかかると思われる
	volatile struct timer *p_timer = l_timer_regs[index].p_timer;

	//// タイマコントロールレジスタ (16TCR)
	// 「GRA の コンペアマッチ／インプットキャプチャで16TCNT をクリア」にする
	p_timer->tcr &= ~(1<<6);
	p_timer->tcr |= (1<<5);

	// クロック選択(φ/4)
	p_timer->tcr &= ~(1<<2);
	p_timer->tcr |= (1<<1);
	p_timer->tcr &= ~(1<<0);

	//// タイマI/Oコントロールレジスタ(TIOR)
	// デフォルトで「アウトプットコンペアレジスタ」になっているからそのままでよい

	//// ジェネラルレジスタGRAを設定
	// 62500 (0xF424)
	p_timer->gra_high = 0xF4;
	p_timer->gra_low = 0x24;

	// コンペアマッチインタラプトイネーブルを許可にする
	timer_interrupt_enable(index);
}

void timer_start(int index)
{
	l_timer_common_reg->tstr |= (1 << index);
}

void timer_stop(int index)
{
	l_timer_common_reg->tstr &= ~(1 << index);
}

void timer_interrupt_enable(int index)
{
	l_timer_common_reg->tisra |= (1 << (index + TIMER_INTERRUPT_ENABLE_BIT));
}

void timer_interrupt_disable(int index)
{
	l_timer_common_reg->tisra &= ~(1 << (index + TIMER_INTERRUPT_ENABLE_BIT));
}

void timer_interrupt_flg_clear(int index)
{
	l_timer_common_reg->tisra &= ~(1 << index);
}

int get_timer_interrupt_interval_msec()
{
	return TIMER_INTERRUPT_INTERVAL_MSEC;
}
