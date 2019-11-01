/* Copyright 2015-2017 Jack Humbert
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#include QMK_KEYBOARD_H
#include "muse.h"

enum preonic_layers {
  _QWERTY,
  _COLEMAK,
  _LOWER,
  _RAISE,
  _ADJUST,
  _DIGIT,
  _LNAV,
  _CWIN,
  _CP
};

enum preonic_keycodes {
  QWERTY = SAFE_RANGE,
  COLEMAK,
  LOWER,
  RAISE,
  BACKLIT,
  M_PT,
  M_PT2,
  Test1,
  Test2
};


/* TAP DANCE
   ==========================================================================
   1. Define TD names here
   2. Register action in tap_dance_actions[]
   ========================================================================== */

enum {
  TD_F1_F11,
  TD_F2_F12
};


enum {
  DYN_SP_C,
  DYN_SP_S
};

enum typemode {
  TYPEMODE_NORM,
  TYPEMODE_FAST
};

typedef struct
{
  uint16_t df;
  uint16_t modes[2];
} dyn_key_t;



/* CUSTOM KEYMAPS
   ========================================================================== */

// Tap dances
#define TD_F11 TD(TD_F1_F11)           // Tap for F1, twice for F11
#define TD_F12 TD(TD_F2_F12)           // Tap for F2, twice for F12

// Momentarily actives layer
#define MO_DIG MO(_DIGIT)               // Hold for Digit
#define O_CWIN LT(_CWIN, KC_O)          // Tap for O, hold for CtrlWin
#define SCLN_RAI LT(_RAISE, KC_SCLN)    // Tap for ;, hold for Raise
#define M_RAI LT(_RAISE, KC_M)          // Tap for M, hold for Raise
#define SLSH_LNAV LT(_LNAV, KC_SLSH)    // Tap for /, hold for LeftNav

// Modifiers
#define SP_RCTL MT(MOD_RCTL, KC_SPC)    // Tap for space, hold for ctrl
#define SP_RSFT MT(MOD_RSFT, KC_SPC)    // Tap for space, hold for shift
#define QUOT_LCTL MT(MOD_LCTL, KC_QUOT) // Tap for quote, hold for ctrl
#define CAPS_LSFT MT(MOD_LSFT, KC_CAPS) // Tap for capsl, hold for shift

// Key Combos
#define CTLSFT LCTL(KC_LSFT)
#define CTLALT LCTL(KC_LALT)
#define CTLALTSFT LALT(LCTL(KC_LSFT))

// Fixes
#define KC_UNDO LCTL(KC_Z)              // Undo = lCtrl-Z

enum typemode mode = TYPEMODE_NORM; 

const dyn_key_t dks[] = {
  [DYN_SP_C] = {
    .df = SP_RCTL,
    .modes = {
      [TYPEMODE_NORM] = 0,
      [TYPEMODE_FAST] = KC_SPC
    }
  }
};

const size_t dks_count = sizeof(dks) / sizeof(dyn_key_t);

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

/* Qwerty
 * ,-------------------------------------------------------------------------------------------------.
 * |  Esc` |   1   |   2   |   3   |   4   |   5   |||   6   |   7   |   8   |   9   |   0   |  Del  |
 * |-------+-------+-------+-------+-------+--------+--------+-------+-------+-------+-------+-------|
 * |  Tab  |   Q   |   W   |   E   |   R   |   T   |||   Y   |   U   |   I   |   O   |   P   |   BS  |
 * |-------+-------+-------+-------+-------+-----------------+-------+-------+-------+-------+-------|
 * | Ctrl  |   A   |   S   |   D   |   F   |   G   |||   H   |   J   |   K   |   L   |   ;   |   "   |
 * |-------+-------+-------+-------+-------+--------|--------+-------+-------+-------+-------+-------|
 * | Shift |   Z   |   X   |   C   |   V   |   B   |||   N   |   M   |   ,   |   .   |   /   | Enter |
 * |-------+-------+-------+-------+-------+--------+--------+-------+-------+-------+-------+-------|
 * | Brite |  GUI  |  Alt  | LEFT  | Lower | SP/Ctl | SP/Sft | Raise |   ↑   |   ←   |   ↓   |   →   |
 * `-------------------------------------------------------------------------------------------------'
 */
