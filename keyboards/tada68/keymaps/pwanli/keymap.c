#include "tada68.h"

// Used for SHIFT_ESC
#define MODS_CTRL_MASK (MOD_BIT(KC_LSHIFT)|MOD_BIT(KC_RSHIFT))

// Each layer gets a name for readability, which is then used in the keymap matrix below.
// The underscores don't mean anything - you can have a layer called STUFF or any other name.
// Layer names don't all need to be of the same length, obviously, and you can also skip them
// entirely and just use numbers.
#define _BL 0
#define _FL 1

// Macros
#define MACRO_ESC 0
#define M_ESC M(MACRO_ESC)

#define ______ KC_TRNS

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  /* Keymap _BL: (Base Layer) Default Layer
   * ,----------------------------------------------------------------.
   * |Esc | 1|  2|  3|  4|  5|  6|  7|  8|  9|  0|  -|  =|Backsp |~ ` |
   * |----------------------------------------------------------------|
   * |Tab  |  Q|  W|  E|  R|  T|  Y|  U|  I|  O|  P|  [|  ]|  \  |Del |
   * |----------------------------------------------------------------|
   * |CAPS   |  A|  S|  D|  F|  G|  H|  J|  K|  L|  ;|  '|Return |PgUp|
   * |----------------------------------------------------------------|
   * |Shift   |  Z|  X|  C|  V|  B|  N|  M|  ,|  .|  /|Shift | Up|PgDn|
   * |----------------------------------------------------------------|
   * |Ctrl|Win |Alt |        Space          |Alt| FN|Ctrl|Lef|Dow|Rig |
   * `----------------------------------------------------------------'
   */
[_BL] = KEYMAP_ANSI(
  M_ESC,   KC_1,   KC_2,   KC_3,   KC_4,   KC_5,   KC_6,   KC_7,  KC_8, KC_9,   KC_0,   KC_MINS, KC_EQL, KC_BSPC,KC_GRV, \
  KC_TAB,  KC_Q,   KC_W,   KC_E,   KC_R,   KC_T,   KC_Y,   KC_U,  KC_I, KC_O,   KC_P,   KC_LBRC, KC_RBRC,KC_BSLS,KC_DEL, \
  KC_LCTL, KC_A,   KC_S,   KC_D,   KC_F,   KC_G,   KC_H,   KC_J,  KC_K, KC_L,   KC_SCLN,KC_QUOT,         KC_ENT, KC_PGUP,\
  KC_LSFT,         KC_Z,   KC_X,   KC_C,   KC_V,   KC_B,   KC_N,  KC_M, KC_COMM,KC_DOT, KC_SLSH, KC_RSFT,KC_UP,  KC_PGDN,\
  KC_LCTL, KC_LGUI,KC_LALT,                KC_SPC,                      MO(_FL),KC_RGUI,KC_RCTRL,KC_LEFT,KC_DOWN,KC_RGHT),

  /* Keymap _FL: Function Layer
   * ,----------------------------------------------------------------.
   * |   | F1|F2 |F3 |F4 |F5 |F6 |F7 |F8 |F9 |F10|F11|F12|Del    |Ins |
   * |----------------------------------------------------------------|
   * |     |   |Up |   |   |   |   |   |   |   |   |   |   |     |    |
   * |----------------------------------------------------------------|
   * |      |<- |Dn | ->|   |   |   |   |   |   |   |   |        |Hme |
   * |----------------------------------------------------------------|
   * |        |Bl-|BL |BL+|   |   |   |   |VU-|VU+|MUT|      |   |End |
   * |----------------------------------------------------------------|
   * |    |    |    |                       |   |   |    |   |   |    |
   * `----------------------------------------------------------------'
   */
[_FL] = KEYMAP_ANSI(
  KC_GRV, KC_F1,  KC_F2,  KC_F3,  KC_F4,  KC_F5,  KC_F6,  KC_F7,  KC_F8,  KC_F9,  KC_F10, KC_F11, KC_F12, KC_DEL, ______, \
  ______,______,  KC_UP, ______, ______, ______, ______, ______, ______, ______,  KC_PSCR,KC_SLCK,KC_PAUS,______, KC_INS, \
  KC_CAPS,KC_LEFT,KC_DOWN,KC_RIGHT,______,______,______, ______,______,______,______,______,              ______,KC_HOME, \
  ______, BL_TOGG, BL_DEC,  BL_INC,______,______,______, ______,KC_VOLD,KC_VOLU,KC_MUTE,          ______, ______, KC_END, \
  ______,______,______,                   ______,                             ______,______,______,______,______, ______),
};

const macro_t *escape_tilde_macro(keyrecord_t *record)
{
  uint8_t shift_esc_shift_mask = get_mods() & MODS_CTRL_MASK;
  if (record->event.pressed)
  {
    if (shift_esc_shift_mask)
    {
      return MACRO(T(GRV), END);
    }
    else
    {
      return MACRO(T(ESC), END);
    }
  }
  return MACRO_NONE;
}

const macro_t *action_get_macro(keyrecord_t *record, uint8_t id, uint8_t opt)
{
  const macro_t *result = MACRO_NONE;
  switch (id)
  {
  case MACRO_ESC:
    result = escape_tilde_macro(record);
    break;
  }
  return result;
}
