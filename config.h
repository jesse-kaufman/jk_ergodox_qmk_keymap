#define ORYX_CONFIGURATOR

#define ___X___ XXXXXXX

#undef TAPPING_TERM
#define TAPPING_TERM 275
#define ONESHOT_TAP_TOGGLE 1
#define ONESHOT_TIMEOUT 1703
#define RGB_DISABLE_TIMEOUT 180000
#define RGB_MATRIX_FRAMEBUFFER_EFFECTS
#define RGB_MATRIX_KEYPRESSES
#define USB_SUSPEND_WAKEUP_DELAY 0
#define RGB_MATRIX_STARTUP_SPD 60


#define MK_KINETIC_SPEED
#define MOUSEKEY_INITIAL_SPEED 300
#define MOUSEKEY_BASE_SPEED 5500
#undef MOUSEKEY_INTERVAL
#define MOUSEKEY_INTERVAL 16


#define COMBO_HOLD_TERM 200

#define COMBO_ONLY_FROM_LAYER 0
#define COMBO_PROCESS_KEY_RELEASE
#define EXTRA_SHORT_COMBOS
#define COMBO_MUST_HOLD_PER_COMBO
#define COMBO_COMBO_TERM_PER_COMBO
// #define COMBO_STRICT_TIMER

#define LEADER_TIMEOUT 1000
#define LEADER_PER_KEY_TIMING
#define LEADER_NO_TIMEOUT


#define CAPS_WORD_IDLE_TIMEOUT 0

#undef LOCKING_SUPPORT_ENABLE
#undef LOCKING_RESYNC_ENABLE

#define LAYER_STATE_8BIT

#undef NKRO_ENABLE

#define PERMISSIVE_HOLD
#define TAPPING_TERM_PER_KEY
#undef HOLD_ON_OTHER_KEY_PRESS
#define IGNORE_MOD_TAP_INTERRUPT
#define TAPPING_FORCE_HOLD_PER_KEY

#define TAP_HOLD_CAPS_DELAY 200



/**
 * RGB MATRIX CONFIG
 */
