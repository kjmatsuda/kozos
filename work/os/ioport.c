#include "defines.h"
#include "ioport.h"

#define IOPORT_NUM 11

#define DATADIR_REGADDR		((struct data_dir_regs *)0xfee000)

#define DATA_REGADDR		((struct data_regs *)0xffffd0)

struct data_dir_regs {
	volatile uint8 regs[IOPORT_NUM];
};

static struct data_dir_regs *l_ddr = DATADIR_REGADDR;

struct data_regs {
	volatile uint8 regs[IOPORT_NUM];
};

static struct data_regs *l_dr = DATA_REGADDR;

/* デバイス初期化 */
int ioport_init()
{
	int port_no = 1;

	for (port_no = 1; port_no <= IOPORT_NUM; port_no++)
	{
		// データディレクション初期化
		ioport_set_data_direction(port_no, 0);
		// データ初期化
		ioport_set_data(port_no, 0);
	}

	return 0;
}

// TODO データディレクション設定、ビットをON/OFFする関数を作る
/* データディレクション設定 */
int ioport_set_data_direction(int port_no, uint8 data_dir)
{
	int port_idx = port_no - 1;
	l_ddr->regs[port_idx] = data_dir;

	return 0;
}

// TODO データ設定、ビットをON/OFFする関数を作る
/* データ設定 */
int ioport_set_data(int port_no, uint8 data)
{
	int port_idx = port_no - 1;
	l_dr->regs[port_idx] = data;

	return 0;
}

/* データ取得 */
int ioport_get_data(int port_no, uint8 *p_data)
{
	int port_idx = port_no - 1;
	*p_data = l_dr->regs[port_idx];

	return 0;
}

/* データビットON判定取得 */
int ioport_data_bit_is_on(int port_no, int bit)
{
	int port_idx = port_no - 1;
	l_dr->regs[port_idx];

	return (l_dr->regs[port_idx] & (1 << bit)) ? 1 : 0;
}
