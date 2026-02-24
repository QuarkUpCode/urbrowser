#ifndef LAYOUT_H
#define LAYOUT_H

typedef struct {

	int children_count;
	char* format;
	void* children;
	int(*action)(void*);

} urdiv;


int append_urdiv(urdiv* parent, urdiv* new_child);

void pp_div(urdiv* d);

#endif
