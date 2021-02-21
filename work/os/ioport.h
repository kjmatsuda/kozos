#ifndef _IOPORT_H_INCLUDED_
#define _IOPORT_H_INCLUDED_

int ioport_init();						/* デバイス初期化 */
int ioport_set_data_direction(int port_no, uint8 data_dir);			/* データディレクション設定 */
int ioport_set_data(int port_no, uint8 data);	/* データ設定 */
int ioport_get_data(int port_no, uint8 *p_data);	/* データ取得 */
int ioport_data_bit_is_on(int port_no, int bit);	/* データビットON判定取得 */

#endif
