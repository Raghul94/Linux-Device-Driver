This modfified usbkbd.c will change the behaviour of CAPSL led in the keyboard.

In Mode 1, the keyboard will have normal behaviour (i.e), the CAPSL led will glow when CAPSLOCK is ON and it will be off when CAPSLOCK is OFF.

In Mode 2, the keyboard will have inverted behaviour (i.e), the CAPSL led will glow when CAPSLOCK id OFF and it will be off when CAPSLOCK is ON.

The keyboard can transition from Mode 1 to Mode 2 only if the CAPSLOCK is OFF.

To install the driver,

1) Find the device id from /sys/bus/usb/devices(run display_driver.sh).

2) Compile the module and install it (run changeKeyboardDriver.sh).

3) Unbind the USBHID driver from the keyboad and bind it with USBKBD driver (run unbind_bind.sh after adding the correct device id in the script).