[_QWERTY] = LAYOUT_preonic_grid( \
  KC_GESC,  KC_1,    KC_2,    KC_3,   KC_4,    KC_5,      KC_6,    KC_7,    KC_8,    KC_9,    KC_0,     KC_DEL,  \
  KC_TAB,   KC_Q,    KC_W,    KC_E,   KC_R,    KC_T,      KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,     KC_BSPC, \
  KC_LCTL,  KC_A,    KC_S,    KC_D,   KC_F,    KC_G,      KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN,  KC_QUOT, \
  KC_LSFT,  KC_Z,    KC_X,    KC_C,   KC_V,    KC_B,      KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH,  KC_ENT,  \
  BACKLIT,  KC_LGUI, KC_LALT, MO_DIG, LOWER,   SP_RSFT,   SP_RCTL, RAISE,   KC_UP  , KC_LEFT, KC_DOWN,  KC_RGHT  \
),

/* Colemak
 * ,-----------------------------------------------------------------------------------.
 * |   `  |   1  |   2  |   3  |   4  |   5  |   6  |   7  |   8  |   9  |   0  | Bksp |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * | Tab  |   Q  |   W  |   F  |   P  |   G  |   J  |   L  |   U  |   Y  |   ;  | Del  |
 * |------+------+------+------+------+-------------+------+------+------+------+------|
 * | Esc  |   A  |   R  |   S  |   T  |   D  |   H  |   N  |   E  |   I  |   O  |  "   |
 * |------+------+------+------+------+------|------+------+------+------+------+------|
 * | Shift|   Z  |   X  |   C  |   V  |   B  |   K  |   M  |   ,  |   .  |   /  |Enter |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * | Brite| Ctrl | Alt  | GUI  |Lower |    Space    |Raise | Left | Down |  Up  |Right |
 * `-----------------------------------------------------------------------------------'
 */
[_COLEMAK] = LAYOUT_preonic_grid( \
  KC_GRV,  KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_BSPC, \
  KC_TAB,  KC_Q,    KC_W,    KC_F,    KC_P,    KC_G,    KC_J,    KC_L,    KC_U,    KC_Y,    KC_SCLN, KC_DEL,  \
  KC_ESC,  KC_A,    KC_R,    KC_S,    KC_T,    KC_D,    KC_H,    KC_N,    KC_E,    KC_I,    KC_O,    KC_QUOT, \
  KC_LSFT, KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    KC_K,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH, KC_ENT,  \
  BACKLIT, KC_LCTL, KC_LALT, KC_LGUI, LOWER,   KC_SPC,  KC_SPC,  RAISE,   KC_LEFT, KC_DOWN, KC_UP,   KC_RGHT  \
),

/* Lower
 * ,-----------------------------------------------------------------------------------------------.
 * |  Del  |   0   |   9  |   8  |   7   |   6   |||       |       |       |       |       |       |
 * |-------+-------+------+------+-------+--------+--------+-------+-------+-------+-------+-------|
 * |  BS   |   P   | O/CW |   I  |   U   |   Y   |||   WU  |   MR  |   M↑  |   WL  |   WR  |       |
 * |-------+-------+------+------+-------+-----------------+-------+-------+-------+-------+-------|
 * | '/Ctl |;/Raise|   L  |   K  |   J   |   H   |||   WD  |   M←  |   M↓  |   M→  |       |       |
 * |-------+-------+------+------+-------+--------|--------+-------+-------+-------+-------+-------|
 * |       |//Digit|   .  |   ,  |M/Raise|   N   ||| Enter |   MM  |   BK  |   FW  |       |       |
 * |-------+-------+------+------+-------+--------+--------+-------+-------+-------+-------+-------|
 * |       |       |      |      |       |        |        |   ML  |       |       |       |       |
 * `-----------------------------------------------------------------------------------------------'
 */
