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
		parent->children_count++;
		return 0;
	}

	parent->children_count++;

	urdiv* new_ptr = (urdiv*)malloc(parent->children_count*sizeof(urdiv));
	memcpy(new_ptr, parent->children, sizeof(urdiv)*(parent->children_count - 1));
	free(parent->children);
	parent->children = new_ptr;
	(parent->children)[parent->children_count-1] = *new_child;

	return 0;
}


//pretty print div
void pp_div(urdiv* d){
	printf("-DIV-\n");
	printf("Address : %8p\n", d);
	printf("Origin : %i\n", d->origin);
	printf("Children count : %d\n", d->children_count);
	printf("Children pointer : %8p\n", d->children);
	printf("Format :");
	int i=0;
	if(d->format) printf("\x1b[%sm", d->format);
	if(d->format) while(d->format[i]) printf(" %2x", d->format[i++]);
	if(d->format) printf(" \x1b[0m");
	printf("\n");
	printf("Action : %s\n", d->action ? "YES" : "NULL");

	if(d->children_count){
		printf("\t> CHILDREN :\n");
		for(int i=0; i<d->children_count; i++){
			pp_div(&(d->children[i]));
		}
		printf("\t END OF CHILDEN\n");
	}
	printf("-----\n");
}
