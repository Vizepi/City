#pragma once

#include <Vector.h>
#include <Triangle.h>
#include <Shape.h>

class Quad : public Shape
{
public:

	inline Quad()
	{

	}

	virtual void Subdivide(std::vector<Shape>& mesh);
	virtual void BuildNeighborhood(std::vector<Shape>& mesh);
	virtual void BuildBuilding(std::vector<Shape>& mesh);

	inline double Area(void) const
	{
		return Triangle(m_a, m_b, m_c).Area() + Triangle(m_a, m_c, m_d).Area();
	}

	// Accessors
	inline const Vector2 A(void) const { return m_a; }
	inline const Vector2 B(void) const { return m_b; }
	inline const Vector2 C(void) const { return m_c; }
	inline const Vector2 D(void) const { return m_d; }

private:

	Vector2 m_a, m_b, m_c, m_d;

};
