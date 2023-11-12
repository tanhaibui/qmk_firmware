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

/* MY NOTE
 * Make command:
 * $> make preonic/rev3:ta-hc:dfu-util
 * ## Press Adjust+`
 *  Options:
 *  Clean: :clean
 *  Build only: remove :dfu-util
 */

#include <stdio.h>
#include QMK_KEYBOARD_H
#include "muse.h"
#include "common.h"
#include "layers.h"
#include "layouts.h"
#include "shortwrites.h"

extern keymap_config_t keymap_config;

enum preonic_keycodes {
  BACKLIT = NEW_SAFE_RANGE,
  SHWLAYDEL,
  M_PT,
  M_LU,
  Test1
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

// Dynamic keys

enum {
  DYN_SP_C,
  DYN_SP_S
};


#define LAYOUT  LAYOUT_preonic_grid

/* CUSTOM KEYMAPS
   ========================================================================== */


// Tap dances
#define TD_F11 TD(TD_F1_F11)            // Tap for F1, twice for F11
#define TD_F12 TD(TD_F2_F12)            // Tap for F2, twice for F12

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

/* Qwerty
 * ,-------------------------------------------------------------------------------------------------.
 * |  ESC` |   1   |   2   |   3   |   4   |   5   |||   6   |   7   |   8   |   9   |   0   | SLDEL |
 * ,-------+-------+-------+-------+-------+--------+--------+-------+-------+-------+-------+-------,
 */
[_QWERTY] = LAYOUT_wrapper(
  KC_GESC, KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    SHWLAYDEL,
                    QWERTY_L1_______,                                     QWERTY_R1_______,
                    QWERTY_L2_______,                                     QWERTY_R2_______,
                    QWERTY_L3_______,                                     QWERTY_R3_______,
                    QWERTY_L4_______,                                     QWERTY_R4_______
),

[_GAME] = LAYOUT_wrapper(
  KC_GRV,  KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    SHWLAYDEL,
                    GAME_L1_________,                                     GAME_R1_________,
                    GAME_L2_________,                                     GAME_R2_________,
                    GAME_L3_________,                                     GAME_R3_________,
                    GAME_L4_________,                                     GAME_R4_________
),

// [_COLEMAK] = LAYOUT_wrapper(
//   KC_GESC, KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    SHWLAYDEL,
//                     COLEMAK_L1______,                                     COLEMAK_R1______,
//                     COLEMAK_L2______,                                     COLEMAK_R2______,
//                     COLEMAK_L3______,                                     COLEMAK_R3______,
//                     COLEMAK_L4______,                                     COLEMAK_R4______
// ),

[_DEADSCLN] = LAYOUT_wrapper(
  _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
                    DEADSCLN_L1_____,                                     DEADSCLN_R1_____,
                    DEADSCLN_L2_____,                                     DEADSCLN_R2_____,
                    DEADSCLN_L3_____,                                     DEADSCLN_R3_____,
                    DEADSCLN_L4_____,                                     DEADSCLN_R4_____
),

/* Lower
 * ,-------------------------------------------------------------------------------------------------.
 * |       |       |       |       |       |       |||       |       |       |       |       |       |
 * ,-------+-------+-------+-------+-------+--------+--------+-------+-------+-------+-------+-------,
 */
[_LOWER] = LAYOUT_wrapper(
  _______, KC_MSTP, KC_MPRV, KC_MNXT, KC_MPLY, _______, _______, _______, _______, _______, _______, _______,
                    LOWER_L1________,                                     LOWER_R1________,
                    LOWER_L2________,                                     LOWER_R2________,
                    LOWER_L3________,                                     LOWER_R3________,
                    LOWER_L4________,                                     LOWER_R4________
),

/* Raise
 * ,-------------------------------------------------------------------------------------------------.
 * |       |   !   |   @   |   #   |   $   |   %   |||   ^   |   &   |   *   |   (   |   )   |       |
 * ,-------+-------+-------+-------+-------+--------+--------+-------+-------+-------+-------+-------,
 */
[_RAISE] = LAYOUT_wrapper(
  _______, KC_EXLM, KC_AT,   KC_HASH, KC_DLR,  KC_PERC, KC_CIRC, KC_AMPR, KC_ASTR, KC_LPRN, KC_RPRN, _______,
                    RAISE_L1________,                                     RAISE_R1________,
                    RAISE_L2________,                                     RAISE_R2________,
                    RAISE_L3________,                                     RAISE_R3________,
                    RAISE_L4________,                                     RAISE_R4________
),

/* Adjust (Lower + Raise)
 * ,-------------------------------------------------------------------------------------------.
 * |Reset  |Debug |EEPRST |Aud on |AudOff|CGnorm|CGswap|Qwerty |Colemk |TermOn |TermOf |       |
 * ,-------+------+-------+-------+------+------+------+-------+-------+-------+-------+-------,
 */
[_ADJUST] = LAYOUT_wrapper(
  RESET,   DEBUG,   EEP_RST, AU_ON,   AU_OFF,  CG_NORM, CG_SWAP, QWERTY,  COLEMAK, TERM_ON, TERM_OFF, _______,
                    ADJUST_L1_______,                                     ADJUST_R1_______,
                    ADJUST_L2_______,                                     ADJUST_R2_______,
                    ADJUST_L3_______,                                     ADJUST_R3_______,
                    ADJUST_L4_______,                                     ADJUST_R4_______
),

/* Fn
 * ,-------------------------------------------------------------------------------------------------.
 * |       |   F1  |   F2  |   F3  |  F4   |  F5   |||  F6   |  F7   |  F8   |  F9   |  F10  |       |
 * ,-------+-------+-------+-------+-------+--------+--------+-------+-------+-------+-------+-------,
 */
[_FN] = LAYOUT_wrapper(
  _______, KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  _______,
                    FN_L1___________,                                     FN_R1___________,
                    FN_L2___________,                                     FN_R2___________,
                    FN_L3___________,                                     FN_R3___________,
                    FN_L4___________,                                     FN_R4___________
),

[_GAMF] = LAYOUT_wrapper(
  _______, KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  _______,
                    GAMF_L1_________,                                     GAMF_R1_________,
                    GAMF_L2_________,                                     GAMF_R2_________,
                    GAMF_L3_________,                                     GAMF_R3_________,
                    GAMF_L4_________,                                     GAMF_R4_________
),

/* LFLIP
 * ,-------------------------------------------------------------------------------------------------.
 * |  DEL  |   0   |   9   |   8   |   7   |   6   |||   5   |   4   |   3   |   2   |   1   |  ESC` |
 * ,-------+-------+-------+-------+-------+--------+--------+-------+-------+-------+-------+-------,
 */
[_LFLIP] = LAYOUT_wrapper(
  KC_DEL,  KC_0,    KC_9,    KC_8,    KC_7,    KC_6,    KC_5,    KC_4,    KC_3,    KC_2,    KC_1,    KC_GESC,
                    LFLIP_L1________,                                     LFLIP_R1________,
                    LFLIP_L2________,                                     LFLIP_R2________,
                    LFLIP_L3________,                                     LFLIP_R3________,
                    LFLIP_L4________,                                     LFLIP_R4________
),

[_CWIN] = LAYOUT_wrapper(
  _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
                    CWIN_L1_________,                                     CWIN_R1_________,
                    CWIN_L2_________,                                     CWIN_R2_________,
                    CWIN_L3_________,                                     CWIN_R3_________,
                    CWIN_L4_________,                                     CWIN_R4_________
),

[_RCWIN] = LAYOUT_wrapper(
  _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
                    RCWIN_L1________,                                     RCWIN_R1________,
                    RCWIN_L2________,                                     RCWIN_R2________,
                    RCWIN_L3________,                                     RCWIN_R3________,
                    RCWIN_L4________,                                     RCWIN_R4________
),

[_RFN] = LAYOUT_wrapper(
  _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
                    RFN_L1__________,                                     RFN_R1__________,
                    RFN_L2__________,                                     RFN_R2__________,
                    RFN_L3__________,                                     RFN_R3__________,
                    RFN_L4__________,                                     RFN_R4__________
),

/* Digit
 * ,-------------------------------------------------------------------------------------------------.
 * |       |       |       |       |       |       |||       |       |       |       |       |       |
 * ,-------+-------+-------+-------+-------+--------+--------+-------+-------+-------+-------+-------,
 */
[_DIGIT] = LAYOUT_wrapper(
  _______, KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  _______,
                    DIGIT_L1________,                                     DIGIT_R1________,
                    DIGIT_L2________,                                     DIGIT_R2________,
                    DIGIT_L3________,                                     DIGIT_R3________,
                    DIGIT_L4________,                                     DIGIT_R4________
),

[_FNALT] = LAYOUT_wrapper(
  _______, A(KC_F1),A(KC_F2),A(KC_F3),A(KC_F4),A(KC_F5),A(KC_F6),A(KC_F7),A(KC_F8),A(KC_F9),A(KC_F10), _______,
                    FN_ALT_L1_______,                                     FN_ALT_R1_______,
                    FN_ALT_L2_______,                                     FN_ALT_R2_______,
                    FN_ALT_L3_______,                                     FN_ALT_R3_______,
                    FN_ALT_L4_______,                                     FN_ALT_R4_______
),

[_FNSFT] = LAYOUT_wrapper(
  _______, S(KC_F1),S(KC_F2),S(KC_F3),S(KC_F4),S(KC_F5),S(KC_F6),S(KC_F7),S(KC_F8),S(KC_F9),S(KC_F10), _______,
                    FN_SFT_L1_______,                                     FN_SFT_R1_______,
                    FN_SFT_L2_______,                                     FN_SFT_R2_______,
                    FN_SFT_L3_______,                                     FN_SFT_R3_______,
                    FN_SFT_L4_______,                                     FN_SFT_R4_______
),

[_RAISEALT] = LAYOUT_wrapper(
  _______, A(KC_F1),A(KC_F2),A(KC_F3),A(KC_F4),A(KC_F5),A(KC_F6),A(KC_F7),A(KC_F8),A(KC_F9),A(KC_F10), _______,
                    RAISE_ALT_L1____,                                     RAISE_ALT_R1____,
                    RAISE_ALT_L2____,                                     RAISE_ALT_R2____,
                    RAISE_ALT_L3____,                                     RAISE_ALT_R3____,
                    RAISE_ALT_L4____,                                     RAISE_ALT_R4____
),

[_LMOUSE] = LAYOUT_wrapper(
  _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
                    LMOUSE_L1_______,                                     LMOUSE_R1_______,
                    LMOUSE_L2_______,                                     LMOUSE_R2_______,
                    LMOUSE_L3_______,                                     LMOUSE_R3_______,
                    LMOUSE_L4_______,                                     LMOUSE_R4_______
),

/* LSymbol
 * ,-------------------------------------------------------------------------------------------------.
 * |       |   !   |   @   |   #   |   $   |   %   |||   ^   |   &   |   *   |   (   |   )   |       |
 * ,-------+-------+-------+-------+-------+--------+--------+-------+-------+-------+-------+-------,
 */
[_LSYMBL] = LAYOUT_wrapper(
  _______, KC_EXLM, KC_AT,   KC_HASH, KC_DLR,  KC_PERC, KC_CIRC, KC_AMPR, KC_ASTR, KC_LPRN, KC_RPRN, _______,
                    LSYMBOL_L1______,                                     LSYMBOL_R1______,
                    LSYMBOL_L2______,                                     LSYMBOL_R2______,
                    LSYMBOL_L3______,                                     LSYMBOL_R3______,
                    LSYMBOL_L4______,                                     LSYMBOL_R4______
),

[_LOWFAKER] = LAYOUT_wrapper(
  _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
                    LOWFAKER_L1_____,                                     LOWFAKER_R1_____,
                    LOWFAKER_L2_____,                                     LOWFAKER_R2_____,
                    LOWFAKER_L3_____,                                     LOWFAKER_R3_____,
                    LOWFAKER_L4_____,                                     LOWFAKER_R4_____
),

[_RAIFAKER] = LAYOUT_wrapper(
  _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
                    RAIFAKER_L1_____,                                     RAIFAKER_R1_____,
                    RAIFAKER_L2_____,                                     RAIFAKER_R2_____,
                    RAIFAKER_L3_____,                                     RAIFAKER_R3_____,
                    RAIFAKER_L4_____,                                     RAIFAKER_R4_____
),

[_CP] = LAYOUT_wrapper(
  _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
                    CP_L1___________,                                     CP_R1___________,
                    CP_L2___________,                                     CP_R2___________,
                    CP_L3___________,                                     CP_R3___________,
                    CP_L4___________,                                     CP_R4___________
),


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


bool process_record_keymap(uint16_t keycode, keyrecord_t *record) {
  static bool shwlaydel_sft = false;
  char tmp[16];
  switch (keycode) {
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
        case SHWLAYDEL:
          sprintf(tmp, "layer: %08lu", layer_state);
          if (record->event.pressed) {
            if (keyboard_report->mods & MOD_BIT(KC_LSFT)) {
              SEND_STRING(tmp);
              shwlaydel_sft = true;
            }
            else
              register_code(KC_DEL);
          } else if (shwlaydel_sft){
            for (size_t i = 0; i < 15; i++) tap_code(KC_BSPACE);
            shwlaydel_sft = false;
          }
          else 
            unregister_code(KC_DEL);
          break;
        case M_PT:
          if (record->event.pressed)
          {
            // ABC123A.HD
            SEND_STRING(SS_TAP(X_F2) SS_TAP(X_RIGHT) SS_TAP(X_BSPACE) SS_TAP(X_BSPACE) SS_TAP(X_BSPACE) SS_TAP(X_BSPACE) " - pt");
          }
          return false;
          break;
        case M_LU:
          if (record->event.pressed)
          {
            SEND_STRING(SS_TAP(X_ESCAPE) ".\\lu.ps1 " SS_LCTRL("v"));
          }
          return false;
          break;
        case Test1:
          if (record->event.pressed)
          {
            #ifdef QMK_KEYS_PER_SCAN
            SEND_STRING("QMKKPS");
            #endif
          }
          return false;
          break;
      }
      
    return true;
};




/* Music configuration
  ===================================================================*/

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


void matrix_scan_keymap(void) {
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