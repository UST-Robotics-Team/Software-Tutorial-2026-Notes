# Installing Compiler (for Windows)

<details>

<summary>Authors</summary>

Li Chi Kin Andy

</details>

> Note: For the purposes of our tutorials you aren't required to install a compiler since for the most part we will be using STM32CubeIDE which comes with everything you need, and the tasks for tutorial 1 should be doable with an online IDE. However, we have seen cases where Windows users need to install a compiler on their own to make CubeIDE work properly, so this is here for reference. More info/instructions for Mac/Linux should be easily found on Google if you're into that.

Windows OS does not have any C/C++ compiler installed by default. This chapter teaches you how to install the MinGW C/C++ compiler. The whole process should take around **10-20 minutes**.

## Step 1

Go to this website [https://sourceforge.net/projects/mingw/](https://sourceforge.net/projects/mingw/) download the compiler

![](../images/264216332-e4098608-3456-4dcb-a817-6cd3aa108203.png)



## Step 2

2.1) Open the downloaded setup tool, press the Install and Continue button, and you will reach this interface.

![](../images/264216995-5af504fa-77e5-43c7-b43a-447d55e8e41f.png)

2.2) Select all packages by clicking 'Mark for Installation', go to Installation (at the top left corner), and click 'Apply Changes'.&#x20;

![](../images/264217506-717a3666-13dd-4f1b-a842-60007c55c5ae.png)

2.3) Start downloading packages



## Step 3

Copy the path of your Mingw to the environment variable

3.1) Search PATH in windows

3.2) Click on 'Edit the system environment variables', in Chinese,'編輯系統環境變數'.

![](../images/264218561-8248493b-369f-4096-8008-d648c2a8772c.png)

3.3) Add C:\MinGW\bin to PATH

![](../images/264222538-fa150969-81c3-4f64-a922-1732d3c09974.png)

## Step 4

To test whether the installation is successful, type `g++ --version` in the terminal to check.

![](<../images/image (14).png>)

##

#### Congratulations 🎉🎉 you have successfully installed the MinGW C/C++ compiler!!

## Reference

[https://www.youtube.com/watch?v=FEeFG9OR-QU\&ab\_channel=GeekyScript](https://www.youtube.com/watch?v=FEeFG9OR-QU\&ab\_channel=GeekyScript)

&#x20;
