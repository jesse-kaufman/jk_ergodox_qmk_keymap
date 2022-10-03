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
 * DESKTOP / NEXT DESKTOP
 */

void dance_desktop(qk_tap_dance_state_t *state, void *user_data) {
	dance_state[DANCE_DESKTOP].step = dance_step(state);
	switch (dance_state[DANCE_DESKTOP].step) {
		case SINGLE_TAP:
			tap_code16(HYPR(KC_5));
			break;

		case SINGLE_HOLD:
			tap_code16(LCTL(KC_RIGHT));
			break;

		case DOUBLE_SINGLE_TAP:
		case DOUBLE_TAP:
			tap_code16(HYPR(KC_5));
			tap_code16(HYPR(KC_5));
			break;

		case MORE_TAPS:
			if(state->count == 3) {
				tap_code16(HYPR(KC_5));
				tap_code16(HYPR(KC_5));
				tap_code16(HYPR(KC_5));
			}
			if(state->count > 3) {
				tap_code16(HYPR(KC_5));
			}
			break;
	}
}


/*
 * SPOTLIGHT / PREVIOUS DESKTOP
 */

void dance_prev_desk(qk_tap_dance_state_t *state, void *user_data) {
	dance_state[DANCE_PREV_DESK].step = dance_step(state);
	switch (dance_state[DANCE_PREV_DESK].step) {
		case SINGLE_TAP:
			tap_code16(LGUI(KC_SPACE));
			break;

		case SINGLE_HOLD:
			tap_code16(LCTL(KC_LEFT));
			break;

		case DOUBLE_SINGLE_TAP:
		case DOUBLE_TAP:
			tap_code16(LGUI(KC_SPACE));
			tap_code16(LGUI(KC_SPACE));
			break;

		case MORE_TAPS:
			if(state->count == 3) {
				tap_code16(LGUI(KC_SPACE));
				tap_code16(LGUI(KC_SPACE));
				tap_code16(LGUI(KC_SPACE));
			}
			if(state->count > 3) {
				tap_code16(LGUI(KC_SPACE));
			}
			break;
	}
}



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
 * SPACE / LAST APP
 */

void dance_space_last_app(qk_tap_dance_state_t *state, void *user_data) {
	if(state->count == 3) {
		tap_code(KC_SPACE);
		tap_code(KC_SPACE);
		tap_code(KC_SPACE);
	}
	if(state->count > 3) {
		tap_code(KC_SPACE);
	}
}
void dance_space_last_app_finished(qk_tap_dance_state_t *state, void *user_data) {
	dance_state[DANCE_SPACE_LAST_APP].step = dance_step(state);
	switch (dance_state[DANCE_SPACE_LAST_APP].step) {
		case DOUBLE_HOLD:
		case SINGLE_TAP:
			register_code(KC_SPACE);
			break;

		case SINGLE_HOLD:
			tap_code16(LGUI(KC_TAB));
			break;

		case DOUBLE_TAP:
		case DOUBLE_SINGLE_TAP:
			tap_code(KC_SPACE);
			tap_code(KC_SPACE);
			break;
	}
}
void dance_space_last_app_reset(qk_tap_dance_state_t *state, void *user_data) {
	dance_state[DANCE_SPACE_LAST_APP].step = dance_step(state);
	switch (dance_state[DANCE_SPACE_LAST_APP].step) {
		case SINGLE_TAP:
		case DOUBLE_HOLD:
		case DOUBLE_TAP:
		case DOUBLE_SINGLE_TAP:
			unregister_code(KC_SPACE);
			break;
	}

	dance_state[DANCE_SPACE_LAST_APP].step = 0;
}


/*
 * QUOTE / DOUBLE QUOTE
 */

