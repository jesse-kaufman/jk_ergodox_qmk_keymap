#include "../definitions/keycodes.h"
#include "lighting.h"
#include "leader.h"

LEADER_EXTERNS();

void my_leader_matrix_scan_user(void) {
	LEADER_DICTIONARY() {
		did_leader_succeed = leading = false;
		leader_start();

        // SPOTLIGHT
        my_key_seq(KC_LEAD, 0, 0, 0, 0, LCMD(KC_SPACE));

        // EDGE
        my_key_seq(KC_E, 0, 0, 0, 0, HYPR(KC_I));

        // TERMINAL
        my_key_seq(KC_T, 0, 0, 0, 0, HYPR(KC_T));

        // SAFARI
        my_key_seq(KC_S, 0, 0, 0, 0, HYPR(KC_S));

        // SAFARI TECH EDITION
        my_key_seq(KC_S, KC_T, 0, 0, 0, HYPR(KC_E));

        // MS OUTLOOK
        my_key_seq(KC_M, KC_S, KC_O, 0, 0, HYPR(KC_O));

        // MS TEAMS
        my_key_seq(KC_M, KC_S, KC_T, 0, 0, HYPR(KC_A));

        // REMINDERS
        my_key_seq(KC_R, KC_E, 0, 0, 0, HYPR(KC_R));

        // PHOTOS
        my_key_seq(KC_P, KC_H, KC_O, 0, 0, HYPR(KC_P));

        // NOTES
        my_key_seq(KC_N, KC_O, 0, 0, 0, HYPR(KC_N));

        // MUSIC
        my_key_seq(KC_MEDIA_PLAY_PAUSE, 0, 0, 0, 0, HYPR(KC_U));

        // MESSAGES
        my_key_seq(KC_M, KC_E, KC_S, 0, 0, HYPR(KC_B));

        // MAIL
        my_key_seq(KC_M, 0, 0, 0, 0, HYPR(KC_M));

        // LIGHTROOM
        my_key_seq(KC_L, KC_R, 0, 0, 0, HYPR(KC_L));

        // FINDER
        my_key_seq(KC_F, 0, 0, 0, 0, HYPR(KC_D));

        // CHROME
        my_key_seq(KC_C, KC_H, KC_R, 0, 0, HYPR(KC_G));

        // CALENDAR
        my_key_seq(KC_C, KC_A, KC_L, 0, 0, HYPR(KC_C));

        // FB MESSENGER
        my_key_seq(KC_F, KC_B, 0, 0, 0, HYPR(KC_F));

        // VISUAL STUDIO CODE
        my_key_seq(KC_V, 0, 0, 0, 0, HYPR(KC_K));

        // OPEN WORK APPS
        my_key_seq(KC_W, KC_O, 0, 0, 0, HYPR(KC_W));

        // CLOSE WORK APPS
        my_key_seq(KC_W, KC_C, 0, 0, 0, HYPR(KC_X));

        // SYSTEM SETTINGS
        my_key_seq(KC_S, KC_Y, KC_S, 0, 0, HYPR(KC_Q));

		leader_end();
	}
}

void my_key_seq(uint16_t kc1, uint16_t kc2, uint16_t kc3, uint16_t kc4, uint16_t kc5, uint16_t tap_kc)
{
    if (kc5)
    {
        SEQ_FIVE_KEYS(kc1, kc2, kc3, kc4, kc5)
        {
            tap_code16(tap_kc);
            did_leader_succeed = true;
        }
    }
    else if (kc4)
    {
        SEQ_FOUR_KEYS(kc1, kc2, kc3, kc4)
        {
            tap_code16(tap_kc);
            did_leader_succeed = true;
        }
    }
    else if (kc3)
    {
        SEQ_THREE_KEYS(kc1, kc2, kc3)
        {
            tap_code16(tap_kc);
            did_leader_succeed = true;
        }
    }
    else if (kc2)
    {
        SEQ_TWO_KEYS(kc1, kc2)
        {
            tap_code16(tap_kc);
            did_leader_succeed = true;
        }
    }
    else if (kc1)
    {
        SEQ_ONE_KEY(kc1)
        {
            tap_code16(tap_kc);
            did_leader_succeed = true;
        }
    };
}

void leader_start(void)
{
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
						tap_code16(LCMD(KC_SPACE));
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
