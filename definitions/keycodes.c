#include "definitions/keycodes.h"
#include "features/leader.h"
#include "features/lighting.h"
#include "string.h"

uint8_t mf_prev_layer = 0;
bool mf_was_interrupted = false;

void mf_handle_key_event(uint16_t keycode, keyrecord_t *record,
                         mf_key_config *key,
                         void (*fn_down)(uint16_t *, keyrecord_t *),
                         void (*fn_up)(uint16_t *, keyrecord_t *));
void mf_do_action(uint16_t keycode, keyrecord_t *record,
                  struct mf_key_event_config *event);
void mf_do_release(uint16_t keycode, keyrecord_t *record,
                   struct mf_key_event_config *event);
void mf_do_interrupt(uint16_t keycode, keyrecord_t *record,
                     struct mf_key_event_config *event);
void mf_handle_caps_word(uint16_t keycode);
void mf_indicate_success(uint16_t *keycode);
void mf_check_disable_oneshot(keyrecord_t *record, uint16_t *keycode_pressed,
                              uint16_t *keycode_sent);

void mf_reset_layer(void) {
  if (mf_prev_layer) {
    layer_move(mf_prev_layer);
  } else {
    layer_move(_BASE);
  }
}

void mf_advanced(uint16_t keycode, keyrecord_t *record, uint16_t tap_kc,
                 bool tap_do_register, uint16_t tap_interrupt_kc,
                 uint16_t hold_kc, bool hold_do_register,
                 uint16_t hold_interrupt_kc) {

  mf_handle_key_event(keycode, record,
                      &(mf_key_config){
                          .tap = {.keycode = tap_kc,
                                  .interrupt_keycode = tap_interrupt_kc,
                                  .do_register = tap_do_register},
                          .hold = {.keycode = hold_kc,
                                   .interrupt_keycode = hold_interrupt_kc,
                                   .do_register = hold_do_register},
                      },
                      MF_NOFN, MF_NOFN);
}

void mf_str_advanced(uint16_t keycode, keyrecord_t *record, const char *tap_str,
                     const char *hold_str) {
  mf_handle_key_event(keycode, record,
                      &(mf_key_config){
                          .tap = {.str = tap_str, .keycode = MF_NOKEY},
                          .hold = {.str = hold_str, .keycode = MF_NOKEY},
                      },
                      MF_NOFN, MF_NOFN);
}

void my_clear_all_mods(void) {
  clear_mods();
  clear_weak_mods();
  clear_oneshot_mods();
  caps_word_off();
}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  if (!mf_process_key(keycode, record)) {
    return false;
  }

  return true;
}

/***                          ***/
/*** PER-KEY HELPER FUNCTIONS ***/
/***                          ***/

/*
 * SYM KEY
 */
void mf_on_sym_key_down(uint16_t *keycode, keyrecord_t *record) {
  if (record->tap.count > 0) {
    // tapped at least once, then pressed (unknown at this point if it's a hold
    // or tap)

    switch (biton32(layer_state)) {
    case _SYM:
      reset_oneshot_layer();
      layer_move(_CODE);
      break;

    case _CODE:
      reset_oneshot_layer();
      mf_reset_layer();
      break;

    default:
      if (record->tap.count == 1) {
        mf_prev_layer = biton32(layer_state);
        layer_move(_SYM);
      }
      break;
    }
  } else {
    // single hold

    reset_oneshot_layer();

    switch (biton32(layer_state)) {
    case _SYM:
      layer_move(_CODE);
      break;

    case _CODE:
      mf_reset_layer();
      break;

    default:
      mf_prev_layer = biton32(layer_state);
      layer_move(_SYM);
      break;
    }
  }
}
void mf_on_sym_key_up(uint16_t *keycode, keyrecord_t *record) {
  // assume !record->event.pressed

  switch (biton32(layer_state)) {
  case _CODE:
  case _SYM:
    if (timer_elapsed(mf_key_timer) < get_tapping_term(*keycode, record)) {
      if (record->tap.count == 1) {
        // handle releases before tapping term for SYM key (i.e.: taps)
        set_oneshot_layer(biton32(layer_state), ONESHOT_START);
      } else {
        reset_oneshot_layer();
        mf_reset_layer();
      }
      return;
    }

    mf_reset_layer();
    break;

  case _BASE:
    reset_oneshot_layer();
    mf_reset_layer();
    break;
  }
}

/***                          ***/
/***     MAIN MF FUNCTIONS    ***/
/***                          ***/

/*
 * MAIN MF PROCESSING FUNCTION
 */
