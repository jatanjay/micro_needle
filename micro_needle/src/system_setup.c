/*
 * system_setup.c
 *
 * Created: 7/22/2024 2:42:56 PM
 *  Author: jatan
 */ 

 #include "system_setup.h"



bool SYS_TICK_10MS = false;
bool SYS_TICK_50MS = false;
bool SYS_TICK_100MS = false;
bool SYS_TICK_200MS = false;
//bool SYS_TICK_500MS = false;
//bool SYS_TICK_1000MS = false;





 /************************************************************************/
/* GPIO - PIN SETUP														*/
/************************************************************************/
 void configure_port_pins(void)
{
	struct port_config config_port_pin;
	port_get_config_defaults(&config_port_pin);
	
	
	/* PA27 is shared between EDBG
	SS and VBUS detection
	
	Usage:

	-Disable pull-up
	- check level on line to detect if VBUS is high and USB cable is present.
	
	*/
	
	config_port_pin.direction  = PORT_PIN_DIR_INPUT;
	config_port_pin.input_pull = PORT_PIN_PULL_DOWN;
	port_pin_set_config(VBUS_PIN, &config_port_pin);
	
	/*
	
	MOTOR'S NSLEEP PIN
	
	*/
	
	config_port_pin.direction  = PORT_PIN_DIR_OUTPUT;
	config_port_pin.input_pull = PORT_PIN_PULL_DOWN;							// START AT PULL DOWN.
	port_pin_set_config(MOTOR_NSLEEP_PIN, &config_port_pin);
	
	
	
	/*
	
	shutdown routine -- turn PA07 low to turn off peripherals
	
	*/
	
	config_port_pin.direction  = PORT_PIN_DIR_OUTPUT;
	config_port_pin.input_pull = PORT_PIN_PULL_UP;								// START AT PULL UP.
	port_pin_set_config(SWITCH_OFF_PIN, &config_port_pin);
	
	
	/*
	
	BUTTON 2
	
	*/
	
	config_port_pin.direction  = PORT_PIN_DIR_INPUT;
	config_port_pin.input_pull = PORT_PIN_PULL_UP;							// START AT PULL DOWN.
	port_pin_set_config(BUTTON_2, &config_port_pin);
	
	
	/*
	GET_CHARGING_STATUS
	*/
	
	config_port_pin.direction  = PORT_PIN_DIR_INPUT;
	config_port_pin.input_pull = PORT_PIN_PULL_DOWN;							// START AT PULL DOWN.
	port_pin_set_config(BAT_CHARGED_PIN, &config_port_pin);
	
	
	/*
	GET_CHARGING_OFF_STATUS
	*/
	
	config_port_pin.direction  = PORT_PIN_DIR_OUTPUT;
	config_port_pin.input_pull = PORT_PIN_PULL_DOWN;							// START AT PULL DOWN.
	port_pin_set_config(CHARGN_OFF_PIN, &config_port_pin);
	
	/*
	SAMPLE ADC PIN
	*/
	
	config_port_pin.direction  = PORT_PIN_DIR_INPUT;
	config_port_pin.input_pull = PORT_PIN_PULL_DOWN;							// START AT PULL DOWN.
	port_pin_set_config(SAMPLE_ADC_PIN, &config_port_pin);
	


	/* Configure LEDs as outputs, turn them off */
	config_port_pin.direction  = PORT_PIN_DIR_OUTPUT;
	port_pin_set_config(XPLAINED_LED, &config_port_pin);

	///* Set buttons as inputs */
	config_port_pin.direction  = PORT_PIN_DIR_INPUT;
	config_port_pin.input_pull = PORT_PIN_PULL_UP;
	port_pin_set_config(BUTTON_1, &config_port_pin);


}




 /************************************************************************/
 /* SYSTEM TC TICK - SETUP												*/
 /************************************************************************/
 void configure_system_tc (void)
 {
	 struct tc_config config_tc;
	 tc_get_config_defaults (&config_tc);
	 config_tc.clock_source = TC_CLOCK_SOURCE;
	 config_tc.counter_size = TC_COUNTER_SIZE;
	 config_tc.clock_prescaler = TC_CLOCK_PRESCALER;
	 config_tc.counter_8_bit.period = SYSTEM_TC_PERIOD_VALUE;

	 config_tc.pwm_channel[TC_COMPARE_CAPTURE_CHANNEL_0].enabled = true;
	 //config_tc.pwm_channel[TC_COMPARE_CAPTURE_CHANNEL_0].pin_out = SYSTEM_TC_PIN_OUT; // PA15 FOR TESTING ; OG PA16 (LED)
	 //config_tc.pwm_channel[TC_COMPARE_CAPTURE_CHANNEL_0].pin_mux = SYSTEM_TC_MUX_OUT; // PA15 FOR TESTING ; OG PA16 (LED)
	 
	 tc_init (&system_timer_instance, SYSTEM_TC, &config_tc);
	 tc_enable (&system_timer_instance);
 }


/************************************************************************/
/* SYSTEM TC TICK - CALLBACK HANDLER									*/
/************************************************************************/
void system_tc_callbacks (void)
{
	tc_register_callback (&system_timer_instance, sys_tc_callback,
	TC_CALLBACK_OVERFLOW);
	tc_enable_callback (&system_timer_instance, TC_CALLBACK_OVERFLOW);
}


