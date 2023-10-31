#include <zephyr/kernel.h>
#include "edge-impulse-sdk/classifier/ei_run_classifier.h"
#include "edge-impulse-sdk/dsp/numpy.hpp"


static const float features[] = { 
-1.3500, 2.7300, 9.7400, -1.4200, 3.2600, 9.8800, -1.1400, 2.8400, 9.6900, -1.1400, 2.8400, 9.6900, -2.3500, 2.3800, 9.3400, -1.3800, 0.4500, 10.2600, -1.4000, -0.5100, 9.3100, -1.1400, -1.4200, 10.0700, -0.7500, -1.6800, 9.8900, -0.4000, -1.9500, 9.0800, -0.4000, -1.9500, 9.0800, -0.9200, -1.7100, 8.0400, -0.9400, -1.8300, 9.7700, -0.6800, -1.7600, 10.0700, -0.7200, -1.3500, 9.5600, -0.3800, -0.3900, 9.8200, 1.2900, -0.6900, 9.5600, 1.2900, -0.6900, 9.5600, 0.4100, -2.6200, 10.0400, -0.6100, -3.6600, 10.0600, -0.1600, -3.7200, 9.9400, -0.2900, -3.3900, 9.3000, -0.2800, -2.3200, 9.3000, -0.0500, -1.6900, 9.1200, -0.0500, -1.6900, 9.1200, 0.5800, -1.2900, 9.3700, 1.1500, -1.2900, 10.1400, 1.0700, -0.8600, 9.9200, 1.5700, -0.4400, 9.6900, 1.7000, 0.3200, 10.2900, 2.3700, 1.0000, 9.7900, 2.3700, 1.0000, 9.7900, 2.3600, 0.8100, 10.0500, 2.3700, 0.6200, 9.6500, 2.9700, 0.7600, 9.6100, 2.0300, 1.0200, 9.6000, 2.0600, 1.4400, 9.3400, 2.0600, 1.4400, 9.6400, 1.9700, 2.0500, 9.6400, 1.2700, 2.7000, 9.0300, 1.4800, 3.4400, 8.9800, 1.0300, 3.7100, 10.1700, 0.8000, 3.2200, 10.0300, -0.2500, 1.7100, 9.8400, -0.2500, 1.7100, 9.8400, -0.1000, 1.4600, 10.0200, 0.8400, 2.4200, 9.8500, 0.4300, 2.8600, 10.0500, 0.1000, 2.4900, 9.9300, -0.5800, 2.0700, 10.1100, -0.8800, 1.8000, 9.9500, -0.8800, 1.8000, 9.9500, -1.1700, 1.4500, 10.0400, -1.9000, 0.7400, 9.9200, -2.8600, -0.2900, 9.0900, -1.7500, -0.7300, 8.8300, -0.7900, -1.2200, 9.7000, -0.6900, -1.0200, 9.9800, -0.6900, -1.0200, 9.9800, -0.9000, -1.8800, 9.9200, -1.0400, -1.5200, 10.1800, -0.4700, -1.8400, 9.9300, -0.4000, -1.8100, 9.7900, -0.7700, -2.2900, 9.4900, -0.5300, -1.9000, 9.8800, -0.5300, -1.9000, 9.8800, 0.0700, -0.6400, 9.5000, 0.7300, -0.0500, 9.6400, 0.5400, -1.2000, 10.1200, 0.2600, -2.6900, 9.8700, 0.5400, -1.3100, 9.8900, 0.7800, -0.7700, 10.2300, 0.7800, -0.7700, 10.2300, 0.1300, -1.6800, 10.1400, -0.3500, -2.0400, 9.5300, -0.2000, -3.0700, 9.7000, 0.2900, -3.4300, 9.3600, 1.1000, -2.1400, 9.8900, 1.4700, -0.3300, 10.3100, 1.4700, -0.3300, 10.3100, 1.8600, 0.9700, 9.9900, 2.0600, 1.3100, 9.9200, 1.5300, 1.2900, 9.2800, 2.0300, 0.7800, 9.5500, 2.0600, 0.2300, 8.7900, 2.2800, 0.6200, 9.3000, 2.2800, 0.6200, 9.3000, 1.9600, 1.4600, 10.1100, 2.4300, 2.6700, 8.7900, 2.7400, 2.8000, 9.1800, 2.4500, 2.5800, 10.2100, 1.7200, 1.8500, 9.8900, 1.1700, 2.3000, 9.7200, 1.1700, 2.3000, 9.7200, 1.5600, 2.6800, 9.7200, 2.1600, 3.5000, 9.5200, 0.6300, 3.8500, 9.7200, -0.5800, 3.5200, 9.1700, -0.6800, 2.7800, 9.7000, -0.6800, 2.7800, 9.7000, -1.0400, 1.9600, 9.9800, -1.6200, 1.7900, 10.0300, -0.6400, 1.8400, 9.5700, -0.2200, 2.2300, 7.9800, -1.6200, 2.9100, 10.0400, -1.5500, 1.5900, 10.0300, -1.5500, 1.5900, 10.0300, -1.8600, 0.4700, 9.7500, -1.8600, -0.2300, 9.5200, -0.9600, -0.2200, 9.8100, -0.7200, -0.3000, 9.4200, -0.7400, -0.9400, 10.1000, -0.9200, -1.5400, 9.3900, -0.9200, -1.5400, 9.3900, -1.7200, -2.2000, 9.8900, -1.2300, -3.1000, 9.7600, -1.5400, -3.7500, 9.7400, -1.3300, -3.0000, 9.5200, -0.2500, -1.9000, 10.0400, 0.7800, -0.4800, 9.2300, 0.7800, -0.4800, 9.2300, 0.7700, 0.2000, 10.0800, 0.7400, -0.8800, 10.1600, -0.4900, -2.3100, 9.4800, -1.0200, -2.3600, 9.9600
};

