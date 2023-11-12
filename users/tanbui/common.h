#include "config_common.h"

enum custom_keycodes {
  QWERTY = SAFE_RANGE,
  COLEMAK,
  CLEFT,
  CRGHT,
  ERRESET,  // Reset runtime userspace eeconfig
  ERWRITE,  // Write runtime userspace eeconfig
  ESECOLON, // Normal semicolon
  EDECOLON, // Dead-key semicolon
  INVERTLOW,// Toggle LOWFAKER layer
  INVERTRAI,// Toggle RAISE layer
  KEEPSFT,

  POWER_RANGE
};

enum power_keycodes {
  LOWER = POWER_RANGE,
  RAISE,
  COMMAND,

  EAGER_RANGE
};

enum eager_keycodes {
  LFLIP = EAGER_RANGE,
  SPLFLIP,
  SFTESC,
  RMOD1,
  MOD3,
  MOD3R,
  MOD4R,
  RSFTSLS,

  TAP_RANGE
};

enum tap_keycodes {
  OPTION = TAP_RANGE,
  FUNCTION,
  DEGIT,
  DEAD_RANGE
};

enum dead_keycodes {
  SCOLON = DEAD_RANGE,

  NEW_SAFE_RANGE  //use "NEW_SAFE_RANGE" for keymap specific codes
};

typedef union {
  uint32_t raw;
  struct {
      bool    dead_semicolon    :1;
  };
} userspace_config_t;

#define POWER_INDEX(x) (x - POWER_RANGE)
#define IS_STRAIGHT_POWER(x) (POWER_RANGE <= x && x < EAGER_RANGE)
#define IS_EAGER_POWER(x) (EAGER_RANGE <= x && x < TAP_RANGE)
#define IS_TAP_POWER(x) (TAP_RANGE <= x && x < DEAD_RANGE)
#define IS_DEAD_POWER(x) (DEAD_RANGE <= x && x < NEW_SAFE_RANGE)

uint32_t update_tri_layersToLayer_state(uint32_t state, uint8_t ls1len, uint8_t *ls1, uint8_t l2, uint8_t l3);

void registerCode(keyrecord_t *record, uint8_t kc);
void registerCodeByEvent(keyevent_t *event, uint8_t kc);
void registerMods(keyrecord_t *record, uint8_t mods);
void registerModsByEvent(keyevent_t event, uint8_t mods);
void registerModsTruthly(bool registerred, uint8_t mods);
bool isOnLayer(uint32_t state, uint8_t layer);