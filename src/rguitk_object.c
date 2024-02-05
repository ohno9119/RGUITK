#include <stdlib.h>
#include <string.h>
#include "rguitk.h"

void* memdup(void* mem, size_t size) { 
	void* out;
   
	out = malloc(size);

	if(out) {
		memcpy(out, mem, size);
	}
	
    return out;
}

RGUITK_EXPORT void rguitk_refcountable_ref(RGUITKRefCountable* refcountable) {
	if (refcountable) {
		rguitk_atomic_inc(&refcountable->ref_count);		
	}
}

RGUITK_EXPORT void rguitk_refcountable_unref(RGUITKRefCountable* refcountable) {
	if (refcountable) {
		if (!rguitk_atomic_dec(&refcountable->ref_count)) {
			if (refcountable->ref_free_func) {
				refcountable->ref_free_func(refcountable);
			} else {
				free(refcountable);
			}
		}
	}
}

RGUITK_EXPORT void rguitk_refcountable_setfreefunc(RGUITKRefCountable* refcountable, RGUITKGenericFunc func) {
	if (refcountable && func) {
		refcountable->ref_free_func = func;
	}	
}

RGUITK_EXPORT void rguitk_object_free(void* obj) {
	RGUITKObject* object;
	
	object = (RGUITKObject*)obj;
	
	if (object) {
		if (object->object_type) {
			free(object->object_type);
		}

		free(object);
	}
}

RGUITK_EXPORT void rguitk_object_fill(RGUITKObject* object, char* type, char* subtype, RGUITKGenericFunc* fillers, RGUITKBool dont_fill) {
	int i;
		
	if (!object || !type || !fillers) {
		return;
	}
	
	if (fillers) {
		i = 0;
		while (fillers[i]) {
			i++;
		}
		
		object->object_fillers = memdup(fillers, sizeof(RGUITKGenericFunc)*i);	
	}

	object->object_type = strdup(type);
	object->object_type = strdup(type);
	object->ref_free_func = rguitk_object_free;
	object->ref_count = 1;
	
	if (dont_fill) {
		i = 0;
		while (object->object_fillers[i]) {
			object->object_fillers[i](object);
			i++;
		}		
	}
}
