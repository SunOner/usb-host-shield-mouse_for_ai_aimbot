# usb-host-shield-mouse
## This fork adds the ability to interact with an [Sunone Aimbot](https://github.com/SunOner/sunone_aimbot)
```
[USB Mouse] --> [USB Host Shield 2.0] --> [Arduino Leonardo] --> [FAKE HID USB] --> [Sunone Aimbot]
```

# Hardware Requirements
- Arduino Leonardo
- USB Host Shield 2.0
- Logitech G series mouse

# How to Use
1.  Connect the USB Host Shield to the Arduino Leonardo.
2.  Connect the Logitech mouse to the USB Host Shield.
3.  Upload the USBHostShieldMouse.ino sketch to the Arduino Leonardo.
4.  Edit `arduino_baudrate` to 115200 and `arduino_16_bit_mouse` to True in [config.ini](https://github.com/SunOner/sunone_aimbot/blob/main/config.ini).

> [!NOTE]
> The side buttons are emulated using the keyboard library. Reassign these keys in the games.

## arduino mouse pre-library is taken from [here](https://github.com/arduino-libraries/Mouse)