[_LOWER] = LAYOUT_preonic_grid( \
  KC_DEL,    KC_0,     KC_9,    KC_8,    KC_7,     KC_6,     _______, _______, _______, _______, _______, _______, \
  KC_BSPC,   KC_P,     O_CWIN,  KC_I,    KC_U,     KC_Y,     KC_WH_U, KC_BTN2, KC_MS_U, KC_WH_L, KC_WH_R, _______, \
  QUOT_LCTL, SCLN_RAI, KC_L,    KC_K,    KC_J,     KC_H,     KC_WH_D, KC_MS_L, KC_MS_D, KC_MS_R, _______, _______, \
  _______,   SLSH_LNAV, KC_DOT,  KC_COMM, M_RAI,   KC_N,     KC_ENT,  KC_BTN3, KC_BTN4, KC_BTN5, _______, _______, \
  _______,   _______,  _______, _______, _______,  _______,  KC_BTN1, _______, _______, _______, _______, _______  \
),

/* Raise
 * ,-------------------------------------------------------------------------------------------------.
 * |       |F1/F11 |F2/F12 |  F3   |  F4   |  F5   |||  F6   |  F7   |  F8   |  F9   |  F10  |       |
 * |-------+-------+-------+-------+-------+--------+--------+-------+-------+-------+-------+-------|
 * |       |   _   |   {   |   }   |   +   |   '   ||| PgUp  | PgDn  |   ↑   |   (   |   )   |       |
 * |-------+-------+-------+-------+-------+-----------------+-------+-------+-------+-------+-------|
 * |       |   -   |   [   |   ]   |   =   |   "   ||| Home  |   ←   |   ↓   |   →   |   :   |   \   |
 * |-------+-------+-------+-------+-------+--------|--------+-------+-------+-------+-------+-------|
 * |CtlSft | Undo  |  Sft  |  Alt  |  Ins  |  Del  |||  End  |   -   |   <   |   >   |       |       |
 * |-------+-------+-------+-------+-------+--------+--------+-------+-------+-------+-------+-------|
 * |       |       |CtlAlt |       |       |        |        |       | Play  | Vol-  | Mute  | Vol+  |
 * `-------------------------------------------------------------------------------------------------'
 */
[_RAISE] = LAYOUT_preonic_grid( \
  _______, TD_F11,  TD_F12,  KC_F3,   KC_F4,   KC_F5,    KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  _______, \
  _______, KC_UNDS, KC_LCBR, KC_RCBR, KC_PLUS, KC_QUOT,  KC_PGUP, KC_PGDN, KC_UP,   KC_LPRN, KC_RPRN, _______, \
  _______, KC_MINS, KC_LBRC, KC_RBRC, KC_EQL,  KC_DQUO,  KC_HOME, KC_LEFT, KC_DOWN, KC_RGHT, KC_COLN, KC_BSLS, \
  CTLSFT,  KC_UNDO, KC_LSFT, KC_LALT, KC_INS,  KC_DEL,   KC_END,  KC_MINS, KC_LT,   KC_GT,   _______, _______, \
  _______, _______, CTLALT,  _______, _______, _______,  _______, _______, KC_MPLY, KC_VOLD, KC_MUTE, KC_VOLU  \
),

/* Adjust (Lower + Raise)
 * ,-----------------------------------------------------------------------------------.
 * |Reset |Debug |EEPRST|Aud on|AudOff|CGnorm|CGswap|Qwerty|Colemk|TermOn|TermOf|AGTogg|
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |   ~  |   !  |   @  |   #  |   $  |   %  |   ^  |   &  |   *  |   (  |   )  |      |
 * |------+------+------+------+------+-------------+------+------+------+------+------|
 * |   `  |   1  |   2  |   3  |   4  |   5  |   6  |   7  |   8  |   9  |   0  |   |  |
 * |------+------+------+------+------+------|------+------+------+------+------+------|
 * |Caps/S|      |      |      |      |      |      |      |   ,  |   .  |   ?  |      |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      |      |      |      |      |             |      |      |      |      |      |
 * `-----------------------------------------------------------------------------------'
 */
