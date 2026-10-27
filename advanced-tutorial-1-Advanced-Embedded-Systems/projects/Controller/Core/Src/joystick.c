#include "joystick.h"
#include "main.h"
/* Add adc.h after enabling ADC1 and generating code in CW1A. */

bool Joystick_Start(void)
{
    /* TODO CW1A: perform F103 ADC self-calibration once and report success. */
    return false;
}

bool Joystick_ReadChannel(uint32_t channel, uint16_t *raw)
{
    /* TODO CW1A: obtain one completed conversion from the requested channel.
       Use polling with a finite timeout. Report failure separately from raw 0.
       Keep the output unchanged unless the complete operation succeeds. */
    (void)channel;
    (void)raw;
    return false;
}
