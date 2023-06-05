/**
 * @file AccelThread.c
 * @author Guilherme Freire (guilherme.freire@fieb.org.br)
 * @brief 
 * @version 0.1
 * @date 2023-06-01
 * 
 * @copyright Copyright (c) 2023
 * 
 */
#include "AccelThread.h"

#define LED0_NODE DT_ALIAS(led0)

static const struct gpio_dt_spec led = GPIO_DT_SPEC_GET(LED0_NODE, gpios);

void AccelThread(void *p1, void *p2, void *p3)
{
  /* Initialization of the Thread */
	// printk("Starting Accel Thread\n");
	int ret;
	if(!gpio_is_ready_dt(&led))
		printf("Could not start led port\n");

	ret = gpio_pin_configure_dt(&led, GPIO_OUTPUT_ACTIVE);
	if(ret != 0)
		printf("Could not configure led port\n");
	// 	return;
	while(1)
	{
		ret = gpio_pin_toggle_dt(&led); //The use of the spec quickens the writing?
		if(ret != 0)
			printf("Could not toggle led port\n");

		printf("Current process: %d\n", (int *)k_current_get());
		k_msleep(250);
	}
}

