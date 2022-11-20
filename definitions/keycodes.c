#include "keycodes.h"
#include "features/tapdance.h"
#include "features/leader.h"
#include "features/lighting.h"
#include "features/casemodes.h"
#include "string.h"

uint8_t mf_prev_layer = 0;
bool mf_key_down = false;


void mf_handle_key_event(uint16_t keycode, keyrecord_t* record, mf_key_config* key, void (*fn_down)(uint16_t, keyrecord_t*), void (*fn_up)(uint16_t, keyrecord_t*));
void mf_do_action(keyrecord_t* record, struct mf_key_event_config* event);
void mf_do_release(uint16_t keycode, keyrecord_t* record, struct mf_key_event_config* event);
void mf_do_interrupt(keyrecord_t* record, struct mf_key_event_config* event);
void mf_handle_caps_word(uint16_t keycode);
void mf_handle_xcase(uint16_t keycode, keyrecord_t *record);
void mf_indicate_success(uint16_t* keycode);

void my_clear_all_mods(void) {
	clear_mods();
	clear_weak_mods();
	clear_oneshot_mods();
	caps_word_off();
	disable_xcase();
}


bool process_record_user(uint16_t keycode, keyrecord_t *record) {

	if (!mf_process_key(keycode, record)) {
		return false;
	}

	return true;
}


/***                          ***/
/*** PER-KEY HELPER FUNCTIONS ***/
/***                          ***/



/*
 * SYM KEY
 */
void mf_on_sym_key_down(uint16_t keycode, keyrecord_t* record) {
	mf_key_down = true;

	if (record->tap.count > 0) {
		// tap

		switch (biton32(layer_state)) {
			case _SYM:
				reset_oneshot_layer();
				layer_move(_CODE);
				set_oneshot_layer(_SYM, ONESHOT_START);
				break;

			case _CODE:
				reset_oneshot_layer();
				layer_off(_CODE);
				MF_RESET_LAYER();
				break;

			default:
				if (record->tap.count == 1) {
					mf_prev_layer = biton32(layer_state);
					layer_move(_SYM);
					set_oneshot_layer(_SYM, ONESHOT_START);
				}
				else if (record->tap.count == 2) {
					reset_oneshot_layer();
					layer_move(_CODE);
					set_oneshot_layer(_CODE, ONESHOT_START);
				}
				break;
		}
	}
	else {
		// hold

		reset_oneshot_layer();

		switch (biton32(layer_state)) {
			case _SYM:
				layer_on(_CODE);
				break;

			case _CODE:
				layer_off(_CODE);
				MF_RESET_LAYER();
				break;

			default:
				mf_prev_layer = biton32(layer_state);
				layer_on(_SYM);
				break;
		}
	}
}
void mf_on_sym_key_up(uint16_t keycode, keyrecord_t* record) {

	// assume !record->event.pressed

	// delay slightly
	_delay_ms(10);

	switch (biton32(layer_state)) {
		case _SYM:
			if (record->tap.count == 0) {
				if (mf_prev_layer) {
					layer_move(mf_prev_layer);
				}
				else {
					layer_move(_BASE);
				}
			}
			break;

		case _CODE:
			if (record->tap.count == 2) {
				SEND_STRING(".");
			}
			if (record->tap.count == 0 || record->tap.count == 2) {
				if (mf_prev_layer) {
					layer_move(mf_prev_layer);
				}
				else {
					layer_move(_BASE);
				}
			}
			break;
	}
}



/***                          ***/
/***     MAIN MF FUNCTIONS    ***/
/***                          ***/

/*
 * MAIN MF PROCESSING FUNCTION
 */
