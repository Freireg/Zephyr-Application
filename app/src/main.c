/**
 * @file main.c
 * @author Guilherme Freire (freireg1503@gmail.com)
 * @brief 
 * @version 0.1
 * @date 2022-08-22
 * 
 * @copyright Copyright (c) 2022
 * 
 */

#include <zephyr/zephyr.h>
#include <zephyr/drivers/gpio.h>

#define MY_STACK_SIZE 500
#define MY_PRIORITY 5
#define SLEEP_TIME_MS   1000

#define LED0_NODE DT_ALIAS(led0)

void my_entry_point(void *p, void *a, void *c);

K_THREAD_STACK_DEFINE(my_stack_area, MY_STACK_SIZE);

// struct k_thread my_thread_data;
static const struct gpio_dt_spec led0 = GPIO_DT_SPEC_GET(LED0_NODE, gpios);
//k_thread_create returnr the ID of the new thread

void my_entry_point(void *p, void *a, void *c)
{
	int ret;
	device_is_ready(led0.port);
	ret = gpio_pin_configure_dt(&led0, GPIO_OUTPUT_ACTIVE);
	if (ret < 0) 
	{
		return;
	}

	while(1)
	{
		gpio_pin_toggle_dt(&led0);
		k_msleep(SLEEP_TIME_MS);
	}
}

// k_tid_t my_tid = k_thread_create(&my_thread_data,													//Pointer to uninitialized struct k_thread
// 																my_stack_area,													//Pointer to the stack space
// 																K_THREAD_STACK_SIZEOF(my_stack_area),		//Stack size in bytes
// 																my_entry_point,													//Thread entry function
// 																NULL,																		//1st entry point parameter
// 																NULL,																		//2nd entry point parameter
// 																NULL,																		//3rd entry point parameter
// 																MY_PRIORITY,														//Thread priority
// 																0,																			//Thread options
// 																K_NO_WAIT);		

K_THREAD_DEFINE(my_entry_point_id, 
								MY_STACK_SIZE, 
								my_entry_point, 
								NULL, NULL, NULL, 
								MY_PRIORITY, 
								0, 
								0);