#include QMK_KEYBOARD_H

// Each layer gets a name for readability, which is then used in the keymap matrix below.
// The underscores don't mean anything - you can have a layer called STUFF or any other name.
// Layer names don't all need to be of the same length, obviously, and you can also skip them
// entirely and just use numbers.
#define _QWERTY 0
#define _LOWER 3
#define _RAISE 4
#define _SOLIDWORKS 5
#define _SOLIDWORKS_NUM 6
#define _MOUSE 7
#define _ADJUST 16


enum custom_keycodes {
  QWERTY = SAFE_RANGE,
  SOLIDWORKS,
  RAISEBSPC,
  RAISEDEL,
  SFTENT,
  LOWERTAB
};

#define LOWER  MO(_LOWER)
#define RAISE  MO(_RAISE)
#define ADJUST MO(_ADJUST)
#define MOUSE MO(_MOUSE)
#define SWNUM  MO(_SOLIDWORKS_NUM)
#define SFT_SPC SFT_T(KC_SPC)


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

//space cadet layer keypress tracking
int last_pressed;

const uint32_t PROGMEM unicode_map[] = {
    [DEGREE]  = 0x00B0,
    [MU] = 0x03BC,
    [DELTA]  = 0x0394
};

//start keymaps

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
/* Qwerty */
[_QWERTY] = LAYOUT(
    KC_ESC,   KC_1,   KC_2,   KC_3,   KC_4,   KC_5,               KC_6,   KC_7,   KC_8,   KC_9,   KC_0,   XXXXXXX, \
    KC_TAB,   KC_Q,   KC_W,   KC_E,   KC_R,   KC_T,               KC_Y,   KC_U,   KC_I,   KC_O,   KC_P,   XXXXXXX, \
    KC_LCTL,  KC_A,   KC_S,   KC_D,   KC_F,  KC_G,                KC_H,   KC_J,   KC_K,   KC_L,   KC_DOT, KC_BSPC, \
    KC_LALT,  KC_Z,   KC_X,   KC_C,   KC_V,   KC_B,               KC_N,   KC_M,   KC_COMM,KC_SCLN, KC_SLSH, MOUSE, \
                      KC_LGUI,SFT_SPC,LOWERTAB, KC_ESC,          KC_LEAD, RAISEBSPC, SFTENT   \
),


/* Lower */
[_LOWER] = LAYOUT(
   KC_ESC,XXXXXXX,XXXXXXX,XXXXXXX,XXXXXXX,XXXXXXX,        XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,  XXXXXXX, \
   KC_TAB,KC_QUES,KC_DQUO,KC_LPRN,KC_RPRN,KC_COLN,        KC_ASTR, KC_7,    KC_8,    KC_9,   KC_CIRC,  XXXXXXX, \
   KC_LCTL,KC_COLN,KC_QUOT,KC_LBRC,KC_RBRC,KC_UNDS,       KC_PLUS, KC_4,    KC_5,    KC_6,   KC_DOT,  KC_DEL, \
   KC_LALT,KC_AT,X(DEGREE),KC_LCBR,KC_RCBR,KC_HASH,         KC_MINS, KC_1,    KC_2,    KC_3,   KC_SLSH,   KC_ENT, \
                      KC_LGUI,SFT_SPC, LOWERTAB, KC_ESC,     KC_ESC, RAISEDEL, KC_0   \
),

/* Raise */
[_RAISE] = LAYOUT(
  KC_ESC,  KC_F1  ,KC_F2   ,KC_F3  ,  KC_F4 ,  KC_F5,         KC_F6,   KC_F7,   KC_F8,   KC_F9  ,KC_F10,  KC_F11 , \
  KC_TAB , KC_BSLS, KC_EXLM, KC_TILD, KC_AMPR, KC_GRV,       KC_HOME,KC_PGDN,KC_PGUP,KC_END ,XXXXXXX,KC_F12 ,\
  KC_LCTL , KC_SLSH, KC_MINS, KC_EQL, KC_PLUS, KC_ASTR,       KC_LEFT,KC_DOWN,KC_UP,KC_RGHT,XXXXXXX,KC_DEL, \
  KC_LALT , KC_PERC, KC_LABK, KC_PIPE, KC_RABK, KC_CIRC,      C(G(KC_LEFT)),XXXXXXX,XXXXXXX,C(G(KC_RGHT)),C(KC_SLSH), KC_RSFT, \
                      KC_LGUI,SFT_SPC, LOWERTAB, KC_ESC,         KC_ESC, RAISEDEL, SFTENT   \

),


