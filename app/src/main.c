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

#include <zephyr/kernel.h>
#include <zephyr/drivers/gpio.h>
// #include <zephyr/drivers/mipi_dsi.h>

#define MY_STACK_SIZE 500
#define MY_PRIORITY 5
#define SLEEP_TIME_MS   1000

#define LED0_NODE DT_ALIAS(led0)
#define LED1_NODE DT_ALIAS(led1)


void firstThreadFunction(void *p, void *a, void *c);
// void secondThreadFunction(void);

K_THREAD_STACK_DEFINE(my_stack_area, MY_STACK_SIZE);

static const struct gpio_dt_spec led0 = GPIO_DT_SPEC_GET(LED0_NODE, gpios);
// static const struct gpio_dt_spec led1 = GPIO_DT_SPEC_GET(LED1_NODE, gpios);



K_THREAD_DEFINE(firstThread_id, 
								MY_STACK_SIZE, 
								firstThreadFunction, 
								NULL, NULL, NULL, 
								MY_PRIORITY, 
								0, 
								0);

// K_THREAD_DEFINE(secondThread_id, 
// 								MY_STACK_SIZE, 
// 								secondThreadFunction, 
// 								NULL, NULL, NULL, 
// 								MY_PRIORITY, 
// 								0, 
// 								0);


void firstThreadFunction(void *p, void *a, void *c)
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

// void secondThreadFunction(void)
// {
// 		int ret;
// 	device_is_ready(led1.port);
// 	ret = gpio_pin_configure_dt(&led1, GPIO_OUTPUT_INACTIVE);
// 	if (ret < 0) 
// 	{
// 		return;
// 	}

// 	while(1)
// 	{
// 		gpio_pin_toggle_dt(&led1);
// 		k_msleep(SLEEP_TIME_MS);
// 	}
// }