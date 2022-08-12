#include QMK_KEYBOARD_H
#include "../definitions/layers.h"
#include "../definitions/keycodes.h"

/**
 * TAP DANCE CODES
 */
enum tap_dance_codes {
	DANCE_SPOTLIGHT,
	DANCE_TAB_LAST_APP,
	DANCE_TAB_MGMT,
	DANCE_PGUP_HOME,
	DANCE_PGDN_END,
	DANCE_ZOOM_OUT,
	DANCE_SEMICOLON,
	DANCE_SLASH_COLON,
	DANCE_QUOTE,
	DANCE_DOT,
	DANCE_12,
	DANCE_13,
	DANCE_14,
	DANCE_15,
	DANCE_16,
	DANCE_DQUOTE,
	DANCE_18,
	DANCE_L_QUOTE,
	DANCE_GTEQ,
	DANCE_LTEQ,
	DANCE_DESKTOP,
	// DANCE_C,

	// leave this for initializing dance_state in tapdance.h
	NUM_DANCE_CODES,
};


// TAP DANCE KEY CODES
#define _ZOOM_OUT_100 TD(DANCE_ZOOM_OUT)
#define _VOL_DOWN TD(DANCE_12)
#define _PLAY TD(DANCE_13)
#define _QUOTE TD(DANCE_QUOTE)
#define _DQUOTE TD(DANCE_DQUOTE)
#define _DOT TD(DANCE_DOT)
#define _TAB_MGMT TD(DANCE_TAB_MGMT)
#define _PGUP_HOME TD(DANCE_PGUP_HOME)
#define _PGDN_END TD(DANCE_PGDN_END)
#define _DESKTOP TD(DANCE_DESKTOP)
#define _SPOTLIGHT TD(DANCE_SPOTLIGHT)
#define _LAST_APP TD(DANCE_TAB_LAST_APP)
#define _SLASH_COLON TD(DANCE_SLASH_COLON)
#define _SEMICOLON TD(DANCE_SEMICOLON)
#define _LCBR TD(DANCE_15)
#define _LBRACKET TD(DANCE_16)
#define _LPRN TD(DANCE_18)
#define _GTEQ TD(DANCE_GTEQ)
#define _LTEQ TD(DANCE_LTEQ)
#define _HYPHEN TD(DANCE_14)
//#define _KC_C TD(DANCE_C)


typedef struct {
	bool is_press_action;
	uint8_t step;
} tap;

enum {
	SINGLE_TAP = 1,
	SINGLE_HOLD,
	DOUBLE_TAP,
	DOUBLE_HOLD,
	DOUBLE_SINGLE_TAP,
	MORE_TAPS
};


uint8_t dance_step(qk_tap_dance_state_t *state);
