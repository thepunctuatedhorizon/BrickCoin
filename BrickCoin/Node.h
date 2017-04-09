/*
 *
 * File: Node.h
 * Author: jtucker
 *
 * Created 12_23_16
 *
 */

#ifndef NODE_H
#define NODE_H

#include "PTriples.h"
#include "Multiplier.h"
#include "Path.h"


//This class initializes the ternary tree of Pythagorean triples that distinguishes 
//    pythagorean triples.
class Node
{
	public:
		//Default constructor.  Left empty;
		Node();

		//Proper initializer.  The anchor node tells what PTriple was is the anchor for the node
		//    The multiplier is the class that allows multiplication of MPZ_T numbers/vectors
		//    The dir integer tells what direction matrix was used to create this node
		//    The path tells the path taken up until this node.
		//    The depth variable tells what level of the ternary tree you are on.
		Node(PTriples& nodeAnchr, Multiplier& mult, int dir, Path oldPath, int depth);
		
	
		// Does the work of initializing the sub nodes
		void initializeSubNodes(Multiplier& mult, int depth);

		// These will return the up, side, or down node object 
		Node getUp() {return *up;}
		Node getSide(){return *side;}
		Node getDown(){return *down;}

		//These will return the address to the up, side, or down node objects
		Node* getU(){return up;}
		Node* getS(){return side;}
		Node* getD() {return down;}

		//Get the depth of the current node
		int getDepth() {return depth;}	
		
		//Returns the PTriple that anchors the node
		PTriples getAnchor(){return nodeAnchor;}

		//Returns the path taken to get this node
		Path getPath() {return path;}

	private:
		//The anchor PTriple
		PTriples nodeAnchor;

		//The path to get to the node
		Path path;

		//The address to the nodes up, side, and down
		Node* up;
		Node* side;
		Node* down;

		// The level of the ternary tree of the current node
		int depth;
};
#endif
