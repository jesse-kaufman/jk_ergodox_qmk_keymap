#ifdef COMBO_ENABLE

#include "definitions/keycodes.h"
#include "features/tapdance.h"
#include "features/lighting.h"

enum combos {
	COMBO_BACKSPACE,
	COMBO_ESC,
	COMBO_TAB,
	COMBO_CUT,
	COMBO_COPY,
	COMBO_PASTE,
	COMBO_SAVE,
	COMBO_SELECT_ALL,
	COMBO_NEXT_DESKTOP,
	COMBO_PREV_DESKTOP,
	COMBO_SQUOTE,
	COMBO_BOOTLOADER,

	COMBO_COUNT
};

uint16_t COMBO_LEN = COMBO_COUNT;

const uint16_t PROGMEM combo_backspace[] = { KC_N, KC_E, COMBO_END };
const uint16_t PROGMEM combo_esc[] = { KC_F, KC_W, COMBO_END };
const uint16_t PROGMEM combo_tab[] = { _KC_R, _KC_S, COMBO_END };
const uint16_t PROGMEM combo_cut[] = { KC_Z, KC_X, KC_C, COMBO_END };
const uint16_t PROGMEM combo_copy[] = { KC_X, KC_C, COMBO_END };
const uint16_t PROGMEM combo_paste[] = { KC_C, KC_V, COMBO_END };
const uint16_t PROGMEM combo_save[] = { KC_Q, KC_W, KC_F, KC_P, COMBO_END };
const uint16_t PROGMEM combo_select_all[] = { KC_Z, KC_X, KC_C, KC_V, COMBO_END };
const uint16_t PROGMEM combo_squote[] = { KC_E, KC_L, COMBO_END };
const uint16_t PROGMEM combo_next_desktop[] = { _KC_R, _KC_S, _KC_T, COMBO_END };
const uint16_t PROGMEM combo_prev_desktop[] = { KC_N, KC_E, KC_L, COMBO_END };
const uint16_t PROGMEM combo_bootloader[] = { KC_F13, KC_Z, COMBO_END };


combo_t key_combos[COMBO_COUNT] = {
	[COMBO_BACKSPACE] = COMBO_ACTION(combo_backspace),
	[COMBO_ESC] = COMBO_ACTION(combo_esc),
	[COMBO_TAB] = COMBO_ACTION(combo_tab),
	[COMBO_CUT] = COMBO_ACTION(combo_cut),
	[COMBO_COPY] = COMBO_ACTION(combo_copy),
	[COMBO_PASTE] = COMBO_ACTION(combo_paste),
	[COMBO_SAVE] = COMBO_ACTION(combo_save),
	[COMBO_SELECT_ALL] = COMBO_ACTION(combo_select_all),
	[COMBO_SQUOTE] = COMBO_ACTION(combo_squote),
	[COMBO_NEXT_DESKTOP] = COMBO_ACTION(combo_next_desktop),
	[COMBO_PREV_DESKTOP] = COMBO_ACTION(combo_prev_desktop),
	[COMBO_BOOTLOADER] = COMBO_ACTION(combo_bootloader),
};

void process_combo_event(uint16_t combo_index, bool pressed) {
	if ( combo_index != COMBO_BACKSPACE && combo_index != COMBO_ESC && combo_index != COMBO_TAB ) {
		clear_mods();
		clear_oneshot_mods();
	}

	if (pressed) {
		switch (combo_index) {
			case COMBO_BACKSPACE:
				register_code(KC_BSPACE);
				break;

			case COMBO_ESC:
				tap_code(KC_ESC);
				break;

			case COMBO_TAB:
				register_code(KC_TAB);
				break;

			case COMBO_SQUOTE:
				tap_code(KC_QUOTE);
				break;

			case COMBO_CUT:
				my_indicate_success();
				tap_code16(LGUI(KC_X));
				break;

			case COMBO_COPY:
				my_indicate_success();
				tap_code16(LGUI(KC_C));
				break;

			case COMBO_PASTE:
				my_indicate_success();
				tap_code16(LGUI(KC_V));
				break;

			case COMBO_SAVE:
				my_indicate_success();
				tap_code16(LGUI(KC_S));
				break;

			case COMBO_SELECT_ALL:
				my_indicate_success();
				tap_code16(LGUI(KC_A));
				break;

			case COMBO_NEXT_DESKTOP:
				my_indicate_success();
				tap_code16(LCTL(KC_LEFT));
				break;

			case COMBO_PREV_DESKTOP:
				my_indicate_success();
				tap_code16(LCTL(KC_RIGHT));
				break;

			case COMBO_BOOTLOADER:
				my_indicate_success();
				reset_keyboard();
				break;
		}
	}
}

bool process_combo_key_release(uint16_t combo_index, combo_t *combo, uint8_t key_index, uint16_t keycode) {
	switch (combo_index) {
		case COMBO_BACKSPACE:
			unregister_code(KC_BSPACE);
			break;

		case COMBO_TAB:
			unregister_code(KC_TAB);
			break;
	}
	return false;
}

bool get_combo_must_hold(uint16_t index, combo_t *combo) {
	switch (index) {
		case COMBO_CUT:
		case COMBO_COPY:
		case COMBO_PASTE:
		case COMBO_SAVE:
		case COMBO_SELECT_ALL:
		case COMBO_NEXT_DESKTOP:
		case COMBO_PREV_DESKTOP:
		case COMBO_BOOTLOADER:
			return true;
	}

	return false;
}

#endif
