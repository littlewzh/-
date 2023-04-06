#include <stdio.h>
#define Error(n,line) \
    printf("Error type %d at Line %d:",n,line);
int func(int a){
	a++;
	int a =1;
	return a;
}
int main(){
	Error(1,3);
	func(1);
	return 0;
}
