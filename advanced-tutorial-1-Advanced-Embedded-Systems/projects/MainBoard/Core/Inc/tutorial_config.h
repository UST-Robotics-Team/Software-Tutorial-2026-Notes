#ifndef TUTORIAL_CONFIG_H
#define TUTORIAL_CONFIG_H
/* Quang Mainboard, wiring functionally confirmed on 2026-10-26.
   IR uses UART2 V/T/R/G: VCC/D0/A0/GND, V reported as 3.3 V.
   A0 = PA3 ADC1 Channel 3; D0 = PA2 input; USART2 stays disabled.
   Ultrasonic uses V/PA0/PA1/G: VCC/Trig/Echo/GND, V reported as 3.3 V.
   TOF wiring/pull-ups on the new board are still pending; keep its flag at 0. */
#define MAINBOARD_PROFILE_QUANG 1
#ifndef IR_WIRING_CONFIRMED
#define IR_WIRING_CONFIRMED 1
#endif
#ifndef ULTRASONIC_WIRING_CONFIRMED
#define ULTRASONIC_WIRING_CONFIRMED 1
#endif
#ifndef TOF_WIRING_CONFIRMED
#define TOF_WIRING_CONFIRMED 0
#endif
#define IR_A0_GPIO_Port GPIOA
#define IR_A0_Pin GPIO_PIN_3
#define IR_A0_ADC_CHANNEL ADC_CHANNEL_3
#define IR_D0_GPIO_Port GPIOA
#define IR_D0_Pin GPIO_PIN_2
#define TOF_ADDRESS_HAL 0x52U
#define SENSOR_IO_TIMEOUT_MS 25U
/* Fixed GPIO roles, no automatic swapping; TIM2 supplies a 1 us timebase. */
#define ULTRASONIC_GPIO_Port GPIOA
#define ULTRASONIC_TRIG_Pin GPIO_PIN_0
#define ULTRASONIC_ECHO_Pin GPIO_PIN_1
#define ULTRASONIC_SETTLE_US 2U
#define ULTRASONIC_TRIGGER_US 20U        /* datasheet asks for more than 10 us */
#define ULTRASONIC_TIMEOUT_US 250000U    /* per transaction, both edges */
#define ULTRASONIC_MIN_PULSE_US 100U     /* shorter than any in-range echo */
#define ULTRASONIC_MM_NUMERATOR 343U     /* 343 m/s at about 20 C */
#define ULTRASONIC_MM_DENOMINATOR 2000U  /* mm per us, and the round trip */
/* Change after recording black/white samples at the same sensor height. */
#define IR_THRESHOLD 2000U
#define IR_BLACK_IS_HIGH 1
#define OBSTACLE_NEAR_MM 200U
#define SENSOR_UPDATE_MS 300U
#endif
