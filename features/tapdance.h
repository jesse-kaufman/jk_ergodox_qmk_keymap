#pragma once

/**
 * TAP DANCE CODES
 */
enum tap_dance_codes {
	DANCE_PREV_DESK,
	DANCE_TAB_MGMT,
	DANCE_QUOTE,
	DANCE_PAREN,
	DANCE_BRACKET,
	DANCE_CBRACKET,
	DANCE_PLAY,
	DANCE_DQUOTE,
	DANCE_DASH,
	DANCE_L_QUOTE,
	DANCE_GTEQ,
	DANCE_LTEQ,
	DANCE_DESKTOP,
	DANCE_APP_WINDOWS,

	// leave this for initializing dance_state in tapdance.c
	NUM_DANCE_CODES,
};


// TAP DANCE KEY CODES
#define _PLAY TD(DANCE_PLAY)
#define _QUOTE TD(DANCE_QUOTE)
#define _DQUOTE TD(DANCE_DQUOTE)
#define _TAB_MGMT TD(DANCE_TAB_MGMT)
#define _DESKTOP TD(DANCE_DESKTOP)
#define _PREV_DESK TD(DANCE_PREV_DESK)
#define _SLASH_COLON TD(DANCE_SLASH_COLON)
// #define _SEMICOLON TD(DANCE_SEMICOLON)
#define _LCBR TD(DANCE_CBRACKET)
#define _LBRACKET TD(DANCE_BRACKET)
#define _LPRN TD(DANCE_PAREN)
#define _HYPHEN TD(DANCE_DASH)


// STUFF FOR TAP DANCE
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
