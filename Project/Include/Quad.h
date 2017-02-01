#pragma once

#include <Vector.h>
#include <Triangle.h>
#include <Shape.h>
#include <Random.h>
#include <Line.h>

class Quad : public Shape
{
public:

	inline Quad(void) : Shape(), m_a(), m_b(), m_c(), m_d(), m_ab(false), m_bc(false), m_cd(false), m_da(false) {}
	inline Quad(const Quad & q) : Shape(), m_a(q.A()), m_b(q.B()), m_c(q.C()), m_d(q.D()), m_ab(q.m_ab), m_bc(q.m_bc), m_cd(q.m_cd), m_da(q.m_da) {}
	inline Quad(const Vector2 & a, const Vector2 & b, const Vector2 & c, const Vector2 & d) : Shape(), m_a(a), m_b(b), m_c(c), m_d(d), m_ab(false), m_bc(false), m_cd(false), m_da(false) {}
	inline Quad(uint64_t seed) : Shape(seed), m_a(), m_b(), m_c(), m_d(), m_ab(false), m_bc(false), m_cd(false), m_da(false) {}
	inline Quad(uint64_t seed, const Vector2 & a, const Vector2 & b, const Vector2 & c, const Vector2 & d) : Shape(seed), m_a(a), m_b(b), m_c(c), m_d(d), m_ab(false), m_bc(false), m_cd(false), m_da(false) {}

	int GetSubdivisionType(void) const;

	virtual void Subdivide(Object & obj);
	virtual void BuildNeighborhood(Object & obj, BuildingSetting& setting);

    void DrawBuildingGround (Object & obj, BuildingSetting & setting);
    void DrawBuildingFloor  (Object & obj, BuildingSetting & setting, int height);
    void DrawBuildingRoof   (Object & obj, BuildingSetting & setting, int height);
    void DrawEmptySpace     (Object & obj, BuildingSetting & setting, int height);

	inline virtual double Area(void) const
	{
		return Triangle(m_a, m_b, m_c).Area() + Triangle(m_a, m_c, m_d).Area();
	}

	inline Vector2 Center(void) const
	{
		return 	Line::Intersection(Line(A(), C()), Line(B(), D()));
	}
	
	inline void Shrink(double roadSize) { Shrink(roadSize, roadSize, roadSize, roadSize); }
	void Shrink(double roadSizeAB, double roadSizeBC, double roadSizeCD, double roadSizeDA);

	Quad GetInscribedRectangle(void) const;
	Quad GetInscribedSquare(void) const;
	bool IsWellFormed(void) const;

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

	inline bool Contains(const Vector2 & rhs) const
	{
		return
			CrossProduct(m_b - m_a, rhs - m_a) > 0.0 &&
			CrossProduct(m_c - m_b, rhs - m_b) > 0.0 &&
			CrossProduct(m_d - m_c, rhs - m_c) > 0.0 &&
			CrossProduct(m_a - m_d, rhs - m_d) > 0.0;
	}
	bool Intersects(const Quad & rhs) const;
	void Rotate(double angle);

private:

	Vector2 m_a, m_b, m_c, m_d;
	bool m_ab, m_bc, m_cd, m_da;

};
