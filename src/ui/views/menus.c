#include "ui/views/menus.h"

/* MENUS TEXT */
const char txt_menu[] = "Menu";
const char txt_setup[] = "Setup";
const char txt_alarms[] = "Alarms";
const char txt_calendar[] = "Calendar";

/* MENUS DEFINITIONS */
/* Dummy sub menu */
const struct MenuList _m_Dummy = {};

/* Main menu */
const struct MenuItem _m_itemSetup = {.title = txt_setup, .action = mNOP};
const struct MenuItem _m_itemAlarms = {.title = txt_alarms, .action = mNOP};
const struct MenuItem _m_itemCalendar = {.title = txt_calendar, .action = mNOP};

const struct MenuList m_MainMenu = {
		.len = 3,
		.title = txt_menu,
		.items = {&_m_itemCalendar, &_m_itemAlarms, &_m_itemSetup}
};

/***************** MENUS INDEX AND ACCESS *********************/
/* Menus index */
const struct MenuList *_m_MenuListsIndex[] = {
		&m_MainMenu
};

/* Provides access to menu lists */
struct MenuList *m_getMenuList(u8 menu_id) {
	return _m_MenuListsIndex[menu_id];
}

/* Provides access not the nested menu list (walks menu tree) */
struct MenuList *m_getNestedMenuList(u8 parent_menu_id, u8 nest_level, u8 nest_tree[]) {
	u8 i;
	u8 item_n;
	struct MenuList *list_ptr;
	/* If nesting level is zero, than it's parent menu */
	if (nest_level == 0) {
		return _m_MenuListsIndex[parent_menu_id];
	}
	/* If nesting level not zero - start digging */
	/* Preload parent menu */
	list_ptr = _m_MenuListsIndex[parent_menu_id];
	/* Iterate/extract nested menus */
	for (i=0; i<nest_level; i++) {
		/* Get n of item that was selected on this level  */
		item_n = nest_tree[i];
		/* Extract nested menu list */
		list_ptr = list_ptr->items[item_n]->sub_list;
	}
	return list_ptr;
}