void dance_quote(qk_tap_dance_state_t *state, void *user_data) {
	if(state->count == 3) {
		tap_code(KC_QUOTE);
		tap_code(KC_QUOTE);
		tap_code(KC_QUOTE);
	}
	if(state->count > 3) {
		tap_code(KC_QUOTE);
	}
}
void dance_quote_finished(qk_tap_dance_state_t *state, void *user_data) {
	dance_state[DANCE_QUOTE].step = dance_step(state);
	switch (dance_state[DANCE_QUOTE].step) {
		case SINGLE_TAP:
			register_code(KC_QUOTE);
			break;

		case SINGLE_HOLD:
			register_code16(KC_DQUO);
			break;

		case DOUBLE_TAP:
			tap_code(KC_QUOTE);
			tap_code(KC_QUOTE);
			clear_mods();
			tap_code(KC_LEFT);
			break;

		case DOUBLE_HOLD:
			tap_code16(KC_DQUO);
			tap_code16(KC_DQUO);
			clear_mods();
			tap_code(KC_LEFT);
			break;
	}
}
void dance_quote_reset(qk_tap_dance_state_t *state, void *user_data) {
	switch (dance_state[DANCE_QUOTE].step) {
		case SINGLE_TAP:
			unregister_code(KC_QUOTE);
			break;

		case SINGLE_HOLD:
			unregister_code16(KC_DQUO);
			break;
	}
	dance_state[DANCE_QUOTE].step = 0;
}


/*
 * COMMA / QUOTE / DOUBLE QUOTE
 */

void dance_comma(qk_tap_dance_state_t *state, void *user_data) {
	if(state->count == 3) {
		tap_code(KC_COMMA);
		tap_code(KC_COMMA);
		tap_code(KC_COMMA);
	}
	if(state->count > 3) {
		tap_code(KC_COMMA);
	}
}
void dance_comma_finished(qk_tap_dance_state_t *state, void *user_data) {
	dance_state[DANCE_COMMA].step = dance_step(state);
	switch (dance_state[DANCE_COMMA].step) {
		case SINGLE_TAP:
			register_code(KC_COMMA);
			break;

		case SINGLE_HOLD:
			tap_code(KC_QUOTE);
			break;

		case DOUBLE_HOLD:
			register_code(KC_COMMA);
			break;

		case DOUBLE_TAP:
			tap_code16(KC_DQUO);
			break;

		case DOUBLE_SINGLE_TAP:
			tap_code(KC_COMMA);
			register_code(KC_COMMA);
	}
}
void dance_comma_reset(qk_tap_dance_state_t *state, void *user_data) {
	switch (dance_state[DANCE_COMMA].step) {
		case SINGLE_TAP:
			unregister_code(KC_COMMA);
			break;

		case DOUBLE_HOLD:
			unregister_code(KC_COMMA);
			break;

		case DOUBLE_SINGLE_TAP:
			unregister_code(KC_COMMA);
			break;
	}
	dance_state[DANCE_COMMA].step = 0;
}


/*
 * DOT / EXCLAMATION POINT
 */

void dance_dot(qk_tap_dance_state_t *state, void *user_data) {
	if(state->count == 3) {
		tap_code(KC_DOT);
		tap_code(KC_DOT);
		tap_code(KC_DOT);
	}
	if(state->count > 3) {
		tap_code(KC_DOT);
	}
}
void dance_dot_finished(qk_tap_dance_state_t *state, void *user_data) {
	dance_state[DANCE_DOT].step = dance_step(state);
	switch (dance_state[DANCE_DOT].step) {
		case SINGLE_TAP:
			register_code(KC_DOT);
			break;

		case SINGLE_HOLD:
			register_code16(KC_EXLM);
			break;

		case DOUBLE_HOLD:
			register_code(KC_DOT);
			break;

		case DOUBLE_TAP:
			tap_code(KC_DOT);
			register_code(KC_DOT);
			break;

		case DOUBLE_SINGLE_TAP:
			tap_code(KC_DOT);
			register_code(KC_DOT);
			break;
	}
}
void dance_dot_reset(qk_tap_dance_state_t *state, void *user_data) {
	switch (dance_state[DANCE_DOT].step) {
		case SINGLE_TAP:
		case DOUBLE_TAP:
		case DOUBLE_HOLD:
		case DOUBLE_SINGLE_TAP:
			unregister_code(KC_DOT);
			break;

		case SINGLE_HOLD:
			unregister_code16(KC_EXLM);
			break;
	}
	dance_state[DANCE_DOT].step = 0;
}


