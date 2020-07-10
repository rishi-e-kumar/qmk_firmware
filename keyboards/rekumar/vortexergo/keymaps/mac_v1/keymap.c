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
#define _MOUSE 5
#define _ADJUST 16


enum custom_keycodes {
  QWERTY = SAFE_RANGE,
  COLEMAK,
  DVORAK,
  RAISEBSPC,
  RAISEDEL,
  SFTSPC,
  CTL_EQL
};

#define LOWER  MO(_LOWER)
#define RAISE  MO(_RAISE)
#define ADJUST MO(_ADJUST)
#define SWNUM  MO(_SOLIDWORKS_NUM)
#define SFT_SPC SFT_T(KC_SPC)
#define GUI_A  GUI_T(KC_A)
#define ALT_S  ALT_T(KC_S)
#define CTL_D  CTL_T(KC_D)
#define SFT_F  SFT_T(KC_F)
#define GUI_DOT  GUI_T(KC_DOT)
#define ALT_L  ALT_T(KC_L)
#define CTL_K  CTL_T(KC_K)
#define SFT_J  SFT_T(KC_J)
#define RAISE_BSPC LT(_RAISE, KC_BSPC)

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

enum unicode_names {
    DEGREE,
    MU,
    DELTA
};

const uint32_t PROGMEM unicode_map[] = {
    [DEGREE]  = 0x00B0,
    [MU] = 0x03BC,
    [DELTA]  = 0x0394
};

//start keymaps

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
/* Qwerty */
[_QWERTY] = LAYOUT(
    KC_Q,   KC_W,   KC_E,   KC_R,   KC_T,               KC_Y,   KC_U,   KC_I,   KC_O,   KC_P, \
    GUI_A,  ALT_S,  CTL_D,  KC_F,  KC_G,                KC_H,   KC_J,  CTL_K,  ALT_L,  GUI_DOT, \
    KC_Z,   KC_X,   KC_C,   KC_V,   KC_B,               KC_N,   KC_M,   KC_COMM,KC_SCLN, TT(_MOUSE), \
            KC_TAB,SFT_SPC, TT(_LOWER),                 RAISE_BSPC, KC_SFTENT, KC_ESC   \
),


/* Lower */
[_LOWER] = LAYOUT(
   KC_QUES,KC_DQUO,KC_LPRN,KC_RPRN,KC_COLN,        KC_ASTR, KC_7,    KC_8,    KC_9,   KC_CIRC, \
   KC_COLN,KC_QUOT,KC_LBRC,KC_RBRC,KC_UNDS,       KC_PLUS, KC_4,    KC_5,    KC_6,   KC_DOT, \
   KC_AT,X(DEGREE),KC_LCBR,KC_RCBR,KC_HASH,         KC_MINS, KC_1,    KC_2,    KC_3,   KC_SLSH, \
                      KC_TAB,SFT_SPC, LOWER,      RAISEDEL, KC_0, KC_ESC   \
),

/* Raise */
[_RAISE] = LAYOUT(
  KC_BSLS, KC_EXLM, KC_TILD, KC_AMPR, KC_COLN,       KC_HOME,KC_PGDN,KC_PGUP,KC_END,XXXXXXX, \
  KC_SLSH, KC_MINS, CTL_EQL, KC_PLUS, KC_ASTR,       KC_LEFT,KC_DOWN,KC_UP,KC_RGHT,KC_DEL, \
  KC_PERC, KC_LABK, KC_PIPE, KC_RABK, KC_CIRC,      C(KC_LEFT),XXXXXXX,XXXXXXX,C(KC_RGHT),XXXXXXX, \
                      KC_TAB,SFT_SPC, LOWER,         RAISEDEL, KC_SFTENT, KC_ESC   \

),


/* Adjust (Lower + Raise) */
[_ADJUST] =  LAYOUT(
  MAGIC_UNSWAP_CTL_GUI, XXXXXXX, XXXXXXX, XXXXXXX, RESET,               QWERTY,  KC_F7, KC_F8, KC_F9, KC_F12, \
  MAGIC_SWAP_CTL_GUI, KC_LALT, KC_LCTL, XXXXXXX,  XXXXXXX,               XXXXXXX, KC_F4, KC_F5, KC_F6, KC_F11, \
  XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,                          XXXXXXX, KC_F1, KC_F2, KC_F3, KC_F10, \
                      KC_TAB,SFT_SPC, LOWER,                            RAISE,   KC_SFTENT, KC_ESC   \
),

/* Adjust (Lower + Raise) */
[_MOUSE] =  LAYOUT(
  XXXXXXX, KC_BTN1, KC_MS_U, KC_BTN2, KC_WH_D,              XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, \
  XXXXXXX, KC_MS_L, KC_MS_D, KC_MS_R, KC_WH_U,              XXXXXXX, KC_VOLD, KC_MUTE, KC_VOLU, XXXXXXX, \
  XXXXXXX, KC_WH_L, KC_BTN3, KC_WH_R, XXXXXXX,              XXXXXXX, KC_MPRV, KC_MPLY, KC_MNXT, _______, \
                      KC_TAB,SFT_SPC, LOWER,                RAISE,   KC_SFTENT, KC_ESC   \
),

};

uint16_t get_tapping_term(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        case SFT_SPC:
            return 150;
        case SFT_F:
            return 150;
        case SFT_J:
            return 150;
        default:
            return TAPPING_TERM;
    }
}

layer_state_t layer_state_set_user(layer_state_t state) {
  return update_tri_layer_state(state, _LOWER, _RAISE, _ADJUST);
}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  static uint16_t hash_timer;

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
    case RAISEBSPC:
      if (record->event.pressed) {
        hash_timer = timer_read();
        layer_on(_RAISE);
      } else {
        layer_off(_RAISE);
        if (timer_elapsed(hash_timer) < TAPPING_TERM) {
          tap_code(KC_BSPC);
        }
      }
      return false;
    case RAISEDEL:
      if (record->event.pressed) {
        hash_timer = timer_read();
        layer_on(_RAISE);
      } else {
        layer_off(_RAISE);
        if (timer_elapsed(hash_timer) < TAPPING_TERM) {
          tap_code(KC_DEL);
        }
      }
      return false;
    case SFTSPC:
      if (record->event.pressed) {
        hash_timer = timer_read();
        register_code(KC_LSFT);
      } else {
        unregister_code(KC_LSFT);
        if (timer_elapsed(hash_timer) < TAPPING_TERM) {
          tap_code(KC_SPC);
        }
      }
      return false;
    case CTL_EQL:
      if (record->event.pressed) {
        hash_timer = timer_read();
        register_code(KC_LCTL);
      } else {
        unregister_code(KC_LCTL);
        if (timer_elapsed(hash_timer) < TAPPING_TERM) {
          tap_code(KC_EQL);
        }
      }
      return false;
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
    case KC_DEL:
    case KC_BSPC:
      RESET_STORED();
      break;
    case KC_LEAD:
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
        SEND_STRING(":\n"
                    "def __init__(self):\n"
        );
        RESET_STORED();
      }
    }
  }


