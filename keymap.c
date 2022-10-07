#include QMK_KEYBOARD_H
#include "version.h"
#include "definitions/keycodes.h"
#include "features/tapdance.h"
#include "features/leader.h"

void matrix_scan_user(void) {
	my_leader_matrix_scan_user();
}


/**
 * KEYMAP LAYOUT
 */
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
	// COLEMAK BASE layer
	[_BASE] = LAYOUT_ergodox_pretty(
		TT(_FN),		___X___,		___X___,		SCMD(KC_4),		SCMD(KC_5),		___X___,	_PREV_DESK,													_DESKTOP,	 	___X___,		___X___,		___X___,		___X___,		___X___,		_TAB_MGMT,
		MEH(KC_F13),	KC_Q,			KC_W,			KC_F,			KC_P,			KC_G,		KC_ESC,														TT(_NUM),		KC_J,			KC_L,			KC_U,			KC_Y,			_HYPHEN,		LGUI(KC_M),
		_APP_WINDOWS,	_KC_A,			_KC_R,			_KC_S,			_KC_T,			KC_D,																					KC_M,			KC_N,			_KC_E,			KC_I,			KC_O,			KC_PGUP,
		_APP_TABS,		KC_Z,			KC_X,			KC_C,			KC_V,			KC_B,		KC_LEAD,													OSL(_CODE),	 	_KC_K,			KC_H,			_COMMA,			_DOT,			KC_QUES,		KC_PGDOWN,
		_UNDO,			_REDO,			_OSM_CTR,		_OSM_OPT,		_OSM_LSHIFT,																											OSL(_SYM),		_OSM_RCMD,		KC_DOWN,		KC_UP,			TT(_FN),
																									_ZOOM_OUT,		_ZOOM_IN,					_VOL_DOWN,		_VOL_UP,
																													MEH(KC_F19),				_PLAY,
																						_SPACE,		_OSM_LCMD,		MEH(KC_F20),				KC_LEAD,		_OSM_LSHIFT,	_SHFT_ENTER
	),
	// SYM layer
	[_SYM] = LAYOUT_ergodox_pretty(
		_______,		_LDFQUO,		_RDFQUO,		_LFQUO,			_RFQUO,			___X___,		_______,												_______,		___X___,		___X___,		___X___,		___X___,		___X___,		_______,
		_______,		___X___,		KC_AT,			KC_HASH,		KC_PERC,		___X___,		_______,												TO(_NUM),		___X___,		KC_AMPR,		KC_COLON,		_DQUOTE,		KC_UNDS,		_______,
		_______,		___X___,		_HYPHEN,		KC_ASTR,		KC_EQUAL,		_GTEQ,																					___X___,		_LPRN,			_LBRACKET,		_LCURLBR,		_DQUOTE,		_______,
		_______,		___X___,		KC_SLASH,		KC_PLUS,		KC_CIRC,		_LTEQ,			_______,												TO(_CODE),		___X___,		KC_DLR,			_KC_SCOLN,		KC_EXLM,		KC_SLASH,		_______,
		_______, 		_______,		_______,		_______,		_______,																												TO(_BASE),		_______,		_______,		_______,		TO(_BASE),
																										_______,		_______,				_______,		KC_APP,
																														_______,				_______,
																						_______,		_______,		_______,				_______,		_______,		TO(_BASE)
	),
	// NUM layer
	[_NUM] = LAYOUT_ergodox_pretty(
		___X___,		___X___,		___X___,		___X___,		___X___,		___X___,		_______,												_______,		___X___,		___X___,		___X___,		___X___,		___X___,		_______,
		_______,		___X___,		_______,		_______,		_______,		___X___,		_______,												TO(_BASE),		___X___,		KC_7,			KC_8,			KC_9,			KC_MINUS,		_______,
		_______,		___X___,		KC_MINUS,		KC_ASTR,		KC_EQUAL,		___X___,																				___X___,		KC_4,			KC_5,			KC_6,			KC_PLUS,		_______,
		_______,		___X___,		KC_SLASH,		KC_PLUS,		KC_MINUS,		___X___,		_______,												TO(_CODE),		KC_DOT,			KC_1,			KC_2,			KC_3,			KC_DOT,			_______,
		_______,		_______,		_______,		_______,		_______,																												TO(_BASE),		_______,		_______,		_______,		TO(_BASE),
																										_______,		_______,				_______,		_______,
																														_______,				_______,
																						_______,		_______,		_______,				_______,		_______,		KC_0
	),
	// CODE layer
	[_CODE] = LAYOUT_ergodox_pretty(
		_______,		___X___,		___X___,		___X___,		___X___,		___X___,		_______,												_______,		___X___,		___X___,		___X___,		___X___,		___X___,		_______,
		_______,		___X___,		___X___,		_KC_COMMENT,	_KC_ML_COMMENT,	___X___,		_______,												TO(_NUM),		___X___,		KC_TILD,		KC_PIPE,		___X___,		_______,		_______,
		_______,		___X___,		___X___,		_KC_NIX_HOME,	___X___,		___X___,																				___X___,		_MEH_LPRN,		_MEH_LBRKT,		_MEH_RBRKT,		___X___,		_______,
		_______,		___X___,		___X___,		_KC_UP_DIR,		___X___,		___X___,		_______,												TO(_BASE),		___X___,		KC_BSLASH,		KC_GRAVE,		___X___,		___X___,		_______,
		_______,		_______,		_______,		_______,		_______,																												TO(_BASE),		_______,		_______,		_______,		TO(_BASE),
																										_______,		_______,				_______,		_______,
																														_______,				_______,
																						_______,		_______,		_______,				_______,		_______,		_______
	),
	// FN layer
	[_FN] = LAYOUT_ergodox_pretty(
		_______,		___X___,		___X___,		___X___,		___X___,		___X___,		_______,												_______,		___X___,		___X___,		___X___,		___X___,		___X___,		_______,
		TO(_BASE),		___X___,		___X___,		___X___,		MEH(KC_P),		MEH(KC_5),		_______,												TO(_NUM),		_FORWARD,		KC_PGUP,		KC_UP,			___X___,		KC_HOME,		_______,
		_______,		___X___,		KC_LSFT,		MEH(KC_0),		MEH(KC_U),		MEH(KC_6),																				LALT(KC_LEFT),	KC_LEFT,		KC_DOWN,		KC_RIGHT,		LALT(KC_RIGHT),	_______,
		_______,		___X___,		MEH(KC_X),		___X___,		MEH(KC_D),		MEH(KC_E),		_______,												TO(_CODE),		_BACK,			KC_PGDOWN,		___X___,		KC_DOT,			KC_END,			_______,
		_______,		_______,		_______,		_______,		_______,																												TO(_BASE),		_______,		KC_LEFT,		KC_RIGHT,		TT(_MOUSE),
																										_SCREEN_DN,		_SCREEN_UP,				_______,		_______,
																														_______,				_______,
																						_______,		_______,		_______,				_______,		_______,		_______
	),
	// MOUSE layer
	[_MOUSE] = LAYOUT_ergodox_pretty(
		_______,		___X___,		___X___,		___X___,		___X___,		___X___,		_______,												_______,		_______,		_______,		_______,		_______,		_______,		_______,
		_______,		___X___,		___X___,		KC_MS_UP,		KC_MS_WH_DOWN,	___X___,		_______,												_______,		_______,		_______,		_______,		_______,		_______,		_______,
		_______,		___X___,		KC_MS_LEFT,		KC_MS_DOWN,		KC_MS_RIGHT,	KC_MS_BTN3,																				_______,		_______,		_______,		_______,		_______,		_______,
		_______,		___X___,		___X___,		___X___,		KC_MS_WH_UP,	KC_MS_BTN2,		_______,												_______,		_______,		_______,		_______,		_______,		_______,		_______,
		_______,		_______,		_______,		_______,		KC_MS_BTN1,																												_______,		_______,		_______,		_______,		_______,
																										_ZOOM_OUT,		_ZOOM_IN,				_______,		_______,
																														_______,				_______,
																						_______,		_______,		_______,				_______,		_______,		_______
	),
};