/*
 * PLAY / PAUSE
 */

void dance_play(qk_tap_dance_state_t *state, void *user_data) {
	dance_state[DANCE_PLAY].step = dance_step(state);
	switch (dance_state[DANCE_PLAY].step) {
		case SINGLE_TAP:
			tap_code16(KC_MEDIA_PLAY_PAUSE);
			break;

		case DOUBLE_HOLD:
			tap_code16(KC_PAUSE);
			break;

		case DOUBLE_TAP:
		case DOUBLE_SINGLE_TAP:
			tap_code16(KC_MEDIA_PLAY_PAUSE);
			tap_code16(KC_MEDIA_PLAY_PAUSE);
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
			register_code16(KC_MINUS);
			break;

		case SINGLE_HOLD:
			register_code16(LALT(LSFT(KC_MINUS)));
			break;

		case DOUBLE_TAP:
			register_code16(LALT(KC_MINUS));
			break;

		case DOUBLE_SINGLE_TAP:
			tap_code16(KC_MINUS);
			register_code16(KC_MINUS);
	}
}
void dance_dash_reset(qk_tap_dance_state_t *state, void *user_data) {
	switch (dance_state[DANCE_DASH].step) {
		case SINGLE_TAP:
			unregister_code16(KC_MINUS);
			break;

		case SINGLE_HOLD:
			unregister_code16(LALT(LSFT(KC_MINUS)));
			break;

		case DOUBLE_TAP:
			unregister_code16(LALT(KC_MINUS));
			break;

		case DOUBLE_SINGLE_TAP:
			unregister_code16(KC_MINUS);
			break;
	}
	dance_state[DANCE_DASH].step = 0;
}


/*
 * LEFT CURLY BRACKET / {}
 */

void dance_cbracket(qk_tap_dance_state_t *state, void *user_data) {
	if(state->count == 3) {
		tap_code16(KC_LCBR);
		tap_code16(KC_LCBR);
		tap_code16(KC_LCBR);
	}
	if(state->count > 3) {
		tap_code16(KC_LCBR);
	}
}
void dance_cbracket_finished(qk_tap_dance_state_t *state, void *user_data) {
	dance_state[DANCE_CBRACKET].step = dance_step(state);
	switch (dance_state[DANCE_CBRACKET].step) {
		case SINGLE_TAP:
			register_code16(KC_LCBR);
			break;

		case DOUBLE_TAP:
			register_code16(MEH(KC_RBRACKET));
			break;

		case DOUBLE_SINGLE_TAP:
			tap_code16(KC_LCBR);
			register_code16(KC_LCBR);
	}
}
void dance_cbracket_reset(qk_tap_dance_state_t *state, void *user_data) {
	switch (dance_state[DANCE_CBRACKET].step) {
		case SINGLE_TAP:
			unregister_code16(KC_LCBR);
			break;

		case DOUBLE_TAP:
			unregister_code16(MEH(KC_RBRACKET));
			break;

		case DOUBLE_SINGLE_TAP:
			unregister_code16(KC_LCBR);
			break;
	}
	dance_state[DANCE_CBRACKET].step = 0;
}


/*
 * LEFT BRACKET / []
 */

