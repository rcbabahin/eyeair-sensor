#ifndef EYEAIR_H_
#define EYEAIR_H_
#include "battery.h"

#define ACCEPTABLE_BORDER_CO2     700
#define DANGEROUS_BORDER_CO2      1000

#define ACCEPTABLE_BORDER_TVOC    75
#define DANGEROUS_BORDER_TVOC     120

#define ACCEPTABLE_BORDER_PM_1_25    25
#define DANGEROUS_BORDER_PM_1_25     40

#define ACCEPTABLE_BORDER_PM_10      54
#define DANGEROUS_BORDER_PM_10       154

#define COUNT_ITERATION_OF_SWITCH 3

typedef enum
{
	NOT_SWITCH = 0,
	WHITE,
	TURQUOISE,
	GREEN,
	ORANGE,
	RED
} LedColorType;

typedef struct
{
	uint8_t PM;
	uint8_t CO2;
	uint8_t TVOC;
	uint8_t battery;
} stateLedType;

typedef struct
{
	uint8_t acceptable;
	uint8_t dangerous;
	uint8_t norm;
} counter_parameter_board;

typedef struct
{
	PMSASensorType *pmsa;
	SHTSensorType *sht;
	CCSSensorType *ccs;
	BatteryStateType battery_state;
	uint8_t wifi_connected;
} DeviceType;

extern DeviceType EyeAirDevice;
extern stateLedType stateLED;

void border_control_CO2_TVOC(void);
void border_control_PM(void);
void calibration_by_env_data(void);

#endif /* EYEAIR_H_ */
