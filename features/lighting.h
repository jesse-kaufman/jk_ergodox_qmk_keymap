extern rgb_config_t rgb_matrix_config;
extern const uint8_t PROGMEM ledmap[][DRIVER_LED_TOTAL][3];

void my_indicate_modifier(void);
void my_indicate_success(void);
void my_flash_twice(void);
// void my_indicate_shift_modifier_on(void);
// void my_indicate_shift_modifier_off(void);
void my_indicate_caps_word_on(void);
void my_indicate_caps_word_off(void);
