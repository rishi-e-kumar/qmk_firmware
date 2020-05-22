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
#define _MOVE 5
#define _NUM 6
#define _ADJUST 16


enum custom_keycodes {
  QWERTY = SAFE_RANGE,
  COLEMAK,
  DVORAK
};

#define LOWER  MO(_LOWER)
#define RAISE  MO(_RAISE)
#define ADJUST MO(_ADJUST)
#define MOVE   MO(_MOVE)

//keystroke logging code
unsigned char current_word[50];
int current_word_length = 0;

void SEND_STORED(void) {
  for (int i = 0; i < current_word_length-2; i++){
    tap_code(current_word[i]);
  }
}

void CLEAR_STORED(void) {
  for (int i = 0; i < current_word_length-2; i++){
    tap_code(KC_BSPC);
  }
}

void RESET_STORED(void) {
  current_word_length = 0;
}

//start keymaps

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
/* Qwerty */
[_QWERTY] = LAYOUT(
    KC_ESC,   KC_1,   KC_2,   KC_3,   KC_4,   KC_5,               KC_6,   KC_7,   KC_8,   KC_9,   KC_0,   KC_BSPC, \
    KC_TAB,   KC_Q,   KC_W,   KC_E,   KC_R,   KC_T,               KC_Y,   KC_U,   KC_I,   KC_O,   KC_P,   KC_COMM, \
    KC_LCTL,  KC_A,   KC_S,   KC_D,   KC_F,   KC_G,               KC_H,   KC_J,   KC_K,   KC_L,   KC_SCLN,KC_DOT, \
    KC_LSFT,  KC_Z,   KC_X,   KC_C,   KC_V,   KC_B,               KC_N,   KC_M,   KC_COMM,KC_DOT, KC_SLSH,KC_LEAD, \
    KC_LGUI,LT(_MOVE, KC_SPC), LT(_LOWER, KC_SPC), MO(_NUM),      KC_RALT,  LT(_RAISE, KC_BSPC),LSFT_T(KC_ENT)   \
),

/* Move */
[_MOVE] = LAYOUT(
   KC_ESC,XXXXXXX,XXXXXXX,XXXXXXX,XXXXXXX,XXXXXXX,                XXXXXXX,XXXXXXX,XXXXXXX,XXXXXXX,XXXXXXX,XXXXXXX, \
   A(KC_TAB),XXXXXXX,XXXXXXX,XXXXXXX,XXXXXXX,XXXXXXX,             KC_HOME,KC_PGDN,KC_PGUP,KC_END ,XXXXXXX,XXXXXXX ,\
   KC_LCTL,XXXXXXX,KC_LALT,KC_LSFT,KC_LCTL,KC_LGUI,               KC_LEFT,KC_DOWN,KC_UP,KC_RGHT,XXXXXXX,XXXXXXX, \
   KC_LSFT,XXXXXXX,C(KC_X),C(KC_C),C(KC_V),XXXXXXX,               C(G(KC_LEFT)),XXXXXXX,XXXXXXX,C(G(KC_RGHT)),C(KC_SLSH), KC_RSFT, \
   KC_LGUI,LT(_MOVE, KC_SPC), LT(_LOWER, KC_SPC), MO(_NUM),      KC_RALT,  LT(_RAISE, KC_BSPC),LSFT_T(KC_ENT)   \
),


/* Lower */
[_LOWER] = LAYOUT(
   KC_ESC,XXXXXXX,XXXXXXX,XXXXXXX,XXXXXXX,XXXXXXX,        XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,  XXXXXXX, \
   KC_TAB,XXXXXXX,XXXXXXX,XXXXXXX,XXXXXXX,KC_COLN,        KC_COLN,KC_LBRC, KC_RBRC, KC_DQUO, XXXXXXX, XXXXXXX, \
   KC_LCTL,XXXXXXX,KC_HASH,KC_UNDS,KC_COLN,KC_UNDS,       KC_UNDS,KC_LPRN,KC_RPRN, KC_QUOT, KC_AT, XXXXXXX, \
   KC_LSFT,XXXXXXX,XXXXXXX,XXXXXXX,XXXXXXX,XXXXXXX,       KC_HASH,KC_LCBR,KC_RCBR,XXXXXXX,XXXXXXX,XXXXXXX, \
    KC_LGUI,LT(_MOVE, KC_SPC), LT(_LOWER, KC_SPC), MO(_NUM),      KC_RALT,  LT(_RAISE, KC_DEL),LSFT_T(KC_ENT)   \
),

