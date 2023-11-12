#include QMK_KEYBOARD_H
#include "common.h"
#include "combos.h"
#include "layers.h"

extern userspace_config_t runtime_userspace_config;

static AnyKRecord all_keys[] = {
  [POWER_INDEX(LOWER)]    = { .state = ANYK_NONE },
  [POWER_INDEX(RAISE)]    = { .state = ANYK_NONE },
  [POWER_INDEX(COMMAND)]  = { .state = ANYK_NONE },
  [POWER_INDEX(LFLIP)]    = { .state = ANYK_NONE },
  [POWER_INDEX(SPLFLIP)]  = { .state = ANYK_NONE },
  [POWER_INDEX(SFTESC)]   = { .state = ANYK_NONE },
  [POWER_INDEX(RMOD1)]    = { .state = ANYK_NONE },
  [POWER_INDEX(MOD3)]     = { .state = ANYK_NONE },
  [POWER_INDEX(MOD3R)]    = { .state = ANYK_NONE },
  [POWER_INDEX(MOD4R)]    = { .state = ANYK_NONE },
  [POWER_INDEX(RSFTSLS)]  = { .state = ANYK_NONE },
  [POWER_INDEX(OPTION)]   = { .state = ANYK_NONE },
  [POWER_INDEX(FUNCTION)] = { .state = ANYK_NONE },
  [POWER_INDEX(SCOLON)]   = { .state = ANYK_NONE }
};

static AnyKOrch all_keys_orch[] = {
  [POWER_INDEX(LOWER)]    = {
    .key      = 0,
    .mods     = 0,
    .layer    = _LOWER,
    .process  = process_key_internal
  },
  [POWER_INDEX(RAISE)]    = {
    .key      = 0,
    .mods     = 0,
    .layer    = _RAISE,
    .process  = process_key_internal
  },
  [POWER_INDEX(COMMAND)]  = {
    .key      = 0,
    .mods     = MOD_LCTL,
    .layer    = 0,
    .process  = process_key_command
  },
  [POWER_INDEX(LFLIP)]    = {
    .key      = KC_ESC,
    .mods     = 0,
    .layer    = _LFLIP,
    .process  = process_key_internal,
  },
  [POWER_INDEX(SPLFLIP)]  = {
    .key      = KC_SPACE,
    .mods     = 0,
    .layer    = _LFLIP,
    .process  = process_key_internal,
  },
  [POWER_INDEX(SFTESC)]   = {
    .key      = KC_ESC,
    .mods     = MOD_BIT(KC_LSFT),
    .layer    = 0,
    .process  = process_key_internal
  },
  [POWER_INDEX(RMOD1)]    = {
    .key      = KC_DEL,
    .mods     = MOD_BIT(KC_LCTL)|MOD_BIT(KC_LALT),
    .layer    = 0,
    .process  = process_key_internal
  },
  [POWER_INDEX(MOD3)]     = {
    .key      = KC_APPLICATION,
    .mods     = MOD_BIT(KC_LSFT),
    .layer    = 0,
    .process  = process_key_internal
  },
  [POWER_INDEX(MOD3R)]    = {
    .key      = KC_TAB,
    .mods     = MOD_BIT(KC_LSFT),
    .layer    = 0,
    .process  = process_key_internal
  },
  [POWER_INDEX(MOD4R)]    = {
    .key      = KC_BSLS,
    .mods     = MOD_BIT(KC_RSFT),
    .layer    = 0,
    .process  = process_key_internal
  },
  [POWER_INDEX(RSFTSLS)]  = {
    .key      = KC_SLSH,
    .mods     = MOD_BIT(KC_RSFT),
    .layer    = 0,
    .process  = process_key_internal
  },
  [POWER_INDEX(OPTION)]   = {
    .key      = KC_TAB,
    .mods     = 0,
    .layer    = _LSYMBL,
    .process  = process_key_option
  },
  [POWER_INDEX(FUNCTION)] = {
    .key      = KC_BSPC,
    .mods     = 0,
    .layer    = _FN,
    .process  = process_key_internal
  },
  [POWER_INDEX(SCOLON)]   = {
    .key      = KC_SCOLON,
    .mods     = 0,
    .layer    = _DEADSCLN,
    .process  = process_key_scolon
  }
};

