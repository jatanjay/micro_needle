
/************************************************************************/
/* PWM_MOTOR_CONTROL :: 3 - SPEED, with system 10ms TC */
/* auth: jatan pandya
 */
/* date: 3/12/2025 - v.1.2.3 */


/* version log */
/************************************************************************/

1.0.0 = PWM Motor actuation on button #1 press, Indication LED cycle (7) colors
1.1.0 = 3 Speed PWM Motor w/ Pulsating mode, LED Array via PWM generation, Battery Charging algorithm and testing
1.2.0 = Remove Button #1 operation, Button #1 Operation on release (unlike on press as <v1.1.0)), add Sleep Mode for battery conservation, Long Press to shutdown/go to sleep
1.2.1 = Indication LED on charge routines finetuing wrt brightness, flicker etc. ; Battery Management and Display algorithm finetuning ; Motor PWM finetuning
1.2.2 = Device Now shows battery state for 2 seconds before going to sleep (long press), Button Response finetune, 
1.2.3 = Code Cleanup before generating Release .hex
  

/************************************************************************/



/************************************************************************/

#include "asf.h"

#include "system_setup.h"

#include "pwm_motor.h"

#include "led_driver.h"

#include "pwm_led.h"

#include "button.h"

#include "system_state.h"

#include "system_logic.h"

#include "adc_sample.h"

int main(void) {
  startup_sys_configs();
  while (true) {
    system_state(); // Get latest system_state
    system_logic(); // Invoke System Logic
  }
}
