#ifdef COMBO_ENABLE

#include "definitions/keycodes.h"
#include "features/leader.h"
#include "features/lighting.h"

enum combos {
    COMBO_BACKSPACE,
    COMBO_BACKSPACE_ALT,
    COMBO_ESC,
    COMBO_TAB,
    COMBO_TAB_ALT,
    COMBO_CUT,
    COMBO_COPY,
    COMBO_PASTE,
    COMBO_SAVE,
    COMBO_SELECT_ALL,
    COMBO_LAST_APP_ALT,
    COMBO_LAST_APP,
    COMBO_DQUOTE,
    COMBO_BOOTLOADER,
    COMBO_RESET_ZOOM,
    COMBO_MUTE,
    COMBO_HOME,
    COMBO_END_KEY,
    COMBO_PAUSE,

    COMBO_COUNT
};

uint16_t combo_key_timer;
uint16_t COMBO_LEN = COMBO_COUNT;

const uint16_t PROGMEM combo_backspace[] = {KC_N, _KC_E, COMBO_END};
const uint16_t PROGMEM combo_backspace_alt[] = {_KC_K, KC_N, COMBO_END};

const uint16_t PROGMEM combo_esc[] = {KC_F, KC_W, COMBO_END};
const uint16_t PROGMEM combo_tab[] = {_KC_S, _KC_T, COMBO_END};
const uint16_t PROGMEM combo_tab_alt[] = {_KC_T, KC_G, COMBO_END};

const uint16_t PROGMEM combo_cut[] = {KC_X, KC_D, COMBO_END};
const uint16_t PROGMEM combo_copy[] = {KC_X, KC_C, COMBO_END};
const uint16_t PROGMEM combo_paste[] = {KC_C, KC_D, COMBO_END};
const uint16_t PROGMEM combo_save[] = {KC_F, KC_P, COMBO_END};

const uint16_t PROGMEM combo_select_all[] = {KC_Z, KC_X, KC_C, KC_D, COMBO_END};

const uint16_t PROGMEM combo_dquote[] = {_KC_E, KC_I, COMBO_END};

const uint16_t PROGMEM combo_reset_zoom[] = {_ZOOM_IN, _ZOOM_OUT, COMBO_END};
const uint16_t PROGMEM combo_mute[] = {_VOL_UP, _VOL_DOWN, COMBO_END};
const uint16_t PROGMEM combo_pause[] = {_PLAY, _VOL_DOWN, COMBO_END};

const uint16_t PROGMEM combo_home[] = {KC_PGUP, KC_O, COMBO_END};
const uint16_t PROGMEM combo_end_key[] = {KC_PGDOWN, KC_QUES, COMBO_END};

const uint16_t PROGMEM combo_last_app_alt[] = {KC_N, _KC_E, KC_I, COMBO_END};
const uint16_t PROGMEM combo_last_app[] = {KC_R, _KC_S, _KC_T, COMBO_END};
const uint16_t PROGMEM combo_bootloader[] = {MEH(KC_F13), KC_Z, COMBO_END};

combo_t key_combos[COMBO_COUNT] = {
    [COMBO_BACKSPACE] = COMBO_ACTION(combo_backspace),
    /* [COMBO_BACKSPACE_ALT] = COMBO_ACTION(combo_backspace_alt), */
    [COMBO_ESC] = COMBO_ACTION(combo_esc),
    [COMBO_TAB] = COMBO_ACTION(combo_tab),
    /* [COMBO_TAB_ALT] = COMBO_ACTION(combo_tab_alt), */
    [COMBO_CUT] = COMBO_ACTION(combo_cut),
    [COMBO_COPY] = COMBO_ACTION(combo_copy),
    [COMBO_PASTE] = COMBO_ACTION(combo_paste),
    [COMBO_SAVE] = COMBO_ACTION(combo_save),
    [COMBO_SELECT_ALL] = COMBO_ACTION(combo_select_all),
    [COMBO_DQUOTE] = COMBO_ACTION(combo_dquote),
    [COMBO_RESET_ZOOM] = COMBO_ACTION(combo_reset_zoom),
    [COMBO_MUTE] = COMBO_ACTION(combo_mute),
    [COMBO_LAST_APP_ALT] = COMBO_ACTION(combo_last_app_alt),
    [COMBO_LAST_APP] = COMBO_ACTION(combo_last_app),
    [COMBO_BOOTLOADER] = COMBO_ACTION(combo_bootloader),
    [COMBO_HOME] = COMBO_ACTION(combo_home),
    [COMBO_END_KEY] = COMBO_ACTION(combo_end_key),
    [COMBO_PAUSE] = COMBO_ACTION(combo_pause),
};

