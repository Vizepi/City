#include <Quad.h>
#include <Line.h>
#include <Random.h>

void Quad::Subdivide(std::ofstream & obj)
{
	Random::Seed(m_seed);
	uint64_t type = 0;
	double area = Area();
	// TODO : Change type
	double stopChance = Setting::Ease(area, double(75ull * 75ull), double(300ull * 300ull));
	if (stopChance < Random::NextDouble())
	{
		BuildNeighborhood(obj);
	}
	double roadSize = Setting::Ease(area, double(2000ull * 2000ull), double(200ull * 200ull)) * 36.0 + 4.0;
	switch (type)
	{
	case 0: // Divided once edges AB and CD
		{
			double abLength = (m_b - m_a).Length();
			double cdLength = (m_d - m_c).Length();
			double abPosition = Random::NextDouble(abLength * 0.4, abLength * 0.6);
			double cdPosition = Random::NextDouble(cdLength * 0.4, cdLength * 0.6);
			Vector2 pAB = m_a + (m_b - m_a) * abPosition;
			Vector2 pCD = m_d + (m_c - m_d) * cdPosition;
			Quad q1(Random::NextUInt64(), m_a, pAB, pCD, m_d);
			q1.Shrink(IsShrinkedAB() ? 0.0 : roadSize, roadSize, IsShrinkedCD() ? 0.0 : roadSize, IsShrinkedDA() ? 0.0 : roadSize);
			q1.SetABShrinked(true).SetBCShrinked(true).SetCDShrinked(true).SetDAShrinked(true);
			Quad q2(Random::NextUInt64(), pAB, m_b, m_d, pCD);
			q2.Shrink(IsShrinkedAB() ? 0.0 : roadSize, IsShrinkedBC() ? 0.0 : roadSize, IsShrinkedCD() ? 0.0 : roadSize, roadSize);
			q2.SetABShrinked(true).SetBCShrinked(true).SetCDShrinked(true).SetDAShrinked(true);
			q1.Subdivide(obj);
			q2.Subdivide(obj);
		}
		break;
	case 1:
		{
			double bcLength = (m_c - m_b).Length();
			double daLength = (m_a - m_d).Length();
			double bcPosition = Random::NextDouble(bcLength * 0.4, bcLength * 0.6);
			double daPosition = Random::NextDouble(daLength * 0.4, daLength * 0.6);
			Vector2 pBC = m_b + (m_c - m_b) * bcPosition;
			Vector2 pDA = m_d + (m_a - m_d) * daPosition;
			Quad q1(Random::NextUInt64(), m_a, m_b, pBC, pDA);
			q1.Shrink(IsShrinkedAB() ? 0.0 : roadSize, IsShrinkedBC() ? 0.0 : roadSize, roadSize, IsShrinkedDA() ? 0.0 : roadSize);
			q1.SetABShrinked(true).SetBCShrinked(true).SetCDShrinked(true).SetDAShrinked(true);
			Quad q2(Random::NextUInt64(),pDA, pBC, m_c, m_d);
			q2.Shrink(roadSize, IsShrinkedBC() ? 0.0 : roadSize, IsShrinkedCD() ? 0.0 : roadSize, IsShrinkedDA() ? 0.0 : roadSize);
			q2.SetABShrinked(true).SetBCShrinked(true).SetCDShrinked(true).SetDAShrinked(true);
			q1.Subdivide(obj);
			q2.Subdivide(obj);
		}
		break;
	case 2:
		break;
	case 3:
		break;
	case 4:
		break;
	default:
		break;
	}
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
