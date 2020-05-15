#include "drivers/touch_key_driver.h"

/* Delays (in key scan cycles) */
#define LP_EVENT_DELAY 40
#define REP_EVENT_DELAY 20
#define REP_DELAY 4

struct TouchKeysState gs_tk_keys_state = {
		{TK_AF_LPRESS, TK_AF_REPEAT, TK_AF_LPRESS, TK_AF_REPEAT, TK_AF_LPRESS},
		ALT_DELAY, 0, 0
};

/* Scan touch keys and return number of pressed key or ID of AF event.
 * If zero, than no keys are pressed. */
u8 tk_scanKeys() {
	u8 pressed_key;
	u8 af_type;
	/* Determine if any key is pressed at the moment */
	if (mBTN_IN_BACK) {
		pressed_key = BACK_KEY;
	} else if (mBTN_IN_LEFT) {
		pressed_key = LEFT_KEY;
	} else if (mBTN_IN_OK) {
		pressed_key = OK_KEY;
	} else if (mBTN_IN_RIGHT) {
		pressed_key = RIGHT_KEY;
	} else if (mBTN_IN_OPT) {
		pressed_key = OPT_KEY;
	} else {
		pressed_key = 0;
	}

	/* If no key is pressed, return zero or terminate long press delay. */
	if (pressed_key == 0) {
		gs_tk_keys_state.counter = 0;
		/* If last pressed key is not zero, determine further steps. */
		if (gs_tk_keys_state.last_pressed != 0) {
			/* Determine AF type for last pressed button */
			af_type = gs_tk_keys_state.alt_functions[(gs_tk_keys_state.last_pressed - 1)];
			/* If was waiting for long press confirmation, terminate and return normal button press */
			if (af_type == TK_AF_LPRESS && gs_tk_keys_state.alt_step == ALT_DELAY) {
				pressed_key = gs_tk_keys_state.last_pressed; // Copy value
				gs_tk_keys_state.last_pressed = 0; // Reset last press key value
				return pressed_key;
			}
		}
		/* In all other cases reset and return zero */
		gs_tk_keys_state.alt_step = ALT_DELAY;
		gs_tk_keys_state.last_pressed = 0;
		return 0;
	}

	/* Determine AF type for pressed button */
	af_type = gs_tk_keys_state.alt_functions[(pressed_key - 1)];
	/* If last pressed key 0, process as new press event. */
	if (gs_tk_keys_state.last_pressed == 0) {
		gs_tk_keys_state.counter = 0;
		gs_tk_keys_state.last_pressed = pressed_key;
		switch (af_type) {
			/* No alternative function */
			case TK_NO_AF:
				gs_tk_keys_state.alt_step = WAIT_RELEASE;
				return pressed_key;
			/* Repeat alternative function */
			case TK_AF_REPEAT:
				gs_tk_keys_state.alt_step = ALT_DELAY;
				return pressed_key;
			/* Long press alternative function */
			case TK_AF_LPRESS:
				gs_tk_keys_state.alt_step = ALT_DELAY;
				return 0; // Zero, because wait to determine long or normal press should be return
		}
	}
	/* If pressed key is the same as last, process repeated event */
	else if (gs_tk_keys_state.last_pressed == pressed_key) {
		switch (af_type) {
			/* No alternative function */
			case TK_NO_AF:
				return 0;
			/* Repeat alternative function */
			case TK_AF_REPEAT:
				gs_tk_keys_state.counter++;
				/* Wait to confirm that fast repeat should be started */
				if (gs_tk_keys_state.alt_step == ALT_DELAY && gs_tk_keys_state.counter >= REP_EVENT_DELAY) {
					gs_tk_keys_state.alt_step = REPEAT_DELAY;
					gs_tk_keys_state.counter = 0;
					return gs_tk_keys_state.last_pressed;
				}
				/* Execute fast repeat */
				else if (gs_tk_keys_state.counter >= REP_DELAY) {
					gs_tk_keys_state.counter = 0;
					return gs_tk_keys_state.last_pressed;
				}
				return 0;
			/* Long press alternative function */
			case TK_AF_LPRESS:
				/* If wait to confirm long press */
				if (gs_tk_keys_state.alt_step == ALT_DELAY) {
					gs_tk_keys_state.counter++;
					/* If long press confirmed */
					if (gs_tk_keys_state.counter >= LP_EVENT_DELAY) {
						gs_tk_keys_state.alt_step = WAIT_RELEASE;
						return gs_tk_keys_state.last_pressed + LP_KEYN_OFFSET;
					}
				}
				return 0;
		}
	}
	/* If pressed key is different than last. Key number changed, while zero is skipped */
	else {
		/* Reset counter and do nothing */
		gs_tk_keys_state.counter = 0;
		return 0;
	}
	return 0;
}





