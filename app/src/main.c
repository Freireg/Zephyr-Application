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
#include <zephyr/device.h>

static const struct device *gpio_ct_dev = 
	DEVICE_DT_GET(DT_NODELABEL(gpiob));


int main(void)
{
	int ret;
	if (!device_is_ready(gpio_ct_dev))
		return;
	ret = gpio_pin_configure(gpio_ct_dev,
													22, GPIO_OUTPUT_ACTIVE);
	if(ret != 0)
		return;


	while(1)
	{
		ret = gpio_pin_toggle(gpio_ct_dev, 22);
		k_msleep(1000);
	}

	
}