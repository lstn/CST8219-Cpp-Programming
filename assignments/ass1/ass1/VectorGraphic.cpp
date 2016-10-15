/**********************************************************************
Filename:			VectorGraphic.cpp
Version: 			1.0
Author:				Lucas Estienne
Student No:  		040 819 959
Course Name/Number:	C++ Programming CST8219
Lab Sect: 			302
Assignment #:		1
Assignment name:	Vector Graphics in C++
Due Date:			September 25 2016
Submission Date:	September 25 2016
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
Function name:		VectorGraphic::VectorGraphic()
Purpose:			Constructor for the VectorGraphic class. Initializes number of elements to 0 and pElements to nullptr.
In parameters:		none
Out parameters:		VectorGraphic
Version:			1.0
Author:				Lucas Estienne
**********************************************************************/
VectorGraphic::VectorGraphic(){
	this->numGraphicElements = 0;
	this->pElements = nullptr;
}

/********************************************************************
Function name:		VectorGraphic::AddGraphicElement
Purpose:			Adds a graphic element to a VectorGraphic class instance.
					Prompts the user for a GraphicElement name, and validates it. Then prompts the user
					for a number of lines in the element (must be > 0), and the coordinates of the points in
					the line. The function then appends the newly created GraphicElement our instance pElements.
In parameters:		none
Out parameters:		void
Version:			1.0
Author:				Lucas Estienne
**********************************************************************/
void VectorGraphic::AddGraphicElement(){
	unsigned int i, j;
	char inputBuffer[1024];
	bool isValidName = false, isValidNumLines = false;

	cout << "Adding A Graphic Element" << endl;

	/* begin increasing array memory */
	GraphicElement* newElements = new GraphicElement[this->numGraphicElements+1];

	for (i = 0; i < this->numGraphicElements; i++){ /* swap lines */
		newElements[i] = this->pElements[i]; /* copy element */
		newElements[i].pLines = new Line[newElements[i].numLines]; /* alloc new pLines */
		for (j = 0; j < newElements[i].numLines; j++) newElements[i].pLines[j] = this->pElements[i].pLines[j]; /* copy coords */
	}

	this->numGraphicElements++;
	unsigned int elemPos = this->numGraphicElements - 1; /* current last element array pos */

	delete[] this->pElements; /* free old pElements */
	this->pElements = newElements; /* and assign newElements to it */
	
	for (i = 0; i < elemPos; i++){ /* swap the lines back */
		this->pElements[i].pLines = newElements[i].pLines; /* copy pLines */
		for (j = 0; j < this->pElements[i].numLines; j++) this->pElements[i].pLines[j] = newElements[i].pLines[j]; /* copy coords */
	}
	/* done increasing array memory */

	
	while (!isValidName){ // validate number of lines input
		cout << "Please enter the name of the new GraphicElement(<256 characters): ";
		cin >> inputBuffer; // take name in

		if (strlen(inputBuffer) > 256 || strlen(inputBuffer) < 1) { /* too big or empty name input*/
			cout << endl << "Invalid name length." << endl;
		}
		else { 
			strcpy_s(this->pElements[elemPos].name, inputBuffer); /* copy name to element */
			isValidName = true;
		}
	}
	
	while (!isValidNumLines){ // validate number of lines input
		cout << "How many lines are there in the new GraphicElement? ";
		cin >> this->pElements[elemPos].numLines;

		if (this->pElements[elemPos].numLines < 1) { /*empty, -1 or input contains no integers*/
			cout << endl << "Invalid input, please input an integer number." << endl;
		}
		else { isValidNumLines = true; }
	}

	this->pElements[elemPos].pLines = new Line[this->pElements[elemPos].numLines]; /* init pLines for newly added element */

	for (i = 0; i < this->pElements[elemPos].numLines; i++) {

		cout << "Please enter the x coord of the start point of line index " << i << ": ";
		cin >> this->pElements[elemPos].pLines[i].start.x;

		cout << "Please enter the y coord of the start point of line index " << i << ": ";
		cin >> this->pElements[elemPos].pLines[i].start.y;

		cout << "Please enter the x coord of the end point of line index " << i << ": ";
		cin >> this->pElements[elemPos].pLines[i].end.x;

		cout << "Please enter the y coord of the end point of line index " << i << ": ";
		cin >> this->pElements[elemPos].pLines[i].end.y;
	}

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

	if (this->numGraphicElements < 1){ /* are there GraphicElements in the array?*/
		cout << "No Graphic Elements to delete.";
		return;
	}

	unsigned int idx, newIdx, i, j;
	bool isValidIndex = false;

	while (!isValidIndex){ // validate number of lines input
		cout << "Please enter the index of the Graphic Element you wish to delete: ";
		cin >> idx;

		if (idx > this->numGraphicElements-1) { /*Cannot delete an element that doesn't exist*/
			cout << endl << "Invalid input, cannot delete a Graphic Element that doesn't exist." << endl;
		}
		else { isValidIndex = true; }
	}

	unsigned int elemPos = this->numGraphicElements - 1; /* current last element array pos */
	GraphicElement* newElements = new GraphicElement[elemPos]; /* shrinking size by 1 */

	for (i = 0, newIdx = 0; i < this->numGraphicElements; i++){
		if (i != idx){ /* skip element if it's the one to be removed */
			newElements[newIdx] = this->pElements[i]; /* copy element */
			newElements[newIdx].pLines = new Line[newElements[newIdx].numLines]; /* alloc new pLines */
			for (j = 0; j < newElements[newIdx].numLines; j++) newElements[newIdx].pLines[j] = this->pElements[i].pLines[j]; /* copy coords */
			newIdx++; /* only increase if we added an element */
		}
	}

	this->numGraphicElements--;
	elemPos--;

	delete[] this->pElements; /* free old pElements */
	this->pElements = newElements; /* and assign newElements to it */

	for (i = 0; i < this->numGraphicElements; i++){ /* swap the lines back */
		this->pElements[i].pLines = newElements[i].pLines; /* copy pLines */
		for (j = 0; j < this->pElements[i].numLines; j++) this->pElements[i].pLines[j] = newElements[i].pLines[j]; /* copy coords */
	}
	
}

/********************************************************************
Function name:		VectorGraphic::ReportVectorGraphic
Purpose:			Uses cout to report the GraphicElement objects inside the VectorGraphic class instance
					struct in a user-readable format. If no GraphicElements are inside the instance,
					the function reports that there are no elements to be displayed.
In parameters:		none
Out parameters:		void
Version:			1.0
Author:				Lucas Estienne
**********************************************************************/
void VectorGraphic::ReportVectorGraphic(){
	unsigned int i, j;
	cout << "VectorGraphic Report" << endl;
	if (this->numGraphicElements < 1){ /* are there GraphicElements in the array?*/
		cout << "No Graphic Elements to report.";
		return;
	}
	for (i = 0; i < this->numGraphicElements; i++){
		cout << "Reporting element " << i << endl;
		cout << "Graphic Element name: " << this->pElements[i].name << endl;
		for (j = 0; j < this->pElements[i].numLines; j++){
			cout << "Line " << j << " start x: " << this->pElements[i].pLines[j].start.x << endl;
			cout << "Line " << j << " start y: " << this->pElements[i].pLines[j].start.y << endl;
			cout << "Line " << j << " end x: " << this->pElements[i].pLines[j].end.x << endl;
			cout << "Line " << j << " end y: " << this->pElements[i].pLines[j].end.y << endl;
		}

	}
}