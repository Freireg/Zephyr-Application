#include <zephyr/kernel.h>
#include <zephyr/drivers/gpio.h>
#include <zephyr/shell/shell.h>
#include <inttypes.h>


/* Specs and Peripherals */
#define LED0_NODE DT_ALIAS(led0)	//Green
#define LED1_NODE DT_ALIAS(led1)	//Blue
#define LED2_NODE DT_ALIAS(led2)	//Red



static const struct gpio_dt_spec green_led = 
	GPIO_DT_SPEC_GET(LED0_NODE, gpios);
	//DEVICE_DT_GET(DT_NODELABEL(gpiob));
static const struct gpio_dt_spec blue_led = 
	GPIO_DT_SPEC_GET(LED1_NODE, gpios);
static const struct gpio_dt_spec red_led = 
	GPIO_DT_SPEC_GET(LED2_NODE, gpios);

//Generic Toggle LED function
static int cmd_toggle_LED(const struct shell *sh, size_t argc, char **argv, void *data)
{
	int val = (intptr_t)data;

	switch (val)
	{
	case 0:
			gpio_pin_toggle_dt(&blue_led);
		break;
	case 1:
			gpio_pin_toggle_dt(&green_led);
		break;
	case 2:
			gpio_pin_toggle_dt(&red_led);
		break;
	default:
			shell_print(sh, "Wrong arg");
		break;
	}

	return 0;
}
//Generic print function
static int cmd_print(const struct shell *sh, size_t argc, char **argv)
{

		shell_print(sh, "Command received");
		return 0;

}

static int cmd_stdalone(const struct shell *sh, size_t argc, char **argv)
{
	shell_print(sh, "Standalone Command");
	return 0;
}

//Creating a subcommand dictionary
SHELL_SUBCMD_DICT_SET_CREATE(sub_toggle_cmds, cmd_toggle_LED,
	(value_0, 0, "value 0"), (value_1, 1, "value 1"),
	(value_2, 2, "value 2"), (value_3, 3, "value 3")
);
//Creating a subcmd set 
SHELL_STATIC_SUBCMD_SET_CREATE(sub_demo,
	SHELL_CMD(prt, NULL, "Print", &cmd_print),
	SHELL_CMD(tog, &sub_toggle_cmds, "Toggle LED", NULL)
);

//Create a command with its subcmds
SHELL_CMD_REGISTER(demo, &sub_demo, "Demo commands", NULL);
//Create a standalone cmd that don't have any subcmds
SHELL_CMD_REGISTER(stdal, NULL, "Stand Alone Command", &cmd_stdalone);

void main(void)
{
	int ret;
	if(!gpio_is_ready_dt(&blue_led))
		printk("Could not start blue_led port\n");

	ret = gpio_pin_configure_dt(&blue_led, GPIO_OUTPUT_INACTIVE);
	if(ret != 0)
		return;
	
	if(!gpio_is_ready_dt(&green_led))
		printk("Could not start green_led port\n");

	ret = gpio_pin_configure_dt(&green_led, GPIO_OUTPUT_INACTIVE);
	if(ret != 0)
		return;

	if(!gpio_is_ready_dt(&red_led))
		printk("Could not start red_led port\n");

	ret = gpio_pin_configure_dt(&red_led, GPIO_OUTPUT_INACTIVE);
	if(ret != 0)
		return;

		
}
