#pragma once

#include <Setting.h>

#include <Vector.h>
#include <Shape.h>
#include <cmath>

class Triangle : public Shape
{
public:

	inline Triangle(void) : Shape(), m_a(), m_b(), m_c(), m_ab(false), m_bc(false), m_ca(false) {}
	inline Triangle(const Triangle & t) : Shape(), m_a(t.A()), m_b(t.B()), m_c(t.C()), m_ab(t.m_ab), m_bc(t.m_bc), m_ca(t.m_ca) {}
	inline Triangle(const Vector2 & a, const Vector2 & b, const Vector2 & c) : Shape(), m_a(a), m_b(b), m_c(c), m_ab(false), m_bc(false), m_ca(false) {}
	inline Triangle(uint64_t seed) : Shape(seed), m_a(), m_b(), m_c(), m_ab(false), m_bc(false), m_ca(false) {}

	inline Triangle(uint64_t seed, const Vector2 & a, const Vector2 & b, const Vector2 & c) : Shape(seed), m_a(a), m_b(b), m_c(c), m_ab(false), m_bc(false), m_ca(false) {}

	int GetSubdivisionType(void) const;

	virtual void Subdivide(Object & obj);
	virtual void BuildNeighborhood(Object & obj);

    void DrawBuildingGround (Object & obj, BuildingSetting & setting);
    void DrawBuildingFloor  (Object & obj, BuildingSetting & setting);
    void DrawBuildingRoof   (Object & obj, BuildingSetting & setting);
    void DrawEmptySpace     (Object & obj, BuildingSetting & setting);

	inline virtual double Area(void) const
	{
		return fabs(CrossProduct(m_a - m_b, m_a - m_c)) / 2.0;
	}

	inline Vector2 Center(void) const
	{
		return (A()+B()+C())/3;
	}
	
	inline void Shrink(double roadSize) { Shrink(roadSize, roadSize, roadSize);  }
	void Shrink(double roadSizeAB, double roadSizeBC, double roadSizeCA);

	// Accessors
	inline const Vector2 & A(void) const { return m_a; }
	inline const Vector2 & B(void) const { return m_b; }
	inline const Vector2 & C(void) const { return m_c; }

	inline Triangle & SetA(const Vector2 & a) { m_a = a; return *this; }
	inline Triangle & SetB(const Vector2 & b) { m_b = b; return *this; }
	inline Triangle & SetC(const Vector2 & c) { m_c = c; return *this; }

	inline bool IsShrinkedAB(void) const { return m_ab; }
	inline bool IsShrinkedBC(void) const { return m_bc; }
	inline bool IsShrinkedCA(void) const { return m_ca; }

	inline Triangle & SetABShrinked(bool shrinked) { m_ab = shrinked; return *this; }
	inline Triangle & SetBCShrinked(bool shrinked) { m_bc = shrinked; return *this; }
	inline Triangle & SetCAShrinked(bool shrinked) { m_ca = shrinked; return *this; }

private:

	Vector2 m_a, m_b, m_c;
	bool m_ab, m_bc, m_ca;

};
