
#include "album.h"

bool operator < (const Album& a, const Album& b)
{
	//cout <<  "Album StrComp < " << (strcmp(a.UPC, b.UPC) < 0) <<endl;
	return (strcmp(a.UPC, b.UPC) < 0);

}

bool operator == (const Album& a, const Album& b)
{
	//cout <<  "Album StrComp < " << (strcmp(a.UPC, b.UPC) < 0) <<endl;
	return (strcmp(a.UPC, b.UPC) == 0) && (strcmp(a.Title, b.Title)  == 0) && (strcmp(a.Artist, b.Artist) == 0)  ;

}

//, const Album& b
/*
bool Album::operator > (const Album& a)
{
	cout <<  "Album StrComp >" << (strcmp(a.UPC, UPC) < 0) <<endl;
	return (strcmp(UPC, a.UPC) < 0);

}
*/

istream & operator >> (istream & stream, Album & C)
{
	stream.getline(C.UPC, UpTo, '\n');
	if(strlen(C.UPC) == 0 ) 
		return stream;
	stream.getline(C.Artist, UpTo, '\n');
	stream.getline(C.Title, UpTo, '\n');
	return stream;
}

ostream & operator << (ostream & stream, Album & C)
{
	stream << C.UPC << "|";
	stream << C.Artist << "|";
	stream << C.Title << "|";
	return stream;
}

string Album::getUPC ()
{
    return UPC;
}

string Album::getTitle()
{
	return Title;
}

int Album::recordSize()
{
	return sizeof(Album);
}

Album::Album()
{
   strcpy (UPC, "\0");  
   strcpy (Artist, "\0");
   strcpy (Title, "\0"); 
}

Album::Album (const Album& otherAlbum)
{
	strcpy (UPC, otherAlbum.UPC);
	strcpy (Artist, otherAlbum.Artist);
	strcpy (Title, otherAlbum.Title);

}

Album::Album (String upc, String artist, String title)
{
	strcpy (UPC, upc);
	strcpy (Artist, artist);
	strcpy (Title, title);
}

Album & Album::operator = (const Album& otherAlbum)
{
	strcpy (UPC, otherAlbum.UPC);
	strcpy (Artist, otherAlbum.Artist);
	strcpy (Title, otherAlbum.Title);
	return *this;
}