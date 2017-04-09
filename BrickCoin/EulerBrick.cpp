/*
 *
 * File: EulerBrick.cpp
 * Author: jtucker
 *
 * Created 12_30_16
 *
 */


#include <stdio.h>
#include <mpir.h>
#include <mpirxx.h>
#include <string>
#include <ostream>
#include <iostream>
#include <sstream>
#include <fstream>

#include "PTriples.h"
#include "EulerBrick.h"
#include "SearchFunctions.h"

EulerBrick::EulerBrick(){}

//The proper constructor. This constructor takes in two PTriples and two Path variables associated
//    with the respective PTriples
EulerBrick::EulerBrick(PTriples fst, PTriples scnd, Path pth1, Path pth2){

	//Storing input information to the correct variables
	first = fst;
	second = scnd;
	pathFirst = pth1;
	pathSecond =pth2;
	checkCanCreate = false;
	isInitialized = false;
	isPerfect = false;
	

	//TODO: How do we prevent <a,b,c> brick = <b, c, a> brick = <c, a, b> etc.?
	//First, if <a,b,c> is a brick, then <b,a,c> will be too.


	//The initialization of the MPZ_T intermediates
	mpz_t temp1, temp2, temp3, temp4;
	mpz_t diagT1, diagT2, zero, one;

	mpz_init_set_str(a, "0", 10);
	mpz_init_set_str(b, "0", 10);
	mpz_init_set_str(c, "0", 10);

	mpz_init_set_str(diagonalAB, "0", 10);
	mpz_init_set_str(diagonalAC, "0", 10);
	mpz_init_set_str(diagonalBC, "0", 10);
	
	mpz_init_set_str(spaceDiagonal2, "0", 10);
	mpz_init_set_str(perfectSpaceDiagonal, "0", 10);
	mpf_init_set_str(spaceDiagonal, "0", 10);

	mpz_init_set_str(temp1, "0", 10);
	mpz_init_set_str(temp2, "0", 10);
	mpz_init_set_str(temp3, "0", 10);
	mpz_init_set_str(temp4, "0", 10);
	mpz_init_set_str(diagT1, "0", 10);
	mpz_init_set_str(diagT2, "0", 10);
	mpz_init_set_str(zero, "0",10);
	mpz_init_set_str(one, "1", 10);

	//We must find the correct order in which to store a, b, c
	first.getA(temp1);
	first.getB(temp2);
	second.getA(temp3);
	second.getB(temp4);

	//This function finds where there are any sides equal 
	int whereE = SearchFunctions::HashEqualsAny(first, second);

	//This structure should not encounter whereE==0. This is a logic error, or improper inputs were provided.
	//TODO: implement the try throw catch correctly!
	//In this try structure, we don't want to initialize any further if the brick doesn't work
	if (whereE == 0){
		//TODO: PROPERLY HANDLE THE ERROR
		std::cout << "ERROR" << std::endl;
	} else if (whereE == 1 || whereE ==3){
			//If whereE ==1 or ==3, the first PTriples can be used for a and b. But only the second value
			//  of the second PTriples can be used (as the first would be equal to a or b from the first PTriples)
		try{
			mpz_set(a, temp1);
			mpz_set(b, temp2);
			mpz_set(c, temp4);
			
			//The AB and BC diagonals can just be read from the third side of each Triangle
			first.getC(diagonalAB);
			second.getC(diagonalBC);

			//Diagonal AC need's to be calculated.
			mpz_set(temp3, zero);
			mpz_set(temp2, zero);
			mpz_mul(temp3, temp1, temp1);
			mpz_mul(temp2, temp4, temp4);
			mpz_add(diagT1, temp2, temp3);
			//This function tests to see if the number is square rootable.
			int sqrtable = mpz_perfect_square_p(diagT1);
	
			//Only if the diagonal is a perfect square can we move on.
			if (sqrtable > 0){
				mpz_root(diagonalAC, diagT1, 2);
			} else { // We need to stop the execution
				std::cout << "ERROR, NOT ROOTABLE" << std::endl;
				throw 10;
			}
		
			//Corresponding hash values are calculated
			
			hashA = FNV::fnv1aHashOfMpz_t(a);
			hashB = FNV::fnv1aHashOfMpz_t(b);
			hashC = FNV::fnv1aHashOfMpz_t(c);
			hashDiagAB = FNV::fnv1aHashOfMpz_t(diagonalAB);
			hashDiagAC = FNV::fnv1aHashOfMpz_t(diagonalAC);
			hashDiagBC = FNV::fnv1aHashOfMpz_t(diagonalBC);
			
			checkCanCreate = true;
	
		} catch (int e) { //TODO: FIX THIS TO WORK PROPERLY
			checkCanCreate = false;
			std::cout << "caught the trown int "  << e << std::endl;
		}


	} else if (whereE == 2|| whereE ==4){
		//If whereE ==2 or ==4, the first PTriples can be used for a and b. But only the first value
		//  of the second PTriples can be used (as the second would be equal to a or b from the first PTriples)
		try {
			mpz_set(a, temp1);
			mpz_set(b, temp2);
			mpz_set(c, temp3);

			//The AB and BC diagonals can just be read from the third side of each PTriples
			first.getC(diagonalAB);
			second.getC(diagonalBC);

			//Diagonal AC need's to be calculated.
			mpz_set(temp2, zero);
			mpz_set(temp4, zero);
			mpz_mul(temp2, temp1, temp1);
			mpz_mul(temp4, temp3, temp3);
			mpz_add(diagT2, temp2, temp4);

			//This function tests to see if the number is square rootable.
			int sqrtable = mpz_perfect_square_p(diagT2);
	
			//Only if the diagonal is a perfect square can we move on.
			if (sqrtable > 0){
				mpz_root(diagonalAC, diagT2, 2);
			} else {// We need to stop the execution
				std::cout << "ERROR, NOT ROOTABLE" << std::endl;
				throw 20;
			}
			
			//FNV1a Hash values are extracted.
			hashA = FNV::fnv1aHashOfMpz_t(a);
			hashB = FNV::fnv1aHashOfMpz_t(b);
			hashC = FNV::fnv1aHashOfMpz_t(c);
			hashDiagAB = FNV::fnv1aHashOfMpz_t(diagonalAB);
			hashDiagAC = FNV::fnv1aHashOfMpz_t(diagonalAC);
			hashDiagBC = FNV::fnv1aHashOfMpz_t(diagonalBC);
		
			checkCanCreate = true;

		} catch (int e) { 
			//TODO: FIX THIS!
			checkCanCreate = false;
			std::cout << "caught the trown int " << e << std::endl;
		}
	}
	if (checkCanCreate) {
		//Here we reset the variables used so we can calc the space diagonal.
		mpz_set(temp1, zero);
		mpz_set(temp2, zero);
		mpz_set(temp3, zero);
		mpz_set(temp4, zero);
		mpz_set(diagT1, zero);
		mpz_set(diagT2, zero);	
	
		mpz_mul(temp1, a, a);
		mpz_mul(temp2, b, b);
		mpz_mul(temp3, c, c);

		mpz_add(temp4, temp1, temp2);
		mpz_add(spaceDiagonal2, temp4, temp3);

		//This checks to see if the space diagonal is a perfect square.
		int spaceDiag = mpz_perfect_square_p(spaceDiagonal2);
		if (spaceDiag>0) { 
			//If the space diagonal is a perfect square
			isPerfect = true;
			mpz_root( perfectSpaceDiagonal, spaceDiagonal2, 2);
			//TODO: We want to send this information to me.  How do I do that?
			//Right now, all that happens is a perfectSpaceDiagonal is printed to the output.
			mpz_out_str(stdout, 10, perfectSpaceDiagonal);
		} else {
			//If the space diagonal is not a perfect square, the approximation is calculated.
			isPerfect = false;
			//The precision is to a hundred decimal places? I guess?
			mpf_set_default_prec(100);
			mpf_t spD;
			mpf_init(spD);
			mpf_init(spaceDiagonal);
			mpf_set_z(spD, spaceDiagonal2);
	
			mpf_sqrt(spaceDiagonal, spD);
		}

		//Here we figure out if the path is correct 
		PTriples fst = SearchFunctions::createFromPath(pathFirst);
		PTriples snd = SearchFunctions::createFromPath(pathSecond);
	

		//This is where we check if the path generated triples and the provided triples are the same;
		bool firstCheck = SearchFunctions::HashAllEquals(first, fst);
		bool secondCheck = SearchFunctions::HashAllEquals(second, snd);
		
		//Only if both checks are true can we give a path verified 
		if ( firstCheck && secondCheck){
			pathVerified = true;
		}

		//We don't have the path fully set up yet.
		//TODO: remove from production code.
		pathVerified = true;
	}

	//Next, we would like to check if the pathVerified and that we can create the Brick.
	if (pathVerified && checkCanCreate){
		//If both checks are satisfied, the brick is initialized. 
		isInitialized = true;

		//The Greatest Common Divisor must be calculated to determine if it is primitive;
		//Initializing the three temp variables;
		mpz_t prim1, prim2, prim3, one;
		mpz_init_set_str(prim1, "-1", 10);
		mpz_init_set_str(prim2, "-1", 10);
		mpz_init_set_str(one, "1", 10);

		//Calculating the gcd of each pair.
		mpz_gcd(prim1, a, b);
		mpz_gcd(prim2, prim1, c);

		//Now we check to see if the gcd is more than one.
		int gcd2 = mpz_cmp(prim2, one);


		if (gcd2 == 0){
			isPrimitive = true;
		}
	}
}

