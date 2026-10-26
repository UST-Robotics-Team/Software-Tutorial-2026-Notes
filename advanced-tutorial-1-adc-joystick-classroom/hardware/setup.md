# Open, build and run

Prepare STM32CubeMX 6.18.1 and STM32Cube FW_F1 V1.8.7 before class. Install the
firmware through CubeMX's firmware package manager. The supplied HAL files let
the starter build, but Generate Code also needs the firmware package installed
on your computer. Check this before the B configuration experiment.

1. Connect ST-Link to the Blue Pill Controller and provide normal board power.
2. Open `projects/Controller-ADC-Lab`, rather than the repository or Mainboard.
3. Trust this folder if VS Code opens it in Restricted Mode. Use the installed
   ST STM32 extension to set up the existing CMake project: STM32F103C8T6,
   Cortex-M3 and GCC.
4. Select **Debug**, then **CMake: Build**. The untouched starter must build.
5. In **Run and Debug**, create/select the ST-Link GDB Server configuration.
   Check the ELF is `build/Debug/Controller_ADC_Lab.elf`. Press F5 to program,
   then Continue if paused at `main()`.

Expect `ADC LAB A`, `PREPARE ADC TODO` and a changing RUN count. This confirms
startup only; it does not demonstrate ADC acquisition. There is no student demo
mode and no hidden answer implementation.

After edits: **save -> build Debug -> F5 -> Continue**.

## Starter IOC

Open `Controller_ADC_Lab.ioc`. Keep the supplied TFT, buttons, SWD and clock
settings. PA0-PA3 are wired to the assembled joystick inputs. The starter
converts only Channel 0 at Rank 1, with Continuous conversion disabled. Its
ADC DMA route is prepared as Normal mode, unused by experiment A. Do not assume
that an analog pin automatically belongs to the regular conversion sequence.

The F103 ADC is 12-bit. Keep its clock at 12 MHz (72 MHz APB2 divided by 6)
and the prepared 71.5-cycle sampling setting. The software reference assumption
starts at 3300 mV; it is not a measured reference voltage.

## Changes for B and C

Inspect the IOC and the generated `adc.c`, not just the displayed numbers:

- Set the regular sequence to four conversions, Channels 0-3, with distinct ranks.
- Enable scan and continuous conversion. Retain the prepared sampling duration.
- Check ADC1 -> DMA1 Channel1: peripheral-to-memory, halfword on both sides,
  memory increment, no peripheral increment, Circular mode. Leave its NVIC
  interrupt disabled for this monitor; a DMA transfer does not require a callback.
- Generate Code, then check `MX_ADC1_Init()` and the ADC DMA setup in `adc.c`.
- Set `LAB_STAGE` to `LAB_DMA` in `lab_config.h`, build and program the same project.
- For C, keep the working four-channel configuration and select `LAB_CALIBRATION`.

The app checks a missing DMA handle and an unsafe transfer width before calling
your start function. It does not correct sequence, increment or transfer mode.
`SCAN` reports the actual configured conversion count; `DMA:C/N` reports the mode.

When comparing Normal and Circular operation, generate/build/program for each
setting and move a stick after startup. Keep all other settings unchanged.
Restore Circular mode before C. Record which behavior changed and why.

The existing complete Controller reference and this lab use different folders
and ELF names. Check the active VS Code window before each programming action.
