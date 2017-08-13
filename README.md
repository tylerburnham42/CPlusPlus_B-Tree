# C++ Album B-Tree
This program is a c++ program that reads in a series of albulms and stores it in a binary file as a B-Tree.
Two pragrams are included:
- createBT.cpp - Creates a btree from an albulm file
- updateBT.cpp - Updates an existing btree 

Creates and updates a BTree of albulms.

It was created on using a command line compiler.  To compile run:
```
c++ -c album.cpp
c++ -c btree.cpp
c++ createBT.cpp album.o btree.o
c++ updateBT.cpp album.o btree.o
```

To run the CreateBT Program use:

`./a.out [Database Binary File] [Input File]`

###Example CreateBT Run
```
[user@location]$ ./a.out binaryfile.dat TestFiles/album.med
Insert 08722|Counting Crows|This Desert Life|
Insert 75599|U2|All That You Can't Leave Behind|
Insert 42276|Tom Petty|Into the Great Wide Open|
Insert 02284|Kenny Loggins|Footloose|
Insert 20831|Dave Matthews|Everyday|
Split! Node elevated: 20831|Dave Matthews|Everyday|
Insert 99000|Train|Drops of Jupiter|
Insert 00100|Dido|No Angel|
Insert 00101|Eva Cassidy|Songbird|
Insert 00102|Metallica|Ride the Lightning|
Split! Node elevated: 00102|Metallica|Ride the Lightning|
Insert 00000|Any Song|Any Artist|
Insert 00001|Any Song|Any Artist|
Insert 00002|Any Song|Any Artist|
Split! Node elevated: 00002|Any Song|Any Artist|
Insert 00003|Any Song|Any Artist|
Insert 00004|Any Song|Any Artist|
Insert 00005|Any Song|Any Artist|
Split! Node elevated: 00005|Any Song|Any Artist|
Insert 99999|Any Song|Any Artist|
Insert 99998|Any Song|Any Artist|
Split! Node elevated: 99000|Train|Drops of Jupiter|
Split! Node elevated: 00102|Metallica|Ride the Lightning|
Insert 00006|Any Song|Any Artist|
Insert 00007|Any Song|Any Artist|
Insert 00008|Any Song|Any Artist|
Split! Node elevated: 00008|Any Song|Any Artist|
Insert 00009|Any Song|Any Artist|
Insert 00010|Any Song|Any Artist|
Insert 00011|Any Song|Any Artist|
Split! Node elevated: 00011|Any Song|Any Artist|
Insert 00012|Any Song|Any Artist|
Insert 00013|Any Song|Any Artist|
Insert 00014|Any Song|Any Artist|
Split! Node elevated: 00014|Any Song|Any Artist|
Split! Node elevated: 00008|Any Song|Any Artist|
Insert |||


PRINTING ENTIRE TREE

----Node Height of 0 ----
00008|Any Song|Any Artist|
00102|Metallica|Ride the Lightning|

----Node Height of 1 ----
00002|Any Song|Any Artist|
00005|Any Song|Any Artist|

----Node Height of 2 ----
|||
00000|Any Song|Any Artist|
00001|Any Song|Any Artist|

----Node Height of 2 ----
00003|Any Song|Any Artist|
00004|Any Song|Any Artist|

----Node Height of 2 ----
00006|Any Song|Any Artist|
00007|Any Song|Any Artist|

----Node Height of 1 ----
00011|Any Song|Any Artist|
00014|Any Song|Any Artist|

----Node Height of 2 ----
00009|Any Song|Any Artist|
00010|Any Song|Any Artist|

----Node Height of 2 ----
00012|Any Song|Any Artist|
00013|Any Song|Any Artist|

----Node Height of 2 ----
00100|Dido|No Angel|
00101|Eva Cassidy|Songbird|

----Node Height of 1 ----
20831|Dave Matthews|Everyday|
99000|Train|Drops of Jupiter|

----Node Height of 2 ----
02284|Kenny Loggins|Footloose|
08722|Counting Crows|This Desert Life|

----Node Height of 2 ----
42276|Tom Petty|Into the Great Wide Open|
75599|U2|All That You Can't Leave Behind|

----Node Height of 2 ----
99998|Any Song|Any Artist|
99999|Any Song|Any Artist|
```
