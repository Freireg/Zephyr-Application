#include <zephyr/kernel.h>
#include <zephyr/drivers/gpio.h>
#include <inttypes.h>

#define LED0_NODE DT_ALIAS(led0)
#define SW0_NODE DT_ALIAS(sw0)

static const struct gpio_dt_spec led = GPIO_DT_SPEC_GET(LED0_NODE, gpios);
static const struct gpio_dt_spec button = GPIO_DT_SPEC_GET(SW0_NODE, gpios);
static struct gpio_callback button_cb_data;


void button_pressed(const struct device *dev, struct gpio_callback *cb, uint32_t pins)
{
  printk("Button pressed at %" PRIu32 "\n", (k_cycle_get_32()/1000));
    /* If we have an LED, match its state to the button's. */
  int val = gpio_pin_get_dt(&button);

  if (val >= 0) {
    gpio_pin_toggle_dt(&led);
  }
}

void init_routine(void)
{
  int ret;

	if (!gpio_is_ready_dt(&button)) {
		printk("Error: button device %s is not ready\n",
		       button.port->name);
		return;
	}

	ret = gpio_pin_configure_dt(&button, GPIO_INPUT);
	if (ret != 0) {
		printk("Error %d: failed to configure %s pin %d\n",
		       ret, button.port->name, button.pin);
		return;
	}

	ret = gpio_pin_interrupt_configure_dt(&button,
					      GPIO_INT_EDGE_TO_ACTIVE);
	if (ret != 0) {
		printk("Error %d: failed to configure interrupt on %s pin %d\n",
			ret, button.port->name, button.pin);
		return;
	}

	gpio_init_callback(&button_cb_data, button_pressed, BIT(button.pin));
	gpio_add_callback(button.port, &button_cb_data);
	printk("Set up button at %s pin %d\n", button.port->name, button.pin);

	if (led.port && !device_is_ready(led.port)) {
		printk("Error %d: LED device %s is not ready; ignoring it\n",
		       ret, led.port->name);
	}
	if (led.port) {
		ret = gpio_pin_configure_dt(&led, GPIO_OUTPUT);
		if (ret != 0) {
			printk("Error %d: failed to configure LED device %s pin %d\n",
			       ret, led.port->name, led.pin);
		} else {
			printk("Set up LED at %s pin %d\n", led.port->name, led.pin);
		}
	}
}
void main(void)
{
  init_routine();
	printk("Press the button\n");
	if (led.port) {
		while (1) {
			k_msleep(1000);
		}
  }
}