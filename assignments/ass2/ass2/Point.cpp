/**********************************************************************
Filename:			Point.cpp
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
Purpose:			This file implements the member functions of the Point class.
*********************************************************************/

#include <iostream>

#include "Point.h"
using namespace std;

/********************************************************************
Function name:		operator<<
Purpose:			Overloads std << operator. Outputs a Point class object to stdout
					in a user-readable format.
In parameters:		ostream& output stream, Point& object to output
Out parameters:		ostream&
Version:			1.0
Author:				Lucas Estienne
**********************************************************************/
ostream& operator<<(ostream& os, Point& point){
	os << "x = " << point.x << "; ";
	os << "y = " << point.y;
	return os;
}