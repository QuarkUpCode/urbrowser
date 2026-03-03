#ifndef LAYOUT_H
#define LAYOUT_H

typedef enum {
	URDIV_DIR_HORIZONTAL = 0,
	URDIV_DIR_VERTICAL,
} ur_direction;

typedef enum {
	ALIGN_DEFAULT = 0,	//left/top
	ALIGN_OPPOSITE	//right/bottom
} ur_alignment;

typedef struct urdiv_s{

	int children_count;
	char* format;
	// void* children;
	struct urdiv_s* children;
	int(*action)(void*);
	int origin;
	int width;
	int dx;
	int height;
	int dy;
	ur_direction direction;
	ur_alignment alignment;
} urdiv;

#define EMPTY_URDIV {0, 0, 0, 0, 0, -1, 0, -1, 0, 0, 0}

int append_urdiv(urdiv* parent, urdiv* new_child);

void pp_div(urdiv* d);

#endif
