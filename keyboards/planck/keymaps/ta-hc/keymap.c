/**
 * Flashing:
 * Rev 5 or earlier:
 * make planck/revX:ta-hc:dfu
 * Rev 6:
 * make planck/rev6:ta-hc:dfu-util
 *
 * 
*/

#include <stdio.h>
#include QMK_KEYBOARD_H
#include "common.h"
#include "shortwrites.h"
#include "layers.h"
#include "layouts.h"

#define LAYOUT  LAYOUT_planck_grid

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
[_QWERTY] = LAYOUT_wrapper(
  QWERTY_L1_______,                                     QWERTY_R1_______,
  QWERTY_L2_______,                                     QWERTY_R2_______,
  QWERTY_L3_______,                                     QWERTY_R3_______,
  QWERTY_L4_______,                                     QWERTY_R4_______
),
[_GAME] = LAYOUT_wrapper(
  GAME_L1_________,                                     GAME_R1_________,
  GAME_L2_________,                                     GAME_R2_________,
  GAME_L3_________,                                     GAME_R3_________,
  GAME_L4_________,                                     GAME_R4_________
),
[_DEADSCLN] = LAYOUT_wrapper(
  DEADSCLN_L1_____,                                     DEADSCLN_R1_____,
  DEADSCLN_L2_____,                                     DEADSCLN_R2_____,
  DEADSCLN_L3_____,                                     DEADSCLN_R3_____,
  DEADSCLN_L4_____,                                     DEADSCLN_R4_____
),
[_LOWER] = LAYOUT_wrapper(
  LOWER_L1________,                                     LOWER_R1________,
  LOWER_L2________,                                     LOWER_R2________,
  LOWER_L3________,                                     LOWER_R3________,
  LOWER_L4________,                                     LOWER_R4________
),
[_RAISE] = LAYOUT_wrapper(
  RAISE_L1________,                                     RAISE_R1________,
  RAISE_L2________,                                     RAISE_R2________,
  RAISE_L3________,                                     RAISE_R3________,
  RAISE_L4________,                                     RAISE_R4________
),
[_ADJUST] = LAYOUT_wrapper(
  ADJUST_L1_______,                                     ADJUST_R1_______,
  ADJUST_L2_______,                                     ADJUST_R2_______,
  ADJUST_L3_______,                                     ADJUST_R3_______,
  ADJUST_L4_______,                                     ADJUST_R4_______
),
[_FN] = LAYOUT_wrapper(
  FN_L1___________,                                     FN_R1___________,
  FN_L2___________,                                     FN_R2___________,
  FN_L3___________,                                     FN_R3___________,
  FN_L4___________,                                     FN_R4___________
),
[_GAMF] = LAYOUT_wrapper(
  GAMF_L1_________,                                     GAMF_R1_________,
  GAMF_L2_________,                                     GAMF_R2_________,
  GAMF_L3_________,                                     GAMF_R3_________,
  GAMF_L4_________,                                     GAMF_R4_________
),
[_LFLIP] = LAYOUT_wrapper(
  LFLIP_L1________,                                     LFLIP_R1________,
  LFLIP_L2________,                                     LFLIP_R2________,
  LFLIP_L3________,                                     LFLIP_R3________,
  LFLIP_L4________,                                     LFLIP_R4________
),
[_CWIN] = LAYOUT_wrapper(
  CWIN_L1_________,                                     CWIN_R1_________,
  CWIN_L2_________,                                     CWIN_R2_________,
  CWIN_L3_________,                                     CWIN_R3_________,
  CWIN_L4_________,                                     CWIN_R4_________
),
[_RCWIN] = LAYOUT_wrapper(
  RCWIN_L1________,                                     RCWIN_R1________,
  RCWIN_L2________,                                     RCWIN_R2________,
  RCWIN_L3________,                                     RCWIN_R3________,
  RCWIN_L4________,                                     RCWIN_R4________
),
[_RFN] = LAYOUT_wrapper(
  RFN_L1__________,                                     RFN_R1__________,
  RFN_L2__________,                                     RFN_R2__________,
  RFN_L3__________,                                     RFN_R3__________,
  RFN_L4__________,                                     RFN_R4__________
),
[_DIGIT] = LAYOUT_wrapper(
  DIGIT_L1________,                                     DIGIT_R1________,
  DIGIT_L2________,                                     DIGIT_R2________,
  DIGIT_L3________,                                     DIGIT_R3________,
  DIGIT_L4________,                                     DIGIT_R4________
),
[_FNALT] = LAYOUT_wrapper(
  FN_ALT_L1_______,                                     FN_ALT_R1_______,
  FN_ALT_L2_______,                                     FN_ALT_R2_______,
  FN_ALT_L3_______,                                     FN_ALT_R3_______,
  FN_ALT_L4_______,                                     FN_ALT_R4_______
),
[_FNSFT] = LAYOUT_wrapper(
  FN_SFT_L1_______,                                     FN_SFT_R1_______,
  FN_SFT_L2_______,                                     FN_SFT_R2_______,
  FN_SFT_L3_______,                                     FN_SFT_R3_______,
  FN_SFT_L4_______,                                     FN_SFT_R4_______
),
[_LMOUSE] = LAYOUT_wrapper(
  LMOUSE_L1_______,                                     LMOUSE_R1_______,
  LMOUSE_L2_______,                                     LMOUSE_R2_______,
  LMOUSE_L3_______,                                     LMOUSE_R3_______,
  LMOUSE_L4_______,                                     LMOUSE_R4_______
),
[_LSYMBL] = LAYOUT_wrapper(
  LSYMBOL_L1______,                                     LSYMBOL_R1______,
  LSYMBOL_L2______,                                     LSYMBOL_R2______,
  LSYMBOL_L3______,                                     LSYMBOL_R3______,
  LSYMBOL_L4______,                                     LSYMBOL_R4______
),
[_LOWFAKER] = LAYOUT_wrapper(
  LOWFAKER_L1_____,                                     LOWFAKER_R1_____,
  LOWFAKER_L2_____,                                     LOWFAKER_R2_____,
  LOWFAKER_L3_____,                                     LOWFAKER_R3_____,
  LOWFAKER_L4_____,                                     LOWFAKER_R4_____
),
[_CP] = LAYOUT_wrapper(
  CP_L1___________,                                     CP_R1___________,
  CP_L2___________,                                     CP_R2___________,
  CP_L3___________,                                     CP_R3___________,
  CP_L4___________,                                     CP_R4___________
),
};
