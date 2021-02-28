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
	len = kz_strlen(str);
	p = kz_kmalloc(len + 2);
	p[0] = '0';
	p[1] = CONSDRV_CMD_WRITE;
	kz_memcpy(&p[2], str, len);
	kz_send(MSGBOX_ID_CONSOUTPUT, len + 2, p);
}

int command_main(int argc, char *argv[])
{
	char *p;
	int size;

	send_use(SERIAL_DEFAULT_DEVICE);

	while (1) {
		send_write("command> "); /* プロンプト表示 */

		/* コンソールからの受信文字列を受け取る */
		kz_recv(MSGBOX_ID_CONSINPUT, &size, &p);
		p[size] = '\0';

		if (!kz_strncmp(p, "echo", 4)) { /* echoコマンド */
			send_write(p + 4); /* echoに続く文字列を出力する */
			send_write("\n");
		}
		else if (!kz_strncmp(p, "ledhi1_0", 8)) {
			ioport_set_data(1, 0x01);
			send_write("ledhi1_0\n");
			send_write("\n");
		}
		else if (!kz_strncmp(p, "ledhi1_7", 8)) {
			ioport_set_data(1, 0x80);
			send_write("ledhi1_7\n");
			send_write("\n");
		}
		else if (!kz_strncmp(p, "ledhi2_0", 8)) {
			ioport_set_data(2, 0x01);
			send_write("ledhi2_0\n");
			send_write("\n");
		}
		else if (!kz_strncmp(p, "ledhi2_7", 8)) {
			ioport_set_data(2, 0x80);
			send_write("ledhi2_7\n");
			send_write("\n");
		}
		else if (!kz_strncmp(p, "ledlo1", 6)) {
			ioport_set_data(1, 0);
			send_write("ledlo1\n");
			send_write("\n");
		}
		else if (!kz_strncmp(p, "ledlo2", 6)) {
			ioport_set_data(2, 0);
			send_write("ledlo2\n");
			send_write("\n");
		}
		else {
			send_write("unknown.\n");
		}

		kz_kmfree(p);
	}

	return 0;
}
