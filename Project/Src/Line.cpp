#include <Line.h>

void Line::Translation(double distance)
{
	Vector2 orthogonal(-(m_b.Y() - m_a.Y()), m_b.X() - m_a.X());

}
