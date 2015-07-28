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
	BTree bt(argv[1]);
	//bt.printTree();
	//bt.reset(argv[1]);

	
	string action;
	fstream infile(argv[2], ios::in);
	while(!infile.eof())
	{
		infile >> action;
		//cout << "action = " << action << endl;
		if(action == "I")
		{
			//string dumb;
			//infile >> dumb;
			//cout << "dumb" << dumb << endl;
			Album a;
			Album b;
			infile >> a;
			infile >> b;
			//cout << "Album" << a << endl;
			//cout << "Album2" << b << endl;
			//cout << "Inserting " << b << endl;
			bt.insert(b);
		}
		else if(action == "S")
		{
			string key;
			infile >> key;
			cout << "Album with key=" << key << " " << (bt.search(key)?" was found":"wasnt found") << endl <<endl;
		}
	}

	cout << endl << endl;
	cout << "Reads " << bt.read << endl;
	cout << "Writes " << bt.write << endl;
	
	//bt.printTree();
	bt.close();

}