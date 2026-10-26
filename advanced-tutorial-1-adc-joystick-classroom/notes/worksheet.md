# ADC / Joystick Lab: prediction and evidence

Use the same worksheet in either teaching group. This activity is ungraded.
Keep predictions as written; add corrections in the observation column.

## A. One input

| Question or test | Prediction before running | Observation | Explanation / correction |
| --- | --- | --- | --- |
| Number of codes and maximum code | | | |
| Near zero / half reference / near reference | | | |
| One axis at both stops and release | | | |
| Software reference: 3300 -> 3000 mV, same physical position | | | |
| Valid raw zero versus a conversion timeout | | | |

Draw your polling success path and timeout path here. Identify when you can
trust the result and what happens to an acquisition after a timeout.

Record the HAL source locations of the conversion-ready flag check and the
data-register read. Explain their roles using the reference manual.

## B. Four inputs

| Physical axis | MCU input / channel | Sequence rank | Buffer index | How verified |
| --- | --- | --- | --- | --- |
| J1 X | | | | |
| J1 Y | | | | |
| J2 X | | | | |
| J2 Y | | | | |

| Change only this setting | Prediction | Observation | Why |
| --- | --- | --- | --- |
| Exchange two ranks | | | |
| Circular -> Normal DMA | | | |
| Restore working scan and Circular DMA | | | |

Explain buffer lifetime, halfword transfers and what the length argument counts.
Explain whether a DMA transfer itself needs an interrupt callback.
Record the sequence-register update you found and draw the buffer's byte offsets.

## C. Calibration and response

| Axis | Minimum | Ten released raw samples | Chosen centre | Maximum | Idle variation |
| --- | --- | --- | --- | --- | --- |
| J1 X | | | | | |
| J1 Y | | | | | |
| J2 X | | | | | |
| J2 Y | | | | | |

Sketch your intended raw-to-position relationship, including both deadband
edges. Write the two scale factors you derived and explain their denominators.

| Input case | Prediction | Observed result | Reason |
| --- | --- | --- | --- |
| Minimum / centre / maximum | | | |
| Each deadband edge and just outside | | | |
| Intermediate position, each side | | | |
| Raw outside calibrated endpoints | | | |
| Invalid endpoint/centre combination | | | |
| One calibration value changed by a partner | | | |

| Deadband | Idle behavior | Small-movement response | Keep / reject, and why |
| --- | --- | --- | --- |
| 60 | | | |
| 120 | | | |

Write one misconception you corrected and one question you still have.
