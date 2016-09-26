#define _CRT_SECURE_NO_WARNINGS
#define _CRTDBG_MAP_ALLOC	// need this to get the line identification
//_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF|_CRTDBG_LEAK_CHECK_DF); // in main, after local declarations
//NB must be in debug build
#include <crtdbg.h>
#include <iostream>
using namespace std;

#include "Point.h"
#include "Line.h"
#include "GraphicElement.h"
#include "VectorGraphic.h"

enum{ RUNNING = 1 };

int main()
{
	char response;
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
	VectorGraphic Image;
	Point p;

	while (RUNNING)
	{
		cout << endl << "Please select an option:" << endl;
		cout << "1. Add a Graphic Element" << endl;
		cout << "2. Delete a GraphicElement" << endl;
		cout << "3. List the Graphic Elements" << endl;
		cout << "q. Quit" << endl;
		cout << "CHOICE: ";
		cin >> response;
		switch (response)
		{
		case '1':Image.AddGraphicElement(); break;
		case '2':Image.DeleteGraphicElement(); break;
		case '3':Image.ReportVectorGraphic(); break;
		case 'q': return 0;
		default:cout << "Please enter a valid option\n";
		}
		cout << endl;
	}
}