#include "defines.h"
#include "syscall.h"
#include "ioport.h"

static int led_sts = 1;

int timer_task_main(int argc, char *argv[])
{
	while (1) {
		if (0 == led_sts)
		{
			ioport_set_data(1, 0x01);
			led_sts = 1;
		}
		else
		{
			ioport_set_data(1, 0);
			led_sts = 0;
		}
		kz_wait();
	}

	return 0;
}
