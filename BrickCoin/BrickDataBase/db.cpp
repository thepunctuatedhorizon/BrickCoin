/*
 *
 * File: db.cpp
 * Author: jtucker
 *
 * Created 1_4_17
 *
 */



#include <iostream>
#include <cstdlib>
#include <vector>
#include <string>
#include <string.h>
#include <stdio.h>
#include <sqlite3.h> 

#include "db.h"

static int callback(void *NotUsed, int argc, char **argv, char **azColName){
   	for( int i=0; i<argc; i++){
      		printf("%s = %s\n", azColName[i], argv[i] ? argv[i] : "NULL");
   	}
   	printf("\n");
   	return 0;
}

static int callBackSignature(void *outputStr, int argc, char **argv, char **azColName){
	(*( std::vector<std::string>*)(outputStr));
	(*( std::vector<std::string>*)(outputStr)).push_back("<");
   	for( int i=0; i<argc; i++){
		(*( std::vector<std::string>*)(outputStr)).push_back( (argv[i] ? argv[i] : "NULL") );
      		printf("%s = %s\n", azColName[i], argv[i] ? argv[i] : "NULL");
   	}
   	printf("\n");
   	return 0;
}

//TODO: FIX!
static int callBackSearchForSignature(void *loc, int argc, char **argv, char **azColName){
   	
	*(int*)loc = std::stoi(argv[0]);

   	return 0;
}

int DB::startDatabase()
{
   	
   	char *zErrMsg = 0;
   	int rc;

	const char* data = "Callback function called";

	char * sql;

   	/* Open database */

	try{
		rc = sqlite3_open("test.db", &db);
		if ( rc ) {
			std::cout << "Can't open database: " << sqlite3_errmsg(db) << std::endl;
			throw 1;
		}

		std::cout << "Opened database successfully" << std::endl;
		
	} catch ( int e ) {
		//What do we do when the sqlite server isn't working?
		return e;
	}

	try {
		
		//Official SQL statment
		sql = "CREATE TABLE IF NOT EXISTS BRICK(" \
			"ID 	INT PRIMARY KEY	NOT NULL," \
			"A	TEXT		NOT NULL," \
			"B	TEXT		NOT NULL," \
			"C	TEXT		NOT NULL," \
			"AHASH	TEXT		NOT NULL," \
			"BHASH	TEXT		NOT NULL," \
			"CHASH	TEXT		NOT NULL," \
			"SHA512	TEXT		NOT NULL );";

   		/* Execute SQL statement */
	   	rc = sqlite3_exec(db, sql, callback, 0, &zErrMsg);
	   	if( rc != SQLITE_OK ){
	   		fprintf(stderr, "SQL error: %s\n", zErrMsg);
	      		sqlite3_free(zErrMsg);
			throw 1;
	   	}
	      	fprintf(stdout, "Table created successfully or already existed\n");
	   	
	} catch (int e) {
		//We care because, why?
		return e;
	}
}

int DB::insertIntoDatabase(char * sql){        
	char *zErrMsg = 0;
	int rc;

   	/* Execute SQL statement */
	try{
   		rc = sqlite3_exec( db, sql, callback, 0, &zErrMsg);
   		if( rc != SQLITE_OK ){
     			fprintf(stderr, "SQL error: %s\n", zErrMsg);
      			sqlite3_free(zErrMsg);
			throw 1;
   		}
      		fprintf(stdout, "Records created successfully\n");
   	} catch (int e) {
		//We should care, but how?
		return e;
	}
	return 0;
}

int DB::closeDatabase(){
	sqlite3_close(db);
	return 0;
}


int DB::getInfoFromDatabase(char * sql) {
	char *zErrMsg = 0;
	int rc;
	const char* data = "Callback function called";

   	/* Execute SQL statement */
   	rc = sqlite3_exec(db, sql, callback, (void*)data, &zErrMsg);
   	if( rc != SQLITE_OK ){
      		fprintf(stderr, "SQL error: %s\n", zErrMsg);
      		sqlite3_free(zErrMsg);
   	}else{
      		fprintf(stdout, "Operation done successfully\n");
   	}
	return 0;
}


