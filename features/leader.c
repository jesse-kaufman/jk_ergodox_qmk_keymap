#include "../definitions/keycodes.h"
#include "lighting.h"
#include "leader.h"

LEADER_EXTERNS();

void my_leader_matrix_scan_user(void) {
	LEADER_DICTIONARY() {
		did_leader_succeed = leading = false;
		leader_start();

		// SPOTLIGHT
		MY_KEY_SEQ(KC_LEAD, 0, 0, 0, 0, LGUI(KC_SPACE));

		// CLICKUP
		MY_KEY_SEQ(KC_C, KC_U, 0, 0, 0, HYPR(KC_I));

		// TERMINAL
		MY_KEY_SEQ(KC_T, 0, 0, 0, 0, HYPR(KC_T));

		// SAFARI
		MY_KEY_SEQ(KC_S, 0, 0, 0, 0, HYPR(KC_S));

		// SAFARI TECH EDITION
		MY_KEY_SEQ(KC_S, KC_T, 0, 0, 0, HYPR(KC_E));

		// MS OUTLOOK
		MY_KEY_SEQ(KC_M, KC_S, KC_O, 0, 0, HYPR(KC_O));

		// MS TEAMS
		MY_KEY_SEQ(KC_M, KC_S, KC_T, 0, 0, HYPR(KC_A));

		// REMINDERS
		MY_KEY_SEQ(KC_R, KC_E, 0, 0, 0, HYPR(KC_R));

		// PHOTOS
		MY_KEY_SEQ(KC_P, KC_H, KC_O, 0, 0, HYPR(KC_P));

		// NOTES
		MY_KEY_SEQ(KC_N, KC_O, 0, 0, 0, HYPR(KC_N));

		// MUSIC
		MY_KEY_SEQ(KC_MEDIA_PLAY_PAUSE, 0, 0, 0, 0, HYPR(KC_U));

		// MESSAGES
		MY_KEY_SEQ(KC_M, KC_E, KC_S, 0, 0, HYPR(KC_B));

		// MAIL
		MY_KEY_SEQ(KC_M, 0, 0, 0, 0, HYPR(KC_M));

		// LIGHTROOM
		MY_KEY_SEQ(KC_L, KC_R, 0, 0, 0, HYPR(KC_L));

		// FINDER
		MY_KEY_SEQ(KC_F, 0, 0, 0, 0, HYPR(KC_D));

		// CHROME
		MY_KEY_SEQ(KC_C, KC_H, KC_R, 0, 0, HYPR(KC_G));

		// CALENDAR
		MY_KEY_SEQ(KC_C, KC_A, KC_L, 0, 0, HYPR(KC_C));

		// FB MESSENGER
		MY_KEY_SEQ(KC_F, KC_B, 0, 0, 0, HYPR(KC_F));

		// ATOM
		MY_KEY_SEQ(KC_A, KC_T, 0, 0, 0, HYPR(KC_H));

		leader_end();
	}
}

void leader_start(void) {
	my_clear_all_mods();
	ergodox_led_all_set(LED_BRIGHTNESS_LO);
	ergodox_led_all_on();
}

bool is_leader_active(void) {
	return leading;
}

bool is_leader_key_valid(uint16_t keycode) {
	if (keycode >= KC_A && keycode <= KC_Z) {
		return true;
	}
	else {
		return false;
	}
}


void leader_end(void) {
	uint8_t seq = 0;
	bool spotlight_active = false;

	if (did_leader_succeed) {
		// If any sequence was matched, did_leader_succeed will have
		// been set to true up in the matrix_scan_user function.
		// Put your code for a matched leader key sequence here.
		my_indicate_success();
	} else {
		// If no sequence was matched, did_leader_succeed will not
		// have been set to true anywhere, so we'll end up here.
		// Put your code for an unmatched leader key sequence here.
		// send hotkey sequence

		while (seq < 5) {
			if (leader_sequence[seq]) {
				if (is_leader_key_valid(leader_sequence[seq])) {
					if (!spotlight_active) {
						tap_code16(LGUI(KC_SPACE));
						wait_ms(70);
						spotlight_active = true;
					}
					tap_code16( leader_sequence[seq] );
				}
			}
			seq++;
		}
	}

	ergodox_led_all_off();
}
