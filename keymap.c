
#include "keymap.h"

void matrix_scan_user(void) {
	my_leader_matrix_scan_user();
}


/**
 * KEYMAP LAYOUT
 */
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
	// BASE layer
	[_BASE] = LAYOUT_ergodox_pretty(
		KC_F17,			XXXXXXX,		XXXXXXX,		XXXXXXX,		SCMD(KC_4),		SCMD(KC_5),		_SPOTLIGHT,												_DESKTOP,		XXXXXXX,		XXXXXXX,		XXXXXXX,		XXXXXXX,		XXXXXXX,		_TAB_MGMT,
		KC_F16,			_KC_Q,			_KC_W,			KC_E,			_KC_R,			_KC_T,			KC_ESC,													KC_LEAD,		KC_Y,			KC_U,			_KC_I,			_KC_O,			KC_P,			XXXXXXX,
		_LAST_APP,		_KC_A,			_KC_S,			KC_D,			_F_FN,			_KC_G,																					_KC_H,			KC_J,			KC_K,			KC_L,			_QUOTE,			_PGUP_HOME,
		_KC_COLEMAK,	KC_Z,			_KC_X,			_KC_C,			_KC_V,			_KC_B,			TT(_FN),												CAPS_WORD, 		_KC_N,			_KC_M,			KC_COMMA,		_DOT,			KC_QUES,		_PGDN_END,
		_UNDO,			_REDO,			_OSM_CTR,		_OSM_OPT,		_OSM_CMD,																												OSL(_SYM),		TT(_NUM),		KC_DOWN,		KC_UP,			TT(_FN),
																										_ZOOM_OUT_100,	_ZOOM_IN,				_VOL_DOWN,		_VOL_UP,
																														_OSM_SHIFT,				_PLAY,
																						_SHFT_SPACE,	KC_TAB,			KC_LEAD,				CAPS_WORD,		KC_BSPACE,		_SHFT_ENTER
	),
	// COLEMAK-DH BASE layer (TARMAK-1)
	[_COLEMAK] = LAYOUT_ergodox_pretty(
		KC_F17,			XXXXXXX,		XXXXXXX,		XXXXXXX,		SCMD(KC_4),		SCMD(KC_5),		_SPOTLIGHT,												_DESKTOP,		XXXXXXX,		XXXXXXX,		XXXXXXX,		XXXXXXX,		XXXXXXX,		_TAB_MGMT,
		KC_F16,			_KC_Q,			_KC_W,			KC_J,			_KC_R,			_KC_T,			KC_ESC,													KC_LEAD,		KC_Y,			KC_U,			_KC_I,			_KC_O,			KC_P,			XXXXXXX,
		_LAST_APP,		_KC_A,			_KC_S,			KC_D,			_F_FN,			_KC_G,																					_KC_M,			_KC_N,			KC_E,			KC_L,			_QUOTE,			_PGUP_HOME,
		_KC_QWERTY,		KC_Z,			_KC_X,			_KC_C,			_KC_V,			_KC_B,			TT(_FN),												CAPS_WORD,		KC_K,			_KC_H,			KC_COMMA,		_DOT,			KC_QUES,		_PGDN_END,
		_UNDO,			_REDO,			_OSM_CTR,		_OSM_OPT,		_OSM_CMD,																												OSL(_SYM),		TT(_NUM),		KC_DOWN,		KC_UP,			TT(_FN),
																										_ZOOM_OUT_100,	_ZOOM_IN,				_VOL_DOWN,		_VOL_UP,
																														_OSM_SHIFT,				_PLAY,
																						_SHFT_SPACE,	KC_TAB,			KC_LEAD,				CAPS_WORD,		KC_BSPACE,		_SHFT_ENTER
	),
	// SYM layer
	[_SYM] = LAYOUT_ergodox_pretty(
		_______,		XXXXXXX,		_LDFQUO,		_RDFQUO,		_LFQUO,			_RFQUO,			_______,												_______,		XXXXXXX,		XXXXXXX,		XXXXXXX,		XXXXXXX,		XXXXXXX,		_______,
		_______,		_KC_NIX_HOME,	KC_AT,			KC_HASH,		KC_DLR,			KC_PERC,		_______,												_______,		KC_AMPR,		KC_PIPE,		_LBRACKET,		KC_RBRACKET,	XXXXXXX,		_______,
		_______,		_KC_COMMENT,	KC_ASTR,		_HYPHEN,		KC_EQUAL,		KC_UNDS,																				KC_SCOLON,		KC_COLON,		_LPRN,			KC_RPRN,		_DQUOTE,		_______,
		_______,		_KC_UP_DIR,		KC_SLASH,		_______,		KC_CIRC,		KC_GRAVE,		_______,												_______,		KC_BSLASH,		KC_TILD,		_LTEQ,			_GTEQ,			KC_SLASH,		_______,
		_______, 		_______,		_______,		_______,		_______,																												OSL(_CODE),		TO(_BASE),		_______,		_______,		TO(_BASE),
																										_______,		_______,				_______,		KC_APP,
																														_______,				_______,
																						_______,		_______,		_______,				_______,		_______,		_______
	),
	// CODE layer
	[_CODE] = LAYOUT_ergodox_pretty(
		_______,		XXXXXXX,		XXXXXXX,		XXXXXXX,		XXXXXXX,		XXXXXXX,		_______,												_______,		XXXXXXX,		XXXXXXX,		XXXXXXX,		XXXXXXX,		XXXXXXX,		_______,
		_______,		XXXXXXX,		XXXXXXX,		XXXXXXX,		XXXXXXX,		XXXXXXX,		_______,												_______,		XXXXXXX,		XXXXXXX,		_MEH_LBRKT,		XXXXXXX,		XXXXXXX,		_______,
		_______,		XXXXXXX,		XXXXXXX,		XXXXXXX,		XXXXXXX,		XXXXXXX,																				XXXXXXX,		XXXXXXX,		MEH(KC_LPRN),	_MEH_RBRKT,		XXXXXXX,		_______,
		_______,		XXXXXXX,		XXXXXXX,		XXXXXXX,		XXXXXXX,		XXXXXXX,		_______,												_______,		XXXXXXX,		XXXXXXX,		KC_LCBR,		KC_RCBR,		XXXXXXX,		_______,
		_______,		_______,		_______,		_______,		_______,																												TO(_BASE),		TO(_BASE),		_______,		_______,		TO(_BASE),
																										_______,		_______,				_______,		_______,
																														_______,				_______,
																						_______,		_______,		_______,				_______,		_______,		_______
	),
	// NUM layer
	[_NUM] = LAYOUT_ergodox_pretty(
		_______,		XXXXXXX,		XXXXXXX,		XXXXXXX,		XXXXXXX,		XXXXXXX,		_______,												_______,		XXXXXXX,		XXXXXXX,		XXXXXXX,		XXXXXXX,		XXXXXXX,		_______,
		_______,		XXXXXXX,		XXXXXXX,		XXXXXXX,		XXXXXXX,		XXXXXXX,		_______,												_______,		XXXXXXX,		KC_7,			KC_8,			KC_9,			XXXXXXX,		_______,
		_______,		XXXXXXX,		KC_ASTR,		KC_MINUS,		KC_EQUAL,		XXXXXXX,																				KC_0,			KC_4,			KC_5,			KC_6,			XXXXXXX,		_______,
		_______,		XXXXXXX,		KC_SLASH,		KC_PLUS,		XXXXXXX,		XXXXXXX,		_______,												_______,		XXXXXXX,		KC_1,			KC_2,			KC_3,			KC_DOT,			_______,
		_______,		_______,		_______,		_______,		_______,																												TO(_BASE),		TO(_BASE),		_______,		_______,		TO(_BASE),
																										_______,		_______,				_______,		_______,
																														_______,				_______,
																						_______,		_______,		_______,				_______,		_______,		_______
	),
	// FN layer
	[_FN] = LAYOUT_ergodox_pretty(
		RESET,			RGB_VAD,		RGB_VAI,		RGB_SPD,		RGB_SPI,		RGB_MOD,		_______,												_______,		RGB_HUD,		RGB_HUI,		XXXXXXX,		_LAYER_LEDS,	XXXXXXX,		_______,
		_______,		XXXXXXX,		KC_BSPACE,		KC_ESCAPE,		XXXXXXX,		XXXXXXX,		_______,												_FORWARD,		LALT(KC_UP),	KC_PGUP,		KC_UP,			KC_HOME,		LALT(KC_DOWN),	_______,
		_______,		LSFT(KC_TAB),	KC_TAB,			XXXXXXX,		_OSM_CMD,		XXXXXXX,																				LALT(KC_LEFT),	KC_LEFT,		KC_DOWN,		KC_RIGHT,		LALT(KC_RIGHT),	KC_HOME,
		_______,		XXXXXXX,		XXXXXXX,		XXXXXXX,		XXXXXXX,		XXXXXXX,		TO(_BASE),												_BACK,			XXXXXXX,		KC_PGDOWN,		XXXXXXX,		KC_END,			XXXXXXX,		KC_END,
		_______,		_______,		_______,		_______,		_______,																												TO(_BASE),		TO(_BASE),		KC_LEFT,		KC_RIGHT,		TT(_MOUSE),
																										_SCREEN_DN,		_SCREEN_UP,				_______,		_______,
																														_______,				_______,
																						_______,		_______,		_______,				_______,		_______,		_______
	),
	// MOUSE layer
	[_MOUSE] = LAYOUT_ergodox_pretty(
		XXXXXXX,		XXXXXXX,		XXXXXXX,		KC_MS_BTN3,		XXXXXXX,		XXXXXXX,		_______,												_______,		XXXXXXX,		XXXXXXX,		XXXXXXX,		XXXXXXX,		XXXXXXX,		_______,
		_______,		KC_MS_WH_LEFT,	KC_MS_WH_RIGHT,	KC_MS_UP,		KC_MS_WH_UP,	XXXXXXX,		_______,												_FORWARD,		_______,		_______,		_______,		_______,		_______,		_______,
		_______,		KC_MS_BTN2,		KC_MS_LEFT,		KC_MS_DOWN,		KC_MS_RIGHT,	KC_MS_BTN1,																				_______,		_______,		_______,		_______,		_______,		_______,
		_______,		XXXXXXX,		XXXXXXX,		_SHFT_WHDN,		KC_MS_WH_DOWN,	_SHFT_WHUP,		_______,												_BACK,			_______,		_______,		_______,		_______,		_______,		_______,
		_______,		_______,		_______,		_______,		_______,																												TO(_BASE),		_______,		_______,		_______,		TO(_BASE),
																									_ZOOM_OUT_100,		_ZOOM_IN,				_______,		_______,
																														_______,				_______,
																						_______,		_______,		_______,				_______,		_______,		_______
	),
};



