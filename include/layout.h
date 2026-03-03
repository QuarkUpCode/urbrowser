#ifndef LAYOUT_H
#define LAYOUT_H

typedef struct urdiv_s{

	int children_count;
	char* format;
	// void* children;
	struct urdiv_s* children;
	int(*action)(void*);
	int origin;

} urdiv;


int append_urdiv(urdiv* parent, urdiv* new_child);

void pp_div(urdiv* d);

#endif
