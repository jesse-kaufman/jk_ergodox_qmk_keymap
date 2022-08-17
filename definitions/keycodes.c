#include QMK_KEYBOARD_H
#include "version.h"
#include "definitions/layers.h"
#include "definitions/keycodes.h"
#include "features/tapdance.h"
#include "features/lighting.h"


bool my_process_hold_for_command_key(uint16_t keycode, keyrecord_t *record,uint16_t hold_keycode) {
	if (record->tap.count && record->event.pressed) {
		tap_code16(keycode); // send regular key tap
		return false;
	} else if (record->event.pressed) {
		my_indicate_success();
		tap_code16(hold_keycode); // Intercept hold function to send hold_keycode
		return false;

	}

	return true;
}


bool process_record_user(uint16_t keycode, keyrecord_t *record) {

	switch (keycode) {
		case _KC_UP_DIR:
			if (record->event.pressed) {
				// keycode _UP_DIR is pressed
				SEND_STRING("../");
				return false;
			}
			break;

		case _KC_COMMENT:
			if (record->event.pressed) {
				// keycode _UP_DIR is pressed
				SEND_STRING("// ");
				return false;
			}
			break;

		case _KC_NIX_HOME:
			if (record->event.pressed) {
				// keycode _UP_DIR is pressed
				SEND_STRING("~/");
				return false;
			}
			break;
	}

	return true;
};
