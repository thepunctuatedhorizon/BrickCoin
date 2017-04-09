/*
*
* File: EulerBrick.h
* Author: jtucker
*
* Created 12_30_16
*
*/

#ifndef TESTCLIENT_H
#define TESTCLIENT_H

#include <string>

class TestClient {

public:
	TestClient() {}

	static int testClient(int argc, char * argv[2], std::string coinSig);


};

#endif