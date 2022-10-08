/*
 * TAPDANCE FUNCTIONALITY
 */

#include QMK_KEYBOARD_H
#include "../definitions/keycodes.h"
#include "tapdance.h"

// variable to hold current state of tap dance
static tap dance_state[NUM_DANCE_CODES];

// returns value of dance state
uint8_t dance_step(qk_tap_dance_state_t *state) {
	if (state->count == 1) {

		// single tap/hold actions

		if (state->interrupted || !state->pressed) {
			// single tap of key
			return SINGLE_TAP;
		}
		else {
			// Key has not been interrupted, but the key is still held, so send a single hold
			return SINGLE_HOLD;
		}
	}
	else if (state->count == 2) {

		// double tap/hold actions

		if (state->interrupted) {
			// DOUBLE_SINGLE_TAP is to distinguish between typing "pepper", and actually wanting a double tap
			// action when hitting 'pp'. Suggested use case for this return value is when you want to send two
			// keystrokes of the key, and not the 'double tap' action/macro.
			return DOUBLE_SINGLE_TAP;
		}
		else if (state->pressed) {
			// tap, then press and hold
			return DOUBLE_HOLD;
		}
		else  {
			// clean double-tap with no interrupt, do the double-tap action instead of typing 'pp' in 'pepper'
			// @see DOUBLE_SINGLE_TAP for pepper analogy
			return DOUBLE_TAP;
		}
	}
	else {
		// more than 2 taps have been received
		return MORE_TAPS;
	}
}





/***											***/
/***	CALLBACKS FOR TAPDANCE ACTIONS ARRAY	***/
/***											***/


/*
 * TAB MANAGEMENT
 */

void dance_tab_mgmt(qk_tap_dance_state_t *state, void *user_data) {
	dance_state[DANCE_TAB_MGMT].step = dance_step(state);
	switch (dance_state[DANCE_TAB_MGMT].step) {
		case SINGLE_TAP:
			tap_code16(LGUI(KC_T));
			break;

		case SINGLE_HOLD:
			tap_code16(LGUI(LSFT(KC_T)));
			break;

		case DOUBLE_TAP:
			tap_code16(LGUI(KC_W));
			break;
	}
}



/*
 * HYPHEN / EN DASH / EM DASH
 */

void dance_dash(qk_tap_dance_state_t *state, void *user_data) {
	if(state->count == 3) {
		tap_code16(KC_MINUS);
		tap_code16(KC_MINUS);
		tap_code16(KC_MINUS);
	}
	if(state->count > 3) {
		tap_code16(KC_MINUS);
	}
}
void dance_dash_finished(qk_tap_dance_state_t *state, void *user_data) {
	dance_state[DANCE_DASH].step = dance_step(state);
	switch (dance_state[DANCE_DASH].step) {
		case SINGLE_TAP:
			tap_code16(KC_MINUS);
			break;

		case SINGLE_HOLD:
			tap_code16(LALT(LSFT(KC_MINUS)));
			break;

		case DOUBLE_TAP:
			tap_code16(LALT(KC_MINUS));
			break;

		case DOUBLE_HOLD:
		case DOUBLE_SINGLE_TAP:
			tap_code16(KC_MINUS);
			register_code16(KC_MINUS);
			break;
	}
}
void dance_dash_reset(qk_tap_dance_state_t *state, void *user_data) {
	switch (dance_state[DANCE_DASH].step) {
		case DOUBLE_SINGLE_TAP:
		case SINGLE_TAP:
			unregister_code16(KC_MINUS);
			break;
	}
	dance_state[DANCE_DASH].step = 0;
}





qk_tap_dance_action_t tap_dance_actions[] = {
	[DANCE_TAB_MGMT] = ACTION_TAP_DANCE_FN(dance_tab_mgmt),
	[DANCE_DASH] = ACTION_TAP_DANCE_FN_ADVANCED(dance_dash, dance_dash_finished, dance_dash_reset),
};
