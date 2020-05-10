#include "defines.h"
#include "ioport.h"

// TODO 実際にはポートは11個あるが、ひとまず5個について実装する
#define IOPORT_NUM 5

#define IOPORT_DATADIR_REG_ADDR		((volatile uint8*)0xee000)

#define IOPORT_DATA_REG_ADDR		((volatile uint8*)0xfffd0)

static volatile uint8* p_data_dir_regs = IOPORT_DATADIR_REG_ADDR;

static volatile uint8* p_data_regs = IOPORT_DATA_REG_ADDR;

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

/* データディレクション設定 */
int ioport_set_data_direction(int port_no, uint8 data_dir)
{
	int port_idx = port_no - 1;
	volatile uint8 *p_data_dir_reg = &(p_data_dir_regs[port_idx]);
	*p_data_dir_reg = data_dir;

	return 0;
}

/* データ設定 */
int ioport_set_data(int port_no, uint8 data)
{
	int port_idx = port_no - 1;
	volatile uint8 *p_data_reg = &(p_data_regs[port_idx]);
	*p_data_reg = data;

	return 0;
}
