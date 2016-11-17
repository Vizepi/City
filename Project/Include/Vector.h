#pragma once

class Vector2
{

public:

	inline Vector2(void) : m_x(0.0), m_y(0.0) {}
	inline Vector2(double x, double y) : m_x(x), m_y(y) {}
	inline Vector2(const Vector2& rhs) : m_x(rhs.m_x), m_y(rhs.m_y) {}
	inline virtual ~Vector2(void) {}

	inline void operator=(const Vector2& rhs) { m_x = rhs.m_x; m_y = rhs.m_y; }

	inline double X(void) const { return m_x; }
	inline double Y(void) const { return m_y; }

	inline void SetX(double x) { m_x = x; }
	inline void SetY(double y) { m_y = y; }

protected:

	double m_x, m_y;

};

inline double Product(const Vector2& a, const Vector2& b)
{
	return a.X() * b.Y() - a.Y() * b.X();
}

inline double DotProduct(const Vector2& a, const Vector2& b)
{
	return a.X() * b.X() + a.Y() * b.Y();
}

inline Vector2 operator-(const Vector2& a, const Vector2& b)
{
	return Vector2(a.X() - b.X(), a.Y() - b.Y());
}

inline Vector2 operator+(const Vector2& a, const Vector2& b)
{
	return Vector2(a.X() + b.X(), a.Y() + b.Y());
}

inline Vector2 operator*(const Vector2& a, const Vector2& b)
{
	return Vector2(a.X() * b.X(), a.Y() * b.Y());
}

inline Vector2 operator/(const Vector2& a, const Vector2& b)
{
	return Vector2(a.X() / b.X(), a.Y() / b.Y());
}

class Vector3
{

public:

	inline Vector3(void) : m_x(0.0), m_y(0.0), m_z(0.0) {}
	inline Vector3(double x, double y, double z) : m_x(x), m_y(y), m_z(z) {}
	inline Vector3(const Vector3& rhs) : m_x(rhs.m_x), m_y(rhs.m_y), m_z(rhs.m_z) {}
	inline virtual ~Vector3(void) {}

	inline void operator=(const Vector3& rhs) { m_x = rhs.m_x; m_y = rhs.m_y; m_z = rhs.m_z; }

	inline double X(void) const { return m_x; }
	inline double Y(void) const { return m_y; }
	inline double Z(void) const { return m_z; }

	inline void SetX(double x) { m_x = x; }
	inline void SetY(double y) { m_y = y; }
	inline void SetZ(double z) { m_z = z; }

protected:

	double m_x, m_y, m_z;

};
