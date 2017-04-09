#include <iostream>

#include <mpir.h>
#include <mpirxx.h>

#include "PTriples.h"
#include "Multiplier.h"
#include "Node.h"
#include "TestServer.h"
#include "TestClient.h"
#include "FNV.h"

#include <thread>
#include "SearchFunctions.h"

#include "Path.h"

#include "EulerBrick.h"

#include "EBVerify.h"

#include "common.h"
#include "hash.h"

#include "BrickDataBase/db.h"

void startServer(std::string hi) {
	TestServer::startServer();
}

int main()
{

	mpz_t brickL, brickW, brickH;
	mpz_init_set_str(brickL, "44", 10);
	mpz_init_set_str(brickW, "117", 10);
	mpz_init_set_str(brickH, "240", 10);
	
	 

	Multiplier mult;

	PTriples test1;
	PTriples test2;
 
	Path path;

	Node* node = new Node(test1, mult, -2, path, 0);
	Node* node1 = new Node(test2, mult, -2, path, 0);
	
	
	PTriples firstAPT = (*node).getUp().getAnchor();
	PTriples secondAPT = (*node1).getUp().getAnchor();
	
	
	Node& refNode = * node;
	
	SearchFunctions::traverseTreeUtil(refNode, firstAPT, 4);

	std::cout << "End of traverse" << std::endl;

	PTriples match = (*node).getDown().getDown().getAnchor();

	std::cout << match.printOutTriple() << std::endl;
	PTriples mmatch = (*node).getUp().getAnchor();

	std::cout << mmatch.printOutTriple() << std::endl;
	





	//Here, I'm testing the Euler Brick

	mpz_t aa, bb, cc, da, db;
	mpz_init_set_str(aa, "240", 10);
	mpz_init_set_str(bb, "117", 10);
	mpz_init_set_str(cc, "44", 10);
	mpz_init_set_str(da, "267", 10);
	mpz_init_set_str(db, "125", 10);
	PTriples* aA = new PTriples(aa, bb, da);
	PTriples* bA = new PTriples(bb, cc, db);
	Path p;

	EulerBrick* eulerBrick = new EulerBrick((*aA), (*bA), p, p);
	
	//CAUSES ERROR!
	std::cout << (*eulerBrick).print();
	
	
	std::cout << "Here's a match, is it a brick?" << std::endl;
	
	EulerBrick* eulerB = new EulerBrick(firstAPT, (*node).getDown().getDown().getAnchor(),p,p);
	std::cout << (*eulerB).print();




	std::cout << "A meandering stream of searching." << std::dec << std::endl;
	
	PTriples* trip = new PTriples(brickW, brickL, db);

	SearchFunctions::traverseTreeUtil(refNode, (*trip), 3);

	std::cout << " TOWSON UNIVERSITY GRAD" << std::endl;
	
	Path pathss;
	pathss.setRoot();
	pathss.addUp();
	pathss.addDown();
	pathss.addDown();

	PTriples result = SearchFunctions::traverseToAndGet((*node), pathss);
	std::cout << result.printOutTriple()<< std::endl;
	
	//Testing the new confirmation system.

	std::cout << "* Testing *" << std::endl;

	EBVerify * verifier = new EBVerify((*eulerBrick));



	BrickCoin* coin = new BrickCoin( (*eulerBrick));

	std::cout << (*coin).getSignature() << std::endl;
	std::cout << (*coin).getHashSignature() << std::endl;

	EBVerify * ver = new EBVerify((*coin));

	std::string coinSig = "<240,117,44>\n<750b7a6f,f00c3c10,290c95cb>\nf82755bb940b750bbc5b49cb8436bd52c8d4246861961303355fea76ba21bef6c09eb11be2d276ee2479a99cbfe9f09bc351d3c5a7c078cb294996fecb1aaed9";

	EBVerify * stringVerify  = new EBVerify(coinSig);


	std::cout << (*eulerBrick).isPrimitiveBrick() << std::endl;

	std::cout << (*eulerBrick).isBrickClose() << std::endl;
	
	mpz_t temp;
	mpz_init_set_str(temp, "0", 10);
	(*eulerBrick).getOddSide(temp);
	std::cout << mpz_get_str(NULL, 10, temp);
	std::cout << std::endl;

	//Testing the derivatives of <a, b, c>
	mpz_t A, B, C, dac, dbc;
	mpz_init_set_str(A, "240", 10);
	mpz_init_set_str(B, "117", 10);
	mpz_init_set_str(C, "44", 10);
	mpz_init_set_str(dac, "244", 10);
	mpz_init_set_str(dbc, "125", 10);
	PTriples* aaa = new PTriples(A, C, dac);
	PTriples* bbb = new PTriples(A, B, dbc);
	Path pp;

	EulerBrick* eulerBricktest = new EulerBrick((*aaa), (*bbb), pp, pp);
	
	std::cout << "Here's the sha512 hash trouble makers" << std::endl;

	
	std::cout << (*coin).getHashSignature() << std::endl;

	delete eulerBricktest;
	delete aaa;
	delete bbb;
	delete stringVerify;
	delete ver;
	delete verifier;
	delete node;
	delete node1;
	delete aA;
	delete bA;
	delete eulerBrick;
	delete trip; 
	//Here I'm starting to test my Bitcoin stuff.
	//Here is the Serialization example
	
	uint32_t n32 = 0x68f7a38b;
    	char str[] = "FooBar";
    	size_t str_len = 10;
    	uint16_t n16 = 0xee12;
    	uint8_t ser[16];
	
	//This is what we expect
    	const char ser_exp[] = "8ba3f768466f6f4261720000000012ee";

    	/* */ 

    	size_t str_real_len = strlen(str);
    	size_t str_pad_len = str_len - str_real_len;

    	*(uint32_t *)(ser) = bbp_eint32(BBP_LITTLE, n32);
    	memcpy(ser + 4, str, str_real_len);
    	if (str_pad_len > 0) {
    		memset(ser + 4 + str_real_len, '\0', str_pad_len);
    	}
    	*(uint16_t *)(ser + 4 + str_len) = bbp_eint16(BBP_LITTLE, n16);

    	bbp_print_hex("ser      ", ser, sizeof(ser));
	printf("ser (exp): %s\n", ser_exp);


	//Here is the hash examples
	 char message[] = "Hello Bitcoin!";
    	uint16_t prefix = 0xd17f;
    	uint8_t suffix = 0x8c;
    	uint8_t digest[32];
    	uint8_t hser[35];

    	const char sha256_exp[] = "518ad5a375fa52f84b2b3df7933ad685eb62cf69869a96731561f94d10826b5c";
    	const char hash256_exp[] = "90986ea4e28b847cc7f9beba87ea81b221ca6eaf9828a8b04c290c21d891bcda";
    	const char hash_ser_exp[] = "7fd190986ea4e28b847cc7f9beba87ea81b221ca6eaf9828a8b04c290c21d891bcda8c";

    	

    	/* SHA-2 digest is big-endian */ 
		/*
    	bbp_sha256(digest, (uint8_t *)message, strlen(message));
    	bbp_print_hex("SHA256(message)      ", digest, 32);
    	printf("SHA256(message) (exp): %s\n", sha256_exp);

    	bbp_sha256(digest, digest, 32);
    	bbp_print_hex("hash256(message)      ", digest, 32);
    	printf("hash256(message) (exp): %s\n", hash256_exp);

    	*(uint16_t *)(hser) = bbp_eint16(BBP_LITTLE, prefix);
    	memcpy(hser + 2, digest, 32);
    	*(hser + 2 + 32) = suffix;

    	bbp_print_hex("ser      ", hser, sizeof(hser));
	printf("ser (exp): %s\n", hash_ser_exp);
	




	*/

	//Here I'm testing the DATABASE FEATURE.
	
	char * sql;
	
   	int rc;


	DB databaseHelper;
	
	databaseHelper.startDatabase();


	/* Create SQL statement */ 
   	sql = "INSERT INTO BRICK (ID,A,B,C,AHASH,BHASH,CHASH,SHA512) "  \
         	"VALUES (1, '44', '117', '240', '290c95cb', 'f00c3c10','750b7a6f','f82755bb940b750bbc5b49cb8436bd52c8d4246861961303355fea76ba21bef6c09eb11be2d276ee2479a99cbfe9f09bc351d3c5a7c078cb294996fecb1aaed9' ); " ;
	databaseHelper.insertIntoDatabase( sql);
	
	databaseHelper.parseAndStore(coinSig);

	/* Create SQL statement */ 
   	sql = "SELECT * from BRICK";
	databaseHelper.getInfoFromDatabase(sql);

	std::vector<std::string> data;
	data.reserve(10);
	std::cout << databaseHelper.getAndRecreateSignature(data, 1);
	std::cout << std::endl;
	std::cout << databaseHelper.searchForSignature("f82755bb940b750bbc5b49cb8436bd52c8d4246861961303355fea76ba21bef6c09eb11be2d276ee2479a99cbfe9f09bc351d3c5a7c078cb294996fecb1aaed9");
   	databaseHelper.closeDatabase();
	
	

	std::thread serverThread(startServer, "hi");
	

	std::cout << "here we GO!" << std::endl;
	char * int1[2];
	int int12;
	std::cin >> int12;
	
	TestClient::testClient(2, int1, (*coin).getHashSignature());

	std::cout << "END!" << std::endl;
	std::string str2;
	std::cin >> str2;

	serverThread.detach();

    return 0;
}

