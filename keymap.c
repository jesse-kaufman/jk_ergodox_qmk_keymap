#include QMK_KEYBOARD_H
#include "version.h"
#include "definitions/keycodes.h"
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
		MEH(KC_F13),	___X___,		___X___,		_SCRNSHT1,		_SCRNSHT2,		___X___,		_PREV_DESK,												_NEXT_DESK,		___X___,		___X___,		___X___,		___X___,		___X___,		_TAB_CLOSE_UN,
		_APP_TABS,		KC_Q,			KC_W,			KC_F,			KC_P,			KC_B,			_ACTION_KEY1,											_NEW_MIN,		KC_J,			KC_L,			KC_U,			KC_Y,			_PAREN,			TO(_NUM),
		_APP_WINDOWS,	KC_A,			KC_R,			_KC_S,			_KC_T,			KC_G,																					KC_M,			KC_N,			_KC_E,			KC_I,			KC_O,			KC_PGUP,
		_FN_KEY,		KC_Z,			KC_X,			KC_C,			KC_D,			_KC_V,			KC_LEAD,												CAPS_WORD,		_KC_K,			KC_H,			KC_COMMA,		_DOT,			KC_QUES,		KC_PGDOWN,
		_UNDO,			_REDO,			KC_LCTL,		KC_LOPT,		KC_LSFT,																												_SYM_KEY,		KC_RCMD,		KC_DOWN,		KC_UP,			_FN_KEY,
																										_ZOOM_OUT,		_ZOOM_IN,				_VOL_DOWN,		_VOL_UP,
																														KC_ESC,					_PLAY,
																						_SPACE,			KC_LCMD,		_ACTION_KEY2,			KC_LEAD,		KC_LSFT,	_SHFT_ENTER
	),

	// SYM layer
	[_SYM] = LAYOUT_ergodox_pretty(
		_______,		_LDFQUO,		_RDFQUO,		_LFQUO,			_RFQUO,			___X___,		_______,												_______,		___X___,		___X___,		___X___,		___X___,		___X___,		_______,
		TO(_BASE),		KC_GRAVE,		KC_AT,			KC_DLR,			_KC_HASH,		KC_PERC,		_______,												_______,		___X___,		KC_AMPR,		KC_UNDS,		KC_PIPE,		_BRACKET,		TO(_NUM),
		_______,		KC_TILD,		KC_ASTR,		_DASH,			_EQUAL,			KC_CIRC,																				___X___,		_LPRN,			KC_COLON,		_RPRN,			___X___,		_______,
		_______,		___X___,		KC_SLASH,		KC_BSLASH,		KC_PLUS,		___X___,		_______,												_______,		___X___,		_LTEQ,			KC_SCOLON,		_GTEQ,			___X___,		_______,
		_______, 		_______,		_______,		_______,		_SYM_KEY,																												TO(_BASE),		_______,		_______,		_______,		TO(_BASE),
																										_______,		_______,				_______,		KC_APP,
																														_______,				_______,
																						_______,		_______,		_______,				_______,		_______,		_______
	),

	// CODE layer
	[_CODE] = LAYOUT_ergodox_pretty(
		_______,		___X___,		___X___,		___X___,		___X___,		___X___,		_______,												_______,		___X___,		___X___,		___X___,		___X___,		___X___,		_______,
		TO(_BASE),		___X___,		___X___,		_COMMENT,		_BEG_CBLOCK,	_END_CBLOCK,	_______,												_______,		___X___,		___X___,		KC_LCBR,		___X___,		_CBRACKET,		TO(_NUM),
		_______,		___X___,		KC_ASTR,		_SARROW,		_DARROW,		_NIX_HOME,																				___X___,		KC_LBRACKET,	___X___,		KC_RBRACKET,	___X___,		_______,
		_______,		___X___,		KC_SLASH,		KC_BSLASH,		_UP_DIR,		_CUR_DIR,		_______,												_______,		___X___,		_HTML_OPEN,		KC_RCBR,		_HTML_CLOSE,	___X___,		_______,
		_______,		_______,		_______,		_______,		_SYM_KEY,																												_______,		_______,		_______,		_______,		TO(_BASE),
																										_______,		_______,				_______,		_______,
																														_______,				_______,
																						_______,		_______,		_______,				_______,		_______,		_______
	),

	// NUM layer
	[_NUM] = LAYOUT_ergodox_pretty(
		_______,		___X___,		___X___,		___X___,		___X___,		___X___,		_______,												_______,		___X___,		___X___,		___X___,		___X___,		___X___,		_______,
		TO(_BASE),		___X___,		_______,		_______,		_______,		___X___,		_______,												_______,		___X___,		KC_7,			KC_8,			KC_9,			KC_EQUAL,		TO(_BASE),
		_______,		___X___,		KC_ASTR,		___X___,		KC_EQUAL,		___X___,																				___X___,		KC_4,			KC_5,			KC_6,			___X___,		_______,
		_______,		___X___,		KC_SLASH,		___X___,		KC_PLUS,		___X___,		_______,												_______,		KC_MINUS,		KC_1,			KC_2,			_KC_3,			___X___,		_______,
		_______,		_______,		_______,		_______,		_______,																												KC_MINUS,		_______,		_______,		_______,		TO(_BASE),
																										_______,		_______,				_______,		_______,
																														_______,				_______,
																						_______,		_______,		_______,				_______,		_______,		KC_0
	),

	// FN layer
	[_FN] = LAYOUT_ergodox_pretty(
		_______,		___X___,		___X___,		___X___,		___X___,		___X___,		_______,												_______,		___X___,		___X___,		___X___,		___X___,		___X___,		_______,
		TO(_BASE),		___X___,		LCMD(KC_W),		LCMD(KC_F),		MEH(KC_P),		MEH(KC_5),		_______,												_______,		MEH(KC_UP),		KC_PGUP,		KC_UP,			___X___,		KC_HOME,		TO(_NUM),
		_______,		___X___,		KC_LSFT,		MO(_NUM),		MEH(KC_U),		MEH(KC_6),																				LOPT(KC_LEFT),	KC_LEFT,		KC_DOWN,		KC_RIGHT,		LOPT(KC_RIGHT),	_______,
		_______,		___X___,		_FN_X,			MEH(KC_0),		MEH(KC_D),		MEH(KC_E),		_______,												_______,		MEH(KC_DOWN),	KC_PGDOWN,		___X___,		KC_DOT,			KC_END,			_______,
		_______,		_______,		_______,		_______,		_______,																												_______,		_______,		KC_LEFT,		KC_RIGHT,		TO(_BASE),
																										_SCREEN_DN,		_SCREEN_UP,				_______,		_______,
																														_______,				_______,
																						_______,		_______,		_______,				_______,		_______,		_______
	),
};







#define _C_BASE {174,255,0}
#define _C_SYM {0,200,255}
#define _C_FN {255,0,251}
#define _C_CODE {40, 1, 145}
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
				_C_CODE,			_C_CODE,			_C_CODE,			_C_CODE,			_C_CODE,
				_C_CODE,			_C_CODE,			_C_CODE,			_C_CODE,			_C_CODE,
				_C_CODE,			_C_CODE,			_C_CODE,			_C_CODE,			_C_CODE,
				_C_CODE,			_C_CODE,			_C_CODE,			_C_CODE,			_C_CODE,
									_C_CODE,			_C_CODE,			_C_CODE,			_C_CODE,

				// LEFT HAND SIDE (MIRRORED)
				_C_CODE,			_C_CODE,			_C_CODE,			_C_CODE,			_C_CODE,
				_C_CODE,			_C_CODE,			_C_CODE,			_C_CODE,			_C_CODE,
				_C_CODE,			_C_CODE,			_C_CODE,			_C_CODE,			_C_CODE,
				_C_CODE,			_C_CODE,			_C_CODE,			_C_CODE,			_C_CODE,
									_C_CODE,			_C_CODE,			_C_CODE,			_C_CODE
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
};
