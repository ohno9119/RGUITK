#ifndef RGUITK
#define RGUITK

#define RGUITK_EXPORT __attribute__((visibility("default")))

#ifdef __GNUC__
	#define rguitk_atomic_inc(a) __sync_add_and_fetch((a), 1)
#endif

#ifdef __GNUC__
	#define rguitk_atomic_dec(a) __sync_sub_and_fetch((a), 1)
#endif

typedef enum {
    RGUITK_FALSE,
    RGUITK_TRUE
} RGUITKBool;

typedef void (*RGUITKGenericFunc)(void*);
typedef struct {
	RGUITKGenericFunc ref_free_func;
    unsigned int ref_count;
} RGUITKRefCountable;

typedef void (*RGUITKObjectFillFunc)(void*);
typedef struct {
	RGUITKRefCountable;
    char *object_type;
    char *object_subtype;
    RGUITKObjectFillFunc* object_fillers;
} RGUITKObject;

#define RGUITK_DISPLAY_TYPE "rguitkdisplay"
#define RGUITK_X11_SUBTYPE "x11"
typedef struct {
	RGUITKObject;
	void *native_display;
} RGUITKDisplay;

#define RGUITK_SCREEN_TYPE "rguitkscreen"
typedef struct {
	RGUITKObject;
	void *native_screen;
	int native_screen_number;
} RGUITKScreen;

extern void rguitk_refcountable_ref(RGUITKRefCountable* refcountable);
extern void rguitk_refcountable_unref(RGUITKRefCountable* refcountable);
extern void rguitk_refcountable_setfreefunc(RGUITKRefCountable* refcountable, RGUITKGenericFunc func);
extern void rguitk_object_fill(RGUITKObject* object, char* type, char* subtype, RGUITKGenericFunc* fillers, RGUITKBool fill);
extern void rguitk_object_free(void* obj);

extern RGUITKDisplay* rguitk_display_open(char* display);
extern RGUITKScreen* rguitk_display_get_default_screen(RGUITKDisplay* display);

#endif
