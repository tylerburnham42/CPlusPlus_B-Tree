#include "btree.h"

BTree::BTree()
{
	//cout << "init" << endl;
	//root = NULL;
	//rootAddr = NULL;

}

BTree::BTree(char * filename)
{
	//cout << "init" << endl;
	//root = NULL;
	//rootAddr = NULL;
	strcpy (treeFileName, filename);
	treeFile.open(filename, ios::binary | ios::in | ios::out);

	BTNode header = getNode(0);
	rootAddr = header.child[0]; 
	root = getNode(rootAddr);

	//printContents(header);
	//printContents(root);
	//cout << "root is at " << rootAddr << endl;

	read = write = 0;

}


 
void BTree::reset (char * filename)
{
	strcpy (treeFileName, filename);


	treeFile.open(treeFileName, ios::binary | ios::out);
   	treeFile.close();
   	treeFile.open(treeFileName, ios::binary | ios::in | ios::out);

   	//writeHeader(filename);

   	BTNode header;
   	writeNode(0, header);



   	BTNode newRoot;
   	newRoot.currSize = 0;
   	treeFile.seekg(0, ios::end);
   	int newAddr = treeFile.tellp();
   	writeNode(newAddr, newRoot);

   	rootAddr = newAddr;
   	root = newRoot;

	header.child[0] = newAddr;
	writeNode(0, header);

	read = write = 0;


}

BTNode BTree::getNode (int recAddr)
{
	read += 1;
	BTNode buffer;
	treeFile.clear();
	treeFile.seekg(recAddr);
	treeFile.read((char *) &buffer, sizeof(buffer));
	treeFile.clear();
	return buffer;

}


void BTree::writeNode(int recAddr, BTNode t)
{
	write +=1;
	treeFile.clear();
	treeFile.seekp(recAddr);
	treeFile.write((char*) &t, sizeof(t));
	treeFile.clear();
}



void BTree::writeHeader (char* filename)
{
	
	BTNode node;
	node.currSize = 0;
	node.child[0] = 0;
	writeNode(0, node);

	//String key = "123456";
	//String name = "ABCDEFGHIJK";
	//String other = "',.pyfoeuk;q";
	//Album a(key,name,other);
	//printNode(0);
} 

bool BTree::isLeaf(BTNode t)
{
	for(int x = 0; x< t.currSize ; x++)
	{
		if(t.child[x] != -1)
		{
			//cout << t.child[x] << " - ";
			return false;
		}
	}
	//cout << "nope12345 " << endl;
	
	return true;
}

void BTree::placeInNode (Pair newP, int currAddr)
{
	BTNode t = getNode(currAddr);
	
	//cout << "rootAddr = " << rootAddr << endl;
	//cout << "Placing in Node with contents from adress " << currAddr << endl;
	//printContents(t);
	

	set<Pair> st;
	set<Pair>::iterator itt;

	st = createSet(t, newP);
	//printSet(st);

	wipeNode(t);
	
	//wipe node


	if(st.size()>ORDER-1)
	{
		//cout << endl << "Time To Split" <<endl;
		set<Pair> lSet;
		set<Pair> rSet;
		BTNode leftSide;
		BTNode rightSide;
		wipeNode(leftSide);
		wipeNode(rightSide);
		Pair moveUp;

		int half = (ORDER/2);
		int count = 0;
		for(itt = st.begin(); itt!= st.end(); itt++)
		{
			Pair curr = *itt;
			if(count<half)
			{
				//cout << " < " << curr.element << endl;
				//AddElementAtNextPosition(curr, &leftSide);
				lSet.insert(curr);
			}
			else if (count>half)
			{
				//cout << " > " << curr.element << endl;
				//AddElementAtNextPosition(curr, &rightSide);
				rSet.insert(curr);
			}
			else
			{
				//cout << " = " << curr.element << endl;
				moveUp = curr;
			}

			count ++;
		}
		Pair blank;
		AddSetPlusNewElementToNode(lSet, blank, leftSide);
		AddSetPlusNewElementToNode(rSet, blank, rightSide);


		BTNode d;
		wipeNode(d);
		writeNode(currAddr, d);
		
		//cout << "this node at "<< currAddr << " should be blank " << d.currSize << endl;
		//printContents(d);
		//cout << endl;

		cout << "Split! Node elevated: " << moveUp.element << endl; 
		//cout << "<<<<LEFT<<<<" << endl;
		//printContents(leftSide);
		treeFile.seekp(0, ios::end);
		moveUp.loffset = treeFile.tellp();
		writeNode(treeFile.tellp(), leftSide);

		/*
		BTNode test = getNode(moveUp.loffset);
		cout << "Left Offset is " << moveUp.loffset <<endl;
		printContents(test);
		*/

		//cout << ">>>>Right>>>" << endl;
		//printContents(rightSide);
		treeFile.seekp(0, ios::end);
		moveUp.roffset = treeFile.tellp();
		writeNode(treeFile.tellp(),rightSide);

		//cout << "New Node Adresses are [" << moveUp.loffset << "," << moveUp.roffset << "]" << endl;


		//cout << moveUp.element << endl << moveUp.loffset << " " << moveUp.roffset << endl;
		if(currAddr == rootAddr)
		{
			
			BTNode newRoot;
			wipeNode(newRoot);
			treeFile.seekp(0, ios::end);
			rootAddr = treeFile.tellp();
			//cout << "New Root At " << rootAddr << endl;
			writeNode(treeFile.tellp(),newRoot);
			placeInNode (moveUp, rootAddr);

		}
		else
		{
			int newaddress = findTheAdressOfWhereTheNewKeyShouldBePut(moveUp.element, rootAddr);
			//cout << "Adding Element to node At " << newaddress << endl;
			placeInNode (moveUp, newaddress);
			return;
		}
	}
	else
	{
		/*
		int count = 0;
		for(itt = st.begin(); itt!= st.end(); itt++)
		{
			Pair curr = *itt;
			AddElementAtNextPosition(curr, &t);

			printContents(t);
			count ++;
		}
		*/

		AddSetPlusNewElementToNode(st, newP, t);

		//cout << "----Node Before Write-----" << endl;
		//printContents(t);
		//cout << "--------------------------" << endl;

		writeNode(currAddr, t);


		//cout << "----Node After Write-----" << endl;
		//printContents(t);
		//cout << "------------------------" << endl;
	}

}

