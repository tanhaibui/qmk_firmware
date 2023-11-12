/* MY NOTE
 * Make command:
 * $> make bm16s:tahc16:dfu
 * ## Press 4x4 -> 4x1 -> 1x1
 */

#include QMK_KEYBOARD_H
#include "../../../shortwrites.h"

enum layers {
	_NPAD,
	_LNAV,
	_RNAV,
	_EMEDIA,
	_LNAVE,
	_HHKB,
	_LALF,
	_FN,
	_NPAD2,
	_CP1,
	_CP2
};


#define LAYOUT_ortho_4x4_East( \
	K00, K01, K02, K03, \
	K10, K11, K12, K13, \
	K20, K21, K22, K23, \
	K30, K31, K32, K33  \
) { \
	{ K03,   K13,   K23,   K33 }, \
	{ K02,   K12,   K22,   K32 }, \
	{ K01,   K11,   K21,   K31 }, \
	{ K00,   K10,   K20,   K30 }  \
}

#define CP(kc)	(kc == 0 ? MO(_CP1)   : LT(_CP1, (kc)))
#define CPP(kc) (kc == 0 ? MO(_CP2)   : LT(_CP2, (kc)))
#define FN(kc)	(kc == 0 ? MO(_FN)	  : LT(_FN, (kc)))
#define NPP(kc) (kc == 0 ? MO(_NPAD2) : LT(_NPAD2, (kc)))
#define mLNAVE	MO(_LNAVE)
#define dNPAD	DF(_NPAD)
#define dLNAV	DF(_LNAV)
#define dRNAV	DF(_RNAV)
#define dEMEDIA DF(_EMEDIA)

// Layer modifiers
#define LMA_HHK LM(_HHKB, MOD_LALT)   // Hold for HHKB with alt mod
#define LMC_LAF LM(_LALF, MOD_LCTL)   // Hold for LALF with ctl mod


const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
	[_NPAD] = LAYOUT_ortho_4x4(
		KC_KP_7,    KC_KP_8, KC_KP_9,  KC_BSPC,
		KC_KP_4,    KC_KP_5, KC_KP_6,  KC_KP_0,
		KC_KP_1,    KC_KP_2, KC_KP_3,  KC_PSLS,
		NPP(PPls),  KC_PDOT, KC_PCMM,  CP(PEnt)
	),
	[_LNAV] = LAYOUT_ortho_4x4(
		LMA_HHK,  KC_PGUP, KC_UP,    KC_PGDN,
		MC(Esc),  KC_LEFT, KC_DOWN,  KC_RGHT,
		LMC_LAF,  mLNAVE,  XXXXXXX,  KC_SPC,
		CP(PEnt), FN(0),    MG(Appl), KC_LSFT 
	),
	[_RNAV] = LAYOUT_ortho_4x4(
		KC_PGUP, KC_UP,   KC_PGDN,  LMA_HHK,  
		KC_LEFT, KC_DOWN, KC_RGHT,  MC(Esc),  
		LMC_LAF, XXXXXXX, XXXXXXX,  XXXXXXX,  
		MS(Sp),  FN(0),    MG(Appl), CP(PEnt)
	),
	[_EMEDIA] = LAYOUT_ortho_4x4_East(
		CP(PgU),  KC_PGDN, KC_UP,    KC_LALT,
		KC_LEFT,  KC_RGHT, KC_DOWN,  KC_LCTL,
		KC_F1,    KC_F2,   KC_ESC,   _______,
		KC_SPC,   KC_LSFT, _______,  KC_ENT 
	),
	[_LNAVE] = LAYOUT_ortho_4x4(
		_______,  _______, _______,  KC_BSPC,
		_______,  _______, KC_HOME,  KC_END,
		KC_DEL,   XXXXXXX, CG(Left), CG(Rght),
		KC_LSFT,  _______, _______,  KC_LCTL 
	),
	[_HHKB] = LAYOUT_ortho_4x4(
		_______,  KC_UP,   MS(PgU),  KC_PGDN,
		KC_TAB,   KC_LEFT, KC_RGHT,  KC_TAB,
		KC_HOME,  KC_ESC,  KC_DOWN,  KC_END,
		_______,  _______, _______,  _______ 
	),
	[_LALF] = LAYOUT_ortho_4x4(
		_______,  KC_W, KC_E,     KC_R,
		_______,  KC_S, KC_D,     KC_F,
		XXXXXXX,  KC_X, KC_C,     KC_V,
		_______,  KC_Z, KC_LSFT,  _______ 
	),
	[_FN] = LAYOUT_ortho_4x4(
		KC_F8,  KC_F9,   KC_F12,  KC_F7,
		KC_F5,  KC_F6,   KC_F11,  KC_F4,
		KC_F2,  KC_F3,   KC_F10,  KC_F1,
		KC_F1,  XXXXXXX, _______, KC_F2 
	),
	[_NPAD2] = LAYOUT_ortho_4x4(
		KC_PGUP,  KC_UP,   KC_PGDN,  _______,
		KC_LEFT,  KC_DOWN, KC_RGHT,  KC_PAST,
		_______,  _______, _______,  KC_PCMM,
		XXXXXXX,  _______, _______,  _______ 
	),
	[_CP1] = LAYOUT_ortho_4x4(
		dLNAV,    XXXXXXX, dNPAD,    dRNAV,
		BL_TOGG,  XXXXXXX, dEMEDIA,  KC_VOLD,
		RGB_TOG,  RGB_MOD, KC_MPLY,  KC_MUTE,
		CPP(0),   XXXXXXX, XXXXXXX,  CPP(0) 
	),
	[_CP2] = LAYOUT_ortho_4x4(
		RESET,    BL_STEP, _______,  RGB_SAI,
		BL_TOGG,  BL_DEC,  BL_INC,   RGB_SAD,
		RGB_TOG,  RGB_MOD, RGB_HUI,  RGB_HUD,
		XXXXXXX,  XXXXXXX, XXXXXXX,  XXXXXXX 
	),
	/*[BLANK] = LAYOUT_ortho_4x4(
		_______,  _______, _______,  _______,
		_______,  _______, _______,  _______,
		_______,  _______, _______,  _______,
		_______,  _______, _______,  _______ 
	),
	*/
};

