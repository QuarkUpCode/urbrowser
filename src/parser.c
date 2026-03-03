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
	
	int invalid = 0;
	if(invalid){
		urfree(d->format);
		d->format = 0;
		return invalid;
	}
	DEBUG("%s\n", d->format);
	return 0;
}

/*
	char* source : char* to the character directly following '<d' in source string
*/
urdiv parse_urdiv(const char* source, int* i){
	// int i=0;
	int j;
	int l;
	// urdiv d = {0, 0, 0, 0, 0, -1, 0, -1, 0};
	urdiv d = EMPTY_URDIV;
	d.origin = *i;
	urdiv tmp;
	while(source[*i] && source[*i]!='>'){
		if(source[*i] == '$'){
			(*i)++;
			if(!source[*i]) break;
			switch(source[*i]){
				case 'f':
					(*i)++; if(!source[*i]) break; if(source[*i] != '=') break;	//now on '='
					(*i)++; if(!source[*i]) break;	//now past '='
					j=0;
					while(source[(*i)+j] && source[(*i)+j]!='>' && source[(*i)+j]!=' ') j++;
					l = j;
					// printf("LEN : %d\n", l);
					d.format = uralloc(l+1);
					j=0;
					while(j<=l){
						d.format[j] = source[*i];
						(*i)++;
						j++;
					}
					d.format[l] = 0x00;
					validate_format(&d);
					break;
				default:
					DEBUG("Unexpected char after $ : %c\n", source[*i]);
					break;
			}
		}
		(*i)++;
	}
	// while(source[*i] && source[*i]!='<') (*i)++;
	// if(!source[*i]) return d;
	// (*i)++;
	// if(!source[*i]) return d;
	while(source[*i]){
		while(source[*i] && source[*i]!='<') (*i)++;
		if(!source[*i]) return d;
		(*i)++;
		if(!source[*i]) return d;
		switch(source[*i]){
			case '/':
				return d;
			case 'd':
				DEBUG("NEW DIV at %d\n", *i);
				tmp = parse_urdiv(source, i);
				append_urdiv(&d, &tmp);
				break;
			default:
				LOG("Unexpected character at source[%d] : %c\n", *i, source[*i]);
				break;
		}
	}
	return d;
}

urdiv parse_from_str(const char* source){
	int i=0;
	const int BASE_WIDTH = 48;
	const int BASE_HEIGHT = 36;
	// urdiv main_div = {0, 0, 0, 0, 0, BASE_WIDTH, 0, BASE_HEIGHT, 0, 0};
	urdiv main_div = EMPTY_URDIV;
	main_div.width = BASE_WIDTH;
	main_div.height = BASE_HEIGHT;
	urdiv tmp;
	while(source[i] != 0x00){
		if(source[i] == '<'){
			i++;
			switch(source[i]){
				case 0x00:
					break;
				case 'd':
					i++;
					// tmp = parse_urdiv(&(source[i]));
					tmp = parse_urdiv(source, &i);
					append_urdiv(&main_div, &tmp);
					break;
				default:
					break;
			}
		}
		i++;
	}
	return main_div;
}

