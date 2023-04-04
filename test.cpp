#include <stdio.h>
#define Error(...) \
    printf("Error type %d at Line %d:",n,line);

int main(){
	Error(1,3);
	return 0;
}