void process_combo_event(uint16_t combo_index, bool pressed) {
    if (pressed) {
        combo_key_timer = timer_read();
    }

    if (leading) {
        return;
    }

    if ((combo_index != COMBO_BACKSPACE)
        && (combo_index != COMBO_BACKSPACE_ALT)) {
        caps_word_off();
    }

    if ((combo_index != COMBO_BACKSPACE)
        && (combo_index != COMBO_BACKSPACE_ALT)
        && (combo_index != COMBO_ESC)
        && (combo_index != COMBO_TAB)
        && (combo_index != COMBO_TAB_ALT)
        && (combo_index != COMBO_PASTE)
        && (combo_index != COMBO_COPY)
        && (combo_index != COMBO_SAVE)) {
        my_clear_all_mods();
    }

    if (pressed) {
        switch (combo_index) {
        case COMBO_BACKSPACE_ALT:
        case COMBO_BACKSPACE:
            register_code(KC_BSPACE);
            break;

        case COMBO_ESC:
            tap_code(KC_ESC);
            break;

        case COMBO_TAB_ALT:
        case COMBO_TAB:
            register_code(KC_TAB);
            break;

        case COMBO_PAUSE:
            tap_code16(HYPR(KC_F17));
            my_indicate_success();
            break;

        case COMBO_DQUOTE:
            tap_code16(KC_DQUO);
            break;

        case COMBO_CUT:
            tap_code16(LCMD(KC_X));
            my_indicate_success();
            break;

        case COMBO_COPY:
            tap_code16(LCMD(KC_C));
            my_flash_twice();
            break;

        case COMBO_PASTE:
            tap_code16(LCMD(KC_V));
            my_indicate_success();
            break;

        case COMBO_SAVE:
            tap_code16(LCMD(KC_S));
            my_flash_twice();
            break;

        case COMBO_SELECT_ALL:
            tap_code16(LCMD(KC_A));
            my_indicate_success();
            break;

        case COMBO_LAST_APP_ALT:
        case COMBO_LAST_APP:
            tap_code16(LCMD(KC_TAB));
            my_indicate_success();
            break;

        case COMBO_BOOTLOADER:
            my_indicate_success();
            reset_keyboard();
            break;

        case COMBO_RESET_ZOOM:
            tap_code16(HYPR(KC_0));
            my_indicate_success();
            break;

        case COMBO_MUTE:
            tap_code16(KC_AUDIO_MUTE);
            my_indicate_success();
            break;

        case COMBO_HOME:
            tap_code(KC_HOME);
            break;

        case COMBO_END_KEY:
            tap_code(KC_END);
            break;
        }
    }

    if (timer_elapsed(combo_key_timer) > 500) {
        switch (combo_index) {
        case COMBO_DQUOTE:
            my_indicate_success();
            tap_code16(KC_DQUO);
            tap_code16(KC_LEFT);
            break;
        }
    }
}

bool process_combo_key_release(
    uint16_t combo_index, combo_t *combo, uint8_t key_index, uint16_t keycode) {
    //
    // process release
    //
    switch (combo_index) {
    case COMBO_BACKSPACE_ALT:
    case COMBO_BACKSPACE:
        unregister_code(KC_BSPACE);
        break;

    case COMBO_TAB_ALT:
    case COMBO_TAB:
        unregister_code(KC_TAB);
        break;
    }
    return false;
}

bool get_combo_term(uint16_t index, combo_t *combo) {
    switch (index) {
    // COMMANDS
    case COMBO_ESC:
    case COMBO_SAVE:
    case COMBO_CUT:
    case COMBO_SELECT_ALL:
    case COMBO_LAST_APP_ALT:
    case COMBO_LAST_APP:
        return 200;

    // COMMANDS NOT EASILY TRIGGERED
    case COMBO_PASTE:
        return 80;

    // BOOTLOADER
    case COMBO_BOOTLOADER:
        return 250;

    case COMBO_DQUOTE:
        return 0;

    // EASILY-TRIGGERED TYPING COMBOS
    case COMBO_COPY:
    case COMBO_TAB:
    case COMBO_BACKSPACE:
        return 5;

    // DEFAULT
    case COMBO_PAUSE:
    case COMBO_RESET_ZOOM:
    case COMBO_HOME:
    case COMBO_END_KEY:
    case COMBO_MUTE:
    case COMBO_BACKSPACE_ALT:
    case COMBO_TAB_ALT:
    default:
        return 25;
    }
}

bool get_combo_must_hold(uint16_t index, combo_t *combo) {
    switch (index) {
    case COMBO_CUT:
    case COMBO_COPY:
    case COMBO_PASTE:
    case COMBO_SAVE:
    case COMBO_SELECT_ALL:
    case COMBO_LAST_APP_ALT:
    case COMBO_LAST_APP:
    case COMBO_BOOTLOADER:
    case COMBO_RESET_ZOOM:
    case COMBO_MUTE:
    case COMBO_PAUSE:
    case COMBO_HOME:
    case COMBO_END_KEY:
        return true;
    }

    return false;
}

#endif
