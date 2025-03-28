#include "MyString.h"
#include <stdlib.h>

int realen(const char *str){
	int len = 0;
	for(; *str != '\0'; str += mblen(str, MB_CUR_MAX) ){
		++len;
	}
	return len;
}