static ComboOrch all_combos_orch[] = {
  [0] = {
    .keycode1 = DEGIT,
    .keycode2 = COMMAND,
    .keycodeOn = 0,
    .keycode1FirstMods = 0,
    .keycode1FirstLayer = 0,
    .keycode2FirstMods = 0,
    .keycode2FirstLayer = 0
  }
};


ComboComotionState process_combo_comotion(uint16_t keycode, bool down, Payload *payload) {
  static ComboComotionState combo_comotion_state = COMOTION_NONE;
  
  AnyKTransition *transition = &payload->transition;

  switch (combo_comotion_state) {
    case COMOTION_NONE:
      if (keycode == COMMAND && down) {
        combo_comotion_state = COMOTION_COMMAND;
      }

    break;
    case COMOTION_COMMAND:
      switch (keycode) {
        case COMMAND:
          if (!down) {
            combo_comotion_state = COMOTION_NONE;
          }

        break;
        case OPTION:
          if (transition->from == ANYK_NONE && transition->to == ANYK_TAP) {
            combo_comotion_state = COMOTION_CTLOW;
            payload_add_action(payload, (Action){ .type = ACTION_LAYER, .code = _LOWFAKER, .state = CODE_DOWN });
          }

        break;
      }

    break;
    case COMOTION_OPTION_WAIT:
      if (keycode == OPTION) {
        combo_comotion_state = COMOTION_NONE;
      }

    break;
    case COMOTION_CTLOW:
      switch (keycode) {
        case COMMAND:
          if (!down) {
            combo_comotion_state = COMOTION_OPTION_WAIT;
            payload_add_action(payload, (Action){ .type = ACTION_LAYER, .code = _LOWFAKER, .state = CODE_UP });
          }

        break;
        case OPTION:
          if (transition->from == ANYK_TAP) {
            if (transition->to == ANYK_HOLD) {
            } else if (transition->to == ANYK_TAPPING_UP) {
              combo_comotion_state = COMOTION_COMMAND;
              payload_add_action(payload, (Action){ .type = ACTION_LAYER, .code = _LOWFAKER, .state = CODE_UP });
            }
          } else if (transition->from == ANYK_HOLD) {
            combo_comotion_state = COMOTION_COMMAND;
            payload_add_action(payload, (Action){ .type = ACTION_LAYER, .code = _LOWFAKER, .state = CODE_UP });
          } 

        break;
      }

    break;
  }

  return combo_comotion_state;
}

void process_combo_internal(uint16_t keycode, Payload *event) {
  for(uint8_t i = 0; i < 1; i++) {
    ComboOrch *orch = &all_combos_orch[i];
    if (keycode == orch->keycode1 || keycode == orch->keycode2) {
      orch->keycodeOn = keycode;
    }
  }
}

bool process_key(uint16_t keycode, keyevent_t *event) {
  uint16_t keycodeIndex = POWER_INDEX(keycode);
  AnyKOrch *orch = &all_keys_orch[keycodeIndex];
  return (*orch->process)(keycode, event, false, 0);
}

bool process_key_internal(uint16_t keycode, keyevent_t *event, bool interrupted, uint16_t interruptedKeycode) {
  Payload payload = IS_EAGER_POWER(keycode) ? process_eager_strategy(keycode, event, interrupted, interruptedKeycode) : IS_TAP_POWER(keycode) ? process_tap_strategy(keycode, event, interrupted) : process_any_key(keycode, event, interrupted);
  payload_execute(&payload);

  return interrupted;
}

