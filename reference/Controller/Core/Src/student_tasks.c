#include "student_tasks.h"
#include "joystick.h"
#include "joystick_normalization.h"
bool CW1_ReadJoystick(uint16_t values[4])
{
    Joystick_Read(values);
    return true;
}
float CW1_NormalizeAxis(uint16_t raw, uint16_t minimum, uint16_t centre,
                       uint16_t maximum, uint16_t deadband)
{
    return Joystick_NormalizeAxis(raw, minimum, centre, maximum, deadband);
}