/* Adjust (Lower + Raise) */
[_ADJUST] =  LAYOUT(
  KC_ESC , RESET,   XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,                      XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, \
  KC_TAB , MAGIC_UNSWAP_CTL_GUI, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,         QWERTY, KC_F7, KC_F8, KC_F9, KC_F12,SOLIDWORKS, \
  KC_LCTL, MAGIC_SWAP_CTL_GUI, KC_VOLD, KC_MUTE, KC_VOLU, XXXXXXX,           XXXXXXX, KC_F4, KC_F5, KC_F6, KC_F11, XXXXXXX, \
  KC_LALT, XXXXXXX, KC_MPRV, KC_MPLY, KC_MNXT, XXXXXXX,                      XXXXXXX, KC_F1, KC_F2, KC_F3, KC_F10, XXXXXXX, \
                      KC_LGUI,SFT_SPC, LOWERTAB,  KC_ESC,                       KC_ESC,  RAISE,  SFTENT   \
),

[_MOUSE] = LAYOUT(
     XXXXXXX,XXXXXXX,XXXXXXX,XXXXXXX,XXXXXXX,XXXXXXX,        XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,  XXXXXXX, \
     XXXXXXX,XXXXXXX,KC_BTN1, KC_MS_U, KC_BTN2, KC_WH_U,     XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,  XXXXXXX, \
     KC_LCTL,XXXXXXX,KC_MS_L,KC_MS_D,KC_MS_R,KC_WH_D,        XXXXXXX, KC_BTN1, XXXXXXX, XXXXXXX, XXXXXXX,  XXXXXXX, \
     KC_LALT,XXXXXXX,KC_WH_L,KC_BTN3,KC_WH_R,XXXXXXX,        C(G(KC_LEFT)), XXXXXXX, XXXXXXX, C(G(KC_RGHT)), XXXXXXX,  XXXXXXX, \
                     KC_LGUI,SFT_SPC, LOWERTAB, KC_ESC,             KC_ESC, RAISE_BSPC, SFTENT   \
),

/* SOLIDWORKS */
[_SOLIDWORKS] = LAYOUT(
    KC_ESC,   KC_1,   KC_2,   KC_3,   KC_4,   KC_5,               KC_6,   KC_7,   KC_8,   KC_9,   KC_0,   XXXXXXX, \
    KC_TAB,   KC_Q,   KC_W,   KC_E,   KC_R,   KC_T,               KC_Y,   KC_U,   KC_I,   KC_O,   KC_P,   XXXXXXX, \
    KC_LCTL,  KC_A,   KC_S,   KC_D,   KC_F,   KC_G,               KC_H,   KC_J,   KC_K,   KC_L,   KC_DOT, KC_BSPC, \
    SWNUM  ,  KC_Z,   KC_X,   KC_C,   KC_V,   KC_B,               KC_N,   KC_M,   KC_COMM,KC_SCLN, KC_SLSH, KC_RSFT, \
                      KC_TAB,SFT_SPC, KC_DEL, KC_ESC,             KC_LEAD, RAISEBSPC, SFTENT   \
),

/* SOLIDWORKS NUM */
[_SOLIDWORKS_NUM] = LAYOUT(
    KC_ESC,   XXXXXXX,XXXXXXX,XXXXXXX,XXXXXXX,XXXXXXX,               KC_6,   KC_7,   KC_8,   KC_9,   KC_0,   XXXXXXX, \
    KC_TAB,   KC_LPRN,   KC_7,   KC_8,   KC_9,KC_RPRN,               KC_Y,   KC_U,   KC_I,   KC_O,   KC_P,   XXXXXXX, \
    KC_LCTL,  KC_ASTR,   KC_4,   KC_5,   KC_6,KC_SLSH,               KC_H,   KC_J,   KC_K,   KC_L,   KC_DOT, KC_BSPC, \
    SWNUM  ,  KC_PLUS,   KC_1,   KC_2,   KC_3,KC_MINS,               KC_N,   KC_M,   KC_COMM,KC_SCLN, KC_SLSH, KC_RSFT, \
                      KC_DOT,KC_0, KC_ENT, KC_BSPC,             KC_LEAD, RAISEDEL, SFTENT   \
)



};

