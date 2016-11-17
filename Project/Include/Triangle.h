#pragma once

#include <cmath>

#include <Vector.h>
#include <Shape.h>

class Triangle : public Shape
{
public:

	inline Triangle(void) : m_a(), m_b(), m_c() {}

	inline Triangle(const Vector2& a, const Vector2& b, const Vector2& c) : m_a(a), m_b(b), m_c(c) {}

	virtual void Subdivide(std::vector<Shape>& mesh);
	virtual void BuildNeighborhood(std::vector<Shape>& mesh);
	virtual void BuildBuilding(std::ofstream& obj, uint32_t globalHeight);

	inline double Area(void) const
	{
		return abs(Product(m_a - m_b, m_a - m_c)) / 2.0;
	}

	inline void Shrink(double roadSize) { Shrink(roadSize, roadSize, roadSize);  }
	void Shrink(double roadSizeAB, double roadSizeBC, double roadSizeCA);

	// Accessors
	inline const Vector2& A(void) const { return m_a; }
	inline const Vector2& B(void) const { return m_b; }
	inline const Vector2& C(void) const { return m_c; }

	inline void SetA(const Vector2& a) { m_a = a; }
	inline void SetB(const Vector2& b) { m_b = b; }
	inline void SetC(const Vector2& c) { m_c = c; }

private:

	Vector2 m_a, m_b, m_c;

};