bool process_key_internal_with_combo(uint16_t keycode, keyevent_t *event, bool interrupted, uint16_t interruptedKeycode) {
  Payload payload = IS_EAGER_POWER(keycode) ? process_eager_strategy(keycode, event, interrupted, interruptedKeycode) : IS_TAP_POWER(keycode) ? process_tap_strategy(keycode, event, interrupted) : process_any_key(keycode, event, interrupted);
  process_combo_internal(keycode, &payload);
  payload_execute(&payload);

  return interrupted;
}

bool process_key_command(uint16_t keycode, keyevent_t *event, bool interrupted, uint16_t interruptedKeycode) {
  Payload payload = process_any_key(keycode, event, false);
  if (payload.transition.from == ANYK_NONE) {
    process_combo_comotion(keycode, true, &payload);
  } else {
    process_combo_comotion(keycode, false, &payload);
  }

  payload_execute(&payload);

  return false;
}

bool process_key_option(uint16_t keycode, keyevent_t *event, bool interrupted, uint16_t interruptedKeycode) {
  Payload payload = process_tap_strategy(keycode, event, interrupted);
  AnyKTransition *transition = &payload.transition;
  if (transition->from == ANYK_NONE) {
    process_combo_comotion(keycode, true, &payload);
  } else if (transition->from == ANYK_TAP) {
    if (transition->to == ANYK_TAPPING_UP) {
      process_combo_comotion(keycode, false, &payload);
    }
  } else if (transition->from == ANYK_HOLD) {
    process_combo_comotion(keycode, false, &payload);
  }

  payload_execute(&payload);

  return interrupted;
}

bool process_key_scolon(uint16_t keycode, keyevent_t *event, bool interrupted, uint16_t interruptedKeycode) {
  if (runtime_userspace_config.dead_semicolon) {
    Payload payload = process_dead_strategy(keycode, event, interrupted, interruptedKeycode);
    payload_execute(&payload);
  } else {
    registerCodeByEvent(event, all_keys_orch[POWER_INDEX(keycode)].key);
  }

  return interrupted;
}

bool interrupt_any_key(uint16_t keycode, InterruptType interruptType) {
  uint16_t keycodeIndex = POWER_INDEX(keycode);
  AnyKRecord *record = &all_keys[keycodeIndex];
  AnyKOrch *orch = &all_keys_orch[keycodeIndex];

  if (record->state == ANYK_TAP) {
    bool tappingTermElapsed = (timer_elapsed(record->event.time) > TAPPING_TERM);
    switch (interruptType) {
      // case INTERRUPT_TAP:
      //   if (!tappingTermElapsed) return (*orch->process)(keycode, &record->event, true, 0);
      // break;
      case INTERRUPT_HOLD:
        if (tappingTermElapsed) return (*orch->process)(keycode, &record->event, true, 0);
      break;
      default:
      break;
    }
  } else if (record->state == ANYK_TAPPING_UP || record->state == ANYK_TAPPING_UP_ONCE) {
    int extraTime = record->state == ANYK_TAPPING_UP_ONCE ? 100 : 0;
    bool tappingTermElapsed = (timer_elapsed(record->event.time) > TAPPING_TERM + extraTime);
    switch (interruptType) {
      case INTERRUPT_BREAK_TAPPING:
        if (tappingTermElapsed) return (*orch->process)(keycode, &record->event, true, 0);
      break;
      default:
      break;
    }
  } else if (record->state == ANYK_TAPPING_DONE) {
    if (interruptType == INTERRUPT_BREAK_TAPPING) {
      return (*orch->process)(keycode, &record->event, true, 0);
    }
  }

  return true;
}

bool interrupt_tap(uint16_t keycode, uint16_t interruptedKeycode, keyevent_t *event) {
  uint16_t keycodeIndex = POWER_INDEX(keycode);
  AnyKRecord *record = &all_keys[keycodeIndex];
  AnyKOrch *orch = &all_keys_orch[keycodeIndex];

  if (record->state == ANYK_TAP) {
    return (*orch->process)(keycode, event, true, interruptedKeycode);
  }

  return true;
}

