/* Copyright 2018 ENDO Katsuhiro <ka2hiro@curlybracket.co.jp>
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */
#include QMK_KEYBOARD_H

// Defines the keycodes used by our macros in process_record_user
#define _QWERTY 0
#define _LOWER 1
#define _RAISE 2
#define _ADJUST 16

enum custom_keycodes {
  QWERTY = SAFE_RANGE,
  LOWER,
  RAISE,
  ADJUST,
  IMEON,
  IMEOFF,
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

[_QWERTY] = LAYOUT_split_3x5_3( \
  KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,         KC_Y,    KC_U,   KC_I,    KC_O,    KC_P,    \
  KC_A,    KC_S,    KC_D,    KC_F,    KC_G,         KC_H,    KC_J,   KC_K,    KC_L,    KC_RCTL, \
  KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,         KC_N,    KC_M,   KC_COMM, KC_DOT,  KC_RSFT, \
                    KC_LALT, KC_LGUI, KC_LSFT,      KC_TAB, KC_SPC, KC_MINS \
),

[_LOWER] = LAYOUT_split_3x5_3( \
  IMEOFF, IMEON, KC_LBRC, KC_RBRC, KC_QUOT,      KC_ESC,  KC_HOME, KC_UP,   KC_END,   KC_ENT,  \
  KC_LT,  KC_GT, KC_LCBR, KC_RCBR, KC_DQUO,      KC_NO,   KC_LEFT,  KC_DOWN, KC_RIGHT, _______, \
  KC_NO,  KC_NO, KC_LPRN, KC_RPRN, KC_SCLN,      KC_BSPC, KC_NO,    KC_NO,   KC_DEL,   _______, \
                 _______, _______, _______,      _______,  _______, _______\
),

[_RAISE] = LAYOUT_split_3x5_3( \
  KC_1,    KC_2,    KC_3,    KC_4,    KC_5,         KC_6,    KC_7,    KC_8,    KC_9,  KC_0,  \
  KC_EXLM, KC_AT,   KC_HASH, KC_DLR,  KC_PERC,      KC_CIRC, KC_AMPR, KC_ASTR, KC_NO, KC_NO, \
  KC_SLSH, KC_BSLS, KC_EQL,  KC_NO,   KC_GRV,        KC_NO,   KC_NO,   KC_NO,   KC_NO, KC_NO, \
                    _______, _______, _______,      _______, _______, _______                \
 ),

[_ADJUST] =  LAYOUT_split_3x5_3( \
  KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,        KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10, \
  KC_F11,  KC_F12,  _______, _______, _______,      _______, _______, _______, _______, _______, \
  RESET,   _______, _______, _______, _______,      _______, _______, _______, _______, _______, \
                    _______, _______, _______,      _______, _______, _______                   \
)
};

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  static uint16_t mem_keycode;
  uint16_t prev_keycode = mem_keycode;
  bool is_tapped = ((!record->event.pressed) && (keycode == prev_keycode));
  if (record->event.pressed) {
    mem_keycode = keycode;
  }

  switch (keycode) {
    case QWERTY:
      if (record->event.pressed) {
        // persistant_default_layer_set(1UL<<_QWERTY);
        set_single_persistent_default_layer(_QWERTY);
      }
      return false;
      break;
    case IMEON:
      if (record->event.pressed) {
        register_code(KC_HENK);
        register_code(KC_LANG1);
      } else {
        unregister_code(KC_HENK);
        unregister_code(KC_LANG1);
      }
      break;
    case IMEOFF:
      if (record->event.pressed) {
        register_code(KC_MHEN);
        register_code(KC_LANG2);
      } else {
        unregister_code(KC_MHEN);
        unregister_code(KC_LANG2);
      }
      break;
    case LOWER:
      if (record->event.pressed) {
        layer_on(_LOWER);
        update_tri_layer(_LOWER, _RAISE, _ADJUST);
      } else {
        layer_off(_LOWER);
        update_tri_layer(_LOWER, _RAISE, _ADJUST);
      }
      return false;
      break;
    case RAISE:
      if (record->event.pressed) {
        layer_on(_RAISE);
        update_tri_layer(_LOWER, _RAISE, _ADJUST);
      } else {
        layer_off(_RAISE);
        update_tri_layer(_LOWER, _RAISE, _ADJUST);
      }
      return false;
      break;
    case KC_SPC:
      if (record->event.pressed) {
        layer_on(_LOWER);
        update_tri_layer(_LOWER, _RAISE, _ADJUST);
      } else {
        layer_off(_LOWER);
        update_tri_layer(_LOWER, _RAISE, _ADJUST);
        if (is_tapped) {
          tap_code(keycode);
        }
      }
      return false;
      break;
    case KC_TAB:
      if (record->event.pressed) {
        layer_on(_RAISE);
        update_tri_layer(_LOWER, _RAISE, _ADJUST);
      } else {
        layer_off(_RAISE);
        update_tri_layer(_LOWER, _RAISE, _ADJUST);
        if (is_tapped) {
          tap_code(keycode);
        }
      }
      return false;
      break;
  }
  return true;
}

void matrix_init_user(void) {
}

void matrix_scan_user(void) {
}

void led_set_user(uint8_t usb_led) {
}
