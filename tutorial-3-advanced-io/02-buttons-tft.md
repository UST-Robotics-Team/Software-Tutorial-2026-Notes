# 02 — Timer Setup (.ioc), Channel Startup & Button Demo

[Back to Index](README.md) · _~35 min hands-on_

---

## 1. STM32CubeMX (.ioc) Setup

Open `MainBoard.ioc` in STM32CubeIDE:

1. **Check the Clock Tree:**
   - **HCLK** = `168 MHz`.
   - **APB1 Timer Clocks** = **`84 MHz`**.
2. **Enable the PWM Channel:**
   - In the left menu, click **Timers** $\to$ **TIM4**.
   - Set **Clock Source** to **Internal Clock**.
   - Under **Channel 2**, select **PWM Generation CH2**.
3. **Check the Pin:**
   - In the chip diagram, confirm pin **`PB7`** turns green and is labelled **`TIM4_CH2`** (**AF2**).
4. **Configure Parameter Settings (bottom window):**

   | Parameter              | Value to Enter     |
   | ---------------------- | ------------------ |
   | Prescaler (PSC)        | **83**             |
   | Counter Mode           | Up                 |
   | Counter Period (ARR)   | **19999**          |
   | Auto-reload preload    | **Enable**         |
   | Mode (Channel 2)       | PWM mode 1         |
   | Pulse (CCR2)           | **1500** (neutral) |
   | Output compare preload | Enable             |
   | CH2 Polarity           | High               |

   > **Where do 83 and 19999 come from?** They are the two divisions from [01-pwm.md §2](01-pwm.md): divide the 84 MHz clock down to 1 µs per tick, then count 20 000 ticks per period. Multiply them back: $84 \times 20\,000 = 1\,680\,000$, and $84\,000\,000 / 1\,680\,000 = 50\,\text{Hz}$.
   > Because 1 tick = 1 µs, the **`CCR2` you type is literally the pulse width in µs**.

5. **Generate Code:**
   - Generate the code.

---

## 2. What CubeMX Generates by Default

Look at what CubeMX just generated for you:

- **`tim.h` / `tim.c`:** Declares the timer handle `TIM_HandleTypeDef htim4` and creates `MX_TIM4_Init()`.
- **`HAL_TIM_PWM_MspInit()`:** Automatically turns on the timer clock and sets pin `PB7` to alternate function mode.
- **`main.c`:** Calls `MX_TIM4_Init()` before the `while (1)` loop.

> ⚠️ **THE BIG GOTCHA (DO NOT MISS THIS):**  
> `MX_TIM4_Init()` **DOES NOT start the timer!** It only configures the registers.  
> Your pin `PB7` will output nothing until you explicitly call:
>
> ```c
> HAL_TIM_PWM_Start(&htim4, TIM_CHANNEL_2);
> ```

---

## 3. How to Control the Servo in Code

Once the timer is running, you change the pulse width using this HAL macro:

```c
__HAL_TIM_SET_COMPARE(&htim4, TIM_CHANNEL_2, pulse_in_us);
```

Since we set 1 tick = $1\,\mu\text{s}$, putting `1500` outputs a $1500\,\mu\text{s}$ pulse!

---

## 4. The `btn_read_rising_edge()` Helper Function

In `main.h`, buttons are read with `btn_read(BTN1)` (1 when pressed, 0 when released).

**Why raw read fails:**  
A `while (1)` loop runs thousands of times per second. If you write:

```c
if (btn_read(BTN1)) { pulse += 100; } /* BUG: Fires 10,000 times during a short tap! */
```

The servo will instantly slam into the limit.

**The Solution — Rising Edge Detection:**  
We only want to trigger **once** when the button is first pushed down ($0 \to 1$ transition):

```c
/* Put this in main.c inside USER CODE BEGIN 0 */
uint8_t btn_read_rising_edge(uint8_t current, uint8_t *prev, uint32_t *last_time)
{
  uint32_t now = HAL_GetTick();
  uint8_t edge = 0;

  /* If currently pressed AND previously released */
  if (current && !(*prev))
  {
    /* Ignore bounce if within 40 ms of last press */
    if (now - *last_time >= 40U)
    {
      edge = 1;
      *last_time = now;
    }
  }
  *prev = current;
  return edge;
}
```

---

## 5. Complete Code Demo: Button-Controlled Servo

Follow these 3 steps to put the code into `Core/Src/main.c`:

