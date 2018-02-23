** Note **  This repository is not maintained anymore. Please see
https://github.com/jforissier/optee_build (branch hikey) for a more
up-to-date environment (based on git submodules, like this one).

If you don't mind using Google's `repo` tool, please use
https://github.com/OP-TEE/manifest (which is the official
master project for OP-TEE). The manifest for HiKey is `hikey.xml`.

---

This repository contains the software required to boot the HiKey board
with OP-TEE:
- ARM Trusted Firmware
- EDK2 (UEFI)
- GRUB 2
- Linux kernel
- BusyBox
- OP-TEE (OS, driver, client library)
- OP-TEE tests


## Usage

### 1. Prerequisites

On the hardware side, you need:
- A [HiKey board](https://www.96boards.org/products/hikey/)
- A power supply (8 - 18V, 2A, 1.7mm jack)
- A PC running Linux (I use Ubuntu 15.04 x86_64)
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
sudo apt-get install \
    android-tools-fastboot \
    autoconf \
    curl \
    gdisk \
    python-serial \
    uuid-dev \
    flex \
    bison \
    mtools
```

If you are running a 64-bit linux distribution, you may also need
the following:
```
sudo apt-get install libc6:i386 libstdc++6:i386 libz1:i386
```

"Known good" cross compilers/toolchains are downloaded automatically from
linaro.org by the Makefile.

Copy the USB device configuration file so that the fastboot command and the
recovery flash script will properly detect the board:

```
sudo cp 51-hikey.rules /etc/udev/rules.d/
```

### 2. How to build

```
# Initialize URLs for git submodules
git submodule init

# Fetch submodules (will take time)
git submodule update --recursive

# Fetch the cross-compilers (~ 90MB) and build
make -j8
```

For a 32-bit TEE Core, use `make SK=32` (32-bit secure kernel).
For a 32-bit root filesystem, use `make NSU=32` (32-bit non-secure user mode).

If you have access to the GlobalPlatform "Initial Configuration Test Suite"
(TEE_Initial_Configuration-Test_Suite_v1_1_0_4-2014_11_07.7z), you my extract
it under optee_test and it will be included automatically. If you later
remove the directory, be sure to clean optee_test (git reset --hard HEAD).

Refer to `make help` for details.

### 3. How to flash the firmware onto the board

Switch to recovery mode (J15 pins 1-2 closed 3-4 closed 5-6 open),
power up the board and run:
```
make flash
```

### 4. How to run OP-TEE tests (xtest)

Connect to the board with:
```
./hikey_console.sh
```

Then you may run the tests with:
```
# Run all tests
xtest
# Run one test
xtest 4001
# Run tests 1* or 1000*
xtest _1
xtest _1000
```
