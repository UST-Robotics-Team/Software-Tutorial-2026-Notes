# CW3: Configuration and Code Ownership

[Lesson](../../notes/04-ultrasonic.md) | [Setup](../../hardware/classwork-setup.md)

| Part | Your work |
| --- | --- |
| IOC | PA0 output LOW, PA1 input, TIM2 internal clock / PSC 83 / ARR 0xFFFFFFFF |
| `ultrasonic_gpio_port.c` | Start TIM2 once, read its counter, write Trig and read Echo |
| `ultrasonic.c` | Implement microsecond delay and shared-deadline edge capture |
| `student_tasks.c` | Assemble Begin/trigger/wait/subtract/convert/Complete |

The supplied Begin/Complete functions clear outputs and maintain diagnostics and
plausibility checks. They do not capture edges or supply the distance formula.
The app supplies the TFT/error display and NEAR label from a valid distance.

Initialize peripherals only by IOC generation. `Ultrasonic_Start()` operates the
already initialized timer with HAL; it must not configure GPIO/clocks/registers.
Keep configuration in IOC; application files operate the generated hardware.

Both edge waits share the deadline measured from the end of Trig. Check timeout
before accepting the edge, including the final iteration. Also use a finite
millisecond watchdog if the microsecond counter stops. Set the matching reason
for no rise/no fall. Trig must return LOW on every exit path.

`CW3_MeasureUltrasonic()` returns false while unfinished. Once complete, true
means it produced an outcome, including error; `*status` separately reports
HAL_OK/HAL_ERROR/HAL_TIMEOUT. Publish no stale distance on failure.

The starter first shows US NOT READY / CHECK CW3 TIMER. After the timer start
succeeds, an unfinished transaction shows DO CW3 TODO. An unfinished edge
function reports EDGE TASK TODO if called by a completed transaction skeleton.
A non-OK delay reports TIMER NOT RUNNING. None runs a reference measurement.

Show the IOC clock calculation, your pulse and waits, a distance derivation,
three ruler comparisons and timeout/recovery. Keep IR working in the same program.
