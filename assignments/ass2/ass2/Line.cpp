/**********************************************************************
Filename:			Line.cpp
Version: 			1.0
Author:				Lucas Estienne
Student No:  		040 819 959
Course Name/Number:	C++ Programming CST8219
Lab Sect: 			302
Assignment #:		2
Assignment name:	Vector Graphic with Overloaded Operators
Due Date:			November 12 2016
Submission Date:	November 12 2016
Professor:			Andrew Tyler
Purpose:			This file implements the member functions of the Line class.
*********************************************************************/

#include <iostream>

#include "Point.h"
#include "Line.h"
using namespace std;

/********************************************************************
Function name:		operator<<
Purpose:			Overloads std << operator. Outputs a Line class object to stdout
					in a user-readable format.
In parameters:		ostream& output stream, Line& object to output
Out parameters:		ostream&
Version:			1.0
Author:				Lucas Estienne
**********************************************************************/
ostream& operator<<(ostream& os, Line& line){
	os << "start Point: " << line.start << "." << endl;
	os << "end Point: " << line.end << "." << endl;
	return os;
}