[Contents](README.md) | [Previous: optional TOF module](06-optional-tof.md)

# Troubleshooting

Start with the board, project and wires before changing the arithmetic.

| Symptom | Ordered checks |
| --- | --- |
| CMake cannot find `arm-none-eabi-gcc` | Select the complete STM32/Arm toolchain; check PATH; reconfigure using a fresh build directory after changing compiler |
| Missing `stdint.h` or `nano.specs` | The compiler installation lacks the embedded C library; use a complete Arm GNU toolchain |
| Build succeeds but screen is blank | Correct MCU/project? Correct ELF flashed? Continued past debugger startup? Power and TFT variant/orientation? |
| Title disappears or text blinks | Redraw the complete frame before each TFT commit; the supplied driver clears the next writable frame. Use the corrected TutorialApp and its single commit; avoid flushing empty frames between sensor updates |
| Controller says `ADC NOT READY` / `CHECK CW1A SETUP` | Enable ADC1 in IOC, generate, then implement `Joystick_Start()` calibration/status; build and reflash |
| Calibration returns HAL_OK but startup is reported as failed | `HAL_OK` equals zero; compare the status with HAL_OK so success becomes Boolean true, rather than returning the status directly |
| Controller says `READ NOT READY` / `CHECK CW1A READ` | Complete the polling function and `CW1_ReadJoystick()`; check channel selection, HAL statuses, finite wait and stop/cleanup |
| ADC IN0/IN1/IN2/IN3 checkbox is pink/unavailable | Click the matching PA pin on the chip diagram and select ADC1_INx to replace its passive GPIO_Analog assignment; see the ADC screenshots |
| Missing `adc.h` in Controller | Generate ADC1 after enabling it; the untouched starter intentionally has no ADC header |
| Generated files or edits appear to have no effect | Confirm CubeMX and VS Code use the same working copy and the flashed ELF comes from that folder; screenshots may show a lecturer's temporary copy |
| Other axes/PUSH show dashes | `JOYSTICK_AXIS_COUNT=1U` intentionally measures only J1X; enable the other inputs and implement their reads before selecting 4U |
| `BAD RAW VALUE` / `CHECK CW1B MATH` | Check the ADC result is a 12-bit code and your normalization returns a finite value in [-1,1] |
| IR NOT READY / CHECK CW2 GPIO | Set/check PA2 passive input, keep USART2 disabled, and implement IR_ReadDigital |
| A0:---- with D0 changing / ADC TODO/ERROR | Configure ADC1 IN3, generate, add adc.h and implement IR_Read polling/status checks |
| SURFACE: ? | Complete CW2_ProcessIR with a measured A0 software threshold |
| US NOT READY / CHECK CW3 TIMER | Configure/generate TIM2 and PA0/PA1, add tim.h and implement Ultrasonic_Start |
| TIMER NOT RUNNING | Check generated clock/timer setup, successful start, counter access and your bounded microsecond delay |
| EDGE TASK TODO | Implement Ultrasonic_WaitEdges with both edges and one shared timeout |
| Ultrasonic stays at DO CW3 TODO | Implement the complete transaction using your timer/GPIO/edge functions, then save/build/flash |
| SHORT PULSE / BAD CALCULATION after enabling CW3 | Check unsigned fall-minus-rise, units, round-trip factor and rounding; the supplied Complete helper rejects unusable results |
| Edits do not change the screen | Save, rebuild and flash the new ELF from the correct project; a running board still has the old program until reflashed |
| Joystick values all zero | Did calibration and each conversion succeed? Correct input/channel, analog pin mode, and completed result? Zero is valid data; distinguish it from a false return |
| Wrong joystick axis changes | Compare the selected ADC channel and output slot; every polling conversion uses Rank 1. Change one channel at a time |
| Idle direction flickers | Record actual centre for each axis; select a suitable deadband; check power/noise |
| Raw axes move but normalized values stay zero | Finish `CW1_NormalizeAxis()`; the normalization stub returns zero |
| Controller title is still CW1 NORMALIZED during A | Expected: the title is fixed. Use ADC NOT READY, READ NOT READY and RAW VALID to identify progress; RAW VALID is not proof B/C is complete |
| Four-channel mode seems to need four ranks | This exercise keeps one regular conversion, Rank 1 and scan/continuous disabled; the C caller requests channels 0/1/2/3 sequentially |
| Normalized output has no intermediate values | Check that division uses floating-point operands before truncation; converting an integer result to float afterwards cannot recover its fractional part |
| Y direction is reversed | Adjust the corresponding `J1_Y_DIRECTION` or `J2_Y_DIRECTION`; the tested board uses -1 for both; do not also reverse in the task |
| Full travel gives PUSH below 1 | Defaults are ADC endpoints 0 and 4095; measure mechanical endpoints and update each MIN/MAX |
| PUSH differs from one axis | It combines X/Y as `min(1, sqrt(x*x+y*y))`; compare both signed axes |
| Both deadbands 60 and 120 give stable zero at rest | This is valid; hold calibration fixed and also compare how much small movement is ignored before the output responds |
| IR A0 always zero/full scale | A0 must go to UART2 R/PA3, ADC1 Channel 3; confirm module 3.3 V, common ground, analog mode and completed conversion |
| IR shows only digital 0/1 while using A0 | A0 on I2C2 C/D is not an ADC connection; use UART2 R. D0 belongs on UART2 T/PA2 |
| IR D0 stuck | Confirm USART2 remains disabled; PA2 must stay GPIO input while the module is attached |
| IR cannot separate black/white | Keep height/angle fixed, choose contrasting surfaces and repeat samples; verify polarity before setting the threshold |
| Turning IR potentiometer does not change A0 | Expected from the supplied schematic: it changes D0's comparator reference |
| TOF address ACKs but distance is wrong | Confirm VL53L1X model, correct register addresses/byte order, driver setup and range validity; ACK alone does not validate a measurement |
| Distance is missing or invalid | For ultrasonic, inspect the echo failure reason; for TOF, inspect HAL status and range validity. Change target position/surface and recover before accepting data |
| TOF fails initialization | Supply and SHUT high? SDA/SCL and pull-ups? HAL address `0x52`? Correct VL53L1X rather than VL53L0X? |
| TOF ACKs but reports invalid range | Read range status, target/light conditions and near-range limits; ACK is not a quality check |
| TOF stops after one result | Check measurement-event clearing and ready polling; distinguish sensor event handling from MCU external interrupts |
| Values stay visible after failure | Clear or replace the display; track status/validity instead of treating the last sample as current |
| A number prints as the letter `u` or `x` | `tft_prints()` uses the project's own mini printf, which has no `l` length modifier: `%lu`/`%04lx` print a literal `u`/`x`. Use `%u`/`%04x` with a 32-bit value; the compiler cannot warn because the `printf` attribute allows them |
| IR/US WIRING CHECK | A wiring flag was deliberately disabled; ask the lecturer to confirm connections. Both classroom flags are enabled in the supplied starter |
| CW3 `ECHO BUSY HIGH` or `NO ECHO RISE` | Confirm GPIO module mode, Trig to PA0, Echo to PA1, common ground and supply. Roles are fixed; the firmware does not swap them |
| TOF bus does not answer | Check the new physical SDA/SCL map, compatible pull-ups and supply; do not reuse old PB10_1 numbering as proof |


Student acquisition functions must implement the stated bounded waits. The
provided sensor initialization is bounded; no general stuck-bus recovery is supplied. If a bus remains busy, power off and ask a lecturer to inspect
the wiring; do not add an endless retry loop.

A logic analyser is useful for verifying START/address/ACK/data/STOP if one is
available. Hardware measurements and the student's live demonstration are still
needed even when the firmware builds and host tests pass.