/************************************************************************/
/* SYSTEM TC TICK Callback function										*/
/************************************************************************/
void sys_tc_callback(struct tc_module *const module_inst)
{
	static int tick_count_1ms;
	static int tick_count_10ms;
	static int tick_count_50ms;
	static int tick_count_100ms;
	static int tick_count_200ms;
	//static int tick_count_500ms;
	//static int tick_count_1000ms;

	tick_count_1ms++;
	
	
	//port_pin_toggle_output_level (LED0_PIN);					// visually check sys clock on PA16
	
	// Check for 10ms interval
	if (tick_count_1ms >= 10)
	{
		tick_count_10ms++;
		tick_count_1ms = 0;
		SYS_TICK_10MS = true;									// Flag for 10ms interval
		//port_pin_toggle_output_level (LED0_PIN);				// visually check sys clock on PA16
	}
	
	// Check for 50ms interval
	if (tick_count_10ms >= 5)
	{
		tick_count_50ms++;
		tick_count_10ms = 0;
		SYS_TICK_50MS = true;									// Flag for 50ms interval
		//port_pin_toggle_output_level (LED0_PIN);				// visually check sys clock on PA16
	}
	
	// Check for 100ms interval
	if (tick_count_50ms >= 2)
	{
		tick_count_100ms++;
		tick_count_50ms = 0;
		SYS_TICK_100MS = true;									// Flag for 100ms interval
		//port_pin_toggle_output_level (LED0_PIN);				// visually check sys clock on PA16
	}
	
	
	// Check for 200ms interval
	if (tick_count_100ms >= 2)
	{
		tick_count_200ms++;
		tick_count_100ms = 0;
		SYS_TICK_200MS = true;									// Flag for 200ms interval
		//port_pin_toggle_output_level (LED0_PIN);				// visually check sys clock on PA16
	}

	//if (tick_count_200ms >= 2)
	//{
		//tick_count_500ms++;
		//tick_count_200ms = 0;
		//SYS_TICK_500MS = true;                                  // Flag for 500ms interval
		////port_pin_toggle_output_level (LED0_PIN);               // visually check sys clock on PA16
	//}
	 //
	//// Check for 1000ms interval
	//if (tick_count_500ms >= 2)
	//{
		//tick_count_1000ms++;
		//tick_count_500ms = 0;
		//SYS_TICK_1000MS = true;                                 // Flag for 1000ms interval
		////port_pin_toggle_output_level (LED0_PIN);               // visually check sys clock on PA16
	//}
	
}
















void configure_extint_channel(void);
void configure_extint_callbacks(void);
void extint_detection_callback(void);


#define BUTTON_0_EIC_LINE_custom		1


void configure_extint_channel(void)
{

	struct extint_chan_conf config_extint_chan;
	extint_chan_get_config_defaults(&config_extint_chan);

	config_extint_chan.gpio_pin           = PIN_PA15A_EIC_EXTINT1;
	config_extint_chan.gpio_pin_mux       = MUX_PA15A_EIC_EXTINT1;
	config_extint_chan.wake_if_sleeping   = true;

	config_extint_chan.gpio_pin_pull      = EXTINT_PULL_UP;
	config_extint_chan.detection_criteria = EXTINT_DETECT_BOTH;
	extint_chan_set_config(BUTTON_0_EIC_LINE_custom, &config_extint_chan);

}

void configure_extint_callbacks(void)
{
	extint_register_callback(extint_detection_callback,
	BUTTON_0_EIC_LINE_custom,
	EXTINT_CALLBACK_TYPE_DETECT);

	extint_chan_enable_callback(BUTTON_0_EIC_LINE_custom,
	EXTINT_CALLBACK_TYPE_DETECT);
}

















void extint_detection_callback(void)
{
	//motor_enable();
	//LED_Off(LED0_PIN);

}


// todo

/* extin on motor button, only for waking motor up, put is button pressed logic in callback */

// clean up modules, system config.h


void configure_sleep_clock(void);

void configure_sleep_clock() {
	// Define the mask value
	const uint32_t mask = 0x00000040;

	// Call the function to set the mask for APB A bus
	enum status_code result = system_apb_clock_set_mask(SYSTEM_CLOCK_APB_APBA, mask);

	if (result != STATUS_OK) {
		Assert(false);
	}
}






void enable_sleep_mode(void);

void enable_sleep_mode(){
	configure_sleep_clock();
	system_set_sleepmode(SYSTEM_SLEEPMODE_STANDBY);
	system_sleep();
}


























/************************************************************************/
/* SYSTEM startup default GPIO pin state setup function					*/
/************************************************************************/

 void startup_default_pin_state(void){
	 port_pin_set_output_level(MOTOR_NSLEEP_PIN,LOW);
	 port_pin_set_output_level(SWITCH_OFF_PIN,HIGH); // at high rev 2
	 port_pin_set_output_level(BUTTON_2,LOW);
	 port_pin_set_output_level(BAT_CHARGED_PIN,LOW);
	 port_pin_set_output_level(CHARGN_OFF_PIN,HIGH);
	 port_pin_set_output_level(SAMPLE_ADC_PIN,LOW);
 }


/************************************************************************/
/* SYSTEM startup function call (config functions)						*/
/************************************************************************/
void startup_sys_configs(void){
	system_init();									// System Initialize
	system_interrupt_enable_global();				// System Interrupts
	configure_port_pins();							// System PORTs
	startup_default_pin_state();
	i2c_master_setup();								// Startup I2C


	configure_system_tc();							// System Clock
	system_tc_callbacks();							// System Clock Callback
	configure_pwm_tcc();							// Startup PWM
	configure_adc();
	configure_pwm_generator();


	configure_extint_channel();
	configure_extint_callbacks();
	extint_detection_callback();


}