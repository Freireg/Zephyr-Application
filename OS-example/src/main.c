#include <zephyr/kernel.h>
#include <zephyr/drivers/gpio.h>
#include <inttypes.h>

/* Specs and Peripherals */
#define LED0_NODE DT_ALIAS(led0)
#define SW0_NODE DT_ALIAS(sw0)

/* Kernel Stack definitions */
#define STACK_SIZE 	1024 
#define PRIORITY		0


static const struct gpio_dt_spec led = 
	GPIO_DT_SPEC_GET(LED0_NODE, gpios);
	//DEVICE_DT_GET(DT_NODELABEL(gpiob));
static const struct gpio_dt_spec button =
	GPIO_DT_SPEC_GET(SW0_NODE, gpios);

void ReportStatus(void *p1, void *p2, void *p3)
{
	/* Initialization of the Task */
	printk("Initializing Report Thread\n");
	while(1)
	{
		k_msleep(500);
	}
}

void BlinkTask(void *p1, void *p2, void *p3)
{
	/* Initialization of the Task */
	printk("Initializing Blink Thread\n");
	int ret;
	if(!gpio_is_ready_dt(&led))
		printk("Could not start led port\n");

	ret = gpio_pin_configure_dt(&led, GPIO_OUTPUT_ACTIVE);
	if(ret != 0)
		return;
	while(1)
	{
		ret = gpio_pin_toggle_dt(&led); //The use of the spec quickens the writing?
		if(ret != 0)
			printk("Could not toggle LED\n");
		k_msleep(500);
	}
}

void MemoryTask(void *p1, void *p2, void *p3)
{
	/* Initialization of the Task */
	printk("Initializing Memory Thread\n");
	while(1)
	{
		
		k_msleep(500);
	}
}

K_THREAD_DEFINE(
	BlinkTaskHandler, STACK_SIZE,
	BlinkTask, NULL, NULL, NULL,
	PRIORITY, 0, 0
);
K_THREAD_DEFINE(
	ReportHandler, STACK_SIZE,
	ReportStatus, NULL, NULL, NULL,
	PRIORITY, 0, 0
);
K_THREAD_DEFINE(
	MemoryHandler, STACK_SIZE,
	MemoryTask, NULL, NULL, NULL,
	PRIORITY, 0, 0
);

// void main(void)
// {
	
// 	k_tid_t ReportTaskHandler = k_thread_create(
// 		&ReportTask_Data, ReportStackArea,
// 		K_THREAD_STACK_SIZEOF(ReportStackArea),
// 		ReportStatus, NULL, NULL, NULL,
// 		PRIORITY, 0, K_NO_WAIT);

// 	k_tid_t BlinkTaskHandler = k_thread_create(
// 		&BlinkTask_Data, BlinkStackArea,
// 		K_THREAD_STACK_SIZEOF(BlinkStackArea),
// 		BlinkTask, NULL, NULL, NULL,
// 		PRIORITY, 0, K_NO_WAIT);

// 	k_tid_t MemoryTaskHandler = k_thread_create(
// 		&MemoryTask_Data, MemoryStackArea,
// 		K_THREAD_STACK_SIZEOF(MemoryStackArea),
// 		MemoryTask, NULL, NULL, NULL,
// 		PRIORITY, 0, K_NO_WAIT);
		
// 	while (1)
// 	{
		
// 	}
// }