bool mf_process_key(uint16_t keycode, keyrecord_t *record) {
  // skip all processing below if the leader key has been tapped
  if (leading) {
    return true;
  }

  if (record->event.pressed) {
    mf_key_timer = timer_read();
  }

  switch (keycode) {
  case _ACTION1:
    MF_TAP_HOLD_ONCE(HYPR(KC_F20), MEH(KC_F20));
    return false;

  case _ACTION2:
    MF_TAP_HOLD_ONCE(HYPR(KC_F19), MEH(KC_F19));
    return false;

  case _TAB_CLOSE_UN:
    MF_TAP_HOLD_ONCE(LCMD(KC_W), LCMD(LSFT(KC_T)));
    return false;

  case _CUR_DIR:
    my_clear_all_mods();
    MF_STR_TAP("./");
    return false;

  case _UP_DIR:
    my_clear_all_mods();
    MF_STR_TAP("../");
    return false;

  case _NIX_HOME:
    my_clear_all_mods();
    MF_STR_TAP("~/");
    return false;

  case _COMMENT:
    my_clear_all_mods();
    MF_STR_TAP("// ");
    return false;

  case _PAREN:
    my_clear_all_mods();
    MF_STR_TAP_HOLD("()" SS_TAP(X_LEFT), "''" SS_TAP(X_LEFT));
    return false;

  case _CBRACKET:
    my_clear_all_mods();
    MF_STR_TAP_HOLD("{}" SS_TAP(X_LEFT), "[]" SS_TAP(X_LEFT));
    return false;

  case _BRACKET:
    my_clear_all_mods();
    MF_STR_TAP_HOLD("[]" SS_TAP(X_LEFT), "{}" SS_TAP(X_LEFT));
    return false;

  case _BEG_CBLOCK:
    my_clear_all_mods();
    MF_STR_TAP_HOLD("/* ", "/**" SS_TAP(X_ENTER));
    return false;

  case _END_CBLOCK:
    my_clear_all_mods();
    MF_STR_TAP("*/");
    return false;

  case _SARROW:
    my_clear_all_mods();
    MF_STR_TAP("->");
    return false;

  case _DARROW:
    my_clear_all_mods();
    MF_STR_TAP_HOLD("=>", "=== ");
    return false;

  case _NEXT_DESK:
    my_clear_all_mods();
    MF_TAP_NO_REPEAT_HOLD(LCTL(KC_RIGHT), LCMD(KC_N));
    return false;

  case _KC_E:
    MF_TAP_NO_REPEAT_HOLD(KC_E, KC_QUOTE);
    return false;

  case _PREV_DESK:
    my_clear_all_mods();
    MF_TAP_NO_REPEAT_HOLD(LCTL(KC_LEFT), KC_F11);
    return false;

  case _HTML_OPEN:
    my_clear_all_mods();
    MF_STR_TAP("<>" SS_TAP(X_LEFT));
    return false;

  case _HTML_CLOSE:
    my_clear_all_mods();
    MF_STR_TAP("</>" SS_TAP(X_LEFT));
    return false;

  case _LTEQ:
    my_clear_all_mods();
    MF_TAP_HOLD_MIXED(KC_LABK, "", MF_NOKEY, "<=");
    return false;

  case _GTEQ:
    my_clear_all_mods();
    MF_TAP_HOLD_MIXED(KC_RABK, "", MF_NOKEY, ">=");
    return false;

  case _APP_WINS:
    MF_TAP_NO_REPEAT_HOLD(LCMD(KC_GRAVE), LCMD(LSFT(KC_GRAVE)));
    return false;

  case _APP_TABS:
    MF_TAP_NO_REPEAT_HOLD(LCTL(KC_TAB), LCMD(LOPT(KC_F19)));
    return false;

  case _SPACE:
    MF_TAP_HOLD_ADVANCED(KC_SPACE, true, KC_SPACE, KC_RSFT, true, KC_RSFT);
    return false;

  case _DOT:
    my_clear_all_mods();
    MF_TAP_NO_REPEAT_HOLD(KC_DOT, KC_EXLM);
    return false;

  case _EQUAL:
    my_clear_all_mods();
    MF_TAP_HOLD_ONCE(KC_EQUAL, LOPT(LSFT(KC_MINUS)));
    return false;

  case _DASH:
    my_clear_all_mods();
    MF_TAP_HOLD_ONCE(KC_MINUS, LOPT(KC_MINUS));
    return false;

  case _KC_HASH:
    my_clear_all_mods();
    MF_TAP_HOLD_MIXED(KC_HASH, "", MF_NOKEY, "#!");
    return false;

  case _ZOOM_OUT:
    my_clear_all_mods();
    MF_TAP_NO_REPEAT_HOLD(LCMD(KC_MINUS), HYPR(KC_Z));
    return false;

  case _SCRNSHT1:
    MF_TAP_HOLD_ONCE(SCMD(KC_4), SCMD(KC_3));
    return false;

  case _ZOOM_IN:
    my_clear_all_mods();
    MF_TAP_NO_REPEAT_HOLD(LCMD(KC_PLUS), MEH(KC_1));
    return false;

  case _VOL_UP:
    my_clear_all_mods();
    MF_TAP_NO_REPEAT_HOLD(KC_AUDIO_VOL_UP, KC_MEDIA_NEXT_TRACK);
    return false;

  case _VOL_DOWN:
    my_clear_all_mods();
    MF_TAP_NO_REPEAT_HOLD(KC_AUDIO_VOL_DOWN, KC_MEDIA_PREV_TRACK);
    return false;

  case _FN_S:
    MF_TAP_NO_REPEAT_HOLD(KC_0, LCMD(KC_S));
    return false;

  case _FN_X:
    my_clear_all_mods();
    MF_TAP_NO_REPEAT_HOLD(MEH(KC_X), LCMD(KC_Q));
    return false;

  case _NEW_MIN:
    my_clear_all_mods();
    MF_TAP_NO_REPEAT_HOLD(LCMD(KC_T), LCMD(KC_M));
    return false;

  case _KC_3:
    my_clear_all_mods();
    MF_TAP_NO_REPEAT_HOLD(KC_3, KC_DOT);
    return false;

  case _LPRN:
    my_clear_all_mods();
    MF_TAP_HOLD_MIXED(KC_LPRN, MF_NOKEY, MF_NOKEY,
                      "()" SS_TAP(X_LEFT)); // NOLINT
    return false;

  case _RPRN:
    my_clear_all_mods();
    MF_TAP_NO_REPEAT_HOLD(KC_RPRN, KC_RBRACKET);
    return false;

  case _SYM_KEY:
    MF_FN_ADVANCED(mf_on_sym_key_down, mf_on_sym_key_up);
    return false;
  }

  // run this here for all non-MF keycodes
  // (also runs in mf_handle_key_event())
  mf_check_disable_oneshot(record, &keycode, KC_NO);

  return true;
}

