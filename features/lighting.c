/**
 * LED CONTROL
 */

#include QMK_KEYBOARD_H
#include "../definitions/layers.h"
#include "lighting.h"
#include "casemodes.h"
#include "leader.h"

#define LED_SUCCESS_INDICATOR_ON_TIME 80
#define LED_SUCCESS_INDICATOR_OFF_TIME 40
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

	if (get_highest_layer(layer_state) == _BASE) {
		ergodox_led_all_off();
	}
	else {
		ergodox_right_led_2_off();
		ergodox_right_led_3_off();
	}
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
}


void my_indicate_leader(void) {
	RGB rgb = {
		.r = 155,
		.g = 5,
		.b = 5
	};

	//
	// left hand
	//

	// bottom row (0)
	// rgb_matrix_set_color( 44, rgb.r, rgb.g, rgb.b );
	rgb_matrix_set_color( 45, rgb.r, rgb.g, rgb.b );
	rgb_matrix_set_color( 46, rgb.r, rgb.g, rgb.b );
	rgb_matrix_set_color( 47, rgb.r, rgb.g, rgb.b );


	// first alpha row [second from the bottom] (1)
	// rgb_matrix_set_color( 43, rgb.r, rgb.g, rgb.b );
	// rgb_matrix_set_color( 42, rgb.r, rgb.g, rgb.b );
	// rgb_matrix_set_color( 41, rgb.r, rgb.g, rgb.b );
	// rgb_matrix_set_color( 40, rgb.r, rgb.g, rgb.b );
	// rgb_matrix_set_color( 39, rgb.r, rgb.g, rgb.b );

	// second alpha row [third row from bottom] (2)
	rgb_matrix_set_color( 34, rgb.r, rgb.g, rgb.b );
	rgb_matrix_set_color( 35, rgb.r, rgb.g, rgb.b );
	rgb_matrix_set_color( 36, rgb.r, rgb.g, rgb.b );
	rgb_matrix_set_color( 37, rgb.r, rgb.g, rgb.b );
	rgb_matrix_set_color( 38, rgb.r, rgb.g, rgb.b );

	// third alpha row [fourth row from bottom] (3)
	// rgb_matrix_set_color( 33, rgb.r, rgb.g, rgb.b );
	// rgb_matrix_set_color( 32, rgb.r, rgb.g, rgb.b );
	// rgb_matrix_set_color( 31, rgb.r, rgb.g, rgb.b );
	// rgb_matrix_set_color( 30, rgb.r, rgb.g, rgb.b );
	// rgb_matrix_set_color( 29, rgb.r, rgb.g, rgb.b );

	// top row (4)
	rgb_matrix_set_color( 24, rgb.r, rgb.g, rgb.b );
	rgb_matrix_set_color( 25, rgb.r, rgb.g, rgb.b );
	rgb_matrix_set_color( 26, rgb.r, rgb.g, rgb.b );
	rgb_matrix_set_color( 27, rgb.r, rgb.g, rgb.b );
	rgb_matrix_set_color( 28, rgb.r, rgb.g, rgb.b );



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
	ergodox_right_led_3_set(LED_BRIGHTNESS_MED);
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

	if (biton32(layer_state) == _BASE) {
		ergodox_right_led_1_off();
	}
}


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
	set_layer_color(biton32(layer_state));

	if (is_leader_active()) {
		my_indicate_leader();
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

void caps_word_set_user(bool active) {
	if (active) {
		my_indicate_caps_word_on();
	} else {
		my_indicate_caps_word_off();
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

	switch(biton32(state)) {
		case _BASE:
//	SEND_STRING(".");

			ergodox_right_led_1_off();
			break;

		default:
		//SEND_STRING("+");
			if (!is_oneshot_layer_active()) {
				ergodox_right_led_1_set(LED_BRIGHTNESS_HI);
			}
			else {
				ergodox_right_led_1_set(LED_BRIGHTNESS_LO);
			}
			ergodox_right_led_1_on();
	}

	return state;
};
