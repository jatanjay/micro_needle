/*
 * led_driver.c
 *
 * Created: 7/9/2024 4:31:23 PM
 *  Author: jatan
 */

#include "led_driver.h"

struct i2c_master_module i2c_master_instance;
struct i2c_master_packet packet = {KTD2026_DEVICE_ADDRESS, DATA_LENGTH_PRIMARY};

#define BUFFER_TURN_OFF_MAIN_DIGITAL                                           \
  { 0x04, 0x00 }
#define BUFFER_DISABLE_PWM1_TIMER                                              \
  { 0x02, 0x00 }

#define BUFFER_SET_COLOR_GREEN                                                 \
  { 0x04, 0x04 }
#define BUFFER_SET_COLOR_RED                                                   \
  { 0x04, 0x01 }
#define BUFFER_SET_COLOR_BLUE                                                  \
  { 0x04, 0x10 }
#define BUFFER_SET_COLOR_YELLOW                                                \
  { 0x04, 0x05 }
#define BUFFER_SET_COLOR_CYAN                                                  \
  { 0x04, 0x14 }
#define BUFFER_SET_COLOR_WHITE                                                 \
  { 0x04, 0x15 }
#define BUFFER_SET_COLOR_PURPLE                                                \
  { 0x04, 0x11 }

#define BUFFER_SET_COLOR_GREEN_PWM                                             \
  { 0x04, 0x08 }
#define BUFFER_SET_CHARGE_ROUTINE_FLASH_PERIOD                                 \
  { 0x01, 0x10 } // 0x20 --> 0x10 increase flash period
#define BUFFER_SET_CHARGE_ROUTINE_TRISE_TFALL                                  \
  { 0x05, 0xEF }
#define BUFFER_SET_CHARGE_ROUTINE_PWM1_TIMER                                   \
  { 0x02, 0x1C }
#define BUFFER_SET_COLOR_GREEN_BRIGHTNESS                                      \
  { 0x04, 0x00 }

#define BUFFER_SET_COLOR_RED_PWM                                               \
  { 0x04, 0x02 }
#define BUFFER_SET_COLOR_RED_BRIGHTNESS                                        \
  { 0x06, 0x50 }
#define BUFFER_SET_LOW_ROUTINE_FLASH_PERIOD                                    \
  { 0x01, 0x82 }
#define BUFFER_SET_LOW_ROUTINE_TRISE_TFALL                                     \
  { 0x02, 0x32 }

#define BUFFER_SET_COLOR_BLUE_LOWEST_BRIGTHNESS                                \
  { 0x08, 0x03 }
#define BUFFER_SET_COLOR_BLUE_LOW_BRIGTHNESS                                   \
  { 0x08, 0x09 }
#define BUFFER_SET_COLOR_BLUE_HIGH_BRIGTHNESS                                  \
  { 0x08, 0x15 }

#define BUFFER_SET_COLOR_BLUE_PWM                                              \
  { 0x04, 0x20 }
#define BUFFER_SET_COLOR_BLUE_PWM_TIMER                                        \
  { 0x02, 0x19 }
#define BUFFER_SET_COLOR_BLUE_PWM_FLASH                                        \
  { 0x01, 0x82 }

void set_color_green_indication(void) {
  uint8_t buffer_set_color_green[DATA_LENGTH_PRIMARY] = BUFFER_SET_COLOR_GREEN;
  packet.data = buffer_set_color_green;
  packet.address = KTD2026_DEVICE_ADDRESS;
  packet.data_length = DATA_LENGTH_PRIMARY;
  while ((i2c_master_write_packet_wait(&i2c_master_instance, &packet)) !=
         STATUS_OK) {
  }
}

void set_color_red_indication(void) {
  uint8_t buffer_set_color_red[DATA_LENGTH_PRIMARY] = BUFFER_SET_COLOR_RED;
  packet.data = buffer_set_color_red;
  packet.address = KTD2026_DEVICE_ADDRESS;
  packet.data_length = DATA_LENGTH_PRIMARY;
  while ((i2c_master_write_packet_wait(&i2c_master_instance, &packet)) !=
         STATUS_OK) {
  }
}

void set_color_blue_indication(void) {
  uint8_t buffer_set_color_blue[DATA_LENGTH_PRIMARY] = BUFFER_SET_COLOR_BLUE;
  packet.data = buffer_set_color_blue;
  packet.address = KTD2026_DEVICE_ADDRESS;
  packet.data_length = DATA_LENGTH_PRIMARY;
  while ((i2c_master_write_packet_wait(&i2c_master_instance, &packet)) !=
         STATUS_OK) {
  }
}

