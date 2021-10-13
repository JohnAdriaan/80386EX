# 80386EX Boot ROM plus Demonstrator

## References
SBC386EX: https://www.RetroBrewComputers.org/doku.php?id=boards:sbc:sbc-386ex:rev2.0
VGA3:     https://www.RetroBrewComputers.org/doku.php?id=boards:ecb:vga3:vga3
Boot:     https://GitHub.com/JohnAdriaan/80386EX
Demo:     https://Wiki.OSDev.org/User:Johnburger/Demo

## How to use

### Configuring the SBC386EX

##### Assumptions
| Peripheral | Description  |
| ---------: | :----------- |
| ROM        | 8K or more   |
| RAM        | 256K or more |
| Clock      | 64 MHz       |
| Serial     | 115,200 bps, No Parity, 8 Data bits, 1 Stop Bit |

### Configuring the VGA3

Note I don't have a keyboard controller chip yet!

##### Assumptions
| Peripheral | Value            | Description                                 |
| ---------: | :--------------- | :------------------------------------------ |
| IO         | `00E0h`          | Off, Off, Off, On, On                       |
| Mem        | `03F0_0000h`     | All Off; Off, Off, Off, Off, On, On, On, On |
| Sync       | Neg, Neg         | Right, Right                                |
| Clock      | 28.322 MHz       |                                             |
| KBD-INT    | IR1              | Right                                       |
| VER-INT    | IR2              | Right                                       |
| Monitor    | 90x43 @ 31.5 kHz | Widescreen LCD. May ignore Sync settings?   |

### Burning the ROM
The whole binary is only 8K in size, so you can burn it to any ROM - just make
sure that you burn it to the _**top**_ of the ROM rather than the start.

### Experimenting
The documentation, such as it is, is in the source code on GitHub.
The main file is `80386EX.asm`, which `%include`s all other `.inc` files.
This file has many constants, some of which can be modified.
Other files have other constants, which may also be modified.
Changing a constant often changes the system behaviour - but unfortunately, also often the code is written to assume that constant.

| File                 | Constant              | Description                                          |
| -------------------: | :-------------------- | :--------------------------------------------------- |
| `80386EX.asm`        | `Boot.BaudRate`       | Serial I/O parameters                                |
|                      | `Boot.Protocol`       |                                                      |
|                      | `Screen.Width`        | Code tries to adjust if these change                 |
|                      | `Screen.Height`       |                                                      |
|                      | `Font.Height`         |                                                      |
|                      | `CPU.CLK2`            | Clock speed                                          |
|                      | `*.Waits`             | Number of Wait States for Chip Select accesses       |
| `Boot/ECB.inc`       | `ECB.Mem.Start`       | Above this is ROM; below this is RAM                 |
|                      | `ECB.IO.Start`        | Avoid on-board peripherals!                          |
| `Boot/Video.inc`     | `Vid.0.Mem.Start`     | Needs to be in ECB space...                          |
|                      | `Vid.0.IO.Start`      |                                                      |
|                      | `Vid.1.Mem.Start`     | Try multiple video cards?                            |
|                      | `Vid.1.IO.Start`      |                                                      |
| `Dev/Timer.inc`      | `Dev.Timer.ClockFreq` | Frequency of Timer Clock                             |
| `Demo/Defn.inc`      | `Demo.Timer.Tick`     | Number of Timer Interrupts a second                  |
|                      | `Demo.Window.Width`   | `.Width` and `.Height` should be relatively prime    |
|                      | `Demo.Window.Height`  |                                                      |
|                      | `Demo.User.Ball.*`    | User preference                                      |
|                      | `Demo.User.Frame.*`   |                                                      |
|                      | `Demo.User.Delay`     | Delay for one kind of multitasking model. See below. |
| `Demo/User/Code.inc` | See `.Wait:`          | There are a number of different multitasking models: |
|                      | `HLT`                 | User code can't use this instruction!                |
|                      | `User.Halt`           | This is a system call to call `HLT` for it           |
|                      | `User.Yield`          | This is a system call to switch to the next Task     |
|                      | `LOOP`                | The system is preemptive, so this works too          |
