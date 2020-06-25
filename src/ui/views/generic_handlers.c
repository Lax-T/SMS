#include "ui/views/generic_handlers.h"
#include "ui/views/menus.h"

/* Handlers for generic list menu

	CONVENTION:
- view_modifier - parent menu ID
- a_reg - currently selected item (0 - first item)
- b_reg - nest level (0 - parent list)
- data_array - items selection tree *

 One menu item UP */
void vgh_listMenuUp(struct ViewContext *view_context) {
	/* Manipulate */
	if (view_context->a_reg > 0) {
		view_context->a_reg--;
	}
}

/* One menu item DOWN */
void vgh_listMenuDown(struct ViewContext *view_context) {
	struct MenuList *menu_list;
	/* Get current menu list */
	menu_list = m_getNestedMenuList(view_context->view_modifier, view_context->b_reg, view_context->data_array);
	/* Manipulate */
	if (view_context->a_reg < (menu_list->len - 1)) {
		view_context->a_reg++;
	}
}

/* Enter nested menu list */
void vgh_listMenuEnter(struct ViewContext *view_context) {
	struct MenuList *menu_list;
	/* Get current menu list */
	menu_list = m_getNestedMenuList(view_context->view_modifier, view_context->b_reg, view_context->data_array);
	/* Check if it's possible to enter submenu. If pointer within range and item contains nested list */
	if (view_context->a_reg < menu_list->len && menu_list->items[view_context->a_reg]->action == mGO_SUB_MENU) {
		/* Store selected on this level item */
		view_context->data_array[view_context->b_reg] = view_context->a_reg;
		/* Increase nest level  */
		view_context->b_reg++;
		/* Go to the first item */
		view_context->a_reg = 0;
	}
}

/* Get menu item action */
u16 vgh_listMenuGetAction(struct ViewContext *view_context) {
	struct MenuList *menu_list;
	/* Get current menu list */
	menu_list = m_getNestedMenuList(view_context->view_modifier, view_context->b_reg, view_context->data_array);
	return menu_list->items[view_context->a_reg]->action;
}

/* Return one level up (to parent list) */
void vgh_listMenuReturn(struct ViewContext *view_context) {
	struct MenuList *menu_list;
	/* Get current menu list */
	menu_list = m_getNestedMenuList(view_context->view_modifier, view_context->b_reg, view_context->data_array);
	/* Check if it's possible to return. If not already on parent level */
	if (view_context->b_reg > 0) {
		/* Return to the previous level */
		view_context->b_reg--;
		/* Recover n of previously selected item */
		view_context->a_reg = view_context->data_array[view_context->b_reg];
	}
}

/* Methods to edit multiple parameters */
/* Set multiple initial parameter values */
void vgh_setMultParams(u8 params[], u8 len, struct ViewContext *view_context) {
	u8 i;
	for (i=0; i < len; i++) {
		view_context->data_array[i * 2] = params[i];
	}
}

/* Set single parameter */
void vgh_setParam(u8 val, u8 position, struct ViewContext *view_context) {
	view_context->data_array[position * 2] = val;
}

/* Set multiple parameter limiters */
void vgh_setMultParamLimiters(u8 limiters[], u8 len, struct ViewContext *view_context) {
	u8 i;
	for (i=0; i < len; i++) {
		view_context->data_array[(i * 2) + 1] = limiters[i];
	}
}

/* Set single limiter */
void vgh_setParamLimiter(u8 val, u8 position, struct ViewContext *view_context) {
	view_context->data_array[(position * 2) + 1] = val;
}

/* Set single parameter and limiter */
void vgh_setParamAndLimiter(u8 val, u8 limiter, u8 position, struct ViewContext *view_context) {
	view_context->data_array[position * 2] = val;
	view_context->data_array[(position * 2) + 1] = limiter;
}

/* Increment parameter */
void vgh_incParam(u8 position, struct ViewContext *view_context) {
	u8 param;
	param = view_context->data_array[position * 2];
	if (param <  view_context->data_array[(position * 2) + 1]) {
		param++;
		view_context->data_array[position * 2] = param;
	}
}

/* Decrement parameter */
void vgh_decParam(u8 position, struct ViewContext *view_context) {
	u8 param;
	param = view_context->data_array[position * 2];
	if (param > 0) {
		param--;
		view_context->data_array[position * 2] = param;
	}
}

/* Get parameter */
u8 vgh_getParam(u8 position, struct ViewContext *view_context) {
	return view_context->data_array[position * 2];
}






