#include "keycodes.h"
#include "features/tapdance.h"
#include "features/leader.h"
#include "features/lighting.h"
#include "features/casemodes.h"
#include "string.h"

void mf_handle_key_event(keyrecord_t* record, mf_key_config* key);
void mf_do_press(keyrecord_t* record, struct mf_key_event_config* event);
void mf_do_release(keyrecord_t* record, struct mf_key_event_config* event);
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
	if (!process_case_modes(keycode, record)) {
		return false;
	}

	// const uint8_t mods = get_mods() | get_oneshot_mods() | get_weak_mods();

	// output nothing if the leader key has been tapped before the MF key
	if (leading) {
		return true;
	}

	switch (keycode) {
		case _CUR_DIR:
			MF_STR_TAP("./");
			return false;

		case _UP_DIR:
			MF_STR_TAP("../");
			return false;

		case _NIX_HOME:
			MF_STR_TAP("~/");
			return false;

		case _COMMENT:
			MF_STR_TAP("// ");
			return false;

		case _PAREN:
			MF_STR_TAP_HOLD("()" SS_TAP(X_LEFT), "''" SS_TAP(X_LEFT));
			return false;

		case _CBRACKET:
			MF_STR_TAP_HOLD("{}" SS_TAP(X_LEFT), "[]" SS_TAP(X_LEFT));
			return false;

		case _BRACKET:
			MF_STR_TAP_HOLD("[]" SS_TAP(X_LEFT), "\"\"" SS_TAP(X_LEFT));
			return false;

		case _BEG_CBLOCK:
			MF_STR_TAP("/*");
			return false;

		case _END_CBLOCK:
			MF_STR_TAP("*/");
			return false;

		case _CODE_ARROWS:
			MF_STR_TAP_HOLD("->", "=>");
			return false;

		case _DESKTOP:
			my_clear_all_mods();
			MF_TAP_NO_REPEAT_HOLD(HYPR(KC_5), LCTL(KC_RIGHT));
			return false;

		case _KC_E:
			MF_TAP_NO_REPEAT_HOLD(KC_E, KC_QUOTE);
			return false;

		case _PREV_DESK:
			my_clear_all_mods();
			MF_TAP_NO_REPEAT_HOLD(LGUI(KC_SPACE), LCTL(KC_LEFT));
			return false;

		case _HTML_OPEN:
			MF_STR_TAP("<>"SS_TAP (X_LEFT));
			return false;

		case _HTML_CLOSE:
			MF_STR_TAP("</>"SS_TAP (X_LEFT));
			return false;

		case _LTEQ:
			MF_TAP_HOLD_MIXED(KC_LABK, "", MF_NOKEY, "<=" );
			return false;

		case _GTEQ:
			MF_TAP_HOLD_MIXED(KC_RABK, "", MF_NOKEY, ">=" );
			return false;

		case _APP_WINDOWS:
			MF_TAP_NO_REPEAT_HOLD(LCMD(KC_GRAVE), KC_F17);
			return false;

		case _APP_TABS:
			MF_TAP_NO_REPEAT_HOLD(LCTL(KC_TAB), LCMD(LSFT(KC_UP)));
			return false;

		case _SPACE:
			MF_TAP_HOLD_ADVANCED(KC_SPACE, true, KC_SPACE, LGUI(KC_TAB), false, KC_SPACE);
			return false;

		case _DOT:
			MF_TAP_HOLD(KC_DOT, KC_EXLM);
			return false;

		case _EQUAL:
			MF_TAP_HOLD_ONCE(KC_EQUAL, LALT(LSFT(KC_MINUS)));
			return false;

		case _DASH:
			MF_TAP_HOLD_ONCE(KC_MINUS, LALT(KC_MINUS));
			return false;

		case _COMMA:
			MF_TAP_HOLD_ONCE(KC_COMMA, KC_QUOTE);
			return false;

		case _KC_HASH:
			MF_TAP_HOLD_MIXED(KC_HASH, "", MF_NOKEY, "#!");
			return false;

		case _ZOOM_OUT:
			my_clear_all_mods();
			MF_TAP_NO_REPEAT_HOLD(LGUI(KC_MINUS),HYPR(KC_Z));
			return false;

		case _ZOOM_IN:
			my_clear_all_mods();
			MF_TAP_NO_REPEAT_HOLD(LGUI(KC_PLUS),MEH(KC_1));
			return false;

		case _VOL_UP:
			my_clear_all_mods();
			MF_TAP_NO_REPEAT_HOLD(KC_AUDIO_VOL_UP, KC_MEDIA_NEXT_TRACK);
			return false;

		case _VOL_DOWN:
			my_clear_all_mods();
			MF_TAP_NO_REPEAT_HOLD(KC_AUDIO_VOL_DOWN, KC_MEDIA_PREV_TRACK);
			return false;

		case _FN_S:
			MF_TAP_NO_REPEAT_HOLD(KC_0, LGUI(KC_S));
			return false;

		case _FN_X:
			my_clear_all_mods();
			MF_TAP_NO_REPEAT_HOLD(MEH(KC_X), LGUI(KC_Q));
			return false;

		case _MINIMIZE:
			my_clear_all_mods();
			MF_TAP_NO_REPEAT_HOLD(KC_NO, LGUI(KC_M));
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
		my_clear_all_mods();
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

		case _LBRACKET:
		case _SPACE:
			return TAPPING_TERM;

		case _KC_E:  // apostrophe when held
		case _KC_T:  // FN layer
		case _KC_S:  // NUM layer
		case _KC_K:  // CODE layer
			return TAPPING_TERM-40;

		case KC_LSFT:
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
