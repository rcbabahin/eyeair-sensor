// This callback file is created for your convenience. You may add application
// code to this file. If you regenerate this file over a previous version, the
// previous version will be overwritten and any code you have added will be
// lost.
#include "stdio.h"
#include "app/framework/include/af.h"
#include "hal/hal.h"
#include EMBER_AF_API_NETWORK_STEERING
#include "app/framework/include/af.h"
#include "app/util/ezsp/ezsp-enum.h"
#include "ccs811.h"
#include "pmsa003.h"
#include "sht20.h"
#include "ws2812.h"
#include "eyeair.h"
#include "buzzer.h"
#include "esp12f.h"
#include "battery.h"
#include "hal/micro/cortexm3/diagnostic.h"

#define TEST_DEVICE

#define BUFFER_SIZE	32
uint8_t buffer[BUFFER_SIZE];
char answer[150];

EmberEventControl checkBatteryEventControl, startScanAndConnectEventControl, PMSAEventControl,	SHTEventControl,
CCSEventControl, startBuzzerAndRGBEventControl, startBuzzerSoundDangerousEventControl;

void Init_I2C(I2C_TypeDef *i2c)
{
	 // Use default settings
	  I2C_Init_TypeDef i2cInit = I2C_INIT_DEFAULT;

		// Enable oscillator to GPIO and I2C0 modules
	  CMU_ClockEnable(cmuClock_I2C0, true);
	  CMU_ClockEnable(cmuClock_GPIO, true);

	  // Using PA2 (SDA) and PA3 (SCL)
	  GPIO_PinModeSet(gpioPortA, 2, gpioModeWiredAndPullUpFilter, 1);
	  GPIO_PinModeSet(gpioPortA, 3, gpioModeWiredAndPullUpFilter, 1);

	  // Enable pins at location 2 as specified in datasheet
	  i2c->ROUTEPEN = 0;
	  i2c->ROUTELOC0 = (_I2C_ROUTELOC0_SDALOC_LOC2 << _I2C_ROUTELOC0_SDALOC_SHIFT) |
                     (_I2C_ROUTELOC0_SCLLOC_LOC2 << _I2C_ROUTELOC0_SCLLOC_SHIFT);
	  i2c->ROUTEPEN = I2C_ROUTEPEN_SDAPEN | I2C_ROUTEPEN_SCLPEN;
	  // Initializing the I2C
	  I2C_Init(i2c, &i2cInit);
}

void Init_USART(USART_TypeDef *usart)
{
  USART_InitAsync_TypeDef init = USART_INITASYNC_DEFAULT;
  init.baudrate = 9600;
//  init.baudrate = 115200;

  // Enable oscillator to GPIO and USART0 modules
  CMU_ClockEnable(cmuClock_HFPER, true);
  CMU_ClockEnable(cmuClock_GPIO, true);
  CMU_ClockEnable(cmuClock_USART0, true);

  // set pin modes for UART0 TX and RX pins
  GPIO_PinModeSet(gpioPortA, 1, gpioModeInput, 0);
  GPIO_PinModeSet(gpioPortA, 0, gpioModePushPull, 1);
//  GPIO_PinModeSet(gpioPortF, 5, gpioModeInput, 0);
//  GPIO_PinModeSet(gpioPortF, 4, gpioModePushPull, 1);

  // Initialize USART asynchronous mode and route pins
  USART_InitAsync(usart, &init);

  usart->ROUTEPEN |= USART_ROUTEPEN_RXPEN | USART_ROUTEPEN_TXPEN;
  usart->ROUTELOC0 = USART_ROUTELOC0_RXLOC_LOC0 | USART_ROUTELOC0_TXLOC_LOC0;
//  usart->ROUTELOC0 = USART_ROUTELOC0_RXLOC_LOC28 | USART_ROUTELOC0_TXLOC_LOC28;

  USART_InitAsync_TypeDef init1 = USART_INITASYNC_DEFAULT;
  init.baudrate = 115200;

  // Enable oscillator to GPIO and USART0 modules
  CMU_ClockEnable(cmuClock_USART1, true);

  // set pin modes for UART1 TX and RX pins
  GPIO_PinModeSet(gpioPortC, 7, gpioModeInput, 0);
  GPIO_PinModeSet(gpioPortC, 6, gpioModePushPull, 1);

  // Initialize USART asynchronous mode and route pins
  USART_InitAsync(USART1, &init1);

  // Enable NVIC USART sources
  NVIC_ClearPendingIRQ(USART1_RX_IRQn);
  NVIC_EnableIRQ(USART1_RX_IRQn);

  USART1->ROUTEPEN |= USART_ROUTEPEN_RXPEN | USART_ROUTEPEN_TXPEN;
  USART1->ROUTELOC0 = USART_ROUTELOC0_RXLOC_LOC11 | USART_ROUTELOC0_TXLOC_LOC11;
}

