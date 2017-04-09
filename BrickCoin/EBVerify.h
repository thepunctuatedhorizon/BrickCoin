/*
 *
 * File: EBVerify.h
 * Author: jtucker
 *
 * Created 1_4_17
 *
 * Purpose: To verify that given objects are truly primitive Euler Bricks, truly BrickCoins, or truly the signatures of a valid BrickCoin.
 *
 */

#ifndef EBVERIFY_H
#define EBVERIFY_H

#include <mpir.h>
#include <mpirxx.h>
#include <string>
#include "PTriples.h"
#include "Path.h"
#include "EulerBrick.h"
#include "BrickCoin.h"

	class EBVerify{
		public:

			//Empty constructor, not to be used;
			EBVerify();

			//The constructor used to verify a Euler Brick is valid;
			EBVerify(EulerBrick brick);

			//The constructor used to verify a BrickCoin is valid;
			EBVerify(BrickCoin coin);

			//The constructor used to verify if a signature of a BrickCoin is valid;
			EBVerify(std::string coin);
		

			//This function returns true only if the verification process worked;
			bool didItVerify();

			BrickCoin getCoin() {
				return coin;
			}

		private:

			//This variable is used to store whether the Brick is perfect
			bool isPerfect;

			//TODO: Implement this in the code.
			//This variable is used to store whether the Brick is primitive
			bool isPrimitive;
	
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


			//This variable store whether the brick verified
			bool verified;
			
			//This variable stores whether the brick path was verified.
			bool pathVerified;

			//This variable stores whether the brick was initialized properly.
			bool isInitialized;

			BrickCoin coin;


	};




#endif
