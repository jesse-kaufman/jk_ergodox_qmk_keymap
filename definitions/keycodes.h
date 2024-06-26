#pragma once
#include "definitions/layers.h"
#include QMK_KEYBOARD_H

void my_clear_all_mods(void);
uint16_t mf_key_timer;

// SHORTCUTS/READABILITY
#define KC_DASH KC_MINUS

// LAYER KEYCODES
#define _FN_KEY TT(_FN)
#define _KC_T LT(_FN, KC_T)
#define _KC_S LT(_NUM, KC_S)
#define _KC_K LT(_CODE, KC_K)
#define _KC_V LT(_CODE, KC_V)

// FANCY QUOTES KEYCODES
#define _LDFQUO LOPT(KC_LBRACKET)
#define _RDFQUO LOPT(LSFT(KC_LBRACKET))
#define _LFQUO LOPT(KC_RBRACKET)
#define _RFQUO LOPT(LSFT(KC_RBRACKET))

// PROGRAMMING SHORTCUTS
#define _MEH_LBRKT MEH(KC_LBRACKET)
#define _MEH_RBRKT MEH(KC_RBRACKET)
#define _MEH_LPRN MEH(KC_LPRN)

// GLOBAL HOTKEYS
#define _FORWARD MEH(KC_UP)
#define _BACK MEH(KC_DOWN)

// MOD TAPS
#define _SHFT_ENTER MT(MOD_LSFT, KC_ENTER)

// OTHER KEYCODES
#define _UNDO LCMD(KC_Z)
#define _REDO LCMD(LSFT(KC_Z))
#define _SCREEN_DN KC_BRIGHTNESS_DOWN
#define _SCREEN_UP KC_BRIGHTNESS_UP
#define _PLAY KC_MEDIA_PLAY_PAUSE
#define _SCRNSHT2 SCMD(KC_5)

// define these first, to prevent collisions with custom_keycodes
enum {
  MF_APP_CONTROL = EZ_SAFE_RANGE,
  MF_ZOOM_IN,
  MF_ZOOM_OUT,
  MF_FN_S,
  MF_FN_X,
  MF_BRACKET,
  MF_QUOTE,
  MF_KEY_COUNT,
  MF_SARROW,
  MF_DARROW,
  MF_LAYERS,
  MF_SCRNSHT1,
  MF_APP_TAPS,
  MF_NEW_MIN,
  MF_APP_WINS,
  MF_NEXT_DESK,
  MF_PREV_DESK,
  MF_TAB_CLOSE_UN,
  MF_PAREN,
  MF_SYM_KEY,
  MF_CBRACKET,

  MF_SAFE_RANGE,
};

enum custom_keycodes {
  _NIX_HOME = MF_SAFE_RANGE,
  _BEG_CBLOCK,
  _END_CBLOCK,
  _COMMENT,
  _HTML_OPEN,
  _HTML_CLOSE,
  _CUR_DIR,
  _UP_DIR,

  CUSTOM_KEYCODE_COUNT,
};

// CUSTOM MULTI-FUNCTION KEYS
#define _SPACE MT(0, KC_SPACE)
#define _LTEQ LT(7, KC_LABK)
#define _DOT LT(7, KC_DOT)
#define _GTEQ LT(8, KC_RABK) // also KC_DOT
#define _NEW_MIN LT(7, MF_NEW_MIN)
#define _APP_TABS LT(7, MF_APP_TAPS)
#define _APP_WINS LT(7, MF_APP_WINS)
#define _NEXT_DESK LT(7, MF_NEXT_DESK)
#define _PREV_DESK LT(7, MF_PREV_DESK)
#define _SCRNSHT1 LT(7, MF_SCRNSHT1)
#define _TAB_CLOSE_UN LT(7, MF_TAB_CLOSE_UN)
#define _KC_E LT(7, KC_E)
#define _COMMA LT(7, KC_COMMA)
#define _LCURLBR LT(7, KC_LCBR)
#define _ZOOM_OUT LT(7, MF_ZOOM_OUT)
#define _ZOOM_IN LT(7, MF_ZOOM_IN)
#define _VOL_UP LT(7, KC_AUDIO_VOL_UP)
#define _VOL_DOWN LT(7, KC_AUDIO_VOL_DOWN)
#define _FN_X LT(7, MF_FN_X)
#define _FN_S LT(7, MF_FN_S)
#define _PAREN LT(7, MF_PAREN)
#define _CBRACKET LT(7, MF_CBRACKET)
#define _BRACKET LT(7, MF_BRACKET)
#define _SARROW LT(7, MF_SARROW)
#define _DARROW LT(7, MF_DARROW)
#define _EQUAL LT(7, KC_EQUAL)
#define _DASH LT(7, KC_DASH)
#define _ACTION1 LT(7, KC_F20)
#define _ACTION2 LT(7, KC_F17)
#define _SYM_KEY LT(7, MF_SYM_KEY)
#define _KC_3 LT(7, KC_3)
#define _KC_HASH LT(8, KC_HASH) // also KC_3
#define _LPRN LT(7, KC_LPRN)
#define _RPRN LT(7, KC_RPRN)
#define _BSLASH LT(7, KC_BSLASH)

