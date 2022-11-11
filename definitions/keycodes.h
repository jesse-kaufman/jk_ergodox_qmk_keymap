#pragma once
#include QMK_KEYBOARD_H
#include "layers.h"

void my_clear_all_mods(void);

// SHORTCUTS/READABILITY
#define KC_DASH   KC_MINUS

// LAYER KEYCODES
#define _KC_T LT(_FN,KC_T)
#define _KC_S LT(_NUM, KC_S)
#define _KC_K LT(_CODE, KC_K)

#define _OSL_SYM OSL(_SYM)

// FANCY QUOTES KEYCODES
#define _LDFQUO LALT(KC_LBRACKET)
#define _RDFQUO LALT(LSFT(KC_LBRACKET))
#define _LFQUO LALT(KC_RBRACKET)
#define _RFQUO LALT(LSFT(KC_RBRACKET))

// ONE-SHOT MODIFIERS
#define _OSM_LCMD OSM(MOD_LGUI)
#define _OSM_RCMD OSM(MOD_RGUI)
#define _OSM_LSHIFT OSM(MOD_LSFT)
#define _OSM_RSHIFT OSM(MOD_RSFT)
#define _OSM_OPT OSM(MOD_LALT)
#define _OSM_CTR OSM(MOD_LCTL)
#define _OSM_CMDALT OSM(MOD_LGUI | MOD_LALT)

// PROGRAMMING SHORTCUTS
#define _MEH_LBRKT MEH(KC_LBRACKET)
#define _MEH_RBRKT MEH(KC_RBRACKET)
#define _MEH_LPRN MEH(KC_LPRN)

// GLOBAL HOTKEYS
#define _FORWARD MEH(KC_UP)
#define _BACK MEH(KC_DOWN)

// MOD TAPS
#define _SHFT_ENTER MT(MOD_RSFT, KC_ENTER)


// OTHER KEYCODES
#define _UNDO LGUI(KC_Z)
#define _REDO LGUI(LSFT(KC_Z))
#define _LAYER_LEDS TOGGLE_LAYER_COLOR
#define _SCREEN_DN KC_BRIGHTNESS_DOWN
#define _SCREEN_UP KC_BRIGHTNESS_UP
#define _PREV KC_MEDIA_PREV_TRACK
#define _NEXT KC_MEDIA_NEXT_TRACK
#define _PLAY KC_MEDIA_PLAY_PAUSE