bool interrupt_dead_layer(uint16_t keycode, uint16_t interruptedKeycode, keyevent_t *event) {
  uint16_t keycodeIndex = POWER_INDEX(keycode);
  AnyKRecord *record = &all_keys[keycodeIndex];
  AnyKOrch *orch = &all_keys_orch[keycodeIndex];

  switch (record->state) {
    case ANYK_TAP:
    case ANYK_TAPPING_UP_ONCE:
      return (*orch->process)(keycode, event, true, interruptedKeycode);
    default:
    break;
  }

  return true;
}

void payload_add_action(Payload *payload, Action action) {
  payload->actions[payload->length++] = action;
}

void payload_insert_action(Payload *payload, Action action) {
  payload->length++;
  for(uint8_t i = payload->length - 1; i > 0; i--) {
    payload->actions[i] = payload->actions[i - 1];
  }

  payload->actions[0] = action;
}

void payload_execute(Payload *payload) {
  for(uint8_t i = 0; i < payload->length; i++) {
    Action *action = &payload->actions[i];
    switch (action->type) {
      case ACTION_LAYER:
        switch (action->state) {
          case CODE_UP:
            layer_off(action->code);
          break;
          case CODE_DOWN:
            layer_on(action->code);
          break;
          default:
          break;
        }

      break;
      case ACTION_MODS:
        switch (action->state) {
          case CODE_UP:
            registerModsTruthly(false, action->code);
          break;
          case CODE_DOWN:
            registerModsTruthly(true, action->code);
          break;
          default:
          break;
        }

      break;
      case ACTION_KEYCODE:
        switch (action->state) {
          case CODE_UP:
            unregister_code(action->code);
          break;
          case CODE_DOWN:
            register_code(action->code);
          break;
          case CODE_TAP:
            tap_code(action->code);
          break;
        }

      break;
    }
  }
}

// Corer puncs are non-shifted keys that also interrupt dead layer dead key
bool is_corner_puncs(uint16_t keycode) {
  uint16_t masked_keycode = keycode & QK_MODS_MAX;
  switch (masked_keycode)
  {
    case KC_MINS:
    case KC_EQL:
    case KC_BSLS:
    case KC_QUOT:
    case KC_GRV:
    case KC_COMM:
    case KC_DOT:
    case KC_SLSH:
    case KC_PPLS:
      return true;
    default:
      return false;
  }
}

