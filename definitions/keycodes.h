#pragma once
#include QMK_KEYBOARD_H
#include "layers.h"

void my_clear_all_mods(void);


// SHORTCUTS/READABILITY
#define KC_DASH   KC_MINUS

// LAYER KEYCODES
#define _FN_KEY      TT(_FN)
#define _KC_T LT(_FN,KC_T)
#define _KC_S LT(_NUM, KC_S)
#define _KC_K LT(_CODE, KC_K)

// FANCY QUOTES KEYCODES
#define _LDFQUO LALT(KC_LBRACKET)
#define _RDFQUO LALT(LSFT(KC_LBRACKET))
#define _LFQUO LALT(KC_RBRACKET)
#define _RFQUO LALT(LSFT(KC_RBRACKET))

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
#define _UNDO LGUI(KC_Z)
#define _REDO LGUI(LSFT(KC_Z))
#define _SCREEN_DN KC_BRIGHTNESS_DOWN
#define _SCREEN_UP KC_BRIGHTNESS_UP
#define _PLAY KC_MEDIA_PLAY_PAUSE


// define these first, to prevent collisions with custom_keycodes
enum {
	MF_APP_CONTROL = EZ_SAFE_RANGE,
	MF_ZOOM,
	MF_FN_LAYER,
	MF_BRACKETS,
	MF_QUOTE,
	MF_KEY_COUNT,
	MF_CODE_ARROWS,
	MF_LAYERS,

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
#define _SPACE       MT(0,  KC_SPACE)
#define _LTEQ        LT(9,  KC_LABK)
#define _GTEQ        LT(10, KC_RABK)
#define _MINIMIZE    LT(10, MF_APP_CONTROL)
#define _APP_TABS    LT(11, MF_APP_CONTROL)
#define _APP_WINDOWS LT(12, MF_APP_CONTROL)
#define _DESKTOP     LT(13, MF_APP_CONTROL)
#define _PREV_DESK   LT(14, MF_APP_CONTROL)
#define _KC_E        LT(17, KC_E)
#define _DOT         LT(8,  KC_DOT)
#define _COMMA       LT(18, KC_COMMA)
#define _LCURLBR     LT(9,  KC_LCBR)
#define _ZOOM_OUT    LT(9,  MF_ZOOM)
#define _ZOOM_IN     LT(10, MF_ZOOM)
#define _VOL_UP      LT(9,  KC_AUDIO_VOL_UP)
#define _VOL_DOWN    LT(9,  KC_AUDIO_VOL_DOWN)
#define _FN_X        LT(9,  MF_FN_LAYER)
#define _FN_S        LT(10, MF_FN_LAYER)
#define _PAREN       LT(9,  MF_BRACKETS)
#define _CBRACKET    LT(10, MF_BRACKETS)
#define _BRACKET     LT(11, MF_BRACKETS)
#define _KC_HASH     LT(9,  KC_HASH)
#define _CODE_ARROWS LT(9,  MF_CODE_ARROWS)
#define _EQUAL       LT(9,  KC_EQUAL)
#define _DASH        LT(9,  KC_DASH)
#define _ACTION_KEY1 LT(9,  KC_F20)
#define _ACTION_KEY2 LT(9,  KC_F19)
#define _SYM_KEY     LT(10, MF_LAYERS)







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
	const char *string;
	bool do_register;
};


typedef struct mf_key_config {
	struct mf_key_event_config tap;
	struct mf_key_event_config hold;
} mf_key_config;

void mf_check_disable_oneshot(keyrecord_t* record, uint16_t keycode);
void mf_disable_oneshot_layer(void);
bool mf_process_key(uint16_t keycode, keyrecord_t *record);


/*
 * TAP/HOLD KEYCODE MACROS
 */
#define MF_TAP_HOLD( tap_kc, hold_kc ) \
	; MF_ADVANCED(tap_kc, MF_DEF_REGISTER_TAP, MF_NOKEY, \
	              hold_kc, MF_DEF_REGISTER_HOLD, MF_NOKEY );

#define MF_TAP_NO_REPEAT_HOLD( tap_kc, hold_kc ) \
	; MF_ADVANCED(tap_kc, MF_DEF_REGISTER_TAP, MF_NOKEY, \
	              hold_kc, false, MF_NOKEY );

#define MF_TAP_HOLD_ONCE( tap_kc, hold_kc ) \
	; MF_ADVANCED(tap_kc, false, MF_NOKEY, \
	              hold_kc, false, MF_NOKEY );

#define MF_TAP_HOLD_ADVANCED( tap_kc, tap_do_register, tap_interrupt_kc, hold_kc, hold_do_register, hold_interrupt_kc ) \
	; MF_ADVANCED(tap_kc, tap_do_register, tap_interrupt_kc, \
	              hold_kc, hold_do_register, hold_interrupt_kc );


#define MF_ADVANCED(tap_kc, tap_do_register, tap_interrupt_kc, \
	                hold_kc, hold_do_register, hold_interrupt_kc) \
	; mf_handle_key_event(keycode, record, &(mf_key_config) { \
		.tap = { .keycode = tap_kc, .interrupt_keycode = tap_interrupt_kc, .do_register = tap_do_register }, \
		.hold = { .keycode = hold_kc, .interrupt_keycode = hold_interrupt_kc, .do_register = hold_do_register }, \
	}, MF_NOFN, MF_NOFN); \
	return false;


/*
 * TAP/HOLD STRING MACROS
 */
 #define MF_STR_TAP_HOLD(tap_str, hold_str) \
	; MF_STR_ADVANCED(tap_str, hold_str);

 #define MF_STR_TAP(str) \
	; MF_STR_ADVANCED(str, "");

#define MF_STR_ADVANCED(tap_str, hold_str) \
	; mf_handle_key_event(keycode, record, &(mf_key_config) { \
		.tap = { .string = tap_str, .keycode = MF_NOKEY  }, \
		.hold = { .string = hold_str, .keycode = MF_NOKEY }, \
	}, MF_NOFN, MF_NOFN); \
	return false;


/*
 * TAP/HOLD FUNCTION MACROS
 */
#define MF_FN(fn_down, fn_up) \
	; MF_FN_ADVANCED(fn_down, fn_up);

#define MF_FN_ADVANCED(fn_down, fn_up) \
	; mf_handle_key_event(keycode, record, &(mf_key_config) {}, fn_down, fn_up); \
	return false;


/*
 * MIXED FUNCTION MACROS
 */
#define MF_TAP_HOLD_MIXED(tap_kc, tap_str, hold_kc, hold_str) \
	; mf_handle_key_event(keycode, record, &(mf_key_config) { \
		.tap = { .string = tap_str, .keycode = tap_kc  }, \
		.hold = { .string = hold_str, .keycode = hold_kc }, \
	}, MF_NOFN, MF_NOFN); \
	return false;

#define MF_RESET_LAYER() \
	if (mf_prev_layer) { \
		layer_move(mf_prev_layer); \
	} \
	else { \
		layer_move(_BASE); \
	}
