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
	//
	// Get settings
	// Setting::GetInstance();
	
	//--------------
	// V0 - 1 Building
	//--------------
	BuildTerrain(obj, 0.0, 10.0);

	//--------------
	// V1 - 1 Building + shrink
	//--------------
	double walkWaySize = 5.0;
	Shrink(walkWaySize, walkWaySize, walkWaySize, walkWaySize);
	BuildTerrain(obj, 0.0, 10.0);

	//--------------
	// V2 - Neighborhood
	//--------------
	Quad innerQuad(*this);
	innerQuad.Shrink(walkWaySize, walkWaySize, walkWaySize, walkWaySize);
	
	//
	// Bat 1
	Vector2 a = m_a;
	Vector2 b = m_a;
	Vector2 c = innerQuad.A();
	Vector2 d = m_a;
	BuildTerrain(Quad(), 0.0, 10.0);


	//
	// Random seed
	random::seed(m_seed);
	
	//
	// Attributs
	/*double MaxQuadBuildingSize = 75.0;
	double MinQuadBuildingSize = 20.0;*/ 
	
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
		/*uint64_t nbBatAB = ab / MinQuadBuildingSize;
		if(ab > 2.0*MinQuadBuildingSize)
		{
			
		}*/
		while(crtLength < ab)
		{
			
		}
	}
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
