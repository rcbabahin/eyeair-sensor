#include "stdint.h"
#include "app/framework/include/af.h"
#include "pmsa003.h"
#include "uartdrv.h"
// Define receive/transmit operation queues
DEFINE_BUF_QUEUE(EMDRV_UARTDRV_MAX_CONCURRENT_RX_BUFS, rxBufferQueue);
DEFINE_BUF_QUEUE(EMDRV_UARTDRV_MAX_CONCURRENT_TX_BUFS, txBufferQueue);
// Configuration for USART0, location 0
#define MY_UART0                                    \
{                                                   \
  USART0,                                           \
  9600,                                           	\
  USART_ROUTELOC0_TXLOC_LOC0,												\
  USART_ROUTELOC0_RXLOC_LOC0,                       \
  usartStopbits1,                                   \
  usartNoParity,                                    \
  usartOVS16,               												\
	0,																								\
  uartdrvFlowControlNone,                           \
  0,                                        				\
  0,                                                \
  0,                                        				\
  0,                                                \
  (UARTDRV_Buffer_FifoQueue_t *)&rxBufferQueue,     \
  (UARTDRV_Buffer_FifoQueue_t *)&txBufferQueue      \
}

UARTDRV_HandleData_t handleData;
UARTDRV_Handle_t handle = &handleData;


static uint16_t makeWord(uint8_t high, uint8_t low);

void PMSA_Init(PMSASensorType *pmsa)
{
	pmsa->mode = PASSIVE;
	pmsa->PM1_0_SP = 0;
	pmsa->PM2_5_SP = 0;
	pmsa->PM10_0_SP = 0;
	pmsa->PM1_0_AE = 0;
	pmsa->PM2_5_AE = 0;
	pmsa->PM10_0_AE = 0;
	pmsa->particles_0_3um = 0;
	pmsa->particles_0_5um = 0;
	pmsa->particles_1_0um = 0;
	pmsa->particles_2_5um = 0;
	pmsa->particles_5_0um = 0;
	pmsa->particles_10_0um = 0;
	pmsa->checksum = 0;

  UARTDRV_InitUart_t initData = MY_UART0;
  UARTDRV_InitUart(handle, &initData);
}

//static void USART_SendBuffer(USART_TypeDef *usart, uint8_t *buf, uint8_t size)
//{
//	for (uint8_t i = 0; i < size; i++)
//	{
//			USART_Tx(usart, *buf++);
//	}
//}

// Standby mode. For low power consumption and prolong the life of the sensor.
void PMSA_Sleep()
{
	uint8_t command[] = { 0x42, 0x4D, 0xE4, 0x00, 0x00, 0x01, 0x73 };

	UARTDRV_TransmitB(handle, command, sizeof(command));
}

// Operating mode. Stable data should be got at least 30 seconds after the sensor wakeup from the sleep mode because of the fan's performance.
void PMSA_WakeUp()
{
	uint8_t command[] = { 0x42, 0x4D, 0xE1, 0x00, 0x01, 0x01, 0x7 };

	UARTDRV_TransmitB(handle, command, sizeof(command));
}

// Active mode. Default mode after power up. In this mode sensor would send serial data to the host automatically.
void PMSA_ActiveMode(PMSASensorType *pmsa)
{
	uint8_t command[] = { 0x42, 0x4D, 0xE1, 0x00, 0x01, 0x01, 0x71 };

	UARTDRV_TransmitB(handle, command, sizeof(command));
	pmsa->mode = ACTIVE;
}

// Passive mode. In this mode sensor would send serial data to the host only for request.
void PMSA_PassiveMode(PMSASensorType *pmsa)
{
	uint8_t command[] = { 0x42, 0x4D, 0xE1, 0x00, 0x00, 0x01, 0x70 };

	UARTDRV_TransmitB(handle, command, sizeof(command));
	pmsa->mode = PASSIVE;
}

// Request read in Passive Mode.
void PMSA_RequestRead(PMSASensorType *pmsa)
{
	if (pmsa->mode == PASSIVE)
	{
			uint8_t command[] = { 0x42, 0x4D, 0xE2, 0x00, 0x00, 0x01, 0x71 };

			UARTDRV_TransmitB(handle, command, sizeof(command));
	}
}

// Function for parse response.
PMSAStateType PMSA_Read(PMSASensorType *pmsa, uint8_t *buff, uint8_t size)
{
		UARTDRV_ReceiveB(handle, buff, size);
			if (buff[0] != 0x42)
				return START_CHAR_NOT_FOUND;
		// calculate checksum: last two bytes is received checksum
		pmsa->checksum = 0;
		for(uint8_t i = 0; i < size - 2; i++)
			pmsa->checksum += buff[i];

		uint16_t receivedChecksum = makeWord(buff[size - 2], buff[size - 1]);
		// return if calculated checksum didn't match
		if (receivedChecksum != pmsa->checksum)
			return CHECKSUM_ERROR;
		else
		{
				pmsa->PM1_0_SP = makeWord(buff[4], buff[5]);
				pmsa->PM2_5_SP = makeWord(buff[6], buff[7]);
				pmsa->PM10_0_SP = makeWord(buff[8], buff[9]);
				pmsa->PM1_0_AE = makeWord(buff[10], buff[11]);
				pmsa->PM2_5_AE = makeWord(buff[12], buff[13]);
				pmsa->PM10_0_AE = makeWord(buff[14], buff[15]);
				pmsa->particles_0_3um = makeWord(buff[16], buff[17]);
				pmsa->particles_0_5um = makeWord(buff[18], buff[19]);
				pmsa->particles_1_0um = makeWord(buff[20], buff[21]);
				pmsa->particles_2_5um = makeWord(buff[22], buff[23]);
				pmsa->particles_5_0um = makeWord(buff[24], buff[25]);
				pmsa->particles_10_0um = makeWord(buff[26], buff[27]);

				return RECEIVED_SUCCES;
		}
}

static uint16_t makeWord(uint8_t high, uint8_t low)
{
	return ((uint16_t)(high << 8) | low) & 0xFFFF;
}
