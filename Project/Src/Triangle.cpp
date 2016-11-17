#include <Triangle.h>
#include <Line.h>

void Triangle::Subdivide(std::vector<Shape>& mesh)
{

}

void Triangle::BuildNeighborhood(std::vector<Shape>& mesh)
{

}

void Triangle::BuildBuilding(std::ofstream & obj, uint32_t globalHeight)
{

}

void Triangle::Shrink(double roadSizeAB, double roadSizeBC, double roadSizeCA)
{
	Line ab(m_a, m_b);
	Line bc(m_b, m_c);
	Line ca(m_c, m_a);

	ab.Translation(roadSizeAB / 2.0);
	bc.Translation(roadSizeBC / 2.0);
	ca.Translation(roadSizeCA / 2.0);

	m_a = Line::Intersection(ab, ca);
	m_b = Line::Intersection(ab, bc);
	m_c = Line::Intersection(bc, ca);
}
