#include <Triangle.h>
#include <Line.h>

void Triangle::Subdivide(std::ofstream & obj)
{

}

void Triangle::BuildNeighborhood(std::ofstream & obj)
{
	uint64_t crtVersion = 1;
	//
	// Get settings
	BuildingSetting s = Setting::GetInstance(Center());
	
	//--------------
	// V0 - 1 Building
	//--------------
	if(0 == crtVersion)
	{
		BuildTerrain(obj, s);
	}
	
	//--------------
	// V1 - 1 Building + shrink
	//--------------
	else if(1 == crtVersion)
	{
		double walkWaySize = 5.0;
		Shrink(walkWaySize);
		BuildTerrain(obj, s);
	}
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
