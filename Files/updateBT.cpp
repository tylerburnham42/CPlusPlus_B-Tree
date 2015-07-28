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
	
	string action;
	fstream infile(argv[2], ios::in);
	while(!infile.eof())
	{
		infile >> action;
		if(action == "I")
		{
			Album a;
			Album b;
			infile >> a;
			infile >> b;
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
	
	bt.close();

}