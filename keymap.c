// Copyright © 2023 Jesse Kaufman. All Rights Reserved.

#include QMK_KEYBOARD_H

#include "definitions/keycodes.h"
#include "features/leader.h"
#include "version.h" // NOLINT

#define _C_BASE {174, 255, 0}
#define _C_SYM {0, 200, 255}
#define _C_FN {255, 0, 251}
#define _C_CODE {40, 1, 145}
#define _C_OFF {0, 0, 0}
#define _C_NUM {255, 32, 0}

void matrix_scan_user(void) {
    my_leader_matrix_scan_user();
}

/* *INDENT-OFF* */

/**
 * KEYMAP LAYOUT
 */
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    // COLEMAK BASE layer
    [_BASE] = LAYOUT_ergodox_pretty(
        MEH(KC_F13),___X___,    ___X___,    _SCRNSHT1,  _SCRNSHT2,  ___X___,    _PREV_DESK,                                 _NEXT_DESK, ___X___,    ___X___,    ___X___,    ___X___,    ___X___,    _TAB_CLOSE_UN, // NOLINT
        _APP_TABS,  KC_Q,       KC_W,       KC_F,       KC_P,       KC_B,       _ACTION1,                                   _NEW_MIN,   KC_J,       KC_L,       KC_U,       KC_Y,       _PAREN,     TO(_NUM), // NOLINT
        _APP_WINS,  KC_A,       KC_R,       _KC_S,      _KC_T,      KC_G,                                                               KC_M,       KC_N,       _KC_E,      KC_I,       KC_O,       KC_PGUP, // NOLINT
        _FN_KEY,    KC_Z,       KC_X,       KC_C,       KC_D,       KC_V,       KC_LEAD,                                    CAPS_WORD,  _KC_K,      KC_H,       KC_COMMA,   _DOT,       KC_QUES,    KC_PGDOWN, // NOLINT
        _UNDO,      _REDO,      KC_LCTL,    KC_LOPT,    KC_LCMD,                                                                                    _SYM_KEY,   KC_RCMD,    KC_DOWN,    KC_UP,      _FN_KEY, // NOLINT
                                                                                _ZOOM_OUT,  _ZOOM_IN,       _VOL_DOWN,      _VOL_UP, // NOLINT
                                                                                            KC_ESC,         _PLAY, // NOLINT
                                                                    _SPACE,     KC_LSFT,    _ACTION2,       CAPS_WORD,      KC_LSFT,    _SHFT_ENTER ), // NOLINT
    // SYM layer
    [_SYM] = LAYOUT_ergodox_pretty(
        _______,    _LDFQUO,    _RDFQUO,    _LFQUO,     _RFQUO,     ___X___,    _______,                                    _______,    ___X___,    ___X___,    ___X___,    ___X___,    ___X___,    _______, // NOLINT
        _______,    KC_GRAVE,   ___X___,    _KC_HASH,   KC_PERC,    KC_CIRC,    _______,                                    _______,    ___X___,    KC_AMPR,    KC_UNDS,    KC_PIPE,    _BRACKET,  TO(_NUM), // NOLINT
        _______,    KC_AT,      KC_SLASH,   _DASH,      _EQUAL,     KC_TILD,                                                            ___X___,    _LPRN,      KC_COLON,   KC_RPRN,    ___X___,    _______, // NOLINT
        TO(_BASE),  ___X___,    KC_ASTR,    _BSLASH,    KC_DLR,     KC_PLUS,    _______,                                    _______,    ___X___,    _LTEQ,      KC_SCOLON,  _GTEQ,      ___X___,    _______, // NOLINT
        _______,    _______,    _______,    _______,    _SYM_KEY,                                                                                   TO(_BASE),  _______,    _______,    _______,    TO(_BASE), // NOLINT
                                                                                _______,    _______,        _______,        KC_APP, // NOLINT
                                                                                            _______,        _______, // NOLINT
                                                                    _______,    _______,    _______,        _______,        _______,     _______ ), // NOLINT

    // CODE layer
    [_CODE] = LAYOUT_ergodox_pretty(
        _______,    ___X___,    ___X___,    ___X___,    ___X___,    ___X___,    _______,                                    _______,    ___X___,    ___X___,    ___X___,    ___X___,    ___X___,    _______, // NOLINT
        _______,    ___X___,    ___X___,    _COMMENT,   _BEG_CBLOCK,_END_CBLOCK,_______,                                    _______,    ___X___,    KC_LCBR,    ___X___,    KC_RCBR,    _CBRACKET,  TO(_NUM), // NOLINT
        _______,    ___X___,    KC_SLASH,   _SARROW,    _DARROW,    _NIX_HOME,                                                          ___X___,    KC_LBRACKET,___X___,    KC_RBRACKET,___X___,    _______, // NOLINT
        TO(_BASE),  ___X___,    KC_ASTR,    ___X___,    _CUR_DIR,    _UP_DIR,   _______,                                    _______,    ___X___,    _HTML_OPEN, ___X___,    _HTML_CLOSE,___X___,    _______, // NOLINT
        _______,    _______,    _______,    _______,    _SYM_KEY,                                                                                   _______,    _______,    _______,    _______,    TO(_BASE), // NOLINT
                                                                                _______,    _______,        _______,        _______, // NOLINT
                                                                                            _______,        _______, // NOLINT
                                                                    _______,    _______,    _______,        _______,        _______,    _______ ), // NOLINT

    // NUM layer
    [_NUM] = LAYOUT_ergodox_pretty(
        _______,    ___X___,    ___X___,    ___X___,    ___X___,    ___X___,    _______,                                    _______,    ___X___,    ___X___,    ___X___,    ___X___,    ___X___,    _______, // NOLINT
        _______,    KC_GRAVE,   ___X___,    ___X___,    KC_PERC,    ___X___,    _______,                                    _______,    ___X___,    KC_7,       KC_8,       KC_9,       KC_EQUAL,   TO(_BASE), // NOLINT
        _______,    KC_AT,      KC_SLASH,   ___X___,    KC_EQUAL,   ___X___,                                                            ___X___,    KC_4,       KC_5,       KC_6,       ___X___,    _______, // NOLINT
        TO(_BASE),  ___X___,    KC_ASTR,    ___X___,    KC_DLR,     KC_PLUS,    _______,                                    _______,    KC_0,       KC_1,       KC_2,       _KC_3,      KC_DOT,     _______, // NOLINT
        _______,    _______,    _______,    _______,    _______,                                                                                    _SYM_KEY, _______,    _______,    _______,    TO(_BASE), // NOLINT
                                                                                _______,    _______,        _______,        _______, // NOLINT
                                                                                            _______,        _______, // NOLINT
                                                                    _______,    _______,    _______,        _______,        _______,    _______ ),// NOLINT

    // FN layer
    [_FN] = LAYOUT_ergodox_pretty(
        _______,    ___X___,    ___X___,    ___X___,    ___X___,    ___X___,    _______,                                    _______,    ___X___,        ___X___,    ___X___,    ___X___,    ___X___,        _______, // NOLINT
        _______,    ___X___,    LCMD(KC_W), LCMD(KC_F), MEH(KC_P),  MEH(KC_5),  _______,                                    _______,    MEH(KC_UP),     KC_PGUP,    KC_UP,      ___X___,    KC_HOME,        TO(_NUM), // NOLINT
        _______,    ___X___,    KC_LSFT,    MO(_NUM),   MEH(KC_U),  MEH(KC_6),                                                          LOPT(KC_LEFT),  KC_LEFT,    KC_DOWN,    KC_RIGHT,   LOPT(KC_RIGHT), _______, // NOLINT
        TO(_BASE),  KC_Z,       _FN_X,      MEH(KC_0),  MEH(KC_D),  MEH(KC_E),  _______,                                    _______,    MEH(KC_DOWN),   KC_PGDOWN,  ___X___,    KC_DOT,     KC_END,         _______, // NOLINT
        _______,    _______,    _______,    _______,    _______,                                                                                        _______,    _______,    KC_LEFT,    KC_RIGHT,       TO(_BASE), // NOLINT
                                                                                _SCREEN_DN, _SCREEN_UP,     _______,        _______, // NOLINT
                                                                                            _______,        _______, // NOLINT
                                                                    _______,    _______,    _______,        _______,        _______,    _______ ), // NOLINT
};







