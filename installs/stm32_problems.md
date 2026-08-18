# Troubleshooting and More Info

Here are some common errors we've seen over the years:

### Program file does not exist

> <img src="https://i.imgur.com/RFDg47S.png" alt="" data-size="original">
>
> If somehow it says _Program file does not exist_, you can click Search Project and select the correct .elf file. In our case, `Release/SW Tutorial 2022.elf`.

### Project is already existing within current workspace

> You have already imported the folder but just didn't see that. To solve this just open the window of c/c++ projects.
>
> ![](https://i.imgur.com/yccdRwE.jpg)&#x20;
>
> Click the tiny "two windows button to show the project&#x20;
>
> If this still don't work, at the top bar select Window" -> "Show View" -> "C/C++ Projects" ![](https://i.imgur.com/4SJLUZV.jpg)

### "Error in launching installer" pops up when installing CubeIDE

> This happens because the exe file is located in a directory with Chinese characters and is not supported by the installer. Solution: Move the exe file to a directory with no Chinese characters in its path.

### ST Link server failed to start

> Windows Solution:
>
> &#x20;![](https://i.imgur.com/wCJXaKf.png)&#x20;
>
> Select Run Configurations, scroll all the way down that page, there’ll be a link to download the STLink Server. Follow the on-screen description.

### gdb failed to start

> Check your OpenOCD path
>
> Windows:
>
> &#x20;![](https://i.imgur.com/AtQTnB6.png)&#x20;
>
> In OpenOCD Command, the path should end with “\openocd.exe”&#x20;
>
> Mac:
>
> &#x20;![](https://i.imgur.com/Xk8Z7zA.png)&#x20;
>
> In OpenODC Command, the path should end with “\openocd”

## More configuration on the IDE

Since STMCubeIDE is based on Eclipse, you can configure the theme, keybindings, formatter and more.

> ![](https://i.imgur.com/jeWyQcS.png)&#x20;
>
> What I have configured:
>
> * Dark theme
> * Clang-formatter
> * Auto-complete
> * VSCode keybindings

## Explore the IDE if you have time!
