#include "keycodes.h"
#include "../features/tapdance.h"

void mf_handle_key_event(keyrecord_t* record, mf_key_config* key);
void mf_do_press(keyrecord_t* record, struct mf_key_event_config* event);
void mf_do_release(keyrecord_t* record, struct mf_key_event_config* event);
void mf_do_interrupt(keyrecord_t* record, struct mf_key_event_config* event);
void mf_handle_caps_word(uint16_t keycode);
bool process_record_user(uint16_t keycode, keyrecord_t *record) {


	switch (keycode) {
		case _KC_COMMENT:
			caps_word_off();
			if (record->event.pressed) {
				SEND_STRING("// ");
			}
			return false;


		case _KC_NIX_HOME:
			caps_word_off();
			if (record->event.pressed) {
				SEND_STRING("~/");
			}
			return false;


		case _KC_UP_DIR:
			caps_word_off();
			if (record->tap.count > 0) {
				// Key is being tapped.
				if (record->event.pressed) {
					// Handle tap press event...
					SEND_STRING("../");
				}
			}
			else {
				// Key is being held.
				if (record->event.pressed) {
					// Handle hold press event...
					SEND_STRING("./");
				}
			}
			return false;


		case _SPACE:
			caps_word_off();
			if (record->event.pressed ) {
				if (record->tap.count > 0 ) {
					// Key is being tapped.
					register_code(KC_SPACE);
				}
				else {
					// Key is being held.
					if (!record->tap.interrupted) {
						// Handle hold press event...
						tap_code16(LGUI(KC_TAB));
					}
					else {
						register_code(KC_SPACE);
					}
				}
			}
			else {
				// key was released
				if (record->tap.count > 0 ) {
					unregister_code(KC_SPACE);
				}
			}
			return false;

		// case _OSM_RSHIFT:
		// 	MF_TAP_HOLD_FN(&hi, &ho);
		// 	return false;

		case _DOT:
			caps_word_off();
			if (record->tap.count > 0) {
				// Key is being tapped.
				if (record->event.pressed) {
					// Handle tap press event...
					register_code(KC_DOT);
				}
				else {
					// Handle tap release event...
					unregister_code(KC_DOT);
				}
			}
			else {
				// Key is being held.
				if (record->event.pressed) {
					// Handle hold press event...
					tap_code16(KC_EXLM);
				}
			}
			return false;


		case _COMMA:
			MF_TAP_HOLD(KC_COMMA, KC_QUOTE);
			return false;
	}

	return true;
}



/***						***/
/***	HELPER FUNCTIONS	***/
/***						***/

// function to handle multi-function keys
void mf_handle_key_event(keyrecord_t* record, mf_key_config* key) {
	/*
	   if ((key->double_hold.keycode || key->double_tap.keycode) && record->tap.count == 2 ) {
	    // key has a double-tap action and was double-tapped/double-held

	    if (record->tap.interrupted) {
	        // This check is to distinguish between typing "pepper", and actually wanting a double tap
	        // action when hitting 'pp'. Suggested use case for this is when you want to send two
	        // keystrokes of the key, and not the 'double tap' action/macro.

	        if (!record->event.pressed) {
	            // Double-tap has been interrupted
	            if (&key->double_tap.keycode) {
	                mf_do_interrupt(&key->double_tap);
	                return;
	            }
	        }
	        else {
	            // Double-hold has been interrupted
	            if (&key->double_hold.keycode) {
	                mf_do_interrupt(&key->double_hold);
	                return;
	            }
	        }
	    }
	    else if (record->event.pressed) {
	        // tapped, then pressed and held

	        if (&key->double_hold.keycode) {
	            // double hold keycode is set, so send it and exit the handler
	            tap_code16(key->double_hold.keycode);
	            return;
	        }
	    }
	    else {
	        // clean double-tap with no interrupt, do the double-tap action instead of typing 'pp' in 'pepper'
	        // @see double single tap for pepper analogy

	        if (&key->double_tap.keycode) {
	            // double tap keycode is set, so send it and exit the handler
	            tap_code16(key->double_tap.keycode);
	            return;
	        }
	    }
	   }
	 */


	if ((key->double_hold.keycode || key->double_tap.keycode || key->double_hold.fn || key->double_tap.fn) && record->tap.count == 2) {
		// key was tapped twice

		if (record->tap.interrupted) {
			// This check is to distinguish between typing "pepper", and actually wanting a double tap
			// action when hitting 'pp'. Suggested use case for this is when you want to send two
			// keystrokes of the key, and not the 'double tap' action/macro.

			if (!record->event.pressed) {
				// Double-tap has been interrupted
				mf_do_interrupt(record,&key->double_tap);
				return;
			}
			else {
				// Double-hold has been interrupted
				mf_do_interrupt(record,&key->double_hold);
				return;
			}
		}
		else if (record->event.pressed) {
			// tapped, then pressed and held
			mf_do_press(record,&key->double_hold);
			return;

		}
		else {
			// clean double-tap with no interrupt, do the double-tap action instead of typing 'pp' in 'pepper'
			// @see double single tap for pepper analogy
			mf_do_press(record,&key->double_tap);
			return;
		}
	}

	if (record->tap.count > 0) {
		// key was tapped one or more times

		if (record->tap.interrupted) {
			if (!record->event.pressed) {
				// interrupt tap and send tap key
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
			mf_do_press(record,&key->hold);
		}
	}
}


void mf_do_press(keyrecord_t* record, struct mf_key_event_config* event) {
	if (event->fn) {
		event->fn(record);
	}
	else {
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
}


void mf_handle_caps_word(uint16_t keycode) {
	if (!caps_word_press_user(keycode)) {
		caps_word_off();
	}
}


void mf_do_release(keyrecord_t* record, struct mf_key_event_config* event) {
	if (event->do_register) {
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

		case _SEMICOLON:
		case _QUOTE:
		case _LBRACKET:
		case _KC_R:
		case _KC_A:
		case _SPACE:
			return TAPPING_TERM;

		case _KC_T:
		case _KC_S:
		case _KC_K:
			return TAPPING_TERM-40;

		case _TAB_MGMT:
			return TAPPING_TERM+50;

		default:
			return TAPPING_TERM-50;
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
