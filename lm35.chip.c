// Wokwi Custom Chip - For docs and examples see:
// https://docs.wokwi.com/chips-api/getting-started
//
// SPDX-License-Identifier: MIT
// Copyright 2023 

#include "wokwi-api.h"
#include <stdlib.h>

typedef struct {
  pin_t pin_out;
  uint32_t temp_attr;
} chip_state_t;

static void chip_timer_callback(void *user_data) {
  chip_state_t *chip = (chip_state_t*)user_data;
  
  // Read the current position of the temperature slider
  float temp_c = attr_read_float(chip->temp_attr);
  
  // LM35 Formula: 10mV per degree Celsius (0.01V / °C)
  float voltage = temp_c * 0.010;
  
  // Keep voltage safe for standard positive ADC ranges
  if (voltage < 0.0) voltage = 0.0; 
  
  // Write the analog voltage to the OUT pin
  pin_dac_write(chip->pin_out, voltage);
}

void chip_init(void) {
  chip_state_t *chip = malloc(sizeof(chip_state_t));

  // Initialize the output pin in ANALOG mode
  chip->pin_out = pin_init("OUT", ANALOG);
  chip->temp_attr = attr_init_float("temperature", 25.0);

  const timer_config_t timer_config = {
    .callback = chip_timer_callback,
    .user_data = chip,
  };
  timer_t timer_id = timer_init(&timer_config);
  timer_start(timer_id, 25000, true); // Refresh pin voltage every 25ms
}