int DB::parseAndStore(std::string coin){
	//TODO: MAKE THIS INPUT RESISTANT!!!

	//This parses the input string into two parts, first the PTriples and Hash data, then second into the SHA512Hash.
	char * parseChar1 = new char[coin.length() +1];
	strcpy(parseChar1, coin.c_str());
	char * pch1;
	pch1 = strtok (parseChar1, "\n");
	std::string parseString = pch1;
	pch1 = strtok (NULL, "\n");
	parseString = parseString+"\n" + pch1;
	pch1 = strtok (NULL, "\n");
	std::string SHA512hash = pch1;

	//Setting up the parsing mechanism
	char * parseChar = new char[parseString.length() + 1];
	strcpy(parseChar, parseString.c_str());
	char * pch;
   	std::vector<std::string> token;

	//The parsing Mechanism
  	pch = strtok (parseChar,"<,>");
	std::string temp = pch;
	token.push_back(temp);
  	while (pch != NULL)
  	{
    		pch = strtok (NULL, "<,>");
		if(pch == NULL){ break;}
		std::string temp = pch;
		token.push_back(temp);
  	}

	//Converting the resulting parsed strings into const chars so that the MPZ_T variables can be initialized.
	std::string aString = token[0];
	std::string bString = token[1];
	std::string cString = token[2];
	std::string aHashString = token[4];
	std::string bHashString = token[5];
	std::string cHashString = token[6];

	//TODO  /*MUST FIGURE OUT HOW TO STORE*/
	std::string sqlStr ="INSERT INTO BRICK (ID,A,B,C,AHASH,BHASH,CHASH,SHA512) VALUES ( 2,'" + aString + "','" + bString + "','" +cString + "','" + aHashString + "','" + bHashString + "','" + cHashString + "','" + SHA512hash + "' ); ";
	const char * sql = sqlStr.c_str(); 
	
	char *zErrMsg = 0;
	int rc;

   	/* Execute SQL statement */
	try{
   		rc = sqlite3_exec( db, sql, callback, 0, &zErrMsg);
   		if( rc != SQLITE_OK ){
     			fprintf(stderr, "SQL error: %s\n", zErrMsg);
      			sqlite3_free(zErrMsg);
			throw 1;
   		}
      		fprintf(stdout, "Records created successfully\n");
   	} catch (int e) {
		//We should care, but how?
		return e;
	}
	return 0;

}


std::string DB::getAndRecreateSignature(std::vector<std::string> data, int recordNum){
	/* Create SQL statement */
	char *sql = "SELECT * from BRICK";
	char *zErrMsg = 0;
	int rc;
	

   	/* Execute SQL statement */
	try {
   		rc = sqlite3_exec(db, sql, callBackSignature, (void*)&data, &zErrMsg);
   		if( rc != SQLITE_OK ){
      			fprintf(stderr, "SQL error: %s\n", zErrMsg);
      			sqlite3_free(zErrMsg);
			throw 1;
   		}else{
      			fprintf(stdout, "Operation done successfully\n");
   		}
	} catch (int e) {
		return "" + e;
	}
	return "<" + data[2] + "," + data[3] + "," + data[4] + ">\n<" + data[5] + "," + data[6]+ "," + data[7] + ">\n" + data[8] + "\n";
}


int DB::searchForSignature(std::string hashSignature){
	std::string sqlString = "SELECT * FROM `BRICK` WHERE SHA512=\"" + hashSignature + "\"";
	const char *sql = sqlString.c_str();
	char *zErrMsg = 0;
	int rc;
	int data;

   	/* Execute SQL statement */
	try {
   		rc = sqlite3_exec(db, sql, callBackSearchForSignature, (void*)&data, &zErrMsg);
   		if( rc != SQLITE_OK ){
      			fprintf(stderr, "SQL error: %s\n", zErrMsg);
      			sqlite3_free(zErrMsg);
			throw -1;
   		}else{
      			fprintf(stdout, "Operation done successfully\n");
   		}
	} catch (int e) {
		return e;
	}
	return data;
}






