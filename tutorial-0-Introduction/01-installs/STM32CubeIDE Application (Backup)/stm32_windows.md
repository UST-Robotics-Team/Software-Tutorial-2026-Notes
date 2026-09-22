# Windows

<details>

<summary>Authors</summary>

Leo Wong, Wesley Leung

</details>

## Download & Install

First download the STM32CubeIDE installer from our [Github](https://github.com/UST-Robotics-Team/Software-Tutorial-2025-Notes/releases/tag/Installer).

> :warning: **Warning**: NEVER place the PCB on top of your computer, it may kill your computer.

> <img src="https://i.imgur.com/s3DFKCY.png" alt="" data-size="original">
>
> You can choose which every directory you like to place the project files. Just make sure you can find it afterwards.

> <img src="https://i.imgur.com/huv0HIY.png" alt="" data-size="original">
>
> J-Link drivers is not needed in this case But definitely check the ST-link drivers cuz we need then to flash(upload) the program to the mainboard.

After you have installed the IDE, please follow the steps below to properly setup your **Integrated Development Environment.**

### Import the project files

Download the [2025-sw-tutorial-v2.zip](../images/2025-sw-tutorial-v2.zip) we prepared for you below.

_Note that we may have some library changes from time to time. So always follow what the tutorial notes say._

> ![](<../../../images/image (3) (1).png>)
>
> Unzip the `sw-tutorial` and put it into any folder. (ignore the metadata)

> &#x20;![](<../../../images/image (1) (1).png>)
>
> Open STMCubeIDE 1.19.1 and you will see the following window.
>
> You can choose whichever directory you like to place the project files. Just make sure you can find it afterwards.

> ![](<../../../images/image (3) (1) (1).png>)\
> Click `File` -> `Open Projects from File System...`&#x20;

> ![](<../../../images/image (29).png>)
>
> Click `Directory` and find the location of your `sw-tutorial` folder.

> <img src="https://i.imgur.com/fjDdL1M.jpg" alt="" data-size="original">
>
> Tada! You have successfully imported the code boilerplate.

### Configure ST-Linkv2 (Windows)

> <img src="https://i.imgur.com/TNJrgms.png" alt="" data-size="original">
>
> Switch build option from Debug to Release

> <img src="https://i.imgur.com/8XwVtFQ.png" alt="" data-size="original">
>
> Click the arrow besides _Run_ and click _Run Configurations..._

> <img src="https://i.imgur.com/AtQTnB6.png" alt="" data-size="original">
>
> Choose STM32 Application the left and select _Debugger_ Tab.
>
>
> ![](/images/STLink%20GDB%20Server.png)
> 
> Change Debug probe to `ST-LINK (GDB Server)`. Also double check that the OpenOCD command is the same as the one in the image above.
>
> ![](/images/STLink%20Software%20System%20Reset.png)
> 
> In `Mode Setup`, select `Software system reset` in `Reset Mode`.
>
> <img src="https://i.imgur.com/Wa5m30S.png" alt="" data-size="original">
>
> If you see this, you should be good to go. Ask someone to give you a mainboard and a ST-LINK (the USB like thingy we use to flash code onto the board) and see if it works.
