#include <stdlib.h>
#include <string.h>

#include "layout.h"
#include "debugging.h"

//!!! PLEASE REPLACE THIS ASAP
int append_urdiv(urdiv* parent, urdiv* new_child){
	
	if(parent->children == 0){
		if(parent->children_count != 0){
			DEBUG("THIS SHOULD NEVER HAPPEN\n");
			parent->children_count = 0;
		}
	}
	if(parent->children_count == 0){
		parent->children = malloc(sizeof(urdiv));
		((urdiv*)parent->children)[0] = *new_child;
		return 0;
	}

	parent->children_count++;

	urdiv* new_ptr = (urdiv*)malloc(parent->children_count*sizeof(urdiv));
	memcpy(new_ptr, parent->children, sizeof(urdiv)*(parent->children_count - 1));
	free(parent->children);
	parent->children = new_ptr;

	return 0;
}
