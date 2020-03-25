#include <stdio.h>
#define TIL 9
#define NUM 200
#define STATES 3
#define DO(n,x) {int i=0,_n=(n);for(;i<_n;++i){x;}}

char array_[TIL]; 			
char* array = &array_[0];

/*
	TIL _ TIL-1 _ TIL-2 _ ... _ 1 _ 0 is the equation 
	there are STATES number of different _ operators 
	which are kept in char* array

	for ex operator between TIL-2 and TIL-3
	contained at array[TIL-3] and so on

	the question is how many equations kind of 
	TIL _ TIL-1  _ ... _ 1 _ 0 are equal to NUM where _
	can be '+', '-' or blank, TIL == 9, NUM == 200
	
	state numbers:
		0 --> blank
		1 --> '+'
		2 --> '-'
*/

int pow_(int n, int exp) {
	int j = 1;
	if (!exp)
		return 1;
	DO(exp,j*=n);
	return j;
}

/*	prints left part of the equation	*/
void arrprint(char *array) {
	int i;
	for (i = TIL; i > 0; i--) {
		printf("%lli", i);
		if (array[i-1] == 1) 
			printf("+");
		if (array[i-1] == 2) 
			printf("-");
	}
	printf("0\n");
	fflush(stdout);
}

/*	return prev which is the equation result 
	of states array and numbers TIL...0			*/
long long eq(char* array) {
	long long prev = 0, cur = TIL, i;
	char a = 1;

	for (i = TIL-1; i >= 0; i--) {
		if (!array[i]) 
			cur = cur*10 + i;
		else {
			prev += (a == 1 ? cur : -cur);
			a = array[i]; cur = i;
		}
	}
	return (prev += (a == 1 ? cur : -cur));
}

/*	shift array to the next state works as column 
	additon of 1 and char* array as a base-3 number  */
void state(char* array) {
	int i;

	for (i = TIL-1; i >= 0; i--) {
		if (array[i] >= 2) {
			array[i] = 0;
		}
		else {
			array[i]++;
			break;
		}
	}
}

/*	consider all combinations of +-blank return cnt 
	which is a counter of all suitable combinations	*/
int cycle(int state_max) {
	int i, cnt = 0;

	DO(state_max,		
		{if (eq(array) == NUM)  {
			arrprint(array);
			cnt++;
		}
		state(array);})
	return cnt;
}

int main()
{
	printf("\n_%d ways to get %d\n", cycle(pow_(STATES, TIL)), NUM);
	return 0;
}
//:~