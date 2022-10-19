#pragma once

/**
 * TAP DANCE CODES
 */
enum tap_dance_codes {
	DANCE_TAB_MGMT,
	DANCE_DASH,

	// leave this for initializing dance_state in tapdance.c
	NUM_DANCE_CODES,
};


// TAP DANCE KEY CODES
#define _TAB_MGMT TD(DANCE_TAB_MGMT)
#define _HYPHEN TD(DANCE_DASH)


// STUFF FOR TAP DANCE
typedef struct {
	bool is_press_action;
	uint8_t step;
} tap;

enum {
	SINGLE_TAP = 1,
	SINGLE_TAP_INTERRUPT,
	SINGLE_HOLD,
	DOUBLE_TAP,
	DOUBLE_HOLD,
	DOUBLE_SINGLE_TAP,
	MORE_TAPS
};

uint8_t dance_step(qk_tap_dance_state_t *state);
