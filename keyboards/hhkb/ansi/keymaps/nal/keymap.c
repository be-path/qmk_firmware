/*  -*-  eval: (turn-on-orgtbl); -*-
 * default HHKB Layout
 */
#include QMK_KEYBOARD_H

#define BASE 0
#define KL_ARROW 1
#define KL_NUM 2

// result of process_record_user
#define PROCESS_OVERRIDE_BEHAVIOR   (false)
#define PROCESS_USUAL_BEHAVIOR      (true)

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [BASE] = LAYOUT(
        KC_ESC, KC_1, KC_2, KC_3, KC_4, KC_5, KC_6, KC_7, KC_8, KC_9, KC_0, KC_MINS, KC_EQL, KC_BSLS, KC_GRV,
        KC_TAB, KC_Q, KC_W, KC_E, KC_R, KC_T, KC_Y, KC_U, KC_I, KC_O, KC_P, KC_LBRC, KC_RBRC, KC_BSPC,
        KC_LCTL, KC_A, KC_S, KC_D, KC_F, KC_G, KC_H, KC_J, KC_K, KC_L, KC_SCLN, KC_QUOT, KC_ENT,
        KC_LSFT, KC_Z, KC_X, KC_C, KC_V, KC_B, KC_N, KC_M, KC_COMM, KC_DOT, KC_SLSH, KC_NO, KC_NO,
        KC_LALT, KC_LGUI, KC_SPC, MO(KL_NUM), KC_NO
    ),
    [KL_ARROW] = LAYOUT(
        KC_LANG2, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO,
        KC_LANG1, KC_NO, KC_NO, KC_SCLN, KC_QUOT, KC_NO, KC_NO, KC_NO, KC_UP, KC_DEL, KC_NO, KC_NO, KC_NO, KC_TRNS,
        KC_TRNS, KC_LPRN, KC_RPRN, KC_LBRC, KC_RBRC, KC_NO, KC_HOME, KC_LEFT, KC_DOWN, KC_RGHT, KC_END, KC_NO, KC_TRNS,
        KC_TRNS, KC_GRV, KC_BSLS, KC_EQL, KC_MINS, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_TRNS, KC_TRNS,
        KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS
    ),
    [KL_NUM] = LAYOUT(
        KC_TRNS, KC_PSLS, KC_PAST, KC_PMNS, KC_PPLS, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO,
        KC_TRNS, KC_PEQL, KC_7, KC_8, KC_9, KC_NO, KC_NO, KC_NO, KC_VOLU, KC_NO, KC_NO, KC_NO, KC_NO, KC_TRNS,
        KC_TRNS, KC_PDOT, KC_4, KC_5, KC_6, KC_NO, KC_MPLY, KC_MPRV, KC_VOLD, KC_MNXT, KC_NO, KC_NO, KC_TRNS,
        KC_TRNS, KC_P0, KC_1, KC_2, KC_3, KC_NO, KC_NO, KC_NO, KC_MUTE, KC_NO, KC_NO, KC_TRNS, KC_TRNS,
        KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS
    ),
};

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  static uint16_t mem_keycode;
  uint16_t prev_keycode = mem_keycode;
  bool is_tapped = ((!record->event.pressed) && (keycode == prev_keycode));
  if (record->event.pressed) {
    mem_keycode = keycode;
  }

  switch (keycode) {
    case KC_SPC: {
      if (record->event.pressed) {
        layer_on(KL_ARROW);
      }
      else {
        layer_off(KL_ARROW);
        if (is_tapped) {
          tap_code(keycode);
        }
      }
      return PROCESS_OVERRIDE_BEHAVIOR;
    } break;

    default: {
    } break;
  }

  return PROCESS_USUAL_BEHAVIOR;
}
