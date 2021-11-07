#ifndef BUZZER_BUZZER_H_
#define BUZZER_BUZZER_H_

// Push-buttons are active-low
#define BUTTON_PRESSED_SOUND_ON (1)

#define BUTTON_SOUND_PORT gpioPortC
#define BUTTON_SOUND_PIN  9

#define BUZZER_PORT gpioPortC
#define BUZZER_PIN  8

#define BUZZER_DEFAULT_FREQ        2093 //C7 - 4th octave "Do"
#define BUZZER_DEFAULT_DELAY       400  //400ms
#define BUZZER_DEFAULT_VOLUME_MAX  10
#define BUZZER_DEFAULT_VOLUME_MUTE 0

void init_buzzer(void);
void buzzer_dangerous_sound(void);

#endif /* BUZZER_BUZZER_H_ */
