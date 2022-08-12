#include "leader.h"

LEADER_EXTERNS();

void matrix_scan_user(void) {
	LEADER_DICTIONARY() {
		did_leader_succeed = leading = false;

		leader_start();

		// Terminal
		SEQ_ONE_KEY(KC_T) {
			tap_code16(HYPR(KC_T));
			did_leader_succeed = true;
		} else
		// Safari
		SEQ_ONE_KEY(KC_S) {
			tap_code16(HYPR(KC_S));
			did_leader_succeed = true;
		} else
		// Notes
		SEQ_TWO_KEYS(KC_N, KC_O) {
			tap_code16(HYPR(KC_N));
			did_leader_succeed = true;
		} else
		// Mail
		SEQ_TWO_KEYS(KC_M, KC_A) {
			tap_code16(HYPR(KC_M));
			did_leader_succeed = true;
		} else
		// Finder
		SEQ_ONE_KEY(KC_F) {
			tap_code16(HYPR(KC_D));
			did_leader_succeed = true;
		} else
		// Messenger (FB)
		SEQ_TWO_KEYS(KC_F, KC_B) {
			tap_code16(HYPR(KC_F));
			did_leader_succeed = true;
		} else
		// Messages
		SEQ_TWO_KEYS(KC_S, KC_M) {
			tap_code16(HYPR(KC_B));
			did_leader_succeed = true;
		} else
		// Terminal
		SEQ_TWO_KEYS(KC_T, KC_E) {
			tap_code16(HYPR(KC_E));
			did_leader_succeed = true;
		} else
		// Chrome
		SEQ_TWO_KEYS(KC_C, KC_H) {
			tap_code16(HYPR(KC_G));
			did_leader_succeed = true;
		} else
		// Lightroom
		SEQ_TWO_KEYS(KC_L, KC_R) {
			tap_code16(HYPR(KC_L));
			did_leader_succeed = true;
		} else
		// Reminders
		SEQ_TWO_KEYS(KC_R, KC_E) {
			tap_code16(HYPR(KC_R));
			did_leader_succeed = true;
		} else
		// Reminders
		SEQ_ONE_KEY(KC_MEDIA_PLAY_PAUSE) {
			tap_code16(HYPR(KC_R));
			did_leader_succeed = true;
		}

		leader_end();
	}
}

void leader_start(void) {
  ergodox_led_all_set(LED_BRIGHTNESS_HI);
  ergodox_led_all_on();
}

void leader_end(void) {
  if (did_leader_succeed) {
    // If any sequence was matched, did_leader_succeed will have
    // been set to true up in the matrix_scan_user function.
    // Put your code for a matched leader key sequence here.
	ergodox_led_all_off();
	_delay_ms(LEADER_BLINK_OFF_TIMEOUT);
	ergodox_led_all_on();
	_delay_ms(LEADER_BLINK_ON_TIMEOUT);
	ergodox_led_all_off();
	_delay_ms(LEADER_BLINK_OFF_TIMEOUT);
	ergodox_led_all_on();
	_delay_ms(LEADER_BLINK_ON_TIMEOUT);
  } else {
    // If no sequence was matched, did_leader_succeed will not
    // have been set to true anywhere, so we'll end up here.
    // Put your code for an unmatched leader key sequence here.
  }

  ergodox_led_all_off();
}