void dance_bracket(qk_tap_dance_state_t *state, void *user_data) {
	if(state->count == 3) {
		tap_code16(KC_LBRACKET);
		tap_code16(KC_LBRACKET);
		tap_code16(KC_LBRACKET);
	}
	if(state->count > 3) {
		tap_code16(KC_LBRACKET);
	}
}
void dance_bracket_finished(qk_tap_dance_state_t *state, void *user_data) {
	dance_state[DANCE_BRACKET].step = dance_step(state);
	switch (dance_state[DANCE_BRACKET].step) {
		case SINGLE_TAP:
			register_code16(KC_LBRACKET);
			break;

		case DOUBLE_TAP:
			tap_code16(KC_LBRACKET);
			tap_code16(KC_RBRACKET);
			unregister_code16(KC_LSFT);
			tap_code16(KC_LEFT);
			break;

		case DOUBLE_SINGLE_TAP:
			tap_code16(KC_LBRACKET);
			unregister_code16(KC_LSFT);
			register_code16(KC_LBRACKET);
	}
}
void dance_bracket_reset(qk_tap_dance_state_t *state, void *user_data) {
	//wait_ms(10);
	switch (dance_state[DANCE_BRACKET].step) {
		case SINGLE_TAP:
			unregister_code16(KC_LBRACKET);
			break;

		case DOUBLE_TAP:
			break;

		case DOUBLE_SINGLE_TAP:
			unregister_code16(KC_LBRACKET);
			break;
	}
	dance_state[DANCE_BRACKET].step = 0;
}


/*
 * DOUBLE QUOTE / ""
 */

void dance_dquote(qk_tap_dance_state_t *state, void *user_data) {
	if(state->count == 3) {
		tap_code16(KC_DQUO);
		tap_code16(KC_DQUO);
		tap_code16(KC_DQUO);
	}
	if(state->count > 3) {
		tap_code16(KC_DQUO);
	}
}
void dance_dquote_finished(qk_tap_dance_state_t *state, void *user_data) {
	dance_state[DANCE_DQUOTE].step = dance_step(state);
	switch (dance_state[DANCE_DQUOTE].step) {
		case SINGLE_TAP:
			register_code16(KC_DQUO);
			break;

		case DOUBLE_TAP:
			tap_code16(KC_DQUO);
			tap_code16(KC_DQUO);
			tap_code16(KC_LEFT);
			break;

		case DOUBLE_SINGLE_TAP:
			tap_code16(KC_DQUO);
			register_code16(KC_DQUO);
	}
}
void dance_dquote_reset(qk_tap_dance_state_t *state, void *user_data) {
	switch (dance_state[DANCE_DQUOTE].step) {
		case SINGLE_TAP:
			unregister_code16(KC_DQUO);
			break;

		case DOUBLE_TAP:
			break;

		case DOUBLE_SINGLE_TAP:
			unregister_code16(KC_DQUO);
			break;
	}
	dance_state[DANCE_DQUOTE].step = 0;
}


/*
 * OPEN PARENTHESIS / ()
 */

void dance_paren(qk_tap_dance_state_t *state, void *user_data) {
	if(state->count == 3) {
		tap_code16(KC_LPRN);
		tap_code16(KC_LPRN);
		tap_code16(KC_LPRN);
	}
	if(state->count > 3) {
		tap_code16(KC_LPRN);
	}
}
void dance_paren_finished(qk_tap_dance_state_t *state, void *user_data) {
	dance_state[DANCE_PAREN].step = dance_step(state);
	switch (dance_state[DANCE_PAREN].step) {
		case SINGLE_TAP:
			register_code16(KC_LPRN);
			break;

		case DOUBLE_TAP:
			tap_code16(KC_LPRN);
			tap_code16(KC_RPRN);
			tap_code16(KC_LEFT);
			break;

		case DOUBLE_SINGLE_TAP:
			tap_code16(KC_LPRN);
			register_code16(KC_LPRN);
	}
}
void dance_paren_reset(qk_tap_dance_state_t *state, void *user_data) {
	switch (dance_state[DANCE_PAREN].step) {
		case SINGLE_TAP:
			unregister_code16(KC_LPRN);
			break;

		case DOUBLE_TAP:
			break;

		case DOUBLE_SINGLE_TAP:
			unregister_code16(KC_LPRN);
			break;
	}
	dance_state[DANCE_PAREN].step = 0;
}


