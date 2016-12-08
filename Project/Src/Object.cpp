#include <Object.h>

Object::Object(const std::string & filename)
    : m_obj(filename.c_str(), std::ios::out)
{

}

Object::~Object()
{
    m_obj.close();
}

void Object::WriteGround(const Quad & q1, const Quad & q2, double heightMin, double heightMax, bool openTop, bool openBottom)
{
    // Bottom vertice
    m_obj << "v " << q1.A().X() << " " << q1.A().Y() << " " << heightMin << "\n"; // -8
    m_obj << "v " << q1.B().X() << " " << q1.B().Y() << " " << heightMin << "\n"; // -7
    m_obj << "v " << q1.C().X() << " " << q1.C().Y() << " " << heightMin << "\n"; // -6
    m_obj << "v " << q1.D().X() << " " << q1.D().Y() << " " << heightMin << "\n"; // -5
    // Top vertice
    m_obj << "v " << q2.A().X() << " " << q2.A().Y() << " " << heightMax << "\n"; // -4
    m_obj << "v " << q2.B().X() << " " << q2.B().Y() << " " << heightMax << "\n"; // -3
    m_obj << "v " << q2.C().X() << " " << q2.C().Y() << " " << heightMax << "\n"; // -2
    m_obj << "v " << q2.D().X() << " " << q2.D().Y() << " " << heightMax << "\n"; // -1

    // Bottom faces
    if (openBottom) 
    {
        m_obj << "f " << -8 << " " << -7 << " " << -6 << "\n";
        m_obj << "f " << -6 << " " << -5 << " " << -8 << "\n";
    }
    // Top faces
    if (openTop)
    {
        m_obj << "f " << -4 << " " << -3 << " " << -2 << "\n";
        m_obj << "f " << -2 << " " << -1 << " " << -4 << "\n";
    }
    // Back face
    m_obj << "f " << -3 << " " << -2 << " " << -7 << "\n";
    m_obj << "f " << -2 << " " << -6 << " " << -7 << "\n";
    // Right face
    m_obj << "f " << -1 << " " << -2 << " " << -5 << "\n";
    m_obj << "f " << -2 << " " << -6 << " " << -5 << "\n";
    // Front face
    m_obj << "f " << -4 << " " << -5 << " " << -8 << "\n";
    m_obj << "f " << -4 << " " << -1 << " " << -3 << "\n";
    // Left face
    m_obj << "f " << -4 << " " << -3 << " " << -8 << "\n";
    m_obj << "f " << -3 << " " << -7 << " " << -8 << "\n";
}

void Object::WriteGround(Triangle t1, Triangle t2, double heightMin, double heightMax, bool openTop, bool openBottom)
{
    // Bottom vertice
    m_obj << "v " << t1.A().X() << " " << t1.A().Y() << " " << heightMin << "\n"; // -6
    m_obj << "v " << t1.B().X() << " " << t1.B().Y() << " " << heightMin << "\n"; // -5
    m_obj << "v " << t1.C().X() << " " << t1.C().Y() << " " << heightMin << "\n"; // -4
    // Top vertice
    m_obj << "v " << t2.A().X() << " " << t2.A().Y() << " " << heightMax << "\n"; // -3
    m_obj << "v " << t2.B().X() << " " << t2.B().Y() << " " << heightMax << "\n"; // -2
    m_obj << "v " << t2.C().X() << " " << t2.C().Y() << " " << heightMax << "\n"; // -1

    // Bottom faces
    if (openBottom) 
    {
        m_obj << "f " << -6 << " " << -5 << " " << -4 << "\n";
    }
    // Top faces
    if (openTop)
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

void Object::WriteFloor(Quad q, double heightMin, double heightMax)
{

}

void Object::WriteFloor(Triangle t, double heightMin, double heightMax)
{

}

void Object::WriteRoof(Quad q, double heightMin, double heightMax)
{

}

void Object::WriteRoof(Triangle t, double heightMin, double heightMax)
{

}

void Object::WriteEmptySpace(Quad q, double heightMin, double heightMax)
{

}

void Object::WriteEmptySpace(Triangle t, double heightMin, double heightMax)
{

}
