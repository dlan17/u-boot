# Build & Run u-boot on A733

## 1. TF-A

download TF-A source:
```sh
 $ git clone -b A733 https://github.com/dlan17/trust-firmware-a
```

compile the code
```sh
 $ cd trusted-firmware-a
 $ make CROSS_COMPILE=aarch64-linux-gnu- PLAT=sun60i_a733 DEBUG=1
 $ export BL31=$(pwd)/build/sun60i_a733/debug/bl31.bin

```

## 2. sunxi-tools

download sunxi-tools
```sh
 $ git clone -b A733 https://github.com/dlan17/sunxi-tools
```

build tools on HOST, usually it's your x86 development machine
```sh
 $ make
```

after its completion, you will get 'sunxi-fel' tool

## 3. u-boot

download u-boot source:
```sh
 $ git clone -b allwinner/A733 https://github.com/dlan17/u-boot
```

compile u-boot:
```sh
 $ cd u-boot
 $ make CROSS_COMPILE=aarch64-linux-gnu- radxa-cubie-a7a_defconfig
 $ make CROSS_COMPILE=aarch64-linux-gnu-
```

run u-boot

in serial console, enter charactor "2" during board power up phase,
to make it enter FEL mode after the DDR initialization.
```log
[105]HELLO! BOOT0 is starting!
[108]BOOT0 commit : {9f6fab4f-dirty}
[122]dram_para_total:0xf
[124]vaild para:5  select dram para2
[128]rtc[3] value = 0xb00f
[131][mmc]: mmc driver ver 2024-03-20 10:36
[141][mmc]: Wrong media type 0x0
[144][mmc]: ***Try SD card 0***
[153][mmc]: HSSDR52/SDR25 4 bit
[156][mmc]: 50000000 Hz
[158][mmc]: 29655 MB
[160][mmc]: ***SD/MMC 0 init OK!!!***
[167]DRAM BOOT DRIVE INFO: V0.601
[171]DRAM_VCC set to 560 mv
[174]DRAM CLK =1800 MHZ
[176]DRAM Type =9 (8:LPDDR4,9:LPDDR5)
[333]Training result is = 7
[336]DRAM Pstate 1 training, frequency is 1200 Mhz
[525]Training result is = 7
[528]DRAM Pstate 2 training, frequency is 800 Mhz
[889]Training result is = 7
[892]DRAM Pstate 3 training, frequency is 400 Mhz
[1001]Training result is = 7
[1004]DRAM Pstate 0 training, frequency is 1800 Mhz
[1013]Actual DRAM SIZE =8192 M
[1016]DRAM SIZE =8192 MBytes, para1 = a10a, para2 = 20001001, dram_tpr13 = 65
[1031]DRAM simple test OK.
[1033]key press : 2
[1035]detected_r user input 2
[1038]Failed preparing the second boot
```
once you see "detected_r user input 2", it means the board enter into FEL mode.


run u-boot! need two images below which generated from the u-boot repository

```sh
 $ sudo sunxi-fel write 0x4D000000 u-boot-sunxi-with-spl.fit.fit
 $ sudo sunxi-fel -v spl u-boot-sunxi-with-spl.bin
```

