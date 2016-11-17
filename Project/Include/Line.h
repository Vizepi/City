#pragma once

#include <Vector.h>

class Line
{

public:

	inline Line(void) : m_a(), m_b() {}
	inline Line(const Vector2& a, const Vector2& b) : m_a(a), m_b(b) {}

	void Translation(double distance);

	// Accessors
	inline const Vector2& A(void) const { return m_a; }
	inline const Vector2& B(void) const { return m_b; }

	inline void SetA(const Vector2& a) { m_a = a; }
	inline void SetB(const Vector2& b) { m_b = b; }

private:

	Vector2 m_a, m_b;

};