/***                        ***/
/***    HELPER FUNCTIONS    ***/
/***                        ***/

void(mf_handle_key_event)(uint16_t keycode, keyrecord_t *record,
                          mf_key_config *key,
                          void (*fn_down)(uint16_t *, keyrecord_t *),
                          void (*fn_up)(uint16_t *, keyrecord_t *)) {
  //
  // function to handle multi-function keys
  //
  if (fn_down && record->event.pressed) {
    (*fn_down)(&keycode, record);
  }

  if (record->tap.count > 0) {
    // key was tapped one or more times

    if (record->tap.interrupted) {
      if (record->event.pressed) {
        // interrupt tap when key is pressed and still down
        mf_do_interrupt(keycode, record, &key->tap);
      }
    } else if (!record->event.pressed) {
      // key up, release tap keycode
      mf_do_release(keycode, record, &key->tap);
      // reset mf_was_interrupted
      mf_was_interrupted = false;
    } else if (record->event.pressed) {
      // key down, press tap keycode
      mf_do_action(keycode, record, &key->tap);
    }
  } else {
    // key is being held or being released from a single hold

    if (record->tap.interrupted) {
      if (record->event.pressed) {
        // hold interrupted
        mf_do_interrupt(keycode, record, &key->hold);
      }
    } else if (!record->event.pressed) {
      // single hold up
      mf_do_release(keycode, record, &key->hold);
    } else if (record->event.pressed) {
      // single hold down

      // if hold string is not set
      // and tap string or keycode is set, send that
      if ((key->hold.str && (0 == strcmp(key->hold.str, ""))) &&
          ((0 != strcmp(key->tap.str, "")) || key->tap.keycode)) {
        // key is a string key and hold string
        // is not defined; send tap string
        mf_do_action(keycode, record, &key->tap);
      } else {
        mf_do_action(keycode, record, &key->hold);
      }
    }
  }

  if (fn_up && !record->event.pressed) {
    (*fn_up)(&keycode, record);
  }
}

