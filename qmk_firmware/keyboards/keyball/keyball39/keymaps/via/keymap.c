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

#include QMK_KEYBOARD_H

#include "quantum.h"

#include "os_detection.h"

// clang-format off
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  // keymap for default (VIA)
  [0] = LAYOUT_universal(
    KC_TAB   , KC_W     , LALT(KC_E), KC_R    , KC_T     ,                           KC_Y     , KC_U     , KC_I     , KC_O     , LT(1,KC_P)  ,
    LCTL_T(KC_A), KC_S  , KC_D     , KC_F     , KC_G     ,                            KC_H     , KC_J     , KC_K     , KC_L     , LT(2,KC_ENT),
    LSFT_T(KC_Z), KC_X  , KC_C     , KC_V     , KC_B     ,                            KC_N     , KC_M     , LALT_T(KC_COMM), LSFT_T(KC_DOT), LT(3,KC_MINS),
    KC_Q     , KC_LSFT  , KC_LALT  , KC_LALT  , LGUI_T(KC_LNG2), LT(3,KC_SPC), KC_LSFT, LT(2,KC_LNG1),    KC_TRNS  , KC_TRNS  , KC_TRNS  , KC_SLSH
  ),

  [1] = LAYOUT_universal(
    KC_TRNS  , KC_TRNS  , KC_TRNS  , KC_TRNS  , KC_TRNS  ,                            KC_TRNS  , KC_MUTE  , KC_VOLD  , KC_VOLU  , KC_TRNS  ,
    KC_TRNS  , KC_TRNS  , KC_TRNS  , KC_TRNS  , KC_TRNS  ,                            KC_TRNS  , KC_TRNS  , KC_TRNS  , KC_TRNS  , KC_TRNS  ,
    KC_TRNS  , KC_TRNS  , KC_TRNS  , KC_TRNS  , KC_TRNS  ,                            KC_TRNS  , KC_MS_BTN3, KC_MS_BTN1, KC_MS_BTN2, KC_TRNS,
    KC_TRNS  , KC_TRNS  , KC_TRNS  , KC_TRNS  , KC_TRNS  , KC_TRNS  , KC_TRNS      , KC_TRNS  , KC_TRNS  , KC_TRNS   , KC_TRNS  , KC_TRNS
  ),

  [2] = LAYOUT_universal(
    KC_CIRC  , KC_7     , KC_8     , KC_9     , KC_EQL   ,                            KC_RBRC  , KC_PGUP  , KC_PGUP  , KC_PGDN  , KC_BSPC  ,
    KC_DLR   , KC_4     , KC_5     , KC_6     , KC_PLUS  ,                        KC_LEFT  , KC_DOWN  , KC_UP    , KC_RGHT  , KC_COLN  ,
    KC_0     , KC_1     , KC_2     , KC_3     , KC_EQL   ,                        KC_RCBR  , KC_MS_BTN4, KC_MS_BTN3, KC_MS_BTN5, KC_TRNS,
    KC_ESC   , KC_0     , KC_BSLS  , KC_BSPC  , KC_ESC   , KC_BSPC  , KC_TRNS      , KC_ENT   , KC_TRNS   , KC_TRNS  , KC_TRNS  , KC_TRNS
  ),

  [3] = LAYOUT_universal(
    RGB_TOG  , KC_DQUO  , KC_EQL   , KC_LPRN  , KC_TILD  ,                            KC_GRV   , KC_RPRN  , KC_PIPE  , KC_ASTR  , KC_PERC  ,
    KC_AT    , KC_QUOT  , KC_DLR   , KC_LBRC  , KC_MINS  ,                            KC_HASH  , KC_RBRC  , KC_F12   , KC_PLUS  , KC_SCLN  ,
    KC_EXLM  , KC_QUES  , KC_CIRC  , KC_LCBR  , KC_BSLS  ,                            KC_AMPR  , KC_RCBR  , KC_LABK  , KC_RABK  , KC_SLSH  ,
    AML_TO   , KBC_SAVE , KC_TRNS  , KC_TRNS  , KBC_SAVE , KC_TRNS  , KC_BSPC  , KC_TRNS      , KC_TRNS   , KC_TRNS  , KC_TRNS  , QK_BOOT 
  ),
};
// clang-format on

layer_state_t layer_state_set_user(layer_state_t state) {
    // Auto enable scroll mode when the highest layer is 3
    keyball_set_scroll_mode(get_highest_layer(state) == 3);
    return state;
}

#ifdef OLED_ENABLE

#    include "lib/oledkit/oledkit.h"

void oledkit_render_info_user(void) {
    keyball_oled_render_keyinfo();
    keyball_oled_render_ballinfo();
    keyball_oled_render_layerinfo();
}
#endif

