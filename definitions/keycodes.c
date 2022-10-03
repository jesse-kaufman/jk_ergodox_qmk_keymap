#include "keycodes.h"

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
					SEND_STRING("../");
	}

	return true;
};
