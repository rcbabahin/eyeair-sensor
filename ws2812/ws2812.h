#ifndef WS2812_WS2812_H_
#define WS2812_WS2812_H_

#define DELAY_LEN 100 //48
#define LED_COUNT 4

// Number of led on board
#define LED_ENABLE 1
#define LED_TVOC   0
#define LED_PM     2
#define LED_CO2    3

#define SET_GREEN_LIGHT(NUM_LED)     ws2812_pixel_rgb_to_buf_dma(0, 60, 0, NUM_LED)
#define SET_ORANGE_LIGHT(NUM_LED)    ws2812_pixel_rgb_to_buf_dma(50, 30, 0, NUM_LED)
#define SET_RED_LIGHT(NUM_LED)       ws2812_pixel_rgb_to_buf_dma(60, 0, 0, NUM_LED)
#define SET_TURQUOISE_LIGHT(NUM_LED) ws2812_pixel_rgb_to_buf_dma(00, 30, 30, NUM_LED)
#define SET_WHITE_LIGHT(NUM_LED)     ws2812_pixel_rgb_to_buf_dma(25, 25, 25, NUM_LED)

#define ARRAY_LEN DELAY_LEN + LED_COUNT*24

#define HIGH (CMU_ClockFreqGet(cmuClock_TIMER1) / PWM_FREQ)*0.72
#define LOW  (CMU_ClockFreqGet(cmuClock_TIMER1) / PWM_FREQ)*0.28

#define BitIsSet(reg, bit) ((reg & (1<<bit)) != 0)

void initLdma(void);
void init_WS2812(void);
void change_color_WS2812(void);
void ws2812_pixel_rgb_to_buf_dma(uint8_t Rpixel , uint8_t Gpixel, uint8_t Bpixel, uint16_t posX);

#endif /* WS2812_WS2812_H_ */