// OS検出してスクロール向き等を変更
#if defined(OS_DETECTION_ENABLE) && defined(DEFERRED_EXEC_ENABLE)
uint32_t os_detect_callback(uint32_t trigger_time, void *cb_arg)
{
#if defined(MAGIC_KEYCODE_ENABLE) || defined(KEYBALL_KEEP_MAGIC_FUNCTIONS)
  keymap_config.raw = eeconfig_read_keymap();
#endif
  switch (detected_host_os())
  {
  case OS_MACOS:
  {
    uint8_t mode = 0;
    keyball_set_scroll_reverse_mode(mode);
#if defined(MAGIC_KEYCODE_ENABLE) || defined(KEYBALL_KEEP_MAGIC_FUNCTIONS)
    keymap_config.swap_lalt_lgui = false;
    // keymap_config.swap_ralt_rgui = false;
#endif
    break;
  }
  case OS_WINDOWS:
  {
    uint8_t mode = KEYBALL_SCROLL_REVERSE_VERTICAL | KEYBALL_SCROLL_REVERSE_HORIZONTAL;
    keyball_set_scroll_reverse_mode(mode);
#if defined(MAGIC_KEYCODE_ENABLE) || defined(KEYBALL_KEEP_MAGIC_FUNCTIONS)
    keymap_config.swap_lalt_lgui = true;
    // keymap_config.swap_ralt_rgui = true;
#endif
    break;
  }
  default:
    break;
  }
#if defined(MAGIC_KEYCODE_ENABLE) || defined(KEYBALL_KEEP_MAGIC_FUNCTIONS)
  eeconfig_update_keymap(keymap_config.raw);
#endif
  return 0;
}
#endif

// ジョイスティックの設定はkeyball.cで定義済み

// 以前の実装用の変数（現在は使用していない）
// static bool alt_pressed = false;
// static bool cmd_pressed = false;
// static bool shift_pressed = false;
// static bool layer2_on = false;
// static bool layer3_on = false;

// ジョイスティックの状態を追跡する変数
static uint16_t joystick_x = 0;
static uint16_t joystick_y = 0;
static bool joystick_key_mode_active = true; // デフォルトでジョイスティックキーモードを有効に

// キーの状態を追跡する変数
static bool key_pressed[256] = {false}; // すべてのキーコードに対応

// カスタムキーコード定義
enum custom_keycodes {
    JS_DEBUG = SAFE_RANGE,
};

void keyboard_post_init_user(void)
{
#if defined(OS_DETECTION_ENABLE) && defined(DEFERRED_EXEC_ENABLE)
    defer_exec(100, os_detect_callback, NULL);
#endif

    // EEPROMをリセット
    // eeconfig_init();

    // ジョイスティックのピンを明示的に設定
    if (is_keyboard_left()) {
        setPinInput(B5); // X軸
        setPinInput(B6); // Y軸
    }
}

// ジョイスティックの処理をprocess_record_user関数で実装
bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    // キーの状態を追跡
    uint8_t kc = keycode & 0xFF; // 下位8ビットのみを使用
    
    if (record->event.pressed) {
        key_pressed[kc] = true;
    } else {
        key_pressed[kc] = false;
    }
    
    switch (keycode) {
        case JS_DEBUG:
            if (record->event.pressed) {
                // ジョイスティックキーモードの切り替え
                joystick_key_mode_active = !joystick_key_mode_active;
            }
            return false;
        default:
            return true;
    }
}

// ジョイスティックの値を読み取る関数
void read_joystick_values(void) {
    if (!is_keyboard_left()) return;
    
    // ジョイスティックの値を読み取る
    joystick_x = joystick_read_axis(0);
    joystick_y = joystick_read_axis(1);
}

// キーがキーボードから押されているかどうかをチェックする関数
bool is_key_pressed_by_keyboard(uint8_t keycode) {
    return key_pressed[keycode];
}

// ジョイスティックによるキー操作を行う関数
void joystick_key_action(uint8_t keycode, bool pressed) {
    if (pressed) {
        register_code(keycode);
    } else {
        // キーがキーボードから押されていない場合のみunregister
        if (!is_key_pressed_by_keyboard(keycode)) {
            unregister_code(keycode);
        }
    }
}

// matrix_scan_user関数でジョイスティックの値を読み取る
void matrix_scan_user(void) {
    static uint32_t joystick_timer = 0;
    static bool js_shift_active = false;
    static bool js_alt_active = false;
    static bool js_gui_active = false;
    static bool js_layer2_active = false;
    
    // 20msごとにジョイスティックの値を読み取る（より高速に）
    if (timer_elapsed32(joystick_timer) > 20) {
        joystick_timer = timer_read32();
        read_joystick_values();
        
        // ジョイスティックキーモードがアクティブな場合、ジョイスティックの値に応じてキーを押す
        if (joystick_key_mode_active) {
            // デッドゾーンを大きくする
            const int16_t deadzone = JOYSTICK_KEY_TH;
            
            // X軸の処理（左右）
            bool new_shift_active = joystick_x > deadzone;
            if (new_shift_active != js_shift_active) {
                joystick_key_action(KC_LSFT, new_shift_active);
                js_shift_active = new_shift_active;
            }
            
            // 左方向の閾値を大きくする
            bool new_layer2_active = joystick_x < -deadzone * 1.5;
            if (new_layer2_active != js_layer2_active) {
                if (new_layer2_active) {
                    layer_on(2);
                } else {
                    layer_off(2);
                }
                js_layer2_active = new_layer2_active;
            }
            
            // Y軸の処理（上下）
            bool new_gui_active = joystick_y > deadzone;
            if (new_gui_active != js_gui_active) {
                joystick_key_action(KC_LGUI, new_gui_active);
                js_gui_active = new_gui_active;
            }
            
            bool new_alt_active = joystick_y < -deadzone;
            if (new_alt_active != js_alt_active) {
                joystick_key_action(KC_LALT, new_alt_active);
                js_alt_active = new_alt_active;
            }
        }
    }
}
