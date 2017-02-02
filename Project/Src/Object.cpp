#include <Object.h>

Object::Object(const std::string & filename)
    : m_obj(filename.c_str(), std::ios::out)
{
}

Object::~Object()
{
    m_obj.close();
}

void Object::WriteQuadPlane(const Quad & q)
{
    m_obj << "v " << q.A().X() << " " << q.A().Y() << " " << 0 << "\n";//-4
    m_obj << "v " << q.B().X() << " " << q.B().Y() << " " << 0 << "\n";//-3
    m_obj << "v " << q.C().X() << " " << q.C().Y() << " " << 0 << "\n";//-2
    m_obj << "v " << q.D().X() << " " << q.D().Y() << " " << 0 << "\n";//-1

    m_obj << "f " << -4 << " " << -3 << " " << -2 << "\n";
    m_obj << "f " << -4 << " " << -2 << " " << -1 << "\n";
}

void Object::WriteTrianglePlane(const Triangle & t)
{
    m_obj << "v " << t.A().X() << " " << t.A().Y() << " " << 0 << "\n";//-3
    m_obj << "v " << t.B().X() << " " << t.B().Y() << " " << 0 << "\n";//-2
    m_obj << "v " << t.C().X() << " " << t.C().Y() << " " << 0 << "\n";//-1

    m_obj << "f " << -3 << " " << -2 << " " << -1 << "\n";
}

void Object::WriteQuadBox(const Quad & q1, const Quad & q2, double hMin,
                          double hMax, bool fillTop, bool fillBottom)
{
	if(q1.A().X() > 10000000.0 ||
		q1.A().Y() > 10000000.0 ||
		q1.B().X() > 10000000.0 ||
		q1.B().Y() > 10000000.0 ||
		q1.C().X() > 10000000.0 ||
		q1.C().Y() > 10000000.0 ||
		q1.D().X() > 10000000.0 ||
		q1.D().Y() > 10000000.0 ||
		q2.A().X() > 10000000.0 ||
		q2.A().Y() > 10000000.0 ||
		q2.B().X() > 10000000.0 ||
		q2.B().Y() > 10000000.0 ||
		q2.C().X() > 10000000.0 ||
		q2.C().Y() > 10000000.0 ||
		q2.D().X() > 10000000.0 ||
		q2.D().Y() > 10000000.0 ||
		q1.A().X() < -10000000.0 ||
		q1.A().Y() < -10000000.0 ||
		q1.B().X() < -10000000.0 ||
		q1.B().Y() < -10000000.0 ||
		q1.C().X() < -10000000.0 ||
		q1.C().Y() < -10000000.0 ||
		q1.D().X() < -10000000.0 ||
		q1.D().Y() < -10000000.0 ||
		q2.A().X() < -10000000.0 ||
		q2.A().Y() < -10000000.0 ||
		q2.B().X() < -10000000.0 ||
		q2.B().Y() < -10000000.0 ||
		q2.C().X() < -10000000.0 ||
		q2.C().Y() < -10000000.0 ||
		q2.D().X() < -10000000.0 ||
		q2.D().Y() < -10000000.0) return;
    // Bottom vertice
    m_obj << "v " << q1.A().X() << " " << q1.A().Y() << " " << hMin << "\n";//-8
    m_obj << "v " << q1.B().X() << " " << q1.B().Y() << " " << hMin << "\n";//-7
    m_obj << "v " << q1.C().X() << " " << q1.C().Y() << " " << hMin << "\n";//-6
    m_obj << "v " << q1.D().X() << " " << q1.D().Y() << " " << hMin << "\n";//-5
    // Top vertice
    m_obj << "v " << q2.A().X() << " " << q2.A().Y() << " " << hMax << "\n";//-4
    m_obj << "v " << q2.B().X() << " " << q2.B().Y() << " " << hMax << "\n";//-3
    m_obj << "v " << q2.C().X() << " " << q2.C().Y() << " " << hMax << "\n";//-2
    m_obj << "v " << q2.D().X() << " " << q2.D().Y() << " " << hMax << "\n";//-1

    // Bottom faces
    if (fillBottom)
    {
        m_obj << "f " << -6 << " " << -7 << " " << -8 << "\n";
        m_obj << "f " << -6 << " " << -8 << " " << -7 << "\n";
    }
    // Top faces
    if (fillTop)
    {
        m_obj << "f " << -4 << " " << -3 << " " << -2 << "\n";
        m_obj << "f " << -4 << " " << -2 << " " << -1 << "\n";
    }
    // Back face
    m_obj << "f " << -7 << " " << -3 << " " << -2 << "\n";
    m_obj << "f " << -7 << " " << -2 << " " << -6 << "\n";
    // Right face
    m_obj << "f " << -6 << " " << -2 << " " << -1 << "\n";
    m_obj << "f " << -6 << " " << -1 << " " << -5 << "\n";
    // Front face
    m_obj << "f " << -5 << " " << -1 << " " << -4 << "\n";
    m_obj << "f " << -5 << " " << -4 << " " << -8 << "\n";
    // Left face
    m_obj << "f " << -8 << " " << -4 << " " << -3 << "\n";
    m_obj << "f " << -8 << " " << -3 << " " << -7 << "\n";
}

