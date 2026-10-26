# CW3: What You Fill In

[CW3 lesson](../../notes/04-ultrasonic.md) | [Setup](../../hardware/classwork-setup.md)

Edit `Core/Src/student_tasks.c`, inside `CW3_MeasureUltrasonic()`.

| Part | Supplied or student? |
| --- | --- |
| GPIO PA0/PA1 and TIM2 1 MHz setup | Supplied |
| Idle check, output clearing and 2 us settling | Supplied: `Ultrasonic_Begin()` |
| 20 us trigger pulse | **Student TODO A** |
| Shared-deadline rising/falling edge capture | Supplied: `Ultrasonic_WaitEdges()` |
| Unsigned falling minus rising timestamp | **Student TODO B** |
| Sound-speed, round-trip conversion and rounding | **Student TODO C** |
| Minimum-width/result checks, diagnostics and final status | Supplied: `Ultrasonic_Complete()` |
| Error display and a single full-frame TFT commit | Supplied app |

Keep the includes, signature and prepared status guards. When helpers fail, the
provided early returns finish that attempt; do not compute a distance from
missing timestamps. `true` means the task supplied an outcome, including error.
It is separate from `HAL_OK`, which equals zero. You do not write those guards.

Leave the top `return false` while filling A/B/C, then remove it and rebuild/flash.
`DO CW3 TODO` means the task is unfinished. It does not trigger a measurement
or run a reference implementation. After completing the TODOs and removing
the early return, the same screen displays your distance or a measurement error.
The complete lecturer solution is excluded from the student archive.

Required: show your trigger sequence, derive one pulse-to-mm calculation, compare
three ruler positions, show timeout/recovery, and keep IR updating on the same
board. Extensions: display cm, add hysteresis, or implement the bounded edge waits.
