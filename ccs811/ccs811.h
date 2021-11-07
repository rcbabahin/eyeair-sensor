#ifndef CCS811_H
#define CCS811_H

#include <stdbool.h>
#include "i2cspm.h"
#include "em_gpio.h"
//#include "status.h"

#ifdef __cplusplus
extern "C" {
#endif

/**************************************************************************//**
* @addtogroup ccs811_details CCS881 - Gas Sensor Details
* @brief CCS881 register interface
* @{
******************************************************************************/
/**************************************************************************//**
* @addtogroup ccs811_registers Register Addresses
* @brief Register definitions
* @{
******************************************************************************/
#define CCS811_WAKE_PORT                      gpioPortD
#define CCS811_WAKE_PIN                       11

#define CCS811_ADDR_STATUS                   0x00 /**< Status register                                                                           */
#define CCS811_ADDR_MEASURE_MODE             0x01 /**< Measurement mode and conditions register                                                  */
#define CCS811_ADDR_ALG_RESULT_DATA          0x02 /**< Algorithm result                                                                          */
#define CCS811_ADDR_RAW_DATA                 0x03 /**< Raw ADC data values for resistance and current source used                                */
#define CCS811_ADDR_ENV_DATA                 0x05 /**< Temperature and Humidity data can be written to enable compensation                       */
#define CCS811_ADDR_NTC                      0x06 /**< Provides the voltage across the reference resistor and the voltage across the NTC resistor */
#define CCS811_ADDR_THRESHOLDS               0x10 /**< Thresholds for operation when interrupts are only generated when eCO2 ppm crosses a threshold */
#define CCS811_ADDR_HW_ID                    0x20 /**< Hardware ID                                                                               */
#define CCS811_ADDR_HW_VERSION               0x21 /**< Hardware Version                                                                          */
#define CCS811_ADDR_FW_BOOT_VERSION          0x23 /**< Firmware Boot Version                                                                     */
#define CCS811_ADDR_FW_APP_VERSION           0x24 /**< Firmware Application Version                                                              */
#define CCS811_ADDR_ERR_ID                   0xE0 /**< Error ID                                                                                  */
#define CCS811_ADDR_FW_ERASE                 0xF1 /**< Firmware erase                                                                            */
#define CCS811_ADDR_FW_PROGRAM               0xF2 /**< Firmware programming                                                                      */
#define CCS811_ADDR_FW_VERIFY                0xF3 /**< Firmware verification                                                                     */
#define CCS811_ADDR_APP_START                0xF4 /**< Application start                                                                         */
#define CCS811_ADDR_SW_RESET                 0xFF /**< Software reset                                                                            */
/** @} (end addtogroup ccs811_registers) */

/**************************************************************************//**
* @addtogroup ccs811_measuremode Measure mode value definitions
* @brief Measure mode value definitions
* @{
******************************************************************************/
#define CCS811_MEASURE_MODE_DRIVE_MODE_SHIFT 4     /**< DRIVE_MODE field bit shift value                                                           */
#define CCS811_MEASURE_MODE_DRIVE_MODE_IDLE  0x00  /**< Idle mode, measurements are disabled                                                       */
#define CCS811_MEASURE_MODE_DRIVE_MODE_1SEC  0x10  /**< IAQ Mode 1, a measurement is performed every second                                        */
#define CCS811_MEASURE_MODE_DRIVE_MODE_10SEC 0x20  /**< IAQ Mode 2, a measurement is performed every 10 seconds                                    */
#define CCS811_MEASURE_MODE_DRIVE_MODE_60SEC 0x30  /**< IAQ Mode 3, a measurement is performed every 60 seconds                                    */
#define CCS811_MEASURE_MODE_DRIVE_MODE_RAW   0x40  /**< IAQ Mode 4, Raw Data Mode, a measurement is performed every 250ms for external algorithms  */
#define CCS811_MEASURE_MODE_INTERRUPT        0x08  /**< Interrupt generation enable                                                                */
#define CCS811_MEASURE_MODE_THRESH           0x04  /**< Enable interrupt when eCO2 level exceeds threshold                                         */
/** @} (end addtogroup ccs811_measuremode) */
/** @} (end addtogroup ccs811_details) */
typedef uint32_t status_t;
/// I2CSPM Peripheral
typedef I2C_TypeDef i2cspm_t;

typedef struct
{
	uint16_t tvoc;
	uint16_t co2;
} CCSSensorType;
/***************************************************************************//**
 * @brief
 *    Initialize the chip.
 *
 * @param[in] i2cspm
 *   The I2CSPM instance to use.
 *
 * @return
 *    @retval STATUS_OK Success
 *    @retval STATUS_INITIALIZATION Initialization was unsuccessful
 ******************************************************************************/
status_t ccs811_init(i2cspm_t *i2cspm);

/***************************************************************************//**
 * @brief
 *    De-initialize the chip.
 *
 * @param[in] i2cspm
 *   The I2CSPM instance to use.
 *
 * @return
 *    @retval STATUS_OK Success
 ******************************************************************************/
status_t ccs811_deinit(i2cspm_t *i2cspm);

/***************************************************************************//**
 * @brief
 *    Reads Hardware ID from the CCS811 sensor
 *
 * @param[in] i2cspm
 *   The I2CSPM instance to use.
 *
 * @param[out] hwID
 *    The Hardware ID of the chip (should be 0x81)
 *
 * @return
 *    @retval STATUS_OK Success
 *    @retval STATUS_TRANSMIT I2C transmission error
 ******************************************************************************/
status_t ccs811_get_hardware_id(i2cspm_t *i2cspm, uint8_t *hwID);

/***************************************************************************//**
 * @brief
 *    Set the measurement mode of the CCS811 sensor.
 *
 * @details
 *  This function must be called before reading measurements from the sensor.
 *
 * @param[in] i2cspm
 *   The I2CSPM instance to use.
 *
 * @param[in] measMode
 *    The desired measurement mode
 *
 * @return
 *    @retval STATUS_OK Success
 *    @retval STATUS_TRANSMIT I2C transmission error
 ******************************************************************************/
status_t ccs811_set_measure_mode(i2cspm_t *i2cspm, uint8_t measMode);

/***************************************************************************//**
 * @brief
 *    Perform a firmware update of the CCS811 sensor.
 *
 * @details
 *    This function overwrites the existing firmware, irrespective of the version
 *    number.
 *
 * @param[in] i2cspm
 *   The I2CSPM instance to use.
 *
 * @param[in] firmware
 *    A buffer containing the contents of the firmware update
 *
 * @param[in] length
 *    The length of the firmware update array
 *
 * @return
 *    @retval STATUS_OK Firmware upgrade successful
 *    @retval STATUS_FAIL Firmware upgrade failed
 ******************************************************************************/
status_t ccs811_update_firmware(i2cspm_t *i2cspm, const uint8_t *firmware, uint32_t length);

/***************************************************************************//**
 * @brief
 *    Read out current firmware of the CCS811 sensor.
 *
 * @param[in] i2cspm
 *    The i2cspm instance to use
 *
 * @param[out] fw_version
 *    The current application firmware. The top 4 bits contain the major firmware
 *    version, the next 4 bits contain the minor and the last 8 bits contain the patch version.
 *
 * @retval STATUS_OK Success
 * @retval STATUS_TRANSMIT I2C transmission error
 ******************************************************************************/
status_t ccs811_read_firmware_version(i2cspm_t *i2cspm, uint16_t *fw_version);

/**************************************************************************//**
* @brief
*    Read the status of the CCS811 sensor.
*
* @param[in] i2cspm
*   The I2CSPM instance to use.
*
* @param[out] status
*    The content of the CCS811 Status Register
*
* @return
*    @retval STATUS_OK Success
*    @retval STATUS_TRANSMIT I2C transmission error
******************************************************************************/
status_t ccs811_get_status(i2cspm_t *i2cspm, uint8_t *status);

/***************************************************************************//**
 * @brief
 *    Read data from a specific Mailbox address.
 *
 * @param[in] i2cspm
 *   The I2CSPM instance to use.
 *
 * @param[in] id
 *    The address of the Mailbox register
 *
 * @param[in] length
 *    The number of bytes to read
 *
 * @param[out] data
 *    The data read from the sensor
 *
 * @return
 *    @retval STATUS_OK Success
 *    @retval STATUS_TRANSMIT I2C transmission error
 ******************************************************************************/
status_t ccs811_read_mailbox(i2cspm_t *i2cspm, uint8_t id, uint8_t length, uint8_t *data);

/***************************************************************************//**
 * @brief
 *    Switch the CCS811 chip from boot to application mode.
 *
 * @param[in] i2cspm
 *   The I2CSPM instance to use
 *
 * @return
 *    @retval STATUS_OK  Success
 *    @retval STATUS_TRANSMIT I2C transmission failure
 *    @retval STATUS_NOT_AVAILABLE Application firmware is not present in the CCS811 device
 *    @retval STATUS_INVALID_STATE Chip firmware did not switch to application mode
 ******************************************************************************/
status_t ccs811_start_application(i2cspm_t *i2cspm);

/***************************************************************************//**
 * @brief
 *    Perform software reset on the CCS811.
 *
 * @param[in] i2cspm
 *   The I2CSPM instance to use
 *
 * @return
 *    @retval STATUS_OK Success
 *    @retval STATUS_TRANSMIT I2C transmission error
 ******************************************************************************/
status_t ccs811_software_reset(i2cspm_t *i2cspm);

/***************************************************************************//**
 * @brief
 *    Check whether new measurement data is available.
 *
 * @param[in] i2cspm
 *   The I2CSPM instance to use
 *
 * @return
 *    True if new data available, otherwise false
 ******************************************************************************/
bool ccs811_is_data_available(i2cspm_t *i2cspm);

/***************************************************************************//**
 * @brief
 *    Read measurement data (eCO2 and TVOC) from the CCS811 sensor.
 *
 * @param[in] i2cspm
 *   The I2CSPM instance to use
 *
 * @param[out] eco2
 *    The equivalent CO2 level (in ppm) read from the sensor
 *
 * @param[out] tvoc
 *    The TVOC level (in ppb) read from the sensor
 *
 * @return
 *    @retval STATUS_OK Success
 *    @retval STATUS_TRANSMIT I2C transmission error
 ******************************************************************************/
status_t ccs811_get_measurement(i2cspm_t *i2cspm, uint16_t *eco2, uint16_t *tvoc);

/***************************************************************************//**
 * @brief
 *    Get the latest readings from the sense resistor of the CCS811 sensor.
 *
 * @param[in] i2cspm
 *   The I2CSPM instance to use
 *
 * @param[out] current
 *    The value of current through the sensor
 *
 * @param[out] rawData
 *    The raw ADC reading of the voltage across the sensor with the selected
 *    current
 *
 * @return
 *    @retval STATUS_OK Success
 *    @retval STATUS_TRANSMIT I2C transmission error
 *****************************************************************************/
status_t ccs811_get_raw_data(i2cspm_t *i2cspm, uint16_t *current, uint16_t *rawData);

/***************************************************************************//**
 * @brief
 *    Write temperature and humidity values to the environmental data regs.
 *
 * @param[in] i2cspm
 *   The I2CSPM instance to use.
 *
 * @param[in] tempData
 *    The environmental temperature in milliCelsius
 *
 * @param[in] rhData
 *    The relative humidity in millipercent
 *
 * @return
 *    @retval STATUS_OK Success
 *    @retval STATUS_TRANSMIT I2C transmission error
 ******************************************************************************/
status_t ccs811_set_env_data(i2cspm_t *i2cspm, int32_t tempData, uint32_t rhData);

/** @} (end addtogroup ccs811) */

void CO2_sensor_init(CCSSensorType *ccs);
void CO2_sensor_get_value(CCSSensorType *ccs);

#ifdef __cplusplus
}
#endif
#endif // CCS811_H
