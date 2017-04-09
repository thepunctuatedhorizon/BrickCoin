/*
 *
 * File: EBVerify.cpp
 * Author: jtucker
 *
 * Created 1_4_17
 *
 */


#include <stdio.h>
#include <mpir.h>
#include <mpirxx.h>

#include "PTriples.h"
#include "EulerBrick.h"
#include "SearchFunctions.h"
#include "EBVerify.h"
#include "BrickCoin.h"


//Empty Constructor 
//This should not be used
EBVerify::EBVerify(){
	// If used, it is very important to ensure the verified flag is set false
	verified = false;
}


//The primary verification constructor, requires a EulerBrick to be provided.  The
//  brick is then analized by the constructor code and deemed to be valid or invalid
EBVerify::EBVerify(EulerBrick brick) {

	//The initialization of all variables
	first = brick.getFirstPTriple();
	second = brick.getSecondPTriple();
	pathFirst = brick.getPath1();
	pathSecond = brick.getPath2();
	verified = false;
	pathVerified = false;
	bool checkCanCreate = false;
	isInitialized = false;

	
	//The initialization of the MPZ_T intermediates
	mpz_t temp1, temp2, temp3, temp4;
	mpz_t diagT1, diagT2, zero, one;
	mpz_init_set_str(temp1, "0", 10);
	mpz_init_set_str(temp2, "0", 10);
	mpz_init_set_str(temp3, "0", 10);
	mpz_init_set_str(temp4, "0", 10);
	mpz_init_set_str(diagT1, "0", 10);
	mpz_init_set_str(diagT2, "0", 10);
	mpz_init_set_str(zero, "0",10);
	mpz_init_set_str(one, "1", 10);

	//Extracting the sidelengths form the PTriples
	first.getA(temp1);
	first.getB(temp2);
	second.getA(temp3);
	second.getB(temp4);

	//This call finds out where the equal side of the PTriples lies.
	int whereE = SearchFunctions::HashEqualsAny(first, second);

	//This if structure should never encounter whereE == 0. 
	if (whereE == 0){
		std::cout << "ERROR" << std::endl;
	} else if (whereE == 1 || whereE ==3){

		//TODO: implement the try throw catch correctly!
		//In this try structure, we don't want to initialize any further if the brick doesn't work
		try{
			//If whereE ==1 or ==3, the first PTriples can be used for a and b. But only the second value
			//  of the second PTriples can be used (as the first would be equal to a or b from the first PTriples)
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
			} else {   // We need to stop the execution
				std::cout << "ERROR, NOT ROOTABLE" << std::endl;
				throw 10;
			}
			
			//Corresponding hash values are calclated
			hashA = FNV::fnv1aHashOfMpz_t(a);
			hashB = FNV::fnv1aHashOfMpz_t(b);
			hashC = FNV::fnv1aHashOfMpz_t(c);
			hashDiagAB = FNV::fnv1aHashOfMpz_t(diagonalAB);
			hashDiagAC = FNV::fnv1aHashOfMpz_t(diagonalAC);
			hashDiagBC = FNV::fnv1aHashOfMpz_t(diagonalBC);

			checkCanCreate = true;

		} catch (int e) { 
			//TODO: FIX THIS TO WORK PROPERLY
			checkCanCreate = false;
			std::cout << "caught the trown int "  << e << std::endl;
		}


	} else if (whereE == 2|| whereE ==4){
		try {
			//If whereE ==2 or ==4, the first PTriples can be used for a and b. But only the first value
			//  of the second PTriples can be used (as the second would be equal to a or b from the first PTriples)
			mpz_set(a, temp1);
			mpz_set(b, temp2);
			mpz_set(c, temp3);

			//The AB and BC diagonals can just be read from the third side of each PTriples
			first.getC(diagonalAB);
			second.getC(diagonalBC);

			//Diagonal AC need's to be calculated.
			mpz_set(temp3, zero);
			mpz_set(temp1, zero);
			mpz_mul(temp3, temp2, temp2);
			mpz_mul(temp1, temp4, temp4);
			mpz_add(diagT2, temp1, temp3);

			//This function tests to see if the number is square rootable.
			int sqrtable = mpz_perfect_square_p(diagT2);
	
			//Only if the diagonal is a perfect square can we move on.
			if (sqrtable > 0){
				mpz_root(diagonalAC, diagT2, 2);
			} else { // We need to stop the execution
				std::cout << "ERROR, NOT ROOTABLE" << std::endl;
				throw 20;
			}
			
			//Corresponding hash values are extracted
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
	
	if (checkCanCreate){

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

		//Next, we would like to check if the pathVerified and that we can create the Brick.
		if (pathVerified && checkCanCreate){
			//If both checks are satisfied, the brick is initialized. 
			//TODO: do you really need this?
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

	// TODO: Get proper paths initiated for test bricks
	//This is here only to circumvent the proper testing until I figure out how to generate the proper paths
	// WARNING: THIS MUST NOT be in the final code.
	pathVerified = true;
	

	if (pathVerified && brick.getHashA() == hashA && brick.getHashB() == hashB && brick.getHashC() == hashC)
	{
		//TODO: what else? Certainly we don't want this output, but it's for testing purposes.
		verified = true;
		//(*coin) = BrickCoin(brick);
		std::cout << "This is a match." << std::endl;
	}

}


//This function will report the validity of the input. When an EBVerify is created, the 
//  constructors will evaluate the given input and set the verified flag.
//  Only verified EulerBricks, BrickCoins, or string input of a signature will allow this to be set true.
bool EBVerify::didItVerify(){
	return verified;
}


//The primary verification constructor, requires a BrickCoin to be provided.  The
//  brickcoin is then analized by the constructor code and deemed to be valid or invalid



EBVerify::EBVerify(BrickCoin coin){

	//Getting the signatures from the BrickCoin
	std::string parseString = coin.getSignature();
	
	std::string SHA512hash = coin.getHashSignature();

	//TODO: MUST MAKE THIS INPUT RESISTANT!!!
	
	//Setting up the parse mechanism.
	char * parseChar = new char[parseString.length() + 1];
	strcpy(parseChar, parseString.c_str());
	
	//The parsed string cutting mechanism
  	char * pch;
   	//Where the parsed strings are stored
	std::vector<std::string> token;

	//The parsing mechanism
  	pch = strtok (parseChar,"<,>");
	std::string temp = pch;
	token.push_back(temp);
  	while (pch != NULL)
  	{
    		pch = strtok (NULL, "<,>");
		if(pch == NULL){ break;}
		std::string temp = pch;
		token.push_back(temp);
  	}


	//Convering the parsed string back into const chars to be put into the MPZ_T variables
	const char * aString = token[0].c_str();
	const char * bString = token[1].c_str();
	const char * cString = token[2].c_str();
	//std::string aHashString = token[3];
	//std::string bHashString = token[4];
	//std::string cHashString = token[5];

	//Initializing MPZ_T variables so that a EulerBrick can be constructed.
	mpz_t aAA, bBB, cCC, ab, bc, a2, b2, c2, temp1, temp2;
	mpz_init_set_str(aAA, aString, 10);
	mpz_init_set_str(bBB, bString, 10);
	mpz_init_set_str(cCC, cString, 10);
	mpz_init_set_str(ab, "0", 10);
	mpz_init_set_str(bc, "0", 10);
	mpz_init_set_str(a2, "0", 10);
	mpz_init_set_str(b2, "0", 10);
	mpz_init_set_str(c2, "0", 10);
	mpz_mul(a2, aAA, aAA);
	mpz_mul(b2, bBB, bBB);
	mpz_mul(c2, cCC, cCC);
	mpz_init_set_str(temp1, "0", 10);
	mpz_init_set_str(temp2, "0", 10);
	mpz_add(temp1, a2, b2);
	mpz_add(temp2, b2, c2);
	
	//Calculating the requisite hypotenuse for the PTriples
	mpz_sqrt(ab, temp1);
	mpz_sqrt(bc, temp2);
	
	//Initializing the PTriples to hold the calculated values
	PTriples * firstTriple = new PTriples(aAA, bBB, ab);
	PTriples * secondTriple = new PTriples(bBB, cCC, bc);

	//TODO: IMPLEMENT PATH FINDER or just pass the paths data through
	Path p1, p2;
	
	//Generating the EulerBrick so it can be verified by the first constructor seen above.
	EulerBrick* generated = new EulerBrick((*firstTriple), (*secondTriple), p1, p2);

	//Initializing another EBVerifier to use the newly generated EulerBrick
	EBVerify* verifyThis = new EBVerify((*generated));

	//If the Verifier on the generated brick is valid, the didItVerify will report true.
	if ((*verifyThis).didItVerify()){
		//We still have to verify the SHA512 Hash. So we generate a coin from which we get its HashSignature;
		BrickCoin* coinVerify = new BrickCoin( (*generated) );

		//Only if the hashes are the same do we say it truly verified.
		
		if (SHA512hash == (*coinVerify).getHashSignature()){
			verified = true;
			//TODO: What else needs to happen?
			//Certainly don't want production code to do this.
			std::cout << "IT Truly verified" << std::endl;
		}
	}
	
}


//TODO: Fix the signature reader. 
EBVerify::EBVerify(std::string coin){

	//TODO: MAKE THIS INPUT RESISTANT!!!

	//This parses the input string into two parts, first the PTriples and Hash data, then second into the SHA512Hash.
	char * parseChar1 = new char[coin.length() +1];
	strcpy(parseChar1, coin.c_str());
	char * pch1;
	pch1 = strtok (parseChar1, "\n");
	std::string parseString = pch1;
	pch1 = strtok (NULL, "\n");
	parseString = parseString+"\n" + pch1;
	pch1 = strtok (NULL, "\n");
	std::string SHA512hash = pch1;
	
	//ONLY for TESTING PURPOSES
	std:: cout << parseString << std::endl;
	std:: cout << SHA512hash << std::endl;

	//Setting up the parsing mechanism
	char * parseChar = new char[parseString.length() + 1];
	strcpy(parseChar, parseString.c_str());
	char * pch;
   	std::vector<std::string> token;

	//The parsing Mechanism
  	pch = strtok (parseChar,"<,>");
	std::string temp = pch;
	token.push_back(temp);
  	while (pch != NULL)
  	{
    		pch = strtok (NULL, "<,>");
		if(pch == NULL){ break;}
		std::string temp = pch;
		token.push_back(temp);
  	}

	//Converting the resulting parsed strings into const chars so that the MPZ_T variables can be initialized.
	const char * aString = token[0].c_str();
	const char * bString = token[1].c_str();
	const char * cString = token[2].c_str();
	std::string aHashString = token[3];
	std::string bHashString = token[4];
	std::string cHashString = token[5];

	//Initializing the MPZ_T variables
	mpz_t aAA, bBB, cCC, ab, bc, a2, b2, c2, temp1, temp2;
	mpz_init_set_str(aAA, aString, 10);
	mpz_init_set_str(bBB, bString, 10);
	mpz_init_set_str(cCC, cString, 10);
	mpz_init_set_str(ab, "0", 10);
	mpz_init_set_str(bc, "0", 10);
	mpz_init_set_str(a2, "0", 10);
	mpz_init_set_str(b2, "0", 10);
	mpz_init_set_str(c2, "0", 10);
	mpz_mul(a2, aAA, aAA);
	mpz_mul(b2, bBB, bBB);
	mpz_mul(c2, cCC, cCC);
	mpz_init_set_str(temp1, "0", 10);
	mpz_init_set_str(temp2, "0", 10);
	mpz_add(temp1, a2, b2);
	mpz_add(temp2, b2, c2);
	
	//Generating the hypotenuses for the PTriples
	mpz_sqrt(ab, temp1);
	mpz_sqrt(bc, temp2);
	
	//Generating the PTriples
	PTriples * firstTriple = new PTriples(aAA, bBB, ab);
	PTriples * secondTriple = new PTriples(bBB, cCC, bc);


	//TODO: FIGURE OUT THE PATH, OR JUST INCLUDE IT IN THE DATA
	Path p1, p2;
	
	//Generate the testing EulerBrick
	EulerBrick* generated = new EulerBrick((*firstTriple), (*secondTriple), p1, p2);

	//Generate the verifier for the EulerBrick
	EBVerify* verifyThis = new EBVerify((*generated));

	//If it verifies, then we have to check the SHAhash
	if ((*verifyThis).didItVerify()){
		//Therefore, we generate a BrickCoin to verify the SHA512 hash
		BrickCoin* coinVerify = new BrickCoin( (*generated) );
		
		if (SHA512hash == (*coinVerify).getHashSignature()){
			verified = true;
			//What do we really want it to do?
			std::cout << "IT Truly verified" << std::endl;
		}
	}
}