static void FindAmountOfDigits(uint16_t p, uint8_t *n)
{
	if (p < 10)
		*n = 1;
	else if (p >= 10)
		*n = 2;
	else if (p >= 100)
		*n = 3;
	else if (p >= 1000)
		*n = 4;
}

void startBuzzerAndRGBEventHandler(void)
{
	emberEventControlSetInactive(startBuzzerAndRGBEventControl);
//	if (halResetWasCrash()) {
//		halPrintCrashSummary(comPortUsart0);
//		halPrintCrashDetails(comPortUsart0);
//		halPrintCrashData(comPortUsart0);
//	}
	init_buzzer();
  PMSA_Init(EyeAirDevice.pmsa);
  SHT20_Init(EyeAirDevice.sht);
  CO2_sensor_init(EyeAirDevice.ccs);
	USART_IntEnable(USART1, USART_IEN_RXDATAV);
	EyeAirDevice.wifi_connected = WIFI_Init();

	emberEventControlSetActive(checkBatteryEventControl);
#ifdef TEST_DEVICE
  emberEventControlSetActive(startScanAndConnectEventControl);
  emberEventControlSetActive(PMSAEventControl);
  emberEventControlSetActive(SHTEventControl);
  emberEventControlSetActive(CCSEventControl);
#else
  emberEventControlSetDelayMinutes(startScanAndConnectEventControl, 20);
  emberEventControlSetDelayMinutes(PMSAEventControl, 20);
  emberEventControlSetDelayMinutes(SHTEventControl, 20);
  emberEventControlSetDelayMinutes(CCSEventControl, 20);
#endif
}

void checkBatteryEventHandler(void)
{
	/*if(GPIO_PinInGet(gpioPortA, 5) == 1)
	  {
			 SET_WHITE_LIGHT(LED_ENABLE);
		}
	else
		{
		   SET_TURQUOISE_LIGHT(LED_ENABLE);
		}

	change_color_WS2812();*/

	emberEventControlSetInactive(checkBatteryEventControl);
	//emberEventControlSetDelayMS(checkBatteryEventControl, 5000);
}