void set_color_yellow_indication(void) {
  uint8_t buffer_set_color_yellow[DATA_LENGTH_PRIMARY] =
      BUFFER_SET_COLOR_YELLOW;
  packet.data = buffer_set_color_yellow;
  packet.address = KTD2026_DEVICE_ADDRESS;
  packet.data_length = DATA_LENGTH_PRIMARY;

  while ((i2c_master_write_packet_wait(&i2c_master_instance, &packet)) !=
         STATUS_OK) {
  }
}

void set_color_cyan_indication(void) {
  uint8_t buffer_set_color_cyan[DATA_LENGTH_PRIMARY] = BUFFER_SET_COLOR_CYAN;
  packet.data = buffer_set_color_cyan;
  packet.address = KTD2026_DEVICE_ADDRESS;
  packet.data_length = DATA_LENGTH_PRIMARY;

  while ((i2c_master_write_packet_wait(&i2c_master_instance, &packet)) !=
         STATUS_OK) {
  }
}

void set_color_white_indication(void) {
  uint8_t buffer_set_color_white[DATA_LENGTH_PRIMARY] = BUFFER_SET_COLOR_WHITE;
  packet.data = buffer_set_color_white;
  packet.address = KTD2026_DEVICE_ADDRESS;
  packet.data_length = DATA_LENGTH_PRIMARY;

  while ((i2c_master_write_packet_wait(&i2c_master_instance, &packet)) !=
         STATUS_OK) {
  }
}

void reset_chip(void) {

  uint8_t buffer_reset_green_red_channel[DATA_LENGTH_PRIMARY] =
      BUFFER_TURN_OFF_MAIN_DIGITAL;
  packet.data = buffer_reset_green_red_channel;
  packet.address = KTD2026_DEVICE_ADDRESS;
  packet.data_length = DATA_LENGTH_PRIMARY;

  while ((i2c_master_write_packet_wait(&i2c_master_instance, &packet)) !=
         STATUS_OK) {
  }
}

void set_battery_charge_routine(void) {

  uint8_t buffer_set_color_green_PWM[DATA_LENGTH_PRIMARY] =
      BUFFER_SET_COLOR_GREEN_PWM;
  uint8_t buffer_set_charge_routine_flash_period[DATA_LENGTH_PRIMARY] =
      BUFFER_SET_CHARGE_ROUTINE_FLASH_PERIOD;
  uint8_t buffer_set_charge_routine_trise_tfall[DATA_LENGTH_PRIMARY] =
      BUFFER_SET_CHARGE_ROUTINE_TRISE_TFALL;
  uint8_t buffer_set_charge_routine_PWM1_timer[DATA_LENGTH_PRIMARY] =
      BUFFER_SET_CHARGE_ROUTINE_PWM1_TIMER;

  packet.address = KTD2026_DEVICE_ADDRESS;
  packet.data_length = DATA_LENGTH_PRIMARY;

  packet.data = buffer_set_color_green_PWM;
  while ((i2c_master_write_packet_wait(&i2c_master_instance, &packet)) !=
         STATUS_OK) {
  }

  packet.data = buffer_set_charge_routine_flash_period;
  while ((i2c_master_write_packet_wait(&i2c_master_instance, &packet)) !=
         STATUS_OK) {
  }
  packet.data = buffer_set_charge_routine_trise_tfall;
  while ((i2c_master_write_packet_wait(&i2c_master_instance, &packet)) !=
         STATUS_OK) {
  }
  packet.data = buffer_set_charge_routine_PWM1_timer;
  while ((i2c_master_write_packet_wait(&i2c_master_instance, &packet)) !=
         STATUS_OK) {
  }
}

void set_battery_low_routine(void) {

  uint8_t buffer_set_color_red_PWM[DATA_LENGTH_PRIMARY] =
      BUFFER_SET_COLOR_RED_PWM;
  uint8_t buffer_set_low_routine_flash_period[DATA_LENGTH_PRIMARY] =
      BUFFER_SET_LOW_ROUTINE_FLASH_PERIOD;
  uint8_t buffer_set_low_routine_trise_tfall[DATA_LENGTH_PRIMARY] =
      BUFFER_SET_LOW_ROUTINE_TRISE_TFALL;
  uint8_t buffer_set_low_routine_brightness[DATA_LENGTH_PRIMARY] =
      BUFFER_SET_COLOR_RED_BRIGHTNESS;

  packet.address = KTD2026_DEVICE_ADDRESS;
  packet.data_length = DATA_LENGTH_PRIMARY;

  packet.data = buffer_set_color_red_PWM;
  while ((i2c_master_write_packet_wait(&i2c_master_instance, &packet)) !=
         STATUS_OK) {
  }
  packet.data = buffer_set_low_routine_flash_period;
  while ((i2c_master_write_packet_wait(&i2c_master_instance, &packet)) !=
         STATUS_OK) {
  }
  packet.data = buffer_set_low_routine_brightness;
  while ((i2c_master_write_packet_wait(&i2c_master_instance, &packet)) !=
         STATUS_OK) {
  }

  packet.data = buffer_set_low_routine_trise_tfall;
  while ((i2c_master_write_packet_wait(&i2c_master_instance, &packet)) !=
         STATUS_OK) {
  }
}