void mf_do_action(uint16_t keycode, keyrecord_t *record,
                  struct mf_key_event_config *event) {
  if (event->keycode) {
    // handle caps word
    mf_handle_caps_word(event->keycode);

    if (event->do_register) {
      mf_indicate_success(&event->keycode);

      // register the keycode
      register_code16(event->keycode);
    } else {
      mf_indicate_success(&event->keycode);

      // tap the keycode
      tap_code16(event->keycode);
    }
  } else if (event->str && (0 != strcmp(event->str, ""))) {
    my_clear_all_mods();
    send_string(event->str);
  }

  mf_check_disable_oneshot(record, &keycode, &event->keycode);
}

void mf_handle_caps_word(uint16_t keycode) {
  if (is_caps_word_on() && !caps_word_press_user(keycode)) {
    caps_word_off();
  }
}

void mf_do_release(uint16_t keycode, keyrecord_t *record,
                   struct mf_key_event_config *event) {
  if (event->do_register && event->keycode) {
    // unregister the keycode
    unregister_code16(event->keycode);
  }

  mf_check_disable_oneshot(record, &keycode, &event->keycode);
}

void mf_do_interrupt(uint16_t keycode, keyrecord_t *record,
                     struct mf_key_event_config *event) {
  if (event->keycode) {
    // handle caps word
    mf_handle_caps_word(event->keycode);

    // send interrupt key tap if set, otherwise send the tap key
    if (event->interrupt_keycode) {
      tap_code16(event->interrupt_keycode);
    } else {
      tap_code16(event->keycode);
    }
  } else if (event->str && (0 != strcmp(event->str, ""))) {
    my_clear_all_mods();
    send_string(event->str);
  }

  mf_was_interrupted = true;
  mf_check_disable_oneshot(record, &keycode, &event->keycode);
}

/***                        ***/
/***    PER-KEY SETTINGS    ***/
/***                        ***/

// set tapping term per key
uint16_t get_tapping_term(uint16_t keycode, keyrecord_t *record) {
  switch (keycode) {
  case _SYM_KEY:
    return 140;

  case _SPACE:
    return TAPPING_TERM;

  case _FN_KEY:
  case _KC_E: // apostrophe when held
  case _KC_T: // FN layer
  case _KC_S: // NUM layer
  case _KC_K: // CODE layer
  case _KC_V: // CODE layer
    return TAPPING_TERM - 40;

  case _TAB_CLOSE_UN:
    return TAPPING_TERM + 50;

  default:
    return TAPPING_TERM - 50;
  }
}

// set force_hold per key
bool get_tapping_force_hold(uint16_t keycode, keyrecord_t *record) {
  switch (keycode) {
  case _KC_E: // apostrophe when held
    return true;

  default:
    return false;
  }
}

bool caps_word_press_user(uint16_t keycode) {
  switch (keycode) {
  // Keycodes that continue Caps Word, with shift applied.
  case KC_A ... KC_Z:
    add_weak_mods(MOD_BIT(KC_LSFT)); // Apply shift to the next key.
    return true;

  // Keycodes that continue Caps Word, without shifting.
  case KC_1 ... KC_0:
  case KC_BSPC:
  case KC_DEL:
  case KC_UNDS:
  case KC_DASH:
  case _SYM_KEY:
  case _FN_KEY:
    return true;

  default:
    return false; // Deactivate Caps Word.
  }
}

void mf_indicate_success(uint16_t *keycode) {
  switch (*keycode) {
  case KC_MEDIA_NEXT_TRACK:
  case KC_MEDIA_PREV_TRACK:
    my_indicate_success();
    break;

  case LCMD(KC_S):
    my_flash_twice();
    break;
  }
}
void mf_check_disable_oneshot(keyrecord_t *record, uint16_t *keycode_pressed,
                              uint16_t *keycode_sent) {
  if (is_oneshot_layer_active()) {
    switch (*keycode_sent) {
    case KC_SPACE:
      if (!mf_was_interrupted) {
        return;
      } else {
        clear_oneshot_layer_state(ONESHOT_PRESSED);
        reset_oneshot_layer();
        mf_reset_layer();
      }
      break;
    }

    switch (*keycode_pressed) {
    case KC_LSFT:
    case KC_LCMD:
    case KC_LCTL:
    case KC_LOPT:
    case KC_RSFT:
    case KC_RCMD:
    case KC_RCTL:
    case KC_ROPT:
    case _SYM_KEY:
      return;
    }

    if (!record->event.pressed) {
      clear_oneshot_layer_state(ONESHOT_PRESSED);
      reset_oneshot_layer();
      mf_reset_layer();
    }
  }
}
