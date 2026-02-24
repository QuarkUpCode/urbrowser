#include <stdlib.h>
#include <string.h>
#include <stdio.h>

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


//pretty print div
void pp_div(urdiv* d){
	printf("-DIV-\n");
	printf("Children count : %d\n", d->children_count);
	printf("Children pointer : %8p\n", d->children);
	printf("Format :");
	int i=0;
	if(d->format) while(d->format[i]) printf(" %2x", d->format[i++]);
	printf("\n");
	printf("Action : %s\n", d->action ? "YES" : "NULL");
	printf("-----\n");
}
