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

typedef enum
{
	BATTERY_40_100 = 1,
	BATTERY_10_40,
	BATTERY_0_10
} BatteryStateType;

#endif /* BATTERY_BATTERY_H_ */