uint16_t get_tapping_term(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        default:
            return TAPPING_TERM;
    }
}

layer_state_t layer_state_set_user(layer_state_t state) {
  return update_tri_layer_state(state, _LOWER, _RAISE, _ADJUST);
}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  static uint16_t hash_timer;

  if (record->event.pressed) {
    last_pressed = keycode;
  }

  switch (keycode) {
    case QWERTY:
      if (record->event.pressed) {
        set_single_persistent_default_layer(_QWERTY);
      }
      return false;
    case SOLIDWORKS:
      if (record->event.pressed) {
        set_single_persistent_default_layer(_SOLIDWORKS);
      }
      return false;
    case RAISEBSPC:
      if (record->event.pressed) {
        hash_timer = timer_read();
        layer_on(_RAISE);
        last_pressed = 10;
      } else {
        layer_off(_RAISE);
        if ((timer_elapsed(hash_timer) < TAPPING_TERM_CADET) && (last_pressed == 10)){
          tap_code(KC_BSPC);
        }
      }
      return false;
    case RAISEDEL:
      if (record->event.pressed) {
        hash_timer = timer_read();
        layer_on(_RAISE);
        last_pressed = 9;
      } else {
        layer_off(_RAISE);
        if ((timer_elapsed(hash_timer) < TAPPING_TERM_CADET) && (last_pressed == 9)){
          tap_code(KC_DEL);
        }
      }
      return false;
    case SFTENT:
      if (record->event.pressed) {
        hash_timer = timer_read();
        register_code(KC_RSFT);
        last_pressed = 8;
      } else {
        unregister_code(KC_RSFT);
        if ((timer_elapsed(hash_timer) < TAPPING_TERM_CADET) && (last_pressed == 8)){
          tap_code(KC_ENT);
        }
      }
      return false;
    case LOWERTAB:
      if (record->event.pressed) {
        hash_timer = timer_read();
        layer_on(_LOWER);
        last_pressed = 7;
      } else {
        layer_off(_LOWER);
        if ((timer_elapsed(hash_timer) < TAPPING_TERM_CADET) && (last_pressed == 10)){
          tap_code(KC_TAB);
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
      /* Kill text (K) */
      SEQ_ONE_KEY(KC_K){
        SEND_STRING(SS_TAP(X_HOME)
                    SS_LSFT(SS_TAP(X_END))
                    SS_TAP(X_BSPC)
                    );      }
      SEQ_TWO_KEYS(KC_K, KC_K){
        SEND_STRING(SS_TAP(X_HOME)
                    SS_LSFT(SS_TAP(X_END))
                    SS_TAP(X_BSPC)
                    SS_TAP(X_BSPC)
                    );
      }
      SEQ_ONE_KEY(KC_J){
        SEND_STRING(SS_LCTL(SS_LSFT(SS_TAP(X_LEFT)))
                    SS_TAP(X_BSPC)
                    );
      }
      SEQ_ONE_KEY(KC_L){
        SEND_STRING(SS_LCTL(SS_LSFT(SS_TAP(X_RGHT)))
                    SS_TAP(X_BSPC)
                    );
      }
      SEQ_TWO_KEYS(KC_L, KC_L){
        SEND_STRING(SS_LSFT(SS_TAP(X_END))
                    SS_TAP(X_BSPC)
                    );
      }
      SEQ_TWO_KEYS(KC_J, KC_J){
        SEND_STRING(SS_LSFT(SS_TAP(X_HOME))
                    SS_TAP(X_BSPC)
                    );
      }
      /* python (P) */
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