void set_motor_speed_1_indication(void) {

  uint8_t buffer_set_blue[DATA_LENGTH_PRIMARY] = BUFFER_SET_COLOR_BLUE_PWM;
  uint8_t buffer_set_blue_lowest_brightness[DATA_LENGTH_PRIMARY] =
      BUFFER_SET_COLOR_BLUE_LOWEST_BRIGTHNESS;

  packet.address = KTD2026_DEVICE_ADDRESS;
  packet.data_length = DATA_LENGTH_PRIMARY;

  packet.data = buffer_set_blue;
  while ((i2c_master_write_packet_wait(&i2c_master_instance, &packet)) !=
         STATUS_OK) {
  }

  packet.data = buffer_set_blue_lowest_brightness;
  while ((i2c_master_write_packet_wait(&i2c_master_instance, &packet)) !=
         STATUS_OK) {
  }
}

void set_motor_speed_2_indication(void) {

  uint8_t buffer_set_blue[DATA_LENGTH_PRIMARY] = BUFFER_SET_COLOR_BLUE_PWM;
  uint8_t buffer_set_blue_low_brightness[DATA_LENGTH_PRIMARY] =
      BUFFER_SET_COLOR_BLUE_LOW_BRIGTHNESS;

  packet.address = KTD2026_DEVICE_ADDRESS;
  packet.data_length = DATA_LENGTH_PRIMARY;

  packet.data = buffer_set_blue;
  while ((i2c_master_write_packet_wait(&i2c_master_instance, &packet)) !=
         STATUS_OK) {
  }

  packet.data = buffer_set_blue_low_brightness;
  while ((i2c_master_write_packet_wait(&i2c_master_instance, &packet)) !=
         STATUS_OK) {
  }
}

void set_motor_speed_3_indication(void) {
  uint8_t buffer_set_blue[DATA_LENGTH_PRIMARY] = BUFFER_SET_COLOR_BLUE_PWM;
  uint8_t buffer_set_blue_high_brightness[DATA_LENGTH_PRIMARY] =
      BUFFER_SET_COLOR_BLUE_HIGH_BRIGTHNESS;

  packet.address = KTD2026_DEVICE_ADDRESS;
  packet.data_length = DATA_LENGTH_PRIMARY;

  packet.data = buffer_set_blue;
  while ((i2c_master_write_packet_wait(&i2c_master_instance, &packet)) !=
         STATUS_OK) {
  }

  packet.data = buffer_set_blue_high_brightness;
  while ((i2c_master_write_packet_wait(&i2c_master_instance, &packet)) !=
         STATUS_OK) {
  }
}

void set_motor_pulsating_indication(void) {
  uint8_t buffer_set_blue[DATA_LENGTH_PRIMARY] = BUFFER_SET_COLOR_BLUE_PWM;
  uint8_t buffer_set_blue_high_brightness[DATA_LENGTH_PRIMARY] =
      BUFFER_SET_COLOR_BLUE_HIGH_BRIGTHNESS;
  uint8_t buffer_set_blue_pwm_timer[DATA_LENGTH_PRIMARY] =
      BUFFER_SET_COLOR_BLUE_PWM_TIMER;
  uint8_t buffer_set_blue_pwm_flash[DATA_LENGTH_PRIMARY] =
      BUFFER_SET_COLOR_BLUE_PWM_FLASH;

  packet.address = KTD2026_DEVICE_ADDRESS;
  packet.data_length = DATA_LENGTH_PRIMARY;

  packet.data = buffer_set_blue;
  while ((i2c_master_write_packet_wait(&i2c_master_instance, &packet)) !=
         STATUS_OK) {
  }

  packet.data = buffer_set_blue_high_brightness;
  while ((i2c_master_write_packet_wait(&i2c_master_instance, &packet)) !=
         STATUS_OK) {
  }

  packet.data = buffer_set_blue_pwm_timer;
  while ((i2c_master_write_packet_wait(&i2c_master_instance, &packet)) !=
         STATUS_OK) {
  }

  packet.data = buffer_set_blue_pwm_flash;
  while ((i2c_master_write_packet_wait(&i2c_master_instance, &packet)) !=
         STATUS_OK) {
  }
}

void i2c_master_setup(void) {
  struct i2c_master_config config_i2c_master;
  i2c_master_get_config_defaults(&config_i2c_master);
  config_i2c_master.buffer_timeout = 10000;
  i2c_master_init(&i2c_master_instance, MASTER_MODULE, &config_i2c_master);
  i2c_master_enable(&i2c_master_instance);
}