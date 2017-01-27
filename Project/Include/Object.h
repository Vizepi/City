#pragma once

#include <Quad.h>
#include <Triangle.h>
#include <fstream>

class Object
{

public:

	Object(const std::string & filename);
    ~Object();

    void WriteQuadBox(const Quad & q1, const Quad & q2, double heightMin, double heightMax, bool openTop, bool openBottom);
    void WriteTriangleBox(Triangle t1, Triangle t2, double heightMin, double heightMax, bool openTop, bool openBottom);
    void WriteQuadFloor(Quad q, BuildingSetting bs, int height);
    void WriteTriangleFloor(Triangle t, BuildingSetting bs, int height);
    void WriteQuadRoof(Quad q, BuildingSetting bs, int height);
    void WriteTriangleRoof(Triangle t, BuildingSetting bs, int height);
    void WriteQuadEmptySpace(Quad q, BuildingSetting bs, int height);
    void WriteTriangleEmptySpace(Triangle t, BuildingSetting bs, int height);

private:

	std::ofstream m_obj;
};
