/*
 * button.c
 *
 * Created: 7/22/2024 3:37:33 PM
 *  Author: jatan
 */

#include <button.h>

/************************************************************************/
/* BUTTON 1 LOGIC FLAGS
 */
/************************************************************************/
bool BUTTON_ONE_PRESS_STATUS = false;
bool BUTTON_ONE_RELEASE_STATUS = false;
bool LongPressB1Flag = false;
int press_B1_delay_count = DELAY_DEBOUNCE_CN;
int long_press_B1_delay_count = DELAY_PRESS_CN;

/************************************************************************/
/* BUTTON 2 LOGIC FLAGS	                                            */
/************************************************************************/
bool BUTTON_TWO_PRESS_STATUS = false;
bool BUTTON_TWO_RELEASE_STATUS = false;
bool LongPressB2Flag = false;
int press_B2_delay_count = DELAY_DEBOUNCE_CN;
int long_press_B2_delay_count = DELAY_PRESS_CN;

bool BUTTON_TWO_TAKE_ACTION = false;
bool BUTTON_TWO_READY_TAKE_ACTION = false;

/************************************************************************/
/* Button 1 function
 */
/************************************************************************/
bool is_button_one_pressed(void) {

  if (!port_pin_get_input_level(BUTTON_1)) {
    BUTTON_ONE_PRESS_STATUS = true;
    press_B1_delay_count--;
    long_press_B1_delay_count--;

  } else {
    BUTTON_ONE_PRESS_STATUS = false;
    press_B1_delay_count = DELAY_DEBOUNCE_CN;
    long_press_B1_delay_count = DELAY_PRESS_CN;
  }

  // long press delay logic
  if (long_press_B1_delay_count <= 0) {
    long_press_B1_delay_count = 0;
    LongPressB1Flag = true;
  }

  // debounce logic
  if (press_B1_delay_count <= 0) {
    press_B1_delay_count = 0;
    BUTTON_ONE_RELEASE_STATUS = false;

    return true;

  } else {
    BUTTON_ONE_RELEASE_STATUS = true;
    return false;
  }

  return false;
}

/************************************************************************/
/* Button 2 function
 */
/************************************************************************/
bool is_button_two_pressed(void) {

  if (!port_pin_get_input_level(BUTTON_2)) {
    BUTTON_TWO_PRESS_STATUS = true;
    press_B2_delay_count--;
    long_press_B2_delay_count--;

  } else {
    BUTTON_TWO_PRESS_STATUS = false;
    BUTTON_TWO_RELEASE_STATUS = true;
    press_B2_delay_count = DELAY_DEBOUNCE_CN;
    long_press_B2_delay_count = DELAY_PRESS_CN;
    if (BUTTON_TWO_READY_TAKE_ACTION) {
      BUTTON_TWO_READY_TAKE_ACTION = false;
      BUTTON_TWO_TAKE_ACTION = true;
      return true;
    }
  }

  // long press delay logic
  if (long_press_B2_delay_count <= 0) {
    LongPressB2Flag = true;
    BUTTON_TWO_PRESS_STATUS = false;
    BUTTON_TWO_RELEASE_STATUS = true;
    press_B2_delay_count = DELAY_DEBOUNCE_CN;
    long_press_B2_delay_count = DELAY_PRESS_CN;
    BUTTON_TWO_READY_TAKE_ACTION = false;
    BUTTON_TWO_TAKE_ACTION = false;

    return true;
  }

  // debounce logic
  if (press_B2_delay_count <= 0) {
    BUTTON_TWO_RELEASE_STATUS = false;
    press_B2_delay_count = 0;
    BUTTON_TWO_READY_TAKE_ACTION = true;

    // return true;
  } else {
    BUTTON_TWO_RELEASE_STATUS = true;
    return false;
  }

  return false;
}

bool is_button_two_take_action(void) {

  if (BUTTON_TWO_TAKE_ACTION) {
    BUTTON_TWO_TAKE_ACTION = false;

    return true;
  }
  return false;
}