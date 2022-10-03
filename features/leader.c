#include "../definitions/keycodes.h"
#include "lighting.h"
#include "leader.h"

LEADER_EXTERNS();

void my_leader_matrix_scan_user(void) {
	LEADER_DICTIONARY() {
		did_leader_succeed = leading = false;

		leader_start();

		SEQ_ONE_KEY(KC_LEAD) {
			tap_code16(LGUI(KC_SPACE));
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
		// send hotkey sequence


		if (leader_sequence[0] >= KC_A && leader_sequence[0] <= KC_Z) {
			register_code16(KC_HYPR);

			tap_code16( leader_sequence[0] );

			if ( leader_sequence[1]) {
				tap_code16( leader_sequence[1] );

				if (leader_sequence[2]) {
					tap_code16( leader_sequence[2] );

					if (leader_sequence[3]) {
						tap_code16( leader_sequence[3] );

						if (leader_sequence[4]) {
							tap_code16( leader_sequence[4] );

						}
					}
				}
			}

			unregister_code16(KC_HYPR);
		}
	}


	ergodox_led_all_off();
}
