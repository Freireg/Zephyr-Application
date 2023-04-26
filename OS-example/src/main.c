#include <zephyr/kernel.h>
#include <zephyr/drivers/gpio.h>
#include <inttypes.h>

/* Specs and Peripherals */
#define LED0_NODE DT_ALIAS(led0)
#define SW0_NODE DT_ALIAS(sw0)

/* Kernel Stack definitions */
#define STACK_SIZE 	1024 
#define PRIORITY		0

K_THREAD_STACK_DEFINE(ReportStackArea, STACK_SIZE);
K_THREAD_STACK_DEFINE(BlinkStackArea, STACK_SIZE);
K_THREAD_STACK_DEFINE(MemoryStackArea, STACK_SIZE);

struct k_thread ReportTask_Data;
struct k_thread BlinkTask_Data;
struct k_thread MemoryTask_Data;


void ReportStatus(void *p1, void *p2, void *p3)
{
	/* Initialization of the Task */
	
	while(1)
	{
	
	}
}

void BlinkTask(void *p1, void *p2, void *p3)
{
	/* Initialization of the Task */
	
	while(1)
	{
	
	}
}

void MemoryTask(void *p1, void *p2, void *p3)
{
	/* Initialization of the Task */
	
	while(1)
	{
	
	}
}

void main(void)
{
	k_tid_t ReportTaskHandler = k_thread_create(
		&ReportTask_Data, ReportStackArea,
		K_THREAD_STACK_SIZEOF(ReportStackArea),
		ReportStatus, NULL, NULL, NULL,
		PRIORITY, 0, K_NO_WAIT);

	k_tid_t BlinkTaskHandler = k_thread_create(
		&BlinkTask_Data, BlinkStackArea,
		K_THREAD_STACK_SIZEOF(BlinkStackArea),
		BlinkTask, NULL, NULL, NULL,
		PRIORITY, 0, K_NO_WAIT);

	k_tid_t MemoryTaskHandler = k_thread_create(
		&MemoryTask_Data, MemoryStackArea,
		K_THREAD_STACK_SIZEOF(MemoryStackArea),
		MemoryTask, NULL, NULL, NULL,
		PRIORITY, 0, K_NO_WAIT);
		
	while (1)
	{
		
	}
}