#include "ui/views/control_methods.h"
#include "ui/views/views.h"

u8 _vcm_pushViewToStack(struct ViewContext *view_ctx);
u8 _vcm_popViewFromStack(struct ViewContext *view_ctx);

/* Reset views stack to zero. Current view becomes base. */
void vcm_resetViewsStack(struct ViewContext *view_ctx) {
	/* Copy array size to zero position */
	u8 arr_size = view_ctx->stack.arr_sizes_stack[view_ctx->stack.stack_pointer];
	view_ctx->stack.arr_sizes_stack[0] = arr_size;
	/* Reset stack pointer */
	view_ctx->stack.stack_pointer = 0;
}

/* Set new view WITHOUT storing previous view to stack (overwrite) */
void vcm_setView(u8 view_id, u8 view_modifier, struct ViewContext *view_ctx, struct UIContext *ui_ctx) {
	/* Get new view array size */
	u8 arr_size = vw_getViewMeta(view_id)->arr_size;
	/* Set new view context values */
	view_ctx->view_id = view_id;
	view_ctx->view_modifier = view_modifier;
	view_ctx->stack.arr_sizes_stack[view_ctx->stack.stack_pointer] = arr_size;
}

/* Enter nested view, previous view is stored to stack. */
void vcm_enterView(u8 view_id, u8 view_modifier, struct ViewContext *view_ctx, struct UIContext *ui_ctx) {
	/* Get new view array size */
	u8 arr_size = vw_getViewMeta(view_id)->arr_size;

	/* Execute exit event for current view */
	vcm_executeEvent(veVIEW_EXIT, view_ctx, ui_ctx);
	/* Store current view to stack */
	_vcm_pushViewToStack(view_ctx);
	/* Load new view */
	view_ctx->view_id = view_id;
	view_ctx->view_modifier = view_modifier;
	view_ctx->stack.arr_sizes_stack[view_ctx->stack.stack_pointer] = arr_size;
	/* Execute enter event for new view */
	vcm_executeEvent(veVIEW_ENTER, view_ctx, ui_ctx);
}

/* TODO: implement when needed */
void vcm_enterViewWithArg() {

}

/* Discard current view and return to previous view. */
void vcm_returnToPrevView(struct ViewContext *view_ctx, struct UIContext *ui_ctx) {
	/* Execute exit event for current view */
	vcm_executeEvent(veVIEW_EXIT, view_ctx, ui_ctx);
	/* Return to previous view */
	_vcm_popViewFromStack(view_ctx);
	/* Execute on return event for loaded view. */
	vcm_executeEvent(veVIEW_RETURN_TO, view_ctx, ui_ctx);
}

/* TODO: implement when needed */
void vcm_returnPrevViewWithArgs() {

}

/* Execute view event handler */
u8 vcm_executeEvent(u8 event_code, struct ViewContext *view_ctx, struct UIContext *ui_ctx) {
	struct ViewMeta *view_meta;
	/* Increment call recursion counter */
	view_ctx->system.recursion_cnt++;
	/* Check recursion counter, if limit is reached - ignore execution and set error flag. */
	if (view_ctx->system.recursion_cnt > UI_MAX_EVENT_RECURSION) {
		view_ctx->system.error_flags |= fUI_RECURSION_ERR;
		return 255;
	}
	/* Get view meta object */
	view_meta = vw_getViewMeta(view_ctx->view_id);
	/* Run view handler method */
	return (view_meta->method)(event_code, view_ctx, ui_ctx);
}


/* Private control methods */
/* Store current view variables to stack. If success returns 1 (TRUE), else - 0 (FALSE)
 This function DOES NOT set values of view_id, modifier, etc. for a new view.
 It's a responsibility of the loader function! */
u8 _vcm_pushViewToStack(struct ViewContext *view_ctx) {
	u8 i = 0;
	u8 current_level = view_ctx->stack.stack_pointer;
	u8 current_arr_size = view_ctx->stack.arr_sizes_stack[current_level];
	/* Check for possibility of stack overflow */
	if (current_level >= (UI_STACK_SIZE - 1)) { // "-1" because pointer starts from 0
		/* Set error flag and exit */
		view_ctx->system.error_flags |= fUI_STACK_OVERFL;
		return FALSE;
	}
	/* Check for possibility of array stack overflow */
	if ((current_arr_size + view_ctx->stack.arr_offset) >= UI_ARR_STACK_SIZE) {
		/* Set error flag and exit */
		view_ctx->system.error_flags |= fUI_ARR_STACK_OVERFL;
		return FALSE;
	}

	/* Store current view ID and modifier */
	view_ctx->stack.id_stack[current_level] = view_ctx->view_id;
	view_ctx->stack.modifier_stack[current_level] = view_ctx->view_modifier;
	/* Store "registers" */
	view_ctx->stack.a_reg_stack[current_level] = view_ctx->a_reg;
	view_ctx->stack.b_reg_stack[current_level] = view_ctx->b_reg;
	view_ctx->stack.x_reg_stack[current_level] = view_ctx->x_reg;
	view_ctx->stack.y_reg_stack[current_level] = view_ctx->y_reg;
	/* Store array */
	while (i < current_arr_size) { // If current view does not use array - skip operation
		view_ctx->stack.arr_stack[view_ctx->stack.arr_offset] = view_ctx->data_array[i];
		view_ctx->stack.arr_offset++;
		i++;
	}

	/* Shift stack pointer */
	view_ctx->stack.stack_pointer++;
	return TRUE;
}

/* Revert previous view variables from stack. */
u8 _vcm_popViewFromStack(struct ViewContext *view_ctx) {
	u8 i = 0;
	u8 current_level;
	u8 arr_size;

	/* If non zero, shift stack pointer to previous view */
	if (view_ctx->stack.stack_pointer > 0) {
		 view_ctx->stack.stack_pointer--;
		 current_level = view_ctx->stack.stack_pointer;
	}
	/* If nowhere to go (already zero) - exit with FALSE result. */
	else {
		return FALSE;
	}

	/* Check for array stack zero disposition */
	arr_size = view_ctx->stack.arr_sizes_stack[current_level];
	if (arr_size > view_ctx->stack.arr_offset) {
		view_ctx->system.error_flags |= fUI_ARR_STACK_DISPOS;
		return FALSE;
	}

	/* Restore view ID and modifier */
	view_ctx->view_id = view_ctx->stack.id_stack[current_level];
	view_ctx->view_modifier = view_ctx->stack.modifier_stack[current_level];
	/* Restore "registers" */
	view_ctx->a_reg = view_ctx->stack.a_reg_stack[current_level];
	view_ctx->a_reg = view_ctx->stack.b_reg_stack[current_level];
	view_ctx->a_reg = view_ctx->stack.x_reg_stack[current_level];
	view_ctx->a_reg = view_ctx->stack.y_reg_stack[current_level];

	/* Set array offset pointer to zero point for current view */
	view_ctx->stack.arr_offset -= arr_size;
	/* Restore array */
	while (i < arr_size) {
		view_ctx->data_array[i] = view_ctx->stack.arr_stack[(view_ctx->stack.arr_offset + i)];
		i++;
	}
	return TRUE;
}



