#include "leader.h"

LEADER_EXTERNS();

void my_leader_matrix_scan_user(void) {
	LEADER_DICTIONARY() {
		did_leader_succeed = leading = false;

		leader_start();

		// Terminal
		SEQ_ONE_KEY(_KC_T) {
			tap_code16(HYPR(KC_T));
			did_leader_succeed = true;
		} else
			// Safari
			SEQ_ONE_KEY(_KC_S) {
				tap_code16(HYPR(KC_S));
				did_leader_succeed = true;
			}else
			// Notes
			SEQ_TWO_KEYS(_KC_N, _KC_O) {
				tap_code16(HYPR(KC_N));
				did_leader_succeed = true;
			}else
			// Mail
			SEQ_TWO_KEYS(_KC_M, _KC_A) {
				tap_code16(HYPR(KC_M));
				did_leader_succeed = true;
			}else
			// Finder
			SEQ_ONE_KEY(_F_FN) {
				tap_code16(HYPR(KC_D));
				did_leader_succeed = true;
			}else
			// Messenger (FB)
			SEQ_TWO_KEYS(_F_FN, _KC_B) {
				tap_code16(HYPR(KC_F));
				did_leader_succeed = true;
			}else
			// Messages
			SEQ_TWO_KEYS(_KC_S, _KC_M) {
				tap_code16(HYPR(KC_B));
				did_leader_succeed = true;
			}else
			// Terminal
			SEQ_TWO_KEYS(_KC_T, KC_E) {
				tap_code16(HYPR(KC_E));
				did_leader_succeed = true;
			}else
			// Chrome
			SEQ_TWO_KEYS(_KC_C, _KC_H) {
				tap_code16(HYPR(KC_G));
				did_leader_succeed = true;
			}else
			// Lightroom
			SEQ_TWO_KEYS(KC_L, _KC_R) {
				tap_code16(HYPR(KC_L));
				did_leader_succeed = true;
			}else
			// Reminders
			SEQ_TWO_KEYS(_KC_R, KC_E) {
				tap_code16(HYPR(KC_R));
				did_leader_succeed = true;
			}else
			// Reminders
			SEQ_ONE_KEY(_PLAY) {
				tap_code16(HYPR(KC_R));
				did_leader_succeed = true;
			}

		leader_end();
	}
}

void leader_start(void) {
	ergodox_led_all_set(LED_BRIGHTNESS_LO);
	ergodox_led_all_on();
}

void leader_end(void) {
	if (did_leader_succeed) {
		// If any sequence was matched, did_leader_succeed will have
		// been set to true up in the matrix_scan_user function.
		// Put your code for a matched leader key sequence here.
		my_indicate_success();
	} else {
		// If no sequence was matched, did_leader_succeed will not
		// have been set to true anywhere, so we'll end up here.
		// Put your code for an unmatched leader key sequence here.
	}

	ergodox_led_all_off();
}
