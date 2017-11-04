// Authors: Emelie Eriksson & Marcus Lignercrona
#include <iostream>
#include <fstream>
#include <string>
#include <stdlib.h>
#include <math.h>
using namespace std;

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

// This implementation of gcd is from 
// https://codereview.stackexchange.com/questions/66711/greatest-common-divisor
int gcd(long long int a, long long int b){
    return b == 0 ? a : gcd(b, a % b);
}

long long int pollards(long long int n){
    if(n == 1)
        return n;

    srand (time(NULL));

    long long int x = (rand() % n) + 3; 
   // std::cout << "x is: " << x << std::endl;
    long long int y = x;
   // std::cout << "x is: " << x << std::endl;
    long long int a = (rand() % n) + 3; // Constant for the f(x) = x^2 + a function
   // std::cout << "x is: " << x << std::endl;

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

long long int findPrimeFactor(long long int number, factoring fact){
    // Run pollard 
    long long int foundFactor = pollards(number);
    // While the factor is not a prime
    while(!fact.miller(foundFactor)){
        // Keep factoring it
        foundFactor = pollards(foundFactor);
    }
    return foundFactor;
}

int main (){
    factoring fact;
    int moreInput = 1;

    string n;
            std::ofstream file;
                            file.open("data.txt");

    do{
        if(std::cin >> n){
            if(n.size()>18){
                std::cout << "fail" << std::endl;
                std::cout << "\n";
                continue;
            }
        }
        else{
            break;
        }

        long long int number = stoll(n.c_str());
        std::cout << "IS NUMBER"<< number<< std::endl;


        // TODO: get all prime factors
        int nrOfTwoFactors = fact.divisor2(number); 
        //std::cout << "nrOfTwoFactors: " << nrOfTwoFactors << "\n" << std::endl;
        for(int i = 0; i < nrOfTwoFactors; i++){
            std::cout << "2" << std::endl;
        }
        if(number==1) continue;
        long long int factor = findPrimeFactor(number, fact);
        std::cout << factor << std::endl;
        int newNumber = number / factor;
        while((newNumber) != 1){
            if(newNumber%factor == 0){
                std::cout << factor << std::endl;
             //   file << factor << std::endl;
                newNumber = newNumber / factor;
            }else{
                factor = findPrimeFactor(newNumber, fact);
                std::cout << factor << std::endl;
              //  file << factor << std::endl;
                newNumber = newNumber / factor;
            }
        }
        std::cout << "\n";
    }while(1);
    file.close();
}