//
std::string EulerBrick::print(){
	std::string returnValue;
	returnValue = "This Brick has the following signatures\n<";
	

	returnValue = returnValue + mpz_get_str(NULL, 10, a);
	returnValue = returnValue + ", ";
	returnValue = returnValue + mpz_get_str(NULL, 10, b);
	returnValue = returnValue + ", ";
	returnValue = returnValue + mpz_get_str(NULL, 10, c);
	returnValue = returnValue + ">\n" + "DiagonalAB: ";
	returnValue = returnValue + mpz_get_str(NULL, 10, diagonalAB);
	returnValue = returnValue + "\nDiagonalAC: ";
	returnValue = returnValue + mpz_get_str(NULL, 10, diagonalAC);
	returnValue = returnValue + "\nDiagonalBC: ";
	returnValue = returnValue + mpz_get_str(NULL, 10, diagonalBC);
	returnValue = returnValue + "\nHashs: <";

	std::stringstream stream;
	stream << std::hex << hashA << ", ";
	stream << hashB << ", " << hashC ;
	stream << ">" << std::endl;

	
	stream << "Space diagonal ";
	if (isPerfect){ 
		stream << "IS a perfect Brick" << std::endl;
		stream <<  "It does have a space diagonal of: ";
		stream << mpz_get_str(NULL, 10, perfectSpaceDiagonal);
		stream << std::endl;
	}
	else{ 
		stream << "is NOT ";
		stream << "a perfect Brick" << std::endl;
		stream << "Even though it wasn't a perfect brick," << std::endl;
		stream <<  "it does have a space diagonal of: ";
		long lng = 1L;
		long * lngp;
		lngp = &lng;
		char * res;
		//FIX THIS SO IT GIVE THE DECIMAL!
		res = mpf_get_str(NULL, lngp, 10, 0, spaceDiagonal);
		stream << res << std::endl;
	}
	returnValue = returnValue + stream.str();
	
	return returnValue;
}