/*
 * GREATER THAN / >=
 */

void dance_gteq(qk_tap_dance_state_t *state, void *user_data) {
	if(state->count == 3) {
		tap_code16(KC_RABK);
		tap_code16(KC_RABK);
		tap_code16(KC_RABK);
	}
	if(state->count > 3) {
		tap_code16(KC_RABK);
	}
}
void dance_gteq_finished(qk_tap_dance_state_t *state, void *user_data) {
	dance_state[DANCE_GTEQ].step = dance_step(state);
	switch (dance_state[DANCE_GTEQ].step) {
		case SINGLE_TAP:
			register_code16(KC_RABK);
			break;

		case DOUBLE_TAP:
			tap_code16(KC_RABK);
			tap_code16(KC_EQUAL);
			break;

		case DOUBLE_SINGLE_TAP:
			tap_code16(KC_RABK);
			register_code16(KC_RABK);
	}
}
void dance_gteq_reset(qk_tap_dance_state_t *state, void *user_data) {
	switch (dance_state[DANCE_GTEQ].step) {
		case SINGLE_TAP:
			unregister_code16(KC_RABK);
			break;

		case DOUBLE_TAP:
			unregister_code16(MEH(KC_DOT));
			break;

		case DOUBLE_SINGLE_TAP:
			unregister_code16(KC_RABK);
			break;
	}
	dance_state[DANCE_GTEQ].step = 0;
}


/*
 * LESS THAN / <=
 */

void dance_lteq(qk_tap_dance_state_t *state, void *user_data) {
	if(state->count == 3) {
		tap_code16(KC_LABK);
		tap_code16(KC_LABK);
		tap_code16(KC_LABK);
	}
	if(state->count > 3) {
		tap_code16(KC_LABK);
	}
}
void dance_lteq_finished(qk_tap_dance_state_t *state, void *user_data) {
	dance_state[DANCE_LTEQ].step = dance_step(state);
	switch (dance_state[DANCE_LTEQ].step) {
		case SINGLE_TAP:
			register_code16(KC_LABK);
			break;

		case DOUBLE_TAP:
			tap_code16(KC_LABK);
			tap_code(KC_EQUAL);
			break;

		case DOUBLE_SINGLE_TAP:
			tap_code16(KC_LABK);
			register_code16(KC_LABK);
	}
}
void dance_lteq_reset(qk_tap_dance_state_t *state, void *user_data) {
	switch (dance_state[DANCE_LTEQ].step) {
		case SINGLE_TAP:
			unregister_code16(KC_LABK);
			break;

		case DOUBLE_TAP:
			unregister_code16(MEH(KC_COMMA));
			break;

		case DOUBLE_SINGLE_TAP:
			unregister_code16(KC_LABK);
			break;
	}
	dance_state[DANCE_LTEQ].step = 0;
}


/*
 * APP WINDOWS
 */

void dance_app_windows(qk_tap_dance_state_t *state, void *user_data) {
	if(state->count == 3) {
		tap_code16(LCMD(KC_GRAVE));
		tap_code16(LCMD(KC_GRAVE));
		tap_code16(LCMD(KC_GRAVE));
	}
	if(state->count > 3) {
		tap_code16(LCMD(KC_GRAVE));
	}
}
void dance_app_windows_finished(qk_tap_dance_state_t *state, void *user_data) {
	dance_state[DANCE_APP_WINDOWS].step = dance_step(state);
	switch (dance_state[DANCE_APP_WINDOWS].step) {
		case SINGLE_TAP:
			tap_code16(LCMD(KC_GRAVE));
			break;

		case DOUBLE_TAP:
			tap_code16(LCMD(KC_GRAVE));
			tap_code16(LCMD(KC_GRAVE));
			break;

		case SINGLE_HOLD:
			tap_code16(LCTL(KC_DOWN));
			break;
	}
}
void dance_app_windows_reset(qk_tap_dance_state_t *state, void *user_data) {
	dance_state[DANCE_APP_WINDOWS].step = 0;
}


