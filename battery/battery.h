/*
 * battery.h
 *
 *  Created on: 7 нояб. 2021 г.
 *      Author: babahin
 */

#ifndef BATTERY_BATTERY_H_
#define BATTERY_BATTERY_H_

#define adcFreq   16000000

#define BATTERY_MON_PORT                      gpioPortA
#define BATTERY_MON_PIN                       4

#define BATTERY_STAT_PORT                     gpioPortA
#define BATTERY_STAT_PIN                      5

#define BATTERY_10                            10
#define BATTERY_40                            40
#define BATTERY_100                           100

typedef enum
{
	BATTERY_40_100 = 1,
	BATTERY_10_40,
	BATTERY_0_10,
	BATTERY_CHARGING,
	BATTERY_ERROR_ADC
} BatteryStateType;

void initADC(void);
void initBatStatePin(void);
BatteryStateType check_battery_state(void);

#endif /* BATTERY_BATTERY_H_ */
