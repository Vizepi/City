#pragma once

#include <Vector.h>

#include <limits>

class Line
{

public:

	inline Line(void) : m_a(), m_b() {}
	inline Line(const Vector2 & a, const Vector2 & b) : m_a(a), m_b(b) {}
	inline Line(const Line& rhs) : m_a(rhs.m_a), m_b(rhs.m_b) {}

	void Translation(double distance);
	Vector2 Orthogonal(void) const;

	// Accessors
	inline const Vector2 & A(void) const { return m_a; }
	inline const Vector2 & B(void) const { return m_b; }

	inline void SetA(const Vector2 & a) { m_a = a; }
	inline void SetB(const Vector2 & b) { m_b = b; }

	inline void Equation(double & a, double & b) const
	{
		a = (m_a.X() != m_b.X()) ? (m_b.Y() - m_a.Y())/(m_b.X() - m_a.X()) : std::numeric_limits<double>::max();
		b = m_a.Y() - a * m_a.X();
	}

	inline Vector2 Center(void) const { return m_a + (m_b - m_a) / 2.0; }

	static Vector2 Intersection(const Line & a, const Line & b);
	static double Distance(const Line & l, const Vector2 & p);
	static double OrientedDistance(const Line & l, const Vector2 & p);

private:

	Vector2 m_a, m_b;

};