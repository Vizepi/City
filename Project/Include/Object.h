#pragma once

#include <Quad.h>
#include <Triangle.h>
#include <fstream>

class Object
{

public:

	Object(const std::string & filename);
    ~Object();

	void WriteQuadBox(Quad q1, Quad q2, double heightMin, double heightMax, bool openTop, bool openBottom);
	void WriteTriangleBox(Triangle t1, Triangle t2, double heightMin, double heightMax, bool openTop, bool openBottom);

	void WriteRoof(Quad q, const Vector2 & v, double heightMin, double heightMax);
	void WriteRoof(Triangle t, double heightMin, double heightMax);

	void WriteEmptySpace(Quad q, double heightMin, double heightMax);
	void WriteEmptySpace(Triangle t, double heightMin, double heightMax);

private:

	std::ofstream m_obj;

};