void Object::WriteTriangleBox(const Triangle & t1, const Triangle & t2,
                              double hMin, double hMax,
                              bool fillTop, bool fillBottom)
{
    // Bottom vertice
    m_obj << "v " << t1.A().X() << " " << t1.A().Y() << " " << hMin << "\n";//-6
    m_obj << "v " << t1.B().X() << " " << t1.B().Y() << " " << hMin << "\n";//-5
    m_obj << "v " << t1.C().X() << " " << t1.C().Y() << " " << hMin << "\n";//-4
    // Top vertice
    m_obj << "v " << t2.A().X() << " " << t2.A().Y() << " " << hMax << "\n";//-3
    m_obj << "v " << t2.B().X() << " " << t2.B().Y() << " " << hMax << "\n";//-2
    m_obj << "v " << t2.C().X() << " " << t2.C().Y() << " " << hMax << "\n";//-1

    // Bottom faces
    if (fillBottom)
    {
        m_obj << "f " << -6 << " " << -5 << " " << -4 << "\n";
    }
    // Top faces
    if (fillTop)
    {
        m_obj << "f " << -3 << " " << -2 << " " << -1 << "\n";
    }
    // Front face
    m_obj << "f " << -3 << " " << -4 << " " << -6 << "\n";
    m_obj << "f " << -3 << " " << -1 << " " << -4 << "\n";
    // Right face
    m_obj << "f " << -1 << " " << -5 << " " << -4 << "\n";
    m_obj << "f " << -1 << " " << -2 << " " << -5 << "\n";
    // Left face
    m_obj << "f " << -2 << " " << -6 << " " << -5 << "\n";
    m_obj << "f " << -2 << " " << -3 << " " << -6 << "\n";
}

void Object::WriteQuadGround(const Quad & q, BuildingSetting bs)
{
    WriteQuadBox(q, q, 0, bs.FloorSize + bs.FloorSpaceSize, true, false);
}

void Object::WriteQuadGroundRotation(Quad & q, BuildingSetting bs)
{
    q.Rotate(3);

    WriteQuadBox(q, q, 0, bs.FloorSize + bs.FloorSpaceSize, true, false);
}

void Object::WriteTriangleGround(const Triangle & t, BuildingSetting bs)
{
    WriteTriangleBox(t, t, 0, bs.FloorSize + bs.FloorSpaceSize, true, false);
}

void Object::WriteQuadFloor(const Quad & q, BuildingSetting bs, int height)
{
    Quad qShrinked = Quad(q);
    qShrinked.Shrink(bs.FloorSpaceSize);

    WriteQuadBox(qShrinked, qShrinked,
        height * (bs.FloorSize + bs.FloorSpaceSize),
        height * (bs.FloorSize + bs.FloorSpaceSize) + bs.FloorSpaceSize,
        false, false);

    WriteQuadBox(q, q,
        height * (bs.FloorSize + bs.FloorSpaceSize) + bs.FloorSpaceSize,
        (height + 1) * (bs.FloorSize + bs.FloorSpaceSize),
        true, true);
}

void Object::WriteQuadFloorRotation(Quad & q, BuildingSetting bs, int height)
{
	q.Rotate(3);

	q.Shrink(bs.FloorSpaceSize);
    Quad qShrinked = Quad(q);
    qShrinked.Shrink(bs.FloorSpaceSize);


    WriteQuadBox(qShrinked, qShrinked,
        height * (bs.FloorSize + bs.FloorSpaceSize),
        height * (bs.FloorSize + bs.FloorSpaceSize) + bs.FloorSpaceSize,
        false, false);

    WriteQuadBox(q, q,
        height * (bs.FloorSize + bs.FloorSpaceSize) + bs.FloorSpaceSize,
        (height + 1) * (bs.FloorSize + bs.FloorSpaceSize),
        true, true);

}

void Object::WriteTriangleFloor(const Triangle & t, BuildingSetting bs,
                                int height)
{
    Triangle tShrinked = Triangle(t);
    tShrinked.Shrink(bs.FloorSpaceSize);

    WriteTriangleBox(tShrinked, tShrinked,
        height * (bs.FloorSize + bs.FloorSpaceSize),
        height * (bs.FloorSize + bs.FloorSpaceSize) + bs.FloorSpaceSize,
        false, false);

    WriteTriangleBox(t, t,
        height * (bs.FloorSize + bs.FloorSpaceSize) + bs.FloorSpaceSize,
        (height + 1) * (bs.FloorSize + bs.FloorSpaceSize),
        true, true);
}

