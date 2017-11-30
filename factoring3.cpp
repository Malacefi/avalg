// Authors: Emelie Eriksson , Marcus Lignercrona & Julien Adler
#include <iostream>
#include <fstream>
#include <string>
#include <stdlib.h>
#include <math.h>
#include <gmp.h>
#include <vector>
//using namespace std;

class factoring{
    public:
        long long int factorBaseLimit(long long int n){
            return ceil(2*exp((sqrt(log(n)*log(log(n))))/4));
        }
      /*  void factorBase(std::vector<long long int> factorbase,long long int limit.){
            for(int i = 3;  ){

            }
        }*/
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
                 a = 2 + (rand() % ((number -1)- 2 + 1));
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
        void sieve(long long int n){
            
        }


};
void newPollard(mpz_t input,mpz_t output){
    if(!mpz_cmp_ui(input,1)){
        return;
    }
    srand (time(NULL));
    mpz_t x,y,a,random;
    gmp_randstate_t state;
    gmp_randinit_default(state);
    mpz_inits(x,y,a,random);

    mpz_urandomb(random,state,100);
    mpz_mod(x,random,input);
    mpz_add_ui(x,x,3);

    mpz_set(y,x);

    mpz_urandomb(random,state,100);
    mpz_mod(a,random,input);
    mpz_add_ui(a,a,3);

    mpz_t currentgcd;
    mpz_set_str(currentgcd,"1",0);
    while(!mpz_cmp_ui(input,1)){
        //turtle
        mpz_mul(x,x,x);
        mpz_add(x,x,a);
        mpz_mod(x,x,input);
        //hare
        mpz_mul(y,y,y);
        mpz_add(y,y,a);
        mpz_mod(y,y,input);

        mpz_mul(y,y,y);
        mpz_add(y,y,a);
        mpz_mod(y,y,input);

        mpz_gcd(currentgcd,x,y);
    }
    mpz_set(output,currentgcd);
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
void newFindPrimeFactor(mpz_t input,mpz_t output){
    mpz_t foundFactor;
    mpz_init(foundFactor);
    while(!mpz_probab_prime_p(foundFactor,15)){
        newPollard(input, foundFactor);
    }
    mpz_set(output,foundFactor);
    return;
}

int main (){
    factoring fact;
    int moreInput = 1;

    std::string n;
    std::ofstream file;
    file.open("data.txt");
    unsigned long earlyPrimes[] = {2,3,5,7,11,13,17,19,23,29,31,37,41,43,47,53,59,61,67,71,73,79,83,89,97,101,103,107,109,113};
    do{
        mpz_t input;
        if(std::cin >> n){
            mpz_init(input);
            mpz_set_str(input,n.c_str(),0);
        }
        else{
            break;
        }
        std::vector<std::string> primes; 
        //OBSERVERA INTE BOOLSK HAR 3 VÄRDEN!
        //Magic number of trial division primes
        for(int i = 0;i< 30;++i){
            while(mpz_divisible_ui_p(input,earlyPrimes[i])){
                mpz_divexact_ui(input,input,earlyPrimes[i]);
                primes.push_back(std::to_string(earlyPrimes[i]));
            }
        }
        mpz_t factor;
        mpz_init(factor);
        while(mpz_cmp_ui(input,1)>0){
            newFindPrimeFactor(input,factor);
            do{
                mpz_divexact(input,input,factor);
                char * temp = mpz_get_str(temp,10,factor);
                primes.push_back(temp);
            }while(mpz_divisible_p(input,factor));
        }
        //last check if the last factor is prime or = 1
        /*if(mpz_probab_prime_p(input,15)){
            char * temp = mpz_get_str(temp,10,input);
            primes.push_back(temp);
            for(std::vector<std::string>::iterator it = primes.begin(); it !=primes.end();++it){
                std::cout << *it << "\n";
            }
        }*/
        if(!mpz_cmp_ui(input,1)){
            for(std::vector<std::string>::iterator it = primes.begin(); it !=primes.end();++it){
                std::cout << *it << "\n";
            }
        }
        else{
            std::cout << "fail \n";
        }
        /*
        long long number = 0;
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
        */
        std::cout << "\n";
    }while(1);
    file.close();
}