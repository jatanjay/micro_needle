/*
 * system_logic.c
 *
 * Created: 7/22/2024 5:19:03 PM
 *  Author: jatan
 */

#include <system_logic.h>

bool BATTERY_CHARGING = false;
bool BATTERY_CHARGED = false;
bool BATTERY_LOW = false;
bool BATTERY_LOWEST = false;

bool Vbus_State;
bool Chargn_On_State;
bool Chargn_Off_State;
bool Charged_State;

bool SYS_TICK_10MS;
bool SYS_TICK_18MS;
bool SYS_TICK_20MS;

bool SYS_TICK_30MS;
bool SYS_TICK_200MS;

bool SYS_SLEEP;

bool led_wave_flag = false;
extern bool is_cycle_led;
int SleepTickCount;
// extern int flash_led_counter = 0;
// void flash_pwm_led(void);

void sys_sleep_logic(void);
void put_to_sleep(void);

void put_to_sleep(void) {
  system_inactive(); // once entered sleep mode -- sys inactive
  system_set_sleepmode(SYSTEM_SLEEPMODE_STANDBY); // set sleep mode 0
  system_sleep();
}

void sys_sleep_logic(void) { put_to_sleep(); }

void system_inactive(void) {
  motor_disable();          // shutdown PWM motor
  pwm_led_system_cleanup(); // shutdown illumination led
  is_cycle_led = false;
  pwm_led_toggle_count = 0; // reset counter to start the routine from beginning
  reset_chip();
}

void regular_routine(void) {
  static bool motor_status_changed = false;
  static bool led_button_status_changed = false;

  //-------------------------------------------------------------

  // if (is_button_one_pressed()) {
  // if (LongPressB1Flag) {
  // system_inactive();
  // LongPressB1Flag = false;
  // // ALLOW IT TO CYCLE AGAIN } else {
  //
  // if (!motor_status_changed && !led_button_status_changed && !Vbus_State) {
  // // makeshift to stop led array working when connected
  // led_button_status_changed = true;
  // motor_status_changed = true;
  // pwm_led_toggle_count++;
  // motor_toggle_count++;
  // cycle_pwm_led();
  //
  // if (!motor_running && motor_toggle_count == 1) {
  // motor_enable();
  //} else {
  // cycle_pwm_motor();
  //}
  //}
  //}
  //}
  //
  // if (BUTTON_ONE_RELEASE_STATUS) {
  // motor_status_changed = false;
  // led_button_status_changed = false;
  //}

  /** shift from button 1 --> 2 11/17

  **/

  if (is_button_two_pressed()) {
    SleepTickCount = SLEEP_TICK_COUNT;
    if (LongPressB2Flag) {
      system_inactive();
    } else {
      if (!motor_status_changed && !led_button_status_changed &&
          !Vbus_State) { // makeshift to stop led array working when connected

        led_button_status_changed = true;
        motor_status_changed = true;
        pwm_led_toggle_count++;
        motor_toggle_count++;

        // if (motor_toggle_count == 0) {
        // led_wave_flag = true;
        //}
        // if(!BATTERY_LOWEST){

        cycle_pwm_led();
        if (!motor_running && motor_toggle_count == 1) {
          motor_enable();
        } else {
          cycle_pwm_motor();
        }
      }
    }
  }

  if (BUTTON_TWO_RELEASE_STATUS) {
    motor_status_changed = false;
    led_button_status_changed = false;
  }

  if (BATTERY_LOWEST) {
    motor_disable();          // shutdown PWM motor
    pwm_led_system_cleanup(); // shutdown illumination led
    pwm_led_toggle_count = 0;
  }

  //-------------------------------------------------------------

  // if (is_button_two_pressed()) {
  // if (LongPressB2Flag) {
  // system_inactive();
  // LongPressB2Flag = false;
  // // ALLOW IT TO CYCLE AGAIN } else { if (!led_button_status_changed) {
  // pwm_led_toggle_count++;
  // led_button_status_changed = true;
  // cycle_pwm_led();
  //}
  //}
  //}
  // if (BUTTON_TWO_RELEASE_STATUS) {
  // led_button_status_changed = false;
  //}

  if (Vbus_State == false) {
    ; // Enable Motor PWM
  } else {

    if (motor_running) {
      system_inactive();
    }
    // ITS PLUGGED IN
    if (Chargn_On_State == false) { // battery charging (plugged in)
      BATTERY_CHARGING = true;      // show battery charge routine
    } else {
      BATTERY_CHARGING = false;
    }
  }
}