#define _C_BASE {174,255,0}
#define _C_SYM {0,200,255}
#define _C_FN {255,0,251}
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
	[_COLEMAK] = {
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
				{255,88,0},		_C_SYM,			_C_SYM,			_C_SYM,

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
				_C_OFF,			_C_OFF,			_C_OFF,			_C_OFF,			_C_OFF,
				_C_OFF,			{255,238,0},	{144,0,255},	{255,238,0},	_C_OFF,
				{0,208,255},	{144,0,255},	{144,0,255},	{144,0,255},	{0,208,255},
				_C_OFF,			{255,238,0},	_C_OFF,			{255,238,0},	_C_OFF,
				{40, 1, 145},	_C_OFF,			_C_OFF,			_C_OFF,

				// LEFT HAND SIDE (MIRRORED)
				_C_OFF,			_C_OFF,			{255,157,0},	_C_OFF,			_C_OFF,
				{0,208,255},	{0,208,255},	{144,0,255},	{0,208,255},	{0,208,255},
				{255,238,0},	{144,0,255},	{144,0,255},	{144,0,255},	{0,255,238},
				_C_OFF,			{0,208,255},	_C_OFF,			{0,208,255},	_C_OFF,
				{40, 1, 145},	_C_OFF,			_C_OFF,			_C_OFF },
};
