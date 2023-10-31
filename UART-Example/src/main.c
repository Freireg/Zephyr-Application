#include <zephyr/kernel.h>
#include <zephyr/device.h>
#include <zephyr/drivers/uart.h>


#include <stdio.h>
#include <string.h>

// const struct device *uart3 = DEVICE_DT_GET(DT_NODELABEL(uart3));

struct uart_config uart_cfg =
{
  .baudrate = 9600,
	.parity = UART_CFG_PARITY_NONE,
	.stop_bits = UART_CFG_STOP_BITS_1,
	.flow_ctrl = UART_CFG_FLOW_CTRL_NONE,
	.data_bits = UART_CFG_DATA_BITS_8,
};

#define UART_DEV_NAME "UART_1"  // Change to the name of your UART device
#define GPS_BUF_SIZE 256*2       // Adjust the buffer size as needed

static uint8_t gps_buffer[GPS_BUF_SIZE];
static const struct device *const uart_dev = DEVICE_DT_GET(DT_NODELABEL(uart3));

void uart_callback(struct device *dev, void *user_data)
{
    ARG_UNUSED(user_data);

    while (uart_fifo_read(uart_dev, gps_buffer, sizeof(gps_buffer))) {
        // Process the received GPS data here
        // You may want to implement a NMEA sentence parser to extract location information
        // For this example, we'll just print the received data
        for (int i = 0; i < sizeof(gps_buffer); i++) {
            if (gps_buffer[i] == '\0') {
                break;
            }
            printk("%c", gps_buffer[i]);
        }
    }
}

void main(void)
{
	if (!device_is_ready(uart_dev)) {
		printk("UART device not found!");
		return 0;
	}

    int ret = uart_configure(uart_dev, &uart_cfg);
	if (ret < 0) {
		if (ret == -ENOTSUP) {
			printk("Interrupt-driven UART API support not enabled\n");
		} else if (ret == -ENOSYS) {
			printk("UART device does not support interrupt-driven API\n");
		} else {
			printk("Error setting UART callback: %d\n", ret);
		}
		return 0;
	}

    uart_irq_callback_user_data_set(uart_dev, uart_callback, NULL);
    uart_irq_rx_enable(uart_dev);

    while (1) {
        // Your main application logic can go here
        // Use k_sleep() or other mechanisms for task scheduling as needed
    }
}
