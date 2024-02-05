#include <stdio.h>
#include <stdlib.h>
#include <rguitk.h>

int main(void) {
	RGUITKDisplay* display;
	RGUITKScreen* screen;
	
	display = rguitk_display_open(NULL);
	screen = rguitk_display_get_default_screen(display);
	printf("%d\n", screen->native_screen_number);
}
