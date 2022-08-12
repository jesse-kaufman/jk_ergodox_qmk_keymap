#pragma once

// LAYER TAP KEYCODES
#define _F_FN LT(_FN,KC_F)

// FANCY QUOTES KEYCODES
#define _LDFQUO LALT(KC_LBRACKET)
#define _RDFQUO LALT(LSFT(KC_LBRACKET))
#define _LFQUO LALT(KC_RBRACKET)
#define _RFQUO LALT(LSFT(KC_RBRACKET))

// ONE-SHOT MODIFIERS
#define _OSM_CMD OSM(MOD_LGUI)
#define _OSM_SHIFT OSM(MOD_LSFT)
#define _OSM_ALT OSM(MOD_LALT)
#define _OSM_CTR OSM(MOD_LCTL)
#define _OSM_CMDALT OSM(MOD_LGUI | MOD_LALT)

// PROGRAMMING SHORTCUTS
#define _MEH_LBRKT MEH(KC_LBRACKET)

// MOUSE KEYCODE
#define _SHFT_WHDN LSFT(KC_MS_WH_DOWN)
#define _SHFT_WHUP LSFT(KC_MS_WH_UP)

// GLOBAL HOTKEYS
#define _ZOOM_IN HYPR(KC_EQUAL)
#define _ZOOM_OUT HYPR(KC_MINUS)
#define _FORWARD MEH(KC_UP)
#define _BACK MEH(KC_DOWN)

// MOD TAPS
#define _SHFT_SPACE MT(MOD_LSFT, KC_SPACE)
#define _SHFT_ENTER MT(MOD_RSFT, KC_ENTER)

// OTHER KEYCODES
#define _UNDO LGUI(KC_Z)
#define _REDO LGUI(LSFT(KC_Z))
#define _LAYER_LEDS TOGGLE_LAYER_COLOR
#define _SCREEN_DN KC_BRIGHTNESS_DOWN
#define _SCREEN_UP KC_BRIGHTNESS_UP
#define _PREV KC_MEDIA_PREV_TRACK
#define _NEXT KC_MEDIA_NEXT_TRACK
#define _VOL_UP KC_AUDIO_VOL_UP

// CUSTOM KEYCODES
enum custom_keycodes {
    _UP_DIR = SAFE_RANGE,
};
