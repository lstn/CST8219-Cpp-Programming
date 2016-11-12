/**********************************************************************
Filename:			VectorGraphic.cpp
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
Purpose:			This file implements the member functions of the VectorGraphic class. These allow the user to add, remove, 
					and display GraphicElements in the VectorGraphic.
*********************************************************************/

#include <iostream>

#include "Point.h"
#include "Line.h"
#include "GraphicElement.h"
#include "VectorGraphic.h"
using namespace std;

/********************************************************************
Function name:		VectorGraphic::AddGraphicElement
Purpose:			Adds a graphic element to a VectorGraphic class instance.
					Prompts the user for a GraphicElement name, and validates it. Then prompts the user
					for a number of lines in the element (must be > 0), and the coordinates of the points in
					the line. The function then uses the += operator to append the GraphicElement to our pElements.
In parameters:		none
Out parameters:		void
Version:			1.0
Author:				Lucas Estienne
**********************************************************************/
void VectorGraphic::AddGraphicElement(){
	cout << "Adding A Graphic Element" << endl;
	unsigned int i;
	char inputBuffer[1024];
	bool isValidName = false, isValidNumLines = false;

	char name[256];
	unsigned int numLines;
	Line* pLines;

	int startX, startY, endX, endY;

	while (!isValidName){ // validate number of lines input
		cout << "Please enter the name of the new GraphicElement(<256 characters): ";
		cin >> inputBuffer; // take name in

		if (strlen(inputBuffer) > 256 || strlen(inputBuffer) < 1) {
			/*too big or empty name input*/
				cout << endl << "Invalid name length." << endl;
		}
		else {
			strcpy_s(name, inputBuffer); /*copy name to element */
				isValidName = true;
		}
	}

	while (!isValidNumLines){ // validate number of lines input
		cout << "How many lines are there in the new GraphicElement? ";
		cin >> numLines;

		if (numLines < 1) {
			/*empty, -1 or input contains no integers*/
				cout << endl << "Invalid input, please input an integer number." << endl;
		}
		else { isValidNumLines = true; }
	}

	pLines = new Line[numLines]; /*init pLines for newly added element */

	for (i = 0; i < numLines; i++) {

		cout << "Please enter the x coord of the start point of line index " << i << ": ";
		cin >> startX;

		cout << "Please enter the y coord of the start point of line index " << i << ": ";
		cin >> startY;

		cout << "Please enter the x coord of the end point of line index " << i << ": ";
		cin >> endX;

		cout << "Please enter the y coord of the end point of line index " << i << ": ";
		cin >> endY; 

		pLines[i] = Line(Point(startX, startY), Point(endX, endY));
	}

	this->operator+=(GraphicElement(pLines, name, numLines));
}

/********************************************************************
Function name:		VectorGraphic::DeleteGraphicElement
Purpose:			Delete a GraphicElement from a VectorGraphic class instance, using an index entered by the user, 
					leaving no unused space in dynamic memory and retaining the order of the remaining elements. If no 
					GraphicElements are inside the instance, the function reports that there are no elements to be removed.
					Also validates the user input index to make sure the element exists.
In parameters:		none
Out parameters:		void
Version:			1.0
Author:				Lucas Estienne
**********************************************************************/
void VectorGraphic::DeleteGraphicElement(){
	cout << "Deleting A Graphic Element" << endl;


	if (numGraphicElements < 1){ /* are there GraphicElements in the array?*/
		cout << "No Graphic Elements to delete.";
		return;
	}
	
	unsigned int idx, newIdx, i;
	bool isValidIndex = false;

	while (!isValidIndex){ // validate number of lines input
		cout << "Please enter the index of the Graphic Element you wish to delete: ";
		cin >> idx;

		if (idx > numGraphicElements-1) { /*Cannot delete an element that doesn't exist*/
			cout << endl << "Invalid input, cannot delete a Graphic Element that doesn't exist." << endl;
		}
		else { isValidIndex = true; }
	}
	
	unsigned int elemPos = numGraphicElements - 1; /* current last element array pos */
	GraphicElement* newElements = new GraphicElement[elemPos]; /* shrinking size by 1 */
	
	for (i = 0, newIdx = 0; i < numGraphicElements; i++){
		if (i != idx){ /* skip element if it's the one to be removed */
			newElements[newIdx] = pElements[i]; /* copy element */
			newIdx++; /* only increase if we added an element */
		}
	}

	numGraphicElements--;

	delete[] pElements; /* free old pElements */
	pElements = newElements; /* and assign newElements to it */
}

/********************************************************************
Function name:		VectorGraphic::operator+=
Purpose:			Overloads the += operator to append a graphic element to the end of the
					pElements array.
In parameters:		GraphicElement& element passed to the operator
Out parameters:		void
Version:			1.0
Author:				Lucas Estienne
**********************************************************************/
void VectorGraphic::operator+=(GraphicElement& graphicElem){
	unsigned int i;
	GraphicElement* newElements = new GraphicElement[numGraphicElements + 1];

	for (i = 0; i < numGraphicElements; i++){
		newElements[i] = pElements[i]; /*copy element */
	}

	numGraphicElements++;
	unsigned int elemPos = numGraphicElements - 1; /*current last element array pos */

	delete[] pElements; /*free old pElements */
	pElements = newElements; /*and assign newElements to it */

	pElements[elemPos] = graphicElem; /* assign passed graphic element to last position in pElements */
}

/********************************************************************
Function name:		VectorGraphic::operator[]
Purpose:			Overloads the [] operator to return the element at said index from pElements.
In parameters:		int index
Out parameters:		GraphicElement&
Version:			1.0
Author:				Lucas Estienne
**********************************************************************/
GraphicElement& VectorGraphic::operator[](int index){
	return pElements[index];
}

/********************************************************************
Function name:		operator<<
Purpose:			Overloads std << operator. Outputs a VectorGraphic class object to stdout 
					in a user-readable format. If no GraphicElements are inside the instance,
					the function reports that there are no elements to be displayed.
In parameters:		ostream& output stream, VectorGraphic& object to output
Out parameters:		ostream&
Version:			1.0
Author:				Lucas Estienne
**********************************************************************/
ostream& operator<<(ostream& os, VectorGraphic& vectorGraphic){
	unsigned int i;
	os << "VectorGraphic Report" << endl;
	if (vectorGraphic.numGraphicElements < 1) { /*are there GraphicElements in the array ? */
		os << "No Graphic Elements to report." << endl;
		return os;
	}
	for (i = 0; i < vectorGraphic.numGraphicElements; i++){
		os << "Reporting Graphic Element " << i << endl;
		os << vectorGraphic.pElements[i];
	}

	return os;
}