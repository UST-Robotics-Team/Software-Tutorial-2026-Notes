#ifndef ULTRASONIC_GPIO_H
#define ULTRASONIC_GPIO_H
#include "sensors.h"
/* RCWL-9610 / HC-SR04-compatible GPIO test on fixed PA0/PA1 roles.
   Trig PA0 is push-pull output, idle low. Echo PA1 is a digital input with
   no internal pull. TIM2 runs at 1 MHz. There is no startup role probe.
   US_WIRING_BOARD means a valid capture on the configured pair; CROSSED is
   retained for API compatibility and is unused by this fixed port. */
HAL_StatusTypeDef Ultrasonic_GPIO_Init(void);
uint32_t Ultrasonic_Micros(void);
void Ultrasonic_Trigger(bool high);
bool Ultrasonic_Echo(void);
uint16_t Ultrasonic_TrigPin(void);
uint16_t Ultrasonic_EchoPin(void);
/* Supplied transaction helpers. Students keep the status guards in the task
   template and fill only trigger timing, pulse subtraction and conversion. */
void Ultrasonic_DelayUs(uint32_t duration);
HAL_StatusTypeDef Ultrasonic_Begin(void);
HAL_StatusTypeDef Ultrasonic_WaitEdges(uint32_t transaction_start,
                                      uint32_t *rise, uint32_t *fall);
HAL_StatusTypeDef Ultrasonic_Complete(uint32_t width_us, uint32_t measured_mm,
                                     uint32_t *distance_mm);
enum { US_OK, US_ECHO_BUSY, US_NO_RISE, US_NO_FALL, US_TOO_SHORT, US_BAD_RESULT };
enum { US_WIRING_UNDETECTED, US_WIRING_BOARD, US_WIRING_CROSSED };
typedef struct {
    uint32_t attempts, successes, pulse_us, distance_mm, reason, echo_idle, wiring;
} Ultrasonic_Diagnostics;
extern volatile Ultrasonic_Diagnostics g_ultrasonic;
#endif