/**
 * CUSTOM MULTI-FUNCTION KEY CONFIG
 */
#define MF_NOKEY 0
#define MF_DEF_REGISTER_TAP true
#define MF_DEF_REGISTER_HOLD true
#define MF_DEF_REGISTER_DOUBLE_TAP false
#define MF_DEF_REGISTER_DOUBLE_HOLD true
#define MF_NOFN NULL

/**
 * STRUCTS FOR MULTIFUNCTION KEYS
 */
struct mf_key_event_config {
  uint16_t keycode;
  uint16_t interrupt_keycode;
  const char *str;
  bool do_register;
};

typedef struct mf_key_config {
  struct mf_key_event_config tap;
  struct mf_key_event_config hold;
} mf_key_config;

void mf_disable_oneshot_layer(void);
bool mf_process_key(uint16_t keycode, keyrecord_t *record);
void mf_reset_layer(void);

void mf_str_advanced(uint16_t keycode, keyrecord_t *record, const char *tap_str,
                     const char *hold_str);

void mf_advanced(uint16_t keycode, keyrecord_t *record, uint16_t tap_kc,
                 bool tap_do_register, uint16_t tap_interrupt_kc,
                 uint16_t hold_kc, bool hold_do_register,
                 uint16_t hold_interrupt_kc);

/*
 * TAP/HOLD STRING MACROS
 */
#define MF_STR_TAP(tap_str)                                                    \
  ;                                                                            \
  mf_str_advanced(keycode, record, tap_str, MF_NOKEY);

#define MF_STR_TAP_HOLD(tap_str, hold_str)                                     \
  ;                                                                            \
  mf_str_advanced(keycode, record, tap_str, hold_str);

/*
 * TAP/HOLD KEYCODE MACROS
 */

#define MF_TAP_HOLD_ONCE(tap_kc, hold_kc)                                      \
  ;                                                                            \
  mf_advanced(keycode, record, tap_kc, false, MF_NOKEY, hold_kc, false,        \
              MF_NOKEY);

#define MF_TAP_NO_REPEAT_HOLD(tap_kc, hold_kc)                                 \
  mf_advanced(keycode, record, tap_kc, MF_DEF_REGISTER_TAP, MF_NOKEY, hold_kc, \
              false, MF_NOKEY);

#define MF_TAP_HOLD_ADVANCED(tap_kc, tap_do_register, tap_interrupt_kc,        \
                             hold_kc, hold_do_register, hold_interrupt_kc)     \
  ;                                                                            \
  mf_handle_key_event(keycode, record,                                         \
                      &(mf_key_config){                                        \
                          .tap = {.keycode = tap_kc,                           \
                                  .interrupt_keycode = tap_interrupt_kc,       \
                                  .do_register = tap_do_register},             \
                          .hold = {.keycode = hold_kc,                         \
                                   .interrupt_keycode = hold_interrupt_kc,     \
                                   .do_register = hold_do_register},           \
                      },                                                       \
                      MF_NOFN, MF_NOFN);

/*
 * TAP/HOLD FUNCTION MACROS
 */
#define MF_FN_ADVANCED(fn_down, fn_up)                                         \
  ;                                                                            \
  mf_handle_key_event(keycode, record, &(mf_key_config){}, fn_down, fn_up);

/*
 * MIXED FUNCTION MACROS
 */
#define MF_TAP_HOLD_MIXED(tap_kc, tap_str, hold_kc, hold_str)                  \
  ;                                                                            \
  mf_handle_key_event(keycode, record,                                         \
                      &(mf_key_config){                                        \
                          .tap = {.str = tap_str, .keycode = tap_kc},          \
                          .hold = {.str = hold_str, .keycode = hold_kc},       \
                      },                                                       \
                      MF_NOFN, MF_NOFN);
