# Sources and Licences

## Project sources

- Course projects and TFT code originate from the
  [HKUST Robotics Team tutorial repository](https://github.com/UST-Robotics-Team/Software-Tutorial-2026-Notes).
  The Controller builds on the Tutorial 2 skeleton; the Mainboard uses Quang
  Ngo's [Tutorial 3 skeleton](https://github.com/UST-Robotics-Team/Software-Tutorial-2026-Notes/blob/38d914ab58b1f5ab9ced345eacfdaa160e798f16/tutorial-3-advanced-io/Tutorial3_Skeleton.zip).
- The Controller's STM32F103xB startup/device support comes from
  [ST CMSIS device F1](https://github.com/STMicroelectronics/cmsis-device-f1/tree/c8e9a4a4f16b6d2cb2a2083cbe5161025280fb22).
- Added STM32F4 peripheral files match the supplied
  [HAL v1.8.5](https://github.com/STMicroelectronics/stm32f4xx-hal-driver/tree/v1.8.5).
- The VL53L1X C subset adapts the ST ULD-based code distributed with
  [SparkFun's library](https://github.com/sparkfun/SparkFun_VL53L1X_Arduino_Library/tree/e88f55d6d82a4a8c519ec90a2660e6ec799b4579/src/st_src).
  It includes a course-specific STM32 HAL platform layer and bounded waits.

Original authorship and component licence notices are retained in the starter.
The VL53L1X notice is in `projects/MainBoard/Drivers/VL53L1X/LICENSE-ST.txt`;
HAL/CMSIS licences remain with their components. The course materials do not
grant a new licence for upstream content.

## Further reading

The explanations build on the earlier course's ADC, interrupt/DMA and I2C/TOF
materials. The worked examples follow this starter's actual scan order,
normalization, register definitions and driver behavior.

- ADC: [ST AN2834](https://www.st.com/resource/en/application_note/an2834-how-to-optimize-the-adc-accuracy-in-the-stm32-mcus-stmicroelectronics.pdf).
- IR: [Vishay TCRT5000 datasheet](https://www.vishay.com/docs/83760/tcrt5000.pdf).
- I2C: [NXP UM10204](https://www.nxp.com/docs/en/user-guide/UM10204.pdf).
- Ultrasonic: [RCWL-9610 manufacturer document, mirrored PDF](https://make.net.za/wp-content/datasheets/RCWL-9610%20Datasheet%20v1.0%20-%20Original.pdf).
- TOF: [ST VL53L1X datasheet](https://www.st.com/resource/en/datasheet/vl53l1x.pdf)
  and [ULD user manual](https://www.st.com/resource/en/user_manual/um2510-a-guide-to-using-the-vl53l1x-ultra-lite-driver-stmicroelectronics.pdf).

## Illustrations

Course diagrams illustrate signal flow and measurement concepts. Module photos
and pad diagrams are supplier reference images provided for the tutorial.
Match the actual module's labels before wiring. Concept diagrams and supplier
photos do not establish a Mainboard connector pinout.
