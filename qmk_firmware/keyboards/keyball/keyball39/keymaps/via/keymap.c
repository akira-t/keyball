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
#include "os_detection.h"
#ifdef SPLIT_KEYBOARD
#include "transactions.h"
#endif

// clang-format off
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  // keymap for default (VIA)
  [0] = LAYOUT_universal(
    KC_TAB   , KC_W     , LALT_T(KC_E), KC_R    , KC_T     ,                           KC_Y     , KC_U     , KC_I     , KC_O     , LT(1,KC_P)  ,
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
    KC_AT    , KC_QUOT  , KC_DLR   , KC_LBRC  , KC_UNDS  ,                            KC_HASH  , KC_RBRC  , KC_F12   , KC_PLUS  , KC_SCLN  ,
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

// スプリットキーボードでジョイスティック情報を転送する
#ifdef SPLIT_KEYBOARD
#define JS_SYNC_ID 0x30

typedef struct {
    int16_t x;
    int16_t y;
} joystick_sync_t;

void joystick_slave_send_data(void);
void joystick_master_receive_handler(uint8_t in_buflen, const void* in_data, uint8_t out_buflen, void* out_data);
#endif

// ジョイスティックの設定はkeyball.cで定義済み

// 以前の実装用の変数（現在は使用していない）
// static bool alt_pressed = false;
// static bool cmd_pressed = false;
// static bool shift_pressed = false;
// static bool layer2_on = false;
// static bool layer3_on = false;

// ジョイスティックの状態を追跡する変数
static int16_t joystick_x = 0;
static int16_t joystick_y = 0;
static bool joystick_key_mode_active = true; // デフォルトでジョイスティックキーモードを有効に

// Hat Switchの方向定義
enum joystick_hat_direction {
    HAT_CENTER = 0,
    HAT_UP = 1,
    HAT_UP_RIGHT = 2,
    HAT_RIGHT = 3,
    HAT_DOWN_RIGHT = 4,
    HAT_DOWN = 5,
    HAT_DOWN_LEFT = 6,
    HAT_LEFT = 7,
    HAT_UP_LEFT = 8
};

// キーの状態を追跡する変数
static bool key_pressed[256] = {false}; // すべてのキーコードに対応

// カスタムキーコード定義
enum custom_keycodes {
    JS_DEBUG = SAFE_RANGE,
};

// keyboard_post_init_user関数でトランザクションハンドラを登録
#ifdef SPLIT_KEYBOARD
void keyboard_post_init_user(void) {
    // マスターのみがハンドラを登録
    if (is_keyboard_master()) {
        transaction_register_rpc(JS_SYNC_ID, joystick_master_receive_handler);
    }
    
    #if defined(OS_DETECTION_ENABLE) && defined(DEFERRED_EXEC_ENABLE)
        defer_exec(100, os_detect_callback, NULL);
    #endif

    // ジョイスティックのピンを明示的に設定
    if (is_keyboard_left()) {
        setPinInput(B5); // X軸
        setPinInput(B6); // Y軸
    }
}
#else
void keyboard_post_init_user(void) {
    #if defined(OS_DETECTION_ENABLE) && defined(DEFERRED_EXEC_ENABLE)
        defer_exec(100, os_detect_callback, NULL);
    #endif

    // ジョイスティックのピンを明示的に設定
    if (is_keyboard_left()) {
        setPinInput(B5); // X軸
        setPinInput(B6); // Y軸
    }
}
#endif

// Hat Switchの状態に応じてキー登録を行う関数（共通キーは保持する改良版）
void process_joystick_hat(uint8_t hat_state) {
    static uint8_t prev_hat_state = HAT_CENTER;
    static bool shift_active = false;
    static bool ctrl_active = false;
    static bool alt_active = false;
    static bool gui_active = false;
    
    if (hat_state == prev_hat_state) {
        return; // 状態に変化がなければ何もしない
    }
    
    // 現在の方向に必要なキー状態を決定
    bool need_shift = false;
    bool need_ctrl = false;
    bool need_alt = false;
    bool need_gui = false;
    
    switch (hat_state) {
        case HAT_UP:
            need_shift = true;
            break;
        case HAT_UP_RIGHT:
            need_shift = true;
            need_alt = true;
            break;
        case HAT_RIGHT:
            need_alt = true;
            break;
        case HAT_DOWN_RIGHT:
            need_gui = true;
            need_shift = true;
            break;
        case HAT_DOWN:
            need_gui = true;
            break;
        case HAT_DOWN_LEFT:
            need_gui = true;
            need_ctrl = true;
            break;
        case HAT_LEFT:
            need_ctrl = true;
            break;
        case HAT_UP_LEFT:
            need_shift = true;
            need_ctrl = true;
            break;
    }
    
    // 必要に応じてキーを押す/離す（状態が変わる場合のみ）
    if (need_shift != shift_active) {
        if (need_shift) {
            register_code(KC_LSFT);
        } else {
            unregister_code(KC_LSFT);
        }
        shift_active = need_shift;
    }
    
    if (need_ctrl != ctrl_active) {
        if (need_ctrl) {
            register_code(KC_LCTL);
        } else {
            unregister_code(KC_LCTL);
        }
        ctrl_active = need_ctrl;
    }
    
    if (need_alt != alt_active) {
        if (need_alt) {
            register_code(KC_LALT);
        } else {
            unregister_code(KC_LALT);
        }
        alt_active = need_alt;
    }
    
    if (need_gui != gui_active) {
        if (need_gui) {
            register_code(KC_LGUI);
        } else {
            unregister_code(KC_LGUI);
        }
        gui_active = need_gui;
    }
    
    prev_hat_state = hat_state;
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

// トラックボールの速度倍率を計算する変数と関数
float current_speed_multiplier = 1.0; // staticを削除してグローバル変数にする

// ジョイスティックの下方向の値に基づいて速度倍率を更新する関数
void update_trackball_speed_multiplier(int16_t joystick_down_value) {
    // ジョイスティックの下方向の入力値をデッドゾーンからの相対値に変換
    // joystick_down_value は正の値（下方向）なので、そのまま使用
    int16_t value = joystick_down_value;
    
    // デッドゾーン以下の場合は倍率1.0（変更なし）
    const int16_t deadzone = JOYSTICK_DEADZONE;
    if (value <= deadzone) {
        current_speed_multiplier = 1.0;
        return;
    }
    
    // 入力値を0.0～1.0の範囲に正規化
    // JOYSTICK_KEY_THを超えた分を、最大値（512程度）までの間で正規化
    float normalized_value = (float)(value - deadzone) / (512.0 - deadzone);
    
    // 値の範囲を制限（0.0～1.0）
    if (normalized_value > 1.0) normalized_value = 1.0;
    
    // 1.0～5.0の範囲で倍率を計算（ここでは線形に変化）
    current_speed_multiplier = 1.0 + normalized_value * 4.0; // 最大5倍
}

// pointing_device_task関数の前処理として速度調整関数を定義
report_mouse_t pointing_device_task_kb(report_mouse_t mouse_report) {
    // ジョイスティックの上方向の入力があった場合のみ倍率を適用
    if (current_speed_multiplier > 1.0) {
        mouse_report.x = (int8_t)((float)mouse_report.x * current_speed_multiplier);
        mouse_report.y = (int8_t)((float)mouse_report.y * current_speed_multiplier);
        mouse_report.h = (int8_t)((float)mouse_report.h * current_speed_multiplier);
        mouse_report.v = (int8_t)((float)mouse_report.v * current_speed_multiplier);
    }
    
    // 元の処理に進む
    return pointing_device_task_user(mouse_report);
}

// スプリットキーボードでジョイスティック情報を転送する
#ifdef SPLIT_KEYBOARD
void joystick_slave_send_data(void) {
    if (!is_keyboard_left() || is_keyboard_master()) {
        return; // スレーブで左側のみ対応
    }
    
    joystick_sync_t data = {
        .x = joystick_x,
        .y = joystick_y
    };
    
    transaction_rpc_send(JS_SYNC_ID, sizeof(data), &data);
}

void joystick_master_receive_handler(uint8_t in_buflen, const void* in_data, uint8_t out_buflen, void* out_data) {
    if (!is_keyboard_master()) {
        return;
    }
    
    const joystick_sync_t *data = (const joystick_sync_t *)in_data;
    joystick_x = data->x;
    joystick_y = data->y;
}
#endif

// ジョイスティックの方向から Hat Switch の状態を取得
uint8_t get_joystick_hat_direction(int16_t x, int16_t y) {
    // デッドゾーンチェック
    const int16_t deadzone = JOYSTICK_KEY_TH;
    
    if (abs(x) <= deadzone && abs(y) <= deadzone) {
        return HAT_CENTER;
    }
    
    // 8方向の判定
    if (y < -deadzone) { // 上方向
        if (x < -deadzone) return HAT_UP_LEFT;
        else if (x > deadzone) return HAT_UP_RIGHT;
        else return HAT_UP;
    } else if (y > deadzone) { // 下方向
        if (x < -deadzone) return HAT_DOWN_LEFT;
        else if (x > deadzone) return HAT_DOWN_RIGHT;
        else return HAT_DOWN;
    } else { // 中央(y)
        if (x < -deadzone) return HAT_LEFT;
        else if (x > deadzone) return HAT_RIGHT;
        else return HAT_CENTER;
    }
}

// matrix_scan_user関数でジョイスティックの値を読み取る
void matrix_scan_user(void) {
    static uint32_t joystick_timer = 0;
    
    // 20msごとにジョイスティックの値を読み取る
    if (timer_elapsed32(joystick_timer) > 20) {
        joystick_timer = timer_read32();
        
        // 左手側のジョイスティック値を読み取る
        if (is_keyboard_left()) {
            read_joystick_values();
            
            #ifdef SPLIT_KEYBOARD
            // スレーブの場合はマスターに送信
            if (!is_keyboard_master()) {
                joystick_slave_send_data();
                return; // スレーブではここで処理を終了
            }
            #endif
        }
        
        // ジョイスティックキーモードがアクティブな場合
        if (joystick_key_mode_active && is_keyboard_master()) {
            // Hat Switch方式でキー状態を管理
            uint8_t hat_state = get_joystick_hat_direction(joystick_x, joystick_y);
            process_joystick_hat(hat_state);
            
            // 下方向の入力があった場合、トラックボールの速度倍率を更新
            if (joystick_y > JOYSTICK_DEADZONE) {
                update_trackball_speed_multiplier(joystick_y);
            } else {
                current_speed_multiplier = 1.0;
            }
        }
    }
}
