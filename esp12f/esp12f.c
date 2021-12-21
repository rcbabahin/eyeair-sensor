#include "stdint.h"
#include "stdio.h"
#include "app/framework/include/af.h"
#include "uartdrv.h"
#include "esp12f.h"
#include "sl_sleeptimer.h"
#include "em_wdog.h"

#define BUF_SIZE		150
#define TIMEOUT_MAX	600

typedef struct
{
  char buffer[BUF_SIZE];
  volatile uint16_t head;
  volatile uint16_t tail;
} ring_buffer;

ring_buffer rb_rx;

void BufferClear(char *b, uint8_t size)
{
	memset(b, '\0', size);
}

void RingBuffer_Init(ring_buffer *rb)
{
	memset(rb->buffer, '\0', BUF_SIZE);
	rb->head = 0;
	rb->tail = 0;
}

void RingBuffer_Flush(ring_buffer *rb)
{
	RingBuffer_Init(rb);
}

uint16_t RingBuffer_IsDataAvaliable(ring_buffer *rb)
{
	return (uint16_t)(BUF_SIZE + rb->head - rb->tail) % BUF_SIZE;
}

int RingBuffer_Peek(ring_buffer *rb)
{
	if (rb->head == rb->tail)
		return -1;
	else
		return rb->buffer[rb->tail];
}

void RingBuffer_AddChar(char c, ring_buffer *rb)
{
	uint16_t i = (rb->head + 1) % BUF_SIZE;
	/* it will just stop to add characters if head + 1 == tail */
	if (i != rb->tail)
	{
			rb->buffer[rb->head] = c;
			rb->head = i;
	}
}

int RingBuffer_ReadChar(ring_buffer *rb)
{
	if (rb->head == rb->tail)
			return -1;
	else
	{
			char c = rb->buffer[rb->tail];
			rb->tail = (rb->tail + 1) % BUF_SIZE;
			return c;
	}
}

void USART_SendString(USART_TypeDef *usart, const char *s)
{
	while(*s != '\0')	USART_Tx(usart, *s++);
}

void USART1_RX_IRQHandler(void)
{
	RingBuffer_AddChar((char)USART_RxDataGet(USART1), &rb_rx);
}

static void timeout_callback(sl_sleeptimer_timer_handle_t *handle, void *data)
{
	volatile bool *wait_flag = (bool *)data;

	(void)handle;

	*wait_flag = false;
}

int WaitForAnswer(char *answer, const char *s)
{
	int retval = -1;
	uint16_t i = 0, j = 0;
	uint8_t len = strlen(s);
	volatile bool wait = true;
	sl_sleeptimer_timer_handle_t timeout_timer;

	sl_sleeptimer_start_timer_ms(&timeout_timer, TIMEOUT_MAX, timeout_callback, (void *)&wait, 0, 0);

	while (wait)
	{
			if (RingBuffer_IsDataAvaliable(&rb_rx))
			{

					answer[i] = RingBuffer_ReadChar(&rb_rx);

					if (answer[i++] == s[j])
							j++;
					else
							j = 0;

					if (j == (len))
					{
							retval = 1;
							wait = false;
					}
			}
			else
			{
					WDOGn_Feed(DEFAULT_WDOG);
			}
	}

	sl_sleeptimer_stop_timer(&timeout_timer);
	RingBuffer_Flush(&rb_rx);

	return retval;
}

uint8_t WIFI_Init(void)
{
	uint8_t state = 1;
	char answer[200];
	RingBuffer_Init(&rb_rx);

//  USART_SendString(USART1, "AT+RST\r\n");
//  if (WaitForAnswer(answer, "OK\r\n") < 0)
//  {
////      Error_Handler(ans);
//  }
//
//  BufferClear(answer, 200);

	USART_SendString(USART1, "AT\r\n");
	if (WaitForAnswer(answer, "OK\r\n") < 0)
	{
//			Error_Handler(ans);
	}

  BufferClear(answer, 200);

//  USART_SendString(USART1, "AT+CWJAP?\r\n");
//  if (WaitForAnswer(answer, "OK\r\n") < 0)
//  {
////      Error_Handler(ans);
//  }
//
//  BufferClear(answer, 200);
//
//  USART_SendString(USART1, "AT+CWJAP=\"eyeair\",\"03062022\"\r\n");
//  if (WaitForAnswer(answer, "OK\r\n") < 0)
//  {
////      Error_Handler(ans);
//  }
//
//	BufferClear(answer, 200);

	USART_SendString(USART1, "AT+CIFSR\r\n");
	if (WaitForAnswer(answer, "OK\r\n") < 0)
	{
//			Error_Handler(ans);
	}

	BufferClear(answer, 200);

	USART_SendString(USART1, "AT+CIPSTART=\"TCP\",\"192.168.173.1\",7070\r\n");
	if (WaitForAnswer(answer, "OK\r\n") < 0)
	{
			if (strstr(answer, "CONNECTED") == NULL)
				state = 0;
	}

	return state;
}

uint8_t WIFI_TCPSendData(char *str_data, uint8_t len)
{
	uint8_t state = 1;
	char send_str[16];
	char answer[150];
	snprintf(send_str, sizeof(send_str), "AT+CIPSEND=%d\r\n", len);

	USART_SendString(USART1, send_str);
	if (WaitForAnswer(answer, "OK\r\n> ") < 0)
	{
//			Error_Handler(ans);
			state = 0;
	}

	BufferClear(answer, 150);

	USART_SendString(USART1, str_data);
	if (WaitForAnswer(answer, "OK\r\n") < 0)
	{
//			Error_Handler(ans);
			state = 0;
	}

	return state;
}
