/**********************************************************************
Filename:			GraphicElement.cpp
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
Purpose:			This file implements the member functions of the GraphicElement class.
*********************************************************************/

#include <iostream>

#include "Point.h"
#include "Line.h"
#include "GraphicElement.h"

using namespace std;

/********************************************************************
Function name:		GraphicElement::GraphicElement
Purpose:			Overloaded constructor for GraphicElement, allowing to set name, number of
					lines and lines themselves.
In parameters:		Line* pointer to array of lines, char* name, unsigned int number of lines
Out parameters:		GraphicElement
Version:			1.0
Author:				Lucas Estienne
**********************************************************************/
GraphicElement::GraphicElement(Line* pLines, char* name, unsigned int numLines){
	unsigned int i;

	strcpy_s(this->name, name); /* copy name */
	this->numLines = numLines;

	this->pLines = new Line[this->numLines]; /* allocate memory for new Lines*/
	for (i = 0; i < this->numLines; i++)this->pLines[i] = pLines[i]; /* copy lines */
	
	delete[] pLines; /* free up and null the pointer for the passed lines */
	pLines = nullptr;
}

/********************************************************************
Function name:		GraphicElement::GraphicElement
Purpose:			Copy constructor for GraphicElement. 
In parameters:		GraphicElement& element passed to the operator
Out parameters:		GraphicElement
Version:			1.0
Author:				Lucas Estienne
**********************************************************************/
GraphicElement::GraphicElement(GraphicElement& graphicElem){
	this->operator=(graphicElem); /* just call assignment operator instead of rewriting the same code */
}

/********************************************************************
Function name:		GraphicElement::operator=
Purpose:			Overloads the assignment operator to do assign a GraphicElement directly
					without having to deal with as much memory management.
In parameters:		GraphicElement& element passed to the operator
Out parameters:		GraphicElement&
Version:			1.0
Author:				Lucas Estienne
**********************************************************************/
GraphicElement& GraphicElement::operator=(GraphicElement& graphicElem){
	unsigned int i;

	strcpy_s(this->name, graphicElem.name); /* copy name */
	this->numLines = graphicElem.numLines;

	this->pLines = new Line[this->numLines]; /* allocate memory for new Lines*/
	for (i = 0; i < this->numLines; i++) this->pLines[i] = graphicElem.pLines[i]; /* copy lines */
	
	delete[] graphicElem.pLines; /* free up and null the pointer for the passed lines */
	graphicElem.pLines = nullptr;

	return *this;
}

/********************************************************************
Function name:		GraphicElement::operator+
Purpose:			Overloads the + operator to effectively merge two GraphicElement objects.
					Concatenates their name to a max of 256 characters.
In parameters:		GraphicElement& element passed to the operator
Out parameters:		GraphicElement
Version:			1.0
Author:				Lucas Estienne
**********************************************************************/
GraphicElement GraphicElement::operator+(GraphicElement& graphicElem){
	unsigned int i, j;
	char mergedName[256];
	char nameBuffer[513];
	unsigned int mergedNumLines;
	Line* pMergedLines;

	sprintf_s(nameBuffer, "%s_%s", this->name, graphicElem.name); /* concat two strings and make sure length is less than 256*/
	strncpy_s(mergedName, nameBuffer, 255);
	mergedName[255] = '\0'; /* terminate possible last element in char* after strncpy */

	mergedNumLines = this->numLines + graphicElem.numLines;
	pMergedLines = new Line[mergedNumLines]; /* allocate memory for merged Lines*/

	for (i = 0; i < this->numLines; i++)
		pMergedLines[i] = this->pLines[i]; /* copy current instance lines over to new merged lines */
	
	for (j = 0; j < graphicElem.numLines; j++, i++)
		pMergedLines[i] = graphicElem.pLines[j]; /* copy passed instance lines over to new merged lines */
	
	return GraphicElement(pMergedLines, mergedName, mergedNumLines);
}

/********************************************************************
Function name:		operator<<
Purpose:			Overloads std << operator. Outputs a GraphicElement class object to stdout
					in a user-readable format.
In parameters:		ostream& output stream, GraphicElement& object to output
Out parameters:		ostream&
Version:			1.0
Author:				Lucas Estienne
**********************************************************************/
ostream& operator<<(ostream& os, GraphicElement& graphicElem){
	unsigned int j;
	os << "Graphic Element name: " << graphicElem.name << endl;
	for (j = 0; j < graphicElem.numLines; j++){
		os << "Line " << j << ":" << endl;
		os << graphicElem.pLines[j] << endl;
	}
	return os;
}