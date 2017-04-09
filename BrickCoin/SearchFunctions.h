/*
* File: SearchFunctions.h
* Author: jtucker
*
* Created on 12_28_16
*/

#ifndef SEARCHFUNCTIONS_H
#define SEARCHFUNCTIONS_H

#include <mpir.h>
#include <mpirxx.h>

#include "FNV.h"
#include "PTriples.h"
#include "Node.h"
#include "Path.h"

//Bored of commenting.
	class SearchFunctions {

		public:
			SearchFunctions();

			//Depreciated
			static bool rawEquals(PTriples& firstT, PTriples& secondT, int first, int second);

			static int CMP(PTriples& firstT, PTriples& secondT, int first, int second);

			static bool HashEquals(PTriples& firstT, PTriples& secondT, int first, int second);

			static bool HashDiagonalEquals(PTriples& firstT, PTriples& secondT);

			static void traverseTreeUtil(Node& rootNode, PTriples& requirement, int depth); 

			static int HashEqualsAny(PTriples& firstT, PTriples& secondT);

			static bool HashAllEquals(PTriples& firstT, PTriples& secondT);

			static PTriples traverseToAndGet(Node& n, Path p);

			static PTriples createFromPath(Path p);
		
		
		private:
			




	};
#endif
