#include <stdlib.h>

#include "rguitk.h"
#include "x11.h"

RGUITK_EXPORT RGUITKDisplay* rguitk_display_open(char* display) {
	return x11_display_open(display);
}

RGUITK_EXPORT RGUITKScreen* rguitk_display_get_default_screen(RGUITKDisplay* display) {
	return x11_display_get_default_screen(display);
}
