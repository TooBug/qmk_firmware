#include "xtrm.h"

bool dg_ctrl_pressed = false;
bool dg_alt_pressed = false;
bool dg_gui_pressed = false;

// 底层布局
int active_layer = 0;

enum dg_custom_keycodes {
  DG_MCTL = SAFE_RANGE,
  DG_APPW,
  DG_IME,   // 切换输入法
  DG_LYT,   // 切换布局
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

  // Mac
  KEYMAP(
    KC_ESC,  KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,    KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_BSPC,
    KC_TAB,  KC_A,    KC_S,    KC_D,    KC_F,    KC_G,    KC_H,    KC_J,    KC_K,    KC_L,             KC_ENT,
    KC_LSFT,          KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    KC_N,    KC_M,    RSFT_T(KC_CAPS), KC_UP,   KC_LCTL,
    KC_LCTL, KC_LALT,          KC_LGUI,          KC_SPC,           MO(3),   MO(4),   KC_LEFT, KC_DOWN, KC_RGHT),

  // Win
  KEYMAP(
    KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,  KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
    KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,  KC_TRNS, KC_TRNS,          KC_TRNS,
    KC_TRNS,          KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,  KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
    KC_LCTL, KC_LGUI,          KC_LALT,          KC_TRNS,          KC_TRNS,  KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS),

  // Win-Mac
  KEYMAP(
    KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,  KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
    KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,  KC_TRNS, KC_TRNS,          KC_TRNS,
    KC_TRNS,          KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,  KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
    KC_LALT, KC_LGUI,          KC_LCTL,          KC_TRNS,          KC_TRNS,  KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS),

  KEYMAP(
    KC_GRV,  KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_BSLS,
    KC_CAPS, KC_INS,  KC_HOME, KC_PGUP, KC_MINS, KC_EQL,  KC_LBRC, KC_RBRC, KC_SCLN, KC_QUOT,          KC_TRNS,
    KC_TRNS,          KC_DEL,  KC_END,  KC_PGDN, KC_TRNS, KC_COMM, KC_DOT,  KC_SLSH, KC_TRNS, KC_TRNS, KC_TRNS,
    KC_TRNS, KC_TRNS,          KC_TRNS,          DG_IME,           KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS),

  KEYMAP(
    KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,  KC_F12,
    KC_TRNS, DG_MCTL, DG_APPW, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_BRID, KC_BRIU, KC_TRNS,          KC_TRNS,
    KC_TRNS,          KC_PSCR, KC_SLCK, KC_PAUS, KC_TRNS, KC_MUTE, KC_VOLD, KC_VOLU, KC_TRNS, KC_TRNS, KC_TRNS,
    KC_TRNS, KC_TRNS,          KC_TRNS,          DG_LYT,           KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, RESET)

};

const macro_t *action_get_macro(keyrecord_t *record, uint8_t id, uint8_t opt) {
  switch (id) {

  }
  return MACRO_NONE;
}

void matrix_init_user(void) {
}

void matrix_scan_user(void) {
}

void led_on(void){
  DDRD |= (1 << 1); PORTD &= ~(1 << 1);
}

void led_off(void){
  DDRD &= ~(1 << 1); PORTD &= ~(1 << 1);
}

void led_flash(void){
  led_on();
  _delay_ms(200);
  led_off();
  _delay_ms(100);
}


bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  switch (keycode) {
    case KC_LCTL:
      dg_ctrl_pressed = record->event.pressed;
      break;

    case KC_LALT:
      dg_alt_pressed = record->event.pressed;
      break;

    case KC_LGUI:
      dg_gui_pressed = record->event.pressed;
      break;

    case DG_MCTL:
      if (record->event.pressed) {
        register_code(KC_LCTL);
        register_code(KC_UP);
      } else {
        unregister_code(KC_UP);
        unregister_code(KC_LCTL);
      }
      break;

    case DG_APPW:
      if (record->event.pressed) {
        register_code(KC_LCTL);
        register_code(KC_DOWN);
      } else {
        unregister_code(KC_DOWN);
        unregister_code(KC_LCTL);
      }
      break;

    case DG_IME:
      if (record->event.pressed) {
        register_code(KC_LGUI);
        register_code(KC_SPC);
      } else {
        unregister_code(KC_LGUI);
        unregister_code(KC_SPC);
      }
      break;

    case DG_LYT:
      if (record->event.pressed) {
        layer_clear();
        active_layer = (active_layer + 1) % 3;
        for(int i=0; i<=active_layer;i++){
            layer_on(active_layer);
            led_flash();
        }
        /* if(active_layer == 0){
            SEND_STRING("Mac(Ctrl-Opt-Cmd)");
        }else if(active_layer == 1){
            SEND_STRING("Win(Ctrl-Win-Alt)");
        }else if(active_layer == 2){
            SEND_STRING("Win(Alt-Win-Ctrl)");
        } */
      }
      return false;
      break;
  }
  return true;
}


void led_set_user(uint8_t usb_led) {
  if (usb_led & (1 << USB_LED_CAPS_LOCK)) {
    led_on();
  } else {
    led_off();
  }
}

void encoder_update_user(uint8_t index, bool clockwise) {
  uint8_t layer = biton32(layer_state);

  switch (layer) {
    case 0:
      if (dg_ctrl_pressed) {
        tap_code(clockwise ? KC_RGHT : KC_LEFT);
        // if (clockwise) {
        //   tap_code(keymap_key_to_keycode(layer, (keypos_t) {.row = 3, .col = 11 }));
        // } else {
        //   tap_code(keymap_key_to_keycode(layer, (keypos_t) {.row = 3, .col = 9 }));
        // }
      } else if (dg_gui_pressed) {
        if (clockwise) {
          tap_code(KC_TAB);
        } else {
          register_code(KC_LSFT);
          tap_code(KC_TAB);
          unregister_code(KC_LSFT);
        }
      } else {
        tap_code(clockwise ? KC_PGDN : KC_PGUP);
      }
      break;
    case 3:
      tap_code(clockwise ? KC_VOLU : KC_VOLD);
      break;
    case 4:
      tap_code(clockwise ? KC_BRIU : KC_BRID);
      break;
  }
}
