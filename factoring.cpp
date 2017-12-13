// Emelie Eriksson, Julien Adler, Marcus Lignercrona
#include <iostream>
#include <fstream>
#include <string>
#include <stdlib.h>
#include <math.h>
#include <gmp.h>
#include <vector>

void pollard(mpz_t input,mpz_t output){
	// If N is 1, end immedietly
    if(!mpz_cmp_ui(input,1)){
        return;
    }

    /* Initializing */
    mpz_t x,y,a,random;
    gmp_randstate_t state;
    gmp_randinit_default(state);

    mpz_init(x);
    mpz_init(y);
    mpz_init(a);
    mpz_init(random);
    /* Initializing done */

    // Generate a random number
    mpz_urandomb(random,state,100);

    mpz_mod(x,random,input);
    mpz_add_ui(x,x,3);

    mpz_set(y,x);

    mpz_urandomb(random,state,100);
    mpz_mod(a,random,input);
    mpz_add_ui(a,a,3);

    mpz_t currentgcd;
    mpz_init(currentgcd);
    mpz_set_str(currentgcd,"1",0);

    int numberOfAtempts = 0;
    // We do a maximum number of 430000 attempts
    // If it can't find a factor within 430000 attemts then it will take too long
    while(!mpz_cmp_ui(currentgcd,1) && numberOfAtempts < 430000){
        numberOfAtempts++;
        
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

        //new gcd
        mpz_sub(currentgcd,x,y);
        mpz_abs(currentgcd,currentgcd);
        mpz_gcd(currentgcd,currentgcd,input);

    }
    mpz_set(output,currentgcd);
    if(numberOfAtempts>429998) mpz_set_si(output,-1);
};

/* This is a function for finding a prime factor by running Pollard 
	until find a factor that we determine, with Miller's, is a prime*/
void findPrimeFactor(mpz_t input,mpz_t output){
    mpz_t foundFactor;
    mpz_init(foundFactor);
    while(mpz_probab_prime_p(foundFactor,15)==0){
    	// Run pollard 
        pollard(input, foundFactor);
        // While the factor is not a prime
        // Keep factoring it
        if(!mpz_cmp_si(foundFactor,-1))break; 
    }
    mpz_set(output,foundFactor);
    return;
}

int main (){
    int moreInput = 1;

    std::string n;
    std::ofstream file;
    file.open("data.txt");

    // We check if any of the first 30 prime numbers are factors to speed up program
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
        if(mpz_probab_prime_p(input,15)){
            char * temp = mpz_get_str(nullptr,10,input);
            std::string tempura(temp);
            primes.push_back(tempura);
            mpz_divexact(input,input,input);
        }
        else if(mpz_cmp_ui(input,1)){
            mpz_t factor;
            mpz_init(factor);
            while(mpz_cmp_ui(input,1)){
                findPrimeFactor(input,factor);
                if(!mpz_cmp_si(factor,-1)){
                    char * temp3 = mpz_get_str(nullptr,10,input);
                    std::string tempura(temp3);
                    //std::cout << "shoudl fail cuz value is" << tempura << "\n";
                    break;
                } 
                do{
                    mpz_divexact(input,input,factor);
                    char * temp = mpz_get_str(nullptr,10,factor);
                    std::string tempura(temp);
                    primes.push_back(tempura);
                }while(mpz_divisible_p(input,factor));
            }
        }
        // Last check if the last factor is prime or = 1
        if(!mpz_cmp_ui(input,1)){
            for(std::vector<std::string>::iterator it = primes.begin(); it !=primes.end();++it){
                std::cout << *it << "\n";
            }
        }
        else{
            std::cout << "fail \n";
        }
        std::cout << "\n";
    }while(1);
    file.close();
}