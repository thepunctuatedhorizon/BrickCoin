/*
* File: Path.cpp
* Author: jtucker
*
* Created 12_29_16
*/


#include "Path.h"
#include "Node.h"
#include <string>


const size_t MAX_PATH_LENGTH = 15;

//Default Constructor
Path::Path() {
	// Initialize
	pathVector.reserve(MAX_PATH_LENGTH);
}

//TODO:Fix this
void Path::foundAtThisNode(int whereFound){

	//Do something
	for (int i = 0; i<pathVector.size(); i++)
	{
		std::cout << pathVector[i] << ", " ;
	}
	std::cout << std::endl;
	std::cout << "The place found = " << whereFound << std::endl;
}


void Path::addUp(){
	pathVector.push_back(1);
}

void Path::addSide(){
	pathVector.push_back(0);
}

void Path::addDown(){
	pathVector.push_back(-1);
}

void Path::setRoot(){

	pathVector.clear();
	pathVector.reserve(MAX_PATH_LENGTH);
	pathVector.push_back(-2);
}

std::string Path::getPath(){
	const int sz = pathVector.size();
	char* path = new char[sz];
	for (int i = 0; i < pathVector.size(); i++){
		path[i] = pathVector[i];
	}
	std::string returnPath = path;
	return returnPath;
}






