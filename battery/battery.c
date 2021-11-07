#include "em_cmu.h"
#include "em_adc.h"
#include "battery.h"

void initADC (void)
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
  initSingle.reference  = adcRef2V5;    // internal 2.5V reference
  initSingle.resolution = adcRes12Bit;  // 12-bit resolution
  initSingle.acqTime    = adcAcqTime4;  // set acquisition time to meet minimum requirements

  initSingle.posSel = adcPosSelAPORT3XCH12; // PA4

  ADC_Init(ADC0, &init);
  ADC_InitSingle(ADC0, &initSingle);
}

BatteryStateType check_battery_state(void)
{
	uint8_t state = 0;
	uint32_t adc_data = 0;

  // Start next ADC conversion
  ADC_Start(ADC0, adcStartSingle);

  // Get ADC result
  adc_data = ADC_DataSingleGet(ADC0);

  // Calculate input voltage in mV
  adc_data = (adc_data * 2500) / 4096;

  if(adc_data < 3120)
  	state = BATTERY_0_10;
  else if(adc_data < 3480)
    state = BATTERY_10_40;
  else
    state = BATTERY_40_100;

  return state;
}

