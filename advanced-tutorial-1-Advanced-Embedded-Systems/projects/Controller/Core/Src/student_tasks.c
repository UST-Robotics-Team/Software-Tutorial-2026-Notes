#include "student_tasks.h"
#include "joystick.h"
bool CW1_ReadJoystick(uint16_t values[4])
{
    /* TODO CW1A: call Joystick_Read(values), then return true. */
    (void)values;
    return false;
}
float CW1_NormalizeAxis(uint16_t raw, uint16_t minimum, uint16_t centre,
                       uint16_t maximum, uint16_t deadband)
{
    /* TODO CW1B: implement the calculation here; no axis-normalization helper
       is supplied in the student project.
       1. Use signed arithmetic for centre-minimum, maximum-centre and raw-centre.
       2. Return zero if either centre-to-endpoint span is <= deadband.
       3. Return zero inside the inclusive centre +/- deadband region.
       4. Outside it, remove the deadband and scale each side separately.
          Use floating-point division.
       5. Clamp the result to [-1,1].
       The UI applies Y polarity afterwards and calculates whole-stick PUSH.
       CW1C: record four-axis calibration and compare deadbands in joystick_config.h. */
    (void)raw; (void)minimum; (void)centre; (void)maximum; (void)deadband;
    return 0.0f;
}