double EulerBrick::isBrickClose(){

	mpf_t spDiP, spDdP;
	mpf_init(spDiP);
	mpf_init(spDdP);
	mpf_trunc(spDiP, spaceDiagonal);
	mpf_sub(spDdP,spaceDiagonal,spDiP);
	return mpf_out_str(NULL, 10, 0, spDdP);
}


PTriples EulerBrick::getFirstPTriple(){

	return first;

}

PTriples EulerBrick::getSecondPTriple() {

	return second;

}

//These function output the side lengths as strings in base ten.
std::string EulerBrick::getA(){
	return mpz_get_str(NULL, 10, a);
}

std::string EulerBrick::getB(){
	return mpz_get_str(NULL, 10, b);
}

std::string EulerBrick::getC(){
	return mpz_get_str(NULL, 10, c);
}

//These functions output the side lengths to the provided mpz_t variable.
void EulerBrick::getAmpz(mpz_t result){
	mpz_set(result, a);
}

void EulerBrick::getBmpz(mpz_t result){
	mpz_set(result, b);
}

void EulerBrick::getCmpz(mpz_t result){
	mpz_set(result, c);
}
		
//These functions output the diagonal lengths to the provided mpz_t variable.
void EulerBrick::getDiagonalABmpz(mpz_t result){
	mpz_set(result, diagonalAB);
}

void EulerBrick::getDiagonalACmpz(mpz_t result){
	mpz_set(result, diagonalAC);
}

void EulerBrick::getDiagonalBCmpz(mpz_t result){
	mpz_set(result, diagonalBC);
}

//These function output the diagonal length as strings in base ten.		
std::string EulerBrick::getDiagonalAB(){
	return mpz_get_str(NULL, 10, diagonalAB);
}

std::string EulerBrick::getDiagonalAC(){
	return mpz_get_str(NULL, 10, diagonalAC);
}

std::string EulerBrick::getDiagonalBC(){
	return mpz_get_str(NULL, 10, diagonalBC);
}

void EulerBrick::getOddSide(mpz_t returnside){

	int oddA = mpz_odd_p(a);
	int oddB = mpz_odd_p(b);
	int oddC = mpz_odd_p(c);

	if (oddA == 0 && oddB == 0 && oddC != 0){
		mpz_set(returnside, c);
	}
	if (oddA == 0 && oddB != 0 && oddC == 0){
		mpz_set(returnside, b);
	}
	if (oddA != 0 && oddB == 0 && oddC == 0){
		mpz_set(returnside, a);
	}
}

void EulerBrick::getShortestSide(mpz_t returnside){

	int aTOb = mpz_cmp(a,b);
	int aTOc = mpz_cmp(a,c);
	int bTOc = mpz_cmp(b,c);

	if (aTOb > 0 && aTOc > 0 && bTOc > 0){
		mpz_set(returnside,c);
	}
	if (aTOb < 0 && aTOc > 0 && bTOc > 0){
		mpz_set(returnside,c);
	}
	if (aTOb < 0 && aTOc < 0 && bTOc > 0){
		mpz_set(returnside, a);
	}
	if (aTOb < 0 && aTOc < 0 && bTOc < 0) {
		mpz_set(returnside, a);
	}
	if (aTOb > 0 && aTOc > 0 && bTOc < 0) {
		mpz_set(returnside, b);
	}
	if ( aTOb >0 && aTOc < 0 && bTOc < 0) {
		mpz_set(returnside, b);
	}
}






