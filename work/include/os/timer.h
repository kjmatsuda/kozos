#ifndef _TIMER_H_INCLUDED_
#define _TIMER_H_INCLUDED_

#include "defines.h"

void timer_init(int index);

void timer_start(int index);

void timer_stop(int index);

void timer_interrupt_enable(int index);

void timer_interrupt_disable(int index);

void timer_interrupt_flg_clear(int index);

int get_timer_interrupt_interval_msec();

// CPPUTEST用関数
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
