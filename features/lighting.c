/**
 * LED CONTROL
 */

#include QMK_KEYBOARD_H
#include "../definitions/layers.h"
#include "lighting.h"
#include "casemodes.h"

#define LED_SUCCESS_INDICATOR_ON_TIME 100
#define LED_SUCCESS_INDICATOR_OFF_TIME 60
#define LED_BRIGHTNESS_MED 100
#define LED_BRIGHTNESS_MED_HI 130
#define LED_RED
#define LED_GREEN
#define LED_BLUE


void keyboard_post_init_user(void) {
	rgb_matrix_enable();
}


// flashes all LEDs once and leaves red LED alone if a layer is active
void my_indicate_success(void) {
	ergodox_led_all_set(LED_BRIGHTNESS_MED);
	ergodox_led_all_on();
	_delay_ms(LED_SUCCESS_INDICATOR_ON_TIME);

	if (layer_state) {
		ergodox_right_led_2_off();
		ergodox_right_led_3_off();
	}
	else {
		ergodox_led_all_off();
	}

	_delay_ms(LED_SUCCESS_INDICATOR_OFF_TIME);
}

// flashes green LED twice
void my_flash_twice(void) {
	ergodox_right_led_2_set(LED_BRIGHTNESS_MED);

	ergodox_right_led_2_on();
	_delay_ms(LED_SUCCESS_INDICATOR_ON_TIME);

	ergodox_right_led_2_off();
	_delay_ms(LED_SUCCESS_INDICATOR_OFF_TIME);

	ergodox_right_led_2_on();
	_delay_ms(LED_SUCCESS_INDICATOR_ON_TIME);

	ergodox_right_led_2_off();
	_delay_ms(LED_SUCCESS_INDICATOR_OFF_TIME);
}


void my_indicate_modifier(void) {
	RGB rgb = {
		.r = 255,
		.g = 55,
		.b = 55
	};

	// left hand
	rgb_matrix_set_color( 44, rgb.r, rgb.g, rgb.b );
	rgb_matrix_set_color( 45, rgb.r, rgb.g, rgb.b );
	rgb_matrix_set_color( 46, rgb.r, rgb.g, rgb.b );
	rgb_matrix_set_color( 47, rgb.r, rgb.g, rgb.b );

	// right hand
	rgb_matrix_set_color( 20, rgb.r, rgb.g, rgb.b );
	rgb_matrix_set_color( 21, rgb.r, rgb.g, rgb.b );
	rgb_matrix_set_color( 22, rgb.r, rgb.g, rgb.b );
	rgb_matrix_set_color( 23, rgb.r, rgb.g, rgb.b );
}


void my_indicate_one_shot_active(void) {
	ergodox_right_led_2_set(LED_BRIGHTNESS_LO);
	ergodox_right_led_2_on();
}
void my_indicate_caps_word_on(void) {
	ergodox_right_led_3_set(LED_BRIGHTNESS_LO);
	ergodox_right_led_3_on();
}
void my_indicate_caps_word_off(void) {
	if (get_xcase_state()) {
		my_indicate_xcase_on();
	}
	else {
		ergodox_right_led_3_off();
	}
}
void my_indicate_xcase_on(void) {
	ergodox_right_led_3_set(LED_BRIGHTNESS_MED_HI);
	ergodox_right_led_3_on();
	if (get_xcase_state() == XCASE_WAIT) {
		ergodox_right_led_1_set(LED_BRIGHTNESS_LO);
		ergodox_right_led_3_set(LED_BRIGHTNESS_LO);
	}
	else {
		ergodox_right_led_1_set(LED_BRIGHTNESS_MED_HI);
		ergodox_right_led_3_set(LED_BRIGHTNESS_MED_HI);
	}
	ergodox_right_led_1_on();
}
void my_indicate_xcase_off(void) {
	if (!is_caps_word_on()) {
		ergodox_right_led_3_off();
	}
	else {
		my_indicate_caps_word_on();
	}

	uint8_t layer = biton32(layer_state);

	if (layer==0) {
		ergodox_right_led_1_off();
	}
}

// void my_indicate_shift_modifier_on(void) {
// 	if (is_caps_word_on()) {
// 		my_indicate_caps_word_on();
// 	}
// 	else {
// 		ergodox_right_led_3_set(LED_BRIGHTNESS_LO);
// 		ergodox_right_led_3_on();
// 	}
// }


// void my_indicate_shift_modifier_off(void) {
// 	ergodox_right_led_3_off();
// }





void set_layer_color(int layer) {
	for (int i = 0; i < DRIVER_LED_TOTAL; i++) {
		RGB rgb = {
			.r = pgm_read_byte(&ledmap[layer][i][0]),
			.g = pgm_read_byte(&ledmap[layer][i][1]),
			.b = pgm_read_byte(&ledmap[layer][i][2]),
		};
		if (!rgb.r && !rgb.g && !rgb.b) {
			rgb_matrix_set_color( i, 0, 0, 0 );
		} else {
			rgb_matrix_set_color( i, rgb.r, rgb.g, rgb.b );
		}
	}
}



void rgb_matrix_indicators_user(void) {

	uint8_t mods = get_oneshot_mods() | get_mods();

	set_layer_color(biton32(layer_state));

	if (mods) {
		// if (mods & MOD_MASK_SHIFT)  {
		// 	my_indicate_shift_modifier_on();
		// }

		if (mods & MOD_MASK_CAG)  {
			my_indicate_modifier();
		}
	}
	else if (!is_caps_word_on()) {
		my_indicate_caps_word_off();
	}
	else if (!get_xcase_state()) {
		my_indicate_xcase_off();
	}
}


void oneshot_mods_changed_user(uint8_t mods) {
	uint8_t one_shot = get_oneshot_mods();

	if (one_shot || is_oneshot_layer_active()) {
		my_indicate_one_shot_active();
	}
	else {
		ergodox_right_led_2_off();
	}
}


void oneshot_layer_changed_user(uint8_t layer) {
	if (layer) {
		my_indicate_one_shot_active();
	}
	else {
		ergodox_right_led_2_off();
	}
}


uint8_t layer_state_set_user(uint8_t state) {

	uint8_t layer = biton32(state);

	if ( layer ) {
		if (!is_oneshot_layer_active()) {
			ergodox_right_led_1_set(LED_BRIGHTNESS_HI);
		}
		else {
			ergodox_right_led_1_set(LED_BRIGHTNESS_LO);
		}
		ergodox_right_led_1_on();
	}
	else {
		ergodox_right_led_1_off();
	}

	return state;
};
