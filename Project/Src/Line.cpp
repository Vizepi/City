#include <Line.h>

void Line::Translation(double distance)
{
	Vector2 orthogonal = (m_b - m_a).Orthogonal();
	orthogonal.Normalize();

	orthogonal = orthogonal * Vector2(distance, distance);

	m_a = m_a + orthogonal;
	m_b = m_b + orthogonal;
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
