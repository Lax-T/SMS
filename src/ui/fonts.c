#include "ui/fonts.h"
#include "ui/fonts/consolas11pt.h"
#include "ui/fonts/arial10ptb.h"
#include "ui/fonts/arial12ptb.h"
#include "ui/fonts/digital19px.h"
#include "ui/fonts/digital25px.h"
#include "ui/fonts/digital44px.h"

/* Get font pointer by ID */
u8* fnt_getFont(u8 font_id) {
	switch (font_id) {
	case CONSOLAS_11PT:
		return getConsolas11ptPtr();
		break;
	case ARIAL_12PTB:
		return getArial12ptBPtr();
		break;
	case DIGITAL_25PX:
		return getDigital25pxPtr();
		break;
	case DIGITAL_44PX:
		return getDigital44pxPtr();
		break;
	case DIGITAL_19PX:
		return getDigital19pxPtr();
		break;
	case ARIAL_10PTB:
		return getArial10ptBPtr();
		break;
	}
}

/* Get char spacing by font ID */
u8 fnt_getCharSpacing(u8 font_id) {
	switch (font_id) {
	case CONSOLAS_11PT:
		return CONSOLAS11PT_SPACING;
	case ARIAL_12PTB:
		return ARIAL12PTB_SPACING;
	case DIGITAL_25PX:
		return DIGITAL25PX_SPACING;
	case DIGITAL_44PX:
		return DIGITAL44PX_SPACING;
	case DIGITAL_19PX:
		return DIGITAL19PX_SPACING;
	case ARIAL_10PTB:
		return ARIAL10PTB_SPACING;
	}
}
