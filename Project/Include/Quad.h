#pragma once

#include <Vector.h>
#include <Triangle.h>
#include <Shape.h>

class Quad : public Shape
{
public:

	inline Quad(void) : Shape(), m_a(), m_b(), m_c(), m_d(), m_ab(false), m_bc(false), m_cd(false), m_da(false) {}
	inline Quad(const Vector2 & a, const Vector2 & b, const Vector2 & c, const Vector2 & d) : Shape(), m_a(a), m_b(b), m_c(c), m_d(d), m_ab(false), m_bc(false), m_cd(false), m_da(false) {}
	inline Quad(uint64_t seed) : Shape(seed), m_a(), m_b(), m_c(), m_d(), m_ab(false), m_bc(false), m_cd(false), m_da(false) {}
	inline Quad(uint64_t seed, const Vector2 & a, const Vector2 & b, const Vector2 & c, const Vector2 & d) : Shape(seed), m_a(a), m_b(b), m_c(c), m_d(d), m_ab(false), m_bc(false), m_cd(false), m_da(false) {}

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

	inline Quad & SetA(const Vector2 & a) { m_a = a; return *this; }
	inline Quad & SetB(const Vector2 & b) { m_b = b; return *this; }
	inline Quad & SetC(const Vector2 & c) { m_c = c; return *this; }
	inline Quad & SetD(const Vector2 & d) { m_d = d; return *this; }

	inline bool IsShrinkedAB(void) const { return m_ab; }
	inline bool IsShrinkedBC(void) const { return m_bc; }
	inline bool IsShrinkedCD(void) const { return m_cd; }
	inline bool IsShrinkedDA(void) const { return m_da; }

	inline Quad & SetABShrinked(bool shrinked) { m_ab = shrinked; return *this; }
	inline Quad & SetBCShrinked(bool shrinked) { m_bc = shrinked; return *this; }
	inline Quad & SetCDShrinked(bool shrinked) { m_cd = shrinked; return *this; }
	inline Quad & SetDAShrinked(bool shrinked) { m_da = shrinked; return *this; }

private:

	Vector2 m_a, m_b, m_c, m_d;
	bool m_ab, m_bc, m_cd, m_da;

};
