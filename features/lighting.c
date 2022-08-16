/**
 * LED CONTROL
 */

#include "lighting.h"

void my_indicate_success(void) {
	ergodox_led_all_set(LED_BRIGHTNESS_HI);
	ergodox_led_all_on();
	_delay_ms(HOLD_FIRED_INDICATOR_TIMEOUT);
	ergodox_led_all_off();
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

void my_indicate_shift_modifier(void) {

		RGB rgb = {
			.r = 255,
			.g = 255,
			.b = 255
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

void keyboard_post_init_user(void) {
  rgb_matrix_enable();
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
  if (keyboard_config.disable_layer_led) { return; }
  uint8_t mods = get_oneshot_mods() | get_mods() ;


  set_layer_color(biton32(layer_state));

  if (is_caps_word_on()) {
	my_indicate_shift_modifier();
		  ergodox_right_led_3_set(LED_BRIGHTNESS_HI);
		  ergodox_right_led_3_on();
  }
	if (is_caps_word_on() || host_keyboard_leds() & (1<<USB_LED_CAPS_LOCK)) {

	}

  if (mods) {
	  if (mods & MOD_MASK_SHIFT )  {
		my_indicate_shift_modifier();
		ergodox_right_led_3_set(LED_BRIGHTNESS_LO);
		ergodox_right_led_3_on();
	  }
	  else if (mods & MOD_MASK_GUI )  {
		my_indicate_modifier();
	  }
	  else if (mods & MOD_MASK_CTRL )  {
		my_indicate_modifier();
	  }
	  else if (mods & MOD_MASK_ALT )  {
		my_indicate_modifier();
	  }
  }
  else if (!is_caps_word_on()) {
	ergodox_right_led_3_off();
  }
}


void oneshot_mods_changed_user(uint8_t mods) {
  //uint8_t led_usb_state = host_keyboard_leds();
  ergodox_right_led_1_set(LED_BRIGHTNESS_HI);

  uint8_t one_shot = get_oneshot_mods();

  if ((mods | one_shot) & MOD_MASK_SHIFT) {
			ergodox_right_led_2_on();
  }
  if ((mods | one_shot) & MOD_MASK_GUI) {
			ergodox_right_led_2_on();
  }
  if ((mods | one_shot) & MOD_MASK_CTRL) {
			ergodox_right_led_2_on();
  }
  if ((mods | one_shot) & MOD_MASK_ALT) {
			ergodox_right_led_2_on();
  }

  if (!(mods| one_shot) ) {
			ergodox_right_led_2_off();
  }
}


uint8_t layer_state_set_user(uint8_t state) {

  uint8_t layer = biton32(state);
  //uint8_t mods = get_oneshot_mods() | get_mods();

  ergodox_right_led_1_off();

  if ( layer ) {
	  if (is_oneshot_layer_active()) {
		ergodox_right_led_1_set(LED_BRIGHTNESS_LO);
	  }
	  else {
		ergodox_right_led_1_set(LED_BRIGHTNESS_HI);
	  }
	ergodox_right_led_1_on();
  }
  else {
	  ergodox_right_led_1_off();
  }

  return state;
};
