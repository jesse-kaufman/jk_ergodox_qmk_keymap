#include QMK_KEYBOARD_H
#include "version.h"
#include "definitions/layers.h"
#include "definitions/keycodes.h"



bool process_record_user(uint16_t keycode, keyrecord_t *record) {
	switch (keycode) {
		case _UP_DIR:
			if (record->event.pressed) {
				// keycode _UP_DIR is pressed
				SEND_STRING("../");
			} else {
				// keycode _UP_DIR is released
			}
			break;
	}
	return true;
};
