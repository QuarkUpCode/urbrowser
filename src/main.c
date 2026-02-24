#include <stdio.h>
#include "debugging.h"

#include "layout.h"
#include "parser.h"
#include "loadfile.h"

int main(int argc, char** argv){

	if(argc < 2){
		fprintf(stderr, "Usage : %s url\n", argv[0]);
		return 1;
	}

	DEBUG("url : %s\n", argv[1]);
	
	char* testsrc = loadfile("test/data/example.uwu");
	urdiv root = parse_from_str(testsrc);
	pp_div(&root);
	pp_div(root.children);

	return 0;
}
