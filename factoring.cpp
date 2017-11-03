//Author Marcus Lignercrona & Emelie Eriksson
#include <iostream>
#include <string>
class factoring{
	public:
		int divisor2(long long & number){
			int temp;
			while(true){
				temp = number & 1;
				if(temp == 0){
					number>>=1;
					std::cout << 2 << "\n";
				}
				else{
					break;
				}
			}
		}
};
	int main (){
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
