#include <stdint.h>
#include <stdlib.h>

#include "layout.h"
#include "debugging.h"

//might later replace with a smarter system
char* uralloc(uint32_t len){
	char* m = malloc(len*sizeof(char));
	if(m==0){
		LOG("Malloc failed\n");
	}
	return m;
}
void urfree(char* p){
	free(p);
	return;
}

int validate_format(urdiv* d){
	
	int invalid = 1;
	if(invalid){
		urfree(d->format);
		d->format = 0;
		return invalid;
	}

	return 0;
}

/*
	char* source : char* to the character directly following '<d' in source string
*/
urdiv parse_urdiv(const char* source){
	int i=0;
	int j;
	int l;
	urdiv d = {0, 0, 0, 0};
	while(source[i] && source[i]!='>'){
		if(source[i] == '$'){
			i++;
			if(!source[i]) break;
			switch(source[i]){
				case 'f':
					i++; if(!source[i]) break; if(source[i] != '=') break;	//now on '='
					i++; if(!source[i]) break;	//now past '='
					j=0;
					while(source[i+j] && source[i+j]!='>') j++;
					l = j;
					d.format = uralloc(l+1);
					j=0;
					while(j<=l){
						d.format[j] = source[i];
						i++;
						j++;
					}
					d.format[l] = 0x00;
					validate_format(&d);
					break;
				default:
					break;
			}
		}
		i++;
	}
	return d;
}

urdiv parse_from_str(const char* source){
	int i=0;
	urdiv main_div = {0, 0, 0, 0};
	urdiv tmp;
	while(source[i] != 0x00){
		if(source[i] == '<'){
			i++;
			switch(source[i]){
				case 0x00:
					break;
				case 'd':
					i++;
					tmp = parse_urdiv(&(source[i]));
					append_urdiv(&main_div, &tmp);
				default:
					break;
			}
		}
		i++;
	}
	return main_div;
}

