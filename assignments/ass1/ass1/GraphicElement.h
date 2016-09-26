#ifndef GRAPHIC_ELEMENT_H
#define GRAPHIC_ELEMENT_H

class GraphicElement
{
	static const int SIZE = 256;
public:
	unsigned int numLines;
	Line* pLines;
	char name[SIZE];
	GraphicElement()
	{
		numLines = 0;
		pLines = nullptr;
	}
	~GraphicElement()
	{
		if (pLines)
			delete[]pLines;
	}
};

#endif