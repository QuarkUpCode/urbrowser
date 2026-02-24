#include <stdio.h>
#include "debugging.h"

int main(int argc, char** argv){

	if(argc < 2){
		fprintf(stderr, "Usage : %s url\n", argv[0]);
		return 1;
	}

	DEBUG("url : %s\n", argv[1]);

	return 0;
}
