[Back to Tutorial 1](./) | [Previous: Clock](02-clock.md) | [Next: Homework](./04-homework.md)

**This section contains Classwork 3**

# 3. TFT

**Outline**
- TFT Basics
- **Classwork 3**

## Printing Something! (finally)

When learning programming, most of the integrated development environment (IDE) you will/might have used will have a console for output and will often be used for debugging.

In C,

```c
int c = 25;
printf("The value of c-squared is : %d",c*c);
//Output will come as "The value of c-squared is : 625"
```

In Python,

```py
c = 25
print("The value of c-squared is: ",c*c) # c**2
#Output will come as "The value of c-squared is : 625"
```

However, in the embedded C Environment, you cannot directly access to the console of the C runtime, and connecting it to debugger is not always possible. (Also, experience may tell you that debugging with the debugger may actually be a painful experience)

Therefore, we added a small display component to the PCB to print debug messages, or display graphics instead. In robotics we often use the TFT as the display.

## Using the TFT

### `tft_init`

We have provided you a TFT library to make it easier to work with. To use this library, you must first call the `tft_init` function BEFORE your `while (1)` main loop.

```c
// Definition of tft_init in the TFT library (provided for you)
void tft_init(TFT_ORIENTATION orientation, uint16_t bg_color, uint16_t text_color, uint16_t text_color_sp, uint16_t highlight_color);

// USAGE
/* main.c*/
/* USER CODE BEGIN 2 */
tft_init(PIN_ON_TOP, BLACK, WHITE, CYAN, DARK_GREY);
/* USER CODE END 2 */
```

<details>
    <summary>Parameter Detail</summary>

- orientation - _**Orientation of the monitor**_
- bg_color - _**Background color**_
- text_color - _**Text color**_
- text_color_sp - _**Special Text color**_ - `[]`
- highlight_color - _**Highlight color**_ - `{}`

The parameters have already been defined for you in `lcd.h` header-file. It is defined as follows:

### \* **Orientation**

```c
typedef enum {
    PIN_ON_TOP,
    PIN_ON_LEFT,
    PIN_ON_BOTTOM,
    PIN_ON_RIGHT
} TFT_ORIENTATION;
```

### \* **Colors**

You may choose one of the following colours according to your own desire for the **TFT**. Of course! You may also define new color yourself. The following are RGB565 format

```c
#define WHITE           (RGB888TO565(0xFFFFFF))
#define BLACK           (RGB888TO565(0x000000))
#define DARK_GREY       (RGB888TO565(0x555555))
#define GREY            (RGB888TO565(0xAAAAAA))
#define RED             (RGB888TO565(0xFF0000))
#define DARK_RED        (RGB888TO565(0x800000))
#define ORANGE          (RGB888TO565(0xFF9900))
#define YELLOW          (RGB888TO565(0xFFFF00))
#define GREEN           (RGB888TO565(0x00FF00))
#define DARK_GREEN      (RGB888TO565(0x00CC00))
#define BLUE            (RGB888TO565(0x0000FF))
#define BLUE2           (RGB888TO565(0x202060))
#define SKY_BLUE        (RGB888TO565(0x11CFFF))
#define CYAN            (RGB888TO565(0x8888FF))
#define PURPLE          (RGB888TO565(0x00AAAA))
#define PINK            (RGB888TO565(0xC71585))
#define GRAYSCALE(S)    (2113*S)
```

### **Example:**

```c
void tft_init(TFT_ORIENTATION orientation, uint16_t bg_color, uint16_t text_color, uint16_t text_color_sp, uint16_t highlight_color);
/*
 * Initialisation Example
 *
 * Orientation : Pin_on_top
 * Background color : black
 * Text color : white
 * Special Text color : red
 * Highlight color : dark green
 */

tft_init(PIN_ON_TOP, BLACK, WHITE, RED, DARK_GREEN);
```

</details>

### **Print String**