Payload process_dead_strategy(uint16_t keycode, keyevent_t *event, bool interrupted, uint16_t interruptedKeycode) {
  AnyKRecord *key = &all_keys[POWER_INDEX(keycode)];
  AnyKOrch *orch = &all_keys_orch[POWER_INDEX(keycode)];

  Payload payload = {
    .transition = { .from = key->state },
    .length = 0
  };

  if (!interrupted) {
    key->event = *event;
    key->event.time = timer_read();
  }

  switch (key->state) {
    case ANYK_NONE:
      if (event->pressed) {
        if (get_mods()) {
          key->state = ANYK_TAPPING_DN;
          payload_add_action(&payload, (Action){ .type = ACTION_KEYCODE, .code = orch->key, .state = CODE_DOWN });
        } else {
          key->state = ANYK_TAP;
          payload_add_action(&payload, (Action){ .type = ACTION_LAYER, .code = orch->layer, .state = CODE_DOWN });
        }
      }
    break;
    case ANYK_TAP:
      if (interrupted) {
        if (interruptedKeycode == 0
         || IS_MOD(interruptedKeycode)
         || is_corner_puncs(interruptedKeycode)
         || interruptedKeycode == KC_SPACE
         || interruptedKeycode == KC_ENTER
         || interruptedKeycode == KC_TAB
         || interruptedKeycode == orch->key) {
          // Do not TAP the dead key
          key->state = ANYK_HOLD;
        } else if ((interruptedKeycode & QK_MODS_MAX) < QK_MODS) {
          if (event->pressed) {
            key->state = ANYK_HOLD;
            payload_add_action(&payload, (Action){ .type = ACTION_KEYCODE, .code = orch->key, .state = CODE_TAP });
          }
        } else if (interruptedKeycode <= QK_MODS_MAX) {
          // interruptedKeycode between (QK_MODS .. QK_MODS_MAX) means shifted keys (e.g. !@#$)
          key->state = ANYK_HOLD;
        }
      } else if (!event->pressed) {
        key->state = ANYK_TAPPING_UP_ONCE;
      }
    break;
    case ANYK_TAPPING_UP_ONCE:
      if (interrupted) {
        if (interruptedKeycode == 0) {
          key->state = ANYK_NONE;
          payload_add_action(&payload, (Action){ .type = ACTION_LAYER, .code = orch->layer, .state = CODE_UP });
          payload_add_action(&payload, (Action){ .type = ACTION_KEYCODE, .code = orch->key, .state = CODE_TAP });
        } else if (IS_MOD(interruptedKeycode)
         || is_corner_puncs(interruptedKeycode)
         || interruptedKeycode == orch->key) {
          key->state = ANYK_TAPPING_DONE;
        } else if ((interruptedKeycode & QK_MODS_MAX) < QK_MODS) {
          key->state = ANYK_TAPPING_DONE;
          payload_add_action(&payload, (Action){ .type = ACTION_KEYCODE, .code = orch->key, .state = CODE_TAP });
        } else if (interruptedKeycode <= QK_MODS_MAX) {
          key->state = ANYK_TAPPING_DONE;
        }
      } else {
        key->state = ANYK_TAPPING_DN;
        payload_add_action(&payload, (Action){ .type = ACTION_LAYER, .code = orch->layer, .state = CODE_UP });
        payload_add_action(&payload, (Action){ .type = ACTION_KEYCODE, .code = orch->key, .state = CODE_TAP });
        payload_add_action(&payload, (Action){ .type = ACTION_KEYCODE, .code = orch->key, .state = CODE_DOWN });
      }
    break;
    case ANYK_TAPPING_UP:
      if (interrupted) {
        key->state = ANYK_NONE;
      } else {
        key->state = ANYK_TAPPING_DN;
        payload_add_action(&payload, (Action){ .type = ACTION_KEYCODE, .code = orch->key, .state = CODE_DOWN });
      }

    break;
    case ANYK_TAPPING_DN:
      key->state = ANYK_TAPPING_UP;
      payload_add_action(&payload, (Action){ .type = ACTION_KEYCODE, .code = orch->key, .state = CODE_UP });
    break;
    case ANYK_TAPPING_DONE:
      if (interrupted) {
        key->state = ANYK_NONE;
        payload_add_action(&payload, (Action){ .type = ACTION_LAYER, .code = orch->layer, .state = CODE_UP });
      }

    break;
    case ANYK_HOLD:
      key->state = ANYK_NONE;
      payload_add_action(&payload, (Action){ .type = ACTION_LAYER, .code = orch->layer, .state = CODE_UP });
    break;
  }

  payload.transition.to = key->state;

  return payload;
}

void restate_payload_layer_or_mods(Payload *payload, AnyKOrch *orch, CodeState newState) {
  if (orch->layer) {
    payload_add_action(payload, (Action){ .type = ACTION_LAYER, .code = orch->layer, .state = newState });
  }

  if (orch->mods) {
    payload_add_action(payload, (Action){ .type = ACTION_MODS, .code = orch->mods, .state = newState });
  }
}

void restate_payload_key(Payload *payload, AnyKOrch *orch, CodeState newState) {
  if (orch->key) {
    payload_add_action(payload, (Action){ .type = ACTION_KEYCODE, .code = orch->key, .state = newState });
  }
}

