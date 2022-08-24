/*
 * TAPDANCE FUNCTIONALITY
 */


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
	} else if (state->count == 2) {

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







/***						***/
/***	PER-KEY SETTINGS	***/
/***						***/

// set permissive hold per key
bool get_permissive_hold(uint16_t keycode, keyrecord_t *record) {
	switch (keycode) {
		case _SHFT_SPACE:
		case _KC_F:
		case _KC_A:
		case _KC_D:
		case _KC_S:
			// Do not select the hold action when another key is tapped.
			return false;

		default:
			// Immediately select the hold action when another key is tapped.
			return true;
	}
}

// set hold on other key press per key
bool get_hold_on_other_key_press(uint16_t keycode, keyrecord_t *record) {
	switch (keycode) {
		case _SHFT_SPACE:
		case _KC_A:
		case _KC_D:
		case _KC_S:
		case _KC_F:
		case _KC_T:
			// Do not select the hold action when another key is pressed.
			return false;

		default:
			// Immediately select the hold action when another key is pressed.
			return true;
	}
}

// set tapping term per key
uint16_t get_tapping_term(uint16_t keycode, keyrecord_t *record) {
	switch (keycode) {
		case _SHFT_SPACE:
		case _SEMICOLON:
		case _QUOTE:
		case _LBRACKET:
		case _OSM_OPT:
		case _OSM_CMD:
		case _OSM_CTR:
			return TAPPING_TERM;

		case _KC_F:
		case _KC_T:
		case _KC_A:
		case _KC_S:
		case _KC_D:
		case _TAB_MGMT:
			return TAPPING_TERM+50;

		default:
			return TAPPING_TERM-100;
	}
}

// customize which key codes disengage caps word
bool caps_word_press_user(uint16_t keycode) {
	switch (keycode) {
		// Keycodes that continue Caps Word, with shift applied.
		case KC_A ... KC_Z:
		case _KC_A:
		case _KC_D:
		case _KC_S:
		case _KC_F:
		case _KC_T:
		case KC_MINS:
			add_weak_mods(MOD_BIT(KC_LSFT));  // Apply shift to next key.
			return true;

		// Keycodes that continue Caps Word, without shifting.
		case KC_1 ... KC_0:
		case KC_BSPC:
		case KC_DEL:
		case KC_UNDS:
			return true;

		default:
			return false;  // Deactivate Caps Word.
	}
}


/***											***/
/***	CALLBACKS FOR TAPDANCE ACTIONS ARRAY	***/
/***											***/


/*
 * DESKTOP / NEXT DESKTOP
 */

void dance_desktop_finished(qk_tap_dance_state_t *state, void *user_data) {
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
	}
}
void dance_desktop_reset(qk_tap_dance_state_t *state, void *user_data) {
	dance_state[DANCE_DESKTOP].step = 0;
}


/*
 * SPOTLIGHT / PREVIOUS DESKTOP
 */

void dance_spotlight_finished(qk_tap_dance_state_t *state, void *user_data) {
	dance_state[DANCE_SPOTLIGHT].step = dance_step(state);
	switch (dance_state[DANCE_SPOTLIGHT].step) {
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
	}
}
void dance_spotlight_reset(qk_tap_dance_state_t *state, void *user_data) {
	dance_state[DANCE_SPOTLIGHT].step = 0;
}


/*
 * TAB MANAGEMENT
 */

