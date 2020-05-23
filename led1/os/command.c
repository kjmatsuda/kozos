#include "defines.h"
#include "kozos.h"
#include "consdrv.h"
#include "lib.h"
#include "ioport.h"

/* コンソール・ドライバの使用開始をコンソール・ドライバに依頼する */
static void send_use(int index)
{
	char *p;
	p = kz_kmalloc(3);
	p[0] = '0';
	p[1] = CONSDRV_CMD_USE;
	p[2] = '0' + index;
	kz_send(MSGBOX_ID_CONSOUTPUT, 3, p);
}

/* コンソールへの文字列出力をコンソール・ドライバに依頼する */
static void send_write(char *str)
{
	char *p;
	int len;
	len = strlen(str);
	p = kz_kmalloc(len + 2);
	p[0] = '0';
	p[1] = CONSDRV_CMD_WRITE;
	memcpy(&p[2], str, len);
	kz_send(MSGBOX_ID_CONSOUTPUT, len + 2, p);
}

int command_main(int argc, char *argv[])
{
	char *p;
	int size;

	send_use(SERIAL_DEFAULT_DEVICE);
	// TODO IOポート初期化は別の場所で実行した方がよい
	// IOポートを初期化
	uint8 syscr_value = ioport_init();
	puts("syscr value: ");
	putxval((unsigned long)syscr_value, 0);
	puts("\n");
	ioport_set_data_direction(1, 0xff);
//	ioport_set_data_direction(2, 0xff);
//	ioport_set_data_direction(3, 0xff);

	while (1) {
		send_write("command> "); /* プロンプト表示 */

		/* コンソールからの受信文字列を受け取る */
		kz_recv(MSGBOX_ID_CONSINPUT, &size, &p);
		p[size] = '\0';

		if (!strncmp(p, "echo", 4)) { /* echoコマンド */
			send_write(p + 4); /* echoに続く文字列を出力する */
			send_write("\n");
		}
		else if (!strncmp(p, "ledhi", 5)) { /* ledhiコマンド */
			ioport_set_data(1, 0xff);
			send_write("ledhi\n");
			send_write("\n");
		}
		else if (!strncmp(p, "ledlo", 5)) { /* ledloコマンド */
			ioport_set_data(1, 0);
			send_write("ledlo\n");
			send_write("\n");
		}
		else {
			send_write("unknown.\n");
		}

		kz_kmfree(p);
	}

	return 0;
}