#define RGB_TRIGGER_ON_KEYDOWN          // trigger on keydown instead of key up to feel more responsive
#undef ENABLE_RGB_MATRIX_SOLID_COLOR     // Static single hue, no speed support
#undef ENABLE_RGB_MATRIX_ALPHAS_MODS        // Static dual hue, speed is hue for secondary hue
#undef ENABLE_RGB_MATRIX_GRADIENT_UP_DOWN    // Static gradient top to bottom, speed controls how much gradient changes
#undef ENABLE_RGB_MATRIX_GRADIENT_LEFT_RIGHT    // Static gradient left to right, speed controls how much gradient changes
#undef ENABLE_RGB_MATRIX_BREATHING           // Single hue brightness cycling animation
#undef ENABLE_RGB_MATRIX_BAND_SAT        // Single hue band fading saturation scrolling left to right
#undef ENABLE_RGB_MATRIX_BAND_VAL       // Single hue band fading brightness scrolling left to right
#undef ENABLE_RGB_MATRIX_BAND_PINWHEEL_SAT   // Single hue 3 blade spinning pinwheel fades saturation
#undef ENABLE_RGB_MATRIX_BAND_PINWHEEL_VAL  // Single hue 3 blade spinning pinwheel fades brightness
#undef ENABLE_RGB_MATRIX_BAND_SPIRAL_SAT    // Single hue spinning spiral fades saturation
#undef ENABLE_RGB_MATRIX_BAND_SPIRAL_VAL    // Single hue spinning spiral fades brightness
#undef ENABLE_RGB_MATRIX_CYCLE_ALL      // Full keyboard solid hue cycling through full gradient
#undef ENABLE_RGB_MATRIX_CYCLE_LEFT_RIGHT   // Full gradient scrolling left to right
#undef ENABLE_RGB_MATRIX_CYCLE_UP_DOWN    // Full gradient scrolling top to bottom
#undef ENABLE_RGB_MATRIX_CYCLE_OUT_IN        // Full gradient scrolling out to in
#undef ENABLE_RGB_MATRIX_CYCLE_OUT_IN_DUAL   // Full dual gradients scrolling out to in
#undef ENABLE_RGB_MATRIX_RAINBOW_MOVING_CHEVRON  // Full gradent Chevron shapped scrolling left to right
#undef ENABLE_RGB_MATRIX_CYCLE_PINWHEEL      // Full gradient spinning pinwheel around center of keyboard
#undef ENABLE_RGB_MATRIX_CYCLE_SPIRAL      // Full gradient spinning spiral around center of keyboard
#undef ENABLE_RGB_MATRIX_DUAL_BEACON         // Full gradient spinning around center of keyboard
#undef ENABLE_RGB_MATRIX_RAINBOW_BEACON      // Full tighter gradient spinning around center of keyboard
#undef ENABLE_RGB_MATRIX_RAINBOW_PINWHEELS   // Full dual gradients spinning two halfs of keyboard
#undef ENABLE_RGB_MATRIX_RAINDROPS           // Randomly changes a single key's hue
#undef ENABLE_RGB_MATRIX_JELLYBEAN_RAINDROPS // Randomly changes a single key's hue and saturation
#undef ENABLE_RGB_MATRIX_HUE_BREATHING       // Hue shifts up a slight ammount at the same time, then shifts back
#undef ENABLE_RGB_MATRIX_HUE_PENDULUM        // Hue shifts up a slight ammount in a wave to the right, then back to the left
#undef ENABLE_RGB_MATRIX_HUE_WAVE      // Hue shifts up a slight ammount and then back down in a wave to the right
#undef ENABLE_RGB_MATRIX_PIXEL_FRACTAL       // Single hue fractal filled keys pulsing horizontally out to edges
#undef ENABLE_RGB_MATRIX_PIXEL_FLOW          // Pulsing RGB flow along LED wiring with random hues
#undef ENABLE_RGB_MATRIX_PIXEL_RAIN          // Randomly light keys with random hues
#undef ENABLE_RGB_MATRIX_TYPING_HEATMAP      // How hot is your WPM!
#undef ENABLE_RGB_MATRIX_DIGITAL_RAIN        // That famous computer simulation
#undef ENABLE_RGB_MATRIX_SOLID_REACTIVE_SIMPLE   // Pulses keys hit to hue & value then fades value out
#undef ENABLE_RGB_MATRIX_SOLID_REACTIVE      // Static single hue, pulses keys hit to shifted hue then fades to current hue
#undef ENABLE_RGB_MATRIX_SOLID_REACTIVE_WIDE       // Hue & value pulse near a single key hit then fades value out
#undef ENABLE_RGB_MATRIX_SOLID_REACTIVE_MULTIWIDE  // Hue & value pulse near multiple key hits then fades value out
#undef ENABLE_RGB_MATRIX_SOLID_REACTIVE_CROSS      // Hue & value pulse the same column and row of a single key hit then fades value out
#undef ENABLE_RGB_MATRIX_SOLID_REACTIVE_MULTICROSS // Hue & value pulse the same column and row of multiple key hits then fades value out
#undef ENABLE_RGB_MATRIX_SOLID_REACTIVE_NEXUS      // Hue & value pulse away on the same column and row of a single key hit then fades value out
#undef ENABLE_RGB_MATRIX_SOLID_REACTIVE_MULTINEXUS // Hue & value pulse away on the same column and row of multiple key hits then fades value out
#undef ENABLE_RGB_MATRIX_SPLASH              // Full gradient & value pulse away from a single key hit then fades value out
#undef ENABLE_RGB_MATRIX_MULTISPLASH         // Full gradient & value pulse away from multiple key hits then fades value out
#undef ENABLE_RGB_MATRIX_SOLID_SPLASH        // Hue & value pulse away from a single key hit then fades value out
#undef ENABLE_RGB_MATRIX_SOLID_MULTISPLASH  // Hue & value pulse away from multiple key hits then fades value out
