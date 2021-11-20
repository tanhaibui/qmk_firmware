
/* Define layer names */
enum userspace_layers {
  _QWERTY,    // 0
  _GAME,
  _DEADSCLN,
  _LOWER,     // 8
  _RAISE,     // 16
  _ADJUST,    // 32   // +24  56 
  _FN,        // 128  
  _RFN,
  _GAMF,
  _DIGIT,
  _CP,
  //_COLEMAK,
  _LFLIP,
  _FNALT,
  _FNSFT,
  _CWIN,
  _RCWIN,
  _LMOUSE,    // 8192
  _LSYMBL,    // 16384
  _LOWFAKER
};

// Momentarily actives layer
#define MO_CP     MO(_CP)                  // Hold for CP
#define FN(kc)    (kc == 0 ? MO(_FN)       : LT(_FN, (kc)))          // Tap for (kc), hold for FN
#define GAMF(kc)  (kc == 0 ? MO(_GAMF)     : LT(_GAMF, (kc)))        // Tap for (kc), hold for GAMF
#define CW(kc)    (kc == 0 ? MO(_CWIN)     : LT(_CWIN, (kc)))        // Tap for (kc), hold for CWIN
#define RFN(kc)   (kc == 0 ? MO(_RFN)      : LT(_RFN, (kc)))         // Tap for (kc), hold for RFN
#define RAI(kc)   (kc == 0 ? RAISE         : LT(_RAISE, (kc)))       // Tap for (kc), hold for RAISE
#define LOW(kc)   (kc == 0 ? LOWER         : LT(_LOWER, (kc)))       // Tap for (kc), hold for LOWER
#define FNAL(kc)  (kc == 0 ? MO(_FNALT)    : LT(_FNALT, (kc)))       // Tap for (kc), hold for FNALT
#define DIG(kc)   (kc == 0 ? MO(_DIGIT)    : LT(_DIGIT, (kc)))       // Tap for (kc), hold for Digit
#define LFL(kc)   (kc == 0 ? MO(_LFLIP)    : LT(_LFLIP, (kc)))       // Tap for (kc), hold for Middle
#define LMOU(kc)  (kc == 0 ? MO(_LMOUSE)   : LT(_LMOUSE, (kc)))      // Tap for (kc), hold for LMouse
#define LGCW      LM(_CWIN,   MOD_LGUI)
#define LGRCW     LM(_RCWIN,  MOD_LGUI)