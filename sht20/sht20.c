#include "stdint.h"
#include "app/framework/include/af.h"
#include "sht20.h"
#include "em_i2c.h"

/***************************************************************************//**
 * @brief I2C read numBytes from follower device starting at target address
 ******************************************************************************/
void I2C_LeaderRead(uint16_t followerAddress, uint8_t *rxBuff, uint8_t numBytes)
{
  // Transfer structure
  I2C_TransferSeq_TypeDef i2cTransfer;
  I2C_TransferReturn_TypeDef result;

  // Initialize I2C transfer
  i2cTransfer.addr          = followerAddress;
  i2cTransfer.flags         = I2C_FLAG_READ;
  i2cTransfer.buf[0].data   = rxBuff;
  i2cTransfer.buf[0].len    = numBytes;
  i2cTransfer.buf[1].data   = NULL;
  i2cTransfer.buf[1].len    = 0;

  result = I2C_TransferInit(I2C0, &i2cTransfer);

  // Send data
  while (result == i2cTransferInProgress) {
    result = I2C_Transfer(I2C0);
  }
}

/***************************************************************************//**
 * @brief I2C write numBytes to follower device starting at target address
 ******************************************************************************/
void I2C_LeaderWrite(uint16_t followerAddress, uint8_t *txBuff, uint8_t numBytes)
{
  // Transfer structure
  I2C_TransferSeq_TypeDef i2cTransfer;
  I2C_TransferReturn_TypeDef result;

  // Initialize I2C transfer
  i2cTransfer.addr          = followerAddress;
  i2cTransfer.flags         = I2C_FLAG_WRITE;
  i2cTransfer.buf[0].data   = txBuff;
  i2cTransfer.buf[0].len    = numBytes;
  i2cTransfer.buf[1].data   = NULL;
  i2cTransfer.buf[1].len    = 0;

  result = I2C_TransferInit(I2C0, &i2cTransfer);

  // Send data
  while (result == i2cTransferInProgress) {
    result = I2C_Transfer(I2C0);
  }
}

/**
 *  @brief Performs a soft reset.
 */
void SHT20_SoftReset(void)
{
	uint8_t cmd = SHT20_SOFT_RESET;

	I2C_LeaderWrite(SHT20_I2C_ADDR, &cmd, 1);
}

/**
 * @brief Gets the value stored in user register.
 * @return 8-bit value stored in user register, 0 to 255.
 */
uint8_t SHT20_ReadUserReg(void)
{
	uint8_t retval;
	uint8_t cmd = SHT20_READ_REG;

	I2C_LeaderWrite(SHT20_I2C_ADDR, &cmd, 1);
	I2C_LeaderRead(SHT20_I2C_ADDR, &retval, 1);

	return retval;
}

/**
 * @brief Sends the designated command to sensor and read a 16-bit raw value.
 * @param cmd Command to send to sensor.
 * @return 16-bit raw value, 0 to 65535.
 */
uint16_t SHT20_GetRaw(uint8_t cmd)
{
	uint8_t rxbuf[3] = { 0 };

	I2C_LeaderWrite(SHT20_I2C_ADDR, &cmd, 1);
	I2C_LeaderRead(SHT20_I2C_ADDR, rxbuf, 3);

	return (uint16_t)(rxbuf[0] << 8) | rxbuf[1];
}

/**
 * @brief Measures and gets the current temperature.
 * @param hold Holding mode, 0 for no hold master, 1 for hold master.
 * @return Floating point temperature value.
 */
float SHT20_GetTemperature(uint8_t hold)
{
	uint8_t cmd = (hold ? SHT20_READ_TEMP_HOLD : SHT20_READ_TEMP_NOHOLD);
	return -46.85 + 175.72 * (SHT20_GetRaw(cmd) / 65536.0);
}

/**
 * @brief Measures and gets the current relative humidity.
 * @param hold Holding mode, 0 for no hold master, 1 for hold master.
 * @return Floating point relative humidity value.
 */
float SHT20_GetRelativeHumidity(uint8_t hold)
{
	uint8_t cmd = (hold ? SHT20_READ_RH_HOLD : SHT20_READ_RH_NOHOLD);
	return -6 + 125.00 * (SHT20_GetRaw(cmd) / 65536.0);
}

/**
 * @brief Sets the measurement resolution.
 * @param res Enum resolution.
 * @note Available resolutions: RES_14_12, RES_12_8, RES_13_10, RES_11_11.
 * @note RES_14_12 = 14-bit temperature and 12-bit RH resolution, etc.
 */
void SHT20_SetResolution(SHT20_Resolution res)
{
	uint8_t val = SHT20_ReadUserReg();
	val = (val & 0x7E) | res;

	uint8_t temp[2] = { SHT20_WRITE_REG, val };
	I2C_LeaderWrite(SHT20_I2C_ADDR, temp, 2);
}

/**
 * @brief Sets all fields of SHTSensorType struct to initial values and the resolution.
 * @param sht SHT20 Sensor struct.
 */
void SHT20_Init(SHTSensorType *sht)
{
	sht->temp = 0;
	sht->rh = 0;

	SHT20_SetResolution(RES_14_12);
}
