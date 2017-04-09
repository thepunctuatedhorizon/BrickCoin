/*
*
* File: BrickCoin.cpp
* Author: jtucker
*
* Created 1_4_17
*
*/


#include <stdio.h>

#include <mpir.h>
#include <mpirxx.h>

#include "openssl\sha.h"

#include "PTriples.h"
#include "EulerBrick.h"
#include "BrickCoin.h"
#include "EBVerify.h"
#include "FNV.h"
#include "Multiplier.h"
#include "Node.h"

BrickCoin::BrickCoin() {
	didItVerify = false;
	signature = "NOT VERIFIED";
}

BrickCoin::BrickCoin(EulerBrick brck, bool verified) {
	brick = brck;
	didItVerify = verified;
	signature = "Not Verified";

	//Required definition
	char mdString[SHA512_DIGEST_LENGTH * 2 + 1];

	if (didItVerify) {

		//Getting the Hash valuse converted to strings
		char hashA1[17];
		char hashB1[17];
		char hashC1[17];

		//Storing the string values of the hash
		std::snprintf(hashA1, sizeof(hashA1), "%x", brick.getHashA());
		std::snprintf(hashB1, sizeof(hashB1), "%x", brick.getHashB());
		std::snprintf(hashC1, sizeof(hashC1), "%x", brick.getHashC());

		//Signature generation
		//TODO: ACTUALLY MAKE THIS USEFUL!  WE NEED TO put them in order? l - g? All permutations?
		//TODO: Double SHA512 hashing? or just once?
		signature = "";
		signature = "<" + brick.getA() + "," + brick.getB() + "," + brick.getC() + ">\n";

		signature = signature + "<" + hashA1 + "," + hashB1 + "," + hashC1 + ">";

		signature = signature + getHashSignature() + "\n";
	}
	else {

		signature = "Coin Not Valid";
	}
}
BrickCoin::BrickCoin(EulerBrick brck) {

	//Storing the brick to the coin;
	brick = brck;

	//Initializing didItVerify to the false state to prevent invalid verifications;
	didItVerify = false;
	signature = "Not Verified";

	//Required definition
	char mdString[SHA512_DIGEST_LENGTH * 2 + 1];

	//Starting up the Verification process;
	EBVerify* verifier = new EBVerify(brick);

	//Recording what the verifier returns;
	didItVerify = (*verifier).didItVerify();

	if (didItVerify) {

		//Getting the Hash valuse converted to strings
		char hashA1[17];
		char hashB1[17];
		char hashC1[17];

		//Storing the string values of the hash
		std::snprintf(hashA1, sizeof(hashA1), "%x", brick.getHashA());
		std::snprintf(hashB1, sizeof(hashB1), "%x", brick.getHashB());
		std::snprintf(hashC1, sizeof(hashC1), "%x", brick.getHashC());

		//Signature generation
		//TODO: ACTUALLY MAKE THIS USEFUL!  WE NEED TO put them in order? l - g? All permutations?
		//TODO: Double SHA512 hashing? or just once?
		signature = "";
		signature = "<" + brick.getA() + "," + brick.getB() + "," + brick.getC() + ">\n";

		signature = signature + "<" + hashA1 + "," + hashB1 + "," + hashC1 + ">\n";
		signature = signature + getHashSignature() + "\n";
	}
	else {

		signature = "Coin Not Valid";
	}


}

std::string BrickCoin::getSignature() {
	return this->signature;
}



std::string BrickCoin::getHashSignature() {

	//Required definition
	char mdString[SHA512_DIGEST_LENGTH * 2 + 1];

	//Only proceed if it verified.
	if (didItVerify) {

		//Turning the signature into unsigned chars
		size_t ss = signature.length();
		unsigned char* data = new unsigned char[ss];

		strncpy((char *)data, signature.c_str(), ss);
		data[ss] = '\0';


		//Initializing the hash
		unsigned char hash[SHA512_DIGEST_LENGTH];

		//Hashing and then storing to the hash variable
		SHA512(data, sizeof(data), hash);


		// Converting the hash value to hex
		for (int i = 0; i < SHA512_DIGEST_LENGTH; i++) {
			std::sprintf(&mdString[i * 2], "%02x", (unsigned int)hash[i]);
		}

	}
	else {
		std::string mdString = "Coin Not Valid";
	}

	//Returing the resulting signature string;
	return mdString;
}
