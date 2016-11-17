#pragma once

#include <Vector.h>

class Line
{

public:

	inline Line(void) : m_a(), m_b() {}
	inline Line(const Vector2& a, const Vector2& b) : m_a(a), m_b(b) {}

	inline void Translation(double distance)
	{
		Vector2 orthogonal(0, 0);
	}

	inline const Vector2& A(void) const { return m_a; }
	inline const Vector2& B(void) const { return m_b; }

private:

	Vector2 m_a, m_b;

};