set<Pair> BTree::createSet(BTNode t, Pair newP)
{
	set<Pair> st;

	for(int x = 0; x < t.currSize; x++)
	{
		Pair P = {t.contents[x],t.child[x],t.child[x+1]};
		st.insert(P);
	}

	st.insert(newP);

	return st;
}

void BTree::AddElementAtNextPosition(Pair curr, BTNode *t)
{
	//cout << endl << curr.element << endl;
	for(int x = 0; x<t->currSize; x++)
	{
		//cout << "[" << (t->contents[x]).getUPC() << "]" << endl;
		if((t->contents[x]).getUPC().empty())
		{
			t->contents[x] = curr.element;
			t->currSize += 1;
			if(curr.loffset != -1 && getNode(curr.loffset).currSize != 0)
				t->child[x] = curr.loffset;
			if(curr.roffset != -1 && getNode(curr.roffset).currSize != 0)
				t->child[x] = curr.roffset;
			return;
		}

	}
	//cout << "ERROR!!! Could not add element" << endl;

}

void BTree::AddSetPlusNewElementToNode(set<Pair> st, Pair newPair, BTNode& t)
{
	set<Pair>::iterator itt;
	int newPairAddr = -1;
	int index = 0;
	Pair curr;
	for(itt = st.begin(); itt!= st.end(); itt++)
	{
		//cout << "index is " << index << endl;
		curr = *itt;
		t.currSize += 1;
		if(curr.element == newPair.element)
		{
			newPairAddr = index;
			//cout << "newPairAddr = " << newPairAddr << endl ;
			index ++;
			continue;

		}
		t.contents[index] = curr.element;
		t.child[index] = curr.loffset;
		index ++;
		//printContents(t);
	}
	//cout << "Final Index is " << index << endl;
	if(!(curr.element == newPair.element))
		t.child[index] = curr.roffset;
	//printContents(t);
	if(newPairAddr == -1)
	{
		//cout << "no new pair" << endl;
		return;
	}
	else
	{
		//cout << "adding new pair element into node" << endl; 
		t.child[newPairAddr] = newPair.loffset;
		t.child[newPairAddr+1] = newPair.roffset;
		t.contents[newPairAddr] = newPair.element;
	}
	//printContents(t);

}

bool BTree::search (string key)
{
	//cout << "search " << key <<endl;
	return search(key, rootAddr);
}

bool BTree::search (string key, int address)
{
	//cout << "Search Key " << key << " at address " << address << endl;
	BTNode t = getNode(address);
	int currentSize = t.currSize;
	if(currentSize < 1)
		return false;

	bool nextAddr = false;


	for(int x = 0; x<currentSize; x++)
	{
		//cout << key.getUPC() << " <" << t.contents[x].getUPC() << endl;
		if(key == t.contents[x].getUPC())
		{
			cout << t.contents[x] << endl;
			return true;

		}
		else if(key < t.contents[x].getUPC())	
		{
			if (t.child[x] == -1)
			{
				return false;
			}
			else
			{
				return search(key, t.child[x]);
			}
		}
	}

	return search(key, t.child[currentSize]);


	//return address;
}