[_ADJUST] = LAYOUT_preonic_grid( \
  RESET,     DEBUG,   EEP_RST, AU_ON,   AU_OFF,  CG_NORM,  CG_SWAP, QWERTY,  COLEMAK, TERM_ON, TERM_OFF, AG_TOGG, \
  KC_GRV,    KC_EXLM, KC_AT,   KC_HASH, KC_DLR,  KC_PERC,  KC_CIRC, KC_AMPR, KC_ASTR, KC_LPRN, KC_RPRN,  _______, \
  KC_TILD,   KC_1,    KC_2,    KC_3,    KC_4,    KC_5,     KC_6,    KC_7,    KC_8,    KC_9,    KC_0,     KC_PIPE, \
  CAPS_LSFT, _______, _______, _______, _______, _______,  _______, _______, KC_COMM, KC_DOT,  KC_QUES,  _______, \
  _______,   _______, _______, _______, _______, _______,  _______, _______, _______, _______, _______,  _______  \
),

/* Digit
 * ,-------------------------------------------------------------------------------------------------.
 * |       |       |       |       |       |       |||       |       |       |       |       |       |
 * |-------+-------+-------+-------+-------+--------+--------+-------+-------+-------+-------+-------|
 * |       |   0   |   9   |   8   |   7   |   6   |||       |       |       |       |       |       |
 * |-------+-------+-------+-------+-------+--------+--------+-------+-------+-------+-------+-------|
 * |       |   1   |   2   |   3   |   4   |   5   |||       |       |       |       |       |       |
 * |-------+-------+-------+-------+-------+--------+--------+-------+-------+-------+-------+-------|
 * |       |       |       |       |       |       |||       |       |       |       |       |       |
 * |-------+-------+-------+-------+-------+--------+--------+-------+-------+-------+-------+-------|
 * |       |       |       |       |       |        |        |       |       |       |       |       |
 * `-------------------------------------------------------------------------------------------------'
 */
[_DIGIT] = LAYOUT_preonic_grid( \
  _______,   _______,   _______,   _______,   _______,   _______,    _______,   _______,   _______,   _______,   _______,   _______,  \
  _______,   KC_0,      KC_9,      KC_8,      KC_7,      KC_6,       _______,   _______,   _______,   _______,   _______,   _______,  \
  _______,   KC_1,      KC_2,      KC_3,      KC_4,      KC_5,       _______,   _______,   _______,   _______,   _______,   _______,  \
  _______,   _______,   _______,   _______,   _______,   _______,    _______,   _______,   _______,   _______,   _______,   _______,  \
  _______,   _______,   _______,   _______,   _______,   _______,    _______,   _______,   _______,   _______,   _______,   _______   \
),

/* LeftNav
 * ,-------------------------------------------------------------------------------------------------.
 * |       |       |       |       |       |       |||       |       |       |       |       |       |
 * |-------+-------+-------+-------+-------+--------+--------+-------+-------+-------+-------+-------|
 * |       |       |       |   ↑   |  PgDn | PgUp  |||       |       |       |       |       |       |
 * |-------+-------+-------+-------+-------+-----------------+-------+-------+-------+-------+-------|
 * |       |       |   ←   |   ↓   |   →   | Home  |||       |       |       |       |       |       |
 * |-------+-------+-------+-------+-------+--------|--------+-------+-------+-------+-------+-------|
 * |       |       |       |       |       | End   |||       |       |       |       |       |       |
 * |-------+-------+-------+-------+-------+--------+--------+-------+-------+-------+-------+-------|
 * |       |       |       |       |       |        |        |       |       |       |       |       |
 * `-------------------------------------------------------------------------------------------------'
 */
[_LNAV] = LAYOUT_preonic_grid( \
  _______, _______, _______, _______, _______, _______,  _______, _______, _______, _______, _______, _______, \
  _______, _______, _______, KC_UP,   KC_PGDN, KC_PGUP,  _______, _______, _______, _______, _______, _______, \
  _______, _______, KC_LEFT, KC_DOWN, KC_RGHT, KC_HOME,  _______, _______, _______, _______, _______, _______, \
  _______, _______, _______, _______, _______, KC_END,   _______, _______, _______, _______, _______, _______, \
  _______, _______, _______, _______, _______, _______,  _______, _______, _______, _______, _______, _______  \
),

