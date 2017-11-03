//Author Marcus Lignercrona & Emelie Eriksson
#include <iostream>
#include <string>
#include <stdlib.h>
#include <math.h>
class factoring{
	public:
		long long powerHelp(int base,int exponent, int mod){
			int toBeReturned = 1;
			base = base % mod;
			for(int i= 0; i<exponent; ++i){
				toBeReturned = (toBeReturned * base) % mod;
			}	
			return toBeReturned;
		}
		/*
		returns the amount of 2 factors in a number while removing the 2 factors from the original number
		*/
		int divisor2(long long & number){
			int counter = 0;
			int temp;
			while(true){
				temp = number & 1;
				if(temp == 0){
					number>>=1;
					counter++;
				}
				else{
					break;
				}
			}
			return counter;
		}
		/*
		Testar primalitet, HERE BE DRAGONS! CALL BY VALUE???
		*/
		bool miller(long long number){
			long long copyNumber = number-1;
			long long t ;
			long long s = divisor2(copyNumber);
			t = copyNumber;
			long long a;
			//Below lies a ma.gic number.
			for(int i = 0; i<1000; ++i){
				//kan få overflow
				 a = 2 + (std::rand() % ((number -1)- 2 + 1));
				// long long temp = pow(a,t);
				// long long u = temp % number;
				long long u = powerHelp(a,t,number);
				 if(u == 1 || u == (number-1)) continue;
				 	for(int j = 0; j < (s -1); ++j){
				 		u = (u*u) % number;
				 		if(u == 1) return false;
				 		if(u == (number -1)) break;
				 	}
				 if(u == (number -1)) continue;
				 return false;
			}
			return true;
		}

};
	int main (){
		factoring fact;
		long long test = 9576890769;
		for(int i = 3; i < 1000; ++i){
			if((i & 1)== 1){
				if(fact.miller(i)){
					std::cout << i << " is prime" << std::endl;
				}
				/*else{
					std::cout << i << " is not prime"<< std::endl;
				}*/
			}
		}
		long long a;
		std::cin >> a;
		while(1){
			std::cout << "fail" << std::endl;
			if(std::cin >> a){	
				std::cout << "\n";
			}
			else{
				break;
			}
		}
	}
