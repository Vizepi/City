#pragma once

#include <Quad.h>
#include <Triangle.h>
#include <fstream>

class Object
{

public:

	Object(const std::string & filename);
    ~Object();

    void WriteQuadPlane          (const Quad & q);
    void WriteTrianglePlane      (const Triangle & t);

    void WriteQuadBox            (const Quad & q1,     const Quad & q2,     double heightMin, double heightMax, bool fillTop, bool fillBottom);
    void WriteTriangleBox        (const Triangle & t1, const Triangle & t2, double heightMin, double heightMax, bool fillTop, bool fillBottom);

    void WriteQuadGround         (const Quad & q,     BuildingSetting bs);
    void WriteQuadGroundRotation (Quad & q,     BuildingSetting bs);
    void WriteTriangleGround     (const Triangle & t, BuildingSetting bs);

    void WriteQuadFloor          (const Quad & q,     BuildingSetting bs, int height);
    void WriteQuadFloorRotation  (Quad & q,     BuildingSetting bs, int height);
    void WriteTriangleFloor      (const Triangle & t, BuildingSetting bs, int height);

    void WriteQuadRoof           (const Quad & q,     BuildingSetting bs, int height);
    void WriteTriangleRoof       (const Triangle & t, BuildingSetting bs, int height);

    void WriteQuadEmptySpace     (const Quad & q,     BuildingSetting bs, int height);
    void WriteTriangleEmptySpace (const Triangle & t, BuildingSetting bs, int height);

	std::ofstream m_obj;
};
