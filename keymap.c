
#include "keymap.h"

/**
 * KEYMAP LAYOUT
 */
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
	// BASE layer
	[_BASE] = LAYOUT_ergodox_pretty(
		KC_F16,			KC_1,			KC_2,			KC_3,			KC_4,			KC_5,			_SPOTLIGHT,												_DESKTOP,		KC_6,			KC_7,			KC_8,			KC_9,			KC_0,			_TAB_MGMT,
		KC_F17,			KC_Q,			KC_W,			KC_E,			KC_R,			KC_T,			KC_ESC,													KC_LEAD,		KC_Y,			KC_U,			KC_I,			KC_O,			KC_P,			KC_F21,
		_LAST_APP,		KC_A,			KC_S,			KC_D,			_F_FN,			KC_G,																					KC_H,			KC_J,			KC_K,			KC_L,			_QUOTE,			_PGUP_HOME,
		KC_F19,			KC_Z,			KC_X,			KC_C,			KC_V,			KC_B,			TT(_FN),												XXXXXXX,		KC_N,			KC_M,			KC_COMMA,		_DOT,			KC_QUES,		_PGDN_END,
		_UNDO,			_REDO,			_OSM_CTR,		OSL(_CODE),		_OSM_CMD,																												OSL(_SYM),		_OSM_CMD,		KC_DOWN,		KC_UP,			TT(_FN),
																										_ZOOM_OUT_100,	_ZOOM_IN,				_VOL_DOWN,		_VOL_UP,
																														_OSM_SHIFT,				_PLAY,
																						_SHFT_SPACE,	KC_TAB,			_OSM_ALT,				CAPS_WORD,		KC_BSPACE,		_SHFT_ENTER
	),
	// SYM layer
	[_SYM] = LAYOUT_ergodox_pretty(
		_______,		XXXXXXX,		_LDFQUO,		_RDFQUO,		_LFQUO,			_RFQUO,			_______,												_______,		XXXXXXX,		XXXXXXX,		XXXXXXX,		XXXXXXX,		XXXXXXX,		_______,
		_______,		KC_EXLM,		KC_AT,			KC_HASH,		KC_DLR,			KC_PERC,		_______,												_______,		KC_AMPR,		KC_SCOLON,		_LBRACKET,		KC_RBRACKET,	KC_PIPE,		_______,
		_______,		XXXXXXX,		KC_ASTR,		_HYPHEN,		KC_EQUAL,		KC_UNDS,																				KC_TILD,		KC_COLON,		_LPRN,			KC_RPRN,		_DQUOTE,		_______,
		_______,		_UP_DIR,		KC_SLASH,		KC_PLUS,		KC_CIRC,		KC_GRAVE,		_______,												_______,		KC_BSLASH,		_SEMICOLON,		_LTEQ,			_GTEQ,			KC_SLASH,		_______,
		XXXXXXX, 		_______,		_______,		_______,		OSL(_CODE),																												OSL(_CODE),		_______,		_______,		_______,		TO(_BASE),
																										_______,		_______,				_______,		KC_APP,
																														_______,				_______,
																						_______,		_______,		_______,				_______,		_______,		_______
	),
	// CODE layer
	[_CODE] = LAYOUT_ergodox_pretty(
		_______,		XXXXXXX,		XXXXXXX,		XXXXXXX,		XXXXXXX,		XXXXXXX,		_______,												_______,		XXXXXXX,		XXXXXXX,		XXXXXXX,		XXXXXXX,		XXXXXXX,		_______,
		_______,		XXXXXXX,		XXXXXXX,		XXXXXXX,		XXXXXXX,		XXXXXXX,		_______,												_______,		XXXXXXX,		XXXXXXX,		_MEH_LBRKT,		_MEH_RBRKT,		XXXXXXX,		_______,
		_______,		XXXXXXX,		XXXXXXX,		XXXXXXX,		XXXXXXX,		XXXXXXX,																				XXXXXXX,		XXXXXXX,		MEH(KC_LPRN),	XXXXXXX,		XXXXXXX,		_______,
		_______,		XXXXXXX,		XXXXXXX,		XXXXXXX,		XXXXXXX,		XXXXXXX,		_______,												_______,		XXXXXXX,		XXXXXXX,		XXXXXXX,		XXXXXXX,		XXXXXXX,		_______,
		_______,		_______,		_______,		_______,		TO(_SYM),																												TO(_BASE),		_______,		_______,		_______,		_______,
																										_______,		_______,				_______,		_______,
																														_______,				_______,
																						_______,		_______,		_______,				_______,		_______,		_______
	),
	// FN layer
	[_FN] = LAYOUT_ergodox_pretty(
		RESET,			RGB_VAD,		RGB_VAI,		RGB_SPD,		RGB_SPI,		RGB_MOD,		_______,												_______,		RGB_HUD,		RGB_HUI,		XXXXXXX,		_LAYER_LEDS,	XXXXXXX,		_______,
		_______,		XXXXXXX,		KC_BSPACE,		KC_ESCAPE,		KC_ESCAPE,		XXXXXXX,		_______,												_FORWARD,		LALT(KC_UP),	KC_PGUP,		KC_UP,			KC_HOME,		LALT(KC_DOWN),	_______,
		_______,		LSFT(KC_TAB),	KC_TAB,			XXXXXXX,		_OSM_CMD,		XXXXXXX,																LALT(KC_LEFT),	KC_LEFT,		KC_DOWN,		KC_RIGHT,		LALT(KC_RIGHT),	KC_HOME,
		_______,		XXXXXXX,		XXXXXXX,		XXXXXXX,		XXXXXXX,		XXXXXXX,		TO(_BASE),												_BACK,			XXXXXXX,		KC_PGDOWN,		XXXXXXX,		KC_END,			XXXXXXX,		KC_END,
		_______,		_______,		_______,		_______,		_______,																												TO(_BASE),		_______,		KC_LEFT,		KC_RIGHT,		TT(_MOUSE),
																										_SCREEN_DN,		_SCREEN_UP,				_PREV,			_NEXT,
																														_______,				_______,
																						_______,		_______,		_______,				_______,		_______,		_______
	),
	// MOUSE layer
	[_MOUSE] = LAYOUT_ergodox_pretty(
		XXXXXXX,		XXXXXXX,		XXXXXXX,		KC_MS_BTN3,		XXXXXXX,		XXXXXXX,		_______,												_______,		XXXXXXX,		XXXXXXX,		XXXXXXX,		XXXXXXX,		XXXXXXX,		_______,
		_______,		KC_MS_WH_LEFT,	KC_MS_WH_DOWN,	KC_MS_UP,		KC_MS_WH_UP,	_PREV,			_______,												_FORWARD,		_______,		_______,		_______,		_______,		_______,		_______,
		_______,		KC_MS_BTN2,		KC_MS_LEFT,		KC_MS_DOWN,		KC_MS_RIGHT,	KC_MS_BTN1,																				_______,		_______,		_______,		_______,		_______,		_______,
		_______,		_SHFT_WHDN,		XXXXXXX,		XXXXXXX,		KC_MS_WH_DOWN,	_SHFT_WHUP,		_______,												_BACK,			_______,		_______,		_______,		_______,		_______,		_______,
		_______,		_______,		_______,		_______,		_______,																												TO(_BASE),		_______,		_______,		_______,		TO(_BASE),
																									_ZOOM_OUT_100,		_ZOOM_IN,				_______,		_______,
																														_______,				_______,
																						_______,		_______,		_______,				_______,		_______,		_______
	),
};


