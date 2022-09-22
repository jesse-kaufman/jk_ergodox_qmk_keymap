#include "keycodes.h"

bool process_record_user(uint16_t keycode, keyrecord_t *record) {

	switch (keycode) {
		case _KC_COMMENT:
			if (record->event.pressed) {
				// keycode _KC_COMMENT is pressed
				SEND_STRING("// ");
			}
			return false;
			break;

		case _KC_NIX_HOME:
			if (record->event.pressed) {
				// keycode _KC_NIX_HOME is pressed
				SEND_STRING("~/");
			}
			return false;
			break;
	}

	return true;
};
