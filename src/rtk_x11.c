#include <stdlib.h>
#include <stdio.h>
#include <X11/Xlib.h>

#include "rguitk.h"

RGUITKDisplay* x11_display_open(char* display) {
	RGUITKDisplay* ret;
    Display* native_display;
	
    native_display = XOpenDisplay(display);
    if (native_display) {
		ret = malloc(sizeof(RGUITKDisplay));
		rguitk_object_fill((RGUITKObject*)ret, RGUITK_DISPLAY_TYPE, RGUITK_X11_SUBTYPE, NULL, RGUITK_FALSE);
		ret->native_display = (void*)native_display;
		return ret;
	}	

	return NULL;
}

RGUITKScreen* x11_display_get_default_screen(RGUITKDisplay* display) {
	RGUITKScreen* ret;
	
	if (!display) {
		return NULL;
	}
	
	ret = malloc(sizeof(RGUITKScreen));
	rguitk_object_fill((RGUITKObject*)ret, RGUITK_SCREEN_TYPE, RGUITK_X11_SUBTYPE, NULL, RGUITK_FALSE);
	ret->native_screen_number = DefaultScreen((Display*)display->native_display);
	ret->native_screen = DefaultScreenOfDisplay((Display*)display->native_display);
	
	return ret;
}
