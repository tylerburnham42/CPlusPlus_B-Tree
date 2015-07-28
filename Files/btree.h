
#include <vector>
#include <set>
#include <iostream>
#include <cstring>
#include <string>
#include <sstream>
#include <cstdlib>
#include <fstream>
#include "album.h"
using namespace std;

#ifndef BTREE_H
#define BTREE_H

class Album;
const int ORDER = 5;
typedef Album keyType;
typedef int IndexArray[ORDER];
typedef keyType ValueArray[ORDER-1];

struct BTNode
{
        int currSize;
        ValueArray contents;
        IndexArray child;
}; 

struct Pair
{
        Album element;
        int loffset;
        int roffset;
        friend bool operator < (const Pair& p1, const Pair& p2)
           { return (p1.element < p2.element);  }
};

class BTree
{
 public:
	BTree();
	BTree(char * filename);
	void writeHeader (char * fileName);
	void insert (keyType key);
	void reset (char * filename);
	void close ();
	void printTree();
	void inorder();
	void reverse();
	int getHeight();
	bool search (string key);
	keyType retrieve (string key);
	void totalio() const;
	int countLeaves();
	int read;
	int write;
	// bool search (keyType key);
	// void print (ostream &);
	// void print (ostream &, int nodeAddr, int level);

	// int open (char * name);
	// int create (char * name);
 private:
	BTNode root;
        int rootAddr;
	char treeFileName[80];
	fstream treeFile;
	int height;
	void printTree (int rootAddr);
	void inorder (int rootAddr);
	void reverse (int rootAddr);


	int findAddr (keyType key, BTNode t, int tAddr);
	int findpAddr(keyType key, BTNode t, int tAddr);
	void insert (keyType key, int recAddr, int oneAddr, int twoAddr);
        BTNode getNode (int recAddr);
        void writeNode(int recAddr, BTNode t);

        void placeNode (keyType k,int recAddr,int oneAddr,int twoAddr);

	bool isLeaf (int recAddr);
	bool isLeaf(BTNode t);
	int countLeaves(int recAddr);
        void adjRoot (keyType rootElem, int oneAddr, int twoAddr);
        void splitNode (keyType& key,int recAddr,int& oneAddr,int& twoAddr);
	bool search (string key, int tAddr);

	template <class T>
	string to_string (const T& t);

	void printSet(set<Pair> st);
	void wipeNode(BTNode& t);
	set<Pair> createSet(BTNode t, Pair newP);
	void placeInNode (Pair newP, int currAddr);
	void AddElementAtNextPosition(Pair curr, BTNode *t);
	int findTheAdressOfWhereTheNewKeyShouldBePut(keyType key, int address);
	void AddSetPlusNewElementToNode(set<Pair> st, Pair newPair, BTNode& t);
	void printContents(BTNode node);
	void printTreeContents(BTNode t);
	void printNode(int recAddr, int height);
	// int search (keyType key, int recAddr = -1);

	// BTNode * FindLeaf (keyType key);
	// load a branch into memory down to the leaf with key
	// int Height 
};

#endif
