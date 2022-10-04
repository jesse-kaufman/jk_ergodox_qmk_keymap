#pragma once
#include QMK_KEYBOARD_H
#include "layers.h"

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

// MOUSE KEYCODE
#define _SHFT_WHDN LSFT(KC_MS_WH_DOWN)
#define _SHFT_WHUP LSFT(KC_MS_WH_UP)

// GLOBAL HOTKEYS
#define _ZOOM_IN HYPR(KC_EQUAL)
#define _ZOOM_OUT HYPR(KC_MINUS)
#define _FORWARD MEH(KC_UP)
#define _BACK MEH(KC_DOWN)

// MOD TAPS
// #define _SPACE MT(MOD_LSFT | MOD_LALT, KC_SPACE)
#define _SHFT_ENTER MT(MOD_RSFT, KC_ENTER)
#define _KC_A MT(MOD_LALT, KC_A)
#define _KC_R MT(MOD_LSFT, KC_R)

// OTHER KEYCODES
#define _UNDO LGUI(KC_Z)
#define _REDO LGUI(LSFT(KC_Z))
#define _LAYER_LEDS TOGGLE_LAYER_COLOR
#define _SCREEN_DN KC_BRIGHTNESS_DOWN
#define _SCREEN_UP KC_BRIGHTNESS_UP
#define _PREV KC_MEDIA_PREV_TRACK
#define _NEXT KC_MEDIA_NEXT_TRACK
#define _VOL_UP KC_AUDIO_VOL_UP
#define _VOL_DOWN KC_AUDIO_VOL_DOWN

// custom tap dances
#define _KC_UP_DIR	LT(9, KC_0)
#define _KC_SCOLN	LT(0, KC_SCOLON)
#define _SPACE		LT(0, KC_SPACE)
#define _DOT		LT(0, KC_DOT)
#define _COMMA		LT(0, KC_COMMA)
#define _LTEQ		LT(9, KC_LABK)
#define _GTEQ		LT(10, KC_RABK)
#define _KC_NIX_HOME	LT(9, KC_1)
#define _KC_CUR_DIR		LT(9, KC_2)
#define _KC_COMMENT		LT(9, KC_NO)
#define _KC_ML_COMMENT	LT(10, KC_NO)
#define _APP_TABS		LT(11, KC_NO)
#define _APP_WINDOWS	LT(12, KC_NO)











// CUSTOM MULTI-FUNCTION KEYS
#define MF_NOKEY 0
#define MF_DEF_REGISTER_TAP true
#define MF_DEF_REGISTER_HOLD true
#define MF_DEF_REGISTER_DOUBLE_TAP false
#define MF_DEF_REGISTER_DOUBLE_HOLD true
#define MF_NOFN 0

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
	struct mf_key_event_config double_tap;
	struct mf_key_event_config double_hold;
} mf_key_config;


/*
 * TAP/HOLD KEYCODE MACROS
 */
#define MF_TAP_HOLD( tap_kc, hold_kc ) \
	; MF_KEY_ADVANCED(tap_kc, MF_DEF_REGISTER_TAP, MF_NOKEY, \
	                  hold_kc, MF_DEF_REGISTER_HOLD, MF_NOKEY, \
	                  MF_NOKEY, MF_DEF_REGISTER_DOUBLE_TAP, MF_NOKEY, \
	                  MF_NOKEY, MF_DEF_REGISTER_DOUBLE_HOLD, MF_NOKEY );

#define MF_TAP_NO_REPEAT_HOLD( tap_kc, hold_kc ) \
	; MF_KEY_ADVANCED(tap_kc, MF_DEF_REGISTER_TAP, MF_NOKEY, \
	                  hold_kc, false, MF_NOKEY, \
	                  MF_NOKEY, MF_DEF_REGISTER_DOUBLE_TAP, MF_NOKEY, \
	                  MF_NOKEY, MF_DEF_REGISTER_DOUBLE_HOLD, MF_NOKEY );

#define MF_TAP_HOLD_ADVANCED( tap_kc, tap_do_register, tap_interrupt_kc, hold_kc, hold_do_register, hold_interrupt_kc ) \
	; MF_KEY_ADVANCED(tap_kc, tap_do_register, tap_interrupt_kc, \
	                  hold_kc, hold_do_register, hold_interrupt_kc, \
	                  MF_NOKEY, MF_DEF_REGISTER_DOUBLE_TAP, MF_NOKEY, \
	                  MF_NOKEY, MF_DEF_REGISTER_DOUBLE_HOLD, MF_NOKEY );

