#include "stdint.h"
#include "stdio.h"
#include "app/framework/include/af.h"
#include "uartdrv.h"
#include "esp12f.h"
#include "sl_sleeptimer.h"

#define BUF_SIZE	200

volatile uint8_t rxbuf[BUF_SIZE];
volatile uint16_t pos = 0;

void USART_SendString(USART_TypeDef *usart, const char *s)
{
	while(*s != '\0')	USART_Tx(usart, *s++);
}

void USART1_RX_IRQHandler(void)
{
	rxbuf[pos] = USART_RxDataGet(USART1);
	pos++;
}

void WaitFor(const char *s)
{
	uint16_t len = strlen(s);

	for (uint8_t i = 0; i < BUF_SIZE; i++)
		rxbuf[i] = 0;

	while (len != pos) {}
	pos = 0;

	/* TODO: compare strings and do error handling */
}

void WIFI_Init(void)
{
	USART_SendString(USART1, "AT\r\n");
	WaitFor("AT\r\r\n\r\nOK\r\n");

	USART_SendString(USART1, "AT+CIFSR\r\n");
	WaitFor("AT+CIFSR\r\r\n+CIFSR:APIP,\"xxx.xxx.x.x\"\r\n+CIFSR:APMAC,\"xx:xx:xx:xx:xx:xx\"\r\n+CIFSR:STAIP,\"xxx.xxx.x.x\"\r\n+CIFSR:STAMAC,\"xx:xx:xx:xx:xx:xx\"\r\n\r\nOK\r\n");

	USART_SendString(USART1, "AT+CIPSTART=\"TCP\",\"192.168.1.2\",7070\r\n");
	WaitFor("AT+CIPSTART=\"TCP\",\"192.168.1.2\",7070\r\r\nCONNECT\r\n\r\nOK\r\n");
}

void WIFI_TCPSendData(char *str_data, uint8_t len)
{
	char send_str[16];
	char send_str_answer[25];
	char recv_answer[29];
	snprintf(send_str, sizeof(send_str), "AT+CIPSEND=%d\r\n", len);
	snprintf(send_str_answer, sizeof(send_str_answer), "AT+CIPSEND=%d\r\r\n\r\nOK\r\n> ", len);
	snprintf(recv_answer, sizeof(recv_answer), "\r\nRecv %d bytes\r\n\r\nSEND OK\r\n", len);

	USART_SendString(USART1, send_str);
	WaitFor(send_str_answer);
	USART_SendString(USART1, str_data);
	WaitFor(recv_answer);
}

