/*
 *
 * File: UsedNonces.h
 * Author: jtucker
 *
 * Created 1_4_17
 *
 */

#ifndef USEDNONCES_H
#define USEDNONCES_H

#include <mpir.h>
#include <mpirxx.h>

#include <sqlite3.h>

#include "PTriples.h"
#include "Path.h"
#include "EulerBrick.h"

// The idea is that each tried nonce shoud be owned EulerBrick hashes. 
// The miners will have a set of them lined up to try.
// The mining process will be: 
//     	        1.  Brick miners will mine for EulerBricks.
//		2.  Brick miner will report all new Bricks to the brick database.
//		3.  The network validates the new bricks and scan database for any diplicates that have been mined
//		4.  The network performs a proof of work (this time almost exactly like bitcoin) that establishes ownership of EulerBricks.  The validation and proof of work are conjoined steps. That is, the network races to verify the bricks AND perform proof of work. 
//		5.  The network is rewarded by a factor of the reward given to processing the transaction base.
//		6.  After a brick miner has been awarded ownership of EulerBricks as above, the Bricks (specifically the SHA512 hashes) that the Miner owns can be sold or used in the next step.
//		7.  After a Brick has been mined, the nonce (The SHA512 hash of the signature) is to be used as the nonces that verify regular market transactions.
//		8.  The transaction miners begin hashing the EulerBrick SHA512 hashes/nonces with the transaction block. This step is the crucial step, why use Bricks? You have to use a brick to successfuly mine a transaction block
//		9.  A successful mining operation will purchase enough EulerBricks (or mine them themselves) so that they can try every nonce they own to see if it meets the work criteria
//		10. A successful mining of a block of transaction data will have used the transaction data, timestamp, ..., and their owned EulerBrick nonce to create a hash that meets the proof of work criterion
//		11. Brick miners are lucky as finding one Brick will generate 5 more bricks plus the HUNDREDS of THOUSANDS more you can create from parameterization. 
//		12. It is an open question as to whether there should be primitive bricks? Or do we tollerate parameterized bricks.
//		13. What balance should be placed between Brick Miners and Transaction Miners? Who is rewarded most?
//		14. Why wouldn't we make a freemarket?  If Bricks are scarce commodities, then the Brick miners will profit most.  If the Bricks are plentiful, the Transaction miners will profit most.
//		15. Bricks will be priced on a market for bricks.

//		16. As an added bonus, any scientific question that has open questions could harnes the ideas above.  Simply plug in the problem to be solved as the Brick, have the network verify the solutions AND do proof of work like bitcoin, and the Hash of the solution becomes a nonce in the transaction database.


#endif
