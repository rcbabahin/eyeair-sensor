#ifndef ESP12F_ESP12F_H_
#define ESP12F_ESP12F_H_

void WIFI_Init(void);
void USART_SendString(USART_TypeDef *usart, const char *s);
void WaitFor(const char *s);
void WIFI_TCPSendData(char *str_data, uint8_t len);

#endif /* ESP12F_ESP12F_H_ */
