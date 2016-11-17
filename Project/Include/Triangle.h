#pragma once

#include <cmath>

#include <Vector.h>
#include <Shape.h>

class Triangle : public Shape
{
public:

	inline Triangle()
	{

	}

	inline Triangle(const Vector2& a, const Vector2& b, const Vector2& c) : m_a(a), m_b(b), m_c(c) {}

	virtual void Subdivide(std::vector<Shape>& mesh);

	inline double Area(void) const
	{
		return abs(Product(m_a - m_b, m_a - m_c)) / 2.0;
	}

	// Accessors
	inline const Vector2 A(void) const { return m_a; }
	inline const Vector2 B(void) const { return m_b; }
	inline const Vector2 C(void) const { return m_c; }

private:

	Vector2 m_a, m_b, m_c;

};
