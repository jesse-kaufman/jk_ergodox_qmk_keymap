#include "keycodes.h"
#include "../features/tapdance.h"
#include "../features/leader.h"
#include "string.h"

void mf_handle_key_event(keyrecord_t* record, mf_key_config* key);
void mf_do_press(keyrecord_t* record, struct mf_key_event_config* event);
void mf_do_release(keyrecord_t* record, struct mf_key_event_config* event);
void mf_do_interrupt(keyrecord_t* record, struct mf_key_event_config* event);
void mf_handle_caps_word(uint16_t keycode);


void mf_clear_all_mods(void) {
	clear_mods();
	clear_weak_mods();
	clear_oneshot_mods();
	caps_word_off();
}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
	const uint8_t mods = get_mods() | get_oneshot_mods() | get_weak_mods();

	// output nothing if the leader key has been tapped before the MF key
	if (leading) {
		return true;
	}

	switch (keycode) {
		case _KC_UP_DIR:
			MF_STR_TAP_HOLD("../", "./");
			return false;

		case _LPRN:
			MF_TAP_HOLD(KC_LPRN, KC_RPRN);
			return false;

		case _KC_NIX_HOME:
			MF_STR_TAP("~/");
			mf_clear_all_mods();
			return false;

		case _KC_COMMENT:
			MF_STR_TAP("// ");
			mf_clear_all_mods();
			return false;

		case _KC_ML_COMMENT:
			if ( mods & MOD_MASK_GUI) {
				MF_STR_TAP("/**" SS_TAP(X_ENTER) " *"SS_TAP (X_ENTER)"*/"SS_TAP (X_UP));
				mf_clear_all_mods();
			}
			else {
				MF_STR_TAP_HOLD("/*", "*/");
			}
			return false;

		case _QUOTE:
			MF_TAP_HOLD_MIXED(KC_QUOTE, "", MF_NOKEY, "''"SS_TAP (X_LEFT));
			return false;

		case _LCURLBR:
			MF_TAP_HOLD(KC_LCBR, KC_RCBR);
			return false;

		case _LBRACKET:
			MF_TAP_HOLD(KC_LBRACKET, KC_RBRACKET);
			return false;

		case _DESKTOP:
			MF_TAP_HOLD(HYPR(KC_5), LCTL(KC_RIGHT));
			mf_clear_all_mods();
			return false;

		case _KC_E:
			MF_TAP_HOLD(KC_E, KC_QUOTE);
			return false;

		case _PREV_DESK:
			MF_TAP_HOLD(LGUI(KC_SPACE), LCTL(KC_LEFT));
			mf_clear_all_mods();
			return false;

		case _DQUOTE:
			MF_TAP_HOLD_MIXED(KC_DQUO, "", MF_NOKEY, "\"\""SS_TAP (X_LEFT));
			return false;

		case _LTEQ:
			MF_TAP_HOLD_MIXED(KC_LABK, "", MF_NOKEY, "<=" );
			return false;

		case _GTEQ:
			MF_TAP_HOLD_MIXED(KC_RABK, "", MF_NOKEY, ">=" );
			return false;

		case _APP_WINDOWS:
			MF_TAP_HOLD(LCMD(KC_GRAVE), KC_F17);
			return false;

		case _APP_TABS:
			MF_TAP_HOLD(LCTL(KC_TAB), LCMD(LSFT(KC_UP)));
			return false;

		case _SPACE:
			MF_TAP_HOLD_ADVANCED(KC_SPACE, true, KC_SPACE, LGUI(KC_TAB), false, KC_SPACE);
			return false;

		case _DOT:
			MF_TAP_HOLD(KC_DOT, KC_EXLM);
			return false;

		case _COMMA:
			MF_TAP_HOLD(KC_COMMA, KC_QUOTE);
			return false;

		case _KC_SCOLN:
			MF_TAP_HOLD(KC_SCOLON, KC_COLON);
			return false;
	}

	return true;
}



/***						***/
/***	HELPER FUNCTIONS	***/
/***						***/

// function to handle multi-function keys
void mf_handle_key_event(keyrecord_t* record, mf_key_config* key) {

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
			mf_do_release(record,&key->tap);
		}
		else if (record->event.pressed) {
			// key down, press tap keycode
			mf_do_press(record,&key->tap);
		}
	}
	else {
		// key is being held or being released from a hold
		// key is being held or being released from a single hold

		if (record->tap.interrupted) {
			if (record->event.pressed) {
				// hold interrupted
				mf_do_interrupt(record,&key->hold);
			}
		}
		else if (!record->event.pressed) {
			// single hold up
			mf_do_release(record,&key->hold);
		}
		else if (record->event.pressed) {
			// single hold down

			// if hold string is not set and tap string or keycode is set, send that
			if ( (key->hold.string && 0 == strcmp(key->hold.string, ""))
			     && (0 != strcmp(key->tap.string, "") || key->tap.keycode)) {

				// key is a string key and hold string is not defined; send tap string
				mf_do_press(record,&key->tap);
			}
			else {
				mf_do_press(record,&key->hold);
			}
		}
	}
}


void mf_do_press(keyrecord_t* record, struct mf_key_event_config* event) {
	if (event->fn) {
		event->fn(record);
	}
	else if (event->keycode) {
		// handle caps word
		mf_handle_caps_word(event->keycode);

		if (event->do_register) {
			// register the keycode
			register_code16(event->keycode);
		}
		else {
			// tap the keycode
			tap_code16(event->keycode);
		}
	}
	else if (event->string && 0 != strcmp(event->string, "")) {
		mf_clear_all_mods();
		send_string(event->string);
	}
}


void mf_handle_caps_word(uint16_t keycode) {
	if (is_caps_word_on() && !caps_word_press_user(keycode)) {
		caps_word_off();
	}
}


void mf_do_release(keyrecord_t* record, struct mf_key_event_config* event) {
	if (event->do_register && event->keycode) {
		// unregister the keycode
		unregister_code16(event->keycode);
	}
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
		mf_clear_all_mods();
		send_string(event->string);
	}
}




/***						***/
/***	PER-KEY SETTINGS	***/
/***						***/

// set tapping term per key
uint16_t get_tapping_term(uint16_t keycode, keyrecord_t *record) {
	switch (keycode) {
		case _OSM_OPT:
		case _OSM_RSHIFT:
		case _OSM_LCMD:
		case _OSM_RCMD:
		case _OSM_CTR:
		case _OSL_SYM:
			return TAPPING_TERM-100;

		case _QUOTE:
		case _LBRACKET:
		case _KC_R:  // SHIFT
		case _KC_A:  // ALT
		case _SPACE:
			return TAPPING_TERM;

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


// customize which key codes disengage caps word
bool caps_word_press_user(uint16_t keycode) {
	switch (keycode) {
		// Keycodes that continue Caps Word, with shift applied.
		case KC_A ... KC_Z:
		case KC_MINS:
			add_weak_mods(MOD_BIT(KC_RSFT));  // Apply shift to next key.
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
