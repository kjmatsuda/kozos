#include "CppUTest/TestHarness.h"

extern "C"
{
#include "timer.h"
}

TEST_GROUP(timer)
{
	void setup()
	{
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
	BITS_EQUAL(0x22, (unsigned char)get_timer_ctrl_register(0), 0x7F);
}