bool mf_process_key(uint16_t keycode, keyrecord_t *record) {
	// skip all processing below if the leader key has been tapped
	if (leading) {
		return true;
	}

	switch (keycode) {
		case _ACTION_KEY1:
			MF_TAP_HOLD_ONCE(HYPR(KC_F20), MEH(KC_F20));
			break;

		case _ACTION_KEY2:
			MF_TAP_HOLD_ONCE(HYPR(KC_F19), MEH(KC_F19));
			break;

		case _CUR_DIR:
			MF_STR_TAP("./");
			break;

		case _UP_DIR:
			MF_STR_TAP("../");
			break;

		case _NIX_HOME:
			MF_STR_TAP("~/");
			break;

		case _COMMENT:
			MF_STR_TAP("// ");
			break;

		case _PAREN:
			MF_STR_TAP_HOLD("()" SS_TAP(X_LEFT), "''" SS_TAP(X_LEFT));
			break;

		case _CBRACKET:
			MF_STR_TAP_HOLD("{}" SS_TAP(X_LEFT), "[]" SS_TAP(X_LEFT));
			break;

		case _BRACKET:
			MF_STR_TAP_HOLD("[]" SS_TAP(X_LEFT), "\"\"" SS_TAP(X_LEFT));
			break;

		case _BEG_CBLOCK:
			MF_STR_TAP("/*");
			break;

		case _END_CBLOCK:
			MF_STR_TAP("*/");
			break;

		case _CODE_ARROWS:
			MF_STR_TAP_HOLD("->", "=>");
			break;

		case _DESKTOP:
			my_clear_all_mods();
			MF_TAP_NO_REPEAT_HOLD(HYPR(KC_5), LCTL(KC_RIGHT));
			break;

		case _KC_E:
			MF_TAP_NO_REPEAT_HOLD(KC_E, KC_QUOTE);
			break;

		case _PREV_DESK:
			my_clear_all_mods();
			MF_TAP_NO_REPEAT_HOLD(LGUI(KC_SPACE), LCTL(KC_LEFT));
			break;

		case _HTML_OPEN:
			MF_STR_TAP("<>"SS_TAP (X_LEFT));
			break;

		case _HTML_CLOSE:
			MF_STR_TAP("</>"SS_TAP (X_LEFT));
			break;

		case _LTEQ:
			MF_TAP_HOLD_MIXED(KC_LABK, "", MF_NOKEY, "<=" );
			break;

		case _GTEQ:
			MF_TAP_HOLD_MIXED(KC_RABK, "", MF_NOKEY, ">=" );
			break;

		case _APP_WINDOWS:
			MF_TAP_NO_REPEAT_HOLD(LCMD(KC_GRAVE), LCMD(LSFT(KC_GRAVE)));
			break;

		case _APP_TABS:
			MF_TAP_NO_REPEAT_HOLD(LCTL(KC_TAB), LGUI(LALT(KC_F19)));
			break;

		case _SPACE:
			MF_TAP_HOLD_ADVANCED(KC_SPACE, true, KC_SPACE, LGUI(KC_TAB), false, KC_SPACE);
			break;

		case _DOT:
			MF_TAP_NO_REPEAT_HOLD(KC_DOT, KC_EXLM);
			break;

		case _EQUAL:
			MF_TAP_HOLD_ONCE(KC_EQUAL, LALT(LSFT(KC_MINUS)));
			break;

		case _DASH:
			MF_TAP_HOLD_ONCE(KC_MINUS, LALT(KC_MINUS));
			break;

		case _KC_HASH:
			MF_TAP_HOLD_MIXED(KC_HASH, "", MF_NOKEY, "#!");
			break;

		case _ZOOM_OUT:
			my_clear_all_mods();
			MF_TAP_NO_REPEAT_HOLD(LGUI(KC_MINUS),HYPR(KC_Z));
			break;

		case _ZOOM_IN:
			my_clear_all_mods();
			MF_TAP_NO_REPEAT_HOLD(LGUI(KC_PLUS),MEH(KC_1));
			break;

		case _VOL_UP:
			my_clear_all_mods();
			MF_TAP_NO_REPEAT_HOLD(KC_AUDIO_VOL_UP, KC_MEDIA_NEXT_TRACK);
			break;

		case _VOL_DOWN:
			my_clear_all_mods();
			MF_TAP_NO_REPEAT_HOLD(KC_AUDIO_VOL_DOWN, KC_MEDIA_PREV_TRACK);
			break;

		case _FN_S:
			MF_TAP_NO_REPEAT_HOLD(KC_0, LGUI(KC_S));
			break;

		case _FN_X:
			my_clear_all_mods();
			MF_TAP_NO_REPEAT_HOLD(MEH(KC_X), LGUI(KC_Q));
			break;

		case _MINIMIZE:
			my_clear_all_mods();
			MF_TAP_NO_REPEAT_HOLD(KC_NO, LGUI(KC_M));
			break;

		case _SYM_KEY:
			MF_FN_ADVANCED(MF_NOFN, MF_NOFN, MF_NOFN, MF_NOFN, mf_on_sym_key_down, mf_on_sym_key_up);
			break;
	}

	// run this here for all non-MF keycodes (also runs in mf_handle_key_event())
	mf_check_disable_oneshot(record, keycode);

	return true;
}



/***						***/
/***	HELPER FUNCTIONS	***/
/***						***/

// function to handle multi-function keys
void (mf_handle_key_event)(uint16_t keycode, keyrecord_t* record, mf_key_config* key, void (*fn_down)(uint16_t, keyrecord_t*), void (*fn_up)(uint16_t, keyrecord_t*)) {

	if (fn_down && record->event.pressed) {
		// interrupt tap when key is pressed and still down
		(*fn_down)(keycode, record);
	}

	if (record->tap.count > 0) {
		// key was tapped one or more times

		if (record->tap.interrupted) {
			if (record->event.pressed) {
				// interrupt tap when key is pressed and still down
				mf_do_interrupt(record,&key->tap);
			}
		}
		else if (!record->event.pressed) {
			// key up, release tap keycode
			mf_do_release(keycode, record, &key->tap);
		}
		else if (record->event.pressed) {
			// key down, press tap keycode
			mf_do_action(record,&key->tap);
		}
	}
	else {
		// key is being held or being released from a single hold

		if (record->tap.interrupted) {
			if (record->event.pressed) {
				// hold interrupted
				mf_do_interrupt(record,&key->hold);
			}
		}
		else if (!record->event.pressed) {
			// single hold up
			mf_do_release(keycode, record, &key->hold);
		}
		else if (record->event.pressed) {
			// single hold down

			// if hold string is not set and tap string or keycode is set, send that
			if ( (key->hold.string && 0 == strcmp(key->hold.string, ""))
			     && (0 != strcmp(key->tap.string, "") || key->tap.keycode)) {

				// key is a string key and hold string is not defined; send tap string
				mf_do_action(record,&key->tap);
			}
			else {
				mf_do_action(record,&key->hold);
			}
		}
	}

	if (fn_up && !record->event.pressed) {
		// interrupt tap when key is pressed and still down
		(*fn_up)(keycode, record);
	}
}


