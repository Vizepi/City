#include <Quad.h>
#include <Line.h>
#include <Random.h>

void Quad::Subdivide(std::ofstream & obj)
{
	double probabilitySum = 0.0;
	Random::Seed(m_seed);
	double rand = Random::NextDouble();
	uint64_t index = 0;
	while (probabilitySum < rand)
	{
		
	}
}

void Quad::BuildNeighborhood(std::ofstream & obj) // Add const vector3 &v with the downtown
{

}

void Quad::Shrink(double roadSizeAB, double roadSizeBC, double roadSizeCD, double roadSizeDA)
{
	Line ab(m_a, m_b);
	Line bc(m_b, m_c);
	Line cd(m_c, m_d);
	Line da(m_d, m_a);

	ab.Translation(roadSizeAB / 2.0);
	bc.Translation(roadSizeBC / 2.0);
	cd.Translation(roadSizeCD / 2.0);
	da.Translation(roadSizeDA / 2.0);

	m_a = Line::Intersection(ab, da);
	m_b = Line::Intersection(ab, bc);
	m_c = Line::Intersection(bc, cd);
	m_d = Line::Intersection(cd, da);
}
