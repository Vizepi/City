#include <Line.h>

#include <cmath>

void Line::Translation(double distance)
{
	Vector2 orthogonal = Orthogonal();

	orthogonal = orthogonal * distance;

	m_a = m_a + orthogonal;
	m_b = m_b + orthogonal;
}

Vector2 Line::Orthogonal(void) const
{
	Vector2 orthogonal = (m_b - m_a).Orthogonal();
	orthogonal.Normalize();
	return orthogonal;
}

/*static*/ Vector2 Line::Intersection(const Line& a, const Line& b)
{
	double tmp1 = a.A().X() * a.B().Y() - a.A().Y() * a.B().X();
	double tmp2 = b.A().X() * b.B().Y() - b.A().Y() * b.B().X();
	double div = (a.A().X() - a.B().X()) * (b.A().Y() - b.B().Y()) - (a.A().Y() - a.B().Y()) * (b.A().X() - b.B().X());
	return Vector2(
		(tmp1 * (b.A().X() - b.B().X()) - (a.A().X() - a.B().X()) * tmp2) / div,
		(tmp1 * (b.A().Y() - b.B().Y()) - (a.A().Y() - a.B().Y()) * tmp2) / div
	);
}

/*static*/ double Line::Distance(const Line& l, const Vector2& p)
{
	/*double a, b;
	l.Equation(a, b);
	return fabs(a * p.X() - p.Y() + b) / sqrt(a * a + 1.0);*/

	Vector2 a = l.m_b - l.m_a;
	Vector2 b = p - l.m_a;
	double dot = DotProduct(a, b);
	return sqrt((p - l.m_a).SquareLength() - (dot * dot / a.SquareLength()));
}

/*static*/ double Line::OrientedDistance(const Line& l, const Vector2& p)
{
	/*double a, b;
	l.Equation(a, b);
	return (a * p.X() - p.Y() + b) / sqrt(a * a + 1.0);*/


	Vector2 a = l.m_b - l.m_a;
	Vector2 b = p - l.m_a;
	double dot = DotProduct(a, b);
	return (CrossProduct(a, b) > 0.0 ? 1.0 : -1.0) * sqrt((p - l.m_a).SquareLength() - (dot * dot / a.SquareLength()));
}
