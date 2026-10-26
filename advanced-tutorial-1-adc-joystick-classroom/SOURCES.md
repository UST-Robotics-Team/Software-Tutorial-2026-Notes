# Sources and validation boundary

- The board, display, startup and build scaffolding derive from the team's
  previously released Controller project. Their original notices remain.
- Peripheral initialization was generated with STM32CubeMX 6.18.1 and
  STM32Cube FW_F1 V1.8.7 for a conservative STM32F103C8 profile.
- The HAL API and register implementation can be read in the bundled
  `projects/Controller-ADC-Lab/Drivers/STM32F1xx_HAL_Driver` source/headers.
- The official STM32F103x8/xB datasheet and ST RM0008 provide the electrical
  characteristics, ADC regular sequence and DMA register descriptions.
- Lab tasks, worksheets and diagrams are the new ungraded classroom material.
  The earlier reference code remains available to both teaching groups.

Software checks cover CubeMX generation, Debug compilation and simulated
HAL/display behavior. They do not establish actual board wiring, voltage
reference accuracy, mechanical calibration or a physical acceptance test.