/* CtrlWin
 * ,-------------------------------------------------------------------------------------------------.
 * |       |       |       |       |       |       |||       |       |       |       |       |       |
 * |-------+-------+-------+-------+-------+--------+--------+-------+-------+-------+-------+-------|
 * |WinTab |       |       |DskLeft|DskRght|DskNew |||DskDel |       |       |       |       |       |
 * |-------+-------+-------+-------+-------+--------+--------+-------+-------+-------+-------+-------|
 * |       |       |       |       |       |       |||       |       |       |       |       |       |
 * |-------+-------+-------+-------+-------+--------+--------+-------+-------+-------+-------+-------|
 * |       |       |       |       |       |       |||       |       |       |       |       |       |
 * |-------+-------+-------+-------+-------+--------+--------+-------+-------+-------+-------+-------|
 * |       |       |       |       |       |        |        |       |       |       |       |       |
 * `-------------------------------------------------------------------------------------------------'
 */
[_CWIN] = LAYOUT_preonic_grid( \
  _______,   _______, _______, _______,       _______,       _______,       _______,     _______,   _______,   _______,   _______,   _______,  \
  G(KC_TAB), _______, _______, C(G(KC_LEFT)), C(G(KC_RGHT)), C(G(KC_D)),    C(G(KC_F4)), _______,   _______,   _______,   _______,   _______,  \
  _______,   _______, _______, M_PT,          M_PT2,         Test1,         Test2,       _______,   _______,   _______,   _______,   _______,  \
  _______,   _______, _______, _______,       _______,       _______,       _______,     _______,   _______,   _______,   _______,   _______,  \
  _______,   _______, _______, _______,       _______,       _______,       _______,     _______,   _______,   _______,   _______,   _______   \
)

/* BLANK
 * ,-------------------------------------------------------------------------------------------------.
 * |       |       |       |       |       |       |||       |       |       |       |       |       |
 * |-------+-------+-------+-------+-------+--------+--------+-------+-------+-------+-------+-------|
 * |       |       |       |       |       |       |||       |       |       |       |       |       |
 * |-------+-------+-------+-------+-------+--------+--------+-------+-------+-------+-------+-------|
 * |       |       |       |       |       |       |||       |       |       |       |       |       |
 * |-------+-------+-------+-------+-------+--------+--------+-------+-------+-------+-------+-------|
 * |       |       |       |       |       |       |||       |       |       |       |       |       |
 * |-------+-------+-------+-------+-------+--------+--------+-------+-------+-------+-------+-------|
 * |       |       |       |       |       |        |        |       |       |       |       |       |
 * `-------------------------------------------------------------------------------------------------'
 */
