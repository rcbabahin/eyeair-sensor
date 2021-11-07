#include <stddef.h>
#include <stdio.h>
#include <string.h>
#include <stdarg.h>
#include "stdbool.h"
#include "em_cmu.h"
#include "em_timer.h"
#include "em_ldma.h"
#include "buzzer.h"
#include "sl_sleeptimer.h"

uint16_t HappyBirthday[] = {
	262, 262, 294, 262, 349, 330, 262,
	262, 294, 262, 392, 349, 262, 262,
	523, 440, 349, 330, 294, 466, 466,
	440, 349, 392, 349};

uint16_t notes[7] = {
		2093, 2349, 2637, 2793, 3136, 3520, 3951
};

uint16_t dangerous[5] = {
		2093, 3520, 2093, 3520, 2093
};

/**************************************************************************//**
 * @brief
 *    GPIO initialization
 *****************************************************************************/
void init_GPIO_buzzer_button(void)
{
  // Enable GPIO and clock
  CMU_ClockEnable(cmuClock_GPIO, true);

  // Configure PC8 as output
  GPIO_PinModeSet(BUZZER_PORT, BUZZER_PIN, gpioModePushPull, 0);

  // Configure PC9 as input with glitch filter enabled
  GPIO_PinModeSet(BUTTON_SOUND_PORT, BUTTON_SOUND_PIN, gpioModeInputPullFilter, 1);
}

/**************************************************************************//**
 * @brief
 *    TIMER initialization
 *****************************************************************************/
void init_timer(void)
{
  /*// Enable clock for TIMER0 module
  CMU_ClockEnable(cmuClock_TIMER1, true);

  // Configure TIMER0 Compare/Capture for output compare
  // Use PWM mode, which sets output on overflow and clears on compare events
  TIMER_InitCC_TypeDef timerCCInit = TIMER_INITCC_DEFAULT;
  timerCCInit.mode = timerCCModePWM;
  TIMER_InitCC(TIMER1, 1, &timerCCInit);

  TIMER1->ROUTELOC0 |=  TIMER_ROUTELOC0_CC1LOC_LOC12;
  TIMER1->ROUTEPEN |= TIMER_ROUTEPEN_CC1PEN;

  // Set top value to overflow at the desired PWM_FREQ frequency
  TIMER_TopSet(TIMER1, CMU_ClockFreqGet(cmuClock_TIMER1) / freq);

  // Set compare value for initial duty cycle
  TIMER_CompareSet(TIMER1, 1, (TIMER_TopGet(TIMER1) * volume) / 100);

  // Configure TIMER0 Compare/Capture for output compare
  // Use PWM mode, which sets output on overflow and clears on compare events
  timerCCInit.mode = timerCCModeCompare;
  TIMER_InitCC(TIMER0, 2, &timerCCInit);

  // Set compare value for initial duty cycle
  TIMER_CompareSet(TIMER0, 2, (TIMER_TopGet(TIMER0) *0.001) );

  TIMER_IntEnable (TIMER0, TIMER_IEN_CC2);
  NVIC_EnableIRQ (TIMER0_IRQn);

   // Initialize the timer
  TIMER_Init_TypeDef timerInit = TIMER_INIT_DEFAULT;
  TIMER_Init(TIMER1, &timerInit);*/

	// Enable clock for WTIMER0 module
	//  CMU_ClockEnable(cmuClock_WTIMER0, true);

	  // Configure WTIMER0 Compare/Capture for output compare
	  // Use PWM mode, which sets output on overflow and clears on compare events
	  TIMER_InitCC_TypeDef timerCCInit = TIMER_INITCC_DEFAULT;
	  timerCCInit.mode = timerCCModePWM;
	  TIMER_InitCC(WTIMER0, 0, &timerCCInit);

	  // Set route to Location 28 and enable
	  // WTIM0_CC0 #30 is PC8
	  WTIMER0->ROUTELOC0 |=  TIMER_ROUTELOC0_CC0LOC_LOC28;
	  WTIMER0->ROUTEPEN |= TIMER_ROUTEPEN_CC0PEN;

	  // Set top value to overflow at the desired PWM_FREQ frequency
	  //TIMER_TopSet(WTIMER0, CMU_ClockFreqGet(cmuClock_WTIMER0) / BUZZER_DEFAULT_FREQ);

	  // Set compare value for initial duty cycle
	  //TIMER_CompareSet(WTIMER0, 0, (TIMER_TopGet(WTIMER0) * BUZZER_DEFAULT_VOLUME_MUTE) / 100);

	  // Initialize and start timer with no prescaling
	  TIMER_Init_TypeDef timerInit = TIMER_INIT_DEFAULT;
	  TIMER_Init(WTIMER0, &timerInit);

	  // Trigger DMA on compare event to set CCVB to update duty cycle on next period
	 // TIMER_IntEnable(WTIMER0, TIMER_IEN_CC0);
}

void deinit_channel_timer(void)
{
	 TIMER_InitCC_TypeDef timerCCInit = TIMER_INITCC_DEFAULT;
	 timerCCInit.mode = timerCCModeOff;
	 TIMER_InitCC(TIMER1, 1, &timerCCInit);
}

/*void TIMER0_IRQHandler(void)
{
  static uint32_t i = 0;

  // Acknowledge the interrupt
  uint32_t flags = TIMER_IntGet(TIMER0);
  TIMER_IntClear(TIMER0, flags);

  // Check for capture event on channel 0
  if (flags & TIMER_IF_CC2) {

    // Record input capture value
  i++;
  }
}*/

void buzzer_set_freq(uint16_t freq)
{
	// Set top value to overflow at the desired PWM_FREQ frequency
	  TIMER_TopSet(WTIMER0, CMU_ClockFreqGet(cmuClock_WTIMER0) / freq);
}

void buzzer_set_volume(uint16_t volume)
{
  // Set compare value for initial duty cycle
  TIMER_CompareSet(WTIMER0, 0, (TIMER_TopGet(WTIMER0) * volume) / 100);
}

void buzzer_sound(uint16_t *buffer_sound, uint8_t buffer_size)
{
	buzzer_set_volume(BUZZER_DEFAULT_VOLUME_MAX);

	for(uint8_t i = 0; i < buffer_size; i++)
	{

		buzzer_set_freq(buffer_sound[i]);
		init_timer();
		sl_sleeptimer_delay_millisecond(100);
	}

	buzzer_set_volume(BUZZER_DEFAULT_VOLUME_MUTE);

	WTIMER0->CMD = TIMER_CMD_STOP;
}

void buzzer_start_sound(void)
{
	buzzer_sound(notes,6);
}

void buzzer_dangerous_sound(void)
{
	buzzer_sound(dangerous,5);
}

void init_buzzer(void)
{
	  // Initializations
	  // Enable clock for WTIMER0 module
    CMU_ClockEnable(cmuClock_WTIMER0, true);

	  init_GPIO_buzzer_button();
	  //init_timer();
	  buzzer_start_sound();
}

