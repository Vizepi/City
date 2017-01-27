#include <Triangle.h>
#include <Line.h>
#include <Object.h>

void Triangle::Subdivide(Object & obj)
{
	obj << "v " << m_a.X() << " " << m_a.Y() << " 0\n";
	obj << "v " << m_b.X() << " " << m_b.Y() << " 0\n";
	obj << "v " << m_c.X() << " " << m_c.Y() << " 0\n";
	obj << "f -1 -2 -3\n";
}

void Triangle::BuildNeighborhood(Object & obj)
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