void mf_do_action(keyrecord_t* record, struct mf_key_event_config* event) {
	if (event->fn_action) {
		(*event->fn_action)(event->keycode, record);
	}
	else if (event->keycode) {
		// handle caps word
		mf_handle_caps_word(event->keycode);
		mf_handle_xcase(event->keycode, record);

		if (event->do_register) {
			mf_indicate_success(&event->keycode);

			// register the keycode
			register_code16(event->keycode);
		}
		else {
			mf_indicate_success(&event->keycode);

			// tap the keycode
			tap_code16(event->keycode);
		}
	}
	else if (event->string && 0 != strcmp(event->string, "")) {
		my_clear_all_mods();
		send_string(event->string);
	}
}


void mf_handle_caps_word(uint16_t keycode) {
	if (is_caps_word_on() && !caps_word_press_user(keycode)) {
		caps_word_off();
	}
}

void mf_handle_xcase(uint16_t keycode, keyrecord_t* record) {
	process_case_modes(keycode, record);
}


void mf_do_release(uint16_t keycode, keyrecord_t* record, struct mf_key_event_config* event) {
	if (event->fn_release) {
		(*event->fn_release)(event->keycode, record);
	}
	else if (event->do_register && event->keycode) {
		// unregister the keycode
		unregister_code16(event->keycode);
	}

	if (event->fn_action) {
		mf_key_down = false;
	}

	mf_check_disable_oneshot(record, keycode);
}


void mf_do_interrupt(keyrecord_t* record, struct mf_key_event_config* event) {

	if (event->keycode) {
		// handle caps word
		mf_handle_caps_word(event->keycode);

		// send interrupt key tap if set, otherwise send the tap key
		if (event->interrupt_keycode) {
			tap_code16(event->interrupt_keycode);
		}
		else {
			tap_code16(event->keycode);
		}
	}
	else if (event->string && 0 != strcmp(event->string, "")) {
		my_clear_all_mods();
		send_string(event->string);
	}
}


void mf_check_disable_oneshot(keyrecord_t* record, uint16_t keycode) {

	if (!record->event.pressed && is_oneshot_layer_active()) {
		switch (keycode) {
			case KC_LSFT:
			case KC_LCMD:
			case KC_LCTL:
			case KC_LOPT:
			case KC_RSFT:
			case KC_RCMD:
			case KC_RCTL:
			case KC_ROPT:
				break;

			case _SYM_KEY:
				break;

			default:
				clear_oneshot_layer_state(ONESHOT_PRESSED);
				MF_RESET_LAYER();
				break;
		}
	}
}







/***						***/
/***	PER-KEY SETTINGS	***/
/***						***/

// set tapping term per key
uint16_t get_tapping_term(uint16_t keycode, keyrecord_t *record) {
	switch (keycode) {
		case _SYM_KEY:
			return 100;

		case _SPACE:
			return TAPPING_TERM;

		case _FN_KEY:
		case _KC_E:  // apostrophe when held
		case _KC_T:  // FN layer
		case _KC_S:  // NUM layer
		case _KC_K:  // CODE layer
			return TAPPING_TERM-40;

		case _TAB_MGMT:
			return TAPPING_TERM+50;

		default:
			return TAPPING_TERM-50;
	}
}

// set force_hold per key
bool get_tapping_force_hold(uint16_t keycode, keyrecord_t *record) {
	switch (keycode) {
		case _KC_E:  // apostrophe when held
			return true;

		default:
			return false;
	}
}

bool caps_word_press_user(uint16_t keycode) {
	switch (keycode) {
		// Keycodes that continue Caps Word, with shift applied.
		case KC_A ... KC_Z:
			add_weak_mods(MOD_BIT(KC_LSFT)); // Apply shift to the next key.
			return true;

		// Keycodes that continue Caps Word, without shifting.
		case KC_1 ... KC_0:
		case KC_BSPC:
		case KC_DEL:
		case KC_UNDS:
		case KC_DASH:
		case _SYM_KEY:
		case _FN_KEY:
			return true;

		default:
			return false; // Deactivate Caps Word.
	}
}


void mf_indicate_success(uint16_t* keycode) {
	switch (*keycode) {
		case KC_MEDIA_NEXT_TRACK:
		case KC_MEDIA_PREV_TRACK:
		case LGUI(KC_Q):
		case LGUI(KC_W):
			my_indicate_success();
			break;

		case LGUI(KC_S):
			my_flash_twice();
			break;

	}
}
