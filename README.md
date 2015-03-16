This repository contains the software required to boot the HiKey board
with UEFI: ARM Trusted Firmware, EDK2, Linux kernel, BusyBox.
See https://github.com/96boards/documentation/wiki/UEFI for details.

## Usage

### 1. Prerequisites

On the hardware side, you need:
- A [HiKey board](https://www.96boards.org/products/hikey/)
- A power supply (8 - 18V, 2A, 1.7mm jack)
- A PC running Linux (I use Ubuntu 14.10)
- A HDMI monitor
- A HDMI cable (full size)
- A USB cable (male/male, A to micro-B) to connect your PC to the board
- A serial to USB adapter cable to connect to the SoC's UART0 (console).
  This  is not strictly required but chances are you won't be able to
  debug any bootloader/secure OS code without it.
  You need a 1.8V-compatible serial cable. The one I use is made by FTDI and
  is reference TTL-232RG-VIP. Not cheap, but works fine.
  Wiring for this cable is as follows:
```
 RED [VCC]     <==> Pin 1 [1.8V]
 BLACK [GND]   <==> Pin 3 [DGND]
 YELLOW [RXD]  <==> Pin 4 [UART0_TX]
 ORANGE [TXD]  <==> Pin 2 [UART0_RX]
 GREEN  [RTS#] <==> (not connected)
 BROWN  [CTS#] <==> (not connected)
```

As for software:
```
$ sudo apt-get install \
    gcc-arm-linux-gnueabihf \
    python-serial \
    gdisk
```

### 2. How to build
```
$ make
```

### 3. How to flash the firmware onto the board
```
$ make help
```
