/*
 *
 * File: Multiplier.h
 * Author: jtucker
 *
 * Created 12_23_16
 *
 */

#ifndef MULTIPLIER_H
#define MULTIPLIER_H

#include <mpir.h>
#include <mpirxx.h>

#include "PTriples.h"

//This class allows the generation of Pythagorean Triples from a seed triple.
class Multiplier
{
    public:
	//Empty Constructor, used to initialize all of the MPZ_T variables
        Multiplier();

	//The essential function, this function takes in the  current PTriple
	//   and then multiplies it by the correct matrix, as indicated by the uSd
	//   integer.  The uSd corresponds to whether you want the up, side, or down 
	//   triple being generated. 
	//   The function returns the generated PTriple.
	PTriples hit( PTriples currentPT, int uSd);


    private:
	// These integers store the values for the UP matrix.
	long int up1, up2, up3;
	long int up4, up5, up6;
	long int up7, up8, up9;

	//These integers store the values for the Side matrix.
	long int side1, side2, side3;
	long int side4, side5, side6;
	long int side7, side8, side9;

	//These integers store the values for the Down matrix.
	long int down1, down2, down3;
	long int down4, down5, down6;
	long int down7, down8, down9;
	
	//These MPZ_T variables are to hold the intermediat values of the calculation.
	mpz_t interm1a, interm1b, interm1c;
	mpz_t interm2a, interm2b, interm2c;
	mpz_t interm3a;

	//These MPZ_T variables are to hold the results and use to initialize the PTriple returned.
	mpz_t result1, result2, result3;
	mpz_t zero;

	//These variables are to hold the Matrix values that are used in the hit calculation.
	long int mtrx1, mtrx2, mtrx3;
	long int mtrx4, mtrx5, mtrx6;
	long int mtrx7, mtrx8, mtrx9;


};

#endif
