#pragma once
#include QMK_KEYBOARD_H

// Short writes
#define Sp      KC_SPC
#define Del     KC_DEL
#define Dot     KC_DOT
#define End     KC_END
#define Tab     KC_TAB
#define PgU     KC_PGUP
#define Grv     KC_GRAVE
#define Brk     KC_PAUSE
#define Eql     KC_EQUAL
#define Ent     KC_ENTER
#define Esc     KC_ESCAPE
#define Ins     KC_INSERT
#define Bsp     KC_BSPACE
#define PgD     KC_PGDOWN       
#define VolU    KC_VOLU
#define VolD    KC_VOLD
#define Home    KC_HOME
#define Down    KC_DOWN
#define Up      KC_UP
#define Left    KC_LEFT
#define Rght    KC_RIGHT
#define Cmma    KC_COMMA
#define Mins    KC_MINUS
#define Quot    KC_QUOTE
#define Slsh    KC_SLASH
#define Bsls    KC_BSLASH
#define Scln    KC_SCOLON
#define PDot    KC_KP_DOT
#define NLck    KC_NUMLOCK
#define PScr    KC_PSCREEN
#define PPls    KC_KP_PLUS
#define PSls    KC_KP_SLASH
#define PEnt    KC_KP_ENTER
#define PAst    KC_KP_ASTERISK
#define Appl    KC_APPLICATION
#define Capsl   KC_CAPSLOCK

// Key Combos
#define CTLSFT  LCTL(KC_LSFT)
#define CTLALT  LCTL(KC_LALT)
#define CTLGUI  LCTL(KC_LGUI)
#define CTLSALT LCTL(LSFT(KC_LALT))

// Fixes
#define KC_UNDO   LCTL(KC_Z)            // Undo = Ctrl-Z
#define KC_COPY   LCTL(KC_C)            // Copy = Ctrl-C
#define KC_FIND   LCTL(KC_F)            // Undo = Ctrl-F
#define KC_PASTE  LCTL(KC_V)            // Undo = Ctrl-V

// Modifier extensions
#define CG(kc)    (QK_LCTL | QK_LGUI | (kc))
// MT remark: Mod bit from 0x01 -> 0x08; (((mod)&0x1F) << 8) -> 0x1F00
#define MC(kc)    MT(MOD_LCTL, (kc))            // Tap for (kc), hold for Ĉ
#define MS(kc)    MT(MOD_LSFT, (kc))            // Tap for (kc), hold for ⇧
#define MA(kc)    MT(MOD_LALT, (kc))            // Tap for (kc), hold for Alt
#define MG(kc)    MT(MOD_LGUI, (kc))            // Tap for (kc), hold for Ĝ
#define MV(kc)    MT(MOD_RCTL, (kc))            // Tap for (kc), hold for RĈ
#define MR(kc)    MT(MOD_RSFT, (kc))            // Tap for (kc), hold for R⇧
#define MX(kc)    MT(MOD_LCTL|MOD_LSFT, (kc))   // Tap for (kc), hold for Ĉ⇧
#define MK(kc)    MT(MOD_LCTL|MOD_LALT, (kc))   // Tap for (kc), hold for ĈAlt
#define MW(kc)    MT(MOD_LCTL|MOD_LGUI, (kc))   // Tap for (kc), hold for ĈĜ
#define MZ(kc)    MT(MOD_LALT|MOD_LSFT, (kc))   // Tap for (kc), hold for Alt⇧