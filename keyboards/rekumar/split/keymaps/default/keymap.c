#include QMK_KEYBOARD_H

// Each layer gets a name for readability, which is then used in the keymap matrix below.
// The underscores don't mean anything - you can have a layer called STUFF or any other name.
// Layer names don't all need to be of the same length, obviously, and you can also skip them
// entirely and just use numbers.
#define _QWERTY 0
#define _COLEMAK 1
#define _DVORAK 2
#define _LOWER 3
#define _RAISE 4
#define _ADJUST 16

enum custom_keycodes {
  QWERTY = SAFE_RANGE,
  COLEMAK,
  DVORAK
};

#define LOWER  MO(_LOWER)
#define RAISE  MO(_RAISE)
#define ADJUST MO(_ADJUST)

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
/* Qwerty */
[_QWERTY] = LAYOUT(
    KC_ESC,   KC_1,   KC_2,   KC_3,   KC_4,   KC_5,     KC_6,   KC_7,   KC_8,   KC_9,   KC_0,   KC_BSPC, \
    KC_TAB,  KC_Q,   KC_W,   KC_E,   KC_R,   KC_T,     KC_Y,   KC_U,   KC_I,   KC_O,   KC_P,   KC_BSLS, \
    KC_LFST, KC_A,   KC_S,   KC_D,   KC_F,   KC_G,     KC_H,   KC_J,   KC_K,   KC_L,   KC_SCLN,KC_QUOT, \
    KC_LCTL, KC_Z,   KC_X,   KC_C,   KC_V,   KC_B,     KC_N,   KC_M,   KC_COMM,KC_DOT, KC_SLSH,KC_RSFT, \
                     KC_LGUI,KC_LALT, LSFT_T(KC_SPC), LOWER,    RAISE,  LCTL_T(KC_BSPC),LALT_T(KC_ENT)                          \
),


/* Lower */
[_LOWER] = LAYOUT( \
   KC_TILD,KC_F1  ,KC_F2  ,KC_F3,  KC_F4,  KC_F5,         KC_F6,  KC_F7,  KC_F8,  KC_F9  ,KC_F10, KC_F11 , \
   _______,_______,_______,_______,KC_PIPE,KC_LBRC,       KC_RBRC,KC_HOME,KC_PGUP,KC_PGDN,KC_END ,KC_F12 , \
   KC_LSFT,_______,_______,_______,KC_QUOT,KC_LPRN,       KC_RPRN,KC_LEFT,KC_UP  ,KC_DOWN,KC_RGHT,_______, \
   KC_LCTL,_______,_______,_______,_______,KC_LCBR,       KC_RCBR,C(G(KC_LEFT)),_______,_______,C(G(KC_RGHT)),KC_RSFT, \
                 KC_LGUI,KC_LALT, LSFT(KC_SPC), LOWER,  RAISE,  LCTL_T(KC_DEL), LALT_T(KC_ENT)                          \
),

/* Raise
 * ,-----------------------------------------------------------------------------------.
 * |   `  |   1  |   2  |   3  |   4  |   5  |   6  |   7  |   8  |   9  |   0  | Del  |
 * |------+------+------+------+------+-------------+------+------+------+------+------|
 * | Del  |  F1  |  F2  |  F3  |  F4  |  F5  |  F6  |   -  |   =  |   [  |   ]  |  \   |
 * |------+------+------+------+------+------|------+------+------+------+------+------|
 * |      |  F7  |  F8  |  F9  |  F10 |  F11 |  F12 |ISO # |ISO / |      |      |      |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      |      |      |      |      |             |      | Next | Vol- | Vol+ | Play |
 * `-----------------------------------------------------------------------------------'
 */
[_RAISE] = LAYOUT( \
  KC_GRV , _______, KC_BTN3, _______, _______, _______,    _______, _______, _______, _______, _______,  KC_DEL, \
  KC_WH_U, KC_BTN1, KC_MS_U, KC_BTN2, KC_CIRC, KC_ASTR,    KC_SLSH, KC_BSLS, _______, _______, _______, _______, \
  KC_WH_D, KC_MS_L, KC_MS_D, KC_MS_R, KC_AMPR, KC_PLUS,    KC_MINS, KC_TILD, KC_VOLD, KC_MUTE, KC_VOLU, _______, \
  _______, _______, _______, _______, _______, KC_LABK,    KC_RABK, _______, KC_MPRV, KC_MPLY, KC_MNXT, _______, \
                   KC_LGUI,KC_LALT, LSFT(KC_SPC), LOWER,   RAISE,  LCTL_T(KC_DEL), LALT_T(KC_ENT)                 \

),

/* Adjust (Lower + Raise)
 * ,-----------------------------------------------------------------------------------.
 * |      | Reset|      |      |      |      |      |      |      |      |      |  Del |
 * |------+------+------+------+------+-------------+------+------+------+------+------|
 * |      |      |      |Aud on|Audoff|AGnorm|AGswap|Qwerty|Colemk|Dvorak|      |      |
 * |------+------+------+------+------+------|------+------+------+------+------+------|
 * |      |      |      |      |      |      |      |      |      |      |      |      |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      |      |      |      |      |             |      |      |      |      |      |
 * `-----------------------------------------------------------------------------------'
 */
[_ADJUST] =  LAYOUT( \
  _______, RESET,   _______, _______, _______, _______,   _______, _______, _______, _______, _______, KC_DEL, \
  _______, _______, MAGIC_UNSWAP_CTL_GUI, _______, _______, _______,   _______, QWERTY , _______, _______,  _______, _______, \
  _______, _______, _______, _______, _______, _______,   _______, _______, _______, _______, _______, _______, \
  _______, _______, _______, _______, _______, _______,   _______, MAGIC_SWAP_CTL_GUI, _______, _______, _______, _______, \
                   KC_LGUI,KC_LALT, LSFT(KC_SPC), LOWER,   RAISE,  LCTL_T(KC_DEL), LALT_T(KC_ENT)                          \

)


};

layer_state_t layer_state_set_user(layer_state_t state) {
  return update_tri_layer_state(state, _LOWER, _RAISE, _ADJUST);
}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  switch (keycode) {
    case QWERTY:
      if (record->event.pressed) {
        set_single_persistent_default_layer(_QWERTY);
      }
      return false;
    case COLEMAK:
      if (record->event.pressed) {
        set_single_persistent_default_layer(_COLEMAK);
      }
      return false;
    case DVORAK:
      if (record->event.pressed) {
        set_single_persistent_default_layer(_DVORAK);
      }
      return false;
  }
  return true;
}