int raw_feature_get_data(size_t offset, size_t length, float *out_ptr) {
    memcpy(out_ptr, features + offset, length * sizeof(float));
    return 0;
}

int main() {
    // This is needed so that output of printf is output immediately without buffering
    setvbuf(stdout, NULL, _IONBF, 0);

#ifdef CONFIG_SOC_NRF5340_CPUAPP
    // Switch CPU core clock to 128 MHz
    nrfx_clock_divider_set(NRF_CLOCK_DOMAIN_HFCLK, NRF_CLOCK_HFCLK_DIV_1);
#endif

    printk("Edge Impulse standalone inferencing (Zephyr)\n");

    if (sizeof(features) / sizeof(float) != EI_CLASSIFIER_DSP_INPUT_FRAME_SIZE) {
        printk("The size of your 'features' array is not correct. Expected %d items, but had %u\n",
            EI_CLASSIFIER_DSP_INPUT_FRAME_SIZE, sizeof(features) / sizeof(float));
        return 1;
    }

    ei_impulse_result_t result = { 0 };

    while (1) {
        // the features are stored into flash, and we don't want to load everything into RAM
        signal_t features_signal;
        features_signal.total_length = sizeof(features) / sizeof(features[0]);
        features_signal.get_data = &raw_feature_get_data;

        // invoke the impulse
        EI_IMPULSE_ERROR res = run_classifier(&features_signal, &result, true);
        printk("run_classifier returned: %d\n", res);

        if (res != 0) return 1;

        printk("Predictions (DSP: %d ms., Classification: %d ms., Anomaly: %d ms.): \n",
                result.timing.dsp, result.timing.classification, result.timing.anomaly);
#if EI_CLASSIFIER_OBJECT_DETECTION == 1
        bool bb_found = result.bounding_boxes[0].value > 0;
        for (size_t ix = 0; ix < result.bounding_boxes_count; ix++) {
            auto bb = result.bounding_boxes[ix];
            if (bb.value == 0) {
                continue;
            }
            printk("    %s (%f) [ x: %u, y: %u, width: %u, height: %u ]\n", bb.label, bb.value, bb.x, bb.y, bb.width, bb.height);
        }
        if (!bb_found) {
            printk("    No objects found\n");
        }
#else
        for (size_t ix = 0; ix < EI_CLASSIFIER_LABEL_COUNT; ix++) {
            printk("    %s: %.5f\n", result.classification[ix].label,
                                    result.classification[ix].value);
        }
#if EI_CLASSIFIER_HAS_ANOMALY == 1
        printk("    anomaly score: %.3f\n", result.anomaly);
#endif
#endif
        k_msleep(2000);
    }
}