#define _C_BASE {174,255,0}
#define _C_SYM {0,200,255}
#define _C_FN {255,0,251}
#define _C_MOUSE {40, 1, 145}
#define _C_OFF {0,0,0}
#define _C_NUM {255,32,0}


/**
 * RGB MATRIX LAYOUT
 */
const uint8_t PROGMEM ledmap[][DRIVER_LED_TOTAL][3] = {
	[_BASE] = {
				// RIGHT HAND SIDE
				_C_BASE,		_C_BASE,		_C_BASE,		_C_BASE,		_C_BASE,
				_C_BASE,		_C_BASE,		_C_BASE,		_C_BASE,		_C_BASE,
				_C_BASE,		_C_BASE,		_C_BASE,		_C_BASE,		_C_BASE,
				_C_BASE,		_C_BASE,		_C_BASE,		_C_BASE,		_C_BASE,
				_C_BASE,		_C_BASE,		_C_BASE,		_C_BASE,

				// LEFT HAND SIDE (MIRRORED)
				_C_BASE,		_C_BASE,		_C_BASE,		_C_BASE,		_C_BASE,
				_C_BASE,		_C_BASE,		_C_BASE,		_C_BASE,		_C_BASE,
				_C_BASE,		_C_BASE,		_C_BASE,		_C_BASE,		_C_BASE,
				_C_BASE,		_C_BASE,		_C_BASE,		_C_BASE,		_C_BASE,
				_C_BASE,		_C_BASE,		_C_BASE,		_C_BASE
	},
	[_SYM] = {
				// RIGHT HAND SIDE
				_C_SYM,			_C_SYM,			_C_SYM,			_C_SYM,			_C_SYM,
				_C_SYM,			_C_SYM,			_C_SYM,			_C_SYM,			_C_SYM,
				_C_SYM,			_C_SYM,			_C_SYM,			_C_SYM,			_C_SYM,
				_C_SYM,			_C_SYM,			_C_SYM,			_C_SYM,			_C_SYM,
				_C_SYM,			_C_SYM,			_C_SYM,			_C_SYM,

				// LEFT HAND SIDE (MIRRORED)
				_C_SYM,			_C_SYM,			_C_SYM,			_C_SYM,			_C_SYM,
				_C_SYM,			_C_SYM,			_C_SYM,			_C_SYM,			_C_SYM,
				_C_SYM,			_C_SYM,			_C_SYM,			_C_SYM,			_C_SYM,
				_C_SYM,			_C_SYM,			_C_SYM,			_C_SYM,			_C_SYM,
				_C_SYM,			_C_SYM,			_C_SYM,			_C_SYM,
	},
	[_CODE] = {
				// RIGHT HAND SIDE
				_C_SYM,			_C_SYM,			_C_SYM,			_C_SYM,			_C_SYM,
				_C_SYM,			_C_SYM,			_C_SYM,			_C_SYM,			_C_SYM,
				_C_SYM,			_C_SYM,			_C_SYM,			_C_SYM,			_C_SYM,
				_C_SYM,			_C_SYM,			_C_SYM,			_C_SYM,			_C_SYM,
				{255,0,251},	_C_SYM,			_C_SYM,			_C_SYM,

				// LEFT HAND SIDE (MIRRORED)
				_C_SYM,			_C_SYM,			_C_SYM,			_C_SYM,			_C_SYM,
				_C_SYM,			_C_SYM,			_C_SYM,			_C_SYM,			_C_SYM,
				_C_SYM,			_C_SYM,			_C_SYM,			_C_SYM,			_C_SYM,
				_C_SYM,			_C_SYM,			_C_SYM,			_C_SYM,			_C_SYM,
				_C_SYM,			_C_SYM,			_C_SYM,			_C_SYM
	},
	[_NUM] = {
				// RIGHT HAND SIDE
				_C_NUM,			_C_NUM,			_C_NUM,			_C_NUM,			_C_NUM,
				_C_NUM,			_C_NUM,			_C_NUM,			_C_NUM,			_C_NUM,
				_C_NUM,			_C_NUM,			_C_NUM,			_C_NUM,			_C_NUM,
				_C_NUM,			_C_NUM,			_C_NUM,			_C_NUM,			_C_NUM,
				_C_NUM,			_C_NUM,			_C_NUM,			_C_NUM,

				// LEFT HAND SIDE (MIRRORED)
				_C_NUM,			_C_NUM,			_C_NUM,			_C_NUM,			_C_NUM,
				_C_NUM,			_C_NUM,			_C_NUM,			_C_NUM,			_C_NUM,
				_C_NUM,			_C_NUM,			_C_NUM,			_C_NUM,			_C_NUM,
				_C_NUM,			_C_NUM,			_C_NUM,			_C_NUM,			_C_NUM,
				_C_NUM,			_C_NUM,			_C_NUM,			_C_NUM
	},
	[_FN] = {
				// RIGHT HAND SIDE
				_C_FN,			_C_FN,			_C_FN,			_C_FN,			_C_FN,
				_C_FN,			_C_FN,			_C_FN,			_C_FN,			_C_FN,
				_C_FN,			_C_FN,			_C_FN,			_C_FN,			_C_FN,
				_C_FN,			_C_FN,			_C_FN,			_C_FN,			_C_FN,
				_C_FN,			_C_FN,			_C_FN,			_C_FN,

				// LEFT HAND SIDE (MIRRORED)
				_C_FN,			_C_FN,			_C_FN,			_C_FN,			_C_FN,
				_C_FN,			_C_FN,			_C_FN,			_C_FN,			_C_FN,
				_C_FN,			_C_FN,			_C_FN,			_C_FN,			_C_FN,
				_C_FN,			_C_FN,			_C_FN,			_C_FN,			_C_FN,
				_C_FN,			_C_FN,			_C_FN,			_C_FN
	},
	[_MOUSE] = {
				// RIGHT HAND SIDE
				_C_MOUSE,		_C_MOUSE,		_C_MOUSE,		_C_MOUSE,		_C_MOUSE,
				_C_MOUSE,		_C_MOUSE,		_C_MOUSE,		_C_MOUSE,		_C_MOUSE,
				_C_MOUSE,		_C_MOUSE,		_C_MOUSE,		_C_MOUSE,		_C_MOUSE,
				_C_MOUSE,		_C_MOUSE,		_C_MOUSE,		_C_MOUSE,		_C_MOUSE,
				_C_MOUSE,		_C_MOUSE,		_C_MOUSE,		_C_MOUSE,

				// LEFT HAND SIDE (MIRRORED)
				_C_MOUSE,		_C_MOUSE,		_C_MOUSE,		_C_MOUSE,		_C_MOUSE,
				_C_MOUSE,		_C_MOUSE,		_C_MOUSE,		_C_MOUSE,		_C_MOUSE,
				_C_MOUSE,		_C_MOUSE,		_C_MOUSE,		_C_MOUSE,		_C_MOUSE,
				_C_MOUSE,		_C_MOUSE,		_C_MOUSE,		_C_MOUSE,		_C_MOUSE,
				_C_MOUSE,		_C_MOUSE,		_C_MOUSE,		_C_MOUSE },
};
