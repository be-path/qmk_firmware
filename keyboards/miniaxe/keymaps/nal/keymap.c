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
enum layer_names {
    _QWERTY,
    _WIN,
    _LOWER,
    _RAISE,
    _ADJUST
};

enum custom_keycodes {
  QWERTY = SAFE_RANGE,
  LOWER,
  RAISE,
  ADJUST,
  IMEON,
  IMEOFF,
  THUMB_L1,
  THUMB_L2,
  THUMB_L2W,
  THUMB_L3,
  THUMB_R1,
  THUMB_R1W,
  THUMB_R2,
  THUMB_R3,
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  [_QWERTY] = LAYOUT_split_3x5_3( \
    LT(_ADJUST, KC_Q),    KC_W,    KC_E,    KC_R,    KC_T,         KC_Y,    KC_U,   KC_I,    KC_O,   KC_P, \
    KC_A,    KC_S,    KC_D,    KC_F,    KC_G,         KC_H,    KC_J,   KC_K,    KC_L,   KC_SCLN, \
    KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,         KC_N,    KC_M,   KC_COMM, KC_DOT, KC_SLSH, \
    THUMB_L1, THUMB_L2, LSFT_T(KC_TAB),                     THUMB_R1, THUMB_R2, THUMB_R3 \
  ),
  [_WIN] =  LAYOUT_split_3x5_3( \
    _______, _______, _______, _______, _______,      _______, _______, _______, _______, _______, \
    _______, _______, _______, _______, _______,      _______, _______, _______, _______, _______, \
    _______, _______, _______, _______, _______,      _______, _______, _______, _______, _______, \
    _______, THUMB_L2W, _______,                      LGUI_T(KC_SPC), _______, _______ \
  ),
  [_LOWER] = LAYOUT_split_3x5_3( \
    KC_TAB,  KC_NO,   KC_LBRC, KC_RBRC, KC_QUOT,     KC_ESC,  KC_HOME, KC_UP,   KC_DEL,   KC_ENT, \
    KC_MINS, KC_UNDS, KC_LCBR, KC_RCBR, KC_DQUO,     KC_HOME, KC_LEFT, KC_DOWN, KC_RIGHT, KC_END, \
    KC_LT,   KC_GT,   KC_LPRN, KC_RPRN, KC_EQL,      KC_BSPC, KC_NO,   KC_NO,   KC_DEL,   KC_NO, \
    _______, _______, _______,                       _______,  _______, _______ \
  ),
  [_RAISE] = LAYOUT_split_3x5_3( \
    KC_DOT, KC_7, KC_8, KC_9, KC_NO,      KC_NO,  KC_AMPR, KC_ASTR, KC_BSLS, KC_NO, \
    KC_MINS, KC_4, KC_5, KC_6, KC_NO,      KC_NO,  KC_DLR,  KC_PERC, KC_CIRC, KC_NO, \
    KC_0,  KC_1, KC_2, KC_3, KC_EQL,      KC_GRV, KC_EXLM, KC_AT,   KC_HASH, KC_NO, \
    _______, _______, _______,           _______, _______, _______ \
  ),
  [_ADJUST] = LAYOUT_split_3x5_3( \
    KC_NO,  LGUI(KC_LBRC), LGUI(KC_RBRC), LGUI(KC_Q), KC_NO,      KC_NO,  KC_NO, KC_NO, KC_NO, KC_NO, \
    KC_NO,  KC_NO, KC_NO, KC_NO, KC_NO,      KC_NO,  KC_NO, KC_NO, KC_NO, KC_NO, \
    KC_NO,  KC_NO, KC_NO, KC_NO, KC_NO,      KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, \
    RCS(KC_TAB), LCTL(KC_TAB), LSFT(KC_TAB),               TG(_WIN), _______, RESET \
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
    case THUMB_L1:
      if (record->event.pressed) {
        register_code(KC_LALT);
      } else {
        unregister_code(KC_LALT);
        if (is_tapped) {
          tap_code(KC_HENK);
          tap_code(KC_LANG1);
        }
      }
      break;
    case THUMB_L2:
      if (record->event.pressed) {
        register_code(KC_LGUI);
      } else {
        unregister_code(KC_LGUI);
      }
      break;
    case THUMB_L2W:
      if (record->event.pressed) {
        register_code(KC_LCTL);
      } else {
        unregister_code(KC_LCTL);
      }
      break;
    case THUMB_L3:
      if (record->event.pressed) {
        register_code(KC_LSFT);
      } else {
        unregister_code(KC_LSFT);
        if (is_tapped) {
          tap_code(KC_TAB);
        }
      }
      break;
    case THUMB_R1:
      if (record->event.pressed) {
        register_code(KC_LCTL);
      } else {
        unregister_code(KC_LCTL);
        if (is_tapped) {
          tap_code(KC_SPC);
        }
      }
      break;
    case THUMB_R1W:
      if (record->event.pressed) {
        register_code(KC_LGUI);
      } else {
        unregister_code(KC_LGUI);
        if (is_tapped) {
          tap_code(KC_SPC);
        }
      }
      break;
    case THUMB_R2:
      if (record->event.pressed) {
        layer_on(_LOWER);
        //update_tri_layer(_LOWER, _RAISE, _ADJUST);
      } else {
        layer_off(_LOWER);
        //update_tri_layer(_LOWER, _RAISE, _ADJUST);
      }
      return false;
      break;
    case THUMB_R3:
      if (record->event.pressed) {
        layer_on(_RAISE);
        //update_tri_layer(_LOWER, _RAISE, _ADJUST);
      } else {
        layer_off(_RAISE);
        //update_tri_layer(_LOWER, _RAISE, _ADJUST);
        if (is_tapped) {
          tap_code(KC_MHEN);
          tap_code(KC_LANG2);
        }
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
        //update_tri_layer(_LOWER, _RAISE, _ADJUST);
      } else {
        layer_off(_LOWER);
        //update_tri_layer(_LOWER, _RAISE, _ADJUST);
      }
      return false;
      break;
    case RAISE:
      if (record->event.pressed) {
        layer_on(_RAISE);
        //update_tri_layer(_LOWER, _RAISE, _ADJUST);
      } else {
        layer_off(_RAISE);
        //update_tri_layer(_LOWER, _RAISE, _ADJUST);
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