/* Raise */
[_RAISE] = LAYOUT(
  KC_ESC,  KC_F1  ,KC_F2   ,KC_F3  ,  KC_F4 ,  KC_F5,         KC_F6,  KC_F7,  KC_F8,  KC_F9  ,KC_F10, KC_F11 , \
  KC_TAB , KC_BSLS, KC_EXLM, KC_TILD, KC_AMPR, KC_COLN,       XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,  KC_F12, \
  KC_LCTL , KC_SLSH, KC_MINS, KC_EQL, KC_PLUS, KC_ASTR,       XXXXXXX, KC_VOLD, KC_MUTE, KC_VOLU,XXXXXXX,  XXXXXXX, \
  KC_LSFT , KC_PERC, KC_LABK, KC_PIPE, KC_RABK, KC_CIRC,       XXXXXXX, KC_MPRV, KC_MPLY, KC_MNXT,XXXXXXX, KC_RSFT, \
    KC_LGUI,LT(_MOVE, KC_SPC), LT(_LOWER, KC_SPC), MO(_NUM),      KC_RALT,  LT(_RAISE, KC_DEL),LSFT_T(KC_ENT)   \

),

/* Numeric */
[_NUM] = LAYOUT(
  XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,        XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, \
  XXXXXXX, KC_AT, KC_EXLM, KC_TILD, KC_AMPR, KC_COLN,        XXXXXXX, KC_7, KC_8, KC_9, XXXXXXX, XXXXXXX, \
  XXXXXXX, KC_SLSH, KC_MINS, KC_EQL, KC_PLUS, KC_ASTR,        XXXXXXX, KC_4, KC_5, KC_6, KC_COMM, XXXXXXX, \
  XXXXXXX, KC_PERC, KC_RABK, KC_PIPE, KC_LABK, KC_CIRC,        KC_MINS, KC_1, KC_2, KC_3, KC_DOT, KC_ENT, \
    KC_LGUI,LT(_MOVE, KC_SPC), LT(_LOWER, KC_SPC), MO(_NUM),      KC_RALT,  LT(_RAISE, KC_BSPC),KC_0   \

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
[_ADJUST] =  LAYOUT(
  XXXXXXX, RESET,   XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,                      XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, \
  XXXXXXX, XXXXXXX, MAGIC_UNSWAP_CTL_GUI, XXXXXXX, XXXXXXX, XXXXXXX,         XXXXXXX, KC_ASRP, KC_ASTG, XXXXXXX,  XXXXXXX, XXXXXXX, \
  XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,                      XXXXXXX, KC_ASDN, KC_ASUP, XXXXXXX, XXXXXXX, XXXXXXX, \
  XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,                      XXXXXXX, MAGIC_SWAP_CTL_GUI, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, \
  KC_LGUI,LT(_LOWER, KC_SPC), LT(_MOVE, KC_SPC), KC_LALT,                    KC_RCTL,  LT(_NUM, KC_BSPC),LT(_RAISE, KC_ENT)   \
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
    case LCTL_T(KC_ENT):
    case LT(_MOVE, KC_SPC):
    case LSFT_T(KC_DEL):
      current_word_length = 0;
      return true;
    default:
    //   if ((record->event.pressed) && (current_word_length < 49)) {
    //     current_word[current_word_length++] = keycode;
    //   }
      return true;
  }
  return true;
}

void post_process_record_user(uint16_t keycode, keyrecord_t *record) {
  switch (keycode) {
    case KC_ENT:
    case KC_SPC:
      RESET_STORED();
      break;
    default:
      if (!(record->event.pressed) && (current_word_length < 49)) {
        current_word[current_word_length++] = keycode;
      }
  }
}


LEADER_EXTERNS();
  void matrix_scan_user(void) {
    LEADER_DICTIONARY() {
      leading = false;
      leader_end();
      /* python (P) */
        //python imports (P->I)
      SEQ_THREE_KEYS(KC_P, KC_I, KC_N) {
        SEND_STRING("import numpy as np\n");;
      }
      SEQ_THREE_KEYS(KC_P, KC_I, KC_M) {
        SEND_STRING("import matplotlib.pyplot as plt\n");;
      }
      SEQ_THREE_KEYS(KC_P, KC_I, KC_P) {
        SEND_STRING("import pandas as pd\n");;
      }
      SEQ_THREE_KEYS(KC_P, KC_I, KC_A) { //import all basic functions
        SEND_STRING("import matplotlib.pyplot as plt\n"
                    "import numpy as np\n"
                    "import seaborn as sns\n"
                    "import pandas as pd\n");;
      }
      SEQ_TWO_KEYS(KC_P, KC_C) {
        CLEAR_STORED();
        SEND_STRING("class ");
        SEND_STORED();
        SEND_STRING("():\n"
                    "\tdef __init__():\n"
                    "\t\t"
        );
        RESET_STORED();
      }
      SEQ_ONE_KEY(KC_R) {
        // char msg[50];
        // sprintf(msg, "%i characters", current_word_length);
        // SEND_STRING(msg);
        for (int i = 0; i < current_word_length-2; i++){
          tap_code(current_word[i]);
        }
        current_word_length = 0;
      }
    }
  }


