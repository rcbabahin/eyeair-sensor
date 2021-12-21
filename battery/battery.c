#include "em_cmu.h"
#include "em_adc.h"
#include "em_gpio.h"
#include "ws2812.h"
#include "battery.h"
#include "gpiointerrupt.h"

void initBatStatePin(void)
{
  // Enable ADC0 clock
  CMU_ClockEnable(cmuClock_GPIO, true);

  GPIO_PinModeSet(gpioPortA, 5, gpioModeInputPullFilter, 1);

  // Enable IRQ for odd numbered GPIO pins
 // NVIC_EnableIRQ(GPIO_ODD_IRQn);

  // Enable falling-edge interrupts for PB pins
 // GPIO_ExtIntConfig(gpioPortA, 5, 5, 1, 1, true);
}



void initADC(void)
{
  // Enable ADC0 clock
  CMU_ClockEnable(cmuClock_ADC0, true);

  // Declare init structs
  ADC_Init_TypeDef init = ADC_INIT_DEFAULT;
  ADC_InitSingle_TypeDef initSingle = ADC_INITSINGLE_DEFAULT;

  // Modify init structs and initialize
  init.prescale = ADC_PrescaleCalc(adcFreq, 0); // Init to max ADC clock for Series 1
  init.timebase = ADC_TimebaseCalc(0);

  initSingle.diff       = false;        // single ended
  initSingle.reference  = adcRefVDD;    // internal 3.3V reference
  initSingle.resolution = adcRes12Bit;  // 12-bit resolution
  initSingle.acqTime    = adcAcqTime4;  // set acquisition time to meet minimum requirements

  initSingle.posSel = adcPosSelAPORT3XCH12; // PA4

  ADC_Init(ADC0, &init);
  ADC_InitSingle(ADC0, &initSingle);
}

BatteryStateType check_battery_state(void)
{
	uint8_t  state = 0;
	uint32_t adc_data = 0;
	float energy_battery = 0;

	if(GPIO_PinInGet(gpioPortA, 5) == 1)
	  {
	   /* // Start next ADC conversion
	     ADC_Start(ADC0, adcStartSingle);

	     // Get ADC result
	     adc_data = ADC_DataSingleGet(ADC0);

	     if(adc_data!=0)
	       {
	           // Calculate input voltage in mV
	           energy_battery = (adc_data * 3.3) / 4096;

	           // Calculate % energy of battery
	           // 100% 2100mV; 0% 1500mV
	           energy_battery = 166.667*energy_battery - 250;

	           if(energy_battery < BATTERY_10)
	             state = BATTERY_0_10;

	           else if(energy_battery < BATTERY_40)
	             state = BATTERY_10_40;

	           else if(energy_battery <= BATTERY_100)
	             state = BATTERY_40_100;

	           else
	             state = BATTERY_ERROR_ADC;

	       }
	     else
	       {
	         state = BATTERY_ERROR_ADC;
	       }*/

			state = BATTERY_40_100;
	  }
	else
	  {
	    state = BATTERY_CHARGING;
	  }
  return state;
}