/* 
[L_BLANK] = LAYOUT_preonic_grid( \
  _______,   _______,   _______,   _______,   _______,   _______,    _______,   _______,   _______,   _______,   _______,   _______,  \
  _______,   _______,   _______,   _______,   _______,   _______,    _______,   _______,   _______,   _______,   _______,   _______,  \
  _______,   _______,   _______,   _______,   _______,   _______,    _______,   _______,   _______,   _______,   _______,   _______,  \
  _______,   _______,   _______,   _______,   _______,   _______,    _______,   _______,   _______,   _______,   _______,   _______,  \
  _______,   _______,   _______,   _______,   _______,   _______,    _______,   _______,   _______,   _______,   _______,   _______   \
),
*/
};

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  switch (keycode) {
        case QWERTY:
          if (record->event.pressed) {
            set_single_persistent_default_layer(_QWERTY);
          }
          return false;
          break;
        case COLEMAK:
          if (record->event.pressed) {
            set_single_persistent_default_layer(_COLEMAK);
          }
          return false;
          break;
        case LOWER:
          if (record->event.pressed) {
            layer_on(_LOWER);
            update_tri_layer(_LOWER, _RAISE, _ADJUST);
          } else {
            layer_off(_LOWER);
            update_tri_layer(_LOWER, _RAISE, _ADJUST);
          }
          return false;
          break;
        case RAISE:
          if (record->event.pressed) {
            layer_on(_RAISE);
            update_tri_layer(_LOWER, _RAISE, _ADJUST);
          } else {
            layer_off(_RAISE);
            update_tri_layer(_LOWER, _RAISE, _ADJUST);
          }
          return false;
          break;
        case BACKLIT:
          if (record->event.pressed) {
            register_code(KC_RSFT);
            #ifdef BACKLIGHT_ENABLE
              backlight_step();
            #endif
            #ifdef __AVR__
            writePinLow(E6);
            #endif
          } else {
            unregister_code(KC_RSFT);
            #ifdef __AVR__
            writePinHigh(E6);
            #endif
          }
          return false;
          break;
        case M_PT:
          if (record->event.pressed)
          {
            SEND_STRING(" - pt");
          }
          return false;
          break;
        case M_PT2:
          if (record->event.pressed)
          {
            // ABC123A.HD
            SEND_STRING(SS_TAP(X_F2) SS_TAP(X_RIGHT) SS_TAP(X_BSPACE) SS_TAP(X_BSPACE) SS_TAP(X_BSPACE) SS_TAP(X_BSPACE) " - pt");
          }
          return false;
          break;
        case Test1:
          if (record->event.pressed)
          {
            mode = TYPEMODE_NORM;
          }
          return false;
          break;
        case Test2:
          if (record->event.pressed)
          {
            mode = TYPEMODE_FAST;
          }
          return false;
          break;
      }

      for (size_t i = 0; i < dks_count; i++)
      {
        if (keycode == dks[i].df)
        {
          //xprintf("dks[DYN_SP_C].df: kc: %u, col: %u, row: %u\n", keycode, record->event.key.col, record->event.key.row);
          //xprintf("typemode: %u\n", mode);
          uint16_t keyval = dks[i].modes[mode];

          if (keyval == 0) { return true; }

          if (record->event.pressed)
          {
            register_code16(keyval);
          }
          else
          {
            unregister_code16(keyval);
          }
          
          return false;
        }
      }
      
    return true;
};

bool muse_mode = false;
uint8_t last_muse_note = 0;
uint16_t muse_counter = 0;
uint8_t muse_offset = 70;
uint16_t muse_tempo = 50;

void encoder_update_user(uint8_t index, bool clockwise) {
  if (muse_mode) {
    if (IS_LAYER_ON(_RAISE)) {
      if (clockwise) {
        muse_offset++;
      } else {
        muse_offset--;
      }
    } else {
      if (clockwise) {
        muse_tempo+=1;
      } else {
        muse_tempo-=1;
      }
    }
  } else {
    if (clockwise) {
      register_code(KC_PGDN);
      unregister_code(KC_PGDN);
    } else {
      register_code(KC_PGUP);
      unregister_code(KC_PGUP);
    }
  }
}

void dip_switch_update_user(uint8_t index, bool active) {
    switch (index) {
        case 0:
            if (active) {
                layer_on(_ADJUST);
            } else {
                layer_off(_ADJUST);
            }
            break;
        case 1:
            if (active) {
                muse_mode = true;
            } else {
                muse_mode = false;
            }
    }
}


void matrix_scan_user(void) {
#ifdef AUDIO_ENABLE
    if (muse_mode) {
        if (muse_counter == 0) {
            uint8_t muse_note = muse_offset + SCALE[muse_clock_pulse()];
            if (muse_note != last_muse_note) {
                stop_note(compute_freq_for_midi_note(last_muse_note));
                play_note(compute_freq_for_midi_note(muse_note), 0xF);
                last_muse_note = muse_note;
            }
        }
        muse_counter = (muse_counter + 1) % muse_tempo;
    } else {
        if (muse_counter) {
            stop_all_notes();
            muse_counter = 0;
        }
    }
#endif
}

bool music_mask_user(uint16_t keycode) {
  switch (keycode) {
    case RAISE:
    case LOWER:
      return false;
    default:
      return true;
  }
}



/* Tap Dance Definitions
   ========================================================================== */

qk_tap_dance_action_t tap_dance_actions[] = {
  // Tap for F11, twice for F12
  [TD_F1_F11] = ACTION_TAP_DANCE_DOUBLE(KC_F1, KC_F11),
  [TD_F2_F12] = ACTION_TAP_DANCE_DOUBLE(KC_F2, KC_F12)
};