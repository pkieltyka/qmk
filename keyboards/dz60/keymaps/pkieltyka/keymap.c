#include QMK_KEYBOARD_H
// #include "dz60.h"

// Macros
#define ______ 					KC_TRNS
#define LAYER_DEFAULT   0
#define LAYER_MACOS     1
#define LAYER_FN        2

#define TAPPING_TERM 200
#define TAPPING_TERM_PER_KEY


// Custom code
enum {
  CC_CTL = SAFE_RANGE,
  CC_ESC,
  CC_DEL
};

// Tap dance codes
enum {
  TD_SUPER_FN   = 0
};


//
// Keymaps
//
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
	
	// layer-0
	LAYOUT_directional(
		CC_ESC, 	KC_1, 		KC_2, 		KC_3, 		KC_4, 		KC_5, 		KC_6, 		KC_7, 		KC_8, 		KC_9, 							KC_0, 		KC_MINS, 		KC_EQL, 	CC_DEL, 	CC_DEL,
		KC_TAB,		KC_Q,			KC_W,			KC_E,			KC_R,			KC_T,			KC_Y,			KC_U,			KC_I,			KC_O,								KC_P,			KC_LBRC,		KC_RBRC,	KC_BSLS,
		KC_LGUI,	KC_A,			KC_S,			KC_D,			KC_F,			KC_G,			KC_H,			KC_J,			KC_K,			KC_L,								KC_SCLN,	KC_QUOT,		KC_ENT,
		KC_LSFT,	KC_Z,			KC_X,			KC_C,			KC_V,			KC_B,			KC_N,			KC_M,			KC_COMM,	KC_DOT,							KC_SLSH,	KC_PGUP,		KC_UP,		KC_PGDN,
		CC_CTL,	  KC_LALT,	KC_LCTL,						KC_NO,		KC_SPC,							KC_NO,		TD(TD_SUPER_FN),  	KC_RCTL,	KC_LEFT,		KC_DOWN, 	KC_RGHT
	),

	// layout-1 -- macos
	LAYOUT_directional(
		______, 	______, 	______, 	______, 	______, 	______, 	______, 	______, 	______, 	______, 	          ______, 	______, 	______, 	______, 		______,
		______,		______,		______,		______,		______,		______,		______,		______,		______,		______,		          ______,		______,		______,		______,
		______,		______,		______,		______,		______,		______,		______,		______,		______,		______,		          ______,		______,		______,
		______,		______,		______,		______,		______,		______,		______,		______,		______,		______,		          ______,		______,		______,		______,
		______,		______,		          KC_LCMD,						KC_NO,		______,							KC_NO,		______,		          ______,		______,		______, 	______
	),

	// layer-2 -- fn keys
	LAYOUT_directional(
		______, 	KC_F1, 		          KC_F2, 		          KC_F3, 		KC_F4, 		KC_F5, 		KC_F6, 		KC_F7, 		KC_F8, 		KC_F9, 			        KC_F10, 	KC_F11, 	KC_F12, 	______, 		KC_DEL,
		______,		TO(LAYER_DEFAULT),	TO(LAYER_MACOS),		______,		______,		______,		______,		______,		______,		______,			        ______,		______,		______,		______,
		______,		______,		          ______,		          ______,		______,		______,		______,		______,		______,		______,			        ______,		______,		______,
		______,		______,		          ______,		          ______,		______,		______,		______,		______,		______,		______,			        ______,		______,		______,		______,
		______,		______,		                              ______,							KC_NO,		______,							KC_NO,	  ______,			        ______,		______,		______, 	______
	)

};


//
// Tap Dancing
//

typedef enum {
  SINGLE_TAP  = 1,
  SINGLE_HOLD = 2,
  DOUBLE_TAP  = 3
} td_state_t;

static td_state_t td_fn_state;

int cur_dance(tap_dance_state_t *state);

// Super-fn methods
void fn_ql_finished(tap_dance_state_t *state, void *user_data);
void fn_ql_reset(tap_dance_state_t *state, void *user_data);

tap_dance_action_t tap_dance_actions[] = {
  [TD_SUPER_FN]     = ACTION_TAP_DANCE_FN_ADVANCED(NULL, fn_ql_finished, fn_ql_reset)
};


// Determine the current tap dance state, generic method
int cur_dance(tap_dance_state_t *state) {
	if (state->count == 1) {
    if (state->interrupted || !state->pressed) {
      return SINGLE_TAP;
    } else {
      return SINGLE_HOLD; 
    }
  }
	if (state->count == 2) {
    return DOUBLE_TAP;
  } else {
    return 8;
  }
}

void fn_ql_finished(tap_dance_state_t *state, void *user_data) {
  td_fn_state = cur_dance(state);
  switch (td_fn_state) {
    case SINGLE_TAP: 
      register_code16(KC_LGUI);
      break;
    case SINGLE_HOLD: 
      register_code16(KC_LGUI);
      break;
    case DOUBLE_TAP: 
      layer_on(LAYER_FN);
      break;
  }
}

void fn_ql_reset(tap_dance_state_t *state, void *user_data) {
	switch (td_fn_state) {
    case SINGLE_TAP:
      unregister_code16(KC_LGUI);
      break;
    case SINGLE_HOLD:
			unregister_code16(KC_LGUI);
      break;
    case DOUBLE_TAP:
			layer_off(LAYER_FN);
      break;
  }
  td_fn_state = 0;
}

bool is_cc_super_ctl = false;
// uint16_t ctl_tap_timer = 0;
// bool ctl_tap_active = false;

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  switch (keycode) {
    case CC_CTL:
      if (record->event.pressed) {
        // down
        is_cc_super_ctl = true;
      } else {
        // released
        is_cc_super_ctl = false;
        // ctl_tap_timer = timer_read();
        // if (ctl_tap_active) {
        //   unregister_code16(KC_LCTL);
        //   ctl_tap_active = false;
        // }
      }
      break;

    case CC_ESC:
      if (is_cc_super_ctl) {
        if (record->event.pressed) {
          register_code(KC_GRAVE);
        } else {
          unregister_code(KC_GRAVE);
        }
      } else {
        static bool grave_esc_was_shifted = false;
        uint8_t shifted = get_mods() & ((MOD_BIT(KC_LSFT) | MOD_BIT(KC_RSFT)));

        if (record->event.pressed) {
          grave_esc_was_shifted = shifted;
          add_key(shifted ? KC_GRAVE : KC_ESCAPE);
        } else {
          del_key(grave_esc_was_shifted ? KC_GRAVE : KC_ESCAPE);
        }
        send_keyboard_report();
      }
      break;

    case CC_DEL:
      if (is_cc_super_ctl) {
        if (record->event.pressed) {
          register_code16(KC_LCTL);
          register_code(KC_DEL);
        } else {
          unregister_code16(KC_LCTL);
          unregister_code(KC_DEL);
        }
      } else {
        if (record->event.pressed) {
          register_code(KC_BSPC);
        } else {
          unregister_code(KC_BSPC);
        }
      }
      break;

    default:
      if (is_cc_super_ctl) {
        if (record->event.pressed) {
          register_code16(KC_LCTL);
        } else {
          unregister_code16(KC_LCTL);
        }
      }
      break;
  }
  return true;
}

// void matrix_scan_user(void) {
//   if (is_cc_super_ctl) {
//     if (timer_elapsed(ctl_tap_timer) < 200) {
//       register_code16(KC_LCTL);
//       ctl_tap_active = true;
//     }
//   }
// }
