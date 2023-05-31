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
#include <zephyr/device.h>
#include <zephyr/drivers/display.h>
#include <lvgl.h>
#include <stdio.h>
#include <string.h>
#include <zephyr/drivers/sensor.h>

const struct device *const mpu6050 = DEVICE_DT_GET_ONE(invensense_mpu6050);
const struct device *display_dev = DEVICE_DT_GET(DT_CHOSEN(zephyr_display));
struct sensor_value sensorOut[7];

static int process_mpu6050(const struct device *dev)
{
	struct sensor_value temperature;
	struct sensor_value accel[3];
	struct sensor_value gyro[3];
	int rc = sensor_sample_fetch(dev);

	if (rc == 0) {
		rc = sensor_channel_get(dev, SENSOR_CHAN_ACCEL_XYZ,
					accel);
	}
	if (rc == 0) {
		rc = sensor_channel_get(dev, SENSOR_CHAN_GYRO_XYZ,
					gyro);
	}
	if (rc == 0) {
		rc = sensor_channel_get(dev, SENSOR_CHAN_AMBIENT_TEMP,
					&temperature);
	}
	if (rc == 0) {
		printf("  accel %f %f %f m/s/s\n"
		       "  gyro  %f %f %f rad/s\n",
		       sensor_value_to_double(&temperature),
		       sensor_value_to_double(&accel[0]),
		       sensor_value_to_double(&accel[1]),
		       sensor_value_to_double(&accel[2]),
		       sensor_value_to_double(&gyro[0]),
		       sensor_value_to_double(&gyro[1]),
		       sensor_value_to_double(&gyro[2]));
	} else {
		printf("sample fetch/get failed: %d\n", rc);
	}
	sensorOut[0] = temperature;
	sensorOut[1] = accel[0];
	sensorOut[2] = accel[1];
	sensorOut[3] = accel[2]; 
	sensorOut[4] = gyro[0]; 
	sensorOut[5] = gyro[1]; 
	sensorOut[6] = gyro[2]; 
	
	return rc;
}

int main(void)
{
	static lv_style_t style;
	lv_obj_t *hello_world_label;
	lv_obj_t *readings_label;
	char count_str[50] = {0};

	if (!device_is_ready(mpu6050)) {
		printf("Device %s is not ready\n", mpu6050->name);
		return 0;
	}
	if (!device_is_ready(display_dev)) {
		printf("Device %s is not ready\n", display_dev->name);
		return;
	}

	if (IS_ENABLED(CONFIG_LV_Z_POINTER_KSCAN)) {
		lv_obj_t *hello_world_button;

		hello_world_button = lv_btn_create(lv_scr_act());
		lv_obj_align(hello_world_button, LV_ALIGN_CENTER, 0, 0);
		hello_world_label = lv_label_create(hello_world_button);
	} 
	else {
		hello_world_label = lv_label_create(lv_scr_act());
	}

	lv_style_init(&style);
	lv_style_set_text_decor(&style, LV_TEXT_DECOR_NONE);

	lv_label_set_text(hello_world_label, "Accel Readings");
	lv_obj_align(hello_world_label, LV_ALIGN_BOTTOM_MID, 0, 0);

	readings_label = lv_label_create(lv_scr_act());
	lv_obj_add_style(readings_label, &style, 0);
	lv_obj_align(readings_label, LV_ALIGN_TOP_MID, 0, 0);

	lv_task_handler();
	display_blanking_off(display_dev);

	while (1) {
		int rc = process_mpu6050(mpu6050);

		if (rc != 0) {
			break;
		}
		sprintf(count_str, "Temp: %f \nAX: %f\nAY: %f\nAZ: %f", 
												sensor_value_to_double(&sensorOut[0]),
												sensor_value_to_double(&sensorOut[1]),
												sensor_value_to_double(&sensorOut[2]),
												sensor_value_to_double(&sensorOut[3]));
		lv_label_set_text(readings_label, count_str);
		lv_task_handler();

		k_sleep(K_SECONDS(1));
	}

	/* triggered runs with its own thread after exit */
	return 0;
}