void PMSAEventHandler(void)
{
	if (!EyeAirDevice.wifi_connected)
	{
			EyeAirDevice.wifi_connected = WIFI_Init();
	}

	PMSA_RequestRead(EyeAirDevice.pmsa);
	PMSAStateType state = PMSA_Read(EyeAirDevice.pmsa, buffer, BUFFER_SIZE);

	if (state == RECEIVED_SUCCES)
	{
			emberAfWriteServerAttribute(1, ZCL_PM1_0_MFG_SPECIFIC_CLUSTER_ID,
			                            ZCL_ATTRIBUTE_ONE_ATTRIBUTE_ID,
			                            (uint8_t *)&(EyeAirDevice.pmsa->PM1_0_AE),
			                            ZCL_INT16U_ATTRIBUTE_TYPE);
			emberAfWriteServerAttribute(1, ZCL_PM2_5_MFG_SPECIFIC_CLUSTER_ID,
			                            ZCL_ATTRIBUTE_ONE_ATTRIBUTE_ID,
			                            (uint8_t *)&(EyeAirDevice.pmsa->PM2_5_AE),
			                            ZCL_INT16U_ATTRIBUTE_TYPE);
			emberAfWriteServerAttribute(1, ZCL_PM10_0_MFG_SPECIFIC_CLUSTER_ID,
			                            ZCL_ATTRIBUTE_ONE_ATTRIBUTE_ID,
			                            (uint8_t *)&(EyeAirDevice.pmsa->PM10_0_AE),
			                            ZCL_INT16U_ATTRIBUTE_TYPE);

			uint8_t n1_0, n2_5, n10;

			FindAmountOfDigits(EyeAirDevice.pmsa->PM1_0_AE, &n1_0);
			FindAmountOfDigits(EyeAirDevice.pmsa->PM2_5_AE, &n2_5);
			FindAmountOfDigits(EyeAirDevice.pmsa->PM10_0_AE, &n10);

			uint8_t n_pm = 26 + n1_0 + n2_5 + n10;
			char data_pm[n_pm + 1];
			snprintf(data_pm, sizeof(data_pm), "PM1.0:%d, PM2.5:%d, PM10.0:%d   ",
			         (uint8_t)EyeAirDevice.pmsa->PM1_0_AE,
			         (uint8_t)EyeAirDevice.pmsa->PM2_5_AE,
			         (uint8_t)EyeAirDevice.pmsa->PM10_0_AE);

			EyeAirDevice.wifi_connected = WIFI_TCPSendData(data_pm, n_pm);

			border_control_PM();

			emberEventControlSetInactive(PMSAEventControl);
			emberEventControlSetDelayMS(PMSAEventControl, 1000);
	}
}

void SHTEventHandler(void)
{
	emberEventControlSetInactive(SHTEventControl);

	EyeAirDevice.sht->temp = SHT20_GetTemperature(1);
	EyeAirDevice.sht->rh = SHT20_GetRelativeHumidity(1);
	int16_t t = (int16_t)(EyeAirDevice.sht->temp * 100);
	int16_t r = (int16_t)(EyeAirDevice.sht->rh * 100);

	emberAfWriteServerAttribute(1, ZCL_TEMP_MEASUREMENT_CLUSTER_ID,
	                            ZCL_CURRENT_TEMPERATURE_ATTRIBUTE_ID,
	                            (uint8_t *)&t, ZCL_INT16U_ATTRIBUTE_TYPE);
	emberAfWriteServerAttribute(1, ZCL_RELATIVE_HUMIDITY_MEASUREMENT_CLUSTER_ID,
	                            ZCL_RELATIVE_HUMIDITY_MEASURED_VALUE_ATTRIBUTE_ID,
	                            (uint8_t *)&r, ZCL_INT16U_ATTRIBUTE_TYPE);

	calibration_by_env_data();

	char data_temp_rh[15];
	snprintf(data_temp_rh, sizeof(data_temp_rh), "TEMP:%d, RH:%d", (uint8_t)(EyeAirDevice.sht->temp-2), (uint8_t)EyeAirDevice.sht->rh);

	EyeAirDevice.wifi_connected = WIFI_TCPSendData(data_temp_rh, 14);

	emberEventControlSetDelayMS(SHTEventControl, 2000);
}

