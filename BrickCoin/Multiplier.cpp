/*
 *
 * File: Multiplier.cpp
 * Author: jtucker
 *
 * Created 12_23_16
 *
 */

#include <mpir.h>
#include <mpirxx.h>

#include "Multiplier.h"

Multiplier::Multiplier(){
	//Initializing the matrix UP
	up1 = 1;  up2 = -2; up3 = 2;
	up4 = 2;  up5 = -1; up6 = 2;
	up7 = 2;  up8 = -2; up9 = 3;

	//Initializing the matrix Side
	side1 = 1; side2 = 2; side3 = 2;
	side4 = 2; side5 = 1; side6 = 2;
	side7 = 2; side8 = 2; side9 = 3;

	//Initializing the matrix Down
	down1 = -1; down2 = 2; down3 = 2;
	down4 = -2; down5 = 1; down6 = 2;
	down7 = -2; down8 = 2; down9 = 3;

	//To avoid invalid pointers, we initialize to zero all interm and result variables.
	mpz_init_set_str (interm1a, "0", 10);
	mpz_init_set_str (interm1b, "0", 10);
	mpz_init_set_str (interm1c, "0", 10);
	
	mpz_init_set_str (interm2a, "0", 10);
	mpz_init_set_str (interm2b, "0", 10);
	mpz_init_set_str (interm2c, "0", 10);

	mpz_init_set_str (interm3a, "0", 10);

	mpz_init_set_str (result1, "0", 10);
	mpz_init_set_str (result2, "0", 10);
	mpz_init_set_str (result3, "0", 10);
	
	
	mpz_init_set_str(zero, "0", 10);


}

// The hit function.  It will "hit" the current PTriple with the correct matrix
//   The correct matrix is chosen by the input of uSd.
PTriples Multiplier::hit(PTriples currentPT, int uSd){
	//setting results to zero to clear old used values.
	mpz_set (result1, zero);
	mpz_set (result2, zero);
	mpz_set (result3, zero);


	//Matrix chooser.
	if (uSd == 1){
		
		mtrx1 = up1; mtrx2 = up2; mtrx3 = up3;
		mtrx4 = up4; mtrx5 = up5; mtrx6 = up6;
		mtrx7 = up7; mtrx8 = up8; mtrx9 = up9;

	} else if (uSd == 2) {

		mtrx1 = side1; mtrx2 = side2; mtrx3 = side3;
		mtrx4 = side4; mtrx5 = side5; mtrx6 = side6;
		mtrx7 = side7; mtrx8 = side6; mtrx9 = side9;

	} else if (uSd == 3) {

		mtrx1 = down1; mtrx2 = down2; mtrx3 = down3;
		mtrx4 = down4; mtrx5 = down5; mtrx6 = down6;
		mtrx7 = down7; mtrx8 = down8; mtrx9 = down9;
	} else {
		std::cout << "ERROR!!" << std::endl;
		return PTriples();
	}

	//Begin matrix multiplications
	//Multiplying to get the first result
	mpz_set (interm1a, zero);
	mpz_set (interm1b, zero);
	mpz_set (interm1c, zero);
	
	mpz_set (interm2a, zero);
	mpz_set (interm2b, zero);
	mpz_set (interm2c, zero);

	mpz_set (interm3a, zero);
	
	currentPT.getA(interm1a);
	mpz_mul_si(interm2a, interm1a, mtrx1);

	currentPT.getB(interm1b);
	mpz_mul_si(interm2b, interm1b, mtrx2);

	currentPT.getC(interm1c);
	mpz_mul_si(interm2c, interm1c, mtrx3); 
	
	mpz_add(interm3a,interm2a,interm2b);
	mpz_add(result1, interm3a, interm2c);

	//Multiplying to get the second result
	mpz_set (interm1a, zero);
	mpz_set (interm1b, zero);
	mpz_set (interm1c, zero);
	
	mpz_set (interm2a, zero);
	mpz_set (interm2b, zero);
	mpz_set (interm2c, zero);

	mpz_set (interm3a, zero);

	currentPT.getA(interm1a);
	mpz_mul_si(interm2a, interm1a, mtrx4);

	currentPT.getB(interm1b);
	mpz_mul_si(interm2b, interm1b, mtrx5);

	currentPT.getC(interm1c);
	mpz_mul_si(interm2c, interm1c, mtrx6); 
	
	mpz_add(interm3a,interm2a,interm2b);
	mpz_add(result2, interm3a, interm2c);

	//Multiplying to get the third result
	mpz_set (interm1a, zero);
	mpz_set (interm1b, zero);
	mpz_set (interm1c, zero);
	
	mpz_set (interm2a, zero);
	mpz_set (interm2b, zero);
	mpz_set (interm2c, zero);

	mpz_set (interm3a, zero);

	currentPT.getA(interm1a);
	mpz_mul_si(interm2a, interm1a, mtrx7);

	currentPT.getB(interm1b);
	mpz_mul_si(interm2b, interm1b, mtrx8);

	currentPT.getC(interm1c);
	mpz_mul_si(interm2c, interm1c, mtrx9); 
	
	mpz_add(interm3a,interm2a,interm2b);
	mpz_add(result3, interm3a, interm2c);


	//This part collects the results of our multiplication.
	PTriples* returnPT = new PTriples(result1, result2, result3);

	return (*returnPT);
}
