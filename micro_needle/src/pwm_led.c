/*
 * pwm_led.c
 *
 * Created: 7/16/2024 2:41:09 PM
 *  Author: jatan
 */

#include "pwm_led.h"

uint8_t pwm_led_toggle_count = 0;
int flash_led_counter;
bool is_cycle_led;
bool pwm_led_toggle_flag;

void set_pwm_color_channel(uint8_t channel, bool enable) {
  if (enable) {
    tcc_enable(&tcc_instance);
    tcc_set_compare_value(&tcc_instance, channel, INDICATION_LED_DUTY_CYCLE);
  } else {
    tcc_set_compare_value(&tcc_instance, channel, ZERO_DUTY_CYCLE);
    // tcc_set_compare_value(&tcc_instance, channel, 0x0FF);
    tcc_disable(&tcc_instance);
  }

  tcc_force_double_buffer_update(&tcc_instance);
}

void pwm_led_system_cleanup(void) {
  // tcc_disable(&tcc_instance);
  set_pwm_color_channel(RED_CHANNEL, false);
  set_pwm_color_channel(BLUE_CHANNEL, false);
  set_pwm_color_channel(GREEN_CHANNEL, false);
  set_pwm_color_channel(WHITE_CHANNEL, false);
}

void set_pwm_color(int color) {

  switch (color) {
  case 0: // Red
    set_pwm_color_channel(RED_CHANNEL, true);
    break;
  case 1: // Green
    set_pwm_color_channel(GREEN_CHANNEL, true);
    break;
  case 2: // Blue
    set_pwm_color_channel(BLUE_CHANNEL, true);
    break;
  case 3: // White
    set_pwm_color_channel(WHITE_CHANNEL, true);
    break;
  case 4: // Yellow (Red + Green)
    set_pwm_color_channel(RED_CHANNEL, true);
    set_pwm_color_channel(GREEN_CHANNEL, true);
    break;
  case 5: // Purple (Red + Blue)
    set_pwm_color_channel(RED_CHANNEL, true);
    set_pwm_color_channel(BLUE_CHANNEL, true);
    break;
  case 6: // Cyan (Blue + Green)
    set_pwm_color_channel(BLUE_CHANNEL, true);
    set_pwm_color_channel(GREEN_CHANNEL, true);
    break;
  default:
    break;
  }
}

void configure_pwm_tcc(void) {
  tcc_get_config_defaults(&config_tcc, CONF_PWM_MODULE);
  config_tcc.compare.wave_generation = TCC_WAVE_GENERATION_SINGLE_SLOPE_PWM;
  config_tcc.counter.period = CONF_DEFAULT_PERIOD;
  config_tcc.counter.clock_prescaler = TCC_CLOCK_PRESCALER_DIV64;

  config_tcc.compare.match[RED_CHANNEL] = ZERO_DUTY_CYCLE;
  config_tcc.compare.match[BLUE_CHANNEL] = ZERO_DUTY_CYCLE;
  config_tcc.compare.match[GREEN_CHANNEL] = ZERO_DUTY_CYCLE;
  config_tcc.compare.match[WHITE_CHANNEL] = ZERO_DUTY_CYCLE;

  // config_tcc.compare.wave_polarity[RED_CHANNEL] = TCC_WAVE_POLARITY_1;
  // config_tcc.compare.wave_polarity[BLUE_CHANNEL] = TCC_WAVE_POLARITY_1;
  // config_tcc.compare.wave_polarity[GREEN_CHANNEL] = TCC_WAVE_POLARITY_1;
  // config_tcc.compare.wave_polarity[WHITE_CHANNEL] = TCC_WAVE_POLARITY_1;

  config_tcc.pins.wave_out_pin[RED_CHANNEL] = PIN_PA04F_TCC0_WO0; // RED
  config_tcc.pins.wave_out_pin_mux[RED_CHANNEL] = MUX_PA04F_TCC0_WO0;
  config_tcc.pins.enable_wave_out_pin[RED_CHANNEL] = true;

  config_tcc.pins.wave_out_pin[GREEN_CHANNEL] = PIN_PA05F_TCC0_WO1; // GREEN
  config_tcc.pins.wave_out_pin_mux[GREEN_CHANNEL] = MUX_PA05F_TCC0_WO1;
  config_tcc.pins.enable_wave_out_pin[GREEN_CHANNEL] = true;

  config_tcc.pins.wave_out_pin[BLUE_CHANNEL] = PIN_PA08E_TCC0_WO2; // BLUE
  config_tcc.pins.wave_out_pin_mux[BLUE_CHANNEL] = MUX_PA08E_TCC0_WO2;
  config_tcc.pins.enable_wave_out_pin[BLUE_CHANNEL] = true;

  config_tcc.pins.wave_out_pin[WHITE_CHANNEL] = PIN_PA09E_TCC0_WO3; // WHITE
  config_tcc.pins.wave_out_pin_mux[WHITE_CHANNEL] = MUX_PA09E_TCC0_WO3;
  config_tcc.pins.enable_wave_out_pin[WHITE_CHANNEL] = true;

  tcc_init(&tcc_instance, CONF_PWM_MODULE, &config_tcc);
  // tcc_enable(&tcc_instance);
}

void cycle_pwm_led(void) {
  flash_led_counter = 0;
  switch (pwm_led_toggle_count) {
  case 1:
    SET_RED;
    SET_BLU;
    SET_GRN;
    break;
  case 6:
    pwm_led_toggle_count = 0;
    pwm_led_system_cleanup(); // Reset to 1 for red
    break;
  }
}
