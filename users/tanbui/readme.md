# Overview
This is tanbui's workspace containing shared codes, keymaps and predefinitions for all 'ta-hc' othorlinear keyboards. The ideal is to reduce the amount of works required to consolidate layout between all of my keyboards everytime I add some changes.

## How to add and configure new keyboard/keymap linked to this shared userspace
- Create a new folder which's name is the name of your new keymap under \keyboards\<kb-name>\keymaps\<new-folder>. This folder should include:
    * config.h (optional)
    * keymap.c
    * rules.mk
    * readme.md (optional)
- By default the userspace used will be the same as the keymap name. If your new keymap's name is different from 'tanbui', add the following line to your rules.mk
    ```
    USER_NAME := tanbui
    ```
- Since tanbui\config.h is limited in including the needed header files (e.g. shortwrites.h), you have to add include header files in your keymap.
    
    Include These important headers in keymap.c:
    * #include "common.h"
    * #include "shortwrites.h"
- Check keymap's config.h file
    * TAPPING_TERM declared

## Build and flash your keymap
- General syntax: **~/qmk_firmware >** `make keyboard:<keymap-name>`
- Examples:
    * Preonic: `make preonic/rev3:ta-hc:dfu-util`
    * Planck: `make planck/rev6:ta-hc:dfu-util`

## Explain some issues:
### Try not to include QMK_KEYBOARD_H in config.h
There is some issue with 'make' when build the planck keyboard.
