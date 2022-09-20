
#include "keymap.h"

void matrix_scan_user(void) {
	my_leader_matrix_scan_user();
}


/**
 * KEYMAP LAYOUT
 */
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
	// COLEMAK-DH (YO MOD) BASE layer
	[_BASE] = LAYOUT_ergodox_pretty(
		XXXXXXX,		XXXXXXX,		XXXXXXX,		SCMD(KC_4),		SCMD(KC_5),		KC_F17,		_SPOTLIGHT,													_DESKTOP,	 	XXXXXXX,		XXXXXXX,		XXXXXXX,		XXXXXXX,		KC_F12,			_TAB_MGMT,
		TT(_FN),		KC_Q,			KC_W,			KC_F,			KC_P,			KC_G,		KC_ESC,														TT(_NUM),		KC_J,			KC_U,			KC_I,			KC_Y,			_QUOTE,			XXXXXXX,
		_APP_WINDOWS,	_KC_A,			_KC_R,			_KC_S,			_KC_T,			KC_D,																					KC_H,			KC_N,			KC_E,			KC_L,			KC_O,			_PGUP_HOME,
		_APP_TABS,		KC_Z,			KC_X,			KC_C,			KC_V,			KC_B,		_TAB,														KC_BSPACE, 		KC_K,			KC_M,			_COMMA,			_DOT,			KC_QUES,		_PGDN_END,
		_UNDO,			_REDO,			_OSM_CTR,		_OSM_OPT,		_OSM_LSHIFT,																											OSL(_SYM),		_OSM_RCMD,		KC_DOWN,		KC_UP,			TT(_FN),
																									_ZOOM_OUT,		_ZOOM_IN,				_VOL_DOWN,			_VOL_UP,
																													CAPS_WORD,				_PLAY,
																						_SPACE,		_OSM_LCMD,		KC_LEAD,				CAPS_WORD,			_OSM_RSHIFT,		_SHFT_ENTER
	),
	// SYM layer
	[_SYM] = LAYOUT_ergodox_pretty(
		_______,		_LDFQUO,		_RDFQUO,		_LFQUO,			_RFQUO,			XXXXXXX,		_______,												_______,		XXXXXXX,		XXXXXXX,		XXXXXXX,		XXXXXXX,		XXXXXXX,		_______,
		_______,		_KC_COMMENT,	KC_AT,			KC_HASH,		KC_DLR,			KC_PERC,		_______,												TO(_NUM),		KC_AMPR,		KC_PIPE,		_LBRACKET,		KC_RBRACKET,	XXXXXXX,		XXXXXXX,
		_______,		_KC_NIX_HOME,	KC_ASTR,		_HYPHEN,		KC_EQUAL,		KC_UNDS,																				KC_SCOLON,		KC_COLON,		_LPRN,			KC_RPRN,		_DQUOTE,		XXXXXXX,
		_______,		_KC_UP_DIR,		KC_SLASH,		KC_PLUS,		KC_CIRC,		KC_GRAVE,		_______,												_______,		KC_BSLASH,		KC_TILD,		_LTEQ,			_GTEQ,			KC_SLASH,		XXXXXXX,
		_______, 		_______,		_______,		_______,		_______,																												OSL(_CODE),		_______,		_______,		_______,		TO(_BASE),
																										_______,		_______,				_______,		KC_APP,
																														_______,				_______,
																						_______,		_______,		_______,				_______,		_______,		TO(_BASE)
	),
	// NUM layer
	[_NUM] = LAYOUT_ergodox_pretty(
		_______,		XXXXXXX,		XXXXXXX,		XXXXXXX,		XXXXXXX,		XXXXXXX,		_______,												_______,		XXXXXXX,		XXXXXXX,		XXXXXXX,		XXXXXXX,		XXXXXXX,		_______,
		_______,		XXXXXXX,		XXXXXXX,		XXXXXXX,		XXXXXXX,		XXXXXXX,		_______,												TO(_BASE),		XXXXXXX,		KC_7,			KC_8,			KC_9,			KC_PLUS,		XXXXXXX,
		_______,		KC_ASTR,		KC_ASTR,		KC_MINUS,		KC_EQUAL,		KC_EQUAL,																				XXXXXXX,		KC_4,			KC_5,			KC_6,			KC_MINUS,		XXXXXXX,
		_______,		KC_SLASH,		KC_SLASH,		KC_PLUS,		XXXXXXX,		XXXXXXX,		_______,												_______,		XXXXXXX,		KC_1,			KC_2,			KC_3,			KC_DOT,			XXXXXXX,
		_______,		_______,		_______,		_______,		_______,																												TO(_BASE),		_______,		_______,		_______,		TO(_BASE),
																										_______,		_______,				_______,		_______,
																														_______,				_______,
																						_______,		_______,		_______,				_______,		_______,		KC_0
	),
	// CODE layer
	[_CODE] = LAYOUT_ergodox_pretty(
		_______,		XXXXXXX,		XXXXXXX,		XXXXXXX,		XXXXXXX,		XXXXXXX,		_______,												_______,		XXXXXXX,		XXXXXXX,		XXXXXXX,		XXXXXXX,		XXXXXXX,		_______,
		_______,		XXXXXXX,		XXXXXXX,		XXXXXXX,		XXXXXXX,		XXXXXXX,		_______,												TO(_NUM),		XXXXXXX,		XXXXXXX,		_MEH_LBRKT,		XXXXXXX,		XXXXXXX,		XXXXXXX,
		_______,		XXXXXXX,		XXXXXXX,		XXXXXXX,		XXXXXXX,		XXXXXXX,																				XXXXXXX,		XXXXXXX,		MEH(KC_LPRN),	_MEH_RBRKT,		XXXXXXX,		XXXXXXX,
		_______,		XXXXXXX,		XXXXXXX,		XXXXXXX,		XXXXXXX,		XXXXXXX,		_______,												_______,		XXXXXXX,		XXXXXXX,		KC_LCBR,		KC_RCBR,		XXXXXXX,		XXXXXXX,
		_______,		_______,		_______,		_______,		_______,																												TO(_BASE),		_______,		_______,		_______,		TO(_BASE),
																										_______,		_______,				_______,		_______,
																														_______,				_______,
																						_______,		_______,		_______,				_______,		_______,		_______
	),
	// FN layer
	[_FN] = LAYOUT_ergodox_pretty(
		RESET,			RGB_VAD,		RGB_VAI,		RGB_SPD,		RGB_SPI,		RGB_MOD,		_______,												_______,		XXXXXXX,		XXXXXXX,		XXXXXXX,		XXXXXXX,		XXXXXXX,		_______,
		TO(_BASE),		XXXXXXX,		KC_BSPACE,		KC_ESCAPE,		XXXXXXX,		XXXXXXX,		_______,												TO(_NUM),		_FORWARD,		KC_PGUP,		KC_UP,			KC_HOME,		KC_HOME,		_______,
		_______,		XXXXXXX,		LSFT(KC_TAB),	KC_TAB,			XXXXXXX,		XXXXXXX,																				LALT(KC_LEFT),	KC_LEFT,		KC_DOWN,		KC_RIGHT,		LALT(KC_RIGHT),		_______,
		_______,		XXXXXXX,		XXXXXXX,		XXXXXXX,		XXXXXXX,		XXXXXXX,		_______,												_______,		_BACK,			KC_PGDOWN,		XXXXXXX,		KC_END,			KC_END,			_______,
		_______,		_______,		_______,		_______,		_______,																												TO(_BASE),		_______,		KC_LEFT,		KC_RIGHT,		TT(_MOUSE),
																										_SCREEN_DN,		_SCREEN_UP,				_______,		_______,
																														_______,				_______,
																						_______,		_______,		_______,				_______,		_______,		_______
	),
	// MOUSE layer
	[_MOUSE] = LAYOUT_ergodox_pretty(
		XXXXXXX,		XXXXXXX,		XXXXXXX,		XXXXXXX,		XXXXXXX,		XXXXXXX,		_______,												_______,		_______,		_______,		_______,		_______,		_______,		_______,
		XXXXXXX,		XXXXXXX,		XXXXXXX,		KC_MS_UP,		KC_MS_WH_DOWN,	XXXXXXX,		_______,												_______,		_______,		_______,		_______,		_______,		_______,		_______,
		XXXXXXX,		XXXXXXX,		KC_MS_LEFT,		KC_MS_DOWN,		KC_MS_RIGHT,	KC_MS_BTN3,																				_______,		_______,		_______,		_______,		_______,		_______,
		XXXXXXX,		XXXXXXX,		XXXXXXX,		XXXXXXX,		KC_MS_WH_UP,	KC_MS_BTN2,		_______,												_______,		_______,		_______,		_______,		_______,		_______,		_______,
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
				_C_SYM,			_C_SYM,			_C_SYM,			_C_SYM,			_C_SYM,
				_C_SYM,			_C_SYM,			_C_SYM,			_C_SYM,			_C_SYM,
				_C_SYM,			_C_SYM,			_C_SYM,			_C_SYM,			_C_SYM,
				_C_SYM,			_C_SYM,			_C_SYM,			_C_SYM,			_C_SYM,
				{255,32,0},		_C_SYM,			_C_SYM,			_C_SYM,

				// LEFT HAND SIDE (MIRRORED)
				_C_SYM,			_C_SYM,			_C_SYM,			_C_SYM,			_C_SYM,
				_C_SYM,			_C_SYM,			_C_SYM,			_C_SYM,			_C_SYM,
				_C_SYM,			_C_SYM,			_C_SYM,			_C_SYM,			_C_SYM,
				_C_SYM,			_C_SYM,			_C_SYM,			_C_SYM,			_C_SYM,
				_C_SYM,			_C_SYM,			_C_SYM,			_C_SYM
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
