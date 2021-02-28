#ifndef _TIMER_H_INCLUDED_
#define _TIMER_H_INCLUDED_

void timer_init(int index);

void timer_start(int index);

void timer_stop(int index);

void timer_interrupt_enable(int index);

void timer_interrupt_disable(int index);

void timer_interrupt_flg_clear(int index);

int get_timer_interrupt_interval_msec();
#endif