void Object::WriteQuadRoof(const Quad & q, BuildingSetting bs, int height)
{
    double r = Random::NextDouble();
    float roofFence = bs.FloorSpaceSize * 20;

    if (r < 0.25)
    {
        Quad qShrinked = Quad(q);
        qShrinked.Shrink(roofFence);

        Quad sideQuads[4];
        sideQuads[0] = Quad(q.A(), q.B(), qShrinked.B(), qShrinked.A());
        sideQuads[1] = Quad(q.B(), q.C(), qShrinked.C(), qShrinked.B());
        sideQuads[2] = Quad(q.C(), q.D(), qShrinked.D(), qShrinked.C());
        sideQuads[3] = Quad(q.D(), q.A(), qShrinked.A(), qShrinked.D());

        for (short i = 0; i < 4; ++i)
        {
            WriteQuadBox(sideQuads[i], sideQuads[i],
                height * (bs.FloorSize + bs.FloorSpaceSize),
                height * (bs.FloorSize + bs.FloorSpaceSize) + roofFence,
                true, false);
        }
    }
    else if (r < 0.4)
    {
        float roofDiagonalOffset = bs.FloorSpaceSize * 150;

        Quad qShrinkedBottom = Quad(q);
        qShrinkedBottom.Shrink(roofFence);

        Quad qShrinkedTop = Quad(qShrinkedBottom);
        qShrinkedTop.Shrink(roofDiagonalOffset);

        WriteQuadBox(qShrinkedBottom, qShrinkedTop,
            height * (bs.FloorSize + bs.FloorSpaceSize),
            height * (bs.FloorSize + bs.FloorSpaceSize) + roofDiagonalOffset,
            true, false);
    }
    else if (r < 0.7)
    {
        float roofGutter = bs.FloorSpaceSize * 30;
        Quad qGrown = Quad(q);
        qGrown.Shrink(-roofFence);

        WriteQuadBox(qGrown, qGrown,
            height * (bs.FloorSize + bs.FloorSpaceSize),
            height * (bs.FloorSize + bs.FloorSpaceSize) + roofFence,
            true, true);
    }
    else
    {
        Vector2 centerQ = q.Center();
        Quad centerQuad = Quad(
			centerQ * 0.99 + q.A() * 0.01, 
			centerQ * 0.99 + q.B() * 0.01,
			centerQ * 0.99 + q.C() * 0.01,
			centerQ * 0.99 + q.D() * 0.01);

        WriteQuadBox(q, centerQuad,
            height * (bs.FloorSize + bs.FloorSpaceSize),
            (height + 1) * (bs.FloorSize + bs.FloorSpaceSize),
            true, true);
    }
}

void Object::WriteTriangleRoof(const Triangle & t, BuildingSetting bs, int height)
{
    double r = Random::NextDouble();
    float roofFence = bs.FloorSpaceSize * 20;

    if (r < 0.25)
    {
        Triangle tShrinked = Triangle(t);
        tShrinked.Shrink(roofFence);

        Quad sideQuads[3];
        sideQuads[0] = Quad(t.A(), t.B(), tShrinked.B(), tShrinked.A());
        sideQuads[1] = Quad(t.B(), t.C(), tShrinked.C(), tShrinked.B());
        sideQuads[2] = Quad(t.C(), t.A(), tShrinked.A(), tShrinked.C());

        for (short i = 0; i < 4; ++i)
        {
            WriteQuadBox(sideQuads[i], sideQuads[i],
                height * (bs.FloorSize + bs.FloorSpaceSize),
                height * (bs.FloorSize + bs.FloorSpaceSize) + roofFence,
                true, false);
        }
    }
    else if (r < 0.4)
    {
        float roofDiagonalOffset = bs.FloorSpaceSize * 150;

        Triangle tShrinkedBottom = Triangle(t);
        tShrinkedBottom.Shrink(roofFence);

        Triangle tShrinkedTop = Triangle(tShrinkedBottom);
        tShrinkedTop.Shrink(roofDiagonalOffset);

        WriteTriangleBox(tShrinkedBottom, tShrinkedTop,
            height * (bs.FloorSize + bs.FloorSpaceSize),
            height * (bs.FloorSize + bs.FloorSpaceSize) + roofDiagonalOffset,
            true, false);
    }
    else if (r < 0.7)
    {
        float roofGutter = bs.FloorSpaceSize * 30;
        Triangle tGrown = Triangle(t);
        tGrown.Shrink(-roofFence);

        WriteTriangleBox(tGrown, tGrown,
            height * (bs.FloorSize + bs.FloorSpaceSize),
            height * (bs.FloorSize + bs.FloorSpaceSize) + roofFence,
            true, true);
    }
    else
    {
        Vector2 centerT = t.Center();
        Triangle centerTriangle = Triangle(centerT, centerT, centerT);

        WriteTriangleBox(t, centerTriangle,
            height * (bs.FloorSize + bs.FloorSpaceSize),
            (height + 1) * (bs.FloorSize + bs.FloorSpaceSize),
            true, true);
    }
}

void Object::WriteQuadEmptySpace(const Quad & q, BuildingSetting bs, int height)
{
    WriteQuadPlane(q);
}

void Object::WriteTriangleEmptySpace(const Triangle & t, BuildingSetting bs, int height)
{
    WriteTrianglePlane(t);
}
