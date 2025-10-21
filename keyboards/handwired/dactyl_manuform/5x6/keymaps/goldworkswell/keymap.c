#include QMK_KEYBOARD_H

#define _QWERTY 0
#define _LOWER 1
#define _RAISE 2

#define RAISE MO(_RAISE)
#define LOWER MO(_LOWER)
#define SAVE  LT(0,KC_S)
#define UNDO  LT(0,KC_Z)
#define REDO  LT(0,KC_Y)
#define FIND  LT(0,KC_F)
#define CUT   LT(0,KC_X)
#define COPY  LT(0,KC_C)
#define PASTE LT(0,KC_V)
#define ALL   LT(0,KC_A) 
enum custom_keycodes {
    ARROW = SAFE_RANGE,
};
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [_QWERTY] = LAYOUT_5x6(
        KC_ESC , KC_1  , KC_2  , KC_3  , KC_4  , KC_5  ,                         KC_6  , KC_7  , KC_8  , KC_9  , KC_0  ,KC_BSPC,
        KC_TAB , KC_Q  , KC_W  , KC_E  , KC_R  , KC_T  ,                         REDO  , KC_U  , KC_I  , KC_O  , KC_P  ,KC_MINS,
        KC_LSFT, KC_A  , SAVE  , KC_D  , FIND  , KC_G  ,                         KC_H  , KC_J  , KC_K  , KC_L  ,KC_SCLN,RSFT_T(KC_QUOT),
        KC_LCTL, UNDO  , CUT  , COPY  , PASTE  , KC_B  ,                         KC_N  , KC_M  ,KC_COMM,KC_DOT ,KC_SLSH,KC_BSLS,
                         KC_LBRC,KC_RBRC,                                                       QK_DYNAMIC_MACRO_PLAY_1, KC_EQL,
                                         RAISE,KC_SPC,                        KC_ENT, LOWER,
                                         KC_BSPC,KC_TAB,                        KC_DEL ,KC_ESC,
                                         KC_GRV, LCS(KC_T),                        KC_LGUI, KC_LALT
    ),

    [_LOWER] = LAYOUT_5x6(
        QK_LAYER_LOCK,KC_EXLM, KC_AT ,KC_HASH,KC_DLR ,S(KC_COMM),                        S(KC_DOT),KC_AMPR,KC_ASTR,KC_LPRN,KC_RPRN,KC_DEL,
        QK_CAPS_WORD_TOGGLE,_______,_______,_______,_______,KC_LBRC,                        KC_RBRC, KC_P7 , KC_P8 , KC_P9 ,KC_EQL,KC_PLUS,
        _______,KC_HOME,KC_PGUP,KC_PGDN,KC_END ,KC_LPRN,                        KC_RPRN, KC_P4 , KC_P5 , KC_P6 ,KC_MINS,KC_PIPE,
        _______,_______,_______,_______,_______,S(KC_LBRC),                        S(KC_RBRC), KC_P1 , KC_P2 , KC_P3 ,_______ ,KC_UNDS,
                        _______,KC_PSCR,                                                            QK_BOOT, KC_P0,
                                                _______,_______,            _______,_______,
                                              DT_UP,_______,            C(KC_Y),_______,
                                                DT_DOWN,DT_PRNT,            _______,QK_DEBUG_TOGGLE

    ),

    [_RAISE] = LAYOUT_5x6(
          QK_LAYER_LOCK , KC_F1 , KC_F2 , KC_F3 , KC_F4 , KC_F5 ,                        KC_F6  , KC_F7 , KC_F8 , KC_F9 ,KC_F10 ,KC_F11 ,
          _______,_______,_______,_______,_______,KC_LBRC,                        KC_RBRC,_______,KC_NUM,KC_INS ,KC_SCRL,KC_MUTE,
          _______,KC_LEFT,KC_UP  ,KC_DOWN,KC_RGHT,KC_LPRN,                        KC_RPRN,KC_LEFT,KC_UP,KC_DOWN,KC_RIGHT,KC_VOLU,
          _______,_______,_______,_______,_______,S(KC_LBRC),                        S(KC_RBRC),_______,_______,_______,_______,KC_VOLD,
                         QK_BOOT,_______,                                  QK_DYNAMIC_MACRO_RECORD_START_1 ,QK_DYNAMIC_MACRO_RECORD_STOP,
                                                  _______,_______,            ARROW,_______,
                                                  _______,_______,            _______,_______,
                                                  _______,_______,            C(A(KC_DEL)),AC_TOGG 
    )
};
bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        case SAVE:
            if (!record->tap.count && record->event.pressed) {
                tap_code16(C(KC_S)); // Intercept hold function to send Ctrl-s
                return false;
            }
            return true;             // Return true for normal processing of tap keycode
        case COPY:
            if (!record->tap.count && record->event.pressed) {
                tap_code16(C(KC_C)); // Intercept hold function to send Ctrl-C
                return false;
            }
            return true;             // Return true for normal processing of tap keycode
        case PASTE:
            if (!record->tap.count && record->event.pressed) {
                tap_code16(C(KC_V)); // Intercept hold function to send Ctrl-V
                return false;
            }
            return true;             // Return true for normal processing of tap keycode
        case CUT:
        if (!record->tap.count && record->event.pressed) {
            tap_code16(C(KC_X)); // Intercept hold function to send Ctrl-x
            return false;
        }
            return true; 
        case FIND:
            if (!record->tap.count && record->event.pressed) {
                tap_code16(C(KC_F)); // Intercept hold function to send Ctrl-f
                return false;
            }
            return true; 
        case UNDO:
            if (!record->tap.count && record->event.pressed) {
                tap_code16(C(KC_Z)); // Intercept hold function to send Ctrl-z
                return false;
            }
            return true; 
        case REDO:
            if (!record->tap.count && record->event.pressed) {
                tap_code16(C(KC_Y)); // Intercept hold function to send Ctrl-Y
                return false;
            }
            return true; 
        case ALL:
            if (!record->tap.count && record->event.pressed) {
                tap_code16(C(KC_A)); // Intercept hold function to send Ctrl-Y
                return false;
            }
            return true; 
        case ARROW:
            if (record->event.pressed) {
                SEND_STRING("->");
            }
            else{}
            break;

    }
    return true;
}