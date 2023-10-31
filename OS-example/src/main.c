#include <zephyr/kernel.h>
#include <zephyr/drivers/gpio.h>
#include <inttypes.h>


/* Specs and Peripherals */
#define LED0_NODE DT_ALIAS(led0)	//Green
#define LED1_NODE DT_ALIAS(led1)	//Blue
#define LED2_NODE DT_ALIAS(led2)	//Red
#define SW0_NODE DT_ALIAS(sw0)

/* Kernel Stack definitions */
#define STACK_SIZE 	1024 
#define PRIORITY		0


static const struct gpio_dt_spec green_led = 
	GPIO_DT_SPEC_GET(LED0_NODE, gpios);
	//DEVICE_DT_GET(DT_NODELABEL(gpiob));
static const struct gpio_dt_spec blue_led = 
	GPIO_DT_SPEC_GET(LED1_NODE, gpios);
static const struct gpio_dt_spec red_led = 
	GPIO_DT_SPEC_GET(LED2_NODE, gpios);
static const struct gpio_dt_spec button =
	GPIO_DT_SPEC_GET(SW0_NODE, gpios);

void ReportStatus(void *p1, void *p2, void *p3)
{
	/* Initialization of the Task */
	printk("Initializing Report Thread\n");
	int ret;
	if(!gpio_is_ready_dt(&blue_led))
		printk("Could not start blue_led port\n");

	ret = gpio_pin_configure_dt(&blue_led, GPIO_OUTPUT_ACTIVE);
	if(ret != 0)
		return;
	while(1)
	{
		ret = gpio_pin_toggle_dt(&blue_led); //The use of the spec quickens the writing?
		if(ret != 0)
			printk("Could not toggle LED\n");

		printk("Current process: %d\n", (int *)k_current_get());
		k_msleep(1500);
	}
}

void BlinkTask(void *p1, void *p2, void *p3)
{
	/* Initialization of the Task */
	printk("Initializing Blink Thread\n");
	int ret;
	if(!gpio_is_ready_dt(&green_led))
		printk("Could not start green_led port\n");

	ret = gpio_pin_configure_dt(&green_led, GPIO_OUTPUT_ACTIVE);
	if(ret != 0)
		return;
	while(1)
	{
		ret = gpio_pin_toggle_dt(&green_led); //The use of the spec quickens the writing?
		if(ret != 0)
			printk("Could not toggle LED\n");
		k_msleep(1000);
	}
}

void MemoryTask(void *p1, void *p2, void *p3)
{
	/* Initialization of the Task */
	printk("Initializing Memory Thread\n");
	int ret;
	if(!gpio_is_ready_dt(&red_led))
		printk("Could not start red_led port\n");

	ret = gpio_pin_configure_dt(&red_led, GPIO_OUTPUT_ACTIVE);
	if(ret != 0)
		return;
	while(1)
	{
		ret = gpio_pin_toggle_dt(&red_led); //The use of the spec quickens the writing?
		if(ret != 0)
			printk("Could not toggle LED\n");
		k_msleep(500);
	}
}

// K_THREAD_DEFINE(
// 	BlinkTaskHandler, STACK_SIZE,
// 	BlinkTask, NULL, NULL, NULL,
// 	PRIORITY, 0, 0
// );
// K_THREAD_DEFINE(
// 	ReportHandler, STACK_SIZE,
// 	ReportStatus, NULL, NULL, NULL,
// 	PRIORITY, 0, 0
// );
// K_THREAD_DEFINE(
// 	MemoryHandler, STACK_SIZE,
// 	MemoryTask, NULL, NULL, NULL,
// 	PRIORITY, 0, 0
// );

static struct k_thread ReportTask_Data;
static struct k_thread BlinkTask_Data;
static struct k_thread MemoryTask_Data;

K_THREAD_STACK_DEFINE(ReportStackArea, STACK_SIZE);
K_THREAD_STACK_DEFINE(BlinkStackArea, STACK_SIZE);
K_THREAD_STACK_DEFINE(MemoryStackArea, STACK_SIZE);

void main(void)
{
	
	k_thread_create(
		&ReportTask_Data, ReportStackArea,
		STACK_SIZE,
		ReportStatus, NULL, NULL, NULL,
		PRIORITY, 0, K_NO_WAIT);

	k_thread_create(
		&BlinkTask_Data, BlinkStackArea,
		STACK_SIZE,
		BlinkTask, NULL, NULL, NULL,
		PRIORITY, 0, K_NO_WAIT);

	k_thread_create(
		&MemoryTask_Data, MemoryStackArea,
		STACK_SIZE,
		MemoryTask, NULL, NULL, NULL,
		PRIORITY, 0, K_NO_WAIT);
		
}