/*
 * APP TABS
 */

void dance_app_tabs(qk_tap_dance_state_t *state, void *user_data) {
	if(state->count == 3) {
		tap_code16(LCTL(KC_TAB));
		tap_code16(LCTL(KC_TAB));
		tap_code16(LCTL(KC_TAB));
	}
	if(state->count > 3) {
		tap_code16(LCTL(KC_TAB));
	}
}
void dance_app_tabs_finished(qk_tap_dance_state_t *state, void *user_data) {
	dance_state[DANCE_APP_TABS].step = dance_step(state);
	switch (dance_state[DANCE_APP_TABS].step) {
		case SINGLE_TAP:
			tap_code16(LCTL(KC_TAB));
			break;

		case DOUBLE_TAP:
		case DOUBLE_SINGLE_TAP:
			tap_code16(LCTL(KC_TAB));
			tap_code16(LCTL(KC_TAB));
			break;
	}
}
void dance_app_tabs_reset(qk_tap_dance_state_t *state, void *user_data) {
	dance_state[DANCE_APP_TABS].step = 0;
}



qk_tap_dance_action_t tap_dance_actions[] = {
	[DANCE_PREV_DESK] = ACTION_TAP_DANCE_FN(dance_prev_desk),
	[DANCE_DESKTOP] = ACTION_TAP_DANCE_FN(dance_desktop),
	[DANCE_TAB_MGMT] = ACTION_TAP_DANCE_FN(dance_tab_mgmt),
	[DANCE_SPACE_LAST_APP] = ACTION_TAP_DANCE_FN_ADVANCED(dance_space_last_app, dance_space_last_app_finished, dance_space_last_app_reset),
	[DANCE_QUOTE] = ACTION_TAP_DANCE_FN_ADVANCED(dance_quote, dance_quote_finished, dance_quote_reset),
	[DANCE_COMMA] = ACTION_TAP_DANCE_FN_ADVANCED(dance_comma, dance_comma_finished, dance_comma_reset),
	[DANCE_DOT] = ACTION_TAP_DANCE_FN_ADVANCED(dance_dot, dance_dot_finished, dance_dot_reset),
	[DANCE_PLAY] = ACTION_TAP_DANCE_FN(dance_play),
	[DANCE_DASH] = ACTION_TAP_DANCE_FN_ADVANCED(dance_dash, dance_dash_finished, dance_dash_reset),
	[DANCE_CBRACKET] = ACTION_TAP_DANCE_FN_ADVANCED(dance_cbracket, dance_cbracket_finished, dance_cbracket_reset),
	[DANCE_BRACKET] = ACTION_TAP_DANCE_FN_ADVANCED(dance_bracket, dance_bracket_finished, dance_bracket_reset),
	[DANCE_DQUOTE] = ACTION_TAP_DANCE_FN_ADVANCED(dance_dquote, dance_dquote_finished, dance_dquote_reset),
	[DANCE_PAREN] = ACTION_TAP_DANCE_FN_ADVANCED(dance_paren, dance_paren_finished, dance_paren_reset),
	[DANCE_GTEQ] = ACTION_TAP_DANCE_FN_ADVANCED(dance_gteq, dance_gteq_finished, dance_gteq_reset),
	[DANCE_LTEQ] = ACTION_TAP_DANCE_FN_ADVANCED(dance_lteq, dance_lteq_finished, dance_lteq_reset),
	[DANCE_APP_WINDOWS] = ACTION_TAP_DANCE_FN_ADVANCED(dance_app_windows, dance_app_windows_finished, dance_app_windows_reset),
	[DANCE_APP_TABS] = ACTION_TAP_DANCE_FN_ADVANCED(dance_app_tabs, dance_app_tabs_finished, dance_app_tabs_reset),
};
