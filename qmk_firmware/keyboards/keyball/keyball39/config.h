/*
Copyright 2022 @Yowkees
Copyright 2022 MURAOKA Taro (aka KoRoN, @kaoriya)

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 2 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#pragma once

// Key matrix parameters
#define MATRIX_ROWS         (4 * 2)  // split keyboard
#define MATRIX_COLS         6
// #define EE_HANDS
// #define MASTER_RIGHT
#define MATRIX_ROW_PINS_RIGHT     { F4, F5, F6, F7 }
#define MATRIX_ROW_PINS     { F4, F5, F6, F7 }
#define MATRIX_COL_PINS_RIGHT     { D4, C6, D7, E6, B4, B5 }
#define MATRIX_COL_PINS     { D4, C6, D7, E6, B4, B3 }
// #define MATRIX_COL_PINS     { D4, C6, D7, E6, B4, B5 }
#define MATRIX_MASKED
#define DEBOUNCE            5
#define DIODE_DIRECTION     COL2ROW

// Split parameters
#define SOFT_SERIAL_PIN         D2
// #define SPLIT_HAND_MATRIX_GRID  F6, B5
#define SPLIT_HAND_MATRIX_GRID  F6, B3
#define SPLIT_USB_DETECT
#ifdef OLED_ENABLE
#    define SPLIT_OLED_ENABLE
#endif

// If your PC does not recognize Keyball, try setting this macro. This macro
// increases the firmware size by 200 bytes, so it is disabled by default, but
// it has been reported to work well in such cases.
//#define SPLIT_WATCHDOG_ENABLE

#define SPLIT_TRANSACTION_IDS_KB KEYBALL_GET_INFO, KEYBALL_GET_MOTION, KEYBALL_SET_CPI

// RGB LED settings
#define WS2812_DI_PIN       D3
#ifdef RGBLIGHT_ENABLE
#    define RGBLED_NUM      48
#    define RGBLED_SPLIT    { 24, 24 }  // (24 + 22)
#    ifndef RGBLIGHT_LIMIT_VAL
#        define RGBLIGHT_LIMIT_VAL  150 // limitated for power consumption
#    endif
#    ifndef RGBLIGHT_VAL_STEP
#        define RGBLIGHT_VAL_STEP   15
#    endif
#    ifndef RGBLIGHT_HUE_STEP
#        define RGBLIGHT_HUE_STEP   17
#    endif
#    ifndef RGBLIGHT_SAT_STEP
#        define RGBLIGHT_SAT_STEP   17
#    endif
#endif
#ifdef RGB_MATRIX_ENABLE
#    define RGB_MATRIX_SPLIT    { 24, 24 }
#endif

#ifndef OLED_FONT_H
#    define OLED_FONT_H "keyboards/keyball/lib/logofont/logofont.c"
#    define OLED_FONT_START 32
#    define OLED_FONT_END 195
#endif

#if !defined(LAYER_STATE_8BIT) && !defined(LAYER_STATE_16BIT) && !defined(LAYER_STATE_32BIT)
#    define LAYER_STATE_8BIT
#endif

// To squeeze firmware size
#undef LOCKING_SUPPORT_ENABLE
#undef LOCKING_RESYNC_ENABLE

#define KEYBALL_KEEP_MAGIC_FUNCTIONS  // windowsで⌘→alt用

// アナログ設定
#define ADC_CHANNEL_VREF ADC_REF_POWER
#define ANALOG_JOYSTICK_X_AXIS_PIN B5
#define ANALOG_JOYSTICK_Y_AXIS_PIN B6
#define ANALOG_JOYSTICK_AXIS_MIN 300

// Min 0, max 32
#define JOYSTICK_BUTTON_COUNT 1
// Min 0, max 6: X, Y, Z, Rx, Ry, Rz
#define JOYSTICK_AXIS_COUNT 2
// Min 8, max 16
#define JOYSTICK_AXIS_RESOLUTION 10
#define JOYSTICK_SPEED 20 // 移動速度の係数
// #define POINTING_DEVICE_INVERT_Y  // 機能せず
#define JOYSTICK_DEADZONE 30  // AMLのためのみ。他の場合はどこかで設定されているか不明　
#define ANALOG_JOYSTICK_WEIGHTS {0, 2, 4, 5, 7, 8, 9, 10, 12, 13, 14, 15, 15, 16, 17, 18, 18, 19, 19, 20, 20, 21, 21, 21, 22, 22, 22, 22, 23, 23, 23, 23, 23, 23, 23, 23, 23, 23, 23, 23, 23, 23, 23, 23, 23, 23, 23, 23, 23, 23, 24, 24, 24, 24, 24, 24, 25, 25, 25, 26, 26, 26, 27, 28, 28, 29, 29, 30, 31, 32, 33, 34, 35, 36, 37, 38, 40, 41, 43, 44, 46, 48, 49, 51, 53, 56, 58, 60, 62, 65, 68, 70, 73, 76, 79, 82, 85, 89, 92, 96, 100}