/**
 * RGB MATRIX LAYOUT
 */
const uint8_t PROGMEM ledmap[][DRIVER_LED_TOTAL][3] = {
    [_BASE] = {
                // RIGHT HAND SIDE
                _C_BASE,        _C_BASE,        _C_BASE,        _C_BASE,        _C_BASE, // NOLINT
                _C_BASE,        _C_BASE,        _C_BASE,        _C_BASE,        _C_BASE, // NOLINT
                _C_BASE,        _C_BASE,        _C_BASE,        _C_BASE,        _C_BASE, // NOLINT
                _C_BASE,        _C_BASE,        _C_BASE,        _C_BASE,        _C_BASE, // NOLINT
                                _C_BASE,        _C_BASE,        _C_BASE,        _C_BASE, // NOLINT

                // LEFT HAND SIDE (MIRRORED)
                _C_BASE,        _C_BASE,        _C_BASE,        _C_BASE,        _C_BASE, // NOLINT
                _C_BASE,        _C_BASE,        _C_BASE,        _C_BASE,        _C_BASE, // NOLINT
                _C_BASE,        _C_BASE,        _C_BASE,        _C_BASE,        _C_BASE, // NOLINT
                _C_BASE,        _C_BASE,        _C_BASE,        _C_BASE,        _C_BASE, // NOLINT
                                _C_BASE,        _C_BASE,        _C_BASE,        _C_BASE // NOLINT
    },
    [_SYM] = {
                // RIGHT HAND SIDE
                _C_SYM,         _C_SYM,         _C_SYM,         _C_SYM,         _C_SYM, // NOLINT
                _C_SYM,         _C_SYM,         _C_SYM,         _C_SYM,         _C_SYM, // NOLINT
                _C_SYM,         _C_SYM,         _C_SYM,         _C_SYM,         _C_SYM, // NOLINT
                _C_SYM,         _C_SYM,         _C_SYM,         _C_SYM,         _C_SYM, // NOLINT
                                _C_SYM,         _C_SYM,         _C_SYM,         _C_SYM, // NOLINT

                // LEFT HAND SIDE (MIRRORED)
                _C_SYM,         _C_SYM,         _C_SYM,         _C_SYM,         _C_SYM, // NOLINT
                _C_SYM,         _C_SYM,         _C_SYM,         _C_SYM,         _C_SYM, // NOLINT
                _C_SYM,         _C_SYM,         _C_SYM,         _C_SYM,         _C_SYM, // NOLINT
                _C_SYM,         _C_SYM,         _C_SYM,         _C_SYM,         _C_SYM, // NOLINT
                                _C_SYM,         _C_SYM,         _C_SYM,         _C_SYM, // NOLINT
    },
    [_CODE] = {
                // RIGHT HAND SIDE
                _C_CODE,            _C_CODE,            _C_CODE,            _C_CODE,            _C_CODE, // NOLINT
                _C_CODE,            _C_CODE,            _C_CODE,            _C_CODE,            _C_CODE, // NOLINT
                _C_CODE,            _C_CODE,            _C_CODE,            _C_CODE,            _C_CODE, // NOLINT
                _C_CODE,            _C_CODE,            _C_CODE,            _C_CODE,            _C_CODE, // NOLINT
                                    _C_CODE,            _C_CODE,            _C_CODE,            _C_CODE, // NOLINT

                // LEFT HAND SIDE (MIRRORED)
                _C_CODE,            _C_CODE,            _C_CODE,            _C_CODE,            _C_CODE, // NOLINT
                _C_CODE,            _C_CODE,            _C_CODE,            _C_CODE,            _C_CODE, // NOLINT
                _C_CODE,            _C_CODE,            _C_CODE,            _C_CODE,            _C_CODE, // NOLINT
                _C_CODE,            _C_CODE,            _C_CODE,            _C_CODE,            _C_CODE, // NOLINT
                                    _C_CODE,            _C_CODE,            _C_CODE,            _C_CODE // NOLINT
    },
    [_NUM] = {
                // RIGHT HAND SIDE
                _C_NUM,         _C_NUM,         _C_NUM,         _C_NUM,         _C_NUM, // NOLINT
                _C_NUM,         _C_NUM,         _C_NUM,         _C_NUM,         _C_NUM, // NOLINT
                _C_NUM,         _C_NUM,         _C_NUM,         _C_NUM,         _C_NUM, // NOLINT
                _C_NUM,         _C_NUM,         _C_NUM,         _C_NUM,         _C_NUM, // NOLINT
                                _C_NUM,         _C_NUM,         _C_NUM,         _C_NUM, // NOLINT

                // LEFT HAND SIDE (MIRRORED)
                _C_NUM,         _C_NUM,         _C_NUM,         _C_NUM,         _C_NUM, // NOLINT
                _C_NUM,         _C_NUM,         _C_NUM,         _C_NUM,         _C_NUM, // NOLINT
                _C_NUM,         _C_NUM,         _C_NUM,         _C_NUM,         _C_NUM, // NOLINT
                _C_NUM,         _C_NUM,         _C_NUM,         _C_NUM,         _C_NUM, // NOLINT
                _C_NUM,         _C_NUM,         _C_NUM,         _C_NUM // NOLINT
    },
    [_FN] = {
                // RIGHT HAND SIDE
                _C_FN,          _C_FN,          _C_FN,          _C_FN,          _C_FN, // NOLINT
                _C_FN,          _C_FN,          _C_FN,          _C_FN,          _C_FN, // NOLINT
                _C_FN,          _C_FN,          _C_FN,          _C_FN,          _C_FN, // NOLINT
                _C_FN,          _C_FN,          _C_FN,          _C_FN,          _C_FN, // NOLINT
                                _C_FN,          _C_FN,          _C_FN,          _C_FN, // NOLINT

                // LEFT HAND SIDE (MIRRORED)
                _C_FN,          _C_FN,          _C_FN,          _C_FN,          _C_FN, // NOLINT
                _C_FN,          _C_FN,          _C_FN,          _C_FN,          _C_FN, // NOLINT
                _C_FN,          _C_FN,          _C_FN,          _C_FN,          _C_FN, // NOLINT
                _C_FN,          _C_FN,          _C_FN,          _C_FN,          _C_FN, // NOLINT
                                _C_FN,          _C_FN,          _C_FN,          _C_FN // NOLINT
    },
};


/* *INDENT-ON* */
