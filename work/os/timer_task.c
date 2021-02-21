#include "defines.h"
#include "kozos.h"
#include "syscall.h"
#include "ioport.h"

int timer_task_main(int argc, char *argv[])
{
	while (1) {
		if (ioport_data_bit_is_on(1, 1))
		{
			ioport_set_data(1, 0);
		}
		else
		{
			ioport_set_data(1, 0x01);
		}

		kz_wait();
	}

	return 0;
}
