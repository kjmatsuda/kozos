#include "defines.h"
#include "ioport.h"

// TODO 実際にはポートは11個あるが、ひとまず5個について実装する
#define IOPORT_NUM 5

#define IOPORT1_DATADIR_REG_ADDR		(*(volatile uint8*)0xfee000)
#define IOPORT2_DATADIR_REG_ADDR		(*(volatile uint8*)0xfee001)
#define IOPORT3_DATADIR_REG_ADDR		(*(volatile uint8*)0xfee002)
#define IOPORT4_DATADIR_REG_ADDR		(*(volatile uint8*)0xfee003)
#define IOPORT5_DATADIR_REG_ADDR		(*(volatile uint8*)0xfee004)
#define IOPORT6_DATADIR_REG_ADDR		(*(volatile uint8*)0xfee005)
#define IOPORT8_DATADIR_REG_ADDR		(*(volatile uint8*)0xfee007)
#define IOPORT9_DATADIR_REG_ADDR		(*(volatile uint8*)0xfee008)
#define IOPORTA_DATADIR_REG_ADDR		(*(volatile uint8*)0xfee009)
#define IOPORTB_DATADIR_REG_ADDR		(*(volatile uint8*)0xfee00A)

#define IOPORT1_DATA_REG_ADDR		(*(volatile uint8*)0xffffd0)
#define IOPORT2_DATA_REG_ADDR		(*(volatile uint8*)0xffffd1)
#define IOPORT3_DATA_REG_ADDR		(*(volatile uint8*)0xffffd2)
#define IOPORT4_DATA_REG_ADDR		(*(volatile uint8*)0xffffd3)
#define IOPORT5_DATA_REG_ADDR		(*(volatile uint8*)0xffffd4)
#define IOPORT6_DATA_REG_ADDR		(*(volatile uint8*)0xffffd5)
#define IOPORT7_DATA_REG_ADDR		(*(volatile uint8*)0xffffd6)
#define IOPORT8_DATA_REG_ADDR		(*(volatile uint8*)0xffffd7)
#define IOPORT9_DATA_REG_ADDR		(*(volatile uint8*)0xffffd8)
#define IOPORTA_DATA_REG_ADDR		(*(volatile uint8*)0xffffd9)
#define IOPORTB_DATA_REG_ADDR		(*(volatile uint8*)0xffffda)

//static volatile uint8* p_data_dir_regs = IOPORT_DATADIR_REG_ADDR;

//static volatile uint8* p_data_regs = IOPORT_DATA_REG_ADDR;

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
//	int port_idx = port_no - 1;
//	volatile uint8 *data_dir_reg = &(p_data_dir_regs[port_idx]);
//	data_dir_reg = data_dir;
	IOPORT1_DATADIR_REG_ADDR = data_dir;
	IOPORT2_DATADIR_REG_ADDR = data_dir;
	IOPORT3_DATADIR_REG_ADDR = data_dir;
	IOPORT4_DATADIR_REG_ADDR = data_dir;
	IOPORT5_DATADIR_REG_ADDR = data_dir;
	IOPORT6_DATADIR_REG_ADDR = data_dir;
	IOPORT8_DATADIR_REG_ADDR = data_dir;
	IOPORT9_DATADIR_REG_ADDR = data_dir;
	IOPORTA_DATADIR_REG_ADDR = data_dir;
	IOPORTB_DATADIR_REG_ADDR = data_dir;

	return 0;
}

/* データ設定 */
int ioport_set_data(int port_no, uint8 data)
{
//	int port_idx = port_no - 1;
//	volatile uint8 *data_reg = &(p_data_regs[port_idx]);
//	data_reg = data;
	IOPORT1_DATA_REG_ADDR = data;
	IOPORT2_DATA_REG_ADDR = data;
	IOPORT3_DATA_REG_ADDR = data;
	IOPORT4_DATA_REG_ADDR = data;
	IOPORT5_DATA_REG_ADDR = data;
	IOPORT6_DATA_REG_ADDR = data;
	IOPORT7_DATA_REG_ADDR = data;
	IOPORT8_DATA_REG_ADDR = data;
	IOPORT9_DATA_REG_ADDR = data;
	IOPORTA_DATA_REG_ADDR = data;
	IOPORTB_DATA_REG_ADDR = data;

	return 0;
}
