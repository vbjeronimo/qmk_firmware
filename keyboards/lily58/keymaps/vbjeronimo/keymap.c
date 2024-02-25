#include QMK_KEYBOARD_H

#define LGUI_A LGUI_T(KC_A)
#define LALT_S LALT_T(KC_S)
#define LSFT_D LSFT_T(KC_D)
#define LCTL_F LCTL_T(KC_F)

#define RCTL_J RCTL_T(KC_J)
#define RSFT_K RSFT_T(KC_K)
#define RALT_L LALT_T(KC_L)
#define RGUI_SC RGUI_T(KC_SCLN)

enum layer_number {
  _MAIN = 0,
  _NUMS,
  _SYMBOLS,
  _NAV,
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

[_MAIN] = LAYOUT(
  XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,                    XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
  CW_TOGG, KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,                       KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_BSLS,
  KC_GRV,  LGUI_A,  LALT_S,  LSFT_D,  LCTL_F,  KC_G,                       KC_H,    RCTL_J,  RSFT_K,  RALT_L,  RGUI_SC, KC_QUOT,
  KC_RALT, KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    XXXXXXX,  XXXXXXX, KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH, KC_RALT,
                XXXXXXX, KC_ESC, KC_SPC, LT(_NUMS, KC_TAB),          LT(_SYMBOLS, KC_BSPC), LT(_NAV, KC_ENT), KC_DEL, XXXXXXX
),

[_NUMS] = LAYOUT(
  XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,                    XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
  XXXXXXX, KC_F11,  KC_F12,  KC_F13,  KC_F14,  KC_F15,                     XXXXXXX, KC_7,    KC_8,    KC_9,    XXXXXXX, XXXXXXX,
  XXXXXXX, KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,                     XXXXXXX, KC_4,    KC_5,    KC_6,    XXXXXXX, XXXXXXX,
  XXXXXXX, KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   XXXXXXX,  XXXXXXX, XXXXXXX, KC_1,    KC_2,    KC_3,    XXXXXXX, XXXXXXX,
                        _______, _______, _______, _______,           _______, KC_0,    KC_DOT, _______
),

[_SYMBOLS] = LAYOUT(
  XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,                     XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
  XXXXXXX, XXXXXXX ,KC_COLN, KC_EQL,  KC_RABK, XXXXXXX,                     XXXXXXX, KC_MINS, KC_PLUS, KC_LBRC, KC_RBRC, XXXXXXX,
  XXXXXXX, KC_EXLM, KC_AT,   KC_HASH, KC_DLR,  KC_PERC,                     KC_CIRC, KC_AMPR, KC_ASTR, KC_LPRN, KC_RPRN, XXXXXXX,
  XXXXXXX, XXXXXXX, KC_LABK, KC_MINS, KC_RABK, XXXXXXX, XXXXXXX,  XXXXXXX,  XXXXXXX, KC_UNDS, KC_UNDS, KC_LCBR, KC_RCBR, XXXXXXX,
                         _______, _______, _______, _______,          _______, _______, _______, _______
),

[_NAV] = LAYOUT(
  XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,                   XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
  XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,                   XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
  XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,                   XXXXXXX, KC_LEFT, KC_DOWN, KC_UP,   KC_RGHT, XXXXXXX,
  XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, QK_BOOT, XXXXXXX, XXXXXXX, KC_HOME, KC_PGDN, KC_PGUP, KC_END,  XXXXXXX,
                         _______, _______, _______, _______,         _______, _______, _______, _______
),

};

bool caps_word_press_user(uint16_t keycode) {
    switch (keycode) {
        // Keycodes that continue Caps Word, with shift applied.
        case KC_A ... KC_Z:
        case KC_MINS:
        case KC_SCLN:
            add_weak_mods(MOD_BIT(KC_LSFT));  // Apply shift to next key.
            return true;

        // Keycodes that continue Caps Word, without shifting.
        case KC_1 ... KC_0:
        case KC_BSPC:
        case KC_DEL:
        case KC_UNDS:
            return true;

        default:
            return false;  // Deactivate Caps Word.
    }
}

//SSD1306 OLED update loop, make sure to enable OLED_ENABLE=yes in rules.mk
#ifdef OLED_ENABLE

oled_rotation_t oled_init_user(oled_rotation_t rotation) {
  if (!is_keyboard_master())
    return OLED_ROTATION_180;  // flips the display 180 degrees if offhand
  return rotation;
}

const char *read_logo(void);

bool oled_task_user(void) {
  if (is_keyboard_master()) {
    oled_write(read_logo(), false);
  }
    return false;
}
#endif // OLED_ENABLE
