#include <stddef.h>
#include <stdio.h>
#include <string.h>
#include <stdarg.h>
#include "stdbool.h"
#include "em_cmu.h"
#include "em_timer.h"
#include "em_ldma.h"
#include "ws2812.h"
#include "sl_sleeptimer.h"
#include "em_adc.h"
#include "battery.h"
#include "em_wdog.h"

// Note: change this to set the desired Output frequency in Hz
#define PWM_FREQ 800000

// Buffer size
#define BUFFER_SIZE 11

uint16_t BUF_DMA[ARRAY_LEN] = {0};

void ws2812_init_buf(void)
{
  for(uint8_t i = DELAY_LEN; i < ARRAY_LEN; i++) BUF_DMA[i] = LOW;
}

void ws2812_pixel_rgb_to_buf_dma(uint8_t Rpixel , uint8_t Gpixel, uint8_t Bpixel, uint16_t posX)
{
  for(uint8_t i = 0; i < 8; i++)
  {
    if (BitIsSet(Rpixel, (7 - i)) == 1)
    {
      BUF_DMA[DELAY_LEN + posX * 24 + i + 8] = HIGH;
    }
    else
    {
      BUF_DMA[DELAY_LEN + posX * 24 + i + 8] = LOW;
    }

    if (BitIsSet(Gpixel, (7 - i)) == 1)
    {
      BUF_DMA[DELAY_LEN + posX * 24 + i + 0] = HIGH;
    }
    else
    {
      BUF_DMA[DELAY_LEN + posX * 24 + i + 0] = LOW;
    }

    if (BitIsSet(Bpixel, (7 - i)) == 1)
    {
      BUF_DMA[DELAY_LEN + posX * 24 + i + 16] = HIGH;
    }
    else
    {
      BUF_DMA[DELAY_LEN + posX * 24 + i + 16] = LOW;
    }
  }
}
// Note: change this to change the duty cycles used in this example
static const uint16_t dutyCyclePercentages[BUFFER_SIZE] =
  {0, 10, 20, 30, 40, 50, 60, 70, 80, 90, 100};

// Buffer of duty cycle values for DMA transfer to CCVB
// Buffer is populated after TIMER is initialized and Top value is set
static uint16_t buffer[BUFFER_SIZE];

/**************************************************************************//**
 * @brief
 *    GPIO initialization
 *****************************************************************************/
void init_GPIO_WS2812(void)
{
  // Enable GPIO and clock
  CMU_ClockEnable(cmuClock_GPIO, true);

  // Configure PC10 as output
  //GPIO_PinModeSet(gpioPortC, 10, gpioModePushPull, 0);
  GPIO_PinModeSet(gpioPortD, 12, gpioModePushPull, 0);
}

/**************************************************************************//**
 * @brief
 *    TIMER initialization
 *****************************************************************************/
void initTimer(void)
{
  // Enable clock for TIMER0 module
  CMU_ClockEnable(cmuClock_TIMER1, true);

  // Configure TIMER0 Compare/Capture for output compare
  // Use PWM mode, which sets output on overflow and clears on compare events
  TIMER_InitCC_TypeDef timerCCInit = TIMER_INITCC_DEFAULT;
  timerCCInit.mode = timerCCModePWM;
  TIMER_InitCC(TIMER1, 0, &timerCCInit);

  // Set route to Location 15 and enable
  // TIM0_CC0 #15 is PC10
 // TIMER0->ROUTELOC0 |=  TIMER_ROUTELOC0_CC0LOC_LOC15;
 // TIMER0->ROUTEPEN |= TIMER_ROUTEPEN_CC0PEN;
  // TIM0_CC0 #20 is PD12
  TIMER1->ROUTELOC0 |=  TIMER_ROUTELOC0_CC0LOC_LOC20;
  TIMER1->ROUTEPEN |= TIMER_ROUTEPEN_CC0PEN;

  // Set top value to overflow at the desired PWM_FREQ frequency
  TIMER_TopSet(TIMER1, CMU_ClockFreqGet(cmuClock_TIMER1) / PWM_FREQ);

  // Initialize and start timer with no prescaling
  TIMER_Init_TypeDef timerInit = TIMER_INIT_DEFAULT;
  timerInit.dmaClrAct = true;

  TIMER_Init(TIMER1, &timerInit);
}

