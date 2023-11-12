typedef enum {
  ANYK_NONE,
  ANYK_TAP,
  ANYK_HOLD,
  ANYK_TAPPING_UP_ONCE,
  //ANYK_TAPPING_DN_ONCE,
  ANYK_TAPPING_UP,
  ANYK_TAPPING_DN,
  ANYK_TAPPING_DONE
} AnyKState;

typedef enum {
  CODE_UP,
  CODE_DOWN,
  CODE_TAP
} CodeState;

typedef enum {
  ACTION_KEYCODE,
  ACTION_MODS,
  ACTION_LAYER
} ActionType;

typedef enum {
  RAISFT_NONE,
  RAISFT_SHIFT,
  RAISFT_RAISE,
  SHIFT_ALL
} ComboRaisftState;

typedef enum {
  COMOTION_NONE,
  COMOTION_COMMAND,
  COMOTION_OPTION_WAIT,
  COMOTION_CTLOW
} ComboComotionState;

typedef enum {
  INTERRUPT_HOLD,
  INTERRUPT_BREAK_TAPPING
} InterruptType;

typedef struct {
  AnyKState state;
  keyevent_t event;
} AnyKRecord;

typedef struct {
  AnyKState from;
  AnyKState to;
} AnyKTransition;

typedef struct {
  ActionType type;
  uint16_t code;
  CodeState state;
} Action;

typedef struct {
  AnyKTransition transition;
  Action actions[4];
  uint8_t length;
} Payload;

typedef struct {
  uint16_t key;
  uint8_t mods;
  uint8_t layer;
  bool (*process) (uint16_t keycode, keyevent_t *event, bool interrupted, uint16_t interruptedKeycode);
} AnyKOrch;

typedef struct {
  uint16_t keycode1;
  uint16_t keycode2;
  uint16_t keycodeOn;
  uint8_t keycode1FirstMods;
  uint8_t keycode1FirstLayer;
  uint8_t keycode2FirstMods;
  uint8_t keycode2FirstLayer;
} ComboOrch;

ComboComotionState process_combo_comotion(uint16_t keycode, bool down, Payload *payload);
void process_combo_internal(uint16_t keycode, Payload *event);

/**
 * process_record_user = [process_key()]
 * process_key = process_key_XXX()
 * process_key_XXX = process_any_key(); payload_execute()
*/
bool process_key(uint16_t keycode, keyevent_t *event);
bool process_key_internal(uint16_t keycode, keyevent_t *event, bool interrupted, uint16_t interruptedKeycode);
bool process_key_internal_with_combo(uint16_t keycode, keyevent_t *event, bool interrupted, uint16_t interruptedKeycode);
bool process_key_command(uint16_t keycode, keyevent_t *event, bool interrupted, uint16_t interruptedKeycode);
bool process_key_option(uint16_t keycode, keyevent_t *event, bool interrupted, uint16_t interruptedKeycode);
bool process_key_scolon(uint16_t keycode, keyevent_t *event, bool interrupted, uint16_t interruptedKeycode);
bool interrupt_any_key(uint16_t keycode, InterruptType interruptType);
bool interrupt_tap(uint16_t keycode, uint16_t interruptedKeycode, keyevent_t *event);
bool interrupt_dead_layer(uint16_t keycode, uint16_t interruptedKeycode, keyevent_t *event);

void payload_add_action(Payload *payload, Action action);
void payload_insert_action(Payload *payload, Action action);
void payload_execute(Payload *payload);
Payload process_dead_strategy(uint16_t keycode, keyevent_t *event, bool interrupted, uint16_t interruptedKeycode);
Payload process_eager_strategy(uint16_t keycode, keyevent_t *event, bool interrupted, uint16_t interruptedKeycode);
Payload process_tap_strategy(uint16_t keycode, keyevent_t *event, bool interrupted);
Payload process_any_key(uint16_t keycode, keyevent_t *event, bool interrupted);