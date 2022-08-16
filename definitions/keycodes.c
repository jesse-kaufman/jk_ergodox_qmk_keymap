#include QMK_KEYBOARD_H
#include "version.h"
#include "definitions/layers.h"
#include "definitions/keycodes.h"
#include "features/tapdance.h"
#include "features/lighting.h"


bool my_process_hold_for_command_key(uint16_t keycode, keyrecord_t *record,uint16_t hold_keycode) {
	if (record->tap.count && record->event.pressed) {
		return true; // Return true for normal processing of tap keycode
	} else if (record->event.pressed) {
		my_indicate_success();
		tap_code16(hold_keycode); // Intercept hold function to send hold_keycode
		return false;
	}

	return true; // this allows for normal processing of key release!
}


bool process_record_user(uint16_t keycode, keyrecord_t *record) {

	switch (keycode) {
		case _UP_DIR:
			if (record->event.pressed) {
				// keycode _UP_DIR is pressed
				SEND_STRING("../");
				return false;
			}
			break;

		case _KC_C:
			return my_process_hold_for_command_key(keycode,record,LGUI(KC_C));

		case _KC_V:
			return my_process_hold_for_command_key(keycode,record,LGUI(KC_V));

		case _KC_X:
			return my_process_hold_for_command_key(keycode,record,LGUI(KC_X));

		case _KC_A:
			return my_process_hold_for_command_key(keycode,record,LGUI(KC_A));

		case _KC_S:
			return my_process_hold_for_command_key(keycode,record,LGUI(KC_S));
			case _KC_R:
				return my_process_hold_for_command_key(keycode,record,LGUI(KC_R));
	}

	return true;
};
