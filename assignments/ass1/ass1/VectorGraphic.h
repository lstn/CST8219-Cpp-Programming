#ifndef VECTOR_GRAPHIC_H
#define VECTOR_GRAPHIC_H

class VectorGraphic
{
	unsigned int numGraphicElements{};
	GraphicElement* pElements{};
public:

	VectorGraphic();
	~VectorGraphic()
	{
		if (pElements)
			delete[]pElements;
	}
	void AddGraphicElement();
	void DeleteGraphicElement();
	void ReportVectorGraphic();
};

#endif