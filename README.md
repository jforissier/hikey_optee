This repository contains the software required to run AOSP on the HiKey board
with OP-TEE:
- ARM Trusted Firmware
- EDK2 (UEFI)
- Linux kernel
- OP-TEE (OS, driver, client library)
- Download rules to get pre-built AOSP binaries from linaro.org


## Usage

### 1. Prerequisites

On the hardware side, you need:
- A [HiKey board](https://www.96boards.org/products/hikey/)
- A power supply (8 - 18V, 2A, 1.7mm jack)
- A PC running Linux (I use Ubuntu 15.04 x86_64)
- A USB cable (male/male, A to micro-B) to connect your PC to the board
- A serial to USB adapter cable to connect to the SoC's UART0 (console).
  This  is not strictly required but chances are you won't be able to
  debug any secure OS code without it (OP-TEE and the Trusted Applications
  send their debug output to this serial console).
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
    android-tools-adb \
    curl \
    gdisk \
    python-serial \
    uuid-dev \
    flex \
    bison
```

If you are running a 64-bit linux distribution, you may also need
the following:
```
sudo apt-get install libc6:i386 libstdc++6:i386 libz1:i386
```

"Known good" cross compilers/toolchains are downloaded automatically from
linaro.org by the Makefile. This includes the Android NDK (Native
Development Kit).

Copy the USB device configuration file so that the fastboot command will
properly detect the board:

```
sudo cp 51-hikey.rules to /etc/udev/rules.d/
```

### 2. How to build
```
# Initialize URLs for git submodules
git submodule init

# Fetch submodules (will take time)
git submodule update

# Fetch the cross-compilers (~ 90MB) and build
make -j8
```

For a 32-bit TEE Core, use `make SK=32` (32-bit secure kernel).

If you have access to the GlobalPlatform "Initial Configuration Test Suite"
(TEE_Initial_Configuration-Test_Suite_v1_1_0_4-2014_11_07.7z), you my extract
it under optee_test and it will be included automatically. If you later
remove the directory, be sure to clean optee_test (git reset --hard HEAD).

### 3. How to flash the firmware onto the board

First, flash the Linaro pre-built AOSP image files. Set the J15 jumpers to:
1-2 closed 3-4 closed 5-6 open (recovery mode), then power up the board and
run:
```
make flash
```

Switch the board back to normal eMMC boot mode (J15 1-2 closed 3-4 open
5-6 open), turn power on, and after a few seconds you can upload the OP-TEE
files with:
```
make install
```

### 4. How to run OP-TEE tests (xtest)

You may monitor the early boot sequence and the OP-TEE debug output by
connecting to the board's boot console with:
```
./hikey_console.sh
```

To get a shell and run command-line programs, use adb:
```
adb shell
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
