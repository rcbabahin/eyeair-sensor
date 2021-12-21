#include "app/framework/include/af.h"
#include "em_cmu.h"
#include "em_timer.h"
#include "ws2812.h"
#include "sht20.h"
#include "pmsa003.h"
#include "ccs811.h"
#include "eyeair.h"
#include "buzzer.h"
#include "battery.h"
#include "em_wdog.h"

extern EmberEventControl startBuzzerSoundDangerousEventControl;

#define COUNTER_PARAM_DEFAULT	\
{															\
		0,												\
		0,												\
		0													\
}

volatile uint8_t flag_first_dangerous = 1;

PMSASensorType pmsa003;
SHTSensorType sht20;
CCSSensorType ccs811;

stateLedType stateLED;

DeviceType EyeAirDevice =
{
		.ccs = &ccs811,
		.pmsa = &pmsa003,
		.sht = &sht20,
		.battery_state = BATTERY_40_100,
		.wifi_connected = 0
};

counter_parameter_board counter_CO2 = COUNTER_PARAM_DEFAULT;
counter_parameter_board counter_TVOC = COUNTER_PARAM_DEFAULT;
counter_parameter_board counter_PM25 = COUNTER_PARAM_DEFAULT;
counter_parameter_board counter_PM1 = COUNTER_PARAM_DEFAULT;
counter_parameter_board counter_PM10 = COUNTER_PARAM_DEFAULT;

static LedColorType check_parameter_boundary(
		uint16_t parameter,
		uint16_t acceptable_border,
		uint16_t dangerous_border,
		counter_parameter_board* counter
		)
{
	LedColorType status_led = NOT_SWITCH;

	if(parameter >= dangerous_border)
	{
			counter->dangerous++;
			if(counter->acceptable != 0) counter->acceptable--;
			if(counter->norm != 0) counter->norm--;

			if(counter->dangerous >= COUNT_ITERATION_OF_SWITCH)
			{
					//SET_RED_LIGHT(NUM_LED);
					counter->dangerous = 0;
					return status_led = RED;
			}
	}
	else if(parameter >= acceptable_border)
	{
			counter->acceptable++;
			if(counter->dangerous != 0) counter->dangerous--;
			if(counter->norm != 0) counter->norm--;

			if(counter->acceptable >= COUNT_ITERATION_OF_SWITCH)
			{
					//SET_ORANGE_LIGHT(NUM_LED);
					counter->acceptable = 0;
					return status_led = ORANGE;
			}
	}
	else
	{
			counter->norm++;
			if(counter->dangerous != 0) counter->dangerous--;
			if(counter->acceptable != 0) counter->acceptable--;

			if(counter->norm >= COUNT_ITERATION_OF_SWITCH)
			{
					//SET_GREEN_LIGHT(NUM_LED);
					counter->norm = 0;
					return status_led = GREEN;
			}
	}

	return status_led;
}



void stop_sound_dangerous(void)
{
	emberEventControlSetInactive(startBuzzerSoundDangerousEventControl);
	flag_first_dangerous = 1;
}

void sound_dangerous(void)
{
	 if ((GPIO_PinInGet(BUTTON_SOUND_PORT, BUTTON_SOUND_PIN) == BUTTON_PRESSED_SOUND_ON))
	 {
			 if(flag_first_dangerous)
			 {
					 emberEventControlSetActive(startBuzzerSoundDangerousEventControl);
					 flag_first_dangerous = 0;
			 }
	 }
	 else
	 {
			 stop_sound_dangerous();
	 }
}

void border_control_CO2_TVOC(void)
{
	// CHECK CO2
	switch(check_parameter_boundary(EyeAirDevice.ccs->co2, ACCEPTABLE_BORDER_CO2, DANGEROUS_BORDER_CO2, &counter_CO2))
	{
		case GREEN:  SET_GREEN_LIGHT(LED_CO2); stop_sound_dangerous(); break;
		case ORANGE: SET_ORANGE_LIGHT(LED_CO2); stop_sound_dangerous(); break;
		case RED:    SET_RED_LIGHT(LED_CO2); sound_dangerous(); break;
	}

	WDOGn_Feed(DEFAULT_WDOG);

	// CHECK TVOC
	switch(check_parameter_boundary(EyeAirDevice.ccs->tvoc, ACCEPTABLE_BORDER_TVOC, DANGEROUS_BORDER_TVOC, &counter_TVOC))
	{
		case GREEN:  SET_GREEN_LIGHT(LED_TVOC); stop_sound_dangerous(); break;
		case ORANGE: SET_ORANGE_LIGHT(LED_TVOC); stop_sound_dangerous(); break;
		case RED:    SET_RED_LIGHT(LED_TVOC); sound_dangerous(); break;
	}

	if(GPIO_PinInGet(gpioPortA, 5) == 1)
		  {
				if(GPIO_PinInGet(gpioPortA, 5) == 1)
				 {SET_WHITE_LIGHT(LED_ENABLE);}
			}
		else
			{
				if(GPIO_PinInGet(gpioPortA, 5) == 0)
			   {SET_TURQUOISE_LIGHT(LED_ENABLE);}
			}

	change_color_WS2812();

	WDOGn_Feed(DEFAULT_WDOG);
}

void border_control_PM(void)
{
	// CHECK ALL PM
	uint8_t status_1_0, status_2_5, status_10_0;

	status_1_0 = check_parameter_boundary(EyeAirDevice.pmsa->PM1_0_SP, ACCEPTABLE_BORDER_PM_1_25, DANGEROUS_BORDER_PM_1_25, &counter_PM1);
	status_2_5 = check_parameter_boundary(EyeAirDevice.pmsa->PM2_5_SP, ACCEPTABLE_BORDER_PM_1_25, DANGEROUS_BORDER_PM_1_25, &counter_PM25);
	status_10_0= check_parameter_boundary(EyeAirDevice.pmsa->PM10_0_SP, ACCEPTABLE_BORDER_PM_10, DANGEROUS_BORDER_PM_10, &counter_PM10);

	if((status_1_0!=NOT_SWITCH)||(status_2_5!=NOT_SWITCH)||(status_10_0!=NOT_SWITCH))
	{

			if((status_1_0==RED)||(status_2_5==RED)||(status_10_0==RED))
			{
					SET_RED_LIGHT(LED_PM);
					sound_dangerous();
			}
			else if((status_1_0==ORANGE)||(status_2_5==ORANGE)||(status_10_0==ORANGE))
			{
					SET_ORANGE_LIGHT(LED_PM);
					stop_sound_dangerous();
			}
			else
			{
					SET_GREEN_LIGHT(LED_PM);
					stop_sound_dangerous();
			}
	}

	WDOGn_Feed(DEFAULT_WDOG);

	if(GPIO_PinInGet(gpioPortA, 5) == 1)
	  {
			if(GPIO_PinInGet(gpioPortA, 5) == 1)
			 {SET_WHITE_LIGHT(LED_ENABLE);}
		}
	else
		{
			if(GPIO_PinInGet(gpioPortA, 5) == 0)
		   {SET_TURQUOISE_LIGHT(LED_ENABLE);}
		}

	change_color_WS2812();

	WDOGn_Feed(DEFAULT_WDOG);
}

void calibration_by_env_data(void)
{
	if((EyeAirDevice.sht->temp != 0) && (EyeAirDevice.sht->rh != 0))
		ccs811_set_env_data(I2C0, EyeAirDevice.sht->temp * 1000, EyeAirDevice.sht->rh * 1000);
}
