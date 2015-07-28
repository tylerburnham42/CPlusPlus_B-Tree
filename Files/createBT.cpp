#include <fstream>
#include <sstream>
#include <string>
#include <iostream>
#include "album.h"
#include "btree.h"

typedef char Stringit[80];
using namespace std;
/*
struct BTNode2
{
        int currSize;
        ValueArray contents;
        IndexArray child;
}; 
*/

int main(int argc, char* argv[])
{
	BTree bt;
	bt.reset(argv[1]);

	
	fstream infile(argv[2], ios::in);
	while(!infile.eof())
	{
		Album a;
		infile >> a;
		//cout << a << endl;
		bt.insert(a);
	}


	bt.printTree();
	bt.close();
/*
	BTNode2 buffer;
	fstream test(argv[1], ios::binary | ios::in | ios::out);
	test.read((char *) &buffer, sizeof(buffer));
	for (int i = 0; i < 5; ++i)
	{
		cout << "[" << buffer.child[i] << "]" ;
	}
	cout << endl;	

*/
}