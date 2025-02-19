/*
 * system_logic.h
 *
 * Created: 7/22/2024 5:19:18 PM
 *  Author: jatan
 */

#ifndef SYSTEM_LOGIC_H_
#define SYSTEM_LOGIC_H_

#include "asf.h"

#include "system_setup.h"

#include "pwm_motor.h"

#include "led_driver.h"

#include "pwm_led.h"

#include "button.h"

#include "system_state.h"

#include "adc_sample.h"

typedef enum {
  BATTERY_STATE_LOWEST,
  BATTERY_STATE_LOW,
  BATTERY_STATE_CHARGED,
} BatteryState;

extern bool BATTERY_CHARGING;
extern bool BATTERY_CHARGED;
extern bool BATTERY_LOW;
extern bool BATTERY_LOWEST;

void regular_routine(void);
void system_inactive(void);
void system_logic(void);
void get_battery_level(void);

// #define VOLTAGE_THRESH_MAX 0x0DDD		// 4
// #define VOLTAGE_THRESH_LOW 0x0C71		// 0x0D2C -- 3.6
// #define VOLTAGE_THRESH_LOWEST 0x0C4D		// 0x0C7A -- 3.54

/*
New Requirement:

20% low,
10% critically low


operating window

4 -- 3.54

1. 20% = (4-3.54 = 0.46V) == New range = 0.80�0.46V = 0.368V = 4V - 0.368V
= 3.632V
2. 10% = 0.90�0.46V=0.414V == 4V - 0.414V = 3.586V

*/

#define VOLTAGE_THRESH_MAX 0x0D84    // 3.9
#define VOLTAGE_THRESH_LOW 0x0C96    // 0x0D2C -- 3.632V
#define VOLTAGE_THRESH_LOWEST 0x0C6D // 0x0C7A -- 3.586V

/*
0x0C7A (3194.88) -- Calculated (3.6v)
0x0D2C (3372.37) -- LWO THRESHOLD (3.8)
0x0D1E (3358.00) -- Close to low threshold for testing
*/

#endif /* SYSTEM_LOGIC_H_ */