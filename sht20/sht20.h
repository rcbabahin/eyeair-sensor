#ifndef SHT20_SHT20_H_
#define SHT20_SHT20_H_

#define SHT20_I2C_ADDR					0x80 // (0x40 << 1)
#define SHT20_HOLD_MASTER				1
#define SHT20_READ_TEMP_HOLD		0xE3
#define	SHT20_READ_RH_HOLD			0xE5
#define SHT20_READ_TEMP_NOHOLD	0xF3
#define SHT20_READ_RH_NOHOLD		0xF5
#define	SHT20_WRITE_REG					0xE6
#define SHT20_READ_REG					0xE7
#define SHT20_SOFT_RESET				0xFE
#define SHT20_TIMEOUT						1000

typedef enum
{
	RES_14_12 = 0x00,
	RES_12_8 = 0x01,
	RES_13_10 = 0x80,
	RES_11_11 = 0x81,
} SHT20_Resolution;

typedef struct
{
	float temp;
	float rh;
} SHTSensorType;

void SHT20_SoftReset(void);
uint8_t SHT20_ReadUserReg(void);
uint16_t SHT20_GetRaw(uint8_t cmd);
float SHT20_GetTemperature(uint8_t hold);
float SHT20_GetRelativeHumidity(uint8_t hold);
void SHT20_SetResolution(SHT20_Resolution res);
void I2C_LeaderWrite(uint16_t followerAddress, uint8_t *txBuff, uint8_t numBytes);
void I2C_LeaderRead(uint16_t followerAddress, uint8_t *rxBuff, uint8_t numBytes);
void SHT20_Init(SHTSensorType *sht);

#endif /* SHT20_SHT20_H_ */