int BTree::findTheAdressOfWhereTheNewKeyShouldBePut(keyType key, int address)
{
	BTNode t = getNode(address);
	int currentSize = t.currSize;
	if(currentSize < 1)
		return 0;

	int nextAddr = -1;

	if(!isLeaf(t))
	{
		//cout << "not leaf" <<endl;
		bool foundIt = false;
		for(int x = 0; x<currentSize; x++)
		{
			//cout << key.getUPC() << " <" << t.contents[x].getUPC() << endl;
			if(key < t.contents[x])	
			{
				nextAddr = findTheAdressOfWhereTheNewKeyShouldBePut(key, t.child[x]);
				return (nextAddr>0) ? nextAddr: address;
			}
		}
		nextAddr = findTheAdressOfWhereTheNewKeyShouldBePut(key, t.child[currentSize]);
		return (nextAddr>0) ? nextAddr: address;
	}

	return address;

}

void BTree::insert (keyType key)
{
	cout << "Insert " << key << endl;

	//cout << "----Root-----" << endl;
	//printContents(root);
	//cout << "-------------" << endl;
	
	//cout << "here" <<endl;
	//cout << "CurrentNdde Size" << currentNode->currSize <<endl;
	if(root.currSize == 0)
	{
		//cout << "Root is 0 adding element" << endl;
		root.currSize = 1;
		root.contents[0] = key;
		root.child[0] = root.child[1] = -1;
		writeNode(rootAddr, root);
		//printContents(root);
		return;
	}

	int currAddr = findTheAdressOfWhereTheNewKeyShouldBePut(key, rootAddr);
	//cout << " insert adress @ - " << currAddr << endl;
	Pair newP = {key,-1,-1};
	placeInNode(newP, currAddr);
	//cout << "rootAddr = " << rootAddr <<endl;

}

void BTree::wipeNode(BTNode& t)
{
	for(int x =0; x<ORDER; x++)
	{
		keyType blank;
		if(x<(ORDER-1))
			t.contents[x] = blank;
		
		t.child[x] = -1;
	}
	t.currSize = 0;	
}


void BTree::printSet(set<Pair> st)
{
	cout << "----Printing Set----" << endl;
	set<Pair>::iterator itt;
	for(itt = st.begin(); itt!= st.end(); itt++)
	{
		Pair curr = *itt;
		cout << curr.element << endl;
	}
	cout << "--------------------" << endl;
}

void BTree::printTree()
{
	cout << endl << endl << "PRINTING ENTIRE TREE" << endl;
	printNode(rootAddr, 0);
}

void BTree::printTreeContents(BTNode t)
{
	string keys;
	string locs;
	for(int x = 0; x<ORDER; x++)
	{
		if(x==t.currSize)
			keys += "::";
		if((x-1)==t.currSize)
			locs += "::";
		if(x<(ORDER-1))
			keys += "[" + t.contents[x].getUPC() + "]";
		
		locs += "[" + to_string(t.child[x]) + "]";
		if(t.child[x] != -1)
			printTreeContents(getNode(t.child[x]));
	}
	if(t.child[ORDER-1] != -1)
		printTreeContents(getNode(t.child[ORDER-1]));
	cout << keys << endl;
	cout << locs<< endl;


}

void BTree::printNode(int recAddr,int height)
{
	BTNode node  = getNode(recAddr);
	int size = node.currSize;
	cout << endl << "----Node Height of " << height << " ----" << endl;
	//cout << "Adress = " << recAddr <<endl;
	for(int x=0; x<size; x++)
	{
		cout << node.contents[x] << endl;
	}
	for(int x=0; x<size; x++)
	{
		if(node.child[x] != -1)
			printNode(node.child[x], height+1);
	}
	if(node.child[size] != -1)
		printNode(node.child[size], height+1);
}

void BTree::printContents(BTNode node)
{
	string keys;
	string locs;
	for(int x =0; x<ORDER; x++)
	{
		if(x==node.currSize)
			keys += "::";
		if((x-1)==node.currSize)
			locs += "::";
		if(x<(ORDER-1))
			keys += "[" + node.contents[x].getTitle().substr(0, 10) + "]";
		
		locs += "[" + to_string(node.child[x]) + "]";
	}
	cout << keys << endl;
	cout << locs<< endl;

}

template <class T>
inline string BTree::to_string (const T& t)
{
    stringstream ss;
    ss << t;
    return ss.str();
}

void BTree::close ()
{
	BTNode header;
	wipeNode(header);
	//cout << "Final Saved Root Addr =" << rootAddr << endl;
	header.child[0] = rootAddr;
	writeNode(0, header);
	//printContents(header);

	treeFile.close();
}