// void regular_routine(void) {
// static bool motor_status_changed = false;
// static bool led_button_status_changed = false;
//
////-------------------------------------------------------------
//
// if (is_button_one_pressed()) {
// if (LongPressB1Flag) {
// system_inactive();
// LongPressB1Flag = false;
// // ALLOW IT TO CYCLE AGAIN
//} else {
// if (!motor_status_changed) {
// motor_toggle_count++;
// motor_status_changed = true;
// if (!motor_running) {
// motor_enable();
//} else {
// cycle_pwm_motor();
//}
//}
//}
//}
//
// if (BUTTON_ONE_RELEASE_STATUS) {
// motor_status_changed = false;
//}
//
////-------------------------------------------------------------
//
// if (is_button_two_pressed()) {
// if (LongPressB2Flag) {
// system_inactive();
// LongPressB2Flag = false;
// // ALLOW IT TO CYCLE AGAIN } else { if (!led_button_status_changed) {
// pwm_led_toggle_count++;
// led_button_status_changed = true;
// cycle_pwm_led();
//}
//}
//}
// if (BUTTON_TWO_RELEASE_STATUS) {
// led_button_status_changed = false;
//}
//
// if (Vbus_State == false) {
//;
//// Enable Motor PWM
//} else {
//
// if (motor_running){
// system_inactive();
//}
//// ITS PLUGGED IN
// if (Chargn_On_State == false) {
// // battery charging (plugged in) BATTERY_CHARGING = true;
// // show battery charge routine
//} else {
// BATTERY_CHARGING = false;
//}
//
//}
//}

void get_battery_level(void) {
  // bool logic = !motor_running && !Vbus_State;
  bool logic = !Vbus_State;
  if (logic) {
    if (adc_result <= VOLTAGE_THRESH_LOWEST) {
      // LOWEST SITUATION
      BATTERY_LOWEST = true;
      BATTERY_LOW = false;
      BATTERY_CHARGED = false;

    } else if (adc_result > VOLTAGE_THRESH_LOWEST &&
               adc_result <= VOLTAGE_THRESH_LOW) { // Ensure adc_result >
                                                   // VOLTAGE_THRESH_LOWEST
      // LOW SITUATION
      BATTERY_LOWEST = false;
      BATTERY_LOW = true;
      BATTERY_CHARGED = false;

    } else if (adc_result > VOLTAGE_THRESH_LOW &&
               adc_result <= VOLTAGE_THRESH_MAX) {
      BATTERY_LOWEST = false;
      BATTERY_LOW = false;
      BATTERY_CHARGED = false;
    } else {
      BATTERY_LOWEST = false;
      BATTERY_LOW = false;
      BATTERY_CHARGED = true;
    }
  } else {
    if (Charged_State) {
      BATTERY_CHARGED = true;
    }
  }
}

/************************************************************************/
/* LOGIC MACHINE */
/************************************************************************/

void system_logic(void) {
  if (SYS_TICK_10MS) {
    SYS_TICK_10MS = false;
    system_state(); // Get latest system_state
    regular_routine();
  }

  // if (SYS_TICK_20MS) {
  // SYS_TICK_20MS = false;
  // if (is_cycle_led){
  // flicker_pwm_led();
  //}
  //}

  if (SYS_TICK_200MS) {
    SYS_TICK_200MS = false;
    sample_adc();
    get_battery_level();
    toggle_nsleep();

    // if (led_wave_flag) {
    // flash_led_counter++;
    // if (flash_led_counter > 7) {
    // flash_led_counter = 7;
    // led_wave_flag = false;
    //}
    // flash_pwm_led();
    //} else {
    // flash_led_counter = 0;
    //}
  }

  if (SYS_SLEEP) {
    SYS_SLEEP = false;
    sys_sleep_logic();
  }
}
