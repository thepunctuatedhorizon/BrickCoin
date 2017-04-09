/*
* File: SearchFunction.cpp
* Author: jtucker
*
* Created 12_28_16
*/

#include <mpir.h>
#include <mpirxx.h>

#include "SearchFunctions.h"

//I'm bored of commenting, I'll just leave this as is.
SearchFunctions::SearchFunctions(){ }

bool SearchFunctions::rawEquals(PTriples& firstT, PTriples& secondT, int first, int second){

	mpz_t temp1, temp2;
	mpz_init_set_str(temp1, "0", 10);
	mpz_init_set_str(temp2, "0", 10);
	if (first == 1 && second == 1){
		firstT.getA(temp1);
		secondT.getA(temp2);
	} else if ( first == 1 && second == 2){
		firstT.getA(temp1);
		secondT.getB(temp2);
	} else if ( first == 1 && second == 3) {
		firstT.getA(temp1);
		secondT.getC(temp2);
	} else if ( first == 2 && second == 1){
		firstT.getB(temp1);
		secondT.getA(temp2);
	} else if ( first == 2 && second == 2) {
		firstT.getB(temp1);
		secondT.getB(temp2);
	} else if ( first == 2 && second == 3){
		firstT.getB(temp1);
		secondT.getC(temp2);
	} else if ( first == 3 && second == 1) {
		firstT.getC(temp1);
		secondT.getA(temp2);
	} else if ( first == 3 && second == 2){
		firstT.getC(temp1);
		secondT.getB(temp2);
	} else if ( first == 3 && second == 3) {
		firstT.getC(temp1);
		secondT.getC(temp2);
	} else {
		return false;
	}
	

	if (mpz_cmp(temp1,temp2)==0)
	{
		return true;
	} 
	return false;	
}


int SearchFunctions::CMP(PTriples& firstT, PTriples& secondT, int first, int second){

	mpz_t temp1, temp2;
	mpz_init_set_str(temp1, "0", 10);
	mpz_init_set_str(temp2, "0", 10);
	if (first == 1 && second == 1){
		firstT.getA(temp1);
		secondT.getA(temp2);
	} else if ( first == 1 && second == 2){
		firstT.getA(temp1);
		secondT.getB(temp2);
	} else if ( first == 1 && second == 3) {
		firstT.getA(temp1);
		secondT.getC(temp2);
	} else if ( first == 2 && second == 1){
		firstT.getB(temp1);
		secondT.getA(temp2);
	} else if ( first == 2 && second == 2) {
		firstT.getB(temp1);
		secondT.getB(temp2);
	} else if ( first == 2 && second == 3){
		firstT.getB(temp1);
		secondT.getC(temp2);
	} else if ( first == 3 && second == 1) {
		firstT.getC(temp1);
		secondT.getA(temp2);
	} else if ( first == 3 && second == 2){
		firstT.getC(temp1);
		secondT.getB(temp2);
	} else if ( first == 3 && second == 3) {
		firstT.getC(temp1);
		secondT.getC(temp2);
	} else {
		return -2;
	}
	

	return mpz_cmp(temp1,temp2);
}


bool SearchFunctions::HashEquals(PTriples& firstT, PTriples& secondT, int first, int second){
	
	uint32_t a, b;
	if (first == 1 && second == 1){
		a = firstT.getAHash();
		b = secondT.getAHash();
	} else if ( first == 1 && second == 2){
		a = firstT.getAHash();
		b = secondT.getBHash();
	} else if ( first == 1 && second == 3) {
		a = firstT.getAHash();
		b = secondT.getCHash();
	} else if ( first == 2 && second == 1){
		a = firstT.getBHash();
		b = secondT.getAHash();
	} else if ( first == 2 && second == 2) {
		a = firstT.getBHash();
		b = secondT.getBHash();
	} else if ( first == 2 && second == 3){
		a = firstT.getBHash();
		b = secondT.getCHash();
	} else if ( first == 3 && second == 1) {
		a = firstT.getCHash();
		b = secondT.getAHash();
	} else if ( first == 3 && second == 2){
		a = firstT.getCHash();
		b = secondT.getBHash();
	} else if ( first == 3 && second == 3) {
		a = firstT.getCHash();
		b = secondT.getCHash();
	} else {
		return false;
	}

	if (a == b) {return true;}

	
}


bool SearchFunctions::HashDiagonalEquals(PTriples& firstT, PTriples& secondT) {

	if (firstT.getCHash() == secondT.getCHash() ){return true;}
	return false;
}


int SearchFunctions::HashEqualsAny(PTriples& firstT, PTriples& secondT){
	
	uint32_t a1 = firstT.getAHash();
	uint32_t b1 = firstT.getBHash();

	uint32_t a2 = secondT.getAHash();
	uint32_t b2 = secondT.getBHash();


	if (a1 == a2){
		return 1;
	} else if ( a1 == b2){
		return 2;
	} else if ( b1 == a2){
		return 3;
	} else if ( b1 == b2) {
		return 4;
	}  else {
		return 0;
	}

}

bool SearchFunctions::HashAllEquals(PTriples& firstT, PTriples& secondT){
	
	uint32_t a1 = firstT.getAHash();
	uint32_t b1 = firstT.getBHash();
	uint32_t c1 = firstT.getCHash();

	uint32_t a2 = secondT.getAHash();
	uint32_t b2 = secondT.getBHash();
	uint32_t c2 = secondT.getCHash();


	if (a1 == a2 && b1 == b2 && c1 == c2){
		return true;
	}  else {
		return false;
	}

}

void SearchFunctions::traverseTreeUtil(Node& rootNode, PTriples& requirement, int depth){

	PTriples nodeTriple = rootNode.getAnchor();
	
	//nodeTriple.printOutTriple();
	 
	int whereEqual = SearchFunctions::HashEqualsAny(nodeTriple, requirement);
	

	if (whereEqual > 0){
		rootNode.getPath().foundAtThisNode(whereEqual);
		return;
	}
	
	if ( depth > 0){
		Node up = rootNode.getUp();
		Node side = rootNode.getSide();
		Node down = rootNode.getDown();
		traverseTreeUtil(up, requirement, depth-1);
		traverseTreeUtil(side, requirement, depth -1);
		traverseTreeUtil(down, requirement, depth -1);
	}
}


PTriples SearchFunctions::traverseToAndGet(Node& n, Path p){
	Node* fPointer = & n;
	for (int i = 0; i < p.size(); i++){
		Node* pointer = fPointer;
		int goWhere = p.getInt(i);
		if (goWhere == -2){
			// good we initialized the path right
		} else if (goWhere == 1) {
			pointer = pointer->getU();
		} else if (goWhere == 0) {
			pointer = pointer->getS();
		} else if (goWhere == -1) {
			pointer = pointer->getD();
		}
		fPointer = pointer;
	}
	
	return (*fPointer).getAnchor();
	
}

PTriples SearchFunctions::createFromPath(Path p){
	PTriples cur;
	Multiplier mult;

	for ( int i = 0; i < p.size(); i++ )
	{
		int dir = p.getInt(i);
		if (dir == -2){
		 	//We don't need to do anything, the path is set up right.
		} else if (dir == 1) {
			cur = mult.hit(cur, 1);
		} else if (dir == 0) {
			cur = mult.hit(cur, 2);
		} else if (dir == -1) {
			cur = mult.hit(cur, 3);
		}
	}
	return cur;
}











