# MacOS

<details>

<summary>Authors</summary>

Leo Wong, Wesley Leung

</details>

## Download & Install

First download the STM32CubeIDE installer from our [Github](https://github.com/UST-Robotics-Team/Software-Tutorial-2025-Notes/releases/tag/Installer).

> :warning: **Warning**: NEVER place the PCB on top of your computer, it may kill your computer.

> <img src="https://i.imgur.com/7IjBmYe.png" alt="" data-size="original">
>
> Click Agree on the bottom right
>
> <img src="https://i.imgur.com/eTFKAw1.png" alt="" data-size="original">
>
> Double click the box icon on the top left.
>
> <img src="https://i.imgur.com/2a6pI0n.png" alt="" data-size="original">
>
> Click OK
>
> <img src="https://i.imgur.com/cW9vxLR.png" alt="" data-size="original">
>
> Go to System Preferences>Security\&Privacy, search near the bottom right region, click "Open Anyway" for "st-stlink-server.2.1.0-1.pkg"
>
> <img src="https://i.imgur.com/JZg4w0E.png" alt="" data-size="original">
>
> Click "Open"

You will now proceed to install st-stlink-server.2.1.0-1.pkg

> <img src="https://i.imgur.com/eJkFhn6.png" alt="" data-size="original">
>
> Click, continue/ install to complete the installation process

After you have done installing the st-stlink-server.2.1.0-1.pkg, install STM32CubeIDE by dragging the Application icon to the Application folder

> <img src="https://i.imgur.com/Za7b8Bk.png" alt="" data-size="original"><img src="https://i.imgur.com/f4IjzMD.png" alt="" data-size="original">
>
> CubeIDE is not malware
>
> <img src="https://i.imgur.com/CXkEcpq.png" alt="" data-size="original">
>
> Go to System Preferences>Security\&Privacy, search near the bottom right region, click "Open Anyway" for "STM32CubelDE"
>
> <img src="https://i.imgur.com/Lb9cFD5.png" alt="" data-size="original">
>
> Press "Open"

After you have installed the IDE, please follow the steps below to properly setup your **Integrated Development Environment.**

### Import the project files

Download the [sw-tutorial.zip](../images/2025-sw-tutorial-v2.zip) we prepared for you below.

_Note that we may have some library changes from time to time. So always follow what the tutorial notes say._

> <img src="https://i.imgur.com/238rqEI.png" alt="" data-size="original">
>
> You can choose whichever directory you like to place the project files. Just make sure you can find it afterwards.
>
> <img src="https://i.imgur.com/JMpsbJJ.png" alt="" data-size="original">
>
> If the application ask for permission to accept incoming network connections, click "Allow" ![](https://i.imgur.com/C2rmwU9.jpg)
>
> Click Import in File tab
>
> <img src="https://i.imgur.com/2znwChr.png" alt="" data-size="original">
>
> Under General choose "Existing Projects into Workspace"
>
> <img src="https://i.imgur.com/Vrg630D.png" alt="" data-size="original"><img src="https://i.imgur.com/EwspMdM.png" alt="" data-size="original">
>
> Extract the entire code boilerplate file (unzipped) you have downloaded and select that as root directory. Click finish afterwards.
>
> <img src="https://i.imgur.com/XUTurja.jpg" alt="" data-size="original">
>
> Tada! You have successfully imported the code boilerplate.

### Configure ST-Linkv2 (Mac)

> <img src="https://i.imgur.com/Ss2oFzC.jpg" alt="" data-size="original">
>
> On the top left click the red cross to close the Information Center page
>
> <img src="https://i.imgur.com/FxREOI3.png" alt="" data-size="original">
>
> You should now see this
>
> <img src="https://i.imgur.com/BEYLbee.png" alt="" data-size="original">
>
> Switch build option from Debug to Release
>
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
> Change Debug probe to `ST-LINK (GDB Server)`. Also double check that the OpenOCD command is the same as the one in the image above.
>
> ![](/images/STLink%20Software%20System%20Reset.png)
> 
> In `Mode Setup`, select `Software system reset` in `Reset Mode`.
>
> ![](https://i.imgur.com/Wa5m30S.png)
>
> If you see this, you should be good to go. Ask someone to give you a mainboard and a ST-LINK (the USB like thingy we use to flash code onto the board) and see if it works.
