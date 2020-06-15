#include "ui/views/generic_handlers.h"
#include "ui/views/menus.h"

/* CONVENTION
 * view_modifier - parent menu ID
 * a_reg - currently selected item (0 - first item)
 * b_reg - nest level (0 - parent list)
 * data_array - items selection tree *
 *  */

/* Handlers for generic list menu */
/* One menu item UP */
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
	}
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


