#include <stdio.h>

int wwww;

int pig(int a){
	int b,c;
	b = a + 100;
	c = b*2;
	wwww = c;
	return c;
}

int dog(){
	int omg = 1;
	return omg+10;
}

int people(){
	int sss = 5;
	return wwww+sss;
}

int main(void){
	int s = 100;
	int d;
	int o;
	int wof;
	int hey;
	d = pig(s);
	o = dog();
	hey = people();
	wof = wwww;
	printf("%d",d);
	printf("%d",wof);
	printf("%d",wwww);
	printf("%d",o);
	printf("%d",hey);
	return 0;
}