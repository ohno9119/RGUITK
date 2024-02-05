#include "rguitk.h"

#ifndef RGUITK_X11
#define RGUITK_X11

RGUITKDisplay* x11_display_open(char* display);
RGUITKScreen* x11_display_get_default_screen(RGUITKDisplay* display);

#endif
