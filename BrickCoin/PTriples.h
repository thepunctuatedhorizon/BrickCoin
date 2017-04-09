/*
* File: PTriples.h
* Author: jtucker
*
* Created on 12_13_16
*/

#ifndef PTRIPLES_H
#define PTRIPLES_H


#include <stdio.h>
#include <string>
#include <iostream>
#include <mpir.h>
#include <mpirxx.h>

//This class is the fundamental class.
//The object PTriples is a pythagorean triple and it is initialized in such a way that it
// should be primitive... That is the gcd = 1;
class PTriples
{
	public:
		//This constructor will initialize the root PTriple.
        	PTriples();
        
		//This constructor will initialize a PTriple given three MPZ_T inputs
        	PTriples(mpz_t &nA, mpz_t &nB, mpz_t &nC);

		//To use these get functions, you MUST supply an Instantiated and INITIALIEZED MPZ_T
		//   that you wish to receive the output in.
        	void getA(mpz_t& result){  mpz_set(result, a);}
        	void getB(mpz_t& result){  mpz_set(result, b);}
        	void getC(mpz_t& result){  mpz_set(result, c);}

		//This is a simple printing out function of the Pythagorean triple
        	std::string printOutTriple();
	
		//This function will return true if the GCD is unity.
		bool isGCDunity();
	
		//Get the FNV1a hash of the MPZ_T sides and hypotenuse
		uint32_t getAHash(){ return ha;}
		uint32_t getBHash(){ return hb;}
		uint32_t getCHash(){ return hc;}


	private:
		//The first side of the pythagorean Triple
        	mpz_t a;
		//The second side of the pythagorean Triple
       		mpz_t b;
		//The hypotenuse of the pythagorean Triple
		//Note: a^2 + b^2 == c^2
        	mpz_t c;

		//The hash variables for their respective sides.
		uint32_t ha;
		uint32_t hb;
		uint32_t hc;

};

#endif
