#pragma once
#include QMK_KEYBOARD_H
#include "../definitions/layers.h"
#include "../definitions/keycodes.h"
#include "lighting.h"
#include "leader.h"

/**
 * TAP DANCE HELPERS
 */
#define MY_DUAL_ACTION_LGUI(kc) { .fn = {my_dual_action_lgui_each_tap, my_dual_action_lgui_finished, my_dual_action_lgui_reset}, .user_data = (void *)&((qk_tap_dance_pair_t) { kc, 0 }), }


/**
 * TAP DANCE CODES
 */
enum tap_dance_codes {
	DANCE_SPOTLIGHT,
	DANCE_TAB_LAST_APP,
	DANCE_TAB_MGMT,
	DANCE_PGUP_HOME,
	DANCE_PGDN_END,
	DANCE_ZOOM_OUT,
	DANCE_SEMICOLON,
	DANCE_SLASH_COLON,
	DANCE_QUOTE,
	DANCE_DOT,
	DANCE_12,
	DANCE_13,
	DANCE_14,
	DANCE_15,
	DANCE_16,
	DANCE_DQUOTE,
	DANCE_18,
	DANCE_L_QUOTE,
	DANCE_GTEQ,
	DANCE_LTEQ,
	DANCE_DESKTOP,
	DANCE_UP_DIR,
 	DANCE_C,
	DANCE_V,
	DANCE_X,
	DANCE_A,
	DANCE_S,
	DANCE_R,
	DANCE_T,
	DANCE_W,
	DANCE_Q,
	DANCE_O,
	DANCE_I,
	DANCE_H,
	DANCE_N,
	DANCE_M,
	DANCE_B,
	DANCE_G,

	// leave this for initializing dance_state in tapdance.h
	NUM_DANCE_CODES,
};


// TAP DANCE KEY CODES
#define _ZOOM_OUT_100 TD(DANCE_ZOOM_OUT)
#define _VOL_DOWN TD(DANCE_12)
#define _PLAY TD(DANCE_13)
#define _QUOTE TD(DANCE_QUOTE)
#define _DQUOTE TD(DANCE_DQUOTE)
#define _DOT TD(DANCE_DOT)
#define _TAB_MGMT TD(DANCE_TAB_MGMT)
#define _PGUP_HOME TD(DANCE_PGUP_HOME)
#define _PGDN_END TD(DANCE_PGDN_END)
#define _DESKTOP TD(DANCE_DESKTOP)
#define _SPOTLIGHT TD(DANCE_SPOTLIGHT)
#define _LAST_APP TD(DANCE_TAB_LAST_APP)
#define _SLASH_COLON TD(DANCE_SLASH_COLON)
#define _SEMICOLON TD(DANCE_SEMICOLON)
#define _LCBR TD(DANCE_15)
#define _LBRACKET TD(DANCE_16)
#define _LPRN TD(DANCE_18)
#define _GTEQ TD(DANCE_GTEQ)
#define _LTEQ TD(DANCE_LTEQ)
#define _KC_UP_DIR TD(DANCE_UP_DIR)
#define _HYPHEN TD(DANCE_14)

// DOUBLE-TAP FOR COMMAND
#define _KC_C TD(DANCE_C)
#define _KC_V TD(DANCE_V)
#define _KC_X TD(DANCE_X)
#define _KC_A TD(DANCE_A)
#define _KC_S TD(DANCE_S)
#define _KC_R TD(DANCE_R)
#define _KC_T TD(DANCE_T)
#define _KC_W TD(DANCE_W)
#define _KC_Q TD(DANCE_Q)
#define _KC_O TD(DANCE_O)
#define _KC_I TD(DANCE_I)
#define _KC_H TD(DANCE_H)
#define _KC_N TD(DANCE_N)
#define _KC_M TD(DANCE_M)
#define _KC_B TD(DANCE_B)
#define _KC_G TD(DANCE_G)











typedef struct {
	bool is_press_action;
	uint8_t step;
} tap;

enum {
	SINGLE_TAP = 1,
	SINGLE_HOLD,
	DOUBLE_TAP,
	DOUBLE_HOLD,
	DOUBLE_SINGLE_TAP,
	MORE_TAPS
};


uint8_t dance_step(qk_tap_dance_state_t *state);
