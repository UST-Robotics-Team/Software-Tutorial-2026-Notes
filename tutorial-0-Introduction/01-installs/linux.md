# Arch Linux
## 01-VSCode
Caution: You cannot find the STM32CubeIDE extension in VSCode if you installed VSCode from the pacman official repository, so you need to install it from AUR(Arch User Repository) instead.

0. Install compiler packages for CMake (Optional, only required if you want to build the project without STM32CubeIDE extension)
```bash
sudo pacman -S arm-none-eabi-gcc arm-none-eabi-binutils arm-none-eabi-gdb arm-none-eabi-newlib
```

1. Compile VSCode from AUR
```bash
git clone https://aur.archlinux.org/visual-studio-code-bin.git
cd visual-studio-code-bin
makepkg -si
```

You can remove the above source directory once you successfully compile it.

2. Run VSCode as user (NOT ROOT) from command line
```bash
code
```

# Ubuntu
To Be Updated