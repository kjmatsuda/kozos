#include "CppUTest/TestHarness.h"
#include <string.h>

extern "C"
{
#include "timer.h"
}

TEST_GROUP(timer)
{
	void setup()
	{
		struct timer_common timer_common_reg;
		memset(&timer_common_reg, 0x00, sizeof(timer_common_reg));
		set_timer_common_reg_address(&timer_common_reg);

		struct timer timer_regs[TIMER_NUM] = { 0 };
		memset(timer_regs, 0x00, sizeof(timer_regs));
		for (int ii = 0; ii < TIMER_NUM; ii++)
		{
			set_timer_reg_address(ii, &(timer_regs[ii]));
		}
	}
	void teardown()
	{
	}
};

TEST(timer, timer_init)
{
	timer_init(0);

	// ビット7 リザーブビット
	// ビット6～5 0b01  コンペアマッチ／インプットキャプチャで16TCNT をクリア
	// ビット4～3 0b00  立ち上がりエッジでカウント
	// ビット2～0 0b010 内部クロック (φ/4)
	uint8 actual = get_timer_ctrl_register(0);
	BITS_EQUAL(0x22, actual, 0x7F);
}

TEST(timer, timer_start)
{
	timer_start(0);

	BITS_EQUAL(0x01, (unsigned char)get_timer_common_start_register(), 0x01);
}

TEST(timer, timer_stop)
{
	timer_start(0);
	timer_stop(0);

	BITS_EQUAL(0x00, (unsigned char)get_timer_common_start_register(), 0x01);
}
