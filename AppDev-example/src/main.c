#include <zephyr/kernel.h>
#include "utils.h"


void main(void)
{
	while(1)
	{
		mylib_hello_world();
		k_msleep(1000);
	}	
}