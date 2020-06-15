#include "globals.h"

/* Menu IDs */
#define midMAIN_MENU 0

#define mGO_VIEW(id,modifier) ((id<<8) | (modifier))
#define mGO_SUB_MENU 0xFFFF
#define mNOP 0

/* Structures definitions */
#ifndef MENU_ITEM_STRUCT_DEF_
#define MENU_ITEM_STRUCT_DEF_
/* Menu list item */
struct MenuItem {
	char *title;
	u16 action;
	struct MenuList *sub_list;
};
#endif

#ifndef MENU_LIST_STRUCT_DEF_
#define MENU_LIST_STRUCT_DEF_
/* Menu list */
struct MenuList {
	u8 len;
	char *title;
	struct MenuItem *items[];
};
#endif

/* Function definitions */
struct MenuList *m_getMenuList(u8 menu_id);
struct MenuList *m_getNestedMenuList(u8 parent_menu_id, u8 nest_level, u8 nest_tree[]);
