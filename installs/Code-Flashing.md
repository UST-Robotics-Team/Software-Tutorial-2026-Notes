# Additional Code Flashing Instructions

## Changing the Settings (Only do for the first time)

> We have discovered that sometimes the OpenOCD is less reliable than the ST-Link GDB Server, so let's change the settings to use that instead.

> <img src="https://i.imgur.com/wCJXaKf.png" alt="" data-size="original">
> 
> Click the arrow besides _Run_ and click _Run Configurations..._
>
> <img src="https://i.imgur.com/QgjX5CL.png" alt="" data-size="original">
>
> Choose STM32 Application the left and select _Debugger_ Tab.
>
> ![](/images/STLink%20GDB%20Server.png)
>
> Change Debug probe to `ST-LINK (GDB Server)`.

## Downloading the most updated `SW-Tutorial.zip`

We have discovered there is some incability with the current `SW-Tutorial.zip` file that is included in the repository. So please download the most updated version from this link: [2025-SW-Tutorial-v2.zip](/images/2025-sw-tutorial-v2.zip)

Please do the following to ensure you have opened the most updated version:
1. Delete the current project from STM32CubeIDE.
   > Right click the project and select `Delete` 
2. Unzip the downloaded `2025-SW-Tutorial-v2.zip` file.
3. Open the project by going to `File -> Open Projects from File System...` and select the unzipped folder.
   > Please ensure you select the correct folder that directly contains the `.project` file instead of the folder that contains the `2025-SW-Tutorial` folder.
4. Make sure you select the project and click finish.
5. You should be seeing this now:
   ![](/images/ST-Updated%20Tutorial%20zip.png)

## Flashing the Code

> In industrial applications, it is common that you need to manually reset the micro controller during flashing. This is because the micro controller might be in a state where it cannot be programmed (e.g. in low power mode). To manually reset the micro controller, you can use the reset button on the board.

By making use the `STLink GDB Server`, you can now flash the code by this:

1. Click the run button 
2. Wait until you see the message `Waiting for debugger connection...`
   ![](/images/STLink%20Reset1.png)
3. When you see that message, press the reset button on the board once only.
   > Note: Do not hold the reset button, just press and release it once and do it once only. (You are suppose to see `Waiting for debugger connection...` more than once)

   > This step is not every time necessary, but if you see the message Error in flashing, then you should restart the process with this step.
4. Wait until you see the message `Download veriified successfully`
   ![](/images/STLink%20Reset2.png)
5. Press the reset button on the board once only again to start the program.
   > :star: After the `run` operation done, the code have been successfully flashed to the board. And you can restart your program by pressing the reset button on the board once only. And flashing the code is not necessary unless you want to update the code.
6. Then you are good to go!