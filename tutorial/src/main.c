#include <zephyr/kernel.h>
#include <zephyr/drivers/gpio.h>
#include <zephyr/device.h>

static const struct gpio_dt_spec led = 
	GPIO_DT_SPEC_GET(DT_NODELABEL(myled), gpios);
	//DEVICE_DT_GET(DT_NODELABEL(gpiob));


int main(void)
{
	int ret;
	if (!device_is_ready(led.port))
		return;
	// ret = gpio_pin_configure(led.port,
	// 												led.pin, led.dt_flags); //This implementation works just as fine
	ret = gpio_pin_configure_dt(&led, GPIO_OUTPUT_ACTIVE);
	if(ret != 0)
		return;

	while(1)
	{
		ret = gpio_pin_toggle_dt(&led); //The use of the spec quickens the writing?
		k_msleep(500);
	}

	
}