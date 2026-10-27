#ifndef ULTRASONIC_GPIO_H
#define ULTRASONIC_GPIO_H
#include "sensors.h"
/* GPIO and timer initialization belong to CubeMX. Student functions operate
   the generated hardware: PA0 Trig, PA1 Echo, TIM2 at one count per us. */
HAL_StatusTypeDef Ultrasonic_Start(void);
uint32_t Ultrasonic_Micros(void);
void Ultrasonic_Trigger(bool high);
bool Ultrasonic_Echo(void);
uint16_t Ultrasonic_TrigPin(void);
uint16_t Ultrasonic_EchoPin(void);
HAL_StatusTypeDef Ultrasonic_DelayUs(uint32_t duration);
HAL_StatusTypeDef Ultrasonic_WaitEdges(uint32_t transaction_start,
                                      uint32_t *rise, uint32_t *fall);
/* Supplied output clearing, diagnostics and plausibility guards. */
HAL_StatusTypeDef Ultrasonic_Begin(void);
HAL_StatusTypeDef Ultrasonic_Complete(uint32_t width_us, uint32_t measured_mm,
                                     uint32_t *distance_mm);
enum { US_OK, US_ECHO_BUSY, US_NO_RISE, US_NO_FALL, US_TOO_SHORT, US_BAD_RESULT, US_TIMER_ERROR, US_EDGE_TASK };
enum { US_WIRING_UNDETECTED, US_WIRING_BOARD, US_WIRING_CROSSED };
typedef struct {
    uint32_t attempts, successes, pulse_us, distance_mm, reason, echo_idle, wiring;
} Ultrasonic_Diagnostics;
extern volatile Ultrasonic_Diagnostics g_ultrasonic;
#endif