void on_dance_tab_mgmt(qk_tap_dance_state_t *state, void *user_data) {
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
 * PAGE UP / HOME
 */

void on_dance_pgup_home(qk_tap_dance_state_t *state, void *user_data) {
	if(state->count == 3) {
		tap_code16(KC_PGUP);
		tap_code16(KC_PGUP);
		tap_code16(KC_PGUP);
	}
	if(state->count > 3) {
		tap_code16(KC_PGUP);
	}
}
void dance_pgup_home_finished(qk_tap_dance_state_t *state, void *user_data) {
	dance_state[DANCE_PGUP_HOME].step = dance_step(state);
	switch (dance_state[DANCE_PGUP_HOME].step) {
		case SINGLE_TAP:
		case DOUBLE_HOLD:
			register_code16(KC_PGUP);
			break;

		case SINGLE_HOLD:
			tap_code16(KC_HOME);
			break;

		case DOUBLE_TAP:
		case DOUBLE_SINGLE_TAP:
			tap_code16(KC_PGUP);
			register_code16(KC_PGUP);
			break;
	}
}
void dance_pgup_home_reset(qk_tap_dance_state_t *state, void *user_data) {
	//wait_ms(5);
	switch (dance_state[DANCE_PGUP_HOME].step) {
		case SINGLE_TAP:
		case DOUBLE_TAP:
		case DOUBLE_SINGLE_TAP:
		case DOUBLE_HOLD:
			unregister_code16(KC_PGUP);
			break;
	}
	dance_state[DANCE_PGUP_HOME].step = 0;
}


/*
 * PAGE DOWN / END
 */

void on_dance_pgdn_end(qk_tap_dance_state_t *state, void *user_data) {
	if(state->count == 3) {
		tap_code16(KC_PGDOWN);
		tap_code16(KC_PGDOWN);
		tap_code16(KC_PGDOWN);
	}
	if(state->count > 3) {
		tap_code16(KC_PGDOWN);
	}
}
void dance_pgdn_end_finished(qk_tap_dance_state_t *state, void *user_data) {
	dance_state[DANCE_PGDN_END].step = dance_step(state);
	switch (dance_state[DANCE_PGDN_END].step) {
		case SINGLE_TAP:
			register_code16(KC_PGDOWN);
			break;

		case SINGLE_HOLD:
			tap_code16(KC_END);
			break;

		case DOUBLE_TAP:
		case DOUBLE_SINGLE_TAP:
			tap_code16(KC_PGDOWN);
			register_code16(KC_PGDOWN);
			break;
	}
}
void dance_pgdn_end_reset(qk_tap_dance_state_t *state, void *user_data) {
	switch (dance_state[DANCE_PGDN_END].step) {
		case SINGLE_TAP:
			unregister_code16(KC_PGDOWN);
			break;

		case DOUBLE_TAP:
		case DOUBLE_SINGLE_TAP:
			unregister_code16(KC_PGDOWN);
			break;
	}
	dance_state[DANCE_PGDN_END].step = 0;
}


/*
 * ZOOM OUT
 */

void on_dance_zoom_out(qk_tap_dance_state_t *state, void *user_data) {
	if(state->count == 3) {
		tap_code16(_ZOOM_OUT);
		tap_code16(_ZOOM_OUT);
		tap_code16(_ZOOM_OUT);
	}
	if(state->count > 3) {
		tap_code16(_ZOOM_OUT);
	}
}
void dance_zoom_out_finished(qk_tap_dance_state_t *state, void *user_data) {
	dance_state[DANCE_ZOOM_OUT].step = dance_step(state);
	switch (dance_state[DANCE_ZOOM_OUT].step) {
		case SINGLE_TAP:
			register_code16(_ZOOM_OUT);
			break;

		case SINGLE_HOLD:
			tap_code16(HYPR(KC_0));
			break;

		case DOUBLE_TAP:
		case DOUBLE_SINGLE_TAP:
			tap_code16(_ZOOM_OUT);
			register_code16(_ZOOM_OUT);
			break;
	}
}
void dance_zoom_out_reset(qk_tap_dance_state_t *state, void *user_data) {
	switch (dance_state[DANCE_ZOOM_OUT].step) {
		case SINGLE_TAP:
		case DOUBLE_TAP:
		case DOUBLE_SINGLE_TAP:
			unregister_code16(_ZOOM_OUT);
			break;
	}
	dance_state[DANCE_ZOOM_OUT].step = 0;
}


/*
 * TAB / LAST APP
 */

void on_dance_tab_last_app(qk_tap_dance_state_t *state, void *user_data) {
	if(state->count == 3) {
		tap_code16(KC_TAB);
		tap_code16(KC_TAB);
		tap_code16(KC_TAB);
	}
	if(state->count > 3) {
		tap_code16(KC_TAB);
	}
}
void dance_tab_last_app_finished(qk_tap_dance_state_t *state, void *user_data) {
	dance_state[DANCE_TAB_LAST_APP].step = dance_step(state);
	switch (dance_state[DANCE_TAB_LAST_APP].step) {
		case SINGLE_TAP:
		case DOUBLE_TAP:
			tap_code16(KC_TAB);
			break;

		case SINGLE_HOLD:
			tap_code16(LGUI(KC_TAB));
			break;

		case DOUBLE_HOLD:
			tap_code16(LCTL(KC_DOWN));
			break;
	}
}
void dance_tab_last_app_reset(qk_tap_dance_state_t *state, void *user_data) {
	dance_state[DANCE_TAB_LAST_APP].step = 0;
}


/*
 * SLASH / COLON
 */

void on_dance_slash_colon(qk_tap_dance_state_t *state, void *user_data) {
	if(state->count == 3) {
		tap_code16(KC_SCOLON);
		tap_code16(KC_SCOLON);
		tap_code16(KC_SCOLON);
	}
	if(state->count > 3) {
		tap_code16(KC_SCOLON);
	}
}
void dance_slash_colon_finished(qk_tap_dance_state_t *state, void *user_data) {
	dance_state[DANCE_SLASH_COLON].step = dance_step(state);
	switch (dance_state[DANCE_SLASH_COLON].step) {
		case SINGLE_TAP:
			tap_code16(KC_SLASH);
			break;

		case SINGLE_HOLD:
			tap_code16(KC_COLN);
			break;

		case DOUBLE_TAP:
			tap_code16(KC_SLASH);
			tap_code16(KC_SLASH);
			break;
	}
}
void dance_slash_colon_reset(qk_tap_dance_state_t *state, void *user_data) {
	dance_state[DANCE_SLASH_COLON].step = 0;
}


/*
 * SEMICOLON / COLON
 */

void on_dance_semicolon(qk_tap_dance_state_t *state, void *user_data) {
	if(state->count == 3) {
		tap_code16(KC_SCOLON);
		tap_code16(KC_SCOLON);
		tap_code16(KC_SCOLON);
	}
	if(state->count > 3) {
		tap_code16(KC_SCOLON);
	}
}
void dance_semicolon_finished(qk_tap_dance_state_t *state, void *user_data) {
	dance_state[DANCE_SEMICOLON].step = dance_step(state);
	switch (dance_state[DANCE_SEMICOLON].step) {
		case SINGLE_TAP:
			register_code16(KC_SCOLON);
			break;

		case SINGLE_HOLD:
			tap_code16(KC_COLN);
			break;

		case DOUBLE_TAP:
			register_code16(KC_SCOLON);
			register_code16(KC_SCOLON);
			break;

		case DOUBLE_SINGLE_TAP:
			tap_code16(KC_SCOLON);
			register_code16(KC_SCOLON);
	}
}
void dance_semicolon_reset(qk_tap_dance_state_t *state, void *user_data) {
	switch (dance_state[DANCE_SEMICOLON].step) {
		case SINGLE_TAP:
			unregister_code16(KC_SCOLON);
			break;

		case SINGLE_HOLD:
			break;

		case DOUBLE_TAP:
			unregister_code16(KC_SCOLON);
			break;

		case DOUBLE_SINGLE_TAP:
			unregister_code16(KC_SCOLON);
			break;
	}
	dance_state[DANCE_SEMICOLON].step = 0;
}


/*
 * QUOTE / DOUBLE QUOTE
 */

void on_dance_quote(qk_tap_dance_state_t *state, void *user_data) {
	if(state->count == 3) {
		tap_code16(KC_QUOTE);
		tap_code16(KC_QUOTE);
		tap_code16(KC_QUOTE);
	}
	if(state->count > 3) {
		tap_code16(KC_QUOTE);
	}
}
void dance_quote_finished(qk_tap_dance_state_t *state, void *user_data) {
	dance_state[DANCE_QUOTE].step = dance_step(state);
	switch (dance_state[DANCE_QUOTE].step) {
		case SINGLE_TAP:
			if (!leading) {
				register_code16(KC_QUOTE);
			}
			break;

		case SINGLE_HOLD:
			register_code16(KC_DQUO);
			break;

		case DOUBLE_TAP:
			tap_code16(KC_QUOTE);
			tap_code16(KC_QUOTE);
			clear_mods();
			tap_code16(KC_LEFT);
			break;

		case DOUBLE_HOLD:
			tap_code16(KC_DQUO);
			tap_code16(KC_DQUO);
			clear_mods();
			tap_code16(KC_LEFT);
			break;
	}
}
void dance_quote_reset(qk_tap_dance_state_t *state, void *user_data) {
	switch (dance_state[DANCE_QUOTE].step) {
		case SINGLE_TAP:
			unregister_code16(KC_QUOTE);
			break;

		case SINGLE_HOLD:
			unregister_code16(KC_DQUO);
			break;
	}
	dance_state[DANCE_QUOTE].step = 0;
}


/*
 * DOT / EXCLAMATION POINT
 */

void on_dance_dot(qk_tap_dance_state_t *state, void *user_data) {
	if(state->count == 3) {
		tap_code16(KC_DOT);
		tap_code16(KC_DOT);
		tap_code16(KC_DOT);
	}
	if(state->count > 3) {
		tap_code16(KC_DOT);
	}
}
void dance_dot_finished(qk_tap_dance_state_t *state, void *user_data) {
	dance_state[DANCE_DOT].step = dance_step(state);
	switch (dance_state[DANCE_DOT].step) {
		case SINGLE_TAP:
			register_code16(KC_DOT);
			break;

		case SINGLE_HOLD:
			register_code16(KC_EXLM);
			break;

		case DOUBLE_HOLD:
			register_code16(KC_DOT);
			break;

		case DOUBLE_TAP:
			tap_code16(KC_DOT);
			register_code16(KC_DOT);
			break;

		case DOUBLE_SINGLE_TAP:
			tap_code16(KC_DOT);
			register_code16(KC_DOT);
	}
}
void dance_dot_reset(qk_tap_dance_state_t *state, void *user_data) {
	switch (dance_state[DANCE_DOT].step) {
		case SINGLE_TAP:
			unregister_code16(KC_DOT);
			break;

		case SINGLE_HOLD:
			unregister_code16(KC_EXLM);
			break;

		case DOUBLE_TAP:
			unregister_code16(KC_DOT);
			break;

		case DOUBLE_HOLD:
			unregister_code16(KC_DOT);
			break;

		case DOUBLE_SINGLE_TAP:
			unregister_code16(KC_DOT);
			break;
	}
	dance_state[DANCE_DOT].step = 0;
}


/*
 * VOLUME DOWN / MUTE
 */

void on_dance_12(qk_tap_dance_state_t *state, void *user_data) {
	if(state->count == 3) {
		tap_code16(KC_AUDIO_VOL_DOWN);
		tap_code16(KC_AUDIO_VOL_DOWN);
		tap_code16(KC_AUDIO_VOL_DOWN);
	}
	if(state->count > 3) {
		tap_code16(KC_AUDIO_VOL_DOWN);
	}
}
void dance_12_finished(qk_tap_dance_state_t *state, void *user_data) {
	dance_state[DANCE_12].step = dance_step(state);
	switch (dance_state[DANCE_12].step) {
		case SINGLE_TAP:
			register_code16(KC_AUDIO_VOL_DOWN);
			break;

		case SINGLE_HOLD:
			register_code16(KC_AUDIO_MUTE);
			break;

		case DOUBLE_TAP:
			register_code16(KC_AUDIO_VOL_DOWN);
			register_code16(KC_AUDIO_VOL_DOWN);
			break;

		case DOUBLE_SINGLE_TAP:
			tap_code16(KC_AUDIO_VOL_DOWN);
			register_code16(KC_AUDIO_VOL_DOWN);
	}
}
void dance_12_reset(qk_tap_dance_state_t *state, void *user_data) {
	switch (dance_state[DANCE_12].step) {
		case SINGLE_TAP:
			unregister_code16(KC_AUDIO_VOL_DOWN);
			break;

		case SINGLE_HOLD:
			unregister_code16(KC_AUDIO_MUTE);
			break;

		case DOUBLE_TAP:
			unregister_code16(KC_AUDIO_VOL_DOWN);
			break;

		case DOUBLE_SINGLE_TAP:
			unregister_code16(KC_AUDIO_VOL_DOWN);
			break;
	}
	dance_state[DANCE_12].step = 0;
}


/*
 * PLAY / PAUSE
 */

void on_dance_13(qk_tap_dance_state_t *state, void *user_data) {
	if(state->count == 3) {
		tap_code16(KC_MEDIA_PLAY_PAUSE);
		tap_code16(KC_MEDIA_PLAY_PAUSE);
		tap_code16(KC_MEDIA_PLAY_PAUSE);
	}
	if(state->count > 3) {
		tap_code16(KC_MEDIA_PLAY_PAUSE);
	}
}
void dance_13_finished(qk_tap_dance_state_t *state, void *user_data) {
	dance_state[DANCE_13].step = dance_step(state);
	switch (dance_state[DANCE_13].step) {
		case SINGLE_TAP:
			register_code16(KC_MEDIA_PLAY_PAUSE);
			break;

		case SINGLE_HOLD:
			register_code16(KC_PAUSE);
			break;

		case DOUBLE_TAP:
			register_code16(KC_MEDIA_PLAY_PAUSE);
			register_code16(KC_MEDIA_PLAY_PAUSE);
			break;

		case DOUBLE_SINGLE_TAP:
			tap_code16(KC_MEDIA_PLAY_PAUSE);
			register_code16(KC_MEDIA_PLAY_PAUSE);
	}
}
void dance_13_reset(qk_tap_dance_state_t *state, void *user_data) {
	switch (dance_state[DANCE_13].step) {
		case SINGLE_TAP:
			unregister_code16(KC_MEDIA_PLAY_PAUSE);
			break;

		case SINGLE_HOLD:
			unregister_code16(KC_PAUSE);
			break;

		case DOUBLE_TAP:
			unregister_code16(KC_MEDIA_PLAY_PAUSE);
			break;

		case DOUBLE_SINGLE_TAP:
			unregister_code16(KC_MEDIA_PLAY_PAUSE);
			break;
	}
	dance_state[DANCE_13].step = 0;
}


/*
 * HYPHEN / EN DASH / EM DASH
 */

void on_dance_14(qk_tap_dance_state_t *state, void *user_data) {
	if(state->count == 3) {
		tap_code16(KC_MINUS);
		tap_code16(KC_MINUS);
		tap_code16(KC_MINUS);
	}
	if(state->count > 3) {
		tap_code16(KC_MINUS);
	}
}
void dance_14_finished(qk_tap_dance_state_t *state, void *user_data) {
	dance_state[DANCE_14].step = dance_step(state);
	switch (dance_state[DANCE_14].step) {
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
void dance_14_reset(qk_tap_dance_state_t *state, void *user_data) {
	switch (dance_state[DANCE_14].step) {
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
	dance_state[DANCE_14].step = 0;
}


/*
 * LEFT CURLY BRACKET / {}
 */

void on_dance_15(qk_tap_dance_state_t *state, void *user_data) {
	if(state->count == 3) {
		tap_code16(KC_LCBR);
		tap_code16(KC_LCBR);
		tap_code16(KC_LCBR);
	}
	if(state->count > 3) {
		tap_code16(KC_LCBR);
	}
}
void dance_15_finished(qk_tap_dance_state_t *state, void *user_data) {
	dance_state[DANCE_15].step = dance_step(state);
	switch (dance_state[DANCE_15].step) {
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
void dance_15_reset(qk_tap_dance_state_t *state, void *user_data) {
	switch (dance_state[DANCE_15].step) {
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
	dance_state[DANCE_15].step = 0;
}


/*
 * LEFT BRACKET / []
 */

void on_dance_16(qk_tap_dance_state_t *state, void *user_data) {
	if(state->count == 3) {
		tap_code16(KC_LBRACKET);
		tap_code16(KC_LBRACKET);
		tap_code16(KC_LBRACKET);
	}
	if(state->count > 3) {
		tap_code16(KC_LBRACKET);
	}
}
void dance_16_finished(qk_tap_dance_state_t *state, void *user_data) {
	dance_state[DANCE_16].step = dance_step(state);
	switch (dance_state[DANCE_16].step) {
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
void dance_16_reset(qk_tap_dance_state_t *state, void *user_data) {
	//wait_ms(10);
	switch (dance_state[DANCE_16].step) {
		case SINGLE_TAP:
			unregister_code16(KC_LBRACKET);
			break;

		case DOUBLE_TAP:
			break;

		case DOUBLE_SINGLE_TAP:
			unregister_code16(KC_LBRACKET);
			break;
	}
	dance_state[DANCE_16].step = 0;
}


/*
 * DOUBLE QUOTE / ""
 */

void on_dance_dquote(qk_tap_dance_state_t *state, void *user_data) {
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

void on_dance_18(qk_tap_dance_state_t *state, void *user_data) {
	if(state->count == 3) {
		tap_code16(KC_LPRN);
		tap_code16(KC_LPRN);
		tap_code16(KC_LPRN);
	}
	if(state->count > 3) {
		tap_code16(KC_LPRN);
	}
}
void dance_18_finished(qk_tap_dance_state_t *state, void *user_data) {
	dance_state[DANCE_18].step = dance_step(state);
	switch (dance_state[DANCE_18].step) {
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
void dance_18_reset(qk_tap_dance_state_t *state, void *user_data) {
	switch (dance_state[DANCE_18].step) {
		case SINGLE_TAP:
			unregister_code16(KC_LPRN);
			break;

		case DOUBLE_TAP:
			break;

		case DOUBLE_SINGLE_TAP:
			unregister_code16(KC_LPRN);
			break;
	}
	dance_state[DANCE_18].step = 0;
}


/*
 * GREATER THAN / >=
 */

void on_dance_gteq(qk_tap_dance_state_t *state, void *user_data) {
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

void on_dance_lteq(qk_tap_dance_state_t *state, void *user_data) {
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
			tap_code16(KC_EQUAL);
			;
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
 * CUR DIR ./ AND UP DIR ../
 */

void on_dance_up_dir(qk_tap_dance_state_t *state, void *user_data) {
	dance_state[DANCE_UP_DIR].step = dance_step(state);
	switch (dance_state[DANCE_UP_DIR].step) {
		case SINGLE_TAP:
			// keycode _UP_DIR is pressed
			SEND_STRING("../");
			break;

		case DOUBLE_TAP:
			SEND_STRING("./");
			break;

		case DOUBLE_SINGLE_TAP:
			tap_code16(KC_LABK);
			register_code16(KC_LABK);
			break;
	}
}


qk_tap_dance_action_t tap_dance_actions[] = {
	[DANCE_SPOTLIGHT] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, dance_spotlight_finished, dance_spotlight_reset),
	[DANCE_DESKTOP] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, dance_desktop_finished, dance_desktop_reset),
	[DANCE_TAB_MGMT] = ACTION_TAP_DANCE_FN(on_dance_tab_mgmt),
	[DANCE_PGUP_HOME] = ACTION_TAP_DANCE_FN_ADVANCED(on_dance_pgup_home, dance_pgup_home_finished, dance_pgup_home_reset),
	[DANCE_PGDN_END] = ACTION_TAP_DANCE_FN_ADVANCED(on_dance_pgdn_end, dance_pgdn_end_finished, dance_pgdn_end_reset),
	[DANCE_ZOOM_OUT] = ACTION_TAP_DANCE_FN_ADVANCED(on_dance_zoom_out, dance_zoom_out_finished, dance_zoom_out_reset),
	[DANCE_TAB_LAST_APP] = ACTION_TAP_DANCE_FN_ADVANCED(on_dance_tab_last_app, dance_tab_last_app_finished, dance_tab_last_app_reset),
	[DANCE_SEMICOLON] = ACTION_TAP_DANCE_FN_ADVANCED(on_dance_semicolon, dance_semicolon_finished, dance_semicolon_reset),
	[DANCE_SLASH_COLON] = ACTION_TAP_DANCE_FN_ADVANCED(on_dance_slash_colon, dance_slash_colon_finished, dance_slash_colon_reset),
	[DANCE_QUOTE] = ACTION_TAP_DANCE_FN_ADVANCED(on_dance_quote, dance_quote_finished, dance_quote_reset),
	[DANCE_DOT] = ACTION_TAP_DANCE_FN_ADVANCED(on_dance_dot, dance_dot_finished, dance_dot_reset),
	[DANCE_12] = ACTION_TAP_DANCE_FN_ADVANCED(on_dance_12, dance_12_finished, dance_12_reset),
	[DANCE_13] = ACTION_TAP_DANCE_FN_ADVANCED(on_dance_13, dance_13_finished, dance_13_reset),
	[DANCE_14] = ACTION_TAP_DANCE_FN_ADVANCED(on_dance_14, dance_14_finished, dance_14_reset),
	[DANCE_15] = ACTION_TAP_DANCE_FN_ADVANCED(on_dance_15, dance_15_finished, dance_15_reset),
	[DANCE_16] = ACTION_TAP_DANCE_FN_ADVANCED(on_dance_16, dance_16_finished, dance_16_reset),
	[DANCE_DQUOTE] = ACTION_TAP_DANCE_FN_ADVANCED(on_dance_dquote, dance_dquote_finished, dance_dquote_reset),
	[DANCE_18] = ACTION_TAP_DANCE_FN_ADVANCED(on_dance_18, dance_18_finished, dance_18_reset),
	[DANCE_GTEQ] = ACTION_TAP_DANCE_FN_ADVANCED(on_dance_gteq, dance_gteq_finished, dance_gteq_reset),
	[DANCE_LTEQ] = ACTION_TAP_DANCE_FN_ADVANCED(on_dance_lteq, dance_lteq_finished, dance_lteq_reset),
	[DANCE_UP_DIR] = ACTION_TAP_DANCE_FN(on_dance_up_dir),
};