void CCSEventHandler(void)
{
	CO2_sensor_get_value(EyeAirDevice.ccs);

	emberAfWriteServerAttribute(1, ZCL_CARBON_DIOXIDE_MFG_SPECIFIC_CLUSTER_ID,
	                            ZCL_ATTRIBUTE_ONE_ATTRIBUTE_ID,
	                            (uint8_t *)&(EyeAirDevice.ccs->co2),
	                            ZCL_INT16U_ATTRIBUTE_TYPE);
	emberAfWriteServerAttribute(1, ZCL_TVOC_MFG_SPECIFIC_CLUSTER_ID,
	                            ZCL_ATTRIBUTE_ONE_ATTRIBUTE_ID,
	                            (uint8_t *)&(EyeAirDevice.ccs->tvoc),
	                            ZCL_INT16U_ATTRIBUTE_TYPE);

	uint8_t n_co2, n_tvoc;

	FindAmountOfDigits(EyeAirDevice.ccs->co2, &n_co2);
	FindAmountOfDigits(EyeAirDevice.ccs->tvoc, &n_tvoc);

	uint8_t n_ccs = 14 + n_co2 + n_tvoc;
	char data_ccs[n_ccs + 1];
	snprintf(data_ccs, sizeof(data_ccs), "TVOC:%d, CO2:%d   ", EyeAirDevice.ccs->tvoc, EyeAirDevice.ccs->co2);

	EyeAirDevice.wifi_connected = WIFI_TCPSendData(data_ccs, n_ccs);

	emberEventControlSetInactive(CCSEventControl);
	emberEventControlSetDelayMS(CCSEventControl, 4000);

  border_control_CO2_TVOC();
}

void startScanAndConnectEventHandler(void)
{
  if (emberAfNetworkState() != EMBER_JOINED_NETWORK) {
      emberAfPluginNetworkSteeringStart();
  } else {
      emberEventControlSetInactive(startScanAndConnectEventControl);
  }
}

void startBuzzerSoundDangerousEventHandler(void)
{
	emberEventControlSetInactive(startBuzzerSoundDangerousEventControl);

	buzzer_dangerous_sound();

	emberEventControlSetDelayMS(startBuzzerSoundDangerousEventControl, 10000);
}

/** @brief Main Start
 *
 * This function is called at the start of main after the HAL has been
 * initialized.  The standard main function arguments of argc and argv are
 * passed in.  However not all platforms have support for main() function
 * arguments.  Those that do not are passed NULL for argv, therefore argv should
 * be checked for NULL before using it.  If the callback determines that the
 * program must exit, it should return true.  The value returned by main() will
 * be the value written to the returnCode pointer.  Otherwise the callback
 * should return false to let normal execution continue.
 *
 * @param returnCode   Ver.: always
 * @param argc   Ver.: always
 * @param argv   Ver.: always
 */
boolean emberAfMainStartCallback(int* returnCode,
                                 int argc,
                                 char** argv)
{
  // NOTE:  argc and argv may not be supported on all platforms, so argv MUST be
  // checked for NULL before referencing it.  On those platforms without argc 
  // and argv "0" and "NULL" are passed respectively.

  return false;  // exit?
}
/** @brief Main Init
 *
 * This function is called from the application's main function. It gives the
 * application a chance to do any initialization required at system startup. Any
 * code that you would normally put into the top of the application's main()
 * routine should be put into this function. This is called before the clusters,
 * plugins, and the network are initialized so some functionality is not yet
 * available.
        Note: No callback in the Application Framework is
 * associated with resource cleanup. If you are implementing your application on
 * a Unix host where resource cleanup is a consideration, we expect that you
 * will use the standard Posix system calls, including the use of atexit() and
 * handlers for signals such as SIGTERM, SIGINT, SIGCHLD, SIGPIPE and so on. If
 * you use the signal() function to register your signal handler, please mind
 * the returned value which may be an Application Framework function. If the
 * return value is non-null, please make sure that you call the returned
 * function from your handler to avoid negating the resource cleanup of the
 * Application Framework itself.
 *
 */
void emberAfMainInitCallback(void)
{
  Init_I2C(I2C0);
	Init_USART(USART0);
	CMU_ClockSelectSet(cmuClock_LFE, cmuSelect_LFXO);
	CMU_ClockEnable(cmuClock_RTCC, true);
	sl_sleeptimer_init();
	initADC();
	initBatStatePin();
  init_WS2812();
  emberEventControlSetActive(startBuzzerAndRGBEventControl);
}


