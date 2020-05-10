#ifndef _IOPORT_H_INCLUDED_
#define _IOPORT_H_INCLUDED_

int ioport_init();						/* デバイス初期化 */
int ioport_set_data_direction(int port_no, uint8 data_dir);			/* データディレクション設定 */
int ioport_set_data(int port_no, uint8 data);	/* データ設定 */

#endif
