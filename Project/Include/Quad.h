#pragma once

#include <Vector.h>
#include <Triangle.h>
#include <Shape.h>

class Quad : public Shape
{
public:

	inline Quad(void) : Shape(), m_a(), m_b(), m_c(), m_d() {}
	inline Quad(const Vector2 & a, const Vector2 & b, const Vector2 & c, const Vector2 & d) : Shape(), m_a(a), m_b(b), m_c(c), m_d(d) {}
	inline Quad(uint64_t seed) : Shape(seed), m_a(), m_b(), m_c(), m_d() {}
	inline Quad(uint64_t seed, const Vector2 & a, const Vector2 & b, const Vector2 & c, const Vector2 & d) : Shape(seed), m_a(a), m_b(b), m_c(c), m_d(d) {}

	virtual void Subdivide(std::ofstream & obj);
	virtual void BuildNeighborhood(std::ofstream & obj);
	inline virtual double Area(void) const
	{
		return Triangle(m_a, m_b, m_c).Area() + Triangle(m_a, m_c, m_d).Area();
	}

	inline void Shrink(double roadSize) { Shrink(roadSize, roadSize, roadSize, roadSize); }
	void Shrink(double roadSizeAB, double roadSizeBC, double roadSizeCD, double roadSizeDA);

	// Accessors
	inline const Vector2 & A(void) const { return m_a; }
	inline const Vector2 & B(void) const { return m_b; }
	inline const Vector2 & C(void) const { return m_c; }
	inline const Vector2 & D(void) const { return m_d; }

	inline void SetA(const Vector2 & a) { m_a = a; }
	inline void SetB(const Vector2 & b) { m_b = b; }
	inline void SetC(const Vector2 & c) { m_c = c; }
	inline void SetD(const Vector2 & d) { m_d = d; }

private:

	Vector2 m_a, m_b, m_c, m_d;

};
