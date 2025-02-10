#include "adc.h"

// Global Variables
volatile uint16_t previous_adc_value = 0;
volatile uint16_t adc_value = 0;

// ADC Initialization
void adc_init_manual() {
    *ADC_CS = (1 << 0);     // Enable ADC
    *ADC_CS &= ~(0xF << 12); // Clear DIV field
    *ADC_CS |= (1 << 12);   // Set DIV field to 1
    sleep_ms(10);           // Stabilization delay
}

// FIFO Initialization
void fcs_init_manual() {
    *ADC_FCS |= (1 << 0);   // Enable FIFO
    *ADC_FCS &= ~(1 << 1);  // Clear SHIFT bit
    *ADC_FCS &= ~(0xF << 24); // Clear THRESH field
    *ADC_FCS |= (1 << 24);  // Set THRESH field to 1
    *ADC_FCS |= (1 << 3);   // Enable FIFO interrupt
    *ADC_INTE = (1 << 0);   // Enable interrupt
    sleep_ms(10);           // Stabilization delay
}

// Start ADC Conversion
void start_adc_conversion() {
    *ADC_CS |= (1 << 2);    // Start single conversion
}

// ADC Interrupt Handler
void adc_irq_handler() {
    adc_value = *ADC_FIFO & 0xFFF; // Read 12-bit ADC result
}