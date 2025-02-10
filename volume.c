#include "adc.h"

volatile uint8_t led;
volatile uint8_t previous_led;

int generate_power_law_levels() {

    uint8_t last_level;
    uint16_t volume;

    uint16_t levels[VOLUME_STEPS];
    
    // Generate power-law volume levels
    for (uint8_t i = 0; i < VOLUME_STEPS; i++) {
        levels[i] = (int)(pow((i - 101) / (double)VOLUME_STEPS, 2) * ADC_MAX);
        //levels[i] = ADC_MAX - (int)(pow((i + 1) / (double)VOLUME_STEPS, 2) * ADC_MAX);
    }

    volume = get_volume_level(adc_value, levels, VOLUME_STEPS, &last_level);

    return volume;
}

// Function to map ADC value to volume level with deadzone
int get_volume_level(uint16_t adc_value, const uint16_t levels[], uint8_t num_steps, uint8_t *last_level) {
    // Clamp the ADC value to valid range
    if (adc_value < 0) adc_value = 0;
    if (adc_value > ADC_MAX) adc_value = ADC_MAX;

    // Hysteresis logic: Check if the ADC value is within the deadzone of the current level
    if (*last_level > 0 && adc_value >= levels[*last_level - 1] + DEADZONE && 
        adc_value <= levels[*last_level] - DEADZONE) {
        return *last_level; // Stay at the current level if within the deadzone
    }

    // If not within the deadzone, find the new level
    for (uint8_t i = 0; i < num_steps; i++) {
        if (adc_value >= levels[i] + DEADZONE) {
            // Only update the level if the ADC value is outside the deadzone of the new level
            if (*last_level != i) {
                *last_level = i; // Update the last level
            }
            return i;
        }
    }

    // If the ADC value is greater than all thresholds, set to the maximum level
    *last_level = num_steps - 1;
    return num_steps - 1;
}
