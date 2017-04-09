/*
* File: Path.h
* Author: jtucker
*
* Created on 12_29_16
*/



#ifndef PATH_H
#define PATH_H


#include <vector>
#include <string>

	class Path{

		public:
			//Path constructor
			Path();
			
			//TODO: Fix this!
			//This function shoud return, or something the path
			void foundAtThisNode(int whereFound);

			//Functions to add to the path
			void addUp();
			void addSide();
			void addDown();

			//sets the path root. This function ensures the path variable is set properly
			void setRoot();

			//This returns the size of the path.		
			int size() {return pathVector.size();}

			//This returns the part of the path associated with the i'th part of the journey
			int getInt(int i) {return pathVector[i];}

			//This function outputs the path as a string
			std::string getPath();
			
		private:
			//This variable holds a vector of ints representing the directions taken in the path.
			std::vector<int> pathVector;


	};

#endif