// define these first, to prevent collisions with custom_keycodes
enum {
	MF_APP_TABS = EZ_SAFE_RANGE,
	MF_APP_WINDOWS,
	MF_DESKTOP,
	MF_PREV_DESK,
	MF_ZOOM_OUT,
	MF_ZOOM_IN,
	MF_FN_X,
	MF_FN_S,
	MF_MINIMIZE,
	MF_PAREN,
	MF_CBRACKET,
	MF_BRACKET,
	MF_QUOTE,
	MF_KEY_COUNT,
	MF_CODE_ARROWS,

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
#define _SPACE       MT(0, KC_SPACE)
#define _LTEQ        LT(9, KC_LABK)
#define _GTEQ        LT(10, KC_RABK)
#define _APP_TABS    LT(11, MF_APP_TABS)
#define _APP_WINDOWS LT(12, MF_APP_WINDOWS)
#define _DESKTOP     LT(13, MF_DESKTOP)
#define _PREV_DESK   LT(14, MF_PREV_DESK)
#define _KC_E        LT(17, KC_E)
#define _DOT         LT(8, KC_DOT)
#define _COMMA       LT(18, KC_COMMA)
#define _LBRACKET    LT(8, KC_LBRACKET)
#define _LCURLBR     LT(9, KC_LCBR)
#define _ZOOM_OUT    LT(9, MF_ZOOM_OUT)
#define _ZOOM_IN     LT(9, MF_ZOOM_IN)
#define _VOL_UP      LT(9, KC_AUDIO_VOL_UP)
#define _VOL_DOWN    LT(9, KC_AUDIO_VOL_DOWN)
#define _FN_X        LT(9, MF_FN_X)
#define _FN_S        LT(9, MF_FN_S)
#define _MINIMIZE    LT(9, MF_MINIMIZE)
#define _PAREN       LT(9, MF_PAREN)
#define _CBRACKET    LT(9, MF_CBRACKET)
#define _BRACKET     LT(9, MF_BRACKET)
#define _KC_HASH     LT(9, KC_HASH)
#define _CODE_ARROWS LT(9, MF_CODE_ARROWS)
#define _EQUAL       LT(9, KC_EQUAL)
#define _DASH        LT(9, KC_DASH)





/**
 * CUSTOM MULTI-FUNCTION KEY CONFIG
 */
#define MF_NOKEY 0
#define MF_DEF_REGISTER_TAP true
#define MF_DEF_REGISTER_HOLD true
#define MF_DEF_REGISTER_DOUBLE_TAP false
#define MF_DEF_REGISTER_DOUBLE_HOLD true
#define MF_NOFN 0


/**
 * STRUCTS FOR MULTIFUNCTION KEYS
 */
struct mf_key_event_config {
	uint16_t keycode;
	uint16_t interrupt_keycode;
	bool do_register;
	void (*fn)(keyrecord_t* record);
	void (*fn_release)(keyrecord_t* record);
	bool fn_do_release;
	const char *string;
};


typedef struct mf_key_config {
	struct mf_key_event_config tap;
	struct mf_key_event_config hold;
} mf_key_config;


/*
 * TAP/HOLD KEYCODE MACROS
 */
#define MF_TAP_HOLD( tap_kc, hold_kc ) \
	; MF_KEY_ADVANCED(tap_kc, MF_DEF_REGISTER_TAP, MF_NOKEY, \
	                  hold_kc, MF_DEF_REGISTER_HOLD, MF_NOKEY );

#define MF_TAP_NO_REPEAT_HOLD( tap_kc, hold_kc ) \
	; MF_KEY_ADVANCED(tap_kc, MF_DEF_REGISTER_TAP, MF_NOKEY, \
	                  hold_kc, false, MF_NOKEY );

#define MF_TAP_HOLD_ONCE( tap_kc, hold_kc ) \
	; MF_KEY_ADVANCED(tap_kc, false, MF_NOKEY, \
	                  hold_kc, false, MF_NOKEY );

#define MF_TAP_HOLD_ADVANCED( tap_kc, tap_do_register, tap_interrupt_kc, hold_kc, hold_do_register, hold_interrupt_kc ) \
	; MF_KEY_ADVANCED(tap_kc, tap_do_register, tap_interrupt_kc, \
	                  hold_kc, hold_do_register, hold_interrupt_kc );


#define MF_KEY_ADVANCED(tap_kc, tap_do_register, tap_interrupt_kc, \
	                    hold_kc, hold_do_register, hold_interrupt_kc) \
	; mf_handle_key_event(record, &(mf_key_config) { \
		.tap = { .keycode = tap_kc, .interrupt_keycode = tap_interrupt_kc, .do_register = tap_do_register }, \
		.hold = { .keycode = hold_kc, .interrupt_keycode = hold_interrupt_kc, .do_register = hold_do_register }, \
	});


/*
 * TAP/HOLD STRING MACROS
 */
 #define MF_STR_TAP_HOLD(tap_str, hold_str) \
	; MF_STR_KEY_ADVANCED(tap_str, hold_str);

 #define MF_STR_TAP(str) \
	; MF_STR_KEY_ADVANCED(str, "");


#define MF_STR_KEY_ADVANCED(tap_str, hold_str) \
	; mf_handle_key_event(record, &(mf_key_config) { \
		.tap = { .string = tap_str, .keycode = MF_NOKEY  }, \
		.hold = { .string = hold_str, .keycode = MF_NOKEY }, \
	});


/*
 * TAP/HOLD FUNCTION MACROS
 */
#define MF_TAP_HOLD_FN(tap_fn, hold_fn) \
	; MF_KEY_FN(tap_fn, hold_fn, MF_NOFN, MF_NOFN, \
	            MF_NOFN, MF_NOFN, MF_NOFN \
	            );

#define MF_KEY_FN(tap_fn, hold_fn, tap_release_fn, hold_release_fn ) \
	; mf_handle_key_event(record, &(mf_key_config) { \
		.tap = { .fn = tap_fn, .fn_release = tap_release_fn }, \
		.hold = { .fn = hold_fn, .fn_release = hold_release_fn }, \
	});

#define MF_TAP_HOLD_MIXED(tap_kc, tap_str, hold_kc, hold_str) \
	; mf_handle_key_event(record, &(mf_key_config) { \
		.tap = { .string = tap_str, .keycode = tap_kc  }, \
		.hold = { .string = hold_str, .keycode = hold_kc }, \
	});
