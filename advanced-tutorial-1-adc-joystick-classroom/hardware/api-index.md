# API index: read the contract before choosing an order

Inspect `Drivers/STM32F1xx_HAL_Driver/Inc/stm32f1xx_hal_adc.h`,
`stm32f1xx_hal_adc_ex.h` and the corresponding source files. The list below is
alphabetical, not an implementation sequence.

| API | Purpose | What to investigate |
| --- | --- | --- |
| `HAL_ADCEx_Calibration_Start` | F103 electrical ADC calibration | When to run it; what it cannot calibrate |
| `HAL_ADC_GetValue` | Read the conversion data register | How you know the result is ready |
| `HAL_ADC_PollForConversion` | Wait with a timeout and return a status | What to do when it times out |
| `HAL_ADC_Start` | Start conversion without DMA | Which IOC trigger/continuous settings apply |
| `HAL_ADC_Start_DMA` | Start transfers to a supplied buffer | Pointer type, transfer width, length and lifetime |
| `HAL_ADC_Stop` | Stop/disable a polling acquisition | Cleanup when a conversion fails |

The global generated handle is `hadc1`, declared in `adc.h`. HAL status values
are `HAL_OK`, `HAL_ERROR`, `HAL_BUSY` and `HAL_TIMEOUT`. An ADC result of zero
is a valid code and must not be used as the error indication.

In `lab_tasks.h`, false means the task is unfinished. For HAL operations, return
true once implemented and put the operation's actual result in `*status`.
The display reports this status; it will not turn an error into a zero reading.

DMA operates on transfers, whose width is configured separately. In this lab
four halfword transfers fill four `uint16_t` elements. The HAL's buffer parameter
type is `uint32_t *`; that type does not make the requested length a byte count.
The display supplies aligned storage that remains allocated after your function
returns. Do not replace it with a local automatic array.

Use the function parameters for voltage and normalization. For the F103's
12-bit result, distinguish the number of possible codes from the largest code.
TFT formatting uses integers; return millivolts and let the supplied display
format the value.
