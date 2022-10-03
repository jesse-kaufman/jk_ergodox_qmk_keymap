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

/***						***/
/***	PER-KEY SETTINGS	***/
/***						***/

// set tapping term per key
uint16_t get_tapping_term(uint16_t keycode, keyrecord_t *record) {
	switch (keycode) {
		case _OSM_OPT:
		case _OSM_RSHIFT:
		case _OSM_LCMD:
		case _OSM_RCMD:
		case _OSM_CTR:
		case _OSL_SYM:
			return TAPPING_TERM-100;

		case _SEMICOLON:
		case _QUOTE:
		case _LBRACKET:
		case _KC_R:
		case _KC_A:
		case _SPACE:
			return TAPPING_TERM;

		case _KC_T:
		case _KC_S:
		case _KC_K:
			return TAPPING_TERM-40;

		case _TAB_MGMT:
			return TAPPING_TERM+50;

		default:
			return TAPPING_TERM-50;
	}
}

// customize which key codes disengage caps word
bool caps_word_press_user(uint16_t keycode) {
	switch (keycode) {
		// Keycodes that continue Caps Word, with shift applied.
		case KC_A ... KC_Z:
		case KC_MINS:
			add_weak_mods(MOD_BIT(KC_RSFT));  // Apply shift to next key.
			return true;

		// Keycodes that continue Caps Word, without shifting.
		case KC_1 ... KC_0:
		case KC_BSPC:
		case KC_DEL:
		case KC_UNDS:
			return true;

		default:
			return false;  // Deactivate Caps Word.
	}
}