Payload process_eager_strategy(uint16_t keycode, keyevent_t *event, bool interrupted, uint16_t interruptedKeycode) {
  AnyKRecord *key = &all_keys[POWER_INDEX(keycode)];
  AnyKOrch *orch = &all_keys_orch[POWER_INDEX(keycode)];
  
  Payload payload = {
    .transition = { .from = key->state },
    .length = 0
  };

  if (!interrupted) {
    key->event = *event;
    key->event.time = timer_read();
  }

  switch (key->state)
  {
    case ANYK_NONE:
      if (get_mods()) {
        key->state = ANYK_TAPPING_DN;
        restate_payload_key(&payload, orch, CODE_DOWN);
      } else {
        key->state = ANYK_TAP;
        restate_payload_layer_or_mods(&payload, orch, CODE_DOWN);
      }
    break;
    case ANYK_TAP:
      if (interrupted) {
        if (interruptedKeycode == 0) {
          // INTERRUPT_HOLD
          key->state = ANYK_HOLD;
        } else {
          // INTERRUPT_TAP
          if (event->pressed) {
            // Same behavior as INTERRUPT_HOLD
            key->state = ANYK_HOLD;
          } else {
            key->state = ANYK_TAPPING_DN;
            restate_payload_layer_or_mods(&payload, orch, CODE_UP);
            restate_payload_key(&payload, orch, CODE_DOWN);
          }
        }
      } else if (!event->pressed) {
        key->state = ANYK_TAPPING_UP;
        if (orch->key & QK_RSFT) {
          if (orch->mods & MOD_MASK_SHIFT) {
            restate_payload_key(&payload, orch, CODE_TAP);
            restate_payload_layer_or_mods(&payload, orch, CODE_UP);
          } else {
            restate_payload_layer_or_mods(&payload, orch, CODE_UP);
            payload_add_action(&payload, (Action){ .type = ACTION_MODS, .code = MOD_BIT(KC_LSFT), .state = CODE_DOWN });
            restate_payload_key(&payload, orch, CODE_TAP);
            payload_add_action(&payload, (Action){ .type = ACTION_MODS, .code = MOD_BIT(KC_LSFT), .state = CODE_UP });
          }
        } else {
          restate_payload_layer_or_mods(&payload, orch, CODE_UP);
          restate_payload_key(&payload, orch, CODE_TAP);
        }
      }
    break;
    case ANYK_TAPPING_UP:
      if (interrupted) {
        key->state = ANYK_NONE;
      } else {
        key->state = ANYK_TAPPING_DN;
        if (orch->key & QK_RSFT) {
          payload_add_action(&payload, (Action){ .type = ACTION_MODS, .code = MOD_BIT(KC_LSFT), .state = CODE_DOWN });
        }

        restate_payload_key(&payload, orch, CODE_DOWN);
      }

    break;
    case ANYK_TAPPING_DN:
      key->state = ANYK_TAPPING_UP;
      restate_payload_key(&payload, orch, CODE_UP);
      if (orch->key & QK_RSFT) {
        payload_add_action(&payload, (Action){ .type = ACTION_MODS, .code = MOD_BIT(KC_LSFT), .state = CODE_UP });
      }

    break;
    case ANYK_HOLD:
      if (!event->pressed) {
        key->state = ANYK_NONE;
        restate_payload_layer_or_mods(&payload, orch, CODE_UP);
      }

    break;
    default:
      break;
  }

  payload.transition.to = key->state;

  return payload;
}

