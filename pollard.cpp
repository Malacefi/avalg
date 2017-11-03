// Authors: Emelie Eriksson & Marcus Lignercrona
#include <iostream>
#include <stdlib.h>
using namespace std;

// This implementation of gcd is from 
// https://codereview.stackexchange.com/questions/66711/greatest-common-divisor
int gcd(int a, int b){
	return b == 0 ? a : gcd(b, a % b);
}

long long int pollards(long long int n){
	if(n == 1)
		return n;

	srand (time(NULL));

	long long int x = (rand() % n) + 3; 
	long long int y = x;
	long long int a = (rand() % n) + 3; // Constant for the f(x) = x^2 + a function

	long long int currentgcd = 1;

	while(currentgcd == 1){
		// Turtle
		x = (x*x + a) % n;

		//Hare
		y = (y*y + a) % n;
		y = (y*y + a) % n;

		//new gcd
		currentgcd = gcd(abs(x - y), n);
	}

	return currentgcd;
}

int main(){
	long long int number = 243;
	long long int factor = pollards(number);
	cout << "A factor to " << number << " is " << factor;
	return 0;
}
