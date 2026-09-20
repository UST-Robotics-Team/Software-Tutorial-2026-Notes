# Basic STM32 Configuration

> Please be **noted** that we are demonstrating how to set up a new
GPIO **OUTPUT** pin.

Throughout your RDC journey, you will not need to configure all pinouts and function modules from scratch due to the many technical considerations involved. We have already provided you with a mostly completed configuration file called "SW Tutorial," which includes commonly used functionalities such as CAN, LED, TFT, and PWM.
However, you may still need to utilize some GPIO pins, and we cannot predict what and where you will connect to the board. Therefore, we will introduce some basic skills for setting up GPIO pins.

### Project Structure

In the project, you will commonly see a folder structure like this:
![Project structure](./image/project%20structure.png)
**Key Points:**

- The `includes` folder contains fundamental libraries that you should not modify. User-written headers should be stored in `/Core/Inc`.
- The `sw-tutorial.ioc` file opens the CubeMX GUI, a tool that allows you to configure different pinouts.
- Note that changes made in the configuration file will not take effect immediately. You must click "Generate Code" in CubeMX to apply the configuration.

### Configuration & Pinout Page

When you click the `.ioc` file, you will enter an interface similar to this:
![](./image/Pinout%20&%20Config.png)

- The leftmost panel is the **Module Panel**, where you can select all the available subsystems for the selected chip.
- The second panel from the left is the **Configuration Panel**, where you can access and set up detailed configurations.
- The main panel on the right is the **Pinout Panel**, where you can choose the purpose of each pin

### How to Configure a GPIO Pin

1. **Select the Pin**: Find the correct pin you want to connect, such as `PC0`, based on the hardware schematic.
2. **Assign Functionality**: Click on the pin and select the appropriate system/application you want to link it to:
   ![](./image/PC0.png)
3. **Configure the Pin**: Open the corresponding system module (in this case, `GPIO`) and locate the pin you just set up:
   ![](./image/PC0_Config.png)
   - Inside this configuration window, you can choose different settings for the GPIO pin. Ideally, you should not need to change anything from the default configuration for a `GPIO Output` pin.
   - You can (and should) also rename the pin with a meaningful name. As mentioned in `02-GPIO.md`, CubeMX will generate the appropriate macro based on the name you enter, so you should rename it here instead of manually writing a macro.
4. **Save your configuration and Generate Code**:\
  As mentioned, you need to save and generate code before you can make your change effective. In CubeMX under CubeIDE, you just need to save your change by click `Ctrl + S` ~~(mac ppl help yourself)~~ and click **YES** in the following Pop-up Windows.
   ![](./image/Generate_Code.png)
5. **Bug Fixing**:
   - Comment the `MX_SPI_Init()` in `main.c`, due to some compilated reason, we have init the SPI in `tft_init()` and so double init may possibiy lead to some issue, therefore please help yourself and comment out this line:
      ```c
        /* main.c */
        /* Initialize all configured peripherals */
        MX_GPIO_Init();
        MX_DMA_Init();
        MX_CAN2_Init();
        // MX_SPI1_Init(); //Help us Comment out this line
        MX_USART1_UART_Init();
        MX_I2C2_Init();
        MX_CAN1_Init();
        MX_USART2_UART_Init();
        MX_TIM5_Init();
      ``` 
   - As the `tft_update()` is accidently put outside the designed zone for some destribution, your `tft_update()`, Please add the `tft_update(1)` in your main `while` loop if you don't find it there

## How to use the pins

After you generate the code, STM CubeIDE suppose will lead you back to the `main.c` or may be some other `.c` / `.h` files, if you want to check whther your code is generated correctly, you can do this:

Go to your `main.h`, you shoould able to find this:
```c
#define {the pin name you put}_Pin GPIO_Pin_{the pin number}
#define {the pin name you put}_GPIO_Port GPIO{The Pin Group}
```
For example I name my new pins as `Valve`, then in my `main.h` I find this:
```c
#define Valve_Pin GPIO_PIN_8
#define Valve_GPIO_Port GPIOB
```
> Please check if you do anything wrong if you cannot find or ask our senior, please **DO NOT** manually add this if you cannot find this!

