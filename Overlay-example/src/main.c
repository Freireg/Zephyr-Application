#include <zephyr/kernel.h>
#include <zephyr/drivers/gpio.h>
#include <zephyr/device.h>

/**
 * @brief Start my specs using Zephyr API
 * 
 */
static const struct gpio_dt_spec led = 
	GPIO_DT_SPEC_GET(DT_NODELABEL(myled), gpios);
	//DEVICE_DT_GET(DT_NODELABEL(gpiob));
static const struct gpio_dt_spec button =
	GPIO_DT_SPEC_GET(DT_NODELABEL(mybutton), gpios);

//***************************************

static struct gpio_callback button_cb_data;


/**
 * @brief Button Callback function
 * 
 * @param dev 
 * @param cb 
 * @param pins 
 */
void button_pressed(const struct device *dev, struct gpio_callback *cb, uint32_t pins)
{
	int ret;
	ret = gpio_pin_toggle_dt(&led); //The use of the spec quickens the writing?
	if(ret != 0)
		printk("Could not toggle LED\n");
}


int main(void)
{
	int ret;
	if(!device_is_ready(led.port))
		return;
	if(!device_is_ready(button.port))
		return;
	// ret = gpio_pin_configure(led.port,
	// 												led.pin, led.dt_flags); //This implementation works just as fine
	ret = gpio_pin_configure_dt(&led, GPIO_OUTPUT_ACTIVE);
	if(ret != 0)
		return;
	ret = gpio_pin_configure_dt(&button, GPIO_INPUT);
	if(ret != 0)
		return;

	ret = gpio_pin_interrupt_configure_dt(&button,
																				GPIO_INT_EDGE_TO_ACTIVE);
	if(ret != 0)
		return;
	
	gpio_init_callback(&button_cb_data, button_pressed, BIT(button.pin));
	gpio_add_callback(button.port, &button_cb_data);

	while(1)
	{
		k_msleep(500);
	}

	
}