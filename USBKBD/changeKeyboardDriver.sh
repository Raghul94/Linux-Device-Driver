#! /bin/bash

sudo make -C /usr/src/linux-headers-$(uname -r) M=$PWD modules

sudo insmod usbkbd.ko




