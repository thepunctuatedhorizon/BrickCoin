/*
 *
 * File: BrickCoin.h
 * Author: jtucker
 *
 * Created 1_4_17
 *
 */

#ifndef BRICKCOIN_H
#define BRICKCOIN_H

#include <string>
#include <stdio.h>

#include <mpir.h>
#include <mpirxx.h>

#include "openssl\sha.h"

#include "PTriples.h"
#include "EulerBrick.h"
#include "FNV.h"
#include "Multiplier.h"
#include "Node.h"


	class BrickCoin{
		public:
			//Constructor to construct the coin frokm a EulerBrick
			BrickCoin(EulerBrick brck);

			//Function to get the signature of the BrickCoin
			std::string getSignature();
		
			//Function to get the SHA512 hash of the BrickCoin
			std::string getHashSignature();

		private:
			
			//This variable holds the signature;
			std::string signature;

			//This variable holds the brick that was used to generate the BrickCoin
			EulerBrick brick;

			//This varible indicates whether the coin is valid and verifiable;
			bool didItVerify;
	};





#endif