### Step 1: What to put in the FRONT (`USER CODE PV` and `USER CODE 0`)

```c
/* USER CODE BEGIN PV */
/* Safe pulse limits (Xin Hui servo: 500 to 2500 us) */
#define SERVO_PULSE_MIN   500U
#define SERVO_PULSE_MAX  2500U
#define SERVO_PULSE_MID  1500U
#define SERVO_STEP_US     100U   /* Amount to step per button click */

static uint32_t g_servo_pulse = SERVO_PULSE_MID;

/* Button edge-tracking variables */
static uint8_t  btn1_prev = 0, btn2_prev = 0;
static uint32_t btn1_time = 0, btn2_time = 0;
/* USER CODE END PV */

/* USER CODE BEGIN 0 */
void servo_set_pulse(uint32_t us)
{
  /* Clamp safely inside limits */
  if (us < SERVO_PULSE_MIN) us = SERVO_PULSE_MIN;
  if (us > SERVO_PULSE_MAX) us = SERVO_PULSE_MAX;
  g_servo_pulse = us;
  __HAL_TIM_SET_COMPARE(&htim4, TIM_CHANNEL_2, g_servo_pulse);
}

uint8_t btn_read_rising_edge(uint8_t current, uint8_t *prev, uint32_t *last_time)
{
  uint32_t now = HAL_GetTick();
  uint8_t edge = 0;
  if (current && !(*prev))
  {
    if (now - *last_time >= 40U)
    {
      edge = 1;
      *last_time = now;
    }
  }
  *prev = current;
  return edge;
}
/* USER CODE END 0 */
```

### Step 2: What to put BEFORE the loop (`USER CODE 2`)

```c
  /* USER CODE BEGIN 2 */
  /* 1. Initialize the TFT screen */
  tft_init(PIN_ON_TOP, BLACK, WHITE, CYAN, DARK_GREY);

  /* 2. Set servo to neutral (1500 us) */
  servo_set_pulse(SERVO_PULSE_MID);

  /* 3. CRITICAL: Start hardware PWM on TIM4 CH2 */
  HAL_TIM_PWM_Start(&htim4, TIM_CHANNEL_2);
  /* USER CODE END 2 */
```

### Step 3: What to put INSIDE `while (1)` (`USER CODE 3`)

```c
  /* USER CODE BEGIN WHILE */
  while (1)
  {
    /* USER CODE END WHILE */

    /* USER CODE BEGIN 3 */
     tft_prints(1, 1, "SERVO BUTTON DEMO");
     tft_prints(1, 3, "BTN1: CW (+100us)");
     tft_prints(1, 4, "BTN2: CCW (-100us)");
     tft_prints(1, 6, "Pulse:");

    /* 1. Read rising edges of BTN1 (PB1) and BTN2 (PA4) */
    uint8_t btn1_click = btn_read_rising_edge(btn_read(BTN1), &btn1_prev, &btn1_time);
    uint8_t btn2_click = btn_read_rising_edge(btn_read(BTN2), &btn2_prev, &btn2_time);

    /* 2. Pressing BTN1 goes one way (CW), BTN2 goes the other way (CCW) */
    if (btn1_click && !btn2_click)
    {
      servo_set_pulse(g_servo_pulse + SERVO_STEP_US);
    }
    else if (btn2_click && !btn1_click)
    {
      servo_set_pulse(g_servo_pulse - SERVO_STEP_US);
    }

    /* 3. Update the TFT Display */
    tft_printi(8, 6, (int32_t)g_servo_pulse);
    tft_prints(14, 6, "us ");
    tft_update(50);
  }
  /* USER CODE END 3 */
```

---

## 6. Wiring & Testing

Before powering on:

1. **Servo Signal Wire (Orange/White):** Connect to **`PB7`**.
2. **Servo Power ($V_{CC}$, Red):** Connect to **external 5V supply** (NOT the 3.3V pin!).
3. **Servo Ground (Brown/Black):** Connect to external supply GND **AND main board GND** (Common GND is required!).

### What you should see:

- Servo starts at 1500 µs (center).
- Each press on **BTN1** moves the servo clockwise by 100 µs.
- Each press on **BTN2** moves the servo counter-clockwise by 100 µs.
- Holding a button does NOT make it runaway (fires once per press).
- TFT displays the commanded pulse width live.

---

[Next: Wireless Control Classwork (D-Pad Presets & Motion) →](03-wireless.md)