After you confirm you have added this new pins, you can use it like how we use it before:

```c
// If it is a GPIO Output Pin, you can:
gpio_set(Valve); // Set the pin to HIGH
gpio_reset(Valve); // Reset the pin to LOW
gpio_toggle(Valve); // Toogle the pin

// If it is a GPIO Input Pin, you can:
uint8_t state = gpio_read(Valve);
```
At the meantime, we are not encouraged to use the `btn_read()` or `led_on()` or `led_off()` as we have mentioned before, we have flip the value of 0 and 1 for led and btn due to the hardware design, and so it may work somehow counter initative if you use it here.

---
> Here are some extended explanation about different mode of GPIO Input and Output, you can try understanding what is happening but no worries if you cannot understand all.
# Extended Reading: GPIO Input Mode

- As we have mentioned, our GPIO only receive discrete 0/1 signal, so it is trivial enough when we have a GND / 3.3V(out TTL is set to be 3.3V) given to the port, but what if it is not connected to anything?
- When it is not connected to anything, it is the case we say it is in a floating state, and it will lead to a unpredictable readings due to noise.
- The following schematics show an example of the pin not being connected to anything:

    <figure><img src="image/Button_Sch.png" alt=""><figcaption></figcaption></figure>
    
    - When the button is pressed, the `BUT1` pin connected to `GND` , which refer to 0.
    - How about when the button is released?
        - Noise will cause you to read a mostly random value
    - Therefore we want to have some mechanism to make it to be a `1` or `3.3V` when the button is released, in the other words, and that is `PULL-UP`  in this case.

- The pull-up or pull-down gives a "**weak**" connection from the pin to either a high or low voltage. It gives a defined value to a floating pin while being weak enough to be easily overridden by any external signal.

#### Pull Up and Pull Down

<figure><img src="image/Pull_Up.png" alt=""><figcaption></figcaption></figure>

<figure><img src="image/Pull_Down.png" alt=""><figcaption></figcaption></figure>

When you choose `Pull Up` or `Pull Down` in the configuration, the MCU will connect the input to the `Vcc` / `GND` by itself and reduced the need for additional hardware components on the PCB.

⭐Other than `Pull Up` or `Pull Down` , you may also choose the `No Pull` for Input Mode if your PCB is already connected to both 3V3 and GND by default.

### Extended Reading: GPIO Output Mode

- Similar to input, we have two modes of output in GPIO, namely **Push-pull** and **Open-drain**
  - **Push-pull(PP)** uses the 2 switches to connect the pin to either high voltage or low voltage, it pushes or pulls the voltage to the level assigned
  - **Open-drain(OD)** is similar but does not use the upper switch, thus it outputs a low voltage or completely disconnects the pin
- Inside the MCU lives a pair of switches, ie.`transistors`:
    <figure><img src="image/GPIO_Output_Mode.png" alt=""><figcaption></figcaption></figure>

### Side Tracker: GPIO Configuration

Below we extract one GPIO `_Init` segment for you to see what is taking place during GPIO INIT, but you does not required to understand what is happening behind

```c
void MX_GPIO_Init(void)
{

  GPIO_InitTypeDef GPIO_InitStruct = {0};

  /* GPIO Ports Clock Enable */
  __HAL_RCC_GPIOB_CLK_ENABLE();

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOB, TFT_BL_Pin|CAM_WEN_Pin|CAM_RCLK_Pin|LED4_Pin
                          |LED3_Pin|LED2_Pin|LED1_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pin : PtPin */
  GPIO_InitStruct.Pin = BTN1_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
  GPIO_InitStruct.Pull = GPIO_PULLUP;
  HAL_GPIO_Init(BTN1_GPIO_Port, &GPIO_InitStruct);

  /* EXTI interrupt init*/
  HAL_NVIC_SetPriority(EXTI15_10_IRQn, 0, 0);
  HAL_NVIC_EnableIRQ(EXTI15_10_IRQn);
}
```
