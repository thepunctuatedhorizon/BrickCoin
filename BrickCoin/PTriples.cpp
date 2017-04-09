/* File: ptriples.cpp
* Author: jtucker
*
* Created 12_13_16
*/

#include <stdio.h>
#include <iostream>
#include <mpir.h>
#include <mpirxx.h>

#include "PTriples.h"
#include "FNV.h"

//Default constructor will create the Root of the pythagorean tree
PTriples::PTriples(){

	//Initializing and setting the MPZ_T variables
	mpz_init_set_str (a,"3",10);
	mpz_init_set_str (b,"4",10);
	mpz_init_set_str (c,"5",10);
	
	//Finding the FNV1a Hash of the above MPZ_T variables
	ha = FNV::fnv1aHashOfMpz_t(a);
	hb = FNV::fnv1aHashOfMpz_t(b);
	hc = FNV::fnv1aHashOfMpz_t(c);	
 
}

//Constructor. Inputs three MPZ_T variables
//  The first two sides ( a, b ) and the hypotenuse ( c ) (should) form a pythagorean triple
//  No error checking is implemented here as this object will be required 3^n times for n levels
//  of the primitive pythagorean triples tree generated in this program.
//  Warning, do not utilize anything other than primitive pythagorean triples.  All discoveries will 
//  be derivatives of the primitive blocks and no value is to be found in these derivative cases.
PTriples::PTriples(mpz_t & nA, mpz_t & nB, mpz_t & nC){

	// MPZ_T variables must be initialized and set to a value before usage.
	mpz_init_set_str(a, "0", 10);
	mpz_init_set_str(b, "0", 10);
	mpz_init_set_str(c, "0", 10);

	//Setting the PTriples sides.
	mpz_set(a, nA);
	mpz_set(b, nB);
	mpz_set(c, nC);	

	//Obtaining the proper hashes. 
	ha = FNV::fnv1aHashOfMpz_t(a);
	hb = FNV::fnv1aHashOfMpz_t(b);
	hc = FNV::fnv1aHashOfMpz_t(c);

}



//This simple function outputs the triple as a three element vector containing the sides of the
//  PTriple.
std::string PTriples::printOutTriple() {

	std::string s ="<";
	s = s + mpz_get_str(NULL, 10, a);
	s = s + ", " + mpz_get_str(NULL, 10, b);
	s = s + ", " + mpz_get_str(NULL, 10, c);
	s = s + ">";
	return s;
}



