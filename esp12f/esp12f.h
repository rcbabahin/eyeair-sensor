#ifndef ESP12F_ESP12F_H_
#define ESP12F_ESP12F_H_

uint8_t WIFI_Init(void);
void USART_SendString(USART_TypeDef *usart, const char *s);
int WaitFor(const char *s);
int WaitForAnswer(char *answer, const char *s);
void BufferClear(char *b, uint8_t size);
uint8_t WIFI_TCPSendData(char *str_data, uint8_t len);

#endif /* ESP12F_ESP12F_H_ */