/**
 * RGB MATRIX LAYOUT
 */
const uint8_t PROGMEM ledmap[][DRIVER_LED_TOTAL][3] = {
	[_BASE] = {
				// RIGHT HAND SIDE
				{174,255,0},	{174,255,0},	{174,255,0},	{174,255,0},	{174,255,0},
				{174,255,0},	{174,255,0},	{174,255,0},	{174,255,0},	{174,255,0},
				{174,255,0},	{174,255,0},	{174,255,0},	{174,255,0},	{174,255,0},
				{174,255,0},	{174,255,0},	{174,255,0},	{174,255,0},	{174,255,0},
				{174,255,0},	{174,255,0},	{174,255,0},	{174,255,0},

				// LEFT HAND SIDE (MIRRORED)
				{174,255,0},	{174,255,0},	{174,255,0},	{174,255,0},	{174,255,0},
				{174,255,0},	{174,255,0},	{174,255,0},	{174,255,0},	{174,255,0},
				{174,255,0},	{174,255,0},	{174,255,0},	{174,255,0},	{174,255,0},
				{174,255,0},	{174,255,0},	{174,255,0},	{174,255,0},	{174,255,0},
				{174,255,0},	{174,255,0},	{174,255,0},	{174,255,0}
	},
	[_SYM] = {
				// RIGHT HAND SIDE
				{0,200,255},	{0,200,255},	{0,200,255},	{0,200,255},	{0,200,255},
				{0,200,255},	{0,200,255},	{0,200,255},	{0,200,255},	{0,200,255},
				{0,200,255},	{0,200,255},	{0,200,255},	{0,200,255},	{0,200,255},
				{0,200,255},	{0,200,255},	{0,200,255},	{0,200,255},	{0,200,255},
				{0,200,255},	{0,200,255},	{0,200,255},	{0,200,255},

				// LEFT HAND SIDE (MIRRORED)
				{0,200,255},	{0,200,255},	{0,200,255},	{0,200,255},	{0,200,255},
				{0,200,255},	{0,200,255},	{0,200,255},	{0,200,255},	{0,200,255},
				{0,200,255},	{0,200,255},	{0,200,255},	{0,200,255},	{0,200,255},
				{0,200,255},	{0,200,255},	{0,200,255},	{0,200,255},	{0,200,255},
				{0,200,255},	{0,200,255},	{0,200,255},	{0,200,255}
	},
	[_CODE] = {
				// RIGHT HAND SIDE
				{0,200,255},	{0,200,255},	{0,200,255},	{0,200,255},	{0,200,255},
				{0,200,255},	{0,200,255},	{0,200,255},	{0,200,255},	{0,200,255},
				{0,200,255},	{0,200,255},	{0,200,255},	{0,200,255},	{0,200,255},
				{0,200,255},	{0,200,255},	{0,200,255},	{0,200,255},	{0,200,255},
				{255,0,251},	{0,200,255},	{0,200,255},	{0,200,255},

				// LEFT HAND SIDE (MIRRORED)
				{0,200,255},	{0,200,255},	{0,200,255},	{0,200,255},	{0,200,255},
				{0,200,255},	{0,200,255},	{0,200,255},	{0,200,255},	{0,200,255},
				{0,200,255},	{0,200,255},	{0,200,255},	{0,200,255},	{0,200,255},
				{0,200,255},	{0,200,255},	{0,200,255},	{0,200,255},	{0,200,255},
				{0,200,255},	{0,200,255},	{0,200,255},	{0,200,255}
	},
	[_FN] = {
				// RIGHT HAND SIDE
				{255,0,251},	{255,0,251},	{255,0,251},	{255,0,251},	{255,0,251},
				{255,0,251},	{255,0,251},	{255,0,251},	{255,0,251},	{255,0,251},
				{255,0,251},	{255,0,251},	{255,0,251},	{255,0,251},	{255,0,251},
				{255,0,251},	{255,0,251},	{255,0,251},	{255,0,251},	{255,0,251},
				{255,0,251},	{255,0,251},	{255,0,251},	{255,0,251},

				// LEFT HAND SIDE (MIRRORED)
				{255,0,251},	{255,0,251},	{255,0,251},	{255,0,251},	{255,0,251},
				{255,0,251},	{255,0,251},	{255,0,251},	{255,0,251},	{255,0,251},
				{255,0,251},	{255,0,251},	{255,0,251},	{255,0,251},	{255,0,251},
				{255,0,251},	{255,0,251},	{255,0,251},	{255,0,251},	{255,0,251},
				{255,0,251},	{255,0,251},	{255,0,251},	{255,0,251}
	},
	[_MOUSE] = {
				// RIGHT HAND SIDE
				{0,0,0},		{0,0,0},		{0,0,0},		{0,0,0},		{0,0,0},
				{0,0,0},		{255,238,0},	{144,0,255},	{255,238,0},	{0,0,0},
				{0,208,255},	{144,0,255},	{144,0,255},	{144,0,255},	{0,208,255},
				{0,0,0},		{255,238,0},	{0,0,0},		{255,238,0},	{0,0,0},
				{40, 1, 145},	{0,0,0},		{0,0,0},		{0,0,0},

				// LEFT HAND SIDE (MIRRORED)
				{0,0,0},		{0,0,0},		{255,157,0},	{0,0,0},		{0,0,0},
				{0,208,255},	{0,208,255},	{144,0,255},	{0,208,255},	{0,208,255},
				{255,238,0},	{144,0,255},	{144,0,255},	{144,0,255},	{0,255,238},
				{0,0,0},		{0,208,255},	{0,0,0},		{0,208,255},	{0,0,0},
				{40, 1, 145},	{0,0,0},		{0,0,0},		{0,0,0} },
};
