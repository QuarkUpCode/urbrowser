#include "layout.h"
#include "debugging.h"

// void apply_size_and_pos(urdiv* parent, urdiv* child){
void apply_size_and_pos(urdiv* parent){

	int margin = 1;

	int w_available = parent->width;
	int h_available = parent->height;
	int current_dx = 0;
	int current_dy = 0;
	
	urdiv* child;

	//first pass : hardcoded sizes
	for(int i=0; i<parent->children_count; i++){
		child = &(parent->children[i]);
		switch(parent->direction){
			case URDIV_DIR_HORIZONTAL:
				if(child->width >= 0){
					if(child->width > w_available) child->width = w_available;
				}
				child->height = parent->height;
				w_available -= child->width;
				break;
			case URDIV_DIR_VERTICAL:
				if(child->height >= 0){
					if(child->height > h_available) child->height = h_available;
				}
				child->width = parent->width;
				h_available -= child->height;
				break;
			default:
				DEBUG("Impossible urdiv.direction value %d\n", parent->direction);
				break;
		}
	}

	int available_count = 0;

	for(int i=0; i<parent->children_count; i++){
		child = &(parent->children[i]);
		switch(parent->direction){
			case URDIV_DIR_HORIZONTAL:
				if(child->width < 0){
					available_count++;
				}
				break;
			case URDIV_DIR_VERTICAL:
				if(child->height < 0){
					available_count++;
				}
				break;
			default:
				DEBUG("Impossible urdiv.direction value %d\n", parent->direction);
				break;
		}
	}

	int len;
	if(parent->direction == URDIV_DIR_HORIZONTAL) len = w_available;
	if(parent->direction == URDIV_DIR_VERTICAL) len = h_available;

	int leftover = len%available_count;
	len /= available_count;

	for(int i=0; i<parent->children_count; i++){
		child = &(parent->children[i]);
		switch(parent->direction){
			case URDIV_DIR_HORIZONTAL:
				if(child->width < 0){
					child->width = len;
					available_count--;
					if(available_count == 0) child->width += leftover;
				}
				break;
			case URDIV_DIR_VERTICAL:
				if(child->height < 0){
					child->height = len;
					available_count--;
					if(available_count == 0) child->height += leftover;
				}
				break;
			default:
				DEBUG("Impossible urdiv.direction value %d\n", parent->direction);
				break;
		}
	}
	
	//recursive bitch
	for(int i=0; i<parent->children_count; i++) apply_size_and_pos(&(parent->children[i]));
}

void apply_alignment(urdiv* root){
	
}


void compute_div_sizes(urdiv* root){

	

}