/**************************************************************************//**
 * @brief
 *    Populate buffer with timer duty cycle values
 *****************************************************************************/
void populateBuffer(void)
{
  for (uint32_t i = 0; i < BUFFER_SIZE; i++) {
    buffer[i] = (uint16_t) (TIMER_TopGet(TIMER1) * dutyCyclePercentages[i] / 100);
  }
}

/**************************************************************************//**
* @brief
*    Initialize the LDMA module
*
* @details
*    Configure the channel descriptor to use the default peripheral to
*    memory transfer descriptor. Modify it to not generate an interrupt
*    upon transfer completion (we don't need it). Additionally, the transfer
*    configuration selects the TIMER0_UFOF signal as the trigger for the LDMA
*    transaction to occur.
*
* @note
*    The descriptor object needs to at least have static scope persistence so
*    that the reference to the object is valid beyond its first use in
*    initialization
*****************************************************************************/
void initLdma(void)
{
  // Channel descriptor configuration
  static LDMA_Descriptor_t descriptor =
    /*LDMA_DESCRIPTOR_LINKREL_M2P_BYTE(&buffer,            // Memory source address
                                    &TIMER1->CC[0].CCVB, // Peripheral destination address
                                    BUFFER_SIZE,         // Number of bytes per transfer
                                    0);  */                // Link to same descriptor

  LDMA_DESCRIPTOR_LINKREL_M2P_BYTE(&BUF_DMA,            // Memory source address
  		                             &TIMER1->CC[0].CCVB, // Peripheral destination address
  		                             ARRAY_LEN,         // Number of bytes per transfer
  		                             0);
  descriptor.xfer.size     = ldmaCtrlSizeHalf; // Unit transfer size
  descriptor.xfer.doneIfs  = 0;                // Don't trigger interrupt when done

  // Transfer configuration and trigger selection
  LDMA_TransferCfg_t transferConfig =
    LDMA_TRANSFER_CFG_PERIPHERAL(ldmaPeripheralSignal_TIMER1_CC0);

  // LDMA initialization
  LDMA_Init_t init = LDMA_INIT_DEFAULT;
  LDMA_Init(&init);

  // Start the transfer
  uint32_t channelNum = 0;
  LDMA_StartTransfer(channelNum, &transferConfig, &descriptor);
}

void change_color_WS2812(void)
{
	 initTimer();
	 initLdma();

	 /*sl_sleeptimer_delay_millisecond(1);

	 TIMER1->CMD = TIMER_CMD_STOP;

	 LDMA_DeInit();*/
}
	  uint8_t  state = 0;
void init_WS2812(void)
{
  BatteryStateType bat_led;

	// Initializations
	  init_GPIO_WS2812();

	  ws2812_init_buf();

	  bat_led = check_battery_state();

	  if(bat_led==BATTERY_CHARGING)
	    {
	      SET_TURQUOISE_LIGHT(LED_ENABLE);
	    }
	  /*else if(bat_led==BATTERY_0_10)
	    {
	      SET_RED_LIGHT(LED_ENABLE);
	    }
    else if(bat_led==BATTERY_10_40)
      {
        SET_ORANGE_LIGHT(LED_ENABLE);
      }*/
    else
      {
        SET_WHITE_LIGHT(LED_ENABLE);
      }

	  WDOGn_Feed(DEFAULT_WDOG);

	  // Initialize DMA only after buffer is populated
	  //populateBuffer();
	  SET_WHITE_LIGHT(LED_PM);
	  SET_WHITE_LIGHT(LED_CO2);
	  SET_WHITE_LIGHT(LED_TVOC);

	  change_color_WS2812();

	  WDOGn_Feed(DEFAULT_WDOG);
}



