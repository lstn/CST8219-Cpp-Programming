#include <iostream>

#include "Point.h"
#include "Line.h"
#include "GraphicElement.h"
#include "VectorGraphic.h"
using namespace std;

VectorGraphic::VectorGraphic(){}

void VectorGraphic::AddGraphicElement(){
	GraphicElement newGraphicElement;
	VectorGraphic vectorBuffer;
	char inputBuffer[1024];
	bool isValidName = false, isValidNumLines = false, isValidCoords = false;
	int numLines, xCoord, yCoord, i;
	unsigned int j;

	cout << "Adding A Graphic Element" << endl;

	while (!isValidName){
		cout << "Please enter the name of the new GraphicElement(<256 characters): ";
		cin >> inputBuffer;

		if (strlen(inputBuffer) > 255 || strlen(inputBuffer) < 1) { // Leave 1 char to append line termination '\0'.
			cout << "Invalid name length.\n" << endl;
		}
		else { isValidName = true; }
	}

	while (!isValidNumLines){
		cout << "How many lines are there in the new GraphicElement? ";
		cin >> numLines; 

		if (numLines < 1) { /* empty, -1 or input contains no integers*/
			cout << endl << "Invalid input, please input an integer number.";
		}
		else { isValidNumLines = true; }
	}

	strcpy_s(newGraphicElement.name, inputBuffer);
	newGraphicElement.numLines = numLines;
	newGraphicElement.pLines = new Line[newGraphicElement.numLines];

	for (i = 0; i < numLines; i++) {

		cout << "Please enter the x coord of the start point of line index " << i << ": ";
		cin >> newGraphicElement.pLines[i].start.x;

		cout << "Please enter the y coord of the start point of line index " << i << ": ";
		cin >> newGraphicElement.pLines[i].start.y;

		cout << "Please enter the x coord of the end point of line index " << i << ": ";
		cin >> newGraphicElement.pLines[i].end.x;

		cout << "Please enter the y coord of the end point of line index " << i << ": ";
		cin >> newGraphicElement.pLines[i].end.y;
	}

	vectorBuffer.numGraphicElements = (this->numGraphicElements > 0) ? this->numGraphicElements : 0;
	vectorBuffer.pElements = new GraphicElement[vectorBuffer.numGraphicElements];

	for (j = 0; j < vectorBuffer.numGraphicElements; j++) { /* copy pImage to buffer so we can reinit pImage */
		memcpy(&vectorBuffer.pElements[j], &this->pElements[j], sizeof(GraphicElement));
		/*vectorBuffer.pElements[j] = this->pElements[j];*/
	}

	this->numGraphicElements += 1; /* increase the number of graphic elements*/

	this->pElements = new GraphicElement[this->numGraphicElements];
	for (j = 0; j < vectorBuffer.numGraphicElements; j++) { /* copy pImage to buffer so we can reinit pImage */
		memcpy(&vectorBuffer.pElements[j], &this->pElements[j], sizeof(GraphicElement));
		/*this->pElements[j] = vectorBuffer.pElements[j];*/
	}
	this->pElements[j] = newGraphicElement;

}

void VectorGraphic::DeleteGraphicElement(){
	cout << "Deleting A Graphic Element" << endl;
}

void VectorGraphic::ReportVectorGraphic(){
	unsigned int i, j;
	cout << "VectorGraphic Report" << endl;

	if (this->numGraphicElements < 1){ /* are the GraphicElements in the array?*/
		cout << "No Graphic Elements to report.";
		return;
	}
	for (i = 0; i < this->numGraphicElements; i++){
		cout << "Reporting element #" << i << endl;
		cout << "Graphic Element name: " << (this->pElements[i]).name << endl;
		for (j = 0; j < (this->pElements[i]).numLines; j++){
			cout << "Line #" << j << " start x: " << this->pElements[i].pLines[j].start.x << endl;
			cout << "Line #" << j << " start y: " << this->pElements[i].pLines[j].start.y << endl;
			cout << "Line #" << j << " end x: " << this->pElements[i].pLines[j].end.x << endl;
			cout << "Line #" << j << " end y: " << this->pElements[i].pLines[j].end.y << endl;
		}

	}
}