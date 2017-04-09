/*
* File: SearchAlgorithm.h
* Author: jtucker
*
* Created 3_9_2017
*/
#ifndef _SEARCH_ALGORITHM
#define _SEARCH_ALGORITHM


#include <mpir.h>
#include <mpirxx.h>

#include "SearchFunctions.h"

#include "FNV.h"
#include "PTriples.h"
#include "Node.h"
#include "Path.h"

//Bored of commenting.
class SearchAlgorithms {
	public:
		SearchAlgorithms();

		SearchAlgorithms(Node& nodeStart);

		SearchAlgorithms(PTriples& target);


	private:
		Path path1;
		Path path2;
		Node startNode;

};

#endif