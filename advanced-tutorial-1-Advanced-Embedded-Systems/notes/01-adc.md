[Contents](README.md) | [Previous: Terms](00-getting-started.md) | [Next: CW1](02-joystick.md)

# 1. ADC — Analog-to-Digital Converter

An ADC converts a voltage into an integer. A GPIO (**General-Purpose
Input/Output**) read gives only HIGH/LOW, so it cannot describe all joystick
positions. Your application assigns physical meaning to the ADC code.

```text
Position → potentiometer voltage → ADC code → position calculation
```

## 1. Sampling, resolution and voltage

**Sampling** chooses when to measure. **Quantization** assigns the measured
voltage to a numerical step.

![Simplified quantization steps and the 12-bit range](images/adc-quantization.png)

A 12-bit ADC has `2^12 = 4096` codes: **0–4095**. Nearby voltages can share
a code. More frequent samples improve time coverage; more bits give finer
voltage steps. Neither fixes reference error or noise.

With an assumed 3.3 V reference:

```text
1.65 V → code near 2048
estimated voltage = raw / 4095 × reference
raw 1024 → 1024 / 4095 × 3.3 ≈ 0.825 V
ideal step ≈ 3.3 / 4096 = 0.000806 V
```

4096 counts the steps; 4095 is the maximum code. Endpoint-scaled voltage is an
estimate, not an exact ADC error model. For integer millivolts:

```c
uint32_t millivolts = (uint32_t)raw * 3300U / 4095U;
```

Multiply before dividing; integer `raw / 4095` is usually zero. The cast makes
the product 32-bit. The 3300 mV reference is assumed, not measured.

**Predict:** raw 3072 corresponds to about **2.476 V**, roughly three quarters
of the voltage range.

## 2. One conversion: polling

**Polling** means the CPU (**Central Processing Unit**) checks completion while
waiting. HAL (**Hardware Abstraction Layer**) provides these operations:

| Step | HAL call | Purpose |
| --- | --- | --- |
| Start | `HAL_ADC_Start()` | Request conversion |
| Wait | `HAL_ADC_PollForConversion()` | Wait for completion with a timeout |
| Read | `HAL_ADC_GetValue()` | Obtain the completed code |
| Stop | `HAL_ADC_Stop()` | Finish the operation |

The supplied `IR_Read()` checks this sequence's status. An error is not a
measurement of zero volts. Polling is simple, but occupies the CPU while waiting.

## 3. Four axes: scan and DMA

**DMA (Direct Memory Access)** moves ADC results into RAM (**Random Access
Memory**) without the CPU copying every result.

| Setting | Meaning |
| --- | --- |
| Channel | Which analog input to measure |
| Rank | Position in the conversion sequence |
| Continuous conversion | Repeat conversions after starting |
| Circular DMA | Repeatedly fill the same memory buffer |

![Scan order and the circular DMA buffer](images/joystick-dma-flow.png)

```text
Rank 1 → values[0]   Rank 2 → values[1]
Rank 3 → values[2]   Rank 4 → values[3]   then repeat
```

The starter starts acquisition once; `Joystick_Read(values)` copies the latest
four readings. DMA moves data; it does not interpret it or improve accuracy.
Polling, interrupts and DMA are acquisition/transfer methods, not sensor protocols.

<details>
<summary>Buffer and sampling details</summary>

The ongoing DMA buffer must remain allocated and uses 16-bit samples.
`volatile` helps CPU reads observe externally updated memory; it does not make
four sequential samples simultaneous or a four-value copy atomic. This monitor
uses each axis independently.

Sampling time lets the ADC input circuit settle. The shortest setting is not
always suitable; use the prepared configuration.

</details>

## 4. Calibration: correct the right part

| Calibration | Establishes/corrects | Does not establish |
| --- | --- | --- |
| ADC self-calibration | Internal converter characteristics | Sensor endpoints |
| Voltage/reference calibration | Code-to-voltage relationship | Joystick centre |
| Sensor/application calibration | Joystick MIN/CENTRE/MAX or IR sample ranges | ADC internal electrical errors |

On the **STM32F103 Controller**, `Joystick_Start()` checks
`HAL_ADCEx_Calibration_Start(&hadc1)` before starting DMA. Run it at startup,
not for every sample. The F405 project does not provide this same F1 API.

Self-calibration does not make the reference exactly 3.3 V or the released
joystick exactly 2048. Measure the reference or mechanical endpoints when those
are the errors you need to correct.

Before CW1, explain why **half the voltage range need not equal half the
joystick's usable travel**. See [IOC settings](../hardware/ioc-guide.md) and
[setup](../hardware/classwork-setup.md). Digital 5 V tolerance does not imply
that an ADC input can measure 5 V.

Reference: [ST AN2834](https://www.st.com/resource/en/application_note/an2834-how-to-optimize-the-adc-accuracy-in-the-stm32-mcus-stmicroelectronics.pdf).
