

#include "leader.h"

#ifdef COMBO_ENABLE
enum combo_events {
	COMBO_BACKSPACE,

	COMBO_LENGTH
};

uint16_t COMBO_LEN = COMBO_LENGTH; // remove the COMBO_COUNT define and use this instead!

const uint16_t PROGMEM combo_backspace[] = {KC_N, KC_E, COMBO_END};


combo_t key_combos[] = {
	[COMBO_BACKSPACE] = COMBO(combo_backspace, KC_BSPACE),

};

void process_combo_event(uint16_t combo_index, bool pressed) {
}
bool process_combo_key_release(uint16_t combo_index, combo_t *combo, uint8_t key_index, uint16_t keycode) {
	switch(combo_index) {
		case COMBO_BACKSPACE:
			return true;
			break;
	}

	return false;
}

#endif
