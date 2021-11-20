#include QMK_KEYBOARD_H
#include "action_layer.h"

#include "common.h"
#include "combos.h"
#include "layers.h"

extern keymap_config_t keymap_config;
userspace_config_t runtime_userspace_config;

__attribute__ ((weak))
bool process_record_keymap(uint16_t keycode, keyrecord_t *record) {
  return true;
}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  if (keycode < POWER_RANGE || (QK_MOD_TAP <= keycode && keycode <= QK_MOD_TAP_MAX)) {
    for (int powerKey = EAGER_RANGE; powerKey < DEAD_RANGE; powerKey++) {
      // Interrupt to completely change state TAP -> HOLD
      if (!interrupt_tap(powerKey, keycode, &record->event))
        return false;
    }

    for (int powerKey = DEAD_RANGE; powerKey < NEW_SAFE_RANGE; powerKey++) {
      if (!interrupt_dead_layer(powerKey, keycode, &record->event))
        return false;
    }
  }

  switch (keycode) {
    case QWERTY:
      if (record->event.pressed) {
        set_single_persistent_default_layer(_QWERTY);
      }
      return false;
      break;
    case COLEMAK:
      if (record->event.pressed) {
        //set_single_persistent_default_layer(_COLEMAK);
      }
      return false;
      break;
    case CLEFT:
      registerMods(record, MOD_LCTL);
      registerCode(record, KC_LEFT);
      return false;
    case CRGHT:
      registerMods(record, MOD_LCTL);
      registerCode(record, KC_RGHT);
      return false;
    case SWITCHLOW:
      if (record->event.pressed) { 
        layer_invert(_LOWFAKER);
      }
      return false;
    case ESECOLON:
      runtime_userspace_config.dead_semicolon = false;
      break;
    case EDECOLON:
      runtime_userspace_config.dead_semicolon = true;
      break;
    case POWER_RANGE ... FUNCTION: // FUNCTION is the last EAGER_RANGE key
      return process_key(keycode, &record->event);
    case DEAD_RANGE: // Currently, DEAD_RANGE only has one key
      for (int powerKey = EAGER_RANGE; powerKey < DEAD_RANGE; powerKey++) {
        // Interupt to change state TAP -> HOLD. Why? this is for dead-scolon (;) key
        if (!interrupt_tap(powerKey, keycode, &record->event)) {
          return false;
        }
      }

      return process_key(keycode, &record->event);
  }

  return process_record_keymap(keycode, record);
}

void matrix_init_user(void) {
  runtime_userspace_config.dead_semicolon = true;
}

__attribute__ ((weak))
void matrix_scan_keymap(void) {}

void matrix_scan_user(void) {
  for (int powerKey = EAGER_RANGE; powerKey < NEW_SAFE_RANGE; powerKey++) {
    interrupt_any_key(powerKey, INTERRUPT_HOLD);
    interrupt_any_key(powerKey, INTERRUPT_BREAK_TAPPING);
  }

  matrix_scan_keymap();
}


__attribute__ ((weak))
layer_state_t layer_state_set_keymap (layer_state_t state) {
  return state;
}

layer_state_t layer_state_set_user(layer_state_t state) {
  state = update_tri_layer_state(state, _FN, _DIGIT, _FNSFT);
  state = update_tri_layer_state(state, _FN, _LFLIP, _LSYMBL);
  state = update_tri_layer_state(state, _LOWER, _RAISE, _ADJUST);
  state = update_tri_layersToLayer_state(state, 2, (uint8_t[]){_LOWER, _RAISE}, _FN, _FNALT);

  return layer_state_set_keymap(state);
}



uint32_t update_tri_layersToLayer_state(uint32_t state, uint8_t ls1len, uint8_t *ls1, uint8_t l2, uint8_t l3) {
  bool isOnOthers[3] = {false, false, false};
  bool isOnL2 = isOnLayer(state, l2);

  for (int i = 0; i < ls1len; i++) {
    bool isOnL1I = isOnLayer(state, ls1[i]);
    for (int j = 0; j < ls1len; j++) {
      if (j != i)
        isOnOthers[j] |= isOnL1I;
    }
  }

  for (int i = 0; i < ls1len; i++) {
    if (!isOnOthers[i] || !isOnL2)
      state = update_tri_layer_state(state, ls1[i], l2, l3);
  }

  return state;
}

void registerCode(keyrecord_t *record, uint8_t kc) {
  registerCodeByEvent(&record->event, kc);
}

void registerCodeByEvent(keyevent_t *event, uint8_t kc) {
  if (event->pressed) {
    register_code(kc);
  } else {
    unregister_code(kc);
  }
}

void registerMods(keyrecord_t *record, uint8_t mods) {
  registerModsByEvent(record->event, mods);
}

void registerModsByEvent(keyevent_t event, uint8_t mods) {
  registerModsTruthly(event.pressed, mods);
}

void registerModsTruthly(bool registerred, uint8_t mods) {
  if (keymap_config.swap_lctl_lgui) {
    if ((mods & (MOD_LCTL | MOD_LGUI)) == (MOD_LCTL | MOD_LGUI)) {
      // If both of them appear then we don't need to swap
    } else if (mods & MOD_LCTL) {
      mods &= ~MOD_LCTL;
      mods |= MOD_LGUI;
    } else if (mods & MOD_LGUI) {
      mods &= ~MOD_LGUI;
      mods |= MOD_LCTL;
    }
  }

  if (registerred) {
    register_mods(mods);
  } else {
    unregister_mods(mods);
  }
}

bool isOnLayer(uint32_t state, uint8_t layer) {
  /*
  There is another ootb method
  #define IS_LAYER_ON(layer) (layer_state & (1UL << (layer)))
  but doesn't work. Guess static layer_state might be not recent.
  */
  layer_state_t layer_state = 1UL << layer;
  return (state & layer_state);
}