Use `tft_prints` to print something starting from the specified row and column, similar to `printf`.

```c
void tft_prints(uint8_t x, uint8_t y, const char* fmt, ...);
```

- **x**: nth horizontal column ranging from 0 to 15 (16 columns)
- **y**: nth vertical row, ranging from 0 to 9 (10 rows)
- **fmt**: string with format templates (same as C's printf)
- **...** : variable to replace the placeholder in the string (same as C's printf)

#### Example

```c
int a = 10;
tft_prints(0, 0, "The value of a is %d", a);
// The value of a is 10
```

### **Print Pixel**

Print a single pixel on the specified cell.

```c
void tft_print_pixel(uint16_t color, uint32_t x, uint32_t y);
```

- **color** : colour of your pixel (Use the `#define` colours)
- **x** : n-th horizontal pixel, ranging from 0 to 127
- **y** : n-th vertical pixel , ranging from 0 to 159

### **Update**

TFT operations may be expensive and the main loop may run very fast. Call `tft_update` to find out whether the TFT should get updated in this iteration.

```c
uint8_t tft_update(uint32_t period);
```

- **period** : period of updates in milliseconds

Example:
```c
tft_update(50);
```

- Add after your other TFT function calls in your while loop.
- Every time the `tft_update` function is called, if `50ms` has not passed, the TFT will not be updated.
- If `50ms` has passed, it will update the TFT based on your TFT function calls (e.g. any new text to print).

### **Miscellaneous**

The TFT library also provides some graphics helpers in `lcd_graphics.h`. Make sure to include that library header under the `USER CODE BEGIN Includes` line so you can use those functions

```c
/* USER CODE BEGIN Includes */

// This line is already added for you:
#include "lcd/lcd.h"

// You need to add this line underneath:
#include "lcd/lcd_graphics.h"

/* USER CODE END Includes */
```

```c
void drawLine(int16_t x0, int16_t y0, int16_t x1, int16_t y1, uint16_t color);

void drawCircle(int16_t x0, int16_t y0, int16_t r, uint16_t color);

void drawTriangle(int16_t x0, int16_t y0, int16_t x1, int16_t y1, int16_t x2, int16_t y2, uint16_t color)
```

Note that these graphics functions would immediately update the TFT screen when called (independent of `tft_update()`).

### **Example of using TFT**

Here is the full workflow.

```c
while(1){
    /*This is referring to your main while(1) loop,
      Do not create another while(1)*/
    tft_prints(0, 0, "Hello World"); // normal
    tft_prints(0, 1, "[Hello World]");  // This is a special text with differnt color
    tft_prints(0, 2, "{Hello World}");  // This is a higlighted text
    tft_prints(0, 3, "|Hello World|");  // This is a underlined text
    drawCircle(50, 100, 10, RED); // Draw a small circle
    tft_update(50);
}
```

## Classwork 3: TFT

For your third and final graded classwork, you will be making a digital clock display with the TFT.

Here are your tasks:

- Print the time elapsed with the format of `mm:ss:sssZ` where `sssZ` means millisecond. e.g. `00:23:109` **(@2)**

- Toggle the highlight of the text you print every second, which means: **(@3)**
  - **1st second**: print normal text
  - **2nd second**: print highlighted text
    - Recall 1:  How to print highlighted text:
      ```c
      tft_prints(0, 2, "{Hello World}");  
      // This is a higlighted text
      ```
    - Recall 2: We define the color of hightlight in `tft_init`:
      ```c
      void tft_init(TFT_ORIENTATION orientation, uint16_t bg_color, uint16_t text_color, uint16_t text_color_sp, uint16_t highlight_color);
      ```
  - **3rd second**: print normal text


> Hint: Making use of mod and integer division.

**Reminder: Please save your code for Classwork 3 in a separate file somewhere before starting homework 1**

---

[Back to Tutorial 1](./) | [Previous: Clock](02-clock.md) | [Next: Homework](./04-homework.md)
