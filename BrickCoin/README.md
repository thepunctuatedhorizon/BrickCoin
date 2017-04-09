This idea is to find Euler Bricks. Any Euler bricks that are primitive shall be a currency unit. The process will be difficult to manage, but it'll work eventually.
 g++ -std=c++14 BrickCoin.cpp BrickDataBase/db.cpp EulerBrick.cpp EBVerify.cpp FNV.cpp main.cpp Multiplier.cpp Node.cpp Path.cpp PTriples.cpp SearchFunctions.cpp -lgmp -lgmpxx -lssl -lcrypto -lsqlite3 -o exe.out


Nonces will be Euler Brick signatures.  Each and every nonce will have to be original.  All other aspects of the Bitcoin process will/should be easily preserved.


