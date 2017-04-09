/*
*
* File: EulerBrick.h
* Author: jtucker
*
* Created 12_30_16
*
*/

#ifndef TESTSERVER_H
#define TESTSERVER_H

class TestServer {

public:
	TestServer() {}

	static int startServer();

	static int fireOffACoinToDatabase(std::string coinText);

};

#endif