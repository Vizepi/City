#include <Quad.h>
#include <Line.h>
#include <Random.h>

void Quad::Subdivide(std::ofstream & obj)
{
	/*double probabilitySum = 0.0;
	Random::Seed(m_seed);
	double rand = Random::NextDouble();
	uint64_t index = 0;
	while (probabilitySum < rand)
	{

	}*/
}

void Quad::BuildNeighborhood(std::ofstream & obj) // Add const vector3 &v with the downtown
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
		Shrink(walkWaySize, walkWaySize, walkWaySize, walkWaySize);
		BuildTerrain(obj, s);
	}
	//--------------
	// V2 - Neighborhood
	//--------------
	else if(2 == crtVersion)
	{
		double walkWaySize = 5.0;
		Quad innerQuad(*this);
		innerQuad.Shrink(walkWaySize, walkWaySize, walkWaySize, walkWaySize);
		
		//
		// Bat 1
		Vector2 a = m_a;
		Vector2 b = Projection(Vector2(innerQuad.A() - m_a),Vector2(m_b - m_a)); // innerQuad.A() on m_a m_b
		Vector2 c = innerQuad.A();
		Vector2 d = Projection(Vector2(innerQuad.A() - m_a),Vector2(m_d - m_a));
		innerQuad.BuildTerrain(obj, s);
	}

	//
	// Random seed
	/*random::seed(m_seed);
	
	//
	// Attributs
	//double MaxQuadBuildingSize = 75.0;
	//double MinQuadBuildingSize = 20.0;
	
	Setting::GetINstance(VEC2
	
	bool isWellFormed = true;
	
	//
	// Check space for buildings
	double ab = (m_a - m_b).Length();
	double bc = (m_b - m_c).Length();
	double cd = (m_c - m_d).Length();
	double da = (m_d - m_a).Length();
	if(ab < MinQuadBuildingSize
		|| bc < MinQuadBuildingSize
		|| cd < MinQuadBuildingSize
		|| da < MinQuadBuildingSize)
	{
		isWellFormed = false;
	}
	
	//
	// Divide Neighborhood ans build buildings
	if(isWellFormed)
	{
		uint64_t nbBatAB = ab / MinQuadBuildingSize;
		if(ab > 2.0*MinQuadBuildingSize)
		{
			
		}
		while(crtLength < ab)
		{
			
		}
	}*/
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