Payload process_tap_strategy(uint16_t keycode, keyevent_t *event, bool interrupted) {
  AnyKRecord *key = &all_keys[POWER_INDEX(keycode)];
  AnyKOrch *orch = &all_keys_orch[POWER_INDEX(keycode)];

  Payload payload = {
    .transition = { .from = key->state },
    .length = 0
  };

  if (!interrupted) {
    key->event = *event;
    key->event.time = timer_read();
  }

  switch (key->state) {
    case ANYK_NONE:
      if (event->pressed) {
        key->state = ANYK_TAP;
      }

    break;
    case ANYK_TAP:
      if (interrupted) {
        key->state = ANYK_HOLD;
        restate_payload_layer_or_mods(&payload, orch, CODE_DOWN);
      } else if (!event->pressed) {
        key->state = ANYK_TAPPING_UP;
        restate_payload_key(&payload, orch, CODE_TAP);
      }

    break;
    case ANYK_TAPPING_UP:
      if (interrupted) {
        key->state = ANYK_NONE;
      } else {
        key->state = ANYK_TAPPING_DN;
        restate_payload_key(&payload, orch, CODE_DOWN);
      }

    break;
    case ANYK_TAPPING_DN:
      key->state = ANYK_TAPPING_UP;
      restate_payload_key(&payload, orch, CODE_UP);

    break;
    case ANYK_HOLD:
      if (!event->pressed) {
        key->state = ANYK_NONE;
        restate_payload_layer_or_mods(&payload, orch, CODE_UP);
      }

    break;
    default:
    break;
  }

  payload.transition.to = key->state;

  return payload;
}

Payload process_any_key(uint16_t keycode, keyevent_t *event, bool interrupted) {
  AnyKRecord *key = &all_keys[POWER_INDEX(keycode)];
  AnyKOrch *orch = &all_keys_orch[POWER_INDEX(keycode)];

  Payload payload = {
    .transition = { .from = key->state },
    .length = 0
  };

  if (!interrupted) {
    key->event = *event;
    key->event.time = timer_read();
  }

  switch (key->state) {
    case ANYK_NONE:
      if (event->pressed) {
        if (IS_STRAIGHT_POWER(keycode)) {
          key->state = ANYK_HOLD;
          if (orch->key) {
            payload_add_action(&payload, (Action){ .type = ACTION_KEYCODE, .code = orch->key, .state = CODE_DOWN });
          } else if (orch->mods) {
            payload_add_action(&payload, (Action){ .type = ACTION_MODS, .code = orch->mods, .state = CODE_DOWN });
          } else if (orch->layer) {
            payload_add_action(&payload, (Action){ .type = ACTION_LAYER, .code = orch->layer, .state = CODE_DOWN });
          }
        } else if (IS_TAP_POWER(keycode)) {
          key->state = ANYK_TAP;
        }
      }

    break;
    case ANYK_TAP:
      // in TAP, we only have STRAT-TAP
      if (interrupted) {
        key->state = ANYK_HOLD;
        if (IS_TAP_POWER(keycode)) {
          restate_payload_layer_or_mods(&payload, orch, CODE_DOWN);
        }
      } else if (!event->pressed) {
        key->state = ANYK_TAPPING_UP;
        restate_payload_key(&payload, orch, CODE_TAP);
      }

    break;
    case ANYK_TAPPING_UP:
      if (interrupted) {
        key->state = ANYK_NONE;
      } else {
        key->state = ANYK_TAPPING_DN;
        restate_payload_key(&payload, orch, CODE_DOWN);
      }

    break;
    case ANYK_TAPPING_DN:
      key->state = ANYK_TAPPING_UP;
      restate_payload_key(&payload, orch, CODE_UP);

    break;
    case ANYK_HOLD:
      if (!event->pressed) {
        key->state = ANYK_NONE;
        if (IS_STRAIGHT_POWER(keycode) && orch->key) {
          payload_add_action(&payload, (Action){ .type = ACTION_LAYER, .code = orch->key, .state = CODE_UP });
        }

        restate_payload_layer_or_mods(&payload, orch, CODE_UP);
      }

    break;
    default:
    break;
  }

  payload.transition.to = key->state;

  return payload;
}