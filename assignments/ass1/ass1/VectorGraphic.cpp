#include <iostream>

#include "Point.h"
#include "Line.h"
#include "GraphicElement.h"
#include "VectorGraphic.h"
using namespace std;

VectorGraphic::VectorGraphic(){
	this->numGraphicElements = 0;
	this->pElements = nullptr;
}

void VectorGraphic::AddGraphicElement(){
	unsigned int i, j;
	cout << "Adding A Graphic Element" << endl;

	/* begin increasing array memory */
	GraphicElement* newElements = new GraphicElement[this->numGraphicElements+1];

	memcpy(newElements, this->pElements, this->numGraphicElements * sizeof(GraphicElement));

	for (i = 0; i < this->numGraphicElements; i++){ /* swap lines */
		newElements[i].pLines = new Line[newElements[i].numLines];
		for (j = 0; j < newElements[i].numLines; j++) newElements[i].pLines[j] = this->pElements[i].pLines[j];
	}

	this->numGraphicElements++;
	unsigned int elemPos = this->numGraphicElements - 1; // current element array pos

	delete[] this->pElements;
	this->pElements = newElements;
	
	for (i = 0; i < elemPos; i++){ /* swap the lines back */
		this->pElements[i].pLines = newElements[i].pLines;
		for (j = 0; j < this->pElements[i].numLines; j++) this->pElements[i].pLines[j] = newElements[i].pLines[j];
	}
	/* done increasing array memory */

	cout << "Please enter the name of the new GraphicElement(<256 characters): ";
	cin >> this->pElements[elemPos].name; // take name in

	bool isValidNumLines = false;
	while (!isValidNumLines){ // validate number of lines input
		cout << "How many lines are there in the new GraphicElement? ";
		cin >> this->pElements[elemPos].numLines;

		if (this->pElements[elemPos].numLines < 1) {
			/*empty, -1 or input contains no integers*/
			cout << endl << "Invalid input, please input an integer number.";
		}
		else { isValidNumLines = true; }
	}

	this->pElements[elemPos].pLines = new Line[this->pElements[elemPos].numLines]; // init pLines

	for (unsigned int i = 0; i < this->pElements[elemPos].numLines; i++) {

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

void VectorGraphic::DeleteGraphicElement(){
	cout << "Deleting A Graphic Element" << endl;
}

void VectorGraphic::ReportVectorGraphic(){
	unsigned int i, j;
	cout << "\nVectorGraphic Report" << endl;
	if (this->numGraphicElements < 1){ /* are the GraphicElements in the array?*/
		cout << "No Graphic Elements to report.";
		return;
	}
	for (i = 0; i < this->numGraphicElements; i++){
		cout << "Reporting element #" << i << endl;
		cout << "Graphic Element name: " << (this->pElements[i]).name << endl;
		for (j = 0; j < this->pElements[i].numLines; j++){
			cout << "Line #" << j << " start x: " << this->pElements[i].pLines[j].start.x << endl;
			cout << "Line #" << j << " start y: " << this->pElements[i].pLines[j].start.y << endl;
			cout << "Line #" << j << " end x: " << this->pElements[i].pLines[j].end.x << endl;
			cout << "Line #" << j << " end y: " << this->pElements[i].pLines[j].end.y << endl;
		}

	}
}