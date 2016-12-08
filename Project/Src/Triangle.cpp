#include <Triangle.h>
#include <Line.h>

void Triangle::Subdivide(std::ofstream & obj)
{

}

void Triangle::BuildNeighborhood(std::ofstream & obj)
{
	//
	// Check space for buildings
	
	//
	// Divide Neighborhood ans build buildings
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
