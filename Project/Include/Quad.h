#pragma once

#include <Vector.h>
#include <Triangle.h>
#include <Shape.h>

class Quad : public Shape
{
public:

	inline Quad(void) : m_a(), m_b(), m_c(), m_d() {}
	inline Quad(const Vector2& a, const Vector2& b, const Vector2& c, const Vector2& d) : m_a(a), m_b(b), m_c(c), m_d(d) {}

	virtual void Subdivide(std::vector<Shape>& mesh);
	virtual void BuildNeighborhood(std::vector<Shape>& mesh);
    virtual void BuildBuilding(std::ofstream & obj, uint32_t minGlobalHeight, uint32_t maxGlobalHeight);

	inline double Area(void) const
	{
		return Triangle(m_a, m_b, m_c).Area() + Triangle(m_a, m_c, m_d).Area();
	}

	// Accessors
	inline const Vector2& A(void) const { return m_a; }
	inline const Vector2& B(void) const { return m_b; }
	inline const Vector2& C(void) const { return m_c; }
	inline const Vector2& D(void) const { return m_d; }

	inline void SetA(const Vector2& a) { m_a = a; }
	inline void SetB(const Vector2& b) { m_b = b; }
	inline void SetC(const Vector2& c) { m_c = c; }
	inline void SetD(const Vector2& d) { m_d = d; }

private:

	Vector2 m_a, m_b, m_c, m_d;

};
