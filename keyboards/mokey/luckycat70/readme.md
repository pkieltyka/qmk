# luckycat70

STM32F103C8T6 keyboard.

* Keyboard Maintainer: [rhmokey](https://github.com/rhmokey)
* Hardware Supported: STM32F103C8T6

Make example for this keyboard (after setting up your build environment):

    make mokey/luckycat70:default

Flashing example for this keyboard:

    make mokey/luckycat70:default:flash

See the [build environment setup](https://docs.qmk.fm/#/getting_started_build_tools) and the [make instructions](https://docs.qmk.fm/#/getting_started_make_guide) for more information. Brand new to QMK? Start with our [Complete Newbs Guide](https://docs.qmk.fm/#/newbs).

## Bootloader

Enter the bootloader in 2 ways:

* **Physical reset button**: Briefly press the button: [boot] first, then press button: [reset]  on the back of the PCB
* **Keycode in layout**: Press the key mapped to `QK_BOOT` if it is available