#define MF_TAP_HOLD_DOUBLE( tap_kc, hold_kc, double_tap_kc, double_hold_kc ) \
	; MF_KEY_ADVANCED(tap_kc, MF_DEF_REGISTER_TAP, MF_NOKEY, \
	                  hold_kc, MF_DEF_REGISTER_HOLD, MF_NOKEY, \
	                  double_tap_kc, MF_DEF_REGISTER_DOUBLE_TAP, MF_NOKEY, \
	                  double_hold_kc, MF_DEF_REGISTER_DOUBLE_HOLD, MF_NOKEY );


#define MF_KEY_ADVANCED(tap_kc, tap_do_register, tap_interrupt_kc, \
	                    hold_kc, hold_do_register, hold_interrupt_kc, \
	                    double_hold_kc, double_hold_do_register, double_hold_interrupt_kc, \
	                    double_tap_kc, double_tap_do_register, double_tap_interrupt_kc) \
	; mf_handle_key_event(record, &(mf_key_config) { \
		.tap = { .keycode = tap_kc, .interrupt_keycode = tap_interrupt_kc, .do_register = tap_do_register }, \
		.hold = { .keycode = hold_kc, .interrupt_keycode = hold_interrupt_kc, .do_register = hold_do_register }, \
		.double_tap = { .keycode = double_tap_kc, .interrupt_keycode = double_tap_interrupt_kc, .do_register = false }, \
		.double_hold = { .keycode = double_hold_kc, .interrupt_keycode = double_hold_interrupt_kc, .do_register = double_hold_do_register } \
	});


/*
 * TAP/HOLD STRING MACROS
 */
 #define MF_STR_TAP_HOLD(tap_str, hold_str) \
	; MF_STR_KEY_ADVANCED(tap_str, hold_str, "", "" );

 #define MF_STR_TAP(str) \
	; MF_STR_KEY_ADVANCED(str, "", "", "" );


#define MF_STR_KEY_ADVANCED(tap_str, hold_str, double_tap_str, double_hold_str) \
	; mf_handle_key_event(record, &(mf_key_config) { \
		.tap = { .string = tap_str, .keycode = MF_NOKEY  }, \
		.hold = { .string = hold_str, .keycode = MF_NOKEY }, \
		.double_tap = { .string = double_tap_str }, \
		.double_hold = { .string = double_hold_str } \
	});


/*
 * TAP/HOLD FUNCTION MACROS
 */
#define MF_TAP_HOLD_FN(tap_fn, hold_fn) \
	; MF_KEY_FN(tap_fn, hold_fn, MF_NOFN, MF_NOFN, \
	            MF_NOFN, MF_NOFN, MF_NOFN \
	            );

#define MF_TAP_HOLD_DOUBLE_FN(tap_fn, hold_fn, double_tap_fn, double_hold_fn) \
	; MF_KEY_FN(tap_fn, hold_fn, double_tap_fn, double_hold_fn, \
	            MF_NOFN, MF_NOFN, MF_NOFN \
	            );

#define MF_KEY_FN(tap_fn, hold_fn, double_tap_fn, double_hold_fn, \
	              tap_release_fn, hold_release_fn, double_hold_release_fn \
	              ) \
	; mf_handle_key_event(record,&(mf_key_config) { \
		.tap = { .fn = tap_fn, .fn_release = tap_release_fn }, \
		.hold = { .fn = hold_fn, .fn_release = hold_release_fn }, \
		.double_tap = { .fn = double_tap_fn }, \
		.double_hold = { .fn = double_hold_fn, .fn_release = double_hold_release_fn } \
	});

#define MF_TAP_HOLD_MIXED(tap_kc, tap_str, hold_kc, hold_str) \
	; mf_handle_key_event(record, &(mf_key_config) { \
		.tap = { .string = tap_str, .keycode = tap_kc  }, \
		.hold = { .string = hold_str, .keycode = hold_kc }, \
	});

#define MF_TAP_HOLD_DOUBLE_MIXED(tap_kc, tap_str, hold_kc, hold_str, double_hold_kc, double_tap_str, double_hold_str) \
	; mf_handle_key_event(record, &(mf_key_config) { \
		.tap = { .string = tap_str, .keycode = tap_kc  }, \
		.hold = { .string = hold_str, .keycode = hold_kc }, \
		.double_tap = { .string = double_tap_str }, \
		.double_hold = { .string = double_hold_str } \
	});
