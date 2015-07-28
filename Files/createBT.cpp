#include <fstream>
#include <sstream>
#include <string>
#include <iostream>
#include "album.h"
#include "btree.h"

typedef char Stringit[80];
using namespace std;

int main(int argc, char* argv[])
{
	BTree bt;
	bt.reset(argv[1]);

	
	fstream infile(argv[2], ios::in);
	while(!infile.eof())
	{
		Album a;
		infile >> a;
		bt.insert(a);
	}

	bt.printTree();
	bt.close();

}