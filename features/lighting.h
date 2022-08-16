#include QMK_KEYBOARD_H
#include "../definitions/layers.h"

extern rgb_config_t rgb_matrix_config;
extern const uint8_t PROGMEM ledmap[][DRIVER_LED_TOTAL][3];

void my_indicate_modifier(void);
void my_indicate_success(void);
void my_indicate_shift_modifier(void);
