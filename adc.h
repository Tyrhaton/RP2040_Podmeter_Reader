#ifndef ADC_H
#define ADC_H

#include <stdio.h>
#include "pico/stdlib.h"
#include "hardware/adc.h"
#include <hardware/gpio.h>
#include <hardware/irq.h>
#include "hardware/uart.h"

// ADC Register Definitions
#undef ADC_BASE
#define ADC_BASE 0x4004C000
#define ADC_CS   (volatile uint32_t*)(ADC_BASE + 0x00)
#define ADC_FCS  (volatile uint32_t*)(ADC_BASE + 0x08)
#define ADC_FIFO (volatile uint32_t*)(ADC_BASE + 0x0c)
#define ADC_INTE (volatile uint32_t*)(ADC_BASE + 0x18)

// Function Declarations
void adc_init_manual();
void fcs_init_manual();
void start_adc_conversion();
void adc_irq_handler();


// Global Variables
extern volatile uint16_t previous_adc_value;
extern volatile uint16_t adc_value;

// Volume Control 
#include <math.h>

// Global Variables
#define VOLUME_STEPS 101  // Number of volume levels (0 to 100)
#define ADC_MAX 4095    // 12-bit ADC maximum value
#define DEADZONE 25   // Deadzone margin to avoid jitter

extern volatile uint8_t led;
extern volatile uint8_t previous_led;

// Function Declarations
int generate_power_law_levels();
int get_volume_level(uint16_t adc_value, const uint16_t levels[], uint8_t num_steps, uint8_t *last_level);

#endif // ADC_H