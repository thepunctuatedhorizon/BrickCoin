/*
 *
 * File: EulerBrick.h
 * Author: jtucker
 *
 * Created 12_30_16
 *
 */

#ifndef EULERBRICK_H
#define EULERBRICK_H

#include <mpir.h>
#include <mpirxx.h>
#include <string>
#include "PTriples.h"
#include "Path.h"


	class EulerBrick{

		public:
			//Empty Constructor Not to be used
			EulerBrick();

			//Proper Constructor, this constructor takes in two PTriples and two Path variables associated
			//    with the respective PTriples
			EulerBrick(PTriples fst, PTriples scnd, Path pth1, Path pth2);

			//This function returns true if the EulerBrick is perfect.
			bool isBrickPerfect();

			//This function returns true if the EulerBrick is primitive.
			bool isPrimitiveBrick(){return isPrimitive;}

			//TODO: IMPLEMENT THIS FUNCTION
			//Currently it will return a string of the decimal part of the spaceDiagonal.
			//What kind of "closeness" are we talking about?
			double isBrickClose();

			//TODO: turn this into a string!
			// This will print out (in future return a string) the signature of the brick.
			std::string print();

			//This function returns the shortest side into the the varable returnside
			void getShortestSide(mpz_t returnside);
			
			//This function returns the odd side to the variable returnside
			void getOddSide(mpz_t returnside);

			//These function returns the respective triples that were used to create this brick.
			PTriples getFirstPTriple();
			PTriples getSecondPTriple();

			//These functions return the respective paths that are associated with the PTriples.
			Path getPath1() { return pathFirst;}
			Path getPath2() { return pathSecond;}

			//These function output the side lengths as strings in base ten.
			std::string getA();
			std::string getB();
			std::string getC();

			//These functions output the side lengths to the provided mpz_t variable.
			void getAmpz(mpz_t result);
			void getBmpz(mpz_t result);
			void getCmpz(mpz_t result);
		
			//These function output the diagonal length as strings in base ten.
			std::string getDiagonalAB();
			std::string getDiagonalAC();
			std::string getDiagonalBC();

			//These functions output the diagonal lengths to the provided mpz_t variable.
			void getDiagonalABmpz(mpz_t result);
			void getDiagonalACmpz(mpz_t result);
			void getDiagonalBCmpz(mpz_t result);

			//Here you can get the FNV1a hashes of the sides
			uint32_t getHashA() {return hashA;}
			uint32_t getHashB() {return hashB;}
			uint32_t getHashC() {return hashC;}

			//Here you can get the FNV1a hashes of the Diagonals.
			uint32_t getHashDaigAB() {return hashDiagAB;}
			uint32_t getHashDaigAC() {return hashDiagAC;}
			uint32_t getHashDiagBC() {return hashDiagBC;}
		
		private:
			//This variable is used to store whether the Brick is perfect
			bool isPerfect;

			//TODO: Implement this in the code.
			//This variable is used to store whether the Brick is primitive
			bool isPrimitive;
		
			//This variable stores whether the brick initialized right
			bool isInitialized;
	
			//These path variables store the path info so that confimation can happen.
			Path pathFirst;
			Path pathSecond;

			//These PTriples store the pair of Pythagorean Triples that construct a Brick.
			PTriples first;
			PTriples second;

			//These MPZ_T variables store the length, width, and height respectively, of the Euler Brick
			mpz_t a;
			mpz_t b;
			mpz_t c;
		
			//These MPZ_T variables store the diagonals of the Euler Brick
			mpz_t diagonalAB;
			mpz_t diagonalAC;
			mpz_t diagonalBC;
			
			//This variables store the square of the space Diagonal 
			mpz_t spaceDiagonal2;

			//This variable will be zero unless there is a perfectSpaceDiagonal;
			mpz_t perfectSpaceDiagonal;

			//This variable stores the decimal approximation of the space Diagonal;
			mpf_t spaceDiagonal;

			//These variables store the FNV1a hash values of the various sides;
			uint32_t hashA;
			uint32_t hashB;
			uint32_t hashC;

			uint32_t hashA2;
			uint32_t hashB2;
			uint32_t hashC2;

			uint32_t hashDiagAB;
			uint32_t hashDiagAC;
			uint32_t hashDiagBC;
			
			//Checks to see if EulerBrick can be created.
			bool checkCanCreate;

			//Is the path verified for the brick
			bool pathVerified;
			

	